#include "mks_cfg.h"
#include "draw_ui.h"
//#include "Extruder.h"
//#include "Repetier.h"
//#include "HAL.h"
#include "pic_manager.h"
#include "spi_flash.h"
//#include "Print.h"
#include "at24cxx.h"
#include "Eeprom.h"
#include <math.h>
#include <stdint.h>
#include "wifi_module.h"

//#include "others.h"

CFG_ITMES gCfgItems;

CFG_PRINTER_ITMES CfgPrinterItems;

PRINTER_DEFINE Change_Repetier_Define;

//#define  BAK_INF_VALID_FLAG			0x76313031//acsii --> V104   //0xaa558761

volatile u32 ugbksize;//flash中Unicode转GBK转换表大小值。

uint16_t readLcdId;

void recover_cfg_inf()
{
	volatile uint32_t  valid_flag;
	valid_flag = HAL::eprGetInt32(EPR_VALID_FLAG_CFG); 
	if(valid_flag == BAK_INF_VALID_FLAG)
	{
		gCfgItems.background_color = HAL::eprGetInt32(EPR_BACKGROUND_COLOR_CFG);
		gCfgItems.title_color = HAL::eprGetInt32(EPR_TITLE_COLOR_CFG);	
		gCfgItems.state_background_color = HAL::eprGetInt32(EPR_STATE_BACKGROUND_COLOR_CFG);
		gCfgItems.state_text_color = HAL::eprGetInt32(EPR_STATE_TEXT_COLOR_CFG);
		gCfgItems.filename_background_color = HAL::eprGetInt32(EPR_FILENAME_BACKGROUND_COLOE_CFG);
		gCfgItems.filename_color = HAL::eprGetInt32(EPR_FILENAME_COLOR_CFG);
		gCfgItems.printingstate_word_background_color = HAL::eprGetInt32(EPR_PRINTINGSTATE_TEXT_BACKGROUND_COLOR_CFG);
		gCfgItems.printingstate_word_color = HAL::eprGetInt32(EPR_PRINTINGSTATE_TEXT_COLOR_CFG);
		gCfgItems.button_3d_effect_flag = HAL::eprGetInt32(EPR_BUTTON_3D_EFFECTS_CFG);
		gCfgItems.language = HAL::eprGetInt32(EPR_LANGUAGE_TYPE_CFG);
        //gCfgItems.have_ups = HAL::eprGetByte(EPR_HAVE_UPS_CFG);
		CfgPrinterItems.cfg_ui_set_maxtemp = HAL::eprGetFloat(EPR_UI_SET_MAX_TEMPERATURE_CFG);
		CfgPrinterItems.cfg_ui_set_heated_bed_maxtemp = HAL::eprGetFloat(EPR_UI_SET_HEAT_BED_TEMPERATURE_CFG);
		gCfgItems.MoreItem_pic_cnt = HAL::eprGetByte(EPR_MOREITEM_PIC_CNT_CFG);	
		gCfgItems.func_btn1_display_flag = HAL::eprGetByte(EPR_SETMENU_FUNC1_DISPLAY_FLAG_CFG);
		gCfgItems.func_btn2_display_flag = HAL::eprGetByte(EPR_SETMENU_FUNC2_DISPLAY_FLAG_CFG);

		CfgPrinterItems.cfg_drive_system = HAL::eprGetByte(EPR_DRIVE_SYSTEM_CFG);
		CfgPrinterItems.cfg_ext0_tempsensor_type = HAL::eprGetByte(EPR_EXT0_TEMPSENSOR_TYPE_CFG);
		CfgPrinterItems.cfg_ext1_tempsensor_type = HAL::eprGetByte(EPR_EXT1_TEMPSENSOR_TYPE_CFG);
		CfgPrinterItems.cfg_heated_bed_sensor_type = HAL::eprGetByte(EPR_HEATED_BED_SENSOR_TYPE_CFG);
		CfgPrinterItems.cfg_delta_max_radius = HAL::eprGetFloat(EPR_DELTA_MAX_RADIUS_CFG);
		CfgPrinterItems.cfg_printer_radius = HAL::eprGetFloat(EPR_PRINTER_RADIUS_CFG);
		CfgPrinterItems.cfg_delta_diagonal_rod = HAL::eprGetFloat(EPR_DELTA_DIAGONAL_ROD_CFG);
		CfgPrinterItems.cfg_delta_floor_safety_margin_mm = HAL::eprGetFloat(EPR_DELTA_FLOOR_SAFETY_MARGIN_MM_CFG);
		CfgPrinterItems.cfg_feature_z_probe = HAL::eprGetByte(EPR_FEATURE_Z_PROBE_CFG);
		CfgPrinterItems.cfg_bed_leveling_method = HAL::eprGetByte(EPR_BED_LEVELING_METHOD_CFG);
		CfgPrinterItems.cfg_z_probe_height = HAL::eprGetFloat(EPR_Z_PROBE_HEIGHT_CFG);
		CfgPrinterItems.cfg_z_probe_x1 = HAL::eprGetFloat(EPR_Z_PROBE_X1_CFG);
		CfgPrinterItems.cfg_z_probe_y1 = HAL::eprGetFloat(EPR_Z_PROBE_Y1_CFG);
		CfgPrinterItems.cfg_z_probe_x2 = HAL::eprGetFloat(EPR_Z_PROBE_X2_CFG);
		CfgPrinterItems.cfg_z_probe_y2 = HAL::eprGetFloat(EPR_Z_PROBE_Y2_CFG);
		CfgPrinterItems.cfg_z_probe_x3 = HAL::eprGetFloat(EPR_Z_PROBE_X3_CFG);
		CfgPrinterItems.cfg_z_probe_y3 = HAL::eprGetFloat(EPR_Z_PROBE_Y3_CFG);
		CfgPrinterItems.cfg_xaxis_steps_per_mm = HAL::eprGetFloat(EPR_XAXIS_STEPS_PER_MM_CFG);
		CfgPrinterItems.cfg_yaxis_steps_per_mm = HAL::eprGetFloat(EPR_YAXIS_STEPS_PER_MM_CFG);
		CfgPrinterItems.cfg_zaxis_steps_per_mm = HAL::eprGetFloat(EPR_ZAXIS_STEPS_PER_MM_CFG);
		CfgPrinterItems.cfg_ext0_steps_per_mm = HAL::eprGetFloat(EPR_EXT0_STEPS_PER_MM_CFG);
		CfgPrinterItems.cfg_max_feedrate_x = HAL::eprGetFloat(EPR_MAX_FEEDRATE_X_CFG);
		CfgPrinterItems.cfg_max_feedrate_y = HAL::eprGetFloat(EPR_MAX_FEEDRATE_Y_CFG);
		CfgPrinterItems.cfg_max_feedrate_z = HAL::eprGetFloat(EPR_MAX_FEEDRATE_Z_CFG);
		CfgPrinterItems.cfg_max_feedrate_e0 = HAL::eprGetFloat(EPR_MAX_FEEDRATE_EXT0_CFG);
		CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_x = HAL::eprGetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_X_CFG);
		CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_y = HAL::eprGetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Y_CFG);
		CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_z = HAL::eprGetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Z_CFG);
		CfgPrinterItems.cfg_max_acceleration_e0 = HAL::eprGetFloat(EPR_MAX_ACCELERATION_EXT0_CFG);
		CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_x = HAL::eprGetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_X_CFG);
		CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_y = HAL::eprGetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Y_CFG);
		CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_z = HAL::eprGetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Z_CFG);
		CfgPrinterItems.cfg_homing_feedrate_x = HAL::eprGetFloat(EPR_HOMING_FEEDRATE_X_CFG);
		CfgPrinterItems.cfg_homing_feedrate_y = HAL::eprGetFloat(EPR_HOMING_FEEDRATE_Y_CFG);
		CfgPrinterItems.cfg_homing_feedrate_z = HAL::eprGetFloat(EPR_HOMING_FEEDRATE_Z_CFG);
		CfgPrinterItems.cfg_ext_mintemp = HAL::eprGetFloat(EPR_MIN_EXTRUDER_TEMP_CFG);
		CfgPrinterItems.cfg_ext_maxtemp = HAL::eprGetFloat(EPR_MAX_EXTRUDER_TEMP_CFG);
		CfgPrinterItems.cfg_heated_bed_maxtemp = HAL::eprGetFloat(EPR_MAX_HEATED_BED_TEMP_CFG);
		CfgPrinterItems.cfg_num_extruder = HAL::eprGetByte(EPR_NUM_EXTRUDER_CFG);
		CfgPrinterItems.cfg_have_heated_bed = HAL::eprGetByte(EPR_HAVE_HEATED_BED_CFG);
		CfgPrinterItems.cfg_invert_x_dir = HAL::eprGetByte(EPR_INVERT_X_DIR_CFG);
		CfgPrinterItems.cfg_invert_y_dir = HAL::eprGetByte(EPR_INVERT_Y_DIR_CFG);
		CfgPrinterItems.cfg_invert_z_dir = HAL::eprGetByte(EPR_INVERT_Z_DIR_CFG);
		CfgPrinterItems.cfg_invert_e0_dir = HAL::eprGetByte(EPR_EXT0_INVERSE_CFG);
		CfgPrinterItems.cfg_x_home_dir = HAL::eprGetByte(EPR_X_HOME_DIR_CFG);
		CfgPrinterItems.cfg_y_home_dir = HAL::eprGetByte(EPR_Y_HOME_DIR_CFG);
		CfgPrinterItems.cfg_z_home_dir = HAL::eprGetByte(EPR_Z_HOME_DIR_CFG);
		CfgPrinterItems.cfg_x_max_length = HAL::eprGetFloat(EPR_X_MAX_LENGTH_CFG);
		CfgPrinterItems.cfg_y_max_length = HAL::eprGetFloat(EPR_Y_MAX_LENGTH_CFG);
		CfgPrinterItems.cfg_z_max_length = HAL::eprGetFloat(EPR_Z_MAX_LENGTH_CFG);
		CfgPrinterItems.cfg_x_min_pos = HAL::eprGetFloat(EPR_X_MIN_POS_CFG);
		CfgPrinterItems.cfg_y_min_pos = HAL::eprGetFloat(EPR_Y_MIN_POS_CFG);
		CfgPrinterItems.cfg_z_min_pos = HAL::eprGetFloat(EPR_Z_MIN_POS_CFG);
		CfgPrinterItems.cfg_endstop_x_min_inverting = HAL::eprGetByte(EPR_ENDSTOP_X_MIN_INVERTING_CFG);
		CfgPrinterItems.cfg_endstop_y_min_inverting = HAL::eprGetByte(EPR_ENDSTOP_Y_MIN_INVERTING_CFG);
		CfgPrinterItems.cfg_endstop_z_min_inverting = HAL::eprGetByte(EPR_ENDSTOP_Z_MIN_INVERTING_CFG);
		CfgPrinterItems.cfg_endstop_x_max_inverting = HAL::eprGetByte(EPR_ENDSTOP_X_MAX_INVERTING_CFG);
		CfgPrinterItems.cfg_endstop_y_max_inverting = HAL::eprGetByte(EPR_ENDSTOP_Y_MAX_INVERTING_CFG);
		CfgPrinterItems.cfg_endstop_z_max_inverting = HAL::eprGetByte(EPR_ENDSTOP_Z_MAX_INVERTING_CFG);		
		CfgPrinterItems.cfg_min_hardware_endstop_x = HAL::eprGetByte(EPR_MIN_HARDWARE_ENDSTOP_X_CFG);	
		CfgPrinterItems.cfg_min_hardware_endstop_y = HAL::eprGetByte(EPR_MIN_HARDWARE_ENDSTOP_Y_CFG);	
		CfgPrinterItems.cfg_min_hardware_endstop_z = HAL::eprGetByte(EPR_MIN_HARDWARE_ENDSTOP_Z_CFG);	
		CfgPrinterItems.cfg_max_hardware_endstop_x = HAL::eprGetByte(EPR_MAX_HARDWARE_ENDSTOP_X_CFG);	
		CfgPrinterItems.cfg_max_hardware_endstop_y = HAL::eprGetByte(EPR_MAX_HARDWARE_ENDSTOP_Y_CFG);	
		CfgPrinterItems.cfg_max_hardware_endstop_z = HAL::eprGetByte(EPR_MAX_HARDWARE_ENDSTOP_Z_CFG);	
		CfgPrinterItems.cfg_min_software_endstop_x = HAL::eprGetByte(EPR_MIN_SOFTWARE_ENDSTOP_X_CFG);	
		CfgPrinterItems.cfg_min_software_endstop_y = HAL::eprGetByte(EPR_MIN_SOFTWARE_ENDSTOP_Y_CFG);	
		CfgPrinterItems.cfg_min_software_endstop_z = HAL::eprGetByte(EPR_MIN_SOFTWARE_ENDSTOP_Z_CFG);	
		CfgPrinterItems.cfg_max_software_endstop_x = HAL::eprGetByte(EPR_MAX_SOFTWARE_ENDSTOP_X_CFG);	
		CfgPrinterItems.cfg_max_software_endstop_y = HAL::eprGetByte(EPR_MAX_SOFTWARE_ENDSTOP_Y_CFG);	
		CfgPrinterItems.cfg_max_software_endstop_z = HAL::eprGetByte(EPR_MAX_SOFTWARE_ENDSTOP_Z_CFG);	
		CfgPrinterItems.cfg_end_effector_horizontal_offset = HAL::eprGetFloat(EPR_END_EFFECTOR_HORIZONTAL_OFFSET_CFG);
		CfgPrinterItems.cfg_carriage_horizontal_offset = HAL::eprGetFloat(EPR_CARRIAGE_HORIZONTAL_OFFSET_CFG);
		CfgPrinterItems.cfg_rod_radius = HAL::eprGetFloat(EPR_ROD_RADIUS_CFG);
		CfgPrinterItems.cfg_bed_leveling_grid_size = HAL::eprGetFloat(EPR_BED_LEVELING_GRID_SIZE_CFG);
		CfgPrinterItems.cfg_z_probe_speed = HAL::eprGetFloat(EPR_Z_PROBE_SPEED_CFG);
		CfgPrinterItems.cfg_z_probe_xy_speed = HAL::eprGetFloat(EPR_Z_PROBE_XY_SPEED_CFG);
		CfgPrinterItems.cfg_stepper_high_delay = HAL::eprGetInt32(EPR_STEPPER_HIGH_DELAY_CFG);
	}
	else
	{
		HAL::eprSetInt32(EPR_BACKGROUND_COLOR_CFG, gCfgItems.background_color);
		HAL::eprSetInt32(EPR_TITLE_COLOR_CFG, gCfgItems.title_color);	
		HAL::eprSetInt32(EPR_STATE_BACKGROUND_COLOR_CFG,gCfgItems.state_background_color);
		HAL::eprSetInt32(EPR_STATE_TEXT_COLOR_CFG, gCfgItems.state_text_color);
		HAL::eprSetInt32(EPR_FILENAME_BACKGROUND_COLOE_CFG, gCfgItems.filename_background_color);
		HAL::eprSetInt32(EPR_FILENAME_COLOR_CFG, gCfgItems.filename_color);
		HAL::eprSetInt32(EPR_PRINTINGSTATE_TEXT_BACKGROUND_COLOR_CFG, gCfgItems.printingstate_word_background_color);
		HAL::eprSetInt32(EPR_PRINTINGSTATE_TEXT_COLOR_CFG, gCfgItems.printingstate_word_color);
		HAL::eprSetInt32(EPR_BUTTON_3D_EFFECTS_CFG, gCfgItems.button_3d_effect_flag);
       // HAL::eprSetByte(EPR_HAVE_UPS_CFG,gCfgItems.have_ups);
		HAL::eprSetInt32(EPR_LANGUAGE_TYPE_CFG, gCfgItems.language);
		HAL::eprSetInt32(EPR_UI_SET_MAX_TEMPERATURE_CFG, CfgPrinterItems.cfg_ui_set_maxtemp);
		HAL::eprSetInt32(EPR_UI_SET_HEAT_BED_TEMPERATURE_CFG, CfgPrinterItems.cfg_ui_set_heated_bed_maxtemp);
		HAL::eprSetByte(EPR_MOREITEM_PIC_CNT_CFG,gCfgItems.MoreItem_pic_cnt);	
		HAL::eprSetByte(EPR_SETMENU_FUNC1_DISPLAY_FLAG_CFG,gCfgItems.func_btn1_display_flag);	
		HAL::eprSetByte(EPR_SETMENU_FUNC2_DISPLAY_FLAG_CFG,gCfgItems.func_btn2_display_flag);	

		HAL::eprSetByte(EPR_DRIVE_SYSTEM_CFG, CfgPrinterItems.cfg_drive_system);
		HAL::eprSetByte(EPR_EXT0_TEMPSENSOR_TYPE_CFG,CfgPrinterItems.cfg_ext0_tempsensor_type);
		HAL::eprSetByte(EPR_EXT1_TEMPSENSOR_TYPE_CFG,CfgPrinterItems.cfg_ext1_tempsensor_type);
		HAL::eprSetByte(EPR_HEATED_BED_SENSOR_TYPE_CFG,CfgPrinterItems.cfg_heated_bed_sensor_type);
		HAL::eprSetFloat(EPR_DELTA_MAX_RADIUS_CFG,CfgPrinterItems.cfg_delta_max_radius);
		HAL::eprSetFloat(EPR_PRINTER_RADIUS_CFG,CfgPrinterItems.cfg_printer_radius);
		HAL::eprSetFloat(EPR_DELTA_DIAGONAL_ROD_CFG,CfgPrinterItems.cfg_delta_diagonal_rod);
		HAL::eprSetFloat(EPR_DELTA_FLOOR_SAFETY_MARGIN_MM_CFG,CfgPrinterItems.cfg_delta_floor_safety_margin_mm);
		 HAL::eprSetByte(EPR_FEATURE_Z_PROBE_CFG,CfgPrinterItems.cfg_feature_z_probe);
		 HAL::eprSetByte(EPR_BED_LEVELING_METHOD_CFG,CfgPrinterItems.cfg_bed_leveling_method);
		 HAL::eprSetFloat(EPR_Z_PROBE_HEIGHT_CFG,CfgPrinterItems.cfg_z_probe_height);
		 HAL::eprSetFloat(EPR_Z_PROBE_X1_CFG,CfgPrinterItems.cfg_z_probe_x1);
		 HAL::eprSetFloat(EPR_Z_PROBE_Y1_CFG,CfgPrinterItems.cfg_z_probe_y1);
		 HAL::eprSetFloat(EPR_Z_PROBE_X2_CFG,CfgPrinterItems.cfg_z_probe_x2);
		 HAL::eprSetFloat(EPR_Z_PROBE_Y2_CFG,CfgPrinterItems.cfg_z_probe_y2);
		 HAL::eprSetFloat(EPR_Z_PROBE_X3_CFG,CfgPrinterItems.cfg_z_probe_x3);
		 HAL::eprSetFloat(EPR_Z_PROBE_Y3_CFG,CfgPrinterItems.cfg_z_probe_y3);
		 HAL::eprSetFloat(EPR_XAXIS_STEPS_PER_MM_CFG,CfgPrinterItems.cfg_xaxis_steps_per_mm);
		 HAL::eprSetFloat(EPR_YAXIS_STEPS_PER_MM_CFG,CfgPrinterItems.cfg_yaxis_steps_per_mm);
		 HAL::eprSetFloat(EPR_ZAXIS_STEPS_PER_MM_CFG,CfgPrinterItems.cfg_zaxis_steps_per_mm);
		 HAL::eprSetFloat(EPR_EXT0_STEPS_PER_MM_CFG,CfgPrinterItems.cfg_ext0_steps_per_mm);
		 HAL::eprSetFloat(EPR_MAX_FEEDRATE_X_CFG,CfgPrinterItems.cfg_max_feedrate_x);
		 HAL::eprSetFloat(EPR_MAX_FEEDRATE_Y_CFG,CfgPrinterItems.cfg_max_feedrate_y);
		 HAL::eprSetFloat(EPR_MAX_FEEDRATE_Z_CFG,CfgPrinterItems.cfg_max_feedrate_z);
		 HAL::eprSetFloat(EPR_MAX_FEEDRATE_EXT0_CFG,CfgPrinterItems.cfg_max_feedrate_e0);
		 HAL::eprSetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_X_CFG,CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_x);
		 HAL::eprSetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Y_CFG,CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_y);
		 HAL::eprSetFloat(EPR_MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Z_CFG,CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_z);
		 HAL::eprSetFloat(EPR_MAX_ACCELERATION_EXT0_CFG,CfgPrinterItems.cfg_max_acceleration_e0);
		 HAL::eprSetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_X_CFG,CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_x);
		 HAL::eprSetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Y_CFG,CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_y);
		 HAL::eprSetFloat(EPR_MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Z_CFG,CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_z);
		 HAL::eprSetFloat(EPR_HOMING_FEEDRATE_X_CFG,CfgPrinterItems.cfg_homing_feedrate_x);
		 HAL::eprSetFloat(EPR_HOMING_FEEDRATE_Y_CFG,CfgPrinterItems.cfg_homing_feedrate_y);
		 HAL::eprSetFloat(EPR_HOMING_FEEDRATE_Z_CFG,CfgPrinterItems.cfg_homing_feedrate_z);
		 HAL::eprSetFloat(EPR_MIN_EXTRUDER_TEMP_CFG,CfgPrinterItems.cfg_ext_mintemp);
		 HAL::eprSetFloat(EPR_MAX_EXTRUDER_TEMP_CFG,CfgPrinterItems.cfg_ext_maxtemp);
		 HAL::eprSetFloat(EPR_MAX_HEATED_BED_TEMP_CFG,CfgPrinterItems.cfg_heated_bed_maxtemp);
		 HAL::eprSetByte(EPR_NUM_EXTRUDER_CFG,CfgPrinterItems.cfg_num_extruder);
		 HAL::eprSetByte(EPR_HAVE_HEATED_BED_CFG,CfgPrinterItems.cfg_have_heated_bed);
		 HAL::eprSetByte(EPR_INVERT_X_DIR_CFG,CfgPrinterItems.cfg_invert_x_dir);
		 HAL::eprSetByte(EPR_INVERT_Y_DIR_CFG,CfgPrinterItems.cfg_invert_y_dir);
		 HAL::eprSetByte(EPR_INVERT_Z_DIR_CFG,CfgPrinterItems.cfg_invert_z_dir);
		 HAL::eprSetByte(EPR_EXT0_INVERSE_CFG,CfgPrinterItems.cfg_invert_e0_dir);
		 HAL::eprSetByte(EPR_X_HOME_DIR_CFG,CfgPrinterItems.cfg_x_home_dir);
		 HAL::eprSetByte(EPR_Y_HOME_DIR_CFG,CfgPrinterItems.cfg_y_home_dir);
		 HAL::eprSetByte(EPR_Z_HOME_DIR_CFG,CfgPrinterItems.cfg_z_home_dir);
		 HAL::eprSetFloat(EPR_X_MAX_LENGTH_CFG,CfgPrinterItems.cfg_x_max_length);
		 HAL::eprSetFloat(EPR_Y_MAX_LENGTH_CFG,CfgPrinterItems.cfg_y_max_length);
		 HAL::eprSetFloat(EPR_Z_MAX_LENGTH_CFG,CfgPrinterItems.cfg_z_max_length);
		 HAL::eprSetFloat(EPR_X_MIN_POS_CFG,CfgPrinterItems.cfg_x_min_pos);
		 HAL::eprSetFloat(EPR_Y_MIN_POS_CFG,CfgPrinterItems.cfg_y_min_pos);
		 HAL::eprSetFloat(EPR_Z_MIN_POS_CFG,CfgPrinterItems.cfg_z_min_pos);
		 HAL::eprSetByte(EPR_ENDSTOP_X_MIN_INVERTING_CFG,CfgPrinterItems.cfg_endstop_x_min_inverting);
		 HAL::eprSetByte(EPR_ENDSTOP_Y_MIN_INVERTING_CFG,CfgPrinterItems.cfg_endstop_y_min_inverting);
		 HAL::eprSetByte(EPR_ENDSTOP_Z_MIN_INVERTING_CFG,CfgPrinterItems.cfg_endstop_z_min_inverting);
		 HAL::eprSetByte(EPR_ENDSTOP_X_MAX_INVERTING_CFG,CfgPrinterItems.cfg_endstop_x_max_inverting);
		 HAL::eprSetByte(EPR_ENDSTOP_Y_MAX_INVERTING_CFG,CfgPrinterItems.cfg_endstop_y_max_inverting);
		 HAL::eprSetByte(EPR_ENDSTOP_Z_MAX_INVERTING_CFG,CfgPrinterItems.cfg_endstop_z_max_inverting);		
		 HAL::eprSetByte(EPR_MIN_HARDWARE_ENDSTOP_X_CFG,CfgPrinterItems.cfg_min_hardware_endstop_x);	
		 HAL::eprSetByte(EPR_MIN_HARDWARE_ENDSTOP_Y_CFG,CfgPrinterItems.cfg_min_hardware_endstop_y);	
		 HAL::eprSetByte(EPR_MIN_HARDWARE_ENDSTOP_Z_CFG,CfgPrinterItems.cfg_min_hardware_endstop_z);	
		 HAL::eprSetByte(EPR_MAX_HARDWARE_ENDSTOP_X_CFG,CfgPrinterItems.cfg_max_hardware_endstop_x);	
		 HAL::eprSetByte(EPR_MAX_HARDWARE_ENDSTOP_Y_CFG,CfgPrinterItems.cfg_max_hardware_endstop_y);	
		 HAL::eprSetByte(EPR_MAX_HARDWARE_ENDSTOP_Z_CFG,CfgPrinterItems.cfg_max_hardware_endstop_z);	
		 HAL::eprSetByte(EPR_MIN_SOFTWARE_ENDSTOP_X_CFG,CfgPrinterItems.cfg_min_software_endstop_x);	
		 HAL::eprSetByte(EPR_MIN_SOFTWARE_ENDSTOP_Y_CFG,CfgPrinterItems.cfg_min_software_endstop_y);	
		 HAL::eprSetByte(EPR_MIN_SOFTWARE_ENDSTOP_Z_CFG,CfgPrinterItems.cfg_min_software_endstop_z);	
		 HAL::eprSetByte(EPR_MAX_SOFTWARE_ENDSTOP_X_CFG,CfgPrinterItems.cfg_max_software_endstop_x);	
		 HAL::eprSetByte(EPR_MAX_SOFTWARE_ENDSTOP_Y_CFG,CfgPrinterItems.cfg_max_software_endstop_y);	
		 HAL::eprSetByte(EPR_MAX_SOFTWARE_ENDSTOP_Z_CFG,CfgPrinterItems.cfg_max_software_endstop_z);	
		 HAL::eprSetFloat(EPR_END_EFFECTOR_HORIZONTAL_OFFSET_CFG,CfgPrinterItems.cfg_end_effector_horizontal_offset);
		 HAL::eprSetFloat(EPR_CARRIAGE_HORIZONTAL_OFFSET_CFG,CfgPrinterItems.cfg_carriage_horizontal_offset);
		 HAL::eprSetFloat(EPR_ROD_RADIUS_CFG,CfgPrinterItems.cfg_rod_radius);
		 HAL::eprSetFloat(EPR_BED_LEVELING_GRID_SIZE_CFG,CfgPrinterItems.cfg_bed_leveling_grid_size);
		 HAL::eprSetFloat(EPR_Z_PROBE_SPEED_CFG,CfgPrinterItems.cfg_z_probe_speed);
		 HAL::eprSetFloat(EPR_Z_PROBE_XY_SPEED_CFG,CfgPrinterItems.cfg_z_probe_xy_speed);
		 HAL::eprSetInt32(EPR_STEPPER_HIGH_DELAY_CFG,CfgPrinterItems.cfg_stepper_high_delay);

		
		valid_flag = BAK_INF_VALID_FLAG;
		HAL::eprSetInt32(EPR_VALID_FLAG_CFG,valid_flag); 
		HAL::AT24CXX_Read(EPR_VALID_FLAG_CFG,(u8*)&valid_flag,4);
		
	}
}

