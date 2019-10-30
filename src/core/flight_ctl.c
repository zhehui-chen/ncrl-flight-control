#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "delay.h"
#include "bound.h"
#include "led.h"
#include "uart.h"
#include "sbus_receiver.h"
#include "mpu6500.h"
#include "motor.h"
#include "lpf.h"
#include "ahrs.h"
#include "madgwick_ahrs.h"
#include "flight_ctl.h"

void rc_safety_protection(void);

SemaphoreHandle_t flight_ctl_semphr;

imu_t imu;
ahrs_t ahrs;

pid_control_t pid_roll;
pid_control_t pid_pitch;
pid_control_t pid_yaw_rate;

float motor1, motor2, motor3, motor4;
radio_t rc;

void pid_controller_init(void)
{
	pid_roll.kp = 0.26f; //0.24
	pid_roll.ki = 0.025f;
	pid_roll.kd = 0.1f;  //0.09

	pid_pitch.kp = 0.26f;
	pid_pitch.ki = 0.025f;
	pid_pitch.kd = 0.1f;

	pid_yaw_rate.kp = 1.0f;
	pid_yaw_rate.ki = 0.0f;
	pid_yaw_rate.kd = 0.0f;
	pid_yaw_rate.output_min = -35.0f;
	pid_yaw_rate.output_max = 35.0f;
}

void flight_ctl_semaphore_handler(void)
{
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(flight_ctl_semphr, &xHigherPriorityTaskWoken);
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}

void imu_read(vector3d_f_t *accel, vector3d_f_t *gyro)
{
	mpu6500_read_unscaled_data(&imu.unscaled_accel, &imu.unscaled_gyro, &imu.unscaled_temp);
	mpu6500_fix_bias(&imu.unscaled_accel, &imu.unscaled_gyro);
	mpu6500_accel_convert_to_scale(&imu.unscaled_accel, accel);
	mpu6500_gyro_convert_to_scale(&imu.unscaled_gyro, gyro);
}

void task_flight_ctl(void *param)
{
	euler_t att_euler_est;

	rc_safety_protection();

	//initialize lpf
	imu_read(&imu.raw_accel, &imu.raw_gyro);
	imu.filtered_accel = imu.raw_accel;
	imu.filtered_gyro = imu.raw_gyro;

	ahrs_init(&imu.raw_accel);
	pid_controller_init();

	madgwick_t madgwick_ahrs_info;
	madgwick_init(&madgwick_ahrs_info, 400, 0.3);

	led_off(LED_R);
	led_off(LED_G);
	led_on(LED_B);

	while(1) {
		if(xSemaphoreTake(flight_ctl_semphr, 1) == pdFALSE) {
			continue;
		}

		read_rc_info(&rc);

		imu_read(&imu.raw_accel, &imu.raw_gyro);

		lpf(&imu.raw_accel, &imu.filtered_accel, 0.07);
		lpf(&imu.raw_gyro, &imu.filtered_gyro, 0.07);

#if 1
		ahrs_estimate(&att_euler_est, ahrs.q, imu.filtered_accel, imu.filtered_gyro);
		ahrs.attitude.roll = att_euler_est.roll;
		ahrs.attitude.pitch = att_euler_est.pitch;
		ahrs.attitude.yaw = att_euler_est.yaw;
#endif

#if 0
		madgwick_imu_ahrs(&madgwick_ahrs_info,
		                  imu.filtered_accel.x,
		                  imu.filtered_accel.y,
		                  imu.filtered_accel.z,
		                  deg_to_rad(imu.filtered_gyro.x),
		                  deg_to_rad(imu.filtered_gyro.y),
		                  deg_to_rad(imu.filtered_gyro.z));

		ahrs.attitude.roll = att_euler_est.roll = madgwick_ahrs_info.Roll;
		ahrs.attitude.pitch = att_euler_est.pitch = madgwick_ahrs_info.Pitch;
		ahrs.attitude.yaw = madgwick_ahrs_info.Yaw;

		ahrs.q[0] = madgwick_ahrs_info.q0;
		ahrs.q[1] = madgwick_ahrs_info.q1;
		ahrs.q[2] = madgwick_ahrs_info.q2;
		ahrs.q[3] = madgwick_ahrs_info.q3;
#endif
		attitude_pd_control(&pid_roll, att_euler_est.roll, -rc.roll, imu.filtered_gyro.x);
		attitude_pd_control(&pid_pitch, att_euler_est.pitch, -rc.pitch, imu.filtered_gyro.y);
		yaw_rate_p_control(&pid_yaw_rate, -rc.yaw, imu.filtered_gyro.z);

		if(rc.safety == false) {
			led_on(LED_R);
			led_off(LED_B);
			motor_control(rc.throttle, pid_roll.output, pid_pitch.output, pid_yaw_rate.output);
		} else {
			led_on(LED_B);
			led_off(LED_R);
			motor_control(0.0, 0, 0, 0);
		}

		//debug_print_rc_info(&rc);

		taskYIELD();
	}
}

