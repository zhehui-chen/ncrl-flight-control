#include "sys_param.h"

enum {
	MR_GEO_GAIN_ROLL_P,
	MR_GEO_GAIN_PITCH_P,
	MR_GEO_GAIN_YAW_P,
	MR_GEO_GAIN_ROLL_D,
	MR_GEO_GAIN_PITCH_D,
	MR_GEO_GAIN_YAW_D,
	MR_GEO_GAIN_RATE_ONLY_YAW_D,
	MR_GEO_GAIN_POS_X,
	MR_GEO_GAIN_POS_Y,
	MR_GEO_GAIN_POS_Z,
	MR_GEO_GAIN_VEL_X,
	MR_GEO_GAIN_VEL_Y,
	MR_GEO_GAIN_VEL_Z,
	MR_GEO_GAIN_POS_X_I,
	MR_GEO_GAIN_POS_Y_I,
	MR_GEO_GAIN_POS_Z_I,
	MR_GEO_UAV_MASS,
	MR_GEO_INERTIA_JXX,
	MR_GEO_INERTIA_JYY,
	MR_GEO_INERTIA_JZZ
} MULTIROTOR_GEOMETRY_PARAM_ID;

sys_param_data multirotor_geometry_param_list[] = {
	SYS_PARAM_ATTR("GAIN_ROLL_P", MR_GEO_GAIN_ROLL_P),
	SYS_PARAM_ATTR("GAIN_PITCH_P", MR_GEO_GAIN_PITCH_P),
	SYS_PARAM_ATTR("GAIN_YAW_P", MR_GEO_GAIN_YAW_P),
	SYS_PARAM_ATTR("GAIN_ROLL_D", MR_GEO_GAIN_ROLL_D),
	SYS_PARAM_ATTR("GAIN_PITCH_D", MR_GEO_GAIN_PITCH_D),
	SYS_PARAM_ATTR("GAIN_YAW_D", MR_GEO_GAIN_YAW_D),
	SYS_PARAM_ATTR("GAIN_RATE_ONLY_YAW_D", MR_GEO_GAIN_RATE_ONLY_YAW_D),
	SYS_PARAM_ATTR("GAIN_POS_X", MR_GEO_GAIN_POS_X),
	SYS_PARAM_ATTR("GAIN_POS_Y", MR_GEO_GAIN_POS_Y),
	SYS_PARAM_ATTR("GAIN_POS_Z", MR_GEO_GAIN_POS_Z),
	SYS_PARAM_ATTR("GAIN_VEL_X", MR_GEO_GAIN_VEL_X),
	SYS_PARAM_ATTR("GAIN_VEL_Y", MR_GEO_GAIN_VEL_Y),
	SYS_PARAM_ATTR("GAIN_VEL_Z", MR_GEO_GAIN_VEL_Z),
	SYS_PARAM_ATTR("GAIN_POS_X_I", MR_GEO_GAIN_POS_X_I),
	SYS_PARAM_ATTR("GAIN_POS_Y_I", MR_GEO_GAIN_POS_Y_I),
	SYS_PARAM_ATTR("GAIN_POS_Z_I", MR_GEO_GAIN_POS_Z_I),
	SYS_PARAM_ATTR("UAV_MASS", MR_GEO_UAV_MASS),
	SYS_PARAM_ATTR("INERTIA_JXX", MR_GEO_INERTIA_JXX),
	SYS_PARAM_ATTR("INERTIA_JYY", MR_GEO_INERTIA_JYY),
	SYS_PARAM_ATTR("INERTIA_JZZ", MR_GEO_INERTIA_JZZ)
};