void cfg_init()
{
	uint32_t sdcard_info_update = 0;
	
	//--------------------------------------------------//
	gCfgItems.preheat_desireSprayerTemp[0]=gCfgItems.preheat_desireSprayerTemp[1] = 180;
	gCfgItems.preheat_desireBedTemp = 50;
	
	gCfgItems.move_dist = 1;
	gCfgItems.printSpeed = 100;
	gCfgItems.printExtSpeed0= 100;
	gCfgItems.printExtSpeed1 = 100;
	gCfgItems.stepPrintSpeed = 1;
	gCfgItems.extruSpeed = 1;
	gCfgItems.extruStep = 5;
	gCfgItems.stepHeat = 1;
	gCfgItems.moveSpeed = 3000;
	
	gCfgItems.custom_pic_flag = 1;
	gCfgItems.language = LANG_ENGLISH;
    gCfgItems.button_3d_effect_flag = 0;
    //gCfgItems.have_ups = 0;
	gCfgItems.background_color = GUI_BK_CLOLOR;
	gCfgItems.title_color = GUI_TITLE_TEXT_COLOR;
	gCfgItems.state_background_color = GUI_STATE_COLOR;
	gCfgItems.state_text_color = GUI_STATE_TEXT_COLOR;
	gCfgItems.filename_color = GUI_FILE_NAME_TEXT_COLOR;
	gCfgItems.filename_background_color = GUI_FILE_NAME_BK_COLOR;
	gCfgItems.printingstate_word_background_color = GUI_PRINTING_STATE_BK_COLOR;
	gCfgItems.printingstate_word_color = GUI_PRINTING_STATE_TEXT_COLOR;
	//gCfgItems.language = 3;
	gCfgItems.pause_zpos = 10;
	gCfgItems.MoreItem_pic_cnt = 0;
	gCfgItems.func_btn1_display_flag = 1;
	gCfgItems.func_btn2_display_flag = 0;
	
	//-------------------------------------------------//

	CfgPrinterItems.cfg_baudrate = 115200;
	
	CfgPrinterItems.cfg_drive_system = 0;
	
	CfgPrinterItems.cfg_num_extruder = 1;
	CfgPrinterItems.cfg_have_heated_bed = 1;
	
	CfgPrinterItems.cfg_ext0_tempsensor_type = 1;
	CfgPrinterItems.cfg_ext1_tempsensor_type = 1;
	CfgPrinterItems.cfg_heated_bed_sensor_type = 1;
	

	CfgPrinterItems.cfg_xaxis_steps_per_mm = 78.74;
	CfgPrinterItems.cfg_yaxis_steps_per_mm = 78.74;
	CfgPrinterItems.cfg_zaxis_steps_per_mm = 400;
	CfgPrinterItems.cfg_ext0_steps_per_mm = 90;

	CfgPrinterItems.cfg_max_feedrate_x = 	200;
	CfgPrinterItems.cfg_max_feedrate_y = 	200;
	CfgPrinterItems.cfg_max_feedrate_z = 	20;
	CfgPrinterItems.cfg_max_feedrate_e0 = 50;

	CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_x = 1000;
	CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_y = 1000;
	CfgPrinterItems.cfg_max_acceleration_units_per_sq_second_z = 100;
	CfgPrinterItems.cfg_max_acceleration_e0 = 1000;

	CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_x = 1000;
	CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_y = 1000;
	CfgPrinterItems.cfg_max_travel_acceleration_units_per_sq_second_z = 100;

	CfgPrinterItems.cfg_homing_feedrate_x = 40;
	CfgPrinterItems.cfg_homing_feedrate_y = 40;
	CfgPrinterItems.cfg_homing_feedrate_z = 2;


	CfgPrinterItems.cfg_ext_mintemp = 150;
	CfgPrinterItems.cfg_ext_maxtemp = 275;
	CfgPrinterItems.cfg_heated_bed_maxtemp = 150;

	CfgPrinterItems.cfg_ui_set_maxtemp = 260;
	CfgPrinterItems.cfg_ui_set_heated_bed_maxtemp = 120;	
	
	CfgPrinterItems.cfg_invert_x_dir = true;
	CfgPrinterItems.cfg_invert_y_dir = false;
	CfgPrinterItems.cfg_invert_z_dir = true;
	CfgPrinterItems.cfg_invert_e0_dir = true;
	CfgPrinterItems.cfg_invert_e1_dir = true;

	CfgPrinterItems.cfg_x_home_dir = -1;
	CfgPrinterItems.cfg_y_home_dir = -1;
	CfgPrinterItems.cfg_z_home_dir = -1;


	CfgPrinterItems.cfg_x_max_length = 230;
	CfgPrinterItems.cfg_y_max_length = 230;
	CfgPrinterItems.cfg_z_max_length = 230;
	
	CfgPrinterItems.cfg_x_min_pos = 0;
	CfgPrinterItems.cfg_y_min_pos = 0;
	CfgPrinterItems.cfg_z_min_pos = 0;


	CfgPrinterItems.cfg_endstop_x_min_inverting = 1;
	CfgPrinterItems.cfg_endstop_y_min_inverting = 1;
	CfgPrinterItems.cfg_endstop_z_min_inverting = 1;
	CfgPrinterItems.cfg_endstop_x_max_inverting = 0;
	CfgPrinterItems.cfg_endstop_y_max_inverting = 0;
	CfgPrinterItems.cfg_endstop_z_max_inverting = 0;

	CfgPrinterItems.cfg_min_hardware_endstop_x = 1;
	CfgPrinterItems.cfg_min_hardware_endstop_y = 1;
	CfgPrinterItems.cfg_min_hardware_endstop_z = 1;
	CfgPrinterItems.cfg_max_hardware_endstop_x = 0;
	CfgPrinterItems.cfg_max_hardware_endstop_y = 0;
	CfgPrinterItems.cfg_max_hardware_endstop_z = 0;

	CfgPrinterItems.cfg_min_software_endstop_x = 0;
	CfgPrinterItems.cfg_min_software_endstop_y = 0;
	CfgPrinterItems.cfg_min_software_endstop_z = 0;
	CfgPrinterItems.cfg_max_software_endstop_x = 1;
	CfgPrinterItems.cfg_max_software_endstop_y = 1;
	CfgPrinterItems.cfg_max_software_endstop_z = 1;

	CfgPrinterItems.cfg_delta_max_radius = 115;
	CfgPrinterItems.cfg_printer_radius = 180;
	CfgPrinterItems.cfg_delta_diagonal_rod = 300;

	CfgPrinterItems.cfg_feature_z_probe = 0;
	CfgPrinterItems.cfg_bed_leveling_method = 0;
	CfgPrinterItems.cfg_z_probe_height = 39.91;
	CfgPrinterItems.cfg_end_effector_horizontal_offset = 28.5;
	CfgPrinterItems.cfg_carriage_horizontal_offset = 25.5;
	CfgPrinterItems.cfg_rod_radius = 157.6;
	CfgPrinterItems.cfg_bed_leveling_grid_size = 5;
	CfgPrinterItems.cfg_z_probe_speed = 80;
	CfgPrinterItems.cfg_z_probe_xy_speed =200;
	CfgPrinterItems.cfg_stepper_high_delay = 0;
	recover_cfg_inf();
    //用于cc936编码转换表计算
    SPI_FLASH_BufferRead((u8*)&ugbksize,FONTINFOADDR,sizeof(ugbksize));

	SPI_FLASH_BufferRead((uint8_t *)&sdcard_info_update,FlASH_INF_VALID_ADDR,4);
	if(sdcard_info_update != FLASH_INF_VALID_FLAG)
	{
		char sdcard_info_buf1[5] = "M84;";
		char sdcard_info_buf2[11] = "G28;G32 S2";
		char sdcard_info_buf3[5] = "G28;";
		//功能按钮
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf1, BUTTON_FUNCTION1_ADDR, strlen(sdcard_info_buf1)+1);
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf2, BUTTON_FUNCTION2_ADDR, strlen(sdcard_info_buf2)+1);		
		//more按钮
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD1_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD2_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD3_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD4_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD5_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD6_ADDR, strlen(sdcard_info_buf3)+1);	
		SPI_FLASH_BufferWrite((uint8_t *)sdcard_info_buf3, BUTTON_CMD7_ADDR, strlen(sdcard_info_buf3)+1);	
	}
}
#if 0
void define_value_init()
{
if(CfgPrinterItems.cfg_drive_system == DELTA 
	|| CfgPrinterItems.cfg_drive_system==TUGA 
	|| CfgPrinterItems.cfg_drive_system==BIPOD)
	Change_Repetier_Define.def_NONLINEAR_SYSTEM = 1;
else
	Change_Repetier_Define.def_NONLINEAR_SYSTEM = 0;


	Change_Repetier_Define.def_ENDSTOP_X_MIN_INVERTING = CfgPrinterItems.cfg_endstop_x_min_inverting;
	Change_Repetier_Define.def_ENDSTOP_Y_MIN_INVERTING = CfgPrinterItems.cfg_endstop_y_min_inverting;
	Change_Repetier_Define.def_ENDSTOP_Z_MIN_INVERTING = CfgPrinterItems.cfg_endstop_z_min_inverting;
	Change_Repetier_Define.def_ENDSTOP_X_MAX_INVERTING = CfgPrinterItems.cfg_endstop_x_max_inverting;
	Change_Repetier_Define.def_ENDSTOP_Y_MAX_INVERTING = CfgPrinterItems.cfg_endstop_y_max_inverting;
	Change_Repetier_Define.def_ENDSTOP_Z_MAX_INVERTING = CfgPrinterItems.cfg_endstop_z_max_inverting;

	Change_Repetier_Define.def_MIN_HARDWARE_ENDSTOP_X = CfgPrinterItems.cfg_min_hardware_endstop_x;
	Change_Repetier_Define.def_MIN_HARDWARE_ENDSTOP_Y = CfgPrinterItems.cfg_min_hardware_endstop_y;
	Change_Repetier_Define.def_MIN_HARDWARE_ENDSTOP_Z = CfgPrinterItems.cfg_min_hardware_endstop_z;
	Change_Repetier_Define.def_MAX_HARDWARE_ENDSTOP_X = CfgPrinterItems.cfg_max_hardware_endstop_x;
	Change_Repetier_Define.def_MAX_HARDWARE_ENDSTOP_Y = CfgPrinterItems.cfg_max_hardware_endstop_y;
	Change_Repetier_Define.def_MAX_HARDWARE_ENDSTOP_Z = CfgPrinterItems.cfg_max_hardware_endstop_z;

	Change_Repetier_Define.def_min_software_endstop_x = CfgPrinterItems.cfg_min_software_endstop_x;
	Change_Repetier_Define.def_min_software_endstop_y = CfgPrinterItems.cfg_min_software_endstop_y;
	Change_Repetier_Define.def_min_software_endstop_z = CfgPrinterItems.cfg_min_software_endstop_z;
	Change_Repetier_Define.def_max_software_endstop_x = CfgPrinterItems.cfg_max_software_endstop_x;
	Change_Repetier_Define.def_max_software_endstop_y = CfgPrinterItems.cfg_max_software_endstop_y;
	Change_Repetier_Define.def_max_software_endstop_z = CfgPrinterItems.cfg_max_software_endstop_z;

	if(CfgPrinterItems.cfg_num_extruder>0)
	{
	if(CfgPrinterItems.cfg_ext0_tempsensor_type == 101)
	{
		Change_Repetier_Define.def_SUPPORT_MAX6675 = 1;
	}
	if(CfgPrinterItems.cfg_ext0_tempsensor_type == 102)
	{
		Change_Repetier_Define.def_SUPPORT_MAX31855 = 1;
	}
	}

	if(Change_Repetier_Define.def_SUPPORT_MAX6675 == 1)
	{
		#if !defined SCK_PIN || !defined MOSI_PIN || !defined MISO_PIN
			#error For MAX6675 support, you need to define SCK_PIN, MISO_PIN and MOSI_PIN in pins.h
		#endif
	}

	#if X_STEP_PIN < 0 || Y_STEP_PIN < 0 || Z_STEP_PIN < 0
		#error One of the following pins is not assigned: X_STEP_PIN,Y_STEP_PIN,Z_STEP_PIN
	#endif
	#if EXT0_STEP_PIN < 0 
	if(CfgPrinterItems.cfg_num_extruder > 0)
		#error EXT0_STEP_PIN not set to a pin number.
	#endif
	#if EXT0_DIR_PIN < 0 
	if(CfgPrinterItems.cfg_num_extruder > 0)
		#error EXT0_DIR_PIN not set to a pin number.
	#endif
	#if PRINTLINE_CACHE_SIZE < 4
		#error PRINTLINE_CACHE_SIZE must be at least 5
	#endif

	Change_Repetier_Define.def_PWM_BOARD_FAN = CfgPrinterItems.cfg_num_extruder + 1;
	Change_Repetier_Define.def_PWM_FAN1 = Change_Repetier_Define.def_PWM_BOARD_FAN+1;
	Change_Repetier_Define.def_PWM_FAN2 = Change_Repetier_Define.def_PWM_FAN1 + 1;
	Change_Repetier_Define.def_PWM_FAN_THERMO = Change_Repetier_Define.def_PWM_FAN2 + 1;


	if(CfgPrinterItems.cfg_have_heated_bed == 1)
	{
		#if FAN_THERMO_PIN > -1
			Change_Repetier_Define.def_NUM_TEMPERATURE_LOOPS = CfgPrinterItems.cfg_num_extruder+2;
		#else
			Change_Repetier_Define.def_NUM_TEMPERATURE_LOOPS = CfgPrinterItems.cfg_num_extruder+1;
		#endif
	}
	else
	{
		#if FAN_THERMO_PIN > -1
			Change_Repetier_Define.def_NUM_TEMPERATURE_LOOPS = CfgPrinterItems.cfg_num_extruder+1;
		#else
			Change_Repetier_Define.def_NUM_TEMPERATURE_LOOPS = CfgPrinterItems.cfg_num_extruder;
		#endif
	}

/*
	if(CfgPrinterItems.cfg_drive_system == DELTA)
	{
		CfgPrinterItems.cfg_xaxis_steps_per_mm = CfgPrinterItems.cfg_axis_steps_per_mm;
		CfgPrinterItems.cfg_yaxis_steps_per_mm = CfgPrinterItems.cfg_axis_steps_per_mm;
		CfgPrinterItems.cfg_zaxis_steps_per_mm = CfgPrinterItems.cfg_axis_steps_per_mm;
	}
*/

if (CfgPrinterItems.cfg_drive_system == DELTA)
{
/** \brief Delta rod length (mm)*/
Change_Repetier_Define.def_DELTA_DIAGONAL_ROD = CfgPrinterItems.cfg_delta_diagonal_rod;	//345 // mm	delta 9
/** \brief column positions - change only to correct build imperfections! */
Change_Repetier_Define.def_DELTA_ALPHA_A = 210;
Change_Repetier_Define.def_DELTA_ALPHA_B = 330;
Change_Repetier_Define.def_DELTA_ALPHA_C = 90;

/** Correct radius by this value for each column. Perfect builds have 0 everywhere. */
Change_Repetier_Define.def_DELTA_RADIUS_CORRECTION_A = 0;
Change_Repetier_Define.def_DELTA_RADIUS_CORRECTION_B = 0;
Change_Repetier_Define.def_DELTA_RADIUS_CORRECTION_C = 0;

/** Correction of the default diagonal size. Value gets added.*/
Change_Repetier_Define.def_DELTA_DIAGONAL_CORRECTION_A = 0;
Change_Repetier_Define.def_DELTA_DIAGONAL_CORRECTION_B = 0;
Change_Repetier_Define.def_DELTA_DIAGONAL_CORRECTION_C = 0;

/** Max. radius (mm) the printer should be able to reach. */
Change_Repetier_Define.def_DELTA_MAX_RADIUS = CfgPrinterItems.cfg_delta_max_radius;//115;//*200

// Margin (mm) to avoid above tower minimum (xMin xMinsteps)
Change_Repetier_Define.def_DELTA_FLOOR_SAFETY_MARGIN_MM = CfgPrinterItems.cfg_delta_floor_safety_margin_mm;

/** \brief Horizontal offset of the universal joints on the end effector (moving platform).
*/
Change_Repetier_Define.def_END_EFFECTOR_HORIZONTAL_OFFSET = CfgPrinterItems.cfg_end_effector_horizontal_offset;

/** \brief Horizontal offset of the universal joints on the vertical carriages.
*/
Change_Repetier_Define.def_CARRIAGE_HORIZONTAL_OFFSET = CfgPrinterItems.cfg_carriage_horizontal_offset;

/** \brief Printer radius in mm,
*/
Change_Repetier_Define.def_PRINTER_RADIUS = CfgPrinterItems.cfg_printer_radius;//*115//	265.25	//delta 10

/* ========== END Delta calibration data ==============*/
Change_Repetier_Define.def_DELTA_HOME_ON_POWER = 0;

Change_Repetier_Define.def_DELTA_X_ENDSTOP_OFFSET_STEPS = 0;
Change_Repetier_Define.def_DELTA_Y_ENDSTOP_OFFSET_STEPS = 0;
Change_Repetier_Define.def_DELTA_Z_ENDSTOP_OFFSET_STEPS = 0;

}
if(CfgPrinterItems.cfg_drive_system == DELTA)
{
	Change_Repetier_Define.def_ENDSTOP_X_BACK_MOVE = 5;		//5	//modify 8
	Change_Repetier_Define.def_ENDSTOP_Y_BACK_MOVE = 5;		//5	//modify 9
	Change_Repetier_Define.def_ENDSTOP_Z_BACK_MOVE = 2;		// 2//modify 10
	
	Change_Repetier_Define.def_ENDSTOP_X_BACK_ON_HOME = 1;
	Change_Repetier_Define.def_ENDSTOP_Y_BACK_ON_HOME = 1;
	Change_Repetier_Define.def_ENDSTOP_Z_BACK_ON_HOME = 0;	

}
else
{
	Change_Repetier_Define.def_ENDSTOP_X_BACK_MOVE = 5;		//5	//modify 8
	Change_Repetier_Define.def_ENDSTOP_Y_BACK_MOVE = 5;		//5	//modify 9
	Change_Repetier_Define.def_ENDSTOP_Z_BACK_MOVE = 2;		// 2 //modify 10
	
	Change_Repetier_Define.def_ENDSTOP_X_BACK_ON_HOME = 1;
	Change_Repetier_Define.def_ENDSTOP_Y_BACK_ON_HOME = 1;
	Change_Repetier_Define.def_ENDSTOP_Z_BACK_ON_HOME = 0;	

}




}
#endif
/**********************add****************************/