void rc_safety_protection(void)
{
	radio_t rc;

	do {
		read_rc_info(&rc);
	} while(rc_safety_check(&rc) == 1);
}

void attitude_pd_control(pid_control_t *pid, float ahrs_attitude,
                         float setpoint_attitude, float angular_velocity)
{
	//error = reference (setpoint) - measurement
	pid->error_current = setpoint_attitude - ahrs_attitude;
	pid->error_integral += (pid->error_current * pid->ki * 0.0025);
	pid->error_derivative = -angular_velocity; //error_derivative = 0 (setpoint) - measurement_derivative

	bound_float(&pid->error_integral, 10.0f, -10.0f);

	pid->p_final = pid->kp * pid->error_current;
	pid->i_final = pid->error_integral;
	pid->d_final = pid->kd * pid->error_derivative;

	pid->output = pid->p_final + pid->i_final + pid->d_final;
}

void yaw_rate_p_control(pid_control_t *pid, float setpoint_yaw_rate, float angular_velocity)
{
	pid->error_current = setpoint_yaw_rate - angular_velocity;

	pid->p_final = pid->kp * -pid->error_current;
	pid->output = pid->p_final;

	bound_float(&pid->output, pid->output_max, pid->output_min);
}

void motor_control(volatile float throttle_percentage, float roll_ctrl_precentage,
                   float pitch_ctrl_precentage, float yaw_ctrl_precentage)
{
	float percentage_to_pwm = 0.01 * (MOTOR_PULSE_MAX - MOTOR_PULSE_MIN);

	float power_basis = throttle_percentage * percentage_to_pwm + MOTOR_PULSE_MIN;

	float roll_pwm = roll_ctrl_precentage * (float)percentage_to_pwm;
	float pitch_pwm = pitch_ctrl_precentage * (float)percentage_to_pwm;
	float yaw_pwm = yaw_ctrl_precentage * (float)percentage_to_pwm;

	float m1_pwm, m2_pwm, m3_pwm, m4_pwm;

	/* (ccw)    (cw)
	    m2       m1
	         x
	    m3       m4
	   (cw)    (ccw) */
	m1_pwm = power_basis + roll_pwm + pitch_pwm - yaw_pwm;
	m2_pwm = power_basis - roll_pwm + pitch_pwm + yaw_pwm;
	m3_pwm = power_basis - roll_pwm - pitch_pwm - yaw_pwm;
	m4_pwm = power_basis + roll_pwm - pitch_pwm + yaw_pwm;
	bound_float(&m1_pwm, MOTOR_PULSE_MAX, MOTOR_PULSE_MIN);
	bound_float(&m2_pwm, MOTOR_PULSE_MAX, MOTOR_PULSE_MIN);
	bound_float(&m3_pwm, MOTOR_PULSE_MAX, MOTOR_PULSE_MIN);
	bound_float(&m4_pwm, MOTOR_PULSE_MAX, MOTOR_PULSE_MIN);

	//generate debug message
	motor1 = (m1_pwm - MOTOR_PULSE_MIN) / percentage_to_pwm;
	motor2 = (m2_pwm - MOTOR_PULSE_MIN) / percentage_to_pwm;
	motor3 = (m3_pwm - MOTOR_PULSE_MIN) / percentage_to_pwm;
	motor4 = (m4_pwm - MOTOR_PULSE_MIN) / percentage_to_pwm;
	bound_float(&motor1, 100.0f, 0.0f);
	bound_float(&motor2, 100.0f, 0.0f);
	bound_float(&motor3, 100.0f, 0.0f);
	bound_float(&motor4, 100.0f, 0.0f);

	set_motor_pwm_pulse(MOTOR1, (uint16_t)m1_pwm);
	set_motor_pwm_pulse(MOTOR2, (uint16_t)m2_pwm);
	set_motor_pwm_pulse(MOTOR3, (uint16_t)m3_pwm);
	set_motor_pwm_pulse(MOTOR4, (uint16_t)m4_pwm);
}
