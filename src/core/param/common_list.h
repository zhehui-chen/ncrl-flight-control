#ifndef __COMMON_LIST_H__
#define __COMMON_LIST_H__

enum {
	/*********************************************
	 * ncrl flight controller defined parameters *
	 *********************************************/
	IMU_FINISH_CALIB = 0,

	/*****************************
	 * px4 compatible parameters *
	 *****************************/
	/* airframe */
	MAV_TYPE,
	/* sensor calibration */
	CAL_ACC0_EN,
	CAL_ACC0_ID,
	CAL_ACC0_XOFF,
	CAL_ACC0_XSCALE,
	CAL_ACC0_YOFF,
	CAL_ACC0_YSCALE,
	CAL_ACC0_ZOFF,
	CAL_ACC0_ZSCALE,
	CAL_ACC1_EN,
	CAL_ACC1_ID,
	CAL_ACC1_XOFF,
	CAL_ACC1_XSCALE,
	CAL_ACC1_YOFF,
	CAL_ACC1_YSCALE,
	CAL_ACC1_ZOFF,
	CAL_ACC1_ZSCALE,
	CAL_ACC_PRIME,
	CAL_BARO_PRIME,
	CAL_GYRO0_EN,
	CAL_GYRO0_ID,
	CAL_GYRO0_XOFF,
	CAL_GYRO0_XSCALE,
	CAL_GYRO0_YOFF,
	CAL_GYRO0_YSCALE,
	CAL_GYRO0_ZOFF,
	CAL_GYRO0_ZSCALE,
	CAL_GYRO1_EN,
	CAL_GYRO1_ID,
	CAL_GYRO1_XOFF,
	CAL_GYRO1_XSCALE,
	CAL_GYRO1_YOFF,
	CAL_GYRO1_YSCALE,
	CAL_GYRO1_ZOFF,
	CAL_GYRO1_ZSCALE,
	CAL_MAG0_EN,
	CAL_MAG0_ID,
	CAL_MAG0_ROT,
	CAL_MAG0_XOFF,
	CAL_MAG0_XSCALE,
	CAL_MAG0_YOFF,
	CAL_MAG0_YSCALE,
	CAL_MAG0_ZOFF,
	CAL_MAG0_ZSCALE,
	CAL_MAG1_ID,
	CAL_MAG1_ROT,
	CAL_MAG2_ID,
	CAL_MAG2_ROT,
	CAL_MAG3_ID,
	CAL_MAG3_ROT,
	CAL_MAG_PRIME,
	SENS_DPRES_OFF,
	/* sensors */
	SENS_BOARD_X_OFF,
	SENS_BOARD_Y_OFF,
	SENS_BOARD_Z_OFF,
	SENS_BOARD_ROT,
	/* radio calibration */
	RC1_DZ,
	RC1_MAX,
	RC1_MIN,
	RC1_REV,
	RC1_TRIM,
	RC2_DZ,
	RC2_MAX,
	RC2_MIN,
	RC2_REV,
	RC2_TRIM,
	RC3_DZ,
	RC3_MAX,
	RC3_MIN,
	RC3_REV,
	RC3_TRIM,
	RC4_DZ,
	RC4_MAX,
	RC4_MIN,
	RC4_REV,
	RC4_TRIM,
	RC5_DZ,
	RC5_MAX,
	RC5_MIN,
	RC5_REV,
	RC5_TRIM,
	RC6_DZ,
	RC6_MAX,
	RC6_MIN,
	RC6_REV,
	RC6_TRIM,
	RC7_DZ,
	RC7_MAX,
	RC7_MIN,
	RC7_REV,
	RC7_TRIM,
	RC8_DZ,
	RC8_MAX,
	RC8_MIN,
	RC8_REV,
	RC8_TRIM,
	RC9_DZ,
	RC9_MAX,
	RC9_MIN,
	RC9_REV,
	RC9_TRIM,
	RC10_DZ,
	RC10_MAX,
	RC10_MIN,
	RC10_REV,
	RC10_TRIM,
	RC11_DZ,
	RC11_MAX,
	RC11_MIN,
	RC11_REV,
	RC11_TRIM,
	RC12_DZ,
	RC12_MAX,
	RC12_MIN,
	RC12_REV,
	RC12_TRIM,
	RC13_REV,
	RC13_TRIM,
	RC14_DZ,
	RC14_MAX,
	RC14_MIN,
	RC14_REV,
	RC14_TRIM,
	RC15_DZ,
	RC15_MAX,
	RC15_MIN,
	RC15_REV,
	RC15_TRIM,
	RC16_DZ,
	RC16_MAX,
	RC16_MIN,
	RC16_REV,
	RC16_TRIM,
	RC17_DZ,
	RC17_MAX,
	RC17_MIN,
	RC17_REV,
	RC17_TRIM,
	RC18_DZ,
	RC18_MAX,
	RC18_MIN,
	RC18_REV,
	RC18_TRIM,
	RC_CHAN_CNT,
	RC_FAILS_THR,
	RC_FLT_CUTOFF,
	RC_FLT_SMP_RATE,
	RC_MAP_AUX1,
	RC_MAP_AUX2,
	RC_MAP_AUX3,
	RC_MAP_AUX4,
	RC_MAP_AUX5,
	RC_MAP_FAILSAFE,
	RC_MAP_PARAM1,
	RC_MAP_PARAM2,
	RC_MAP_PARAM3,
	RC_MAP_PITCH,
	RC_MAP_ROLL,
	RC_MAP_THROTTLE,
	RC_MAP_YAW,
	RC_RSSI_PWM_CHAN,
	RC_RSSI_PWM_MAX,
	RC_RSSI_PWM_MIN,
	TRIM_PITCH,
	TRIM_ROLL,
	TRIM_YAW,
	/* radio switches */
	RC_ACRO_TH,
	RC_ARMSWITCH_TH,
	RC_ASSIST_TH,
	RC_AUTO_TH,
	RC_GEAR_TH,
	RC_KILLSWITCH_TH,
	RC_LOITER_TH,
	RC_MAN_TH,
	RC_MAP_ACRO_SW,
	RC_MAP_ARM_SW,
	RC_MAP_FLAPS,
	RC_MAP_FLTMODE,
	RC_MAP_GEAR_SW,
	RC_MAP_KILL_SW,
	RC_MAP_LOITER_SW,
	RC_MAP_MAN_SW,
	RC_MAP_MODE_SW,
	RC_MAP_OFFB_SW,
	RC_MAP_POSCTL_SW,
	RC_MAP_RATT_SW,
	RC_MAP_RETURN_SW,
	RC_MAP_STAB_SW,
	RC_MAP_TRANS_SW,
	RC_OFFB_TH,
	RC_POSCTL_TH,
	RC_RATT_TH,
	RC_RETURN_TH,
	RC_STAB_TH,
	RC_TRANS_TH,
	/* system */
	SYS_AUTOSTART,
	SYS_AUTOCONFIG,
	/* commander */
	COM_ARM_IMU_ACC,
	COM_ARM_IMU_GYR,
	COM_ARM_MAG,
	COM_ARM_MIS_REQ,
	COM_ARM_SWISBTN,
	COM_STM_WO_GPS,
	COM_DISARM_LAND,
	COM_DL_LOSS_T,
	COM_DL_REG_T,
	COM_EF_C2T,
	COM_EF_THROT,
	COM_EF_TIME1,
	COM_FLTMODE1,
	COM_FLTMODE2,
	COM_FLTMODE3,
	COM_FLTMODE4,
	COM_FLTMODE5,
	COM_FLTMODE6,
	COM_HLDL_LOSS_T,
	COM_HLDL_REG_T,
	COM_HOME_H_T,
	COM_HOME_V_T,
	COM_LOW_BAT_ACT,
	COM_OF_LOSS_T,
	COM_POS_FS_DELAY,
	COM_POS_FS_EPH,
	COM_POS_FS_EPV,
	COM_POS_FS_GAIN,
	COM_POS_FS_PROB,
	COM_RC_ARM_HYST,
	COM_RC_IN_MODE,
	COM_RC_LOSS_T,
	COM_RC_OVERIDE,
	COM_RC_STICK_OV,
	COM_VEL_FS_EVH,
	/* MAVLink */
	MAV_SYS_ID,
	/* Battery */
	BAT_A_PER_V,
	BAT_CAPACITY,
	BAT_CNT_V_CURR,
	BAT_CNT_V_VOLT,
	BAT_CRIT_THR,
	BAT_LOW_THR,
	BAT_N_CELLS,
	BAT_R_INTERNAL,
	BAT_SOURCE,
	BAT_V_CHARGED,
	BAT_V_DIV,
	BAT_V_EMPTY,
	BAT_V_LOAD_DROP,
	BAT_V_OFFS_CURR,
	/* return to land  */
	RTL_LAND_DELAY,
	RTL_DESCEND_ALT,
	RTL_RETURN_ALT,
	NAV_DLL_ACT,
	NAV_RCL_ACT,
	/*----------------------*/
	COMMON_PARAM_CNT
} COMMON_PARAM_ID;

void init_common_params(void);

#endif