void printer_init()
{
	uint32_t flash_inf_valid_flag = 0;

	gCfgItems.preheat_desireBedTemp = 50;
	gCfgItems.preheat_desireSprayerTemp[0] = gCfgItems.preheat_desireSprayerTemp[1] = 180;
	gCfgItems.desireBedTemp = 0;
	gCfgItems.desireSprayerTemp[0] = gCfgItems.desireSprayerTemp[1] = 0;
	gCfgItems.curSprayerChoose = 0;
	gCfgItems.extruSpeed = 1;
	gCfgItems.extruStep = 5;
	gCfgItems.stepHeat = 1;
	gCfgItems.moveSpeed = 3000;
	gCfgItems.machineType = 1;
	gCfgItems.fanOnoff = 0;
	gCfgItems.fanSpeed = 0;
	gCfgItems.pre_fanSpeed = 0;//127;
	//gCfgItems.language = 1;//?òì??D??
	gCfgItems.language = LANG_ENGLISH;//ó￠??
	gCfgItems.sprayerNum = 1;
	gCfgItems.printSpeed = 100;
	gCfgItems.printExtSpeed0= 100;
	gCfgItems.printExtSpeed1 = 100;
	gCfgItems.stepPrintSpeed = 1;
	gCfgItems.move_dist = 1;
	gCfgItems.baud = 4;
/*
	gCfgItems.touch_adj_flag = 0;
	gCfgItems.touch_adj_xMin = 336;
	gCfgItems.touch_adj_xMax = 4059;
	gCfgItems.touch_adj_yMin = 3814;
	gCfgItems.touch_adj_yMax = 106;
*/

	gCfgItems.touch_adj_flag = 0;
	gCfgItems.touch_adj_xMin = 3518;
	gCfgItems.touch_adj_xMax = 389;
	gCfgItems.touch_adj_yMin = 284;
	gCfgItems.touch_adj_yMax = 3770;


	gCfgItems.fileSysType = 1;

	gCfgItems.rePrintFlag = printer_normal;

	gCfgItems.custom_bed_flag = 1;

	//chen 9.28
	gCfgItems.add_checkSum=0;
	gCfgItems.display_error=0;
	gCfgItems.restart_data_init = 0;

	if(readLcdId == 0x9341)
	{
		gCfgItems.touch_adj_flag = 0;
		gCfgItems.touch_adj_xMin = 3518;
		gCfgItems.touch_adj_xMax = 389;
		gCfgItems.touch_adj_yMin = 284;
		gCfgItems.touch_adj_yMax = 3770;

		/*
		int tmpCoord;
		
		if(gCfgItems.touch_adj_xMin <  gCfgItems.touch_adj_xMax)
		{
			tmpCoord = gCfgItems.touch_adj_xMin;
			gCfgItems.touch_adj_xMin = gCfgItems.touch_adj_xMax;
			gCfgItems.touch_adj_xMax = tmpCoord;
		}
		if(gCfgItems.touch_adj_yMin >  gCfgItems.touch_adj_yMax)
		{
			tmpCoord = gCfgItems.touch_adj_yMin;
			gCfgItems.touch_adj_yMin = gCfgItems.touch_adj_yMax;
			gCfgItems.touch_adj_yMax = tmpCoord;
		}
		*/
		
	}
	if(readLcdId == 0x8989)
	{
		gCfgItems.touch_adj_flag = 0;
		gCfgItems.touch_adj_xMin = 389;
		gCfgItems.touch_adj_xMax = 3518;
		gCfgItems.touch_adj_yMin = 284;
		gCfgItems.touch_adj_yMax = 3770;	
	}

	if(readLcdId == 0x9488)
	{
		gCfgItems.touch_adj_flag = 0;
		gCfgItems.touch_adj_xMin =201;
		gCfgItems.touch_adj_xMax =3919;
		gCfgItems.touch_adj_yMin = 3776;
		gCfgItems.touch_adj_yMax = 164;	
	}
#if defined(TFT70)
	gCfgItems.background_color = 0x000000;//à?é?
	gCfgItems.title_color = 0xFFFFFF;//°×é?
	gCfgItems.state_background_color = 0x000000;//é?à?é?
	gCfgItems.state_text_color = 0xFFFFFF;//°×é?
	//gCfgItems.filename_background_color = 0x000000;//à?é?
	//gCfgItems.filename_color = 0xFFFFFF;//°×é?
	//gCfgItems.printingstate_word_background_color = 0x000000;//à?é?
	//gCfgItems.printingstate_word_color = 0xFFFFFF;//°×é?
	gCfgItems.btn_color = 0xc88f75;
	gCfgItems.btn_textcolor = 0xffffff;
	gCfgItems.btn_state_color = 0x505050;
	gCfgItems.btn_state_textcolor = 0xffffff;
	gCfgItems.btn_state_sel_color = 0x9dfcff;
	gCfgItems.btn_state_sel_textcolor = 0x000000;
	gCfgItems.back_btn_color = 0xFFFFFF;
	gCfgItems.back_btn_textcolor = 0x000000;
	gCfgItems.printing_bar_color_left= 0x00ff00;
	gCfgItems.printing_bar_color_right= 0xAAAAAA ;
	gCfgItems.printing_bar_text_color_left = 0x000000;
	gCfgItems.printing_bar_text_color_right = 0x000000;
	gCfgItems.dialog_btn_color = 0xff0000;
	gCfgItems.dialog_btn_textcolor = 0xffffff;
	gCfgItems.printfile_color = 0x000000;
	gCfgItems.printfile_textcolor = 0xffffff;
#elif defined(TFT35)
	gCfgItems.background_color = 0x000000;//à?é?
	gCfgItems.title_color = 0xFFFFFF;//°×é?
	gCfgItems.state_background_color = 0x000000;//é?à?é?
	gCfgItems.state_text_color = 0xFFFFFF;//°×é?
	//gCfgItems.filename_background_color = 0x000000;//à?é?
	//gCfgItems.filename_color = 0xFFFFFF;//°×é?
	//gCfgItems.printingstate_word_background_color = 0x000000;//à?é?
	//gCfgItems.printingstate_word_color = 0xFFFFFF;//°×é?
	gCfgItems.btn_color = 0xc88f75;
	gCfgItems.btn_textcolor = 0xffffff;
	gCfgItems.btn_state_color = 0x505050;
	gCfgItems.btn_state_textcolor = 0xffffff;
	gCfgItems.btn_state_sel_color = 0x9dfcff;
	gCfgItems.btn_state_sel_textcolor = 0x000000;
	gCfgItems.back_btn_color = 0xFFFFFF;
	gCfgItems.back_btn_textcolor = 0x000000;
	gCfgItems.printing_bar_color_left= 0x00ff00;
	gCfgItems.printing_bar_color_right= 0xAAAAAA ;
	gCfgItems.printing_bar_text_color_left = 0x000000;
	gCfgItems.printing_bar_text_color_right = 0x000000;
	gCfgItems.dialog_btn_color = 0xff0000;
	gCfgItems.dialog_btn_textcolor = 0xffffff;
	gCfgItems.printfile_color = 0x000000;
	gCfgItems.printfile_textcolor = 0xffffff;
#endif
	
	gCfgItems.button_3d_effect_flag = 0;
	
	gCfgItems.MoreItem_pic_cnt = 0;

	/*wifi_cfg*/
	gCfgItems.wifi_mode_sel = 1;//1?aAP?￡ê?￡??????aclient?￡ê?￡???è??aAP?￡ê??￡
	
	//**memset(wifiPara, 0, sizeof(wifiPara));
	//**memset(ipPara, 0, sizeof(ipPara));
	
	//**strcpy(wifiPara.ap_name,WIFI_AP_NAME);
	//**strcpy(wifiPara.keyCode,WIFI_KEY_CODE);
	//client?￡ê?3?ê??μ
	//**strcpy(ipPara.ip_addr,IP_ADDR);
	//**strcpy(ipPara.mask,IP_MASK);
	//**strcpy(ipPara.gate,IP_GATE);
	//**strcpy(ipPara.dns,IP_DNS);
	
	//**ipPara.dhcp_flag = IP_DHCP_FLAG;

	//AP?￡ê?3?ê??μ
	/*strcpy(ipPara.dhcpd_ip,AP_IP_ADDR);  //**
	strcpy(ipPara.dhcpd_mask,AP_IP_MASK);
	strcpy(ipPara.dhcpd_gate,AP_IP_GATE);
	strcpy(ipPara.dhcpd_dns,AP_IP_DNS);
	strcpy(ipPara.start_ip_addr,IP_START_IP);
	strcpy(ipPara.end_ip_addr,IP_END_IP);
	
	ipPara.dhcpd_flag = AP_IP_DHCP_FLAG;*/  //**

	gCfgItems.firmware_type = 1;

	gCfgItems.Pause_XPOS = -1;
	gCfgItems.Pause_YPOS = -1;
	gCfgItems.Pause_ZADD = 10;

	gCfgItems.func_btn1_display_flag = 1;
	gCfgItems.func_btn2_display_flag = 1;
	
	gCfgItems.preheat_max_desireSprayerTemp = MAX_SPRAYER_TEMP;
	gCfgItems.preheat_max_desireBedTemp = MAX_BED_TEMP;	

	gCfgItems.pwrdn_mtrdn_level_flg = 1;
	
	gCfgItems.print_finish_close_machine_flg = 0;

	gCfgItems.morefunc_cnt = 0;

	gCfgItems.filament_load_speed = 1200;
	gCfgItems.filament_unload_speed = 1200;
	gCfgItems.filament_load_length= 200;
	gCfgItems.filament_unload_length= 200;
	gCfgItems.filament_limit_temper = 200;
	//gCfgItems.filament_unload_limit_temper = 200;

	
	gCfgItems.leveling_mode = 0;
	gCfgItems.leveling_point_number = 4;
	//(50,50)
	gCfgItems.leveling_point1_x = 50;
	gCfgItems.leveling_point1_y = 50;
	//(180,50)
	gCfgItems.leveling_point2_x = 180;
	gCfgItems.leveling_point2_y = 50;
	//(180,180)
	gCfgItems.leveling_point3_x = 180;
	gCfgItems.leveling_point3_y = 180;
	//(50,180)
	gCfgItems.leveling_point4_x = 50;
	gCfgItems.leveling_point4_y = 180;

	gCfgItems.leveling_xy_speed = 3000;
	gCfgItems.leveling_z_speed = 1500;

	gCfgItems.leveling_z_high = 10;

	gCfgItems.zpos = 0;
	memset((char *)gCfgItems.move_z_coordinate,0,sizeof(gCfgItems.move_z_coordinate));	
	gCfgItems.getzpos_enable= 0;

	//gCfgItems.pwroff_save_mode = 1;
	
	gCfgItems.sd_saving = 0;
	memset((char *)gCfgItems.z_display_pos,0,sizeof(gCfgItems.z_display_pos));	
	strcpy((char *)gCfgItems.z_display_pos,(char *)"0.00");

	gCfgItems.breakpoint_z_error = 0.2;
	gCfgItems.leveling_mode = 0;

	gCfgItems.pwroff_save_mode = 1;
	gCfgItems.filament_det1_level_flg = 0;
	gCfgItems.filament_det2_level_flg = 0;
	gCfgItems.have_ups = 0;
	gCfgItems.insert_det_module = 0;
	
	gCfgItems.multiple_language = 1;
	gCfgItems.stepZoffset = 0.1;	
	gCfgItems.quickstop_display_flg = 0;
	gCfgItems.zoffset_display_flg = 0;

	gCfgItems.display_style = 1;//屏幕首页显示模式，0:经典模式，1:简约模式。
	gCfgItems.mask_PB0_PB1_Function = 0;//屏蔽PB0和PB1检测功能；1:屏蔽功能；0:不屏蔽功能	
	gCfgItems.btn_text_offset = 23;
	gCfgItems.overturn_180 = 0;

	gCfgItems.baby_step_display_flg = 0;
	gCfgItems.calibrate_disp_flag = 0;

	/*wifi_cfg*/
	gCfgItems.wifi_mode_sel = 1;//1为AP模式，其他为client模式，默认为AP模式。
	
	memset(&wifiPara, 0, sizeof(wifiPara));
	memset(&ipPara, 0, sizeof(ipPara));
	
	strcpy(wifiPara.ap_name,WIFI_AP_NAME);
	strcpy(wifiPara.keyCode,WIFI_KEY_CODE);
	//client模式初始值
	strcpy(ipPara.ip_addr,IP_ADDR);
	strcpy(ipPara.mask,IP_MASK);
	strcpy(ipPara.gate,IP_GATE);
	strcpy(ipPara.dns,IP_DNS);
	
	ipPara.dhcp_flag = IP_DHCP_FLAG;

	//AP模式初始值
	strcpy(ipPara.dhcpd_ip,AP_IP_ADDR);
	strcpy(ipPara.dhcpd_mask,AP_IP_MASK);
	strcpy(ipPara.dhcpd_gate,AP_IP_GATE);
	strcpy(ipPara.dhcpd_dns,AP_IP_DNS);
	strcpy(ipPara.start_ip_addr,IP_START_IP);
	strcpy(ipPara.end_ip_addr,IP_END_IP);
	
	ipPara.dhcpd_flag = AP_IP_DHCP_FLAG;

	gCfgItems.wifi_type = ESP_WIFI;
	
	strcpy((char*)gCfgItems.cloud_hostUrl, "baizhongyun.cn");
	gCfgItems.cloud_port = 10086;

	gCfgItems.zoffset_disp_flag = 0;
	memset((void *)gCfgItems.disp_zoffset_buf,0,sizeof(gCfgItems.disp_zoffset_buf));

	recover_cfg_inf_tft();

	gCfgItems.custom_pic_flag = 1;

	get_sd_cfg();

	strcpy((char*)gCfgItems.F_speed, "F1000\n");
	
	if(gCfgItems.pwroff_save_mode != 0)
	{
		gCfgItems.pwroff_save_mode = 1;
	}
	gCfgItems.filename_background_color = gCfgItems.printfile_color;
	gCfgItems.filename_color = gCfgItems.printfile_textcolor;

	gCfgItems.filament_loading_time = (uint16_t)(((float)gCfgItems.filament_load_length/gCfgItems.filament_load_speed)*60);
	gCfgItems.filament_unloading_time = (uint16_t)(((float)gCfgItems.filament_unload_length/gCfgItems.filament_unload_speed)*60);

	if(gCfgItems.multiple_language == 0)
	{
		if(gCfgItems.language_bak != 0)
		{
			gCfgItems.language = gCfgItems.language_bak;
			HAL::AT24CXX_Write(BAK_LANGUARY_ADDR,(uint8_t *)&gCfgItems.language,1);	
		}
	}
	
	SPI_FLASH_BufferRead((u8*)&ugbksize,FONTINFOADDR,sizeof(ugbksize));
	
	SPI_FLASH_BufferRead((uint8_t *)&flash_inf_valid_flag,FlASH_INF_VALID_ADDR,4);
	if(flash_inf_valid_flag == FLASH_INF_VALID_FLAG)
	{
		SPI_FLASH_BufferRead((uint8_t *)wifiPara.ap_name,WIFI_NAME_ADDR,32);
		SPI_FLASH_BufferRead((uint8_t *)wifiPara.keyCode,WIFI_KEYCODE_ADDR,64);
		SPI_FLASH_BufferRead((uint8_t *)ipPara.ip_addr,WIFI_IP_ADDR,15);
		SPI_FLASH_BufferRead((uint8_t *)ipPara.mask,WIFI_MASK_ADDR,15);
		SPI_FLASH_BufferRead((uint8_t *)ipPara.gate,WIFI_GATE_ADDR,15);
		SPI_FLASH_BufferRead((uint8_t*)&ipPara.dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
		SPI_FLASH_BufferRead((uint8_t*)&gCfgItems.wifi_mode_sel,WIFI_MODE_SEL_ADDR,1);
		SPI_FLASH_BufferRead((uint8_t*)&gCfgItems.wifi_type,WIFI_MODE_TYPE_ADDR,1);
		if((gCfgItems.wifi_type != HLK_WIFI) && (gCfgItems.wifi_type != ESP_WIFI))
		{
			gCfgItems.wifi_type = ESP_WIFI;
		}
	}

	if(gCfgItems.custom_pic_flag == 1)
	{
		//**bmp_struct.XSize = 78;
		//**bmp_struct.YSize = 104;
		bmp_struct.XSize = BTN_PIC_X_PIXEL;
		bmp_struct.YSize = BTN_PIC_Y_PIXEL;
		//**BMP_PIC_X = 0 ;
		//**BMP_PIC_Y = 0;
		BMP_PIC_X = BTN_PIC_X_OFFSET;
		BMP_PIC_Y = BTN_PIC_Y_OFFSET;

		bmp_struct_50.XSize = STATE_PIC_X_PIXEL;
		bmp_struct_50.YSize = STATE_PIC_Y_PIXEL;
#if defined(TFT35)
		bmp_struct_92.XSize = OTHER_BTN_XPIEL;
		bmp_struct_92.YSize = OTHER_BTN_XPIEL;
		
		bmp_struct_150.XSize = PRINTING_BTN_XPIEL;
		bmp_struct_150.YSize = PRINTING_BTN_XPIEL;		
#endif
	}
	else
	{
		bmp_struct.XSize = 80;
		bmp_struct.YSize = 50;
		BMP_PIC_X = 0 ;
		BMP_PIC_Y = 17;
	}
}
void recover_cfg_inf_tft()
{
	uint32_t  valid_flag;
	uint32_t  tmp_reprint_flag;
	uint32_t  tmp_reprint_offset;

	HAL::AT24CXX_Read(BAK_VALID_FLAG_ADDR,(uint8_t *)&valid_flag ,  4); 
	if(valid_flag == BAK_INF_VALID_FLAG)
	{
		HAL::AT24CXX_Read(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud ,  1); 
		HAL::AT24CXX_Read(BAK_LANGUARY_ADDR,(uint8_t *)&gCfgItems.language ,  1); 
		HAL::AT24CXX_Read(BAK_MOV_SPEED_ADDR,(uint8_t *)&gCfgItems.moveSpeed ,  1); 
		HAL::AT24CXX_Read(BAK_MOV_DIST_ADDR, (uint8_t *)&gCfgItems.move_dist,  1); 
		HAL::AT24CXX_Read(BAK_EXTRU_SPEED_ADDR,(uint8_t *)&gCfgItems.extruSpeed ,  1); 
		HAL::AT24CXX_Read(BAK_MACHINE_TYPE_ADDR, (uint8_t *)&gCfgItems.machineType,  1); 
		HAL::AT24CXX_Read(BAK_SPRAYER_NUM_ADDR,(uint8_t *)&gCfgItems.sprayerNum ,  1); 
		HAL::AT24CXX_Read(BAK_FAN_SPEED_ADDR,(uint8_t *)&gCfgItems.fanSpeed ,  1); 
		HAL::AT24CXX_Read(BAK_FILE_SYS_ADDR, (uint8_t *)&gCfgItems.fileSysType,  1); 
		//从V1.2.0版本以后，不再需要校正屏幕
		/*
		I2C_EE_BufferRead((uint8_t *)&gCfgItems.touch_adj_flag, BAK_TOUCH_ADJ_FLAG_ADDR,  1); 
		if(gCfgItems.touch_adj_flag == 0xaa)
		{
			I2C_EE_BufferRead((uint8_t *)&gCfgItems.touch_adj_xMin, BAK_TOUCH_ADJ_XMIN_ADDR,  4); 
			I2C_EE_BufferRead((uint8_t *)&gCfgItems.touch_adj_xMax, BAK_TOUCH_ADJ_XMAX_ADDR,  4); 
			I2C_EE_BufferRead((uint8_t *)&gCfgItems.touch_adj_yMin, BAK_TOUCH_ADJ_YMIN_ADDR,  4); 
			I2C_EE_BufferRead((uint8_t *)&gCfgItems.touch_adj_yMax, BAK_TOUCH_ADJ_YMAX_ADDR,  4); 
		}
		*/
		HAL::AT24CXX_Read(BAK_REPRINT_INFO,(uint8_t *)&tmp_reprint_flag ,  4); 
		gCfgItems.rePrintFlag = tmp_reprint_flag >> 24;
		//断电偏移量出错处理
		HAL::AT24CXX_Read(BAK_REPRINT_OFFSET,(uint8_t *)&tmp_reprint_offset ,  4);
		if(tmp_reprint_offset == 0xffffffff)
		{
			gCfgItems.rePrintFlag = printer_normal;
		}		

		//I2C_EE_BufferRead((uint8_t *)&gCfgItems.custom_pic_flag, BAK_CUSTOM_PIC_ADDR,  1); 

		HAL::AT24CXX_Read(BAK_BACKGROUND_COLOR_ADD, (uint8_t *)&gCfgItems.background_color,4);
		HAL::AT24CXX_Read(BAK_TITIL_COLOR_ADD,(uint8_t *)&gCfgItems.title_color ,4);
		HAL::AT24CXX_Read(BAK_STATE_BKCOLOR_ADD,(uint8_t *)&gCfgItems.state_background_color ,4);
		HAL::AT24CXX_Read(BAK_STATE_TEXTCOLOR_ADD, (uint8_t *)&gCfgItems.state_text_color,4);
		HAL::AT24CXX_Read(BAK_FILENAME_BKCOLOR_ADD,(uint8_t *)&gCfgItems.printfile_color ,4);
		HAL::AT24CXX_Read(BAK_FILENAME_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.printfile_textcolor ,4);
		HAL::AT24CXX_Read(BAK_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_color ,4);
		HAL::AT24CXX_Read(BAK_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_textcolor ,4);
		HAL::AT24CXX_Read(BAK_STATE_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_color,4);
		HAL::AT24CXX_Read(BAK_STATE_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_textcolor ,4);
		HAL::AT24CXX_Read(BAK_BACK_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.back_btn_color,4);
		HAL::AT24CXX_Read(BAK_BACK_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.back_btn_textcolor ,4);
		HAL::AT24CXX_Read(BAK_SEL_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_sel_color,4);
		HAL::AT24CXX_Read(BAK_SEL_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_sel_textcolor ,4);
		HAL::AT24CXX_Read(BAK_DIALOG_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.dialog_btn_color,4);
		HAL::AT24CXX_Read(BAK_DIALOG_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.dialog_btn_textcolor ,4);

		
		HAL::AT24CXX_Read(BAK_MOREITEM_PIC_CNT,(uint8_t *)&gCfgItems.MoreItem_pic_cnt ,1);	

		HAL::AT24CXX_Read(BAK_CUSTOM_BED_FLAG_ADDR,(uint8_t *)&gCfgItems.custom_bed_flag ,1);
		
		HAL::AT24CXX_Read(BAK_BUTTON_3D_EFFECT_FLAG, (uint8_t *)&gCfgItems.button_3d_effect_flag,1);
		HAL::AT24CXX_Read(BAK_FIRMWARETYPE_ADDR,(uint8_t *)&gCfgItems.firmware_type,1);

		HAL::AT24CXX_Read(BAK_PAUSE_XPOS_ADDR,(uint8_t *)&gCfgItems.Pause_XPOS,2);
		HAL::AT24CXX_Read(BAK_PAUSE_YPOS_ADDR,(uint8_t *)&gCfgItems.Pause_YPOS,2);
		HAL::AT24CXX_Read(BAK_PAUSE_ZADD_ADDR,(uint8_t *)&gCfgItems.Pause_ZADD,2);

		
		HAL::AT24CXX_Read(BAK_FUNC1_DISPLAY_ADDR,(uint8_t *)&gCfgItems.func_btn1_display_flag,1);
		HAL::AT24CXX_Read(BAK_FUNC2_DISPLAY_ADDR,(uint8_t *)&gCfgItems.func_btn2_display_flag,1);

		HAL::AT24CXX_Read(BAK_SPRAYER1_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireSprayerTemp,2);
		HAL::AT24CXX_Read(BAK_BED_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireBedTemp,2);

		//**HAL::AT24CXX_Read(BAK_PWRDN_MTRDN_LEVEL_FLG_ADDR,(uint8_t *)&gCfgItems.pwrdn_mtrdn_level_flg,1);
		HAL::AT24CXX_Read(BAK_PRINT_FINISH_CLOASE_MACHINE_ADDR,(uint8_t *)&gCfgItems.print_finish_close_machine_flg,1);
		HAL::AT24CXX_Read(BAK_PRINTING_MOREFUNC_CNT_ADDR,(uint8_t *)&gCfgItems.morefunc_cnt,1);
		
		HAL::AT24CXX_Read(BAK_FILAMENT_LOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_load_speed,2);
		HAL::AT24CXX_Read(BAK_FILAMENT_UNLOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_unload_speed,2);
		HAL::AT24CXX_Read(BAK_FILAMENT_LOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_load_length,2);
		HAL::AT24CXX_Read(BAK_FILAMENT_UNLOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_unload_length,2);
		HAL::AT24CXX_Read(BAK_FILAMENT_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_limit_temper,2);
		//HAL::AT24CXX_Read(BAK_FILAMENT_UNLOAD_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_unload_limit_temper,2);
		
		HAL::AT24CXX_Read(BAK_LEVELING_POINT_NUMBER_ADDR,(uint8_t *)&gCfgItems.leveling_point_number,1);
		HAL::AT24CXX_Read(BAK_LEVELING_MODE_ADDR,(uint8_t *)&gCfgItems.leveling_mode,1);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT1_X_ADDR,(uint8_t *)&gCfgItems.leveling_point1_x,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT1_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point1_y,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT2_X_ADDR,(uint8_t *)&gCfgItems.leveling_point2_x,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT2_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point2_y,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT3_X_ADDR,(uint8_t *)&gCfgItems.leveling_point3_x,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT3_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point3_y,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT4_X_ADDR,(uint8_t *)&gCfgItems.leveling_point4_x,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT4_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point4_y,2);
		//chen 9.15
		HAL::AT24CXX_Read(BAK_LEVELING_POINT5_X_ADDR,(uint8_t *)&gCfgItems.leveling_point5_x,2);
		HAL::AT24CXX_Read(BAK_LEVELING_POINT5_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point5_y,2);
		
		HAL::AT24CXX_Read(BAK_LEVELING_Z_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_z_speed,2);
		HAL::AT24CXX_Read(BAK_LEVELING_XY_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_xy_speed,2);

		#ifdef SAVE_FROM_SD
		HAL::AT24CXX_Read(BAK_PWROFF_SAVE_MODE_ADDR,(uint8_t *)&gCfgItems.pwroff_save_mode,1);	
		#endif
		HAL::AT24CXX_Read(BAK_BREAKPOINT_Z_ERROR_ADDR,(uint8_t *)&gCfgItems.breakpoint_z_error,4);
		HAL::AT24CXX_Read(BAK_LEVELING_MODE_ADDR,(uint8_t *)&gCfgItems.leveling_mode,1);
		HAL::AT24CXX_Read(BAK_FILAMENT_DET1_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det1_level_flg,1);
		HAL::AT24CXX_Read(BAK_FILAMENT_DET2_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det2_level_flg,1);
		HAL::AT24CXX_Read(BAK_HAVE_UPS_ADDR,(uint8_t *)&gCfgItems.have_ups,1);
		HAL::AT24CXX_Read(BAK_INSERT_MODULE_ADDR,(uint8_t *)&gCfgItems.insert_det_module,1);
		HAL::AT24CXX_Read(BAK_MULTIPLE_LANGUAGE_ADDR,(uint8_t *)&gCfgItems.multiple_language,1);
		HAL::AT24CXX_Read(BAK_QUICKSTOP_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.quickstop_display_flg,1);	
		HAL::AT24CXX_Read(BAK_ZOFFSET_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.zoffset_display_flg,1);
		HAL::AT24CXX_Read(BAK_LEVELING_Z_HIGH_ADDR,(uint8_t *)&gCfgItems.leveling_z_high,2);
		HAL::AT24CXX_Read(BAK_SCREEN_DISPLAY_MODE_ADDR,(uint8_t *)&gCfgItems.display_style,1);
		HAL::AT24CXX_Read(BAK_MASK_PB0_PB1_FUNCTION_ADDR,(uint8_t *)&gCfgItems.mask_PB0_PB1_Function,1);
		HAL::AT24CXX_Read(BAK_BTN_TEXT_OFFSET_ADDR,(uint8_t *)&gCfgItems.btn_text_offset,1);
		HAL::AT24CXX_Read(BAK_SCREEN_OVERTURN_180_ADDR,(uint8_t *)&gCfgItems.overturn_180,1);
		HAL::AT24CXX_Read(BAK_CLOUD_FLAG_ADDR,(uint8_t *)&gCfgItems.cloud_enable,1);
		//chen 9.28
		HAL::AT24CXX_Read(BAK_M110_ADD_CHECKSUM_ADDR,(uint8_t *)&gCfgItems.add_checkSum,1);
		HAL::AT24CXX_Read(BAK_DISP_EEROR_ADDR,(uint8_t *)&gCfgItems.display_error,1);

		HAL::AT24CXX_Read(BAK_BABY_STEP_DISP_ADDR,(uint8_t *)&gCfgItems.baby_step_display_flg,1);	
		HAL::AT24CXX_Read(BAK_CALIBRATE_DISP_FLAG_ADDR,(uint8_t *)&gCfgItems.calibrate_disp_flag ,1);

	}
	else
	{
		HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR,(uint8_t *)&gCfgItems.baud ,  1); 
		HAL::AT24CXX_Write(BAK_LANGUARY_ADDR,(uint8_t *)&gCfgItems.language ,  1); 
		HAL::AT24CXX_Write(BAK_MOV_SPEED_ADDR,(uint8_t *)&gCfgItems.moveSpeed ,  1); 
		HAL::AT24CXX_Write(BAK_MOV_DIST_ADDR,(uint8_t *)&gCfgItems.move_dist ,  1); 
		HAL::AT24CXX_Write(BAK_EXTRU_SPEED_ADDR,(uint8_t *)&gCfgItems.extruSpeed ,  1); 
		HAL::AT24CXX_Write(BAK_MACHINE_TYPE_ADDR,(uint8_t *)&gCfgItems.machineType  ,  1);
		HAL::AT24CXX_Write(BAK_SPRAYER_NUM_ADDR, (uint8_t *)&gCfgItems.sprayerNum,  1); 
		HAL::AT24CXX_Write(BAK_FAN_SPEED_ADDR,(uint8_t *)&gCfgItems.fanSpeed ,  1); 
		HAL::AT24CXX_Write(BAK_FILE_SYS_ADDR,(uint8_t *)&gCfgItems.fileSysType ,  1);
		/*
		I2C_EE_BufferWrite((uint8_t *)&gCfgItems.touch_adj_flag, BAK_TOUCH_ADJ_FLAG_ADDR,  1); 
		I2C_EE_BufferWrite((uint8_t *)&gCfgItems.touch_adj_xMin, BAK_TOUCH_ADJ_XMIN_ADDR,  4); 
		I2C_EE_BufferWrite((uint8_t *)&gCfgItems.touch_adj_xMax, BAK_TOUCH_ADJ_XMAX_ADDR,  4); 
		I2C_EE_BufferWrite((uint8_t *)&gCfgItems.touch_adj_yMin, BAK_TOUCH_ADJ_YMIN_ADDR,  4); 
		I2C_EE_BufferWrite((uint8_t *)&gCfgItems.touch_adj_yMax, BAK_TOUCH_ADJ_YMAX_ADDR,  4); 
		*/
		//I2C_EE_BufferWrite((uint8_t *)&gCfgItems.custom_pic_flag, BAK_CUSTOM_PIC_ADDR,  1); 
		HAL::AT24CXX_Write(BAK_BACKGROUND_COLOR_ADD, (uint8_t *)&gCfgItems.background_color,4);
		HAL::AT24CXX_Write(BAK_TITIL_COLOR_ADD,(uint8_t *)&gCfgItems.title_color ,4);
		HAL::AT24CXX_Write(BAK_STATE_BKCOLOR_ADD,(uint8_t *)&gCfgItems.state_background_color ,4);
		HAL::AT24CXX_Write(BAK_STATE_TEXTCOLOR_ADD, (uint8_t *)&gCfgItems.state_text_color,4);
		HAL::AT24CXX_Write(BAK_FILENAME_BKCOLOR_ADD,(uint8_t *)&gCfgItems.printfile_color ,4);
		HAL::AT24CXX_Write(BAK_FILENAME_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.printfile_textcolor ,4);
		HAL::AT24CXX_Write(BAK_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_color ,4);
		HAL::AT24CXX_Write(BAK_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_textcolor ,4);
		HAL::AT24CXX_Write(BAK_STATE_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_color,4);
		HAL::AT24CXX_Write(BAK_STATE_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_textcolor ,4);
		HAL::AT24CXX_Write(BAK_BACK_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.back_btn_color,4);
		HAL::AT24CXX_Write(BAK_BACK_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.back_btn_textcolor ,4);
		HAL::AT24CXX_Write(BAK_SEL_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_sel_color,4);
		HAL::AT24CXX_Write(BAK_SEL_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.btn_state_sel_textcolor ,4);
		HAL::AT24CXX_Write(BAK_DIALOG_BTN_BKCOLOR_ADD,(uint8_t *)&gCfgItems.dialog_btn_color,4);
		HAL::AT24CXX_Write(BAK_DIALOG_BTN_TEXTCOLOR_ADD,(uint8_t *)&gCfgItems.dialog_btn_textcolor ,4);
		
		HAL::AT24CXX_Write(BAK_MOREITEM_PIC_CNT,(uint8_t *)&gCfgItems.MoreItem_pic_cnt ,1);	

		HAL::AT24CXX_Write(BAK_CUSTOM_BED_FLAG_ADDR,(uint8_t *)&gCfgItems.custom_bed_flag,1);

		HAL::AT24CXX_Write(BAK_BUTTON_3D_EFFECT_FLAG,(uint8_t *)&gCfgItems.button_3d_effect_flag,1);

		HAL::AT24CXX_Write(BAK_FIRMWARETYPE_ADDR,(uint8_t *)&gCfgItems.firmware_type,1);

		HAL::AT24CXX_Write(BAK_PAUSE_XPOS_ADDR,(uint8_t *)&gCfgItems.Pause_XPOS,2);
		HAL::AT24CXX_Write(BAK_PAUSE_YPOS_ADDR,(uint8_t *)&gCfgItems.Pause_YPOS,2);
		HAL::AT24CXX_Write(BAK_PAUSE_ZADD_ADDR,(uint8_t *)&gCfgItems.Pause_ZADD,2);

		HAL::AT24CXX_Write(BAK_FUNC1_DISPLAY_ADDR,(uint8_t *)&gCfgItems.func_btn1_display_flag,1);
		HAL::AT24CXX_Write(BAK_FUNC2_DISPLAY_ADDR,(uint8_t *)&gCfgItems.func_btn2_display_flag,1);

		HAL::AT24CXX_Write(BAK_SPRAYER1_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireSprayerTemp,2);
		HAL::AT24CXX_Write(BAK_BED_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireBedTemp,2);

		//**HAL::AT24CXX_Write(BAK_PWRDN_MTRDN_LEVEL_FLG_ADDR,(uint8_t *)&gCfgItems.pwrdn_mtrdn_level_flg,1);
		//**HAL::AT24CXX_Write(BAK_PRINT_FINISH_CLOASE_MACHINE_ADDR,(uint8_t *)&gCfgItems.print_finish_close_machine_flg,1);
		HAL::AT24CXX_Write(BAK_PRINTING_MOREFUNC_CNT_ADDR,(uint8_t *)&gCfgItems.morefunc_cnt,1);
		
		HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_load_speed,2);
		HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_unload_speed,2);
		HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_load_length,2);
		HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_unload_length,2);
		HAL::AT24CXX_Write(BAK_FILAMENT_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_limit_temper,2);
		//HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_unload_limit_temper,2);
		
		HAL::AT24CXX_Write(BAK_LEVELING_MODE_ADDR,(uint8_t *)&gCfgItems.leveling_mode,1);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT1_X_ADDR,(uint8_t *)&gCfgItems.leveling_point1_x,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT1_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point1_y,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT2_X_ADDR,(uint8_t *)&gCfgItems.leveling_point2_x,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT2_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point2_y,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT3_X_ADDR,(uint8_t *)&gCfgItems.leveling_point3_x,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT3_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point3_y,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT4_X_ADDR,(uint8_t *)&gCfgItems.leveling_point4_x,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT4_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point4_y,2);
		//chen 9.15
		HAL::AT24CXX_Write(BAK_LEVELING_POINT5_X_ADDR,(uint8_t *)&gCfgItems.leveling_point5_x,2);
		HAL::AT24CXX_Write(BAK_LEVELING_POINT5_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point5_y,2);
		
		HAL::AT24CXX_Write(BAK_LEVELING_Z_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_z_speed,2);
		HAL::AT24CXX_Write(BAK_LEVELING_XY_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_xy_speed,2);

		#ifdef SAVE_FROM_SD
		HAL::AT24CXX_Write(BAK_PWROFF_SAVE_MODE_ADDR,(uint8_t *)&gCfgItems.pwroff_save_mode,1);
		#endif
		HAL::AT24CXX_Write(BAK_BREAKPOINT_Z_ERROR_ADDR,(uint8_t *)&gCfgItems.breakpoint_z_error,4);
		HAL::AT24CXX_Write(BAK_LEVELING_MODE_ADDR,(uint8_t *)&gCfgItems.leveling_mode	,1);	
		HAL::AT24CXX_Write(BAK_FILAMENT_DET1_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det1_level_flg,1);
		HAL::AT24CXX_Write(BAK_FILAMENT_DET2_FLAG_ADDR,(uint8_t *)&gCfgItems.filament_det2_level_flg,1);
		HAL::AT24CXX_Write(BAK_HAVE_UPS_ADDR,(uint8_t *)&gCfgItems.have_ups,1);
		HAL::AT24CXX_Write(BAK_INSERT_MODULE_ADDR,(uint8_t *)&gCfgItems.insert_det_module,1);
		HAL::AT24CXX_Write(BAK_MULTIPLE_LANGUAGE_ADDR,(uint8_t *)&gCfgItems.multiple_language,1);

		HAL::AT24CXX_Write(BAK_QUICKSTOP_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.quickstop_display_flg,1);	
		HAL::AT24CXX_Write(BAK_ZOFFSET_DISPLAY_FLG_ADDR,(uint8_t *)&gCfgItems.zoffset_display_flg,1);
		HAL::AT24CXX_Write(BAK_LEVELING_Z_HIGH_ADDR,(uint8_t *)&gCfgItems.leveling_z_high,2);
		HAL::AT24CXX_Write(BAK_SCREEN_DISPLAY_MODE_ADDR,(uint8_t *)&gCfgItems.display_style,1);
		HAL::AT24CXX_Write(BAK_MASK_PB0_PB1_FUNCTION_ADDR,(uint8_t *)&gCfgItems.mask_PB0_PB1_Function,1);
		HAL::AT24CXX_Write(BAK_BTN_TEXT_OFFSET_ADDR,(uint8_t *)&gCfgItems.btn_text_offset,1);
		HAL::AT24CXX_Write(BAK_SCREEN_OVERTURN_180_ADDR,(uint8_t *)&gCfgItems.overturn_180,1);
		HAL::AT24CXX_Write(BAK_CLOUD_FLAG_ADDR,(uint8_t *)&gCfgItems.cloud_enable,1);
		//chen 9.28
		HAL::AT24CXX_Write(BAK_M110_ADD_CHECKSUM_ADDR,(uint8_t *)&gCfgItems.add_checkSum,1);
		HAL::AT24CXX_Write(BAK_DISP_EEROR_ADDR,(uint8_t *)&gCfgItems.display_error,1);
		HAL::AT24CXX_Write(BAK_BABY_STEP_DISP_ADDR,(uint8_t *)&gCfgItems.baby_step_display_flg,1);	
		HAL::AT24CXX_Write(BAK_CALIBRATE_DISP_FLAG_ADDR,(uint8_t *)&gCfgItems.calibrate_disp_flag ,1);

		valid_flag = BAK_INF_VALID_FLAG;
		HAL::AT24CXX_Write(BAK_VALID_FLAG_ADDR,(uint8_t *)&valid_flag ,  4); 		
	}

}

void bakup_cfg_inf(BAK_INF_ITEM_ID  cfgItemId, uint32_t  value)
{
	switch(cfgItemId)
	{
		case BAK_BAUD_ID:
			HAL::AT24CXX_Write(BAK_BAUDRATE_ADDR, (uint8_t *)&value,  1);
			break;

		case BAK_LANG_ID:
			HAL::AT24CXX_Write(BAK_LANGUARY_ADDR,(uint8_t *)&value ,  1);
			break;

		case BAK_MOV_SPEED_ID:
			HAL::AT24CXX_Write(BAK_MOV_SPEED_ADDR,(uint8_t *)&value,  1);
			break;
			
		case BAK_MOV_DIST_ID:
			HAL::AT24CXX_Write(BAK_MOV_DIST_ADDR,(uint8_t *)&value ,  1);
			break;
				
		case BAK_EXTRU_SPEED_ID:
			HAL::AT24CXX_Write(BAK_EXTRU_SPEED_ADDR, (uint8_t *)&value,  1);
			break;

		case BAK_MACH_TYPE_ID:
			HAL::AT24CXX_Write(BAK_MACHINE_TYPE_ADDR, (uint8_t *)&value,  1);
			break;
			
		case BAK_SPRAY_NUM_ID:
			HAL::AT24CXX_Write(BAK_SPRAYER_NUM_ADDR,(uint8_t *)&value ,  1);
			break;
				
		case BAK_FAN_SPEED_ID:
			HAL::AT24CXX_Write(BAK_FAN_SPEED_ADDR,(uint8_t *)&value ,  1);
			break;
					
		case BAK_FILE_SYS_ID:
			HAL::AT24CXX_Write(BAK_FILE_SYS_ADDR, (uint8_t *)&value,  1);
			break;

		case BAK_TOUCH_ADJ_FLAG_ID:
			HAL::AT24CXX_Write(BAK_TOUCH_ADJ_FLAG_ADDR, (uint8_t *)&value,  1);
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_TOUCH_ADJ_FLAG_ADDR,  1);
			break;

		case BAK_TOUCH_ADJ_XMAX_ID:
			HAL::AT24CXX_Write(BAK_TOUCH_ADJ_XMAX_ADDR, (uint8_t *)&value,  4);
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_TOUCH_ADJ_XMAX_ADDR,  4);
			break;

		case BAK_TOUCH_ADJ_XMIN_ID:
			HAL::AT24CXX_Write(BAK_TOUCH_ADJ_XMIN_ADDR, (uint8_t *)&value,  4);
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_TOUCH_ADJ_XMIN_ADDR,  4);
			break;

		case BAK_TOUCH_ADJ_YMAX_ID:
			HAL::AT24CXX_Write(BAK_TOUCH_ADJ_YMAX_ADDR, (uint8_t *)&value,  4);
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_TOUCH_ADJ_YMAX_ADDR,  4);
			break;

		case BAK_TOUCH_ADJ_YMIN_ID:
			HAL::AT24CXX_Write(BAK_TOUCH_ADJ_YMIN_ADDR, (uint8_t *)&value,  4);
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_TOUCH_ADJ_YMIN_ADDR,  4);
			break;

		case BAK_CUSTOM_PIC_ID:
			//I2C_EE_BufferWrite((uint8_t *)&value, BAK_CUSTOM_PIC_ADDR,  1);

		default:
			break;
	}
}

void bakup_file_path(uint8_t *path, uint32_t  len)
{
	if((path == 0) || (len == 0))
	{
		return;
	}
	HAL::AT24CXX_Write(BAK_FILE_PATH_LEN_ADDR,(uint8_t *)&len ,  1);
	HAL::AT24CXX_Write(BAK_FILE_PATH_ADDR,path ,  len);
}

uint8_t  DecStr2Float(int8_t * buf,  float  *result)
{
	int  index = 0;
	
	float  retVal = 0;
	int8_t  dot_flag = 0;
	int8_t  negat_flag = 0;
		
	if(buf == 0  ||  result == 0)
	{
		return  0;
	}

	do
	{
		if((buf[index] <= '9')  &&  (buf[index]  >= '0'))
		{
			if(dot_flag)
			{
				retVal  += (float)((buf[index] - '0') * pow((double )10, (double )(0 - dot_flag)));
				dot_flag++;
			}
			else
			{
				retVal  *=  10;
				retVal  += buf[index] - '0';
			}
			
		}
		else if(buf[index]  == '.')
		{
			dot_flag = 1;
		}
		else if(buf[index] == '-')
		{
				negat_flag = 1;
		}
		else
		{
				if(negat_flag)
				{
					*result = (float)0 - retVal;
				}
				else
				{
						*result = retVal;
				}
			
			return 1;
		}
		index++;
			
	} while(1);
	
}


/**********************end****************************/

