#include "draw_ui.h"
#include "Multi_language.h"


//********************************************//




#define PRINTING_GBK							"正在打印"
#define PRINTING_OPERATION_GBK				"操作"
#define PRINTING_PAUSE_GBK						"暂停"

#define PRINTING_OTHER_LANGUGE				"Printing"
#define PRINTING_OPERATION_OTHER_LANGUGE		"Operation"
#define PRINTING_PAUSE_OTHER_LANGUGE			"Pause"

#define PRINTING_SP				"Imprimiendo"
#define PRINTING_AJUSTES_SP		"Ajustes"
#define PRINTING_PAUSAR_SP			"Pausar"
//*********************************************//


common_menu_def common_menu;
main_menu_def main_menu;
preheat_menu_def preheat_menu;
move_menu_def move_menu;
home_menu_def home_menu;
file_menu_def file_menu;
extrude_menu_def extrude_menu;
leveling_menu_def leveling_menu;
set_menu_def set_menu;
more_menu_def more_menu;
wifi_menu_def wifi_menu;
cloud_menu_def cloud_menu;
about_menu_def about_menu;
fan_menu_def fan_menu;
filament_menu_def filament_menu;
printing_menu_def printing_menu;
operation_menu_def operation_menu;
pause_menu_def pause_menu;
speed_menu_def speed_menu;
printing_more_menu_def printing_more_menu;
dialog_menu_def dialog_menu;
language_menu_def language_menu;
print_file_dialog_menu_def print_file_dialog_menu;
filesys_menu_def filesys_menu;
zoffset_menu_def zoffset_menu;
tool_menu_def tool_menu;
MachinePara_menu_def MachinePara_menu;
MachineSettings_menu_def MachineSettings_menu;
TemperatureSettings_menu_def TemperatureSettings_menu;

machine_common_def machine_menu;

void machine_setting_disp()
{
    MachinePara_menu.title = MACHINE_PARA_TITLE_EN;
    MachinePara_menu.MachineSetting = MACHINE_TYPE_CNOFIG_EN;
    MachinePara_menu.TemperatureSetting=TEMPERATURE_CONFIG_EN;
    MachinePara_menu.MotorSetting=MOTOR_CONFIG_EN;
    MachinePara_menu.AdvanceSetting=ADVANCE_CONFIG_EN;
	MachinePara_menu.Custom = CUSTOM_CONFIG_EN;
	MachinePara_menu.Console = CONSOLE_EN;

    machine_menu.default_value = DEFAULT_EN;
    machine_menu.next=NEXT_EN;
    machine_menu.previous=PREVIOUS_EN;
	machine_menu.back  = BACK_TEXT_EN;

    machine_menu.MachineConfigTitle = MACHINE_CONFIG_TITLE_EN;
    machine_menu.MachineType=MACHINE_TYPE_EN;
    machine_menu.Stroke=MACHINE_STROKE_EN;
    machine_menu.HomeDir=MACHINE_HOMEDIR_EN;
    machine_menu.EndStopType=MACHINE_ENDSTOP_TYPE_EN;
    machine_menu.FilamentConf=MACHINE_FILAMENT_CONFIG_EN;
    machine_menu.LevelingConf=MACHINE_LEVELING_CONFIG_EN;
	machine_menu.BaudRateConf = MACHINE_BAUDRATE_CONFIG_EN;
	machine_menu.FirmwareType = MACHINE_FIRMWARE_CONFIG_EN;
	machine_menu.PausePosConf = MACHINE_PAUSEPOSI_CONFIG_EN;
	machine_menu.WifiConf = MACHINE_WIFI_CONFIG_EN;

    machine_menu.MachineTypeConfTitle = MACHINE_TYPE_CONFIG_TITLE_EN;
    machine_menu.xyz=MACHINE_TYPE_XYZ_EN;
    machine_menu.delta=MACHINE_TYPE_DELTA_EN;
    machine_menu.corexy=MACHINE_TYPE_COREXY_EN;
	machine_menu.normal= MACHINE_TYPE_NORMAL_EN;

    machine_menu.FirmwareTypeConfTitle = FIRMWARE_TYPE_CONFIG_TITLE_EN;
    machine_menu.marlin=FIRMWARE_TYPE_MARLIN_EN;
    machine_menu.repetier=FIRMWARE_TYPE_REPETIER_EN;
    machine_menu.smoothie=FIRMWARE_TYPE_SMOOTHIE_EN;

    machine_menu.BaudRateConfTitle = BAUD_RATE_CONFIG_TITLE_EN;
    machine_menu.rate1=BAUD_RATE_9600_EN;
    machine_menu.rate2=BAUD_RATE_57600_EN;
    machine_menu.rate3=BAUD_RATE_115200_EN;
	machine_menu.rate4=BAUD_RATE_250000_EN;

	machine_menu.wifiConfTile = WIFI_CONFIG_TILE_EN;
	machine_menu.WifiKey	  = WIFI_KEY_SET_EN;
	machine_menu.WifiMode	  = WIFI_MODE_SEL_EN;
	machine_menu.cloudEnable  = WIFI_CLOUD_ENABLE_EN;
	machine_menu.cloudHost 	  = WIFI_CLOUD_ADDR_EN;
	machine_menu.cloudPort    = WIFI_CLOUD_PORT_EN;
	machine_menu.WifiMode0	  = WIFI_MODE0_EN;
	machine_menu.WifiMode1	  = WIFI_MODE1_EN;
	machine_menu.WifiName	  = WIFI_NAME_SET_EN;
	

    machine_menu.StrokeConfTitle=MACHINE_STROKE_CONF_TITLE_EN;
    machine_menu.xStroke=X_MAX_LENGTH_EN;
    machine_menu.yStroke=Y_MAX_LENGTH_EN;
    machine_menu.zStroke=Z_MAX_LENGTH_EN;
	
    machine_menu.xmin=X_MIN_LENGTH_EN;
    machine_menu.ymin=Y_MIN_LENGTH_EN;
    machine_menu.zmin=Z_MIN_LENGTH_EN;

    machine_menu.HomeDirConfTitle=HOME_DIR_CONF_TITLE_EN;
    machine_menu.xHomeDir=HOME_DIR_X_EN;
    machine_menu.yHomeDir=HOME_DIR_Y_EN;
    machine_menu.zHomeDir=HOME_DIR_Z_EN;
    machine_menu.min=HOME_MIN_EN;
    machine_menu.max=HOME_MAX_EN;

    machine_menu.PositionPuaseConfTitle=PAUSE_POSITION_CONF_TITLE_EN;
    machine_menu.xPosition=POSITION_X_EN;
    machine_menu.yPosition=POSITION_Y_EN;
    machine_menu.zPosition=POSITION_Z_EN;

    machine_menu.EndstopConfTitle=ENDSTOP_CONF_TITLE_EN;
    machine_menu.xEndstop_min=MIN_ENDSTOP_X_EN;
    machine_menu.yEndstop_min=MIN_ENDSTOP_Y_EN;
    machine_menu.zEndstop_min=MIN_ENDSTOP_Z_EN;
    machine_menu.xEndstop_max=MAX_ENDSTOP_X_EN;
    machine_menu.yEndstop_max=MAX_ENDSTOP_Y_EN;
    machine_menu.zEndstop_max=MAX_ENDSTOP_Z_EN;            
    machine_menu.FilamentEndstop=ENDSTOP_FIL_EN;
    machine_menu.LevelingEndstop=ENDSTOP_LEVEL_EN;
    machine_menu.opened=ENDSTOP_OPENED_EN;
    machine_menu.closed=ENDSTOP_CLOSED_EN;

    machine_menu.FilamentConfTitle=FILAMENT_CONF_TITLE_EN;
    machine_menu.InTemperature=FILAMENT_IN_TEMPERATURE_EN;
    machine_menu.InLength=FILAMENT_IN_LENGTH_EN;
    machine_menu.InSpeed=FILAMENT_IN_SPEED_EN;
    machine_menu.OutTemperature=FILAMENT_OUT_TEMPERATURE_EN;
    machine_menu.OutLength=FILAMENT_OUT_LENGTH_EN;
    machine_menu.OutSpeed=FILAMENT_OUT_SPEED_EN;

    machine_menu.LevelingParaConfTitle=LEVELING_CONF_TITLE_EN;
    machine_menu.LevelingParaConf=LEVELING_PARA_CONF_EN;
    machine_menu.DeltaLevelConf=LEVELING_DELTA_EN;
    machine_menu.XYZLevelconf=LEVELING_XYZ_EN;

    machine_menu.LevelingSubConfTitle=LEVELING_PARA_CONF_TITLE_EN;
    machine_menu.AutoLevelEnable=AUTO_LEVELING_ENABLE_EN;
    machine_menu.BLtouchEnable=BLTOUCH_LEVELING_ENABLE_EN;
    machine_menu.ProbePort=PROBE_PORT_EN;
    machine_menu.ProbeXoffset=PROBE_X_OFFSET_EN;
    machine_menu.ProbeYoffset=PROBE_Y_OFFSET_EN;
    machine_menu.ProbeZoffset=PROBE_Z_OFFSET_EN;
    machine_menu.ProbeXYspeed=PROBE_XY_SPEED_EN;
    machine_menu.ProbeZspeed=PROBE_Z_SPEED_EN;
    machine_menu.enable = ENABLE_EN;
    machine_menu.disable = DISABLE_EN;
    machine_menu.z_min = Z_MIN_EN;
    machine_menu.z_max = Z_MAX_EN;
	machine_menu.leveling_z_speed = LEVELING_Z_SPEED_EN;
	machine_menu.leveling_xy_speed = LEVELING_XY_SPEED_EN;
	machine_menu.leveling_z_high = LEVELING_Z_HIGH_EN;

    machine_menu.LevelingSubDeltaConfTitle=DELTA_LEVEL_CONF_TITLE_EN;
    machine_menu.MachineRadius=DELTA_MACHINE_RADIUS_EN;
    machine_menu.DiagonalRod=DELTA_DIAGONAL_ROD_EN;
    machine_menu.PrintableRadius=DELTA_PRINT_RADIUS_EN;
    machine_menu.DeltaHeight=DELTA_HEIGHT_EN;
    machine_menu.SmoothRodOffset=SMOOTH_ROD_OFFSET_EN;
    machine_menu.EffectorOffset=EFFECTOR_OFFSET_EN;
    machine_menu.CalibrationRadius=CALIBRATION_RADIUS_EN;

    machine_menu.LevelingSubXYZConfTitle=XYZ_LEVEL_CONF_TITLE_EN;
    //machine_menu.Level_positon=PROBE_REACH_MAX_LEFT_EN;
    //machine_menu.ProbeMaxRigh=PROBE_REACH_MAX_RIGHT_EN;
    //machine_menu.ProbeMaxfront=PROBE_REACH_MAX_FRONT_EN;
   // machine_menu.ProbeMaxback=PROBE_REACH_MAX_BACK_EN;

    machine_menu.TemperatureConfTitle=TEMPERATURE_CONF_TITLE_EN;
    machine_menu.NozzleConf=NOZZLE_CONF_EN;
    machine_menu.HotBedConf=HOTBED_CONF_EN;
    machine_menu.PreheatTemperConf=PREHEAT_TEMPER_EN;

    machine_menu.NozzleConfTitle=NOZZLE_CONF_TITLE_EN;
    machine_menu.NozzleCnt=NOZZLECNT_EN;
    machine_menu.NozzleType=NOZZLE_TYPE_EN;
    machine_menu.NozzleAdjustType=NOZZLE_ADJUST_TYPE_EN;
    machine_menu.NozzleMinTemperature=NOZZLE_MIN_TEMPERATURE_EN;
    machine_menu.NozzleMaxTemperature=NOZZLE_MAX_TEMPERATURE_EN;
    machine_menu.Extrude_Min_Temper=EXTRUD_MIN_TEMPER_EN;

    machine_menu.HotbedEnable=HOTBED_ENABLE_EN;
    machine_menu.HotbedConfTitle=HOTBED_CONF_TITLE_EN;
    machine_menu.HotbedAjustType=HOTBED_ADJUST_EN;
    machine_menu.HotbedMinTemperature=HOTBED_MIN_TEMPERATURE_EN;
    machine_menu.HotbedMaxTemperature=HOTBED_MAX_TEMPERATURE_EN;

    machine_menu.MotorConfTitle=MOTOR_CONF_TITLE_EN;
    machine_menu.MaxFeedRateConf=MAXFEEDRATE_CONF_EN;
    machine_menu.AccelerationConf=ACCELERATION_CONF_EN;
    machine_menu.JerkConf=JERKCONF_EN;
    machine_menu.StepsConf=STEPSCONF_EN;
    machine_menu.MotorDirConf=MOTORDIRCONF_EN;
    machine_menu.HomeFeedRateConf=HOMEFEEDRATECONF_EN;
    machine_menu.CurrentConf=CURRENTCONF_EN;	
	machine_menu.GetInfo = GETEEPROM_EN;
	machine_menu.SaveInfo =SAVETOEEPROM_EN;
	machine_menu.TMCBumpSen = TMCBUMPCONF_EN;

    machine_menu.TMCBumpTitle=TMC_CONF_TITLE_EN;
    machine_menu.X_Sensivisity=X_SENSITIVITY_EN;
    machine_menu.Y_Sensivisity=Y_SENSITIVITY_EN;
    machine_menu.Z_Sensivisity=Z_SENSITIVITY_EN;

    machine_menu.MaxFeedRateConfTitle=MAXFEEDRATE_CONF_TITLE_EN;
    machine_menu.XMaxFeedRate=X_MAXFEEDRATE_EN;
    machine_menu.YMaxFeedRate=Y_MAXFEEDRATE_EN;
    machine_menu.ZMaxFeedRate=Z_MAXFEEDRATE_EN;
    machine_menu.E0MaxFeedRate=E0_MAXFEEDRATE_EN;
    machine_menu.E1MaxFeedRate=E1_MAXFEEDRATE_EN;

    machine_menu.AccelerationConfTitle=ACCELERATION_CONF_TITLE_EN;
    machine_menu.PrintAcceleration=PRINT_ACCELERATION_EN;
    machine_menu.RetractAcceleration=RETRACT_ACCELERATION_EN;
    machine_menu.TravelAcceleration=TRAVEL_ACCELERATION_EN;
    machine_menu.X_Acceleration=X_ACCELERATION_EN;
    machine_menu.Y_Acceleration=Y_ACCELERATION_EN;
    machine_menu.Z_Acceleration=Z_ACCELERATION_EN;
    machine_menu.E0_Acceleration=E0_ACCELERATION_EN;
    machine_menu.E1_Acceleration=E1_ACCELERATION_EN;

    machine_menu.JerkConfTitle=JERK_CONF_TITLE_EN;
    machine_menu.X_Jerk=X_JERK_EN;
    machine_menu.Y_Jerk=Y_JERK_EN;
    machine_menu.Z_Jerk=Z_JERK_EN;
    machine_menu.E_Jerk=E_JERK_EN;

    machine_menu.StepsConfTitle=STEPS_CONF_TITLE_EN;
    machine_menu.X_Steps=X_STEPS_EN;
    machine_menu.Y_Steps=Y_STEPS_EN;
    machine_menu.Z_Steps=Z_STEPS_EN;
    machine_menu.E0_Steps=E0_STEPS_EN;
    machine_menu.E1_Steps=E1_STEPS_EN;

    machine_menu.CurrentConfTitle=CURRENT_CONF_TITLE_EN;
    machine_menu.X_Current=X_CURRENT_EN;
    machine_menu.Y_Current=Y_CURRENT_EN;
    machine_menu.Z_Current=Z_CURRENT_EN;
    machine_menu.E0_Current=E0_CURRENT_EN;
    machine_menu.E1_Current=E1_CURRENT_EN;	

    machine_menu.MotorDirConfTitle=MOTORDIR_CONF_TITLE_EN;
    machine_menu.X_MotorDir=X_MOTORDIR_EN;
    machine_menu.Y_MotorDir=Y_MOTORDIR_EN;
    machine_menu.Z_MotorDir=Z_MOTORDIR_EN;
    machine_menu.E0_MotorDir=E0_MOTORDIR_EN;
    machine_menu.E1_MotorDir=E1_MOTORDIR_EN;
    machine_menu.Invert_0=INVERT_P_EN;
    machine_menu.Invert_1=INVERT_N_EN;

    machine_menu.HomeFeedRateConfTitle=HOMEFEEDRATE_CONF_TITLE_EN;
    machine_menu.XY_HomeFeedRate=X_HOMESPEED_EN;
    //machine_menu.Y_HomeFeedRate=Y_HOMESPEED_EN;
    machine_menu.Z_HomeFeedRate=Z_HOMESPEED_EN;

    machine_menu.AdvancedConfTitle=ADVANCED_CONF_TITLE_EN;
    machine_menu.PwrOffDection=PWROFF_DECTION_EN;
    machine_menu.PwrOffAfterPrint=PWROFF_AFTER_PRINT_EN;
    machine_menu.HaveUps=HAVE_UPS_EN;
    machine_menu.Z2andZ2Endstop=Z2_AND_Z2ENDSTOP_CONF_EN;
    machine_menu.EnablePinsInvert=ENABLE_PINS_CONF_EN;

    machine_menu.Z2ConfTitle=Z2_AND_Z2ENDSTOP_CONF_TITLE_EN;
    machine_menu.Z2Enable=Z2_ENABLE_EN;
    machine_menu.Z2EndstopEnable=Z2_ENDSTOP_EN;
    machine_menu.Z2Port=Z2_PORT_EN;

    machine_menu.EnablePinsInvertTitle=ENABLE_PINS_CONF_TITLE_EN;
    machine_menu.XInvert=X_ENABLE_PINS_INVERT_EN;
    machine_menu.YInvert=Y_ENABLE_PINS_INVERT_EN;
    machine_menu.ZInvert=Z_ENABLE_PINS_INVERT_EN;
    machine_menu.EInvert=E_ENABLE_PINS_INVERT_EN;

    machine_menu.key_back = KEY_BACK_EN;
    machine_menu.key_rest = KEY_REST_EN;
    machine_menu.key_confirm = KEY_CONFIRM_EN;
    //

    set_menu.machine_para = MACHINE_PARA_EN;

	machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_EN;
	machine_menu.low_level = MOTOR_EN_LOW_LEVEL_EN;

	machine_menu.CustomConfTitle = CUSTOMCONF_TITLE_EN;
	machine_menu.display		 = DISPLAY_CONF_EN;
	machine_menu.button 		 = BUTTON_CONF_EN;
	
	machine_menu.DisplayConfTitle = DISPLAY_TITLE_EN;
	machine_menu.btn_3D_ecffects = BUTTON_3D_EN;
	machine_menu.btn_text_offset = BTN_TEXT_OFFSET_EN;
	machine_menu.screen_overturn = SCREEN_OVERTURN_EN;
	machine_menu.display_mode =    DISPLAY_MODE_EN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_EN;
	machine_menu.simple_theme	= SIMPLETHEME_EN;
	machine_menu.classic_theme	= SIMPLETHEME_EN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_EN;
	machine_menu.babastepting = ENABLE_BABASTEPTING_EN;
	//
	machine_menu.buttonConfTitle = BUTTON_TITLE_EN;
	machine_menu.function_btn1_display = DISPLAY_FUNCTIONBTN1_EN;
	machine_menu.function_btn1_cmd = FUNCTION_BTN1_TEXT_EN;
	machine_menu.quickStop_btn = DISPLAY_QUICKSTOP_EN;
	machine_menu.zoffset_btn_display = DISPLAY_ZOFFSET_EN;
	machine_menu.print_more_btn  = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.more_btn		 = MORE_BTN_TITLE_EN;
	machine_menu.displayCalibrate = DISPLAY_CALIBRATE_EN;
	
	machine_menu.MoreButtonConfTitle = MORE_BTN_TITLE_EN;
	machine_menu.moreItem_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_btn1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_btn2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_btn3 = BUTTON3_NAME_EN;			
	machine_menu.moreItem_btn4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_btn5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_btn6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_btn7 = BUTTON7_NAME_EN;
	
	machine_menu.MoreFunctionConfTitle = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.morefunc_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_func1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_func2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_func3 = BUTTON3_NAME_EN;			 
	machine_menu.moreItem_func4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_func5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_func6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_func7 = BUTTON7_NAME_EN;

	machine_menu.AutoLevelCmd = AUTOLEVELCMD_EN;

}
void disp_language_init()
{
	preheat_menu.value_state= TEXT_VALUE;
	preheat_menu.step_1c= TEXT_1C;
	preheat_menu.step_5c= TEXT_5C;
	preheat_menu.step_10c= TEXT_10C;

	move_menu.x_add = AXIS_X_ADD_TEXT;
	move_menu.x_dec = AXIS_X_DEC_TEXT;
	move_menu.y_add = AXIS_Y_ADD_TEXT;
	move_menu.y_dec = AXIS_Y_DEC_TEXT;
	move_menu.z_add = AXIS_Z_ADD_TEXT;
	move_menu.z_dec = AXIS_Z_DEC_TEXT;
	
	move_menu.step_01mm = TEXT_01MM;
	move_menu.step_1mm = TEXT_1MM;
	move_menu.step_10mm = TEXT_10MM;
	move_menu.step_001mm = TEXT_001MM;
	move_menu.step_005mm = TEXT_005MM;

	home_menu.home_x= HOME_X_TEXT;
	home_menu.home_y= HOME_Y_TEXT;
	home_menu.home_z= HOME_Z_TEXT;
	home_menu.home_all= HOME_ALL_TEXT;

	extrude_menu.temp_value = TEXT_VALUE_T;
	extrude_menu.count_value_mm= TEXT_VALUE_mm;
	extrude_menu.count_value_cm= TEXT_VALUE_cm;
	extrude_menu.count_value_m= TEXT_VALUE_m;
	extrude_menu.step_1mm = EXTRUDE_1MM_TEXT;
	extrude_menu.step_5mm = EXTRUDE_5MM_TEXT;
	extrude_menu.step_10mm = EXTRUDE_10MM_TEXT;

	fan_menu.full = FAN_OPEN_TEXT;
	fan_menu.half = FAN_HALF_TEXT;
	fan_menu.off = FAN_CLOSE_TEXT;

	speed_menu.step_1percent = STEP_1PERCENT;
	speed_menu.step_5percent = STEP_5PERCENT;
	speed_menu.step_10percent = STEP_10PERCENT;

	language_menu.chinese_s = LANGUAGE_S_CN;
	language_menu.chinese_t = LANGUAGE_T_CN;
	language_menu.english = LANGUAGE_EN;
	language_menu.russian = LANGUAGE_RU;
	language_menu.spanish = LANGUAGE_SP;
	language_menu.german = LANGUAGE_GE;
	language_menu.japan = LANGUAGE_JP;
	language_menu.korean = LANGUAGE_KR;
	language_menu.portuguese = LANGUAGE_PR;
	language_menu.italy = LANGUAGE_IT;
	language_menu.brazil = LANGUAGE_BR;
	language_menu.french = LANGUAGE_FR;
    
	about_menu.type_name= ABOUT_TYPE_TEXT;
	about_menu.firmware_v= ABOUT_VERSION_TEXT;
	//about_menu.wifi = ABOUT_WIFI_TEXT;	

	wifi_menu.ip = WIFI_IP_TEXT;
	wifi_menu.wifi = WIFI_NAME_TEXT;
	wifi_menu.key = WIFI_KEY_TEXT;
	wifi_menu.state_ap = WIFI_STATE_AP_TEXT;
	wifi_menu.state_sta = WIFI_STATE_STA_TEXT;
	wifi_menu.connected = WIFI_CONNECTED_TEXT;
	wifi_menu.disconnected = WIFI_DISCONNECTED_TEXT;
	wifi_menu.exception = WIFI_EXCEPTION_TEXT;

	printing_menu.temp1 = TEXT_VALUE;
	printing_menu.temp2 = TEXT_VALUE;
	printing_menu.bed_temp = TEXT_VALUE;

	filament_menu.stat_temp = TEXT_VALUE;

	zoffset_menu.step001 = ZOFFSET_STEP001;
	zoffset_menu.step01 = ZOFFSET_STEP01;
	zoffset_menu.step1 = ZOFFSET_STEP1;
//
    machine_menu.key_0 = KEYBOARD_KEY0_EN;
    machine_menu.key_1 = KEYBOARD_KEY1_EN;
    machine_menu.key_2 = KEYBOARD_KEY2_EN;
    machine_menu.key_3 = KEYBOARD_KEY3_EN;
    machine_menu.key_4 = KEYBOARD_KEY4_EN;
    machine_menu.key_5 = KEYBOARD_KEY5_EN;
    machine_menu.key_6 = KEYBOARD_KEY6_EN;
    machine_menu.key_7 = KEYBOARD_KEY7_EN;
    machine_menu.key_8 = KEYBOARD_KEY8_EN;
    machine_menu.key_9 = KEYBOARD_KEY9_EN;
    machine_menu.key_point= KEYBOARD_KEY_POINT_EN;
	machine_menu.negative=KEYBOARD_KEY_NEGATIVE_EN;

    	keyboard_menu.apply=MANUAL_IP_APPLY_EN;
	keyboard_menu.password=TEXT_WIFI_PASSWORD_EN;
	keyboard_menu.space = TEXT_WIFI_SAPCE_EN;
      keyboard_menu.letter = TEXT_WIFI_LETTER_EN;
      keyboard_menu.digital = TEXT_WIFI_DIGITAL_EN;
      keyboard_menu.symbol = TEXT_WIFI_SYMBOL_EN;  
	keyboard_menu.send = TEXT_SEND_EN;  
	
      //tips
      tips_menu.pointBold = TEXT_WIFI_POINT_BOLD_EN;
	   tips_menu.joining = TEXT_WIFI_JOINING_EN;
	   tips_menu.failedJoin = TEXT_WIFI_FAILED_JOIN_EN;
	   tips_menu.wifiConected = TEXT_WIFI_WIFI_CONECTED_EN;	
	   
    machine_setting_disp();
	operation_menu.babystep = TEXT_BABY_STEP;
		
	switch(gCfgItems.language)
	{
		case LANG_SIMPLE_CHINESE:
           //
              MachinePara_menu.title = MACHINE_PARA_TITLE_CN;
            MachinePara_menu.MachineSetting = MACHINE_TYPE_CNOFIG_CN;
            MachinePara_menu.TemperatureSetting=TEMPERATURE_CONFIG_CN;
            MachinePara_menu.MotorSetting=MOTOR_CONFIG_CN;
            MachinePara_menu.AdvanceSetting=ADVANCE_CONFIG_CN;
            MachinePara_menu.Custom = CUSTOM_CONFIG_CN;
            machine_menu.default_value = DEFAULT_CN;
            machine_menu.next=NEXT_CN;
            machine_menu.previous=PREVIOUS_CN;
			machine_menu.back  = BACK_TEXT_CN;

            machine_menu.MachineConfigTitle = MACHINE_CONFIG_TITLE_CN;
            machine_menu.MachineType=MACHINE_TYPE_CN;
            machine_menu.Stroke=MACHINE_STROKE_CN;
            machine_menu.HomeDir=MACHINE_HOMEDIR_CN;
//            machine_menu.EndStopType=MACHINE_ENDSTOP_TYPE_CN;
            machine_menu.FilamentConf=MACHINE_FILAMENT_CONFIG_CN;
            machine_menu.LevelingConf=MACHINE_LEVELING_CONFIG_CN;
	machine_menu.BaudRateConf = MACHINE_BAUDRATE_CONFIG_CN;
	machine_menu.FirmwareType = MACHINE_FIRMWARE_CONFIG_CN;
	machine_menu.PausePosConf = MACHINE_PAUSEPOSI_CONFIG_CN;
	machine_menu.WifiConf = MACHINE_WIFI_CONFIG_CN;
            machine_menu.MachineTypeConfTitle = MACHINE_TYPE_CONFIG_TITLE_CN;
            machine_menu.xyz=MACHINE_TYPE_XYZ_CN;
            machine_menu.delta=MACHINE_TYPE_DELTA_CN;
            machine_menu.corexy=MACHINE_TYPE_COREXY_CN;
					machine_menu.normal= MACHINE_TYPE_NORMAL_CN;
            
    machine_menu.FirmwareTypeConfTitle = FIRMWARE_TYPE_CONFIG_TITLE_CN;
    machine_menu.marlin=FIRMWARE_TYPE_MARLIN_CN;
    machine_menu.repetier=FIRMWARE_TYPE_REPETIER_CN;
    machine_menu.smoothie=FIRMWARE_TYPE_SMOOTHIE_CN;

    machine_menu.BaudRateConfTitle = BAUD_RATE_CONFIG_TITLE_CN;
//    machine_menu.rate1=BAUD_RATE_9600_CN;
//    machine_menu.rate2=BAUD_RATE_57600_CN;
//    machine_menu.rate3=BAUD_RATE_115200_CN;
//	machine_menu.rate4=BAUD_RATE_250000_CN;

	machine_menu.wifiConfTile = WIFI_CONFIG_TILE_CN;
	machine_menu.WifiKey	  = WIFI_KEY_SET_CN;
	machine_menu.WifiMode	  = WIFI_MODE_SEL_CN;
	machine_menu.cloudEnable  = WIFI_CLOUD_CNABLE_CN;
	machine_menu.cloudHost 	  = WIFI_CLOUD_ADDR_CN;
	machine_menu.cloudPort    = WIFI_CLOUD_PORT_CN;
	machine_menu.WifiMode0	  = WIFI_MODE0_CN;
	machine_menu.WifiMode1	  = WIFI_MODE1_CN;
	machine_menu.WifiName	  = WIFI_NAME_SET_CN;
//	keyboard_menu.apply=KEY_CONFIRM_CN;

//		keyboard_menu.send = TEXT_SEND_CN; 
		
            machine_menu.StrokeConfTitle=MACHINE_STROKE_CONF_TITLE_CN;
            machine_menu.xStroke=X_MAX_LENGTH_CN;
            machine_menu.yStroke=Y_MAX_LENGTH_CN;
            machine_menu.zStroke=Z_MAX_LENGTH_CN;
			
	    machine_menu.xmin=X_MIN_LENGTH_CN;
	    machine_menu.ymin=Y_MIN_LENGTH_CN;
	    machine_menu.zmin=Z_MIN_LENGTH_CN;

            machine_menu.HomeDirConfTitle=HOME_DIR_CONF_TITLE_CN;
            machine_menu.xHomeDir=HOME_DIR_X_CN;
            machine_menu.yHomeDir=HOME_DIR_Y_CN;
            machine_menu.zHomeDir=HOME_DIR_Z_CN;
            machine_menu.min=HOME_MIN_CN;
            machine_menu.max=HOME_MAX_CN;

			machine_menu.PositionPuaseConfTitle=PAUSE_POSITION_CONF_TITLE_CN;
			machine_menu.xPosition=POSITION_X_CN;
			machine_menu.yPosition=POSITION_Y_CN;
			machine_menu.zPosition=POSITION_Z_CN;
            machine_menu.EndstopConfTitle=ENDSTOP_CONF_TITLE_CN;
//            machine_menu.xEndstop_min=MIN_ENDSTOP_X_CN;
//            machine_menu.yEndstop_min=MIN_ENDSTOP_Y_CN;
//            machine_menu.zEndstop_min=MIN_ENDSTOP_Z_CN;
//            machine_menu.xEndstop_max=MAX_ENDSTOP_X_CN;
//            machine_menu.yEndstop_max=MAX_ENDSTOP_Y_CN;
//            machine_menu.zEndstop_max=MAX_ENDSTOP_Z_CN;            
            machine_menu.FilamentEndstop=ENDSTOP_FIL_CN;
            machine_menu.LevelingEndstop=ENDSTOP_LEVEL_CN;
            machine_menu.opened=ENDSTOP_OPENED_CN;
            machine_menu.closed=ENDSTOP_CLOSED_CN;

            machine_menu.FilamentConfTitle=FILAMENT_CONF_TITLE_CN;
            machine_menu.InTemperature=FILAMENT_IN_TEMPERATURE_CN;
            machine_menu.InLength=FILAMENT_IN_LENGTH_CN;
            machine_menu.InSpeed=FILAMENT_IN_SPEED_CN;
            machine_menu.OutTemperature=FILAMENT_OUT_TEMPERATURE_CN;
            machine_menu.OutLength=FILAMENT_OUT_LENGTH_CN;
            machine_menu.OutSpeed=FILAMENT_OUT_SPEED_CN;
                        
            machine_menu.LevelingParaConfTitle=LEVELING_CONF_TITLE_CN;
            machine_menu.LevelingParaConf=LEVELING_PARA_CONF_CN;
            machine_menu.DeltaLevelConf=LEVELING_DELTA_CN;
            machine_menu.XYZLevelconf=LEVELING_XYZ_CN;

            machine_menu.LevelingSubConfTitle=LEVELING_PARA_CONF_TITLE_CN;
            machine_menu.AutoLevelEnable=AUTO_LEVELING_ENABLE_CN;
//            machine_menu.BLtouchEnable=BLTOUCH_LEVELING_ENABLE_CN;
            machine_menu.ProbePort=PROBE_PORT_CN;
            machine_menu.ProbeXoffset=PROBE_X_OFFSET_CN;
            machine_menu.ProbeYoffset=PROBE_Y_OFFSET_CN;
            machine_menu.ProbeZoffset=PROBE_Z_OFFSET_CN;
            machine_menu.ProbeXYspeed=PROBE_XY_SPEED_CN;
            machine_menu.ProbeZspeed=PROBE_Z_SPEED_CN;
            machine_menu.enable = ENABLE_CN;
            machine_menu.disable = DISABLE_CN;
            machine_menu.z_min = Z_MIN_CN;
            machine_menu.z_max = Z_MAX_CN;
					machine_menu.high_level = LEVEL_HIGH_CN;
					machine_menu.low_level = LEVEL_LOW_CN;
					machine_menu.pwr_saveMode = OFF_SAVE_MODE_CN;
					machine_menu.pwr_saveMode1 = OFF_SAVE_MODE1_CN;
					machine_menu.pwr_saveMode2 = OFF_SAVE_MODE2_CN;
					machine_menu.disable_PB0_PB1 = DISABLE_PB1_PB0_CONF_CN;
					machine_menu.level_PB0 = LEVEL_PB0_CONF_CN;
					machine_menu.level_PB1 = LEVEL_PB1_CONF_CN;
					machine_menu.z_error = BREAKPOINT_Z_ERROR_CN;
            	
			machine_menu.leveling_z_speed = LEVELING_Z_SPEED_CN;
			machine_menu.leveling_xy_speed = LEVELING_XY_SPEED_CN;
			machine_menu.leveling_z_high = LEVELING_Z_HIGH_CN;

            machine_menu.LevelingSubDeltaConfTitle=DELTA_LEVEL_CONF_TITLE_CN;
            machine_menu.MachineRadius=DELTA_MACHINE_RADIUS_CN;
            machine_menu.DiagonalRod=DELTA_DIAGONAL_ROD_CN;
            machine_menu.PrintableRadius=DELTA_PRINT_RADIUS_CN;
            machine_menu.DeltaHeight=DELTA_HEIGHT_CN;
            machine_menu.SmoothRodOffset=SMOOTH_ROD_OFFSET_CN;
            machine_menu.EffectorOffset=EFFECTOR_OFFSET_CN;
            machine_menu.CalibrationRadius=CALIBRATION_RADIUS_CN;

            machine_menu.LevelingSubXYZConfTitle=XYZ_LEVEL_CONF_TITLE_CN;
            //machine_menu.ProbeMaxLeft=PROBE_REACH_MAX_LEFT_CN;
            //machine_menu.ProbeMaxRigh=PROBE_REACH_MAX_RIGHT_CN;
            //machine_menu.ProbeMaxfront=PROBE_REACH_MAX_FRONT_CN;
            //machine_menu.ProbeMaxback=PROBE_REACH_MAX_BACK_CN;

            machine_menu.TemperatureConfTitle=TEMPERATURE_CONF_TITLE_CN;
            machine_menu.NozzleConf=NOZZLE_CONF_CN;
            machine_menu.HotBedConf=HOTBED_CONF_CN;
			machine_menu.PreheatTemperConf=PREHEAT_TEMPER_CN;

            machine_menu.NozzleConfTitle=NOZZLE_CONF_TITLE_CN;
            machine_menu.NozzleCnt=NOZZLECNT_CN;
            machine_menu.NozzleType=NOZZLE_TYPE_CN;
            machine_menu.NozzleAdjustType=NOZZLE_ADJUST_TYPE_CN;
            machine_menu.NozzleMinTemperature=NOZZLE_MIN_TEMPERATURE_CN;
            machine_menu.NozzleMaxTemperature=NOZZLE_MAX_TEMPERATURE_CN;
			machine_menu.Extrude_Min_Temper=EXTRUD_MIN_TEMPER_CN;

	     machine_menu.HotbedEnable=HOTBED_ENABLE_CN;
            machine_menu.HotbedConfTitle=HOTBED_CONF_TITLE_CN;
            machine_menu.HotbedAjustType=HOTBED_ADJUST_CN;
            machine_menu.HotbedMinTemperature=HOTBED_MIN_TEMPERATURE_CN;
            machine_menu.HotbedMaxTemperature=HOTBED_MAX_TEMPERATURE_CN;

            machine_menu.MotorConfTitle=MOTOR_CONF_TITLE_CN;
            machine_menu.MaxFeedRateConf=MAXFEEDRATE_CONF_CN;
            machine_menu.AccelerationConf=ACCELERATION_CONF_CN;
            machine_menu.JerkConf=JERKCONF_CN;
            machine_menu.StepsConf=STEPSCONF_CN;
            machine_menu.MotorDirConf=MOTORDIRCONF_CN;
            machine_menu.HomeFeedRateConf=HOMEFEEDRATECONF_CN;
		    machine_menu.CurrentConf=CURRENTCONF_CN;	
		    machine_menu.GetInfo = GETEEPROM_CN;
		    machine_menu.SaveInfo =SAVETOEEPROM_CN;
		    machine_menu.TMCBumpSen = TMCBUMPCONF_CN;

		    machine_menu.TMCBumpTitle=TMC_CONF_TITLE_CN;
		    machine_menu.X_Sensivisity=X_SENSITIVITY_CN;
		    machine_menu.Y_Sensivisity=Y_SENSITIVITY_CN;
		    machine_menu.Z_Sensivisity=Z_SENSITIVITY_CN;
            machine_menu.MaxFeedRateConfTitle=MAXFEEDRATE_CONF_TITLE_CN;
            machine_menu.XMaxFeedRate=X_MAXFEEDRATE_CN;
            machine_menu.YMaxFeedRate=Y_MAXFEEDRATE_CN;
            machine_menu.ZMaxFeedRate=Z_MAXFEEDRATE_CN;
            machine_menu.E0MaxFeedRate=E0_MAXFEEDRATE_CN;
            machine_menu.E1MaxFeedRate=E1_MAXFEEDRATE_CN;

            machine_menu.AccelerationConfTitle=ACCELERATION_CONF_TITLE_CN;
            machine_menu.PrintAcceleration=PRINT_ACCELERATION_CN;
            machine_menu.RetractAcceleration=RETRACT_ACCELERATION_CN;
            machine_menu.TravelAcceleration=TRAVEL_ACCELERATION_CN;
            machine_menu.X_Acceleration=X_ACCELERATION_CN;
            machine_menu.Y_Acceleration=Y_ACCELERATION_CN;
            machine_menu.Z_Acceleration=Z_ACCELERATION_CN;
            machine_menu.E0_Acceleration=E0_ACCELERATION_CN;
            machine_menu.E1_Acceleration=E1_ACCELERATION_CN;

            machine_menu.JerkConfTitle=JERK_CONF_TITLE_CN;
            machine_menu.X_Jerk=X_JERK_CN;
            machine_menu.Y_Jerk=Y_JERK_CN;
            machine_menu.Z_Jerk=Z_JERK_CN;
            machine_menu.E_Jerk=E_JERK_CN;

            machine_menu.StepsConfTitle=STEPS_CONF_TITLE_CN;
            machine_menu.X_Steps=X_STEPS_CN;
            machine_menu.Y_Steps=Y_STEPS_CN;
            machine_menu.Z_Steps=Z_STEPS_CN;
            machine_menu.E0_Steps=E0_STEPS_CN;
            machine_menu.E1_Steps=E1_STEPS_CN;
            
		    machine_menu.CurrentConfTitle=CURRENT_CONF_TITLE_CN;
		    machine_menu.X_Current=X_CURRENT_CN;
		    machine_menu.Y_Current=Y_CURRENT_CN;
		    machine_menu.Z_Current=Z_CURRENT_CN;
		    machine_menu.E0_Current=E0_CURRENT_CN;
		    machine_menu.E1_Current=E1_CURRENT_CN;	
            machine_menu.MotorDirConfTitle=MOTORDIR_CONF_TITLE_CN;
            machine_menu.X_MotorDir=X_MOTORDIR_CN;
            machine_menu.Y_MotorDir=Y_MOTORDIR_CN;
            machine_menu.Z_MotorDir=Z_MOTORDIR_CN;
            machine_menu.E0_MotorDir=E0_MOTORDIR_CN;
            machine_menu.E1_MotorDir=E1_MOTORDIR_CN;
            machine_menu.Invert_0=INVERT_P_CN;
            machine_menu.Invert_1=INVERT_N_CN;

            machine_menu.HomeFeedRateConfTitle=HOMEFEEDRATE_CONF_TITLE_CN;
            machine_menu.XY_HomeFeedRate=X_HOMESPEED_CN;
            //machine_menu.Y_HomeFeedRate=Y_HOMESPEED_CN;
            machine_menu.Z_HomeFeedRate=Z_HOMESPEED_CN;
          
            machine_menu.AdvancedConfTitle=ADVANCED_CONF_TITLE_CN;
            machine_menu.PwrOffDection=PWROFF_DECTION_CN;
            machine_menu.PwrOffAfterPrint=PWROFF_AFTER_PRINT_CN;
            machine_menu.HaveUps=HAVE_UPS_CN;
            machine_menu.Z2andZ2Endstop=Z2_AND_Z2ENDSTOP_CONF_CN;
            machine_menu.EnablePinsInvert=ENABLE_PINS_CONF_CN;

            machine_menu.Z2ConfTitle=Z2_AND_Z2ENDSTOP_CONF_TITLE_CN;
//            machine_menu.Z2Enable=Z2_ENABLE_CN;
//            machine_menu.Z2EndstopEnable=Z2_ENDSTOP_CN;
            machine_menu.Z2Port=Z2_PORT_CN;

            machine_menu.EnablePinsInvertTitle=ENABLE_PINS_CONF_TITLE_CN;
//            machine_menu.XInvert=X_ENABLE_PINS_INVERT_CN;
//            machine_menu.YInvert=Y_ENABLE_PINS_INVERT_CN;
//            machine_menu.ZInvert=Z_ENABLE_PINS_INVERT_CN;
//            machine_menu.EInvert=E_ENABLE_PINS_INVERT_CN;

            machine_menu.key_back = KEY_BACK_CN;
            machine_menu.key_rest = KEY_REST_CN;
            machine_menu.key_confirm = KEY_CONFIRM_CN;
  		  set_menu.machine_para = MACHINE_PARA_CN;
					machine_menu.high_level = MOTOR_CN_HIGH_LEVEL_CN;
					machine_menu.low_level = MOTOR_CN_LOW_LEVEL_CN;
	machine_menu.CustomConfTitle = CUSTOMCONF_TITLE_CN;
	machine_menu.display		 = DISPLAY_CONF_CN;
	machine_menu.button 		 = BUTTON_CONF_CN;
	
	machine_menu.DisplayConfTitle = DISPLAY_TITLE_CN;
	machine_menu.btn_3D_ecffects = BUTTON_3D_CN;
	machine_menu.btn_text_offset = BTN_TEXT_OFFSET_CN;
	machine_menu.screen_overturn = SCREEN_OVERTURN_CN;
	machine_menu.display_mode =    DISPLAY_MODE_CN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_CN;
	machine_menu.babastepting    = ENABLE_BABASTEPTING_CN;
	machine_menu.simple_theme	= SIMPLETHEME_CN;
	machine_menu.classic_theme	= CLASSICTHEME_CN;	
	//
	machine_menu.buttonConfTitle = BUTTON_TITLE_CN;
	machine_menu.function_btn1_display = DISPLAY_FUNCTIONBTN1_CN;
	machine_menu.function_btn1_cmd = FUNCTION_BTN1_TEXT_CN;
	machine_menu.quickStop_btn = DISPLAY_QUICKSTOP_CN;
	machine_menu.zoffset_btn_display = DISPLAY_ZOFFSET_CN;
	machine_menu.print_more_btn  = PRINT_MORE_BTN_TITLE_CN;
	machine_menu.more_btn		 = MORE_BTN_TITLE_CN;
	machine_menu.displayCalibrate = DISPLAY_CALIBRATE_CN;
	machine_menu.MoreButtonConfTitle = MORE_BTN_TITLE_CN;
	machine_menu.moreItem_cnt = BUTTON_COUNT_CN;
	machine_menu.moreItem_btn1 = BUTTON1_NAME_CN;
	machine_menu.moreItem_btn2 = BUTTON2_NAME_CN;
	machine_menu.moreItem_btn3 = BUTTON3_NAME_CN;			
	machine_menu.moreItem_btn4 = BUTTON4_NAME_CN;
	machine_menu.moreItem_btn5 = BUTTON5_NAME_CN;
	machine_menu.moreItem_btn6 = BUTTON6_NAME_CN;
	machine_menu.moreItem_btn7 = BUTTON7_NAME_CN;
	
	machine_menu.MoreFunctionConfTitle = PRINT_MORE_BTN_TITLE_CN;
	machine_menu.morefunc_cnt = BUTTON_COUNT_CN;
	machine_menu.moreItem_func1 = BUTTON1_NAME_CN;
	machine_menu.moreItem_func2 = BUTTON2_NAME_CN;
	machine_menu.moreItem_func3 = BUTTON3_NAME_CN;			 
	machine_menu.moreItem_func4 = BUTTON4_NAME_CN;
	machine_menu.moreItem_func5 = BUTTON5_NAME_CN;
	machine_menu.moreItem_func6 = BUTTON6_NAME_CN;
	machine_menu.moreItem_func7 = BUTTON7_NAME_CN;

	machine_menu.AutoLevelCmd = AUTOLEVELCMD_CN;
//			machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_CN;
//			machine_menu.low_level = MOTOR_EN_LOW_LEVEL_CN;
            //
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_CN;
			common_menu.text_back=BACK_TEXT_CN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_CN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_CN;
			common_menu.print_special_title = PRINTING_GBK;
			common_menu.pause_special_title = PRINTING_PAUSE_GBK;
			common_menu.operate_special_title = PRINTING_OPERATION_GBK;			
			//主页面
			main_menu.title=TITLE_READYPRINT_CN;
			main_menu.preheat=PREHEAT_TEXT_CN;
			main_menu.move=MOVE_TEXT_CN;
			main_menu.home=HOME_TEXT_CN;
			main_menu.print=PRINT_TEXT_CN;
			main_menu.extrude=EXTRUDE_TEXT_CN;
			main_menu.leveling=LEVELING_TEXT_CN;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_CN;
			main_menu.fan = FAN_TEXT_CN;
			main_menu.set=SET_TEXT_CN;
			main_menu.more=MORE_TEXT_CN;
			main_menu.tool = TOOL_TEXT_CN;
			//TOOL
			tool_menu.title = TOOL_TEXT_CN;
			tool_menu.preheat = TOOL_PREHEAT_CN;
			tool_menu.extrude = TOOL_EXTRUDE_CN;
			tool_menu.move = TOOL_MOVE_CN;
			tool_menu.home= TOOL_HOME_CN;
			tool_menu.leveling = TOOL_LEVELING_CN;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_CN;
			tool_menu.filament = TOOL_FILAMENT_CN;
			tool_menu.more = TOOL_MORE_CN;			
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_CN;
			preheat_menu.title=TITLE_PREHEAT_CN;
			preheat_menu.add=ADD_TEXT_CN;
			preheat_menu.dec=DEC_TEXT_CN;
			preheat_menu.ext1=EXTRUDER_1_TEXT_CN;
			preheat_menu.ext2=EXTRUDER_2_TEXT_CN;
			preheat_menu.hotbed=HEATBED_TEXT_CN;
			preheat_menu.off=CLOSE_TEXT_CN;
			//移动
			move_menu.title = MOVE_TEXT_CN;
			//归零
			home_menu.title=TITLE_HOME_CN;
			home_menu.stopmove = HOME_STOPMOVE_CN;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_CN;
			file_menu.page_up=PAGE_UP_TEXT_CN;
			file_menu.page_down=PAGE_DOWN_TEXT_CN;
			file_menu.file_loading = FILE_LOADING_CN;
			file_menu.no_file = NO_FILE_CN;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_CN;//NO_FILE_AND_CHECK_CN;
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_CN;
			extrude_menu.in=EXTRUDER_IN_TEXT_CN;
			extrude_menu.out=EXTRUDER_OUT_TEXT_CN;
			extrude_menu.ext1=EXTRUDER_1_TEXT_CN;
			extrude_menu.ext2=EXTRUDER_2_TEXT_CN;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_CN;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_CN;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_CN;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_CN;
			//调平
			leveling_menu.title=TITLE_LEVELING_CN;
			leveling_menu.position1=LEVELING_POINT1_TEXT_CN;
			leveling_menu.position2=LEVELING_POINT2_TEXT_CN;
			leveling_menu.position3=LEVELING_POINT3_TEXT_CN;
			leveling_menu.position4=LEVELING_POINT4_TEXT_CN;
			leveling_menu.position5=LEVELING_POINT5_TEXT_CN;
			leveling_menu.count=LEVELING_POINTS_TEXT_CN;
			//设置
			set_menu.title=TITLE_SET_CN;
			set_menu.filesys=FILESYS_TEXT_CN;
			set_menu.wifi=WIFI_TEXT_CN;
			set_menu.about=ABOUT_TEXT_CN;
			set_menu.fan=FAN_TEXT_CN;
			set_menu.filament=FILAMENT_TEXT_CN;
			set_menu.breakpoint=BREAK_POINT_TEXT_CN;
			set_menu.motoroff=MOTOR_OFF_TEXT_CN;
			set_menu.language=LANGUAGE_TEXT_CN;
            set_menu.machine_para = MACHINE_PARA_CN;//
            
			//????
			filesys_menu.title = TITLE_FILESYS_CN;
			filesys_menu.sd_sys = SD_CARD_TEXT_CN;
			filesys_menu.usb_sys = U_DISK_TEXT_CN;
			//更多
			more_menu.title = TITLE_MORE_CN;
			more_menu.zoffset = ZOFFSET_CN;
			more_menu.calibrate = CALIBRATE_CN;
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_CN;
			//wifi_menu.ip = WIFI_IP_TEXT_CN;
			//wifi_menu.state= WIFI_STA_TEXT_CN;
			wifi_menu.cloud= CLOUD_TEXT_CN;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_CN;
			//CLOUD
			cloud_menu.title = TITLE_CLOUD_TEXT_CN;
			cloud_menu.bind = CLOUD_BINDED_CN;
			cloud_menu.binded = CLOUD_BINDED_CN;
			cloud_menu.unbind = CLOUD_UNBIND_CN;
			cloud_menu.unbinding = CLOUD_UNBINDED_CN;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_CN;
			cloud_menu.disable = CLOUD_DISABLE_CN;
			//关于
			about_menu.title = ABOUT_TEXT_CN;
			about_menu.type = ABOUT_TYPE_TEXT_CN;
			about_menu.version = ABOUT_VERSION_TEXT_CN;
			about_menu.wifi = ABOUT_WIFI_TEXT_CN;	

			//风扇
			fan_menu.title = FAN_TEXT_CN;
			fan_menu.add = FAN_ADD_TEXT_CN;
			fan_menu.dec = FAN_DEC_TEXT_CN;
			fan_menu.state = FAN_TIPS1_TEXT_CN;
			//换料
			filament_menu.title = TITLE_FILAMENT_CN;
			filament_menu.in = FILAMENT_IN_TEXT_CN;
			filament_menu.out = FILAMENT_OUT_TEXT_CN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_CN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_CN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_CN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_CN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_CN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_CN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_CN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_CN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_CN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_CN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_CN;


			//语言
			language_menu.title = TITLE_LANGUAGE_CN;
			language_menu.next = PAGE_DOWN_TEXT_CN;
			language_menu.up = PAGE_UP_TEXT_CN;
			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_CN;
			printing_menu.option = PRINTING_OPERATION_CN;
			printing_menu.stop = PRINTING_STOP_CN;
			printing_menu.pause = PRINTING_PAUSE_CN;
			printing_menu.resume = PRINTING_RESUME_CN;

			//操作界面
			operation_menu.title = TITLE_OPERATION_CN;
			operation_menu.pause = PRINTING_PAUSE_CN;
			operation_menu.stop = PRINTING_STOP_CN;
			operation_menu.temp = PRINTING_TEMP_CN;
			operation_menu.fan = FAN_TEXT_CN;
			operation_menu.filament= FILAMENT_TEXT_CN;
			operation_menu.extr = PRINTING_EXTRUDER_CN;
			operation_menu.speed = PRINTING_CHANGESPEED_CN;
			operation_menu.more = PRINTING_MORE_CN;
			operation_menu.move = PRINTING_MOVE_CN;
			operation_menu.auto_off = AUTO_SHUTDOWN_CN;
			operation_menu.manual_off = MANUAL_SHUTDOWN_CN;			
			//暂停界面
			pause_menu.title= TITLE_PAUSE_CN;
			pause_menu.resume = PRINTING_RESUME_CN;
			pause_menu.stop = PRINTING_STOP_CN;
			pause_menu.extrude = PRINTING_EXTRUDER_CN;
			pause_menu.move = PRINTING_MOVE_CN;
			pause_menu.filament= FILAMENT_TEXT_CN;
			pause_menu.more = PRINTING_MORE_CN;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_CN;
			speed_menu.add = ADD_TEXT_CN;
			speed_menu.dec = DEC_TEXT_CN;
			speed_menu.move = MOVE_SPEED_CN;
			speed_menu.extrude = EXTRUDER_SPEED_CN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_CN;
			speed_menu.move_speed = MOVE_SPEED_STATE_CN;
			//打印中---更多界面
			printing_more_menu.title = TITLE_MORE_CN;
			printing_more_menu.fan = FAN_TEXT_CN;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_CN;
			printing_more_menu.manual = MANUAL_SHUTDOWN_CN;
			printing_more_menu.speed = PRINTING_CHANGESPEED_CN;
			printing_more_menu.temp = PRINTING_TEMP_CN;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_CN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_CN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_CN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_CN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_CN;
			print_file_dialog_menu.retry = DIALOG_RETRY_CN;
			print_file_dialog_menu.stop = DIALOG_STOP_CN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_CN;	
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_CN;
			print_file_dialog_menu.filament_no_press=DIALOG_FILAMENT_NO_PRESS_CN;

			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_CN;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_CN;
			

			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_CN;
			zoffset_menu.inc = ZOFFSET_INC_CN;
			zoffset_menu.dec = ZOFFSET_DEC_CN;
			break;
		#if 1
		case LANG_COMPLEX_CHINESE:
            MachinePara_menu.title = MACHINE_PARA_TITLE_T_CN;
            MachinePara_menu.MachineSetting = MACHINE_TYPE_CNOFIG_T_CN;
            MachinePara_menu.TemperatureSetting=TEMPERATURE_CONFIG_T_CN;
            MachinePara_menu.MotorSetting=MOTOR_CONFIG_T_CN;
            MachinePara_menu.AdvanceSetting=ADVANCE_CONFIG_T_CN;
					MachinePara_menu.Custom = CUSTOM_CONFIG_T_CN;
            machine_menu.default_value = DEFAULT_T_CN;
            machine_menu.next=NEXT_T_CN;
            machine_menu.previous=PREVIOUS_T_CN;
			machine_menu.back  = BACK_TEXT_T_CN;

            machine_menu.MachineConfigTitle = MACHINE_CONFIG_TITLE_T_CN;
            machine_menu.MachineType=MACHINE_TYPE_T_CN;
            machine_menu.Stroke=MACHINE_STROKE_T_CN;
            machine_menu.HomeDir=MACHINE_HOMEDIR_T_CN;
//            machine_menu.EndStopType=MACHINE_ENDSTOP_TYPE_T_CN;
            machine_menu.FilamentConf=MACHINE_FILAMENT_CONFIG_T_CN;
            machine_menu.LevelingConf=MACHINE_LEVELING_CONFIG_T_CN;
	machine_menu.BaudRateConf = MACHINE_BAUDRATE_CONFIG_T_CN;
	machine_menu.FirmwareType = MACHINE_FIRMWARE_CONFIG_T_CN;
	machine_menu.PausePosConf = MACHINE_PAUSEPOSI_CONFIG_T_CN;
	machine_menu.WifiConf = MACHINE_WIFI_CONFIG_T_CN;
            machine_menu.MachineTypeConfTitle = MACHINE_TYPE_CONFIG_TITLE_T_CN;
            machine_menu.xyz=MACHINE_TYPE_XYZ_T_CN;
            machine_menu.delta=MACHINE_TYPE_DELTA_T_CN;
            machine_menu.corexy=MACHINE_TYPE_COREXY_T_CN;
					machine_menu.normal= MACHINE_TYPE_NORMAL_T_CN;
            
    machine_menu.FirmwareTypeConfTitle = FIRMWARE_TYPE_CONFIG_TITLE_T_CN;

    machine_menu.BaudRateConfTitle = MACHINE_BAUDRATE_CONFIG_T_CN;


	machine_menu.wifiConfTile = WIFI_CONFIG_TILE_T_CN;
	machine_menu.WifiKey	  = WIFI_KEY_SET_T_CN;
	machine_menu.WifiMode	  = WIFI_MODE_SEL_T_CN;
	machine_menu.cloudEnable  = WIFI_CLOUD_ENABLE_T_CN;
	machine_menu.cloudHost 	  = WIFI_CLOUD_ADDR_T_CN;
	machine_menu.cloudPort    = WIFI_CLOUD_PORT_T_CN;
	machine_menu.WifiMode0	  = WIFI_MODE0_T_CN;
	machine_menu.WifiMode1	  = WIFI_MODE1_T_CN;
	machine_menu.WifiName	  = WIFI_NAME_SET_T_CN;
//			keyboard_menu.send = TEXT_SEND_T_CN; 
//				keyboard_menu.apply=KEY_CONFIRM_T_CN;
          //  machine_menu.StrokeConfTitle=MACHINE_STROKE_CONF_TITLE_T_CN;
          //  machine_menu.xStroke=X_MAX_LENGTH_T_CN;
          //  machine_menu.yStroke=Y_MAX_LENGTH_T_CN;
          //  machine_menu.zStroke=Z_MAX_LENGTH_T_CN;
			
	    machine_menu.xmin=X_MIN_LENGTH_T_CN;
	    machine_menu.ymin=Y_MIN_LENGTH_T_CN;
	    machine_menu.zmin=Z_MIN_LENGTH_T_CN;

            machine_menu.HomeDirConfTitle=HOME_DIR_CONF_TITLE_T_CN;
            machine_menu.xHomeDir=HOME_DIR_X_T_CN;
            machine_menu.yHomeDir=HOME_DIR_Y_T_CN;
            machine_menu.zHomeDir=HOME_DIR_Z_T_CN;
            machine_menu.min=HOME_MIN_T_CN;
            machine_menu.max=HOME_MAX_T_CN;

			machine_menu.PositionPuaseConfTitle=PAUSE_POSITION_CONF_TITLE_T_CN;
			machine_menu.xPosition=POSITION_X_T_CN;
			machine_menu.yPosition=POSITION_Y_T_CN;
			machine_menu.zPosition=POSITION_Z_T_CN;
            machine_menu.EndstopConfTitle=ENDSTOP_CONF_TITLE_T_CN;
//            machine_menu.xEndstop_min=MIN_ENDSTOP_X_T_CN;
//            machine_menu.yEndstop_min=MIN_ENDSTOP_Y_T_CN;
//            machine_menu.zEndstop_min=MIN_ENDSTOP_Z_T_CN;
//            machine_menu.xEndstop_max=MAX_ENDSTOP_X_T_CN;
//            machine_menu.yEndstop_max=MAX_ENDSTOP_Y_T_CN;
//            machine_menu.zEndstop_max=MAX_ENDSTOP_Z_T_CN;            
            machine_menu.FilamentEndstop=ENDSTOP_FIL_T_CN;
            machine_menu.LevelingEndstop=ENDSTOP_LEVEL_T_CN;
            machine_menu.opened=ENDSTOP_OPENED_T_CN;
            machine_menu.closed=ENDSTOP_CLOSED_T_CN;

            machine_menu.FilamentConfTitle=FILAMENT_CONF_TITLE_T_CN;
            machine_menu.InTemperature=FILAMENT_IN_TEMPERATURE_T_CN;
            machine_menu.InLength=FILAMENT_IN_LENGTH_T_CN;
            machine_menu.InSpeed=FILAMENT_IN_SPEED_T_CN;
            machine_menu.OutTemperature=FILAMENT_OUT_TEMPERATURE_T_CN;
            machine_menu.OutLength=FILAMENT_OUT_LENGTH_T_CN;
            machine_menu.OutSpeed=FILAMENT_OUT_SPEED_T_CN;
                        
            machine_menu.LevelingParaConfTitle=LEVELING_CONF_TITLE_T_CN;
            machine_menu.LevelingParaConf=LEVELING_PARA_CONF_T_CN;
            machine_menu.DeltaLevelConf=LEVELING_DELTA_T_CN;
            machine_menu.XYZLevelconf=LEVELING_XYZ_T_CN;

            machine_menu.LevelingSubConfTitle=LEVELING_PARA_CONF_TITLE_T_CN;
            machine_menu.AutoLevelEnable=AUTO_LEVELING_ENABLE_T_CN;
//            machine_menu.BLtouchEnable=BLTOUCH_LEVELING_ENABLE_T_CN;
            machine_menu.ProbePort=PROBE_PORT_T_CN;
            machine_menu.ProbeXoffset=PROBE_X_OFFSET_T_CN;
            machine_menu.ProbeYoffset=PROBE_Y_OFFSET_T_CN;
            machine_menu.ProbeZoffset=PROBE_Z_OFFSET_T_CN;
            machine_menu.ProbeXYspeed=PROBE_XY_SPEED_T_CN;
            machine_menu.ProbeZspeed=PROBE_Z_SPEED_T_CN;
            machine_menu.enable = ENABLE_T_CN;
            machine_menu.disable = DISABLE_T_CN;
            machine_menu.z_min = Z_MIN_T_CN;
            machine_menu.z_max = Z_MAX_T_CN;
					machine_menu.high_level = LEVEL_HIGH_T_CN;
					machine_menu.low_level = LEVEL_LOW_T_CN;
					machine_menu.pwr_saveMode = OFF_SAVE_MODE_T_CN;
					machine_menu.pwr_saveMode1 = OFF_SAVE_MODE1_T_CN;
					machine_menu.pwr_saveMode2 = OFF_SAVE_MODE2_T_CN;
					machine_menu.disable_PB0_PB1 = DISABLE_PB1_PB0_CONF_T_CN;
					machine_menu.level_PB0 = LEVEL_PB0_CONF_T_CN;
					machine_menu.level_PB1 = LEVEL_PB1_CONF_T_CN;
					machine_menu.z_error = BREAKPOINT_Z_ERROR_T_CN;
            	
			machine_menu.leveling_z_speed = LEVELING_Z_SPEED_T_CN;
			machine_menu.leveling_xy_speed = LEVELING_XY_SPEED_T_CN;
			machine_menu.leveling_z_high = LEVELING_Z_HIGH_T_CN;

            machine_menu.LevelingSubDeltaConfTitle=DELTA_LEVEL_CONF_TITLE_T_CN;
            machine_menu.MachineRadius=DELTA_MACHINE_RADIUS_T_CN;
            machine_menu.DiagonalRod=DELTA_DIAGONAL_ROD_T_CN;
            machine_menu.PrintableRadius=DELTA_PRINT_RADIUS_T_CN;
            machine_menu.DeltaHeight=DELTA_HEIGHT_T_CN;
            machine_menu.SmoothRodOffset=SMOOTH_ROD_OFFSET_T_CN;
            machine_menu.EffectorOffset=EFFECTOR_OFFSET_T_CN;
            machine_menu.CalibrationRadius=CALIBRATION_RADIUS_T_CN;

            machine_menu.LevelingSubXYZConfTitle=XYZ_LEVEL_CONF_TITLE_T_CN;
            //machine_menu.ProbeMaxLeft=PROBE_REACH_MAX_LEFT_T_CN;
            //machine_menu.ProbeMaxRigh=PROBE_REACH_MAX_RIGHT_T_CN;
            //machine_menu.ProbeMaxfront=PROBE_REACH_MAX_FRONT_T_CN;
            //machine_menu.ProbeMaxback=PROBE_REACH_MAX_BACK_T_CN;

            machine_menu.TemperatureConfTitle=TEMPERATURE_CONF_TITLE_T_CN;
            machine_menu.NozzleConf=NOZZLE_CONF_T_CN;
            machine_menu.HotBedConf=HOTBED_CONF_T_CN;
			machine_menu.PreheatTemperConf=PREHEAT_TEMPER_T_CN;

            machine_menu.NozzleConfTitle=NOZZLE_CONF_TITLE_T_CN;
            machine_menu.NozzleCnt=NOZZLECNT_T_CN;
            machine_menu.NozzleType=NOZZLE_TYPE_T_CN;
            machine_menu.NozzleAdjustType=NOZZLE_ADJUST_TYPE_T_CN;
            machine_menu.NozzleMinTemperature=NOZZLE_MIN_TEMPERATURE_T_CN;
            machine_menu.NozzleMaxTemperature=NOZZLE_MAX_TEMPERATURE_T_CN;
			machine_menu.Extrude_Min_Temper=EXTRUD_MIN_TEMPER_T_CN;

	     machine_menu.HotbedEnable=HOTBED_ENABLE_T_CN;
            machine_menu.HotbedConfTitle=HOTBED_CONF_TITLE_T_CN;
            machine_menu.HotbedAjustType=HOTBED_ADJUST_T_CN;
            machine_menu.HotbedMinTemperature=HOTBED_MIN_TEMPERATURE_T_CN;
            machine_menu.HotbedMaxTemperature=HOTBED_MAX_TEMPERATURE_T_CN;

            machine_menu.MotorConfTitle=MOTOR_CONF_TITLE_T_CN;
            machine_menu.MaxFeedRateConf=MAXFEEDRATE_CONF_T_CN;
            machine_menu.AccelerationConf=ACCELERATION_CONF_T_CN;
            machine_menu.JerkConf=JERKCONF_T_CN;
            machine_menu.StepsConf=STEPSCONF_T_CN;
            machine_menu.MotorDirConf=MOTORDIRCONF_T_CN;
            machine_menu.HomeFeedRateConf=HOMEFEEDRATECONF_T_CN;
		    machine_menu.CurrentConf=CURRENTCONF_T_CN;	
		    machine_menu.GetInfo = GETEEPROM_T_CN;
		    machine_menu.SaveInfo =SAVETOEEPROM_T_CN;
		    machine_menu.TMCBumpSen = TMCBUMPCONF_T_CN;

		    machine_menu.TMCBumpTitle=TMC_CONF_TITLE_T_CN;
		    machine_menu.X_Sensivisity=X_SENSITIVITY_T_CN;
		    machine_menu.Y_Sensivisity=Y_SENSITIVITY_T_CN;
		    machine_menu.Z_Sensivisity=Z_SENSITIVITY_T_CN;
            machine_menu.MaxFeedRateConfTitle=MAXFEEDRATE_CONF_TITLE_T_CN;
            machine_menu.XMaxFeedRate=X_MAXFEEDRATE_T_CN;
            machine_menu.YMaxFeedRate=Y_MAXFEEDRATE_T_CN;
            machine_menu.ZMaxFeedRate=Z_MAXFEEDRATE_T_CN;
            machine_menu.E0MaxFeedRate=E0_MAXFEEDRATE_T_CN;
            machine_menu.E1MaxFeedRate=E1_MAXFEEDRATE_T_CN;

            machine_menu.AccelerationConfTitle=ACCELERATION_CONF_TITLE_T_CN;
            machine_menu.PrintAcceleration=PRINT_ACCELERATION_T_CN;
            machine_menu.RetractAcceleration=RETRACT_ACCELERATION_T_CN;
            machine_menu.TravelAcceleration=TRAVEL_ACCELERATION_T_CN;
            machine_menu.X_Acceleration=X_ACCELERATION_T_CN;
            machine_menu.Y_Acceleration=Y_ACCELERATION_T_CN;
            machine_menu.Z_Acceleration=Z_ACCELERATION_T_CN;
            machine_menu.E0_Acceleration=E0_ACCELERATION_T_CN;
            machine_menu.E1_Acceleration=E1_ACCELERATION_T_CN;

            machine_menu.JerkConfTitle=JERK_CONF_TITLE_T_CN;
            machine_menu.X_Jerk=X_JERK_T_CN;
            machine_menu.Y_Jerk=Y_JERK_T_CN;
            machine_menu.Z_Jerk=Z_JERK_T_CN;
            machine_menu.E_Jerk=E_JERK_T_CN;

            machine_menu.StepsConfTitle=STEPS_CONF_TITLE_T_CN;
            machine_menu.X_Steps=X_STEPS_T_CN;
            machine_menu.Y_Steps=Y_STEPS_T_CN;
            machine_menu.Z_Steps=Z_STEPS_T_CN;
            machine_menu.E0_Steps=E0_STEPS_T_CN;
            machine_menu.E1_Steps=E1_STEPS_T_CN;
            
		    machine_menu.CurrentConfTitle=CURRENT_CONF_TITLE_T_CN;
		    machine_menu.X_Current=X_CURRENT_T_CN;
		    machine_menu.Y_Current=Y_CURRENT_T_CN;
		    machine_menu.Z_Current=Z_CURRENT_T_CN;
		    machine_menu.E0_Current=E0_CURRENT_T_CN;
		    machine_menu.E1_Current=E1_CURRENT_T_CN;	
            machine_menu.MotorDirConfTitle=MOTORDIR_CONF_TITLE_T_CN;
            machine_menu.X_MotorDir=X_MOTORDIR_T_CN;
            machine_menu.Y_MotorDir=Y_MOTORDIR_T_CN;
            machine_menu.Z_MotorDir=Z_MOTORDIR_T_CN;
            machine_menu.E0_MotorDir=E0_MOTORDIR_T_CN;
            machine_menu.E1_MotorDir=E1_MOTORDIR_T_CN;
            machine_menu.Invert_0=INVERT_P_T_CN;
            machine_menu.Invert_1=INVERT_N_T_CN;

            machine_menu.HomeFeedRateConfTitle=HOMEFEEDRATE_CONF_TITLE_T_CN;
            machine_menu.XY_HomeFeedRate=X_HOMESPEED_T_CN;
            //machine_menu.Y_HomeFeedRate=Y_HOMESPEED_T_CN;
            machine_menu.Z_HomeFeedRate=Z_HOMESPEED_T_CN;
          
            machine_menu.AdvancedConfTitle=ADVANCED_CONF_TITLE_T_CN;
            machine_menu.PwrOffDection=PWROFF_DECTION_T_CN;
            machine_menu.PwrOffAfterPrint=PWROFF_AFTER_PRINT_T_CN;
            machine_menu.HaveUps=HAVE_UPS_T_CN;
            machine_menu.Z2andZ2Endstop=Z2_AND_Z2ENDSTOP_CONF_T_CN;
            machine_menu.EnablePinsInvert=ENABLE_PINS_CONF_T_CN;

            machine_menu.Z2ConfTitle=Z2_AND_Z2ENDSTOP_CONF_TITLE_T_CN;
//            machine_menu.Z2Enable=Z2_ENABLE_T_CN;
//            machine_menu.Z2EndstopEnable=Z2_ENDSTOP_T_CN;
            machine_menu.Z2Port=Z2_PORT_T_CN;

            machine_menu.EnablePinsInvertTitle=ENABLE_PINS_CONF_TITLE_T_CN;
//            machine_menu.XInvert=X_ENABLE_PINS_INVERT_T_CN;
//            machine_menu.YInvert=Y_ENABLE_PINS_INVERT_T_CN;
//            machine_menu.ZInvert=Z_ENABLE_PINS_INVERT_T_CN;
//            machine_menu.EInvert=E_ENABLE_PINS_INVERT_T_CN;

            machine_menu.key_back = KEY_BACK_T_CN;
            machine_menu.key_rest = KEY_REST_T_CN;
            machine_menu.key_confirm = KEY_CONFIRM_T_CN;
  		  set_menu.machine_para = MACHINE_PARA_T_CN;
//					machine_menu.high_level = MOTOR_T_CN_HIGH_LEVEL_T_CN;
//					machine_menu.low_level = MOTOR_T_CN_LOW_LEVEL_T_CN;
	machine_menu.CustomConfTitle = CUSTOMCONF_TITLE_T_CN;
	machine_menu.display		 = DISPLAY_CONF_T_CN;
	machine_menu.button 		 = BUTTON_CONF_T_CN;
	
	machine_menu.DisplayConfTitle = DISPLAY_TITLE_T_CN;
	machine_menu.btn_3D_ecffects = BUTTON_3D_T_CN;
	machine_menu.btn_text_offset = BTN_TEXT_OFFSET_T_CN;
	machine_menu.screen_overturn = SCREEN_OVERTURN_T_CN;
	machine_menu.display_mode =    DISPLAY_MODE_T_CN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_T_CN;
	machine_menu.babastepting = ENABLE_BABASTEPTING_T_CN;
	machine_menu.simple_theme	= SIMPLETHEME_T_CN;
	machine_menu.classic_theme	= CLASSICTHEME_T_CN;
	//
	machine_menu.buttonConfTitle = BUTTON_TITLE_T_CN;
	machine_menu.function_btn1_display = DISPLAY_FUNCTIONBTN1_T_CN;
	machine_menu.function_btn1_cmd = FUNCTION_BTN1_TEXT_T_CN;
	machine_menu.quickStop_btn = DISPLAY_QUICKSTOP_T_CN;
	machine_menu.zoffset_btn_display = DISPLAY_ZOFFSET_T_CN;
	machine_menu.displayCalibrate =  DISPLAY_CALIBRATE_T_CN ;				
	machine_menu.print_more_btn  = PRINT_MORE_BTN_TITLE_T_CN;
	machine_menu.more_btn		 = MORE_BTN_TITLE_T_CN;
	machine_menu.MoreButtonConfTitle = MORE_BTN_TITLE_T_CN;
	machine_menu.moreItem_cnt = BUTTON_COUNT_T_CN;
	machine_menu.moreItem_btn1 = BUTTON1_NAME_T_CN;
	machine_menu.moreItem_btn2 = BUTTON2_NAME_T_CN;
	machine_menu.moreItem_btn3 = BUTTON3_NAME_T_CN;			
	machine_menu.moreItem_btn4 = BUTTON4_NAME_T_CN;
	machine_menu.moreItem_btn5 = BUTTON5_NAME_T_CN;
	machine_menu.moreItem_btn6 = BUTTON6_NAME_T_CN;
	machine_menu.moreItem_btn7 = BUTTON7_NAME_T_CN;
	
	machine_menu.MoreFunctionConfTitle = PRINT_MORE_BTN_TITLE_T_CN;
	machine_menu.morefunc_cnt = BUTTON_COUNT_T_CN;
	machine_menu.moreItem_func1 = BUTTON1_NAME_T_CN;
	machine_menu.moreItem_func2 = BUTTON2_NAME_T_CN;
	machine_menu.moreItem_func3 = BUTTON3_NAME_T_CN;			 
	machine_menu.moreItem_func4 = BUTTON4_NAME_T_CN;
	machine_menu.moreItem_func5 = BUTTON5_NAME_T_CN;
	machine_menu.moreItem_func6 = BUTTON6_NAME_T_CN;
	machine_menu.moreItem_func7 = BUTTON7_NAME_T_CN;

	machine_menu.AutoLevelCmd = AUTOLEVELCMD_T_CN;
		machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_T_CN;
		machine_menu.low_level = MOTOR_EN_LOW_LEVEL_T_CN;
        //

            
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_T_CN;
			common_menu.text_back=BACK_TEXT_T_CN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_T_CN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_T_CN;
			common_menu.print_special_title = PRINTING_GBK;
			common_menu.pause_special_title = PRINTING_PAUSE_GBK;
			common_menu.operate_special_title = PRINTING_OPERATION_GBK;			
			//主页面
			main_menu.title=TITLE_READYPRINT_T_CN;
			main_menu.preheat=PREHEAT_TEXT_T_CN;
			main_menu.move=MOVE_TEXT_T_CN;
			main_menu.home=HOME_TEXT_T_CN;
			main_menu.print=PRINT_TEXT_T_CN;
			main_menu.extrude=EXTRUDE_TEXT_T_CN;
			main_menu.leveling=LEVELING_TEXT_T_CN;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_T_CN;
			main_menu.fan = FAN_TEXT_T_CN;
			main_menu.set=SET_TEXT_T_CN;
			main_menu.more=MORE_TEXT_T_CN;
			main_menu.tool = TOOL_TEXT_T_CN;
			//TOOL
			tool_menu.title = TOOL_TEXT_T_CN;
			tool_menu.preheat = TOOL_PREHEAT_T_CN;
			tool_menu.extrude = TOOL_EXTRUDE_T_CN;
			tool_menu.move = TOOL_MOVE_T_CN;
			tool_menu.home= TOOL_HOME_T_CN;
			tool_menu.leveling = TOOL_LEVELING_T_CN;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_T_CN;
			tool_menu.filament = TOOL_FILAMENT_T_CN;
			tool_menu.more = TOOL_MORE_T_CN;			
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_T_CN;
			preheat_menu.title=TITLE_PREHEAT_T_CN;
			preheat_menu.add=ADD_TEXT_T_CN;
			preheat_menu.dec=DEC_TEXT_T_CN;
			preheat_menu.ext1=EXTRUDER_1_TEXT_T_CN;
			preheat_menu.ext2=EXTRUDER_2_TEXT_T_CN;
			preheat_menu.hotbed=HEATBED_TEXT_T_CN;
			preheat_menu.off=CLOSE_TEXT_T_CN;
			//移动
			move_menu.title = MOVE_TEXT_T_CN;
			more_menu.zoffset = ZOFFSET_T_CN;
			more_menu.calibrate = CALIBRATE_T_CN;
			//归零
			home_menu.title=TITLE_HOME_T_CN;
			home_menu.stopmove = HOME_STOPMOVE_T_CN;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_T_CN;
			file_menu.page_up=PAGE_UP_TEXT_T_CN;
			file_menu.page_down=PAGE_DOWN_TEXT_T_CN;
			file_menu.file_loading = FILE_LOADING_T_CN;
			file_menu.no_file = NO_FILE_T_CN;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_T_CN;//NO_FILE_AND_CHECK_T_CN;
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_T_CN;
			extrude_menu.in=EXTRUDER_IN_TEXT_T_CN;
			extrude_menu.out=EXTRUDER_OUT_TEXT_T_CN;
			extrude_menu.ext1=EXTRUDER_1_TEXT_T_CN;
			extrude_menu.ext2=EXTRUDER_2_TEXT_T_CN;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_T_CN;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_T_CN;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_T_CN;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_T_CN;
			//调平
			leveling_menu.title=TITLE_LEVELING_CN;
			leveling_menu.position1=LEVELING_POINT1_TEXT_T_CN;
			leveling_menu.position2=LEVELING_POINT2_TEXT_T_CN;
			leveling_menu.position3=LEVELING_POINT3_TEXT_T_CN;
			leveling_menu.position4=LEVELING_POINT4_TEXT_T_CN;
			leveling_menu.position5=LEVELING_POINT5_TEXT_T_CN;
			leveling_menu.count = LEVELING_POINTS_TEXT_T_CN;
			//设置
			set_menu.title=TITLE_SET_T_CN;
			set_menu.filesys=FILESYS_TEXT_T_CN;
			set_menu.wifi=WIFI_TEXT_T_CN;
			set_menu.about=ABOUT_TEXT_T_CN;
			set_menu.fan=FAN_TEXT_T_CN;
			set_menu.filament=FILAMENT_TEXT_T_CN;
			set_menu.breakpoint=BREAK_POINT_TEXT_T_CN;
			set_menu.motoroff=MOTOR_OFF_TEXT_T_CN;
			set_menu.language=LANGUAGE_TEXT_T_CN;
            set_menu.machine_para = MACHINE_PARA_T_CN;//
			//????
			filesys_menu.title = TITLE_FILESYS_T_CN;
			filesys_menu.sd_sys = SD_CARD_TEXT_T_CN;
			filesys_menu.usb_sys = U_DISK_TEXT_T_CN;
			//更多
			more_menu.title = TITLE_MORE_T_CN;
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_CN;
			//wifi_menu.ip = WIFI_IP_TEXT_CN;
			//wifi_menu.state= WIFI_STA_TEXT_CN;
			wifi_menu.cloud= CLOUD_TEXT_T_CN;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_T_CN;
			//CLOUD
			cloud_menu.title = TITLE_CLOUD_TEXT_T_CN;
			cloud_menu.bind = CLOUD_BINDED_T_CN;
			cloud_menu.binded = CLOUD_BINDED_T_CN;
			cloud_menu.unbind = CLOUD_UNBIND_T_CN;
			cloud_menu.unbinding = CLOUD_UNBINDED_T_CN;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_T_CN;
			cloud_menu.disable = CLOUD_DISABLE_T_CN;
			//关于
			about_menu.title = ABOUT_TEXT_T_CN;
			about_menu.type = ABOUT_TYPE_TEXT_T_CN;
			about_menu.version = ABOUT_VERSION_TEXT_T_CN;
			about_menu.wifi = ABOUT_WIFI_TEXT_T_CN;

			//风扇
			fan_menu.title = FAN_TEXT_T_CN;
			fan_menu.add = FAN_ADD_TEXT_T_CN;
			fan_menu.dec = FAN_DEC_TEXT_T_CN;
			fan_menu.state = FAN_TIPS1_TEXT_T_CN;
			//换料
			filament_menu.title = TITLE_FILAMENT_T_CN;
			filament_menu.in = FILAMENT_IN_TEXT_T_CN;
			filament_menu.out = FILAMENT_OUT_TEXT_T_CN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_T_CN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_T_CN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_T_CN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_T_CN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_T_CN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_T_CN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_T_CN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_T_CN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_T_CN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_T_CN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_T_CN;


			//语言
			language_menu.title = TITLE_LANGUAGE_T_CN;
			language_menu.next = PAGE_DOWN_TEXT_T_CN;
			language_menu.up = PAGE_UP_TEXT_T_CN;
			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_T_CN;
			printing_menu.option = PRINTING_OPERATION_T_CN;
			printing_menu.stop = PRINTING_STOP_T_CN;
			printing_menu.pause = PRINTING_PAUSE_T_CN;
			printing_menu.resume = PRINTING_RESUME_T_CN;

			//操作界面
			operation_menu.title = TITLE_OPERATION_T_CN;
			operation_menu.pause = PRINTING_PAUSE_T_CN;
			operation_menu.stop = PRINTING_STOP_T_CN;
			operation_menu.temp = PRINTING_TEMP_T_CN;
			operation_menu.fan = FAN_TEXT_T_CN;
			operation_menu.extr = PRINTING_EXTRUDER_T_CN;
			operation_menu.speed = PRINTING_CHANGESPEED_T_CN;			
			operation_menu.filament= FILAMENT_TEXT_T_CN;
			operation_menu.more = PRINTING_MORE_T_CN;
			operation_menu.move = PRINTING_MOVE_T_CN;
			operation_menu.auto_off = AUTO_SHUTDOWN_T_CN;
			operation_menu.manual_off = MANUAL_SHUTDOWN_T_CN;			
			//暂停界面
			pause_menu.title= TITLE_PAUSE_T_CN;
			pause_menu.resume = PRINTING_RESUME_T_CN;
			pause_menu.stop = PRINTING_STOP_T_CN;
			pause_menu.extrude = PRINTING_EXTRUDER_T_CN;
			pause_menu.move = PRINTING_MOVE_T_CN;
			pause_menu.filament= FILAMENT_TEXT_T_CN;
			pause_menu.more = PRINTING_MORE_T_CN;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_T_CN;
			speed_menu.add = ADD_TEXT_T_CN;
			speed_menu.dec = DEC_TEXT_T_CN;
			speed_menu.move = MOVE_SPEED_T_CN;
			speed_menu.extrude = EXTRUDER_SPEED_T_CN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_T_CN;
			speed_menu.move_speed = MOVE_SPEED_STATE_T_CN;
			//打印中---更多界面
			printing_more_menu.title = TITLE_MORE_T_CN;
			printing_more_menu.fan = FAN_TEXT_T_CN;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_T_CN;
			printing_more_menu.manual = MANUAL_SHUTDOWN_T_CN;
			printing_more_menu.speed = PRINTING_CHANGESPEED_T_CN;
			printing_more_menu.temp = PRINTING_TEMP_T_CN;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_CN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_T_CN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_T_CN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_T_CN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_T_CN;
			print_file_dialog_menu.retry = DIALOG_RETRY_T_CN;
			print_file_dialog_menu.stop = DIALOG_STOP_T_CN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_T_CN;		
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_T_CN;
			print_file_dialog_menu.filament_no_press=DIALOG_FILAMENT_NO_PRESS_T_CN;

			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_T_CN;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_T_CN;
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_T_CN;
			zoffset_menu.inc = ZOFFSET_INC_T_CN;
			zoffset_menu.dec = ZOFFSET_DEC_T_CN;			
			break;
		case LANG_ENGLISH:
            //????
                    MachinePara_menu.title = MACHINE_PARA_TITLE_EN;
                    MachinePara_menu.MachineSetting = MACHINE_TYPE_CNOFIG_EN;
                    MachinePara_menu.TemperatureSetting=TEMPERATURE_CONFIG_EN;
                    MachinePara_menu.MotorSetting=MOTOR_CONFIG_EN;
                    MachinePara_menu.AdvanceSetting=ADVANCE_CONFIG_EN;
					MachinePara_menu.Custom = CUSTOM_CONFIG_EN;
					MachinePara_menu.Console = CONSOLE_EN;
            
                    machine_menu.default_value = DEFAULT_EN;
                    machine_menu.next=NEXT_EN;
                    machine_menu.previous=PREVIOUS_EN;
            
                    machine_menu.MachineConfigTitle = MACHINE_CONFIG_TITLE_EN;
                    machine_menu.MachineType=MACHINE_TYPE_EN;
                    machine_menu.Stroke=MACHINE_STROKE_EN;
                    machine_menu.HomeDir=MACHINE_HOMEDIR_EN;
                    machine_menu.EndStopType=MACHINE_ENDSTOP_TYPE_EN;
                    machine_menu.FilamentConf=MACHINE_FILAMENT_CONFIG_EN;
                    machine_menu.LevelingConf=MACHINE_LEVELING_CONFIG_EN;
	machine_menu.BaudRateConf = MACHINE_BAUDRATE_CONFIG_EN;
	machine_menu.FirmwareType = MACHINE_FIRMWARE_CONFIG_EN;
	machine_menu.PausePosConf = MACHINE_PAUSEPOSI_CONFIG_EN;
	machine_menu.WifiConf = MACHINE_WIFI_CONFIG_EN;
                    machine_menu.MachineTypeConfTitle = MACHINE_TYPE_CONFIG_TITLE_EN;
                    machine_menu.xyz=MACHINE_TYPE_XYZ_EN;
                    machine_menu.delta=MACHINE_TYPE_DELTA_EN;
                    machine_menu.corexy=MACHINE_TYPE_COREXY_EN;
					machine_menu.normal= MACHINE_TYPE_NORMAL_EN;
            
    machine_menu.FirmwareTypeConfTitle = FIRMWARE_TYPE_CONFIG_TITLE_EN;
    machine_menu.marlin=FIRMWARE_TYPE_MARLIN_EN;
    machine_menu.repetier=FIRMWARE_TYPE_REPETIER_EN;
    machine_menu.smoothie=FIRMWARE_TYPE_SMOOTHIE_EN;

    machine_menu.BaudRateConfTitle = BAUD_RATE_CONFIG_TITLE_EN;
    machine_menu.rate1=BAUD_RATE_9600_EN;
    machine_menu.rate2=BAUD_RATE_57600_EN;
    machine_menu.rate3=BAUD_RATE_115200_EN;
	machine_menu.rate4=BAUD_RATE_250000_EN;

	machine_menu.wifiConfTile = WIFI_CONFIG_TILE_EN;
	machine_menu.WifiKey	  = WIFI_KEY_SET_EN;
	machine_menu.WifiMode	  = WIFI_MODE_SEL_EN;
	machine_menu.cloudEnable  = WIFI_CLOUD_ENABLE_EN;
	machine_menu.cloudHost 	  = WIFI_CLOUD_ADDR_EN;
	machine_menu.cloudPort    = WIFI_CLOUD_PORT_EN;
	machine_menu.WifiMode0	  = WIFI_MODE0_EN;
	machine_menu.WifiMode1	  = WIFI_MODE1_EN;
	machine_menu.WifiName	  = WIFI_NAME_SET_EN;
                    machine_menu.StrokeConfTitle=MACHINE_STROKE_CONF_TITLE_EN;
                    machine_menu.xStroke=X_MAX_LENGTH_EN;
                    machine_menu.yStroke=Y_MAX_LENGTH_EN;
                    machine_menu.zStroke=Z_MAX_LENGTH_EN;

			machine_menu.xmin=X_MIN_LENGTH_EN;
		       machine_menu.ymin=Y_MIN_LENGTH_EN;
		       machine_menu.zmin=Z_MIN_LENGTH_EN;		
            
                    machine_menu.HomeDirConfTitle=HOME_DIR_CONF_TITLE_EN;
                    machine_menu.xHomeDir=HOME_DIR_X_EN;
                    machine_menu.yHomeDir=HOME_DIR_Y_EN;
                    machine_menu.zHomeDir=HOME_DIR_Z_EN;
                    machine_menu.min=HOME_MIN_EN;
                    machine_menu.max=HOME_MAX_EN;
            
			machine_menu.PositionPuaseConfTitle=PAUSE_POSITION_CONF_TITLE_EN;
			machine_menu.xPosition=POSITION_X_EN;
			machine_menu.yPosition=POSITION_Y_EN;
			machine_menu.zPosition=POSITION_Z_EN;
                    machine_menu.EndstopConfTitle=ENDSTOP_CONF_TITLE_EN;
                    machine_menu.xEndstop_min=MIN_ENDSTOP_X_EN;
                    machine_menu.yEndstop_min=MIN_ENDSTOP_Y_EN;
                    machine_menu.zEndstop_min=MIN_ENDSTOP_Z_EN;
                    machine_menu.xEndstop_max=MAX_ENDSTOP_X_EN;
                    machine_menu.yEndstop_max=MAX_ENDSTOP_Y_EN;
                    machine_menu.zEndstop_max=MAX_ENDSTOP_Z_EN;            
                    machine_menu.FilamentEndstop=ENDSTOP_FIL_EN;
                    machine_menu.LevelingEndstop=ENDSTOP_LEVEL_EN;
                    machine_menu.opened=ENDSTOP_OPENED_EN;
                    machine_menu.closed=ENDSTOP_CLOSED_EN;
            
                    machine_menu.FilamentConfTitle=FILAMENT_CONF_TITLE_EN;
                    machine_menu.InTemperature=FILAMENT_IN_TEMPERATURE_EN;
                    machine_menu.InLength=FILAMENT_IN_LENGTH_EN;
                    machine_menu.InSpeed=FILAMENT_IN_SPEED_EN;
                    machine_menu.OutTemperature=FILAMENT_OUT_TEMPERATURE_EN;
                    machine_menu.OutLength=FILAMENT_OUT_LENGTH_EN;
                    machine_menu.OutSpeed=FILAMENT_OUT_SPEED_EN;
                                
                    machine_menu.LevelingParaConfTitle=LEVELING_CONF_TITLE_EN;
                    machine_menu.LevelingParaConf=LEVELING_PARA_CONF_EN;
                    machine_menu.DeltaLevelConf=LEVELING_DELTA_EN;
                    machine_menu.XYZLevelconf=LEVELING_XYZ_EN;
            
                    machine_menu.LevelingSubConfTitle=LEVELING_PARA_CONF_TITLE_EN;
                    machine_menu.AutoLevelEnable=AUTO_LEVELING_ENABLE_EN;
                    machine_menu.BLtouchEnable=BLTOUCH_LEVELING_ENABLE_EN;
                    machine_menu.ProbePort=PROBE_PORT_EN;
                    machine_menu.ProbeXoffset=PROBE_X_OFFSET_EN;
                    machine_menu.ProbeYoffset=PROBE_Y_OFFSET_EN;
                    machine_menu.ProbeZoffset=PROBE_Z_OFFSET_EN;
                    machine_menu.ProbeXYspeed=PROBE_XY_SPEED_EN;
                    machine_menu.ProbeZspeed=PROBE_Z_SPEED_EN;
                    machine_menu.enable = ENABLE_EN;
                    machine_menu.disable = DISABLE_EN;
                    machine_menu.z_min = Z_MIN_EN;
                    machine_menu.z_max = Z_MAX_EN;
					machine_menu.high_level = LEVEL_HIGH_EN;
					machine_menu.low_level = LEVEL_LOW_EN;
					machine_menu.pwr_saveMode = OFF_SAVE_MODE_EN;
					machine_menu.pwr_saveMode1 = OFF_SAVE_MODE1_EN;
					machine_menu.pwr_saveMode2 = OFF_SAVE_MODE2_EN;
					machine_menu.disable_PB0_PB1 = DISABLE_PB1_PB0_CONF_EN;
					machine_menu.level_PB0 = LEVEL_PB0_CONF_EN;
					machine_menu.level_PB1 = LEVEL_PB1_CONF_EN;
					machine_menu.z_error = BREAKPOINT_Z_ERROR_EN;
            	
			machine_menu.leveling_z_speed = LEVELING_Z_SPEED_EN;
			machine_menu.leveling_xy_speed = LEVELING_XY_SPEED_EN;
			machine_menu.leveling_z_high = LEVELING_Z_HIGH_EN;

                    machine_menu.LevelingSubDeltaConfTitle=DELTA_LEVEL_CONF_TITLE_EN;
                    machine_menu.MachineRadius=DELTA_MACHINE_RADIUS_EN;
                    machine_menu.DiagonalRod=DELTA_DIAGONAL_ROD_EN;
                    machine_menu.PrintableRadius=DELTA_PRINT_RADIUS_EN;
                    machine_menu.DeltaHeight=DELTA_HEIGHT_EN;
                    machine_menu.SmoothRodOffset=SMOOTH_ROD_OFFSET_EN;
                    machine_menu.EffectorOffset=EFFECTOR_OFFSET_EN;
                    machine_menu.CalibrationRadius=CALIBRATION_RADIUS_EN;
            
                    machine_menu.LevelingSubXYZConfTitle=XYZ_LEVEL_CONF_TITLE_EN;
                    //machine_menu.ProbeMaxLeft=PROBE_REACH_MAX_LEFT_EN;
                    //machine_menu.ProbeMaxRigh=PROBE_REACH_MAX_RIGHT_EN;
                    //machine_menu.ProbeMaxfront=PROBE_REACH_MAX_FRONT_EN;
                    //machine_menu.ProbeMaxback=PROBE_REACH_MAX_BACK_EN;
            
                    machine_menu.TemperatureConfTitle=TEMPERATURE_CONF_TITLE_EN;
                    machine_menu.NozzleConf=NOZZLE_CONF_EN;
                    machine_menu.HotBedConf=HOTBED_CONF_EN;
                    machine_menu.PreheatTemperConf=PREHEAT_TEMPER_EN;
            
                    machine_menu.NozzleConfTitle=NOZZLE_CONF_TITLE_EN;
                    machine_menu.NozzleCnt=NOZZLECNT_EN;
                    machine_menu.NozzleType=NOZZLE_TYPE_EN;
                    machine_menu.NozzleAdjustType=NOZZLE_ADJUST_TYPE_EN;
                    machine_menu.NozzleMinTemperature=NOZZLE_MIN_TEMPERATURE_EN;
                    machine_menu.NozzleMaxTemperature=NOZZLE_MAX_TEMPERATURE_EN;
                    machine_menu.Extrude_Min_Temper=EXTRUD_MIN_TEMPER_EN;

		    machine_menu.HotbedEnable=HOTBED_ENABLE_EN;
                    machine_menu.HotbedConfTitle=HOTBED_CONF_TITLE_EN;
                    machine_menu.HotbedAjustType=HOTBED_ADJUST_EN;
                    machine_menu.HotbedMinTemperature=HOTBED_MIN_TEMPERATURE_EN;
                    machine_menu.HotbedMaxTemperature=HOTBED_MAX_TEMPERATURE_EN;
            
                    machine_menu.MotorConfTitle=MOTOR_CONF_TITLE_EN;
                    machine_menu.MaxFeedRateConf=MAXFEEDRATE_CONF_EN;
                    machine_menu.AccelerationConf=ACCELERATION_CONF_EN;
                    machine_menu.JerkConf=JERKCONF_EN;
                    machine_menu.StepsConf=STEPSCONF_EN;
                    machine_menu.MotorDirConf=MOTORDIRCONF_EN;
                    machine_menu.HomeFeedRateConf=HOMEFEEDRATECONF_EN;
		    machine_menu.CurrentConf=CURRENTCONF_EN;	
		    machine_menu.GetInfo = GETEEPROM_EN;
		    machine_menu.SaveInfo =SAVETOEEPROM_EN;
		    machine_menu.TMCBumpSen = TMCBUMPCONF_EN;

		    machine_menu.TMCBumpTitle=TMC_CONF_TITLE_EN;
		    machine_menu.X_Sensivisity=X_SENSITIVITY_EN;
		    machine_menu.Y_Sensivisity=Y_SENSITIVITY_EN;
		    machine_menu.Z_Sensivisity=Z_SENSITIVITY_EN;
                    machine_menu.MaxFeedRateConfTitle=MAXFEEDRATE_CONF_TITLE_EN;
                    machine_menu.XMaxFeedRate=X_MAXFEEDRATE_EN;
                    machine_menu.YMaxFeedRate=Y_MAXFEEDRATE_EN;
                    machine_menu.ZMaxFeedRate=Z_MAXFEEDRATE_EN;
                    machine_menu.E0MaxFeedRate=E0_MAXFEEDRATE_EN;
                    machine_menu.E1MaxFeedRate=E1_MAXFEEDRATE_EN;
            
                    machine_menu.AccelerationConfTitle=ACCELERATION_CONF_TITLE_EN;
                    machine_menu.PrintAcceleration=PRINT_ACCELERATION_EN;
                    machine_menu.RetractAcceleration=RETRACT_ACCELERATION_EN;
                    machine_menu.TravelAcceleration=TRAVEL_ACCELERATION_EN;
                    machine_menu.X_Acceleration=X_ACCELERATION_EN;
                    machine_menu.Y_Acceleration=Y_ACCELERATION_EN;
                    machine_menu.Z_Acceleration=Z_ACCELERATION_EN;
                    machine_menu.E0_Acceleration=E0_ACCELERATION_EN;
                    machine_menu.E1_Acceleration=E1_ACCELERATION_EN;
            
                    machine_menu.JerkConfTitle=JERK_CONF_TITLE_EN;
                    machine_menu.X_Jerk=X_JERK_EN;
                    machine_menu.Y_Jerk=Y_JERK_EN;
                    machine_menu.Z_Jerk=Z_JERK_EN;
                    machine_menu.E_Jerk=E_JERK_EN;
            
                    machine_menu.StepsConfTitle=STEPS_CONF_TITLE_EN;
                    machine_menu.X_Steps=X_STEPS_EN;
                    machine_menu.Y_Steps=Y_STEPS_EN;
                    machine_menu.Z_Steps=Z_STEPS_EN;
                    machine_menu.E0_Steps=E0_STEPS_EN;
                    machine_menu.E1_Steps=E1_STEPS_EN;
            
		    machine_menu.CurrentConfTitle=CURRENT_CONF_TITLE_EN;
		    machine_menu.X_Current=X_CURRENT_EN;
		    machine_menu.Y_Current=Y_CURRENT_EN;
		    machine_menu.Z_Current=Z_CURRENT_EN;
		    machine_menu.E0_Current=E0_CURRENT_EN;
		    machine_menu.E1_Current=E1_CURRENT_EN;	
                    machine_menu.MotorDirConfTitle=MOTORDIR_CONF_TITLE_EN;
                    machine_menu.X_MotorDir=X_MOTORDIR_EN;
                    machine_menu.Y_MotorDir=Y_MOTORDIR_EN;
                    machine_menu.Z_MotorDir=Z_MOTORDIR_EN;
                    machine_menu.E0_MotorDir=E0_MOTORDIR_EN;
                    machine_menu.E1_MotorDir=E1_MOTORDIR_EN;
                    machine_menu.Invert_0=INVERT_P_EN;
                    machine_menu.Invert_1=INVERT_N_EN;
            
                    machine_menu.HomeFeedRateConfTitle=HOMEFEEDRATE_CONF_TITLE_EN;
                    machine_menu.XY_HomeFeedRate=X_HOMESPEED_EN;
                    //machine_menu.Y_HomeFeedRate=Y_HOMESPEED_EN;
                    machine_menu.Z_HomeFeedRate=Z_HOMESPEED_EN;
            
                    machine_menu.AdvancedConfTitle=ADVANCED_CONF_TITLE_EN;
                    machine_menu.PwrOffDection=PWROFF_DECTION_EN;
                    machine_menu.PwrOffAfterPrint=PWROFF_AFTER_PRINT_EN;
                    machine_menu.HaveUps=HAVE_UPS_EN;
                    machine_menu.Z2andZ2Endstop=Z2_AND_Z2ENDSTOP_CONF_EN;
                    machine_menu.EnablePinsInvert=ENABLE_PINS_CONF_EN;
            
                    machine_menu.Z2ConfTitle=Z2_AND_Z2ENDSTOP_CONF_TITLE_EN;
                    machine_menu.Z2Enable=Z2_ENABLE_EN;
                    machine_menu.Z2EndstopEnable=Z2_ENDSTOP_EN;
                    machine_menu.Z2Port=Z2_PORT_EN;
            
                    machine_menu.EnablePinsInvertTitle=ENABLE_PINS_CONF_TITLE_EN;
                    machine_menu.XInvert=X_ENABLE_PINS_INVERT_EN;
                    machine_menu.YInvert=Y_ENABLE_PINS_INVERT_EN;
                    machine_menu.ZInvert=Z_ENABLE_PINS_INVERT_EN;
                    machine_menu.EInvert=E_ENABLE_PINS_INVERT_EN;
            
                    machine_menu.key_back = KEY_BACK_EN;
                    machine_menu.key_rest = KEY_REST_EN;
                    machine_menu.key_confirm = KEY_CONFIRM_EN;
  		  set_menu.machine_para = MACHINE_PARA_EN;
					machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_EN;
					machine_menu.low_level = MOTOR_EN_LOW_LEVEL_EN;
	machine_menu.CustomConfTitle = CUSTOMCONF_TITLE_EN;
	machine_menu.display		 = DISPLAY_CONF_EN;
	machine_menu.button 		 = BUTTON_CONF_EN;
	
	machine_menu.DisplayConfTitle = DISPLAY_TITLE_EN;
	machine_menu.btn_3D_ecffects = BUTTON_3D_EN;
	machine_menu.btn_text_offset = BTN_TEXT_OFFSET_EN;
	machine_menu.screen_overturn = SCREEN_OVERTURN_EN;
	machine_menu.display_mode =    DISPLAY_MODE_EN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_EN;
	machine_menu.simple_theme	= SIMPLETHEME_EN;
	machine_menu.classic_theme	= CLASSICTHEME_EN;
	//
	machine_menu.buttonConfTitle = BUTTON_TITLE_EN;
	machine_menu.function_btn1_display = DISPLAY_FUNCTIONBTN1_EN;
	machine_menu.function_btn1_cmd = FUNCTION_BTN1_TEXT_EN;
	machine_menu.quickStop_btn = DISPLAY_QUICKSTOP_EN;
	machine_menu.zoffset_btn_display = DISPLAY_ZOFFSET_EN;
	machine_menu.print_more_btn  = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.more_btn		 = MORE_BTN_TITLE_EN;
	machine_menu.MoreButtonConfTitle = MORE_BTN_TITLE_EN;
	machine_menu.moreItem_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_btn1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_btn2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_btn3 = BUTTON3_NAME_EN;			
	machine_menu.moreItem_btn4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_btn5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_btn6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_btn7 = BUTTON7_NAME_EN;
	
	machine_menu.MoreFunctionConfTitle = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.morefunc_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_func1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_func2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_func3 = BUTTON3_NAME_EN;			 
	machine_menu.moreItem_func4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_func5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_func6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_func7 = BUTTON7_NAME_EN;

	machine_menu.AutoLevelCmd = AUTOLEVELCMD_EN;
					machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_EN;
					machine_menu.low_level = MOTOR_EN_LOW_LEVEL_EN;
                    //

            
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_EN;
			common_menu.text_back=BACK_TEXT_EN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_EN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_EN;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;			
			//主页面
			main_menu.title=TITLE_READYPRINT_EN;
			main_menu.preheat=PREHEAT_TEXT_EN;
			main_menu.move=MOVE_TEXT_EN;
			main_menu.home=HOME_TEXT_EN;
			main_menu.print=PRINT_TEXT_EN;
			main_menu.extrude=EXTRUDE_TEXT_EN;
			main_menu.leveling=LEVELING_TEXT_EN;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_EN;
			main_menu.fan = FAN_TEXT_EN;
			main_menu.set=SET_TEXT_EN;
			main_menu.more=MORE_TEXT_EN;
			main_menu.tool = TOOL_TEXT_EN;
			//TOOL
			tool_menu.title = TOOL_TEXT_EN;
			tool_menu.preheat = TOOL_PREHEAT_EN;
			tool_menu.extrude = TOOL_EXTRUDE_EN;
			tool_menu.move = TOOL_MOVE_EN;
			tool_menu.home= TOOL_HOME_EN;
			tool_menu.leveling = TOOL_LEVELING_EN;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_EN;
			tool_menu.filament = TOOL_FILAMENT_EN;
			tool_menu.more = TOOL_MORE_EN;				
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_EN;
			preheat_menu.title=TITLE_PREHEAT_EN;
			preheat_menu.add=ADD_TEXT_EN;
			preheat_menu.dec=DEC_TEXT_EN;
			preheat_menu.ext1=EXTRUDER_1_TEXT_EN;
			preheat_menu.ext2=EXTRUDER_2_TEXT_EN;
			preheat_menu.hotbed=HEATBED_TEXT_EN;
			preheat_menu.off=CLOSE_TEXT_EN;
			//移动
			move_menu.title = TITLE_MOVE_EN;
			//归零
			home_menu.title=TITLE_HOME_EN;
			home_menu.stopmove = HOME_STOPMOVE_EN;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_EN;
			file_menu.page_up=PAGE_UP_TEXT_EN;
			file_menu.page_down=PAGE_DOWN_TEXT_EN;
			file_menu.file_loading = FILE_LOADING_EN;
			file_menu.no_file = NO_FILE_EN;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_EN;//NO_FILE_AND_CHECK_EN;			
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_EN;
			extrude_menu.in=EXTRUDER_IN_TEXT_EN;
			extrude_menu.out=EXTRUDER_OUT_TEXT_EN;
			extrude_menu.ext1=EXTRUDER_1_TEXT_EN;
			extrude_menu.ext2=EXTRUDER_2_TEXT_EN;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_EN;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_EN;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_EN;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_EN;
			//调平
			leveling_menu.title=TITLE_LEVELING_EN;
			leveling_menu.position1=LEVELING_POINT1_TEXT_EN;
			leveling_menu.position2=LEVELING_POINT2_TEXT_EN;
			leveling_menu.position3=LEVELING_POINT3_TEXT_EN;
			leveling_menu.position4=LEVELING_POINT4_TEXT_EN;
			leveling_menu.position5=LEVELING_POINT5_TEXT_EN;
			leveling_menu.count = LEVELING_POINTS_TEXT_EN;
			//设置
			set_menu.title=TITLE_SET_EN;
			set_menu.filesys=FILESYS_TEXT_EN;
			set_menu.wifi=WIFI_TEXT_EN;
			set_menu.about=ABOUT_TEXT_EN;
			set_menu.fan=FAN_TEXT_EN;
			set_menu.filament=FILAMENT_TEXT_EN;
			set_menu.breakpoint=BREAK_POINT_TEXT_EN;
			set_menu.motoroff=MOTOR_OFF_TEXT_EN;
			set_menu.language=LANGUAGE_TEXT_EN;
            set_menu.machine_para = MACHINE_PARA_EN;//
			//??
			more_menu.title = TITLE_MORE_EN;
			more_menu.zoffset = ZOFFSET_EN;
			more_menu.calibrate = CALIBRATE_EN;
			//文件系统
			filesys_menu.title = TITLE_FILESYS_EN;
			filesys_menu.sd_sys = SD_CARD_TEXT_EN;
			filesys_menu.usb_sys = U_DISK_TEXT_EN;
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_EN;
			//wifi_menu.ip = WIFI_IP_TEXT_EN;
			//wifi_menu.state= WIFI_STA_TEXT_EN;
			wifi_menu.cloud= CLOUD_TEXT_EN;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_EN;

			cloud_menu.title = TITLE_CLOUD_TEXT_EN;
			cloud_menu.bind = CLOUD_BINDED_EN;
			cloud_menu.binded = CLOUD_BINDED_EN;
			cloud_menu.unbind = CLOUD_UNBIND_EN;
			cloud_menu.unbinding = CLOUD_UNBINDED_EN;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_EN;
			cloud_menu.disable = CLOUD_DISABLE_EN;
			//关于
			about_menu.title = TITLE_ABOUT_EN;
			about_menu.type = ABOUT_TYPE_TEXT_EN;
			about_menu.version = ABOUT_VERSION_TEXT_EN;
			about_menu.wifi = ABOUT_WIFI_TEXT_EN;			
			//风扇
			fan_menu.title = TITLE_FAN_EN;
			fan_menu.add = FAN_ADD_TEXT_EN;
			fan_menu.dec = FAN_DEC_TEXT_EN;
			fan_menu.state = FAN_TIPS1_TEXT_EN;
			//换料
			filament_menu.title = TITLE_FILAMENT_EN;
			filament_menu.in = FILAMENT_IN_TEXT_EN;
			filament_menu.out = FILAMENT_OUT_TEXT_EN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_EN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_EN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_EN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_EN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_EN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_EN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_EN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_EN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_EN;

			//语言
			language_menu.title = TITLE_LANGUAGE_EN;
			language_menu.next = PAGE_DOWN_TEXT_EN;
			language_menu.up = PAGE_UP_TEXT_EN;			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_EN;
			printing_menu.option = PRINTING_OPERATION_EN;
			printing_menu.stop = PRINTING_STOP_EN;
			printing_menu.pause = PRINTING_PAUSE_EN;
			printing_menu.resume = PRINTING_RESUME_EN;

			//操作界面
			operation_menu.title = TITLE_OPERATION_EN;
			operation_menu.pause = PRINTING_PAUSE_EN;
			operation_menu.stop = PRINTING_STOP_EN;
			operation_menu.temp = PRINTING_TEMP_EN;
			operation_menu.fan = FAN_TEXT_EN;
			operation_menu.extr = PRINTING_EXTRUDER_EN;
			operation_menu.speed = PRINTING_CHANGESPEED_EN;			
			operation_menu.filament= FILAMENT_TEXT_EN;
			operation_menu.more = PRINTING_MORE_EN;
			operation_menu.move = PRINTING_MOVE_EN;
			operation_menu.auto_off = AUTO_SHUTDOWN_EN;
			operation_menu.manual_off = MANUAL_SHUTDOWN_EN;			
			//暂停界面
			pause_menu.title= TITLE_PAUSE_EN;
			pause_menu.resume = PRINTING_RESUME_EN;
			pause_menu.stop = PRINTING_STOP_EN;
			pause_menu.extrude = PRINTING_EXTRUDER_EN;
			pause_menu.move = PRINTING_MOVE_EN;
			pause_menu.filament = FILAMENT_TEXT_EN;
			pause_menu.more = PRINTING_MORE_EN;

			//变速界面
			speed_menu.title = TITLE_CHANGESPEED_EN;
			speed_menu.add = ADD_TEXT_EN;
			speed_menu.dec = DEC_TEXT_EN;
			speed_menu.move = MOVE_SPEED_EN;
			speed_menu.extrude = EXTRUDER_SPEED_EN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_EN;
			speed_menu.move_speed = MOVE_SPEED_STATE_EN;
			//打印中---更多界面
			printing_more_menu.title = TITLE_MORE_EN;
			printing_more_menu.fan = FAN_TEXT_EN;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_EN;
			printing_more_menu.manual = MANUAL_SHUTDOWN_EN;
			printing_more_menu.speed = PRINTING_CHANGESPEED_EN;
			printing_more_menu.temp = PRINTING_TEMP_EN;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_EN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_EN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_EN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_EN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_EN;
			print_file_dialog_menu.retry = DIALOG_RETRY_EN;
			print_file_dialog_menu.stop = DIALOG_STOP_EN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_EN;	
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_EN;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_EN;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_EN;			
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_EN;
			zoffset_menu.inc = ZOFFSET_INC_EN;
			zoffset_menu.dec = ZOFFSET_DEC_EN;				
			break;
		case LANG_RUSSIAN:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_RU;
			common_menu.text_back=BACK_TEXT_RU;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_RU;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_RU;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;			
			//主页面
			main_menu.title=TITLE_READYPRINT_RU;
			main_menu.preheat=PREHEAT_TEXT_RU;
			main_menu.move=MOVE_TEXT_RU;
			main_menu.home=HOME_TEXT_RU;
			main_menu.print=PRINT_TEXT_RU;
			main_menu.extrude=EXTRUDE_TEXT_RU;
			main_menu.leveling=LEVELING_TEXT_RU;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_RU;
			main_menu.fan = FAN_TEXT_RU;
			main_menu.set=SET_TEXT_RU;
			main_menu.more=MORE_TEXT_RU;
			main_menu.tool = TOOL_TEXT_RU;
			//TOOL
			tool_menu.title = TOOL_TEXT_RU;
			tool_menu.preheat = TOOL_PREHEAT_RU;
			tool_menu.extrude = TOOL_EXTRUDE_RU;
			tool_menu.move = TOOL_MOVE_RU;
			tool_menu.home= TOOL_HOME_RU;
			tool_menu.leveling = TOOL_LEVELING_RU;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_RU;
			tool_menu.filament = TOOL_FILAMENT_RU;
			tool_menu.more = TOOL_MORE_RU;				
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_RU;
			preheat_menu.title=TITLE_PREHEAT_RU;
			preheat_menu.add=ADD_TEXT_RU;
			preheat_menu.dec=DEC_TEXT_RU;
			preheat_menu.ext1=EXTRUDER_1_TEXT_RU;
			preheat_menu.ext2=EXTRUDER_2_TEXT_RU;
			preheat_menu.hotbed=HEATBED_TEXT_RU;
			preheat_menu.off=CLOSE_TEXT_RU;
			//移动
			move_menu.title = MOVE_TEXT_RU;
			//归零
			home_menu.title=TITLE_HOME_RU;
			home_menu.stopmove = HOME_STOPMOVE_RU;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_RU;
			file_menu.page_up=PAGE_UP_TEXT_RU;
			file_menu.page_down=PAGE_DOWN_TEXT_RU;
			file_menu.file_loading = FILE_LOADING_RU;
			file_menu.no_file = NO_FILE_RU;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_RU;//NO_FILE_AND_CHECK_RU;			
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_RU;
			extrude_menu.in=EXTRUDER_IN_TEXT_RU;
			extrude_menu.out=EXTRUDER_OUT_TEXT_RU;
			extrude_menu.ext1=EXTRUDER_1_TEXT_RU;
			extrude_menu.ext2=EXTRUDER_2_TEXT_RU;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_RU;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_RU;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_RU;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_RU;
			//调平
			leveling_menu.title=TITLE_LEVELING_RU;
			leveling_menu.position1=LEVELING_POINT1_TEXT_RU;
			leveling_menu.position2=LEVELING_POINT2_TEXT_RU;
			leveling_menu.position3=LEVELING_POINT3_TEXT_RU;
			leveling_menu.position4=LEVELING_POINT4_TEXT_RU;
			leveling_menu.position5=LEVELING_POINT5_TEXT_RU;
			//设置
			set_menu.title=TITLE_SET_RU;
			set_menu.filesys=FILESYS_TEXT_RU;
			set_menu.wifi=WIFI_TEXT_RU;
			set_menu.about=ABOUT_TEXT_RU;
			set_menu.fan=FAN_TEXT_RU;
			set_menu.filament=FILAMENT_TEXT_RU;
			set_menu.breakpoint=BREAK_POINT_TEXT_RU;
			set_menu.motoroff=MOTOR_OFF_TEXT_RU;
			set_menu.language=LANGUAGE_TEXT_RU;
			            set_menu.machine_para = MACHINE_PARA_RU;
			//更多
			more_menu.title = TITLE_MORE_RU;	
			more_menu.zoffset = ZOFFSET_RU;
			more_menu.calibrate = CALIBRATE_RU;
			//文件系统
			filesys_menu.title = TITLE_FILESYS_RU;
			filesys_menu.sd_sys = SD_CARD_TEXT_RU;
			filesys_menu.usb_sys = U_DISK_TEXT_RU;			
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_RU;
			//wifi_menu.ip = WIFI_IP_TEXT_RU;
			//wifi_menu.state= WIFI_STA_TEXT_RU;
			wifi_menu.cloud= CLOUD_TEXT_RU;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_RU;


			cloud_menu.title = TITLE_CLOUD_TEXT_RU;
			cloud_menu.bind = CLOUD_BINDED_RU;
			cloud_menu.binded = CLOUD_BINDED_RU;
			cloud_menu.unbind = CLOUD_UNBIND_RU;
			cloud_menu.unbinding = CLOUD_UNBINDED_RU;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_RU;
			cloud_menu.disable = CLOUD_DISABLE_RU;			
			//关于
			about_menu.title = ABOUT_TEXT_RU;
			about_menu.type = ABOUT_TYPE_TEXT_RU;
			about_menu.version = ABOUT_VERSION_TEXT_RU;
			about_menu.wifi = ABOUT_WIFI_TEXT_RU;			
			//风扇
			fan_menu.title = FAN_TEXT_RU;
			fan_menu.add = FAN_ADD_TEXT_RU;
			fan_menu.dec = FAN_DEC_TEXT_RU;
			fan_menu.state = FAN_TIPS1_TEXT_RU;
			//换料
			filament_menu.title = TITLE_FILAMENT_RU;
			filament_menu.in = FILAMENT_IN_TEXT_RU;
			filament_menu.out = FILAMENT_OUT_TEXT_RU;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_RU;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_RU;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_RU;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_RU;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_RU;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_RU;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_RU;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_RU;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_RU;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_RU;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_RU;

			//语言
			language_menu.title = LANGUAGE_TEXT_RU;
			language_menu.next = PAGE_DOWN_TEXT_RU;
			language_menu.up = PAGE_UP_TEXT_RU;
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_RU;
			printing_menu.option = PRINTING_OPERATION_RU;
			printing_menu.stop = PRINTING_STOP_RU;
			printing_menu.pause = PRINTING_PAUSE_RU;
			printing_menu.resume = PRINTING_RESUME_RU;

			//操作界面
			operation_menu.title = TITLE_OPERATION_RU;
			operation_menu.pause = PRINTING_PAUSE_RU;
			operation_menu.stop = PRINTING_STOP_RU;
			operation_menu.temp = PRINTING_TEMP_RU;
			operation_menu.fan = FAN_TEXT_RU;
			operation_menu.extr = PRINTING_EXTRUDER_RU;
			operation_menu.speed = PRINTING_CHANGESPEED_RU;			
			operation_menu.filament= FILAMENT_TEXT_RU;
			operation_menu.more = PRINTING_MORE_RU;
			operation_menu.move = PRINTING_MOVE_RU;
			operation_menu.auto_off = AUTO_SHUTDOWN_RU;
			operation_menu.manual_off = MANUAL_SHUTDOWN_RU;			
			//暂停界面
			pause_menu.title= TITLE_PAUSE_RU;
			pause_menu.resume = PRINTING_RESUME_RU;
			pause_menu.stop = PRINTING_STOP_RU;
			pause_menu.extrude = PRINTING_EXTRUDER_RU;
			pause_menu.move = PRINTING_MOVE_RU;
			pause_menu.filament= FILAMENT_TEXT_RU;
			pause_menu.more = PRINTING_MORE_RU;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_RU;
			speed_menu.add = ADD_TEXT_RU;
			speed_menu.dec = DEC_TEXT_RU;
			speed_menu.move = MOVE_SPEED_RU;
			speed_menu.extrude = EXTRUDER_SPEED_RU;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_RU;
			speed_menu.move_speed = MOVE_SPEED_STATE_RU;
			//打印中---更多界面
			printing_more_menu.title = TITLE_MORE_RU;
			printing_more_menu.fan = FAN_TEXT_RU;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_RU;
			printing_more_menu.manual = MANUAL_SHUTDOWN_RU;
			printing_more_menu.speed = PRINTING_CHANGESPEED_RU;
			printing_more_menu.temp = PRINTING_TEMP_RU;
			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_RU;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_RU;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_RU;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_RU;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_RU;
			print_file_dialog_menu.retry = DIALOG_RETRY_RU;
			print_file_dialog_menu.stop = DIALOG_STOP_RU;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_RU;		
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_RU;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_RU;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_RU;			
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_RU;
			zoffset_menu.inc = ZOFFSET_INC_RU;
			zoffset_menu.dec = ZOFFSET_DEC_RU;			
			break;
		case LANG_SPANISH:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_SP;
			common_menu.text_back=BACK_TEXT_SP;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_SP;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_SP;
			common_menu.print_special_title = PRINTING_SP;
			common_menu.pause_special_title = PRINTING_PAUSAR_SP;
			common_menu.operate_special_title = PRINTING_AJUSTES_SP;			
			//主页面
			main_menu.title=TITLE_READYPRINT_SP;
			main_menu.preheat=PREHEAT_TEXT_SP;
			main_menu.move=MOVE_TEXT_SP;
			main_menu.home=HOME_TEXT_SP;
			main_menu.print=PRINT_TEXT_SP;
			main_menu.extrude=EXTRUDE_TEXT_SP;
			main_menu.leveling=LEVELING_TEXT_SP;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_SP;
			main_menu.fan = FAN_TEXT_SP;
			main_menu.set=SET_TEXT_SP;
			main_menu.more=MORE_TEXT_SP;
			main_menu.tool = TOOL_TEXT_SP;
			//TOOL
			tool_menu.title = TOOL_TEXT_SP;
			tool_menu.preheat = TOOL_PREHEAT_SP;
			tool_menu.extrude = TOOL_EXTRUDE_SP;
			tool_menu.move = TOOL_MOVE_SP;
			tool_menu.home= TOOL_HOME_SP;
			tool_menu.leveling = TOOL_LEVELING_SP;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_SP;
			tool_menu.filament = TOOL_FILAMENT_SP;
			tool_menu.more = TOOL_MORE_SP;				
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_SP;
			preheat_menu.title=TITLE_PREHEAT_SP;
			preheat_menu.add=ADD_TEXT_SP;
			preheat_menu.dec=DEC_TEXT_SP;
			preheat_menu.ext1=EXTRUDER_1_TEXT_SP;
			preheat_menu.ext2=EXTRUDER_2_TEXT_SP;
			preheat_menu.hotbed=HEATBED_TEXT_SP;
			preheat_menu.off=CLOSE_TEXT_SP;
			//移动
			move_menu.title = MOVE_TEXT_SP;
			//归零
			home_menu.title=TITLE_HOME_SP;
			home_menu.home_x= HOME_X_TEXT_SP;
			home_menu.home_y= HOME_Y_TEXT_SP;
			home_menu.home_z= HOME_Z_TEXT_SP;
			home_menu.home_all= HOME_ALL_TEXT_SP;
			home_menu.stopmove = HOME_STOPMOVE_SP;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_SP;
			file_menu.page_up=PAGE_UP_TEXT_SP;
			file_menu.page_down=PAGE_DOWN_TEXT_SP;
			file_menu.file_loading = FILE_LOADING_SP;
			file_menu.no_file = NO_FILE_SP;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_SP;//NO_FILE_AND_CHECK_SP;			
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_SP;
			extrude_menu.in=EXTRUDER_IN_TEXT_SP;
			extrude_menu.out=EXTRUDER_OUT_TEXT_SP;
			extrude_menu.ext1=EXTRUDER_1_TEXT_SP;
			extrude_menu.ext2=EXTRUDER_2_TEXT_SP;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_SP;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_SP;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_SP;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_SP;
			//调平
			leveling_menu.title=TITLE_LEVELING_SP;
			leveling_menu.position1=LEVELING_POINT1_TEXT_SP;
			leveling_menu.position2=LEVELING_POINT2_TEXT_SP;
			leveling_menu.position3=LEVELING_POINT3_TEXT_SP;
			leveling_menu.position4=LEVELING_POINT4_TEXT_SP;
			leveling_menu.position5=LEVELING_POINT5_TEXT_SP;
			//设置
			set_menu.title=TITLE_SET_SP;
			set_menu.filesys=FILESYS_TEXT_SP;
			set_menu.wifi=WIFI_TEXT_SP;
			set_menu.about=ABOUT_TEXT_SP;
			set_menu.fan=FAN_TEXT_SP;
			set_menu.filament=FILAMENT_TEXT_SP;
			set_menu.breakpoint=BREAK_POINT_TEXT_SP;
			set_menu.motoroff=MOTOR_OFF_TEXT_SP;
			set_menu.language=LANGUAGE_TEXT_SP;
			            set_menu.machine_para = MACHINE_PARA_SP;
			//更多
			more_menu.title = TITLE_MORE_SP;
			more_menu.zoffset = ZOFFSET_SP;
			more_menu.calibrate = CALIBRATE_SP;
			//文件系统
			filesys_menu.title = TITLE_FILESYS_SP;
			filesys_menu.sd_sys = SD_CARD_TEXT_SP;
			filesys_menu.usb_sys = U_DISK_TEXT_SP;		
			
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_SP;
			//wifi_menu.ip = WIFI_IP_TEXT_SP;
			//wifi_menu.state= WIFI_STA_TEXT_SP;
			wifi_menu.cloud= CLOUD_TEXT_SP;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_SP;

			cloud_menu.title = TITLE_CLOUD_TEXT_SP;
			cloud_menu.bind = CLOUD_BINDED_SP;
			cloud_menu.binded = CLOUD_BINDED_SP;
			cloud_menu.unbind = CLOUD_UNBIND_SP;
			cloud_menu.unbinding = CLOUD_UNBINDED_SP;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_SP;
			cloud_menu.disable = CLOUD_DISABLE_SP;			
			//关于
			about_menu.title = ABOUT_TEXT_SP;
			about_menu.type = ABOUT_TYPE_TEXT_SP;
			about_menu.version = ABOUT_VERSION_TEXT_SP;
			about_menu.wifi = ABOUT_WIFI_TEXT_SP;				
			//风扇
			fan_menu.title = FAN_TEXT_SP;
			fan_menu.add = FAN_ADD_TEXT_SP;
			fan_menu.dec = FAN_DEC_TEXT_SP;
			fan_menu.state = FAN_TIPS1_TEXT_SP;
			//换料
			filament_menu.title = TITLE_FILAMENT_SP;
			filament_menu.in = FILAMENT_IN_TEXT_SP;
			filament_menu.out = FILAMENT_OUT_TEXT_SP;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_SP;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_SP;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_SP;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_SP;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_SP;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_SP;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_SP;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_SP;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_SP;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_SP;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_SP;

			//语言
			language_menu.title = LANGUAGE_TEXT_SP;
			language_menu.next = PAGE_DOWN_TEXT_SP;
			language_menu.up = PAGE_UP_TEXT_SP;			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_SP;
			printing_menu.option = PRINTING_OPERATION_SP;
			printing_menu.stop = PRINTING_STOP_SP;
			printing_menu.pause = PRINTING_PAUSE_SP;
			printing_menu.resume = PRINTING_RESUME_SP;

			//操作界面
			operation_menu.title = TITLE_OPERATION_SP;
			operation_menu.pause = PRINTING_PAUSE_SP;
			operation_menu.stop = PRINTING_STOP_SP;
			operation_menu.temp = PRINTING_TEMP_SP;
			operation_menu.fan = FAN_TEXT_SP;
			operation_menu.extr = PRINTING_EXTRUDER_SP;
			operation_menu.speed = PRINTING_CHANGESPEED_SP;			
			operation_menu.filament = FILAMENT_TEXT_SP;
			operation_menu.more = PRINTING_MORE_SP;
			operation_menu.move = PRINTING_MOVE_SP;
			operation_menu.auto_off = AUTO_SHUTDOWN_SP;
			operation_menu.manual_off = MANUAL_SHUTDOWN_SP;
			//暂停界面
			pause_menu.title= TITLE_PAUSE_RU;
			pause_menu.resume = PRINTING_RESUME_SP;
			pause_menu.stop = PRINTING_STOP_SP;
			pause_menu.extrude = PRINTING_EXTRUDER_SP;
			pause_menu.move = PRINTING_MOVE_SP;
			pause_menu.filament= FILAMENT_TEXT_SP;
			pause_menu.more = PRINTING_MORE_SP;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_SP;
			speed_menu.add = ADD_TEXT_SP;
			speed_menu.dec = DEC_TEXT_SP;
			speed_menu.move = MOVE_SPEED_SP;
			speed_menu.extrude = EXTRUDER_SPEED_SP;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_SP;
			speed_menu.move_speed = MOVE_SPEED_STATE_SP;
			//打印中---更多界面
			printing_more_menu.title= TITLE_MORE_SP;
			printing_more_menu.fan = FAN_TEXT_SP;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_SP;
			printing_more_menu.manual = MANUAL_SHUTDOWN_SP;
			printing_more_menu.speed = PRINTING_CHANGESPEED_SP;		
			printing_more_menu.temp = PRINTING_TEMP_SP;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_SP;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_SP;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_SP;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_SP;
			print_file_dialog_menu.retry = DIALOG_RETRY_SP;
			print_file_dialog_menu.stop = DIALOG_STOP_SP;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_SP;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_SP;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_SP;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_SP;
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_SP;
			zoffset_menu.inc = ZOFFSET_INC_SP;
			zoffset_menu.dec = ZOFFSET_DEC_SP;			
			break;
		#endif

		case LANG_FRENCH:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_FR;
			common_menu.text_back=BACK_TEXT_FR;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_FR;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_FR;			
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;

			//主页面
			main_menu.title=TITLE_READYPRINT_FR;
			main_menu.preheat=PREHEAT_TEXT_FR;
			main_menu.move=MOVE_TEXT_FR;
			main_menu.home=HOME_TEXT_FR;
			main_menu.print=PRINT_TEXT_FR;
			main_menu.extrude=EXTRUDE_TEXT_FR;
			main_menu.leveling=LEVELING_TEXT_FR;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_FR;
			main_menu.fan = FAN_TEXT_FR;
			main_menu.set=SET_TEXT_FR;
			main_menu.more=MORE_TEXT_FR;
			main_menu.tool = TOOL_TEXT_FR;
			//TOOL
			tool_menu.title = TOOL_TEXT_FR;
			tool_menu.preheat = TOOL_PREHEAT_FR;
			tool_menu.extrude = TOOL_EXTRUDE_FR;
			tool_menu.move = TOOL_MOVE_FR;
			tool_menu.home= TOOL_HOME_FR;
			tool_menu.leveling = TOOL_LEVELING_FR;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_FR;
			tool_menu.filament = TOOL_FILAMENT_FR;
			tool_menu.more = TOOL_MORE_FR;			
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_FR;
			preheat_menu.title=TITLE_PREHEAT_FR;
			preheat_menu.add=ADD_TEXT_FR;
			preheat_menu.dec=DEC_TEXT_FR;
			preheat_menu.ext1=EXTRUDER_1_TEXT_FR;
			preheat_menu.ext2=EXTRUDER_2_TEXT_FR;
			preheat_menu.hotbed =HEATBED_TEXT_FR;
			preheat_menu.off=CLOSE_TEXT_FR;
			//移动
			move_menu.title = MOVE_TEXT_FR;
			//归零
			home_menu.title=TITLE_HOME_FR;
			home_menu.stopmove = HOME_STOPMOVE_FR;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_FR;
			file_menu.page_up=PAGE_UP_TEXT_FR;
			file_menu.page_down=PAGE_DOWN_TEXT_FR;
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_FR;
			extrude_menu.in=EXTRUDER_IN_TEXT_FR;
			extrude_menu.out=EXTRUDER_OUT_TEXT_FR;
			extrude_menu.ext1=EXTRUDER_1_TEXT_FR;
			extrude_menu.ext2=EXTRUDER_2_TEXT_FR;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_FR;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_FR;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_FR;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_FR;
			//调平
			leveling_menu.title=TITLE_LEVELING_FR;
			leveling_menu.position1=LEVELING_POINT1_TEXT_FR;
			leveling_menu.position2=LEVELING_POINT2_TEXT_FR;
			leveling_menu.position3=LEVELING_POINT3_TEXT_FR;
			leveling_menu.position4=LEVELING_POINT4_TEXT_FR;
			leveling_menu.position5=LEVELING_POINT5_TEXT_FR;
			//设置
			set_menu.title=TITLE_SET_FR;
			set_menu.filesys=FILESYS_TEXT_FR;
			set_menu.wifi=WIFI_TEXT_FR;
			set_menu.about=ABOUT_TEXT_FR;
			set_menu.fan=FAN_TEXT_FR;
			set_menu.filament=FILAMENT_TEXT_FR;
			set_menu.breakpoint=BREAK_POINT_TEXT_FR;
			set_menu.motoroff=MOTOR_OFF_TEXT_FR;
			set_menu.language=LANGUAGE_TEXT_FR;
			            set_menu.machine_para = MACHINE_PARA_FR;
			//更多
			more_menu.title = TITLE_MORE_FR;
			more_menu.zoffset = ZOFFSET_FR;
			more_menu.calibrate = CALIBRATE_FR;
			//文件系统
			filesys_menu.title = TITLE_FILESYS_FR;
			filesys_menu.sd_sys = SD_CARD_TEXT_FR;
			filesys_menu.usb_sys = U_DISK_TEXT_FR;
			file_menu.file_loading = FILE_LOADING_FR;
			file_menu.no_file = NO_FILE_FR;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_FR;//NO_FILE_AND_CHECK_FR;				
			//WIFI
			wifi_menu.title=WIFI_NAME_TEXT_FR;
			//wifi_menu.key = WIFI_KEY_TEXT_FR;
			//wifi_menu.ip = WIFI_IP_TEXT_FR;
			//wifi_menu.state= WIFI_STA_TEXT_FR;
			//wifi_menu.cloud= CLOSE_TEXT_FR;
			//关于
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_FR;
			about_menu.title = ABOUT_TEXT_FR;
			about_menu.type = ABOUT_TYPE_TEXT_FR;
			about_menu.version = ABOUT_VERSION_TEXT_FR;
			about_menu.wifi = ABOUT_WIFI_TEXT_FR;				
			//风扇
			fan_menu.title = FAN_TEXT_FR;
			fan_menu.add = FAN_ADD_TEXT_FR;
			fan_menu.dec = FAN_DEC_TEXT_FR;
			fan_menu.state = FAN_TIPS1_TEXT_FR;
			//换料
			filament_menu.title = TITLE_FILAMENT_FR;
			filament_menu.in = FILAMENT_IN_TEXT_FR;
			filament_menu.out = FILAMENT_OUT_TEXT_FR;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_FR;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_FR;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_FR;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_FR;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_FR;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_FR;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_FR;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_FR;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_FR;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_FR;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_FR;

			//语言
			language_menu.title = LANGUAGE_TEXT_FR;
			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_FR;
			printing_menu.option = PRINTING_OPERATION_FR;
			printing_menu.stop = PRINTING_STOP_FR;
			printing_menu.pause = PRINTING_PAUSE_FR;
			printing_menu.resume = PRINTING_RESUME_FR;

			//操作界面
			operation_menu.title = TITLE_OPERATION_FR;
			operation_menu.pause = PRINTING_PAUSE_FR;
			operation_menu.stop = PRINTING_STOP_FR;
			operation_menu.temp = PRINTING_TEMP_FR;
			operation_menu.fan = FAN_TEXT_FR;
			operation_menu.extr = PRINTING_EXTRUDER_FR;
			operation_menu.speed = PRINTING_CHANGESPEED_FR;
			operation_menu.filament = FILAMENT_TEXT_FR;
			operation_menu.more = PRINTING_MORE_FR;
			operation_menu.move = PRINTING_MOVE_FR;
			operation_menu.auto_off = AUTO_SHUTDOWN_FR;
			operation_menu.manual_off = MANUAL_SHUTDOWN_FR;			
			//暂停界面
			pause_menu.title= TITLE_PAUSE_FR;
			pause_menu.resume = PRINTING_RESUME_FR;
			pause_menu.stop = PRINTING_STOP_FR;
			pause_menu.extrude = PRINTING_EXTRUDER_FR;
			pause_menu.move = PRINTING_MOVE_FR;
			pause_menu.filament = FILAMENT_TEXT_FR;
			pause_menu.more = PRINTING_MORE_FR;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_FR;
			speed_menu.add = ADD_TEXT_FR;
			speed_menu.dec = DEC_TEXT_FR;
			speed_menu.move = MOVE_SPEED_FR;
			speed_menu.extrude = EXTRUDER_SPEED_FR;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_FR;
			speed_menu.move_speed = MOVE_SPEED_STATE_FR;
			//打印中---更多界面
			printing_more_menu.fan = FAN_TEXT_FR;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_FR;
			printing_more_menu.manual = MANUAL_SHUTDOWN_FR;
			printing_more_menu.speed = PRINTING_CHANGESPEED_FR;	
			printing_more_menu.temp = PRINTING_TEMP_FR;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_FR;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_FR;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_FR;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_FR;
			print_file_dialog_menu.retry = DIALOG_RETRY_FR;
			print_file_dialog_menu.stop = DIALOG_STOP_FR;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_FR;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_FR;		
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_FR;
			
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_FR;
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_FR;
			zoffset_menu.inc = ZOFFSET_INC_FR;
			zoffset_menu.dec = ZOFFSET_DEC_FR;			
			break;
			
		case LANG_ITALY:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_IT;
			common_menu.text_back=BACK_TEXT_IT;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_IT;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_IT;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;

			//主页面
			main_menu.title=TITLE_READYPRINT_IT;
			main_menu.preheat=PREHEAT_TEXT_IT;
			main_menu.move=MOVE_TEXT_IT;
			main_menu.home=HOME_TEXT_IT;
			main_menu.print=PRINT_TEXT_IT;
			main_menu.extrude=EXTRUDE_TEXT_IT;
			main_menu.leveling=LEVELING_TEXT_IT;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_IT;
			main_menu.fan = FAN_TEXT_IT;
			main_menu.set=SET_TEXT_IT;
			main_menu.more=MORE_TEXT_IT;
			main_menu.tool = TOOL_TEXT_IT;
			//TOOL
			tool_menu.title = TOOL_TEXT_IT;
			tool_menu.preheat = TOOL_PREHEAT_IT;
			tool_menu.extrude = TOOL_EXTRUDE_IT;
			tool_menu.move = TOOL_MOVE_IT;
			tool_menu.home= TOOL_HOME_IT;
			tool_menu.leveling = TOOL_LEVELING_IT;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_IT;
			tool_menu.filament = TOOL_FILAMENT_IT;
			tool_menu.more = TOOL_MORE_IT;			
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_IT;
			preheat_menu.title=TITLE_PREHEAT_IT;
			preheat_menu.add=ADD_TEXT_IT;
			preheat_menu.dec=DEC_TEXT_IT;
			preheat_menu.ext1=EXTRUDER_1_TEXT_IT;
			preheat_menu.ext2=EXTRUDER_2_TEXT_IT;
			preheat_menu.hotbed=HEATBED_TEXT_IT;
			preheat_menu.off=CLOSE_TEXT_IT;
			//移动
			move_menu.title = MOVE_TEXT_IT;
			//归零
			home_menu.title=TITLE_HOME_IT;
			home_menu.stopmove = HOME_STOPMOVE_IT;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_IT;
			file_menu.page_up=PAGE_UP_TEXT_IT;
			file_menu.page_down=PAGE_DOWN_TEXT_IT;
			file_menu.file_loading = FILE_LOADING_IT;
			file_menu.no_file = NO_FILE_IT;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_IT;//NO_FILE_AND_CHECK_IT;				
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_IT;
			extrude_menu.in=EXTRUDER_IN_TEXT_IT;
			extrude_menu.out=EXTRUDER_OUT_TEXT_IT;
			extrude_menu.ext1=EXTRUDER_1_TEXT_IT;
			extrude_menu.ext2=EXTRUDER_2_TEXT_IT;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_IT;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_IT;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_IT;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_IT;
			//调平
			leveling_menu.title=TITLE_LEVELING_IT;
			leveling_menu.position1=LEVELING_POINT1_TEXT_IT;
			leveling_menu.position2=LEVELING_POINT2_TEXT_IT;
			leveling_menu.position3=LEVELING_POINT3_TEXT_IT;
			leveling_menu.position4=LEVELING_POINT4_TEXT_IT;
			leveling_menu.position5=LEVELING_POINT5_TEXT_IT;
			//设置
			set_menu.title=TITLE_SET_IT;
			set_menu.filesys=FILESYS_TEXT_IT;
			set_menu.wifi=WIFI_TEXT_IT;
			set_menu.about=ABOUT_TEXT_IT;
			set_menu.fan=FAN_TEXT_IT;
			set_menu.filament=FILAMENT_TEXT_IT;
			set_menu.breakpoint=BREAK_POINT_TEXT_IT;
			set_menu.motoroff=MOTOR_OFF_TEXT_IT;
			set_menu.language=LANGUAGE_TEXT_IT;
			            set_menu.machine_para = MACHINE_PARA_IT;
			//更多
			more_menu.title = TITLE_MORE_IT;
			more_menu.zoffset = ZOFFSET_IT;
			more_menu.calibrate = CALIBRATE_IT;
			//文件系统
			filesys_menu.title = TITLE_FILESYS_IT;
			filesys_menu.sd_sys = SD_CARD_TEXT_IT;
			filesys_menu.usb_sys = U_DISK_TEXT_IT;

			//WIFI
			wifi_menu.title=WIFI_NAME_TEXT_IT;
			//wifi_menu.key = WIFI_KEY_TEXT_IT;
			//wifi_menu.ip = WIFI_IP_TEXT_IT;
			//wifi_menu.state= WIFI_STA_TEXT_IT;
			wifi_menu.cloud= CLOSE_TEXT_IT;
			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_IT;
			//关于
			about_menu.title = ABOUT_TEXT_IT;
			about_menu.type = ABOUT_TYPE_TEXT_IT;
			about_menu.version = ABOUT_VERSION_TEXT_IT;
			about_menu.wifi = ABOUT_WIFI_TEXT_IT;				
			//风扇
			fan_menu.title = FAN_TEXT_IT;
			fan_menu.add = FAN_ADD_TEXT_IT;
			fan_menu.dec = FAN_DEC_TEXT_IT;
			fan_menu.state = FAN_TIPS1_TEXT_IT;
			//换料
			filament_menu.title = TITLE_FILAMENT_IT;
			filament_menu.in = FILAMENT_IN_TEXT_IT;
			filament_menu.out = FILAMENT_OUT_TEXT_IT;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_IT;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_IT;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_IT;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_IT;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_IT;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_IT;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_IT;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_IT;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_IT;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_IT;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_IT;

			//语言
			language_menu.title = LANGUAGE_TEXT_IT;
			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_IT;
			printing_menu.option = PRINTING_OPERATION_IT;
			printing_menu.stop = PRINTING_STOP_IT;
			printing_menu.pause = PRINTING_PAUSE_IT;
			printing_menu.resume = PRINTING_RESUME_IT;

			//操作界面
			operation_menu.title = TITLE_OPERATION_IT;
			operation_menu.pause = PRINTING_PAUSE_IT;
			operation_menu.stop = PRINTING_STOP_IT;
			operation_menu.temp = PRINTING_TEMP_IT;
			operation_menu.fan = FAN_TEXT_IT;
			operation_menu.extr = PRINTING_EXTRUDER_IT;
			operation_menu.speed = PRINTING_CHANGESPEED_IT;			
			operation_menu.filament = FILAMENT_TEXT_IT;
			operation_menu.more = PRINTING_MORE_IT;
			operation_menu.move = PRINTING_MOVE_IT;
			operation_menu.auto_off = AUTO_SHUTDOWN_IT;
			operation_menu.manual_off = MANUAL_SHUTDOWN_IT;
			//暂停界面
			pause_menu.title= TITLE_PAUSE_IT;
			pause_menu.resume = PRINTING_RESUME_IT;
			pause_menu.stop = PRINTING_STOP_IT;
			pause_menu.extrude = PRINTING_EXTRUDER_IT;
			pause_menu.move = PRINTING_MOVE_IT;
			pause_menu.filament = FILAMENT_TEXT_IT;
			pause_menu.more = PRINTING_MORE_IT;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_IT;
			speed_menu.add = ADD_TEXT_IT;
			speed_menu.dec = DEC_TEXT_IT;
			speed_menu.move = MOVE_SPEED_IT;
			speed_menu.extrude = EXTRUDER_SPEED_IT;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_IT;
			speed_menu.move_speed = MOVE_SPEED_STATE_IT;
			//打印中---更多界面
			printing_more_menu.fan = FAN_TEXT_IT;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_IT;
			printing_more_menu.manual = MANUAL_SHUTDOWN_IT;
			printing_more_menu.temp = PRINTING_TEMP_IT;	
			printing_more_menu.speed = PRINTING_CHANGESPEED_IT;		

						//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_IT;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_IT;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_IT;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_IT;
			print_file_dialog_menu.retry = DIALOG_RETRY_IT;
			print_file_dialog_menu.stop = DIALOG_STOP_IT;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_IT;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_IT;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_IT;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_IT;
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_IT;
			zoffset_menu.inc = ZOFFSET_INC_IT;
			zoffset_menu.dec = ZOFFSET_DEC_IT;			
			break;

			#if 0
		case LANG_KOREAN:
			common_menu.text_back=BACK_TEXT_KR;
			//主页面
			main_menu.title=TITLE_READYPRINT_KR;
			main_menu.preheat=PREHEAT_TEXT_KR;
			main_menu.move=MOVE_TEXT_KR;
			main_menu.home=HOME_TEXT_KR;
			main_menu.print=PRINT_TEXT_KR;
			main_menu.extrude=EXTRUDE_TEXT_KR;
			main_menu.leveling=LEVELING_TEXT_KR;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_KR;
			main_menu.set=SET_TEXT_KR;
			main_menu.more=MORE_TEXT_KR;
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_KR;
			preheat_menu.title=TITLE_PREHEAT_KR;
			preheat_menu.add=ADD_TEXT_KR;
			preheat_menu.dec=DEC_TEXT_KR;
			preheat_menu.ext1=EXTRUDER_1_TEXT_KR;
			preheat_menu.ext2=EXTRUDER_2_TEXT_KR;
			preheat_menu.off=CLOSE_TEXT_KR;
			//移动
			move_menu.title = MOVE_TEXT_KR;
			//归零
			home_menu.title=TITLE_HOME_KR;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_KR;
			file_menu.page_up=PAGE_UP_TEXT_KR;
			file_menu.page_down=PAGE_DOWN_TEXT_KR;
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_KR;
			extrude_menu.in=EXTRUDER_IN_TEXT_KR;
			extrude_menu.out=EXTRUDER_OUT_TEXT_KR;
			extrude_menu.ext1=EXTRUDER_1_TEXT_KR;
			extrude_menu.ext2=EXTRUDER_2_TEXT_KR;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_KR;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_KR;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_KR;
			//调平
			leveling_menu.title=TITLE_LEVELING_KR;
			leveling_menu.position1=LEVELING_POINT1_TEXT_KR;
			leveling_menu.position2=LEVELING_POINT2_TEXT_KR;
			leveling_menu.position3=LEVELING_POINT3_TEXT_KR;
			leveling_menu.position4=LEVELING_POINT4_TEXT_KR;
			leveling_menu.position5=LEVELING_POINT5_TEXT_KR;
			//设置
			set_menu.title=TITLE_SET_KR;
			set_menu.wifi=WIFI_TEXT_KR;
			set_menu.about=ABOUT_TEXT_KR;
			set_menu.fan=FAN_TEXT_KR;
			set_menu.filament=FILAMENT_TEXT_KR;
			set_menu.breakpoint=BREAK_POINT_TEXT_KR;
			set_menu.motoroff=MOTOR_OFF_TEXT_KR;
			set_menu.language=LANGUAGE_TEXT_KR;
			//更多
			//strcpy(more_menu.back,BACK_TEXT_EN);	
			//WIFI
			wifi_menu.title=WIFI_NAME_TEXT_KR;
			wifi_menu.key = WIFI_KEY_TEXT_KR;
			wifi_menu.ip = WIFI_IP_TEXT_KR;
			wifi_menu.state= WIFI_STA_TEXT_KR;
			wifi_menu.cloud= CLOSE_TEXT_KR;
			//关于
			about_menu.title = ABOUT_TEXT_KR;
			//风扇
			fan_menu.title = FAN_TEXT_KR;
			fan_menu.add = FAN_ADD_TEXT_KR;
			fan_menu.dec = FAN_DEC_TEXT_KR;
			fan_menu.state = FAN_TIPS1_TEXT;
			//换料
			filament_menu.title = TITLE_FILAMENT_TEXT_KR;
			filament_menu.in = FILAMENT_IN_TEXT_KR;
			filament_menu.out = FILAMENT_OUT_TEXT_KR;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_KR;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_KR;

			//语言
			language_menu.title = LANGUAGE_TEXT_KR;
			
			//正在打印界面
			printing_menu.title = TITLE_PRINTING_KR;
			printing_menu.option = PRINTING_OPERATION_KR;
			printing_menu.stop = PRINTING_STOP_KR;
			printing_menu.pause = PRINTING_PAUSE_KR;
			printing_menu.resume = PRINTING_RESUME_KR;

			//操作界面
			operation_menu.title = TITLE_OPERATION_KR;
			operation_menu.pause = PRINTING_PAUSE_KR;
			operation_menu.stop = PRINTING_STOP_KR;
			operation_menu.temp = PRINTING_TEMP_KR;
			operation_menu.speed = PRINTING_CHANGESPEED_KR;
			operation_menu.more = PRINTING_MORE_KR;
			//暂停界面
			pause_menu.title= PRINTING_PAUSE_KR;
			pause_menu.resume = PRINTING_RESUME_KR;
			pause_menu.stop = PRINTING_STOP_KR;
			pause_menu.extrude = PRINTING_EXTRUDER_KR;
			pause_menu.move = PRINTING_MOVE_KR;
			pause_menu.temp = PRINTING_TEMP_KR;
			pause_menu.more = PRINTING_MORE_KR;

			//变速界面
			speed_menu.title = PRINTING_CHANGESPEED_KR;
			speed_menu.add = ADD_TEXT_KR;
			speed_menu.dec = DEC_TEXT_KR;
			speed_menu.move = MOVE_SPEED_KR;
			speed_menu.extrude = EXTRUDER_SPEED_KR;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_KR;
			speed_menu.move_speed = MOVE_SPEED_STATE_KR;
			//打印中---更多界面
			printing_more_menu.fan = FAN_TEXT_KR;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_KR;
			printing_more_menu.manual = MANUAL_SHUTDOWN_KR;
			printing_more_menu.filament = FILAMENT_TEXT_KR;						
			break;		
		#endif	
		default:break;
                    MachinePara_menu.title = MACHINE_PARA_TITLE_EN;
                    MachinePara_menu.MachineSetting = MACHINE_TYPE_CNOFIG_EN;
                    MachinePara_menu.TemperatureSetting=TEMPERATURE_CONFIG_EN;
                    MachinePara_menu.MotorSetting=MOTOR_CONFIG_EN;
                    MachinePara_menu.AdvanceSetting=ADVANCE_CONFIG_EN;
					MachinePara_menu.Custom = CUSTOM_CONFIG_EN;
					MachinePara_menu.Console = CONSOLE_EN;
            
                    machine_menu.default_value = DEFAULT_EN;
                    machine_menu.next=NEXT_EN;
                    machine_menu.previous=PREVIOUS_EN;
            		machine_menu.back = BACK_TEXT_EN;
                    machine_menu.MachineConfigTitle = MACHINE_CONFIG_TITLE_EN;
                    machine_menu.MachineType=MACHINE_TYPE_EN;
                    machine_menu.Stroke=MACHINE_STROKE_EN;
                    machine_menu.HomeDir=MACHINE_HOMEDIR_EN;
                    machine_menu.EndStopType=MACHINE_ENDSTOP_TYPE_EN;
                    machine_menu.FilamentConf=MACHINE_FILAMENT_CONFIG_EN;
                    machine_menu.LevelingConf=MACHINE_LEVELING_CONFIG_EN;
	machine_menu.BaudRateConf = MACHINE_BAUDRATE_CONFIG_EN;
	machine_menu.FirmwareType = MACHINE_FIRMWARE_CONFIG_EN;
	machine_menu.PausePosConf = MACHINE_PAUSEPOSI_CONFIG_EN;
	machine_menu.WifiConf = MACHINE_WIFI_CONFIG_EN;
                    machine_menu.MachineTypeConfTitle = MACHINE_TYPE_CONFIG_TITLE_EN;
                    machine_menu.xyz=MACHINE_TYPE_XYZ_EN;
                    machine_menu.delta=MACHINE_TYPE_DELTA_EN;
                    machine_menu.corexy=MACHINE_TYPE_COREXY_EN;
					machine_menu.normal= MACHINE_TYPE_NORMAL_EN;
            
    machine_menu.FirmwareTypeConfTitle = FIRMWARE_TYPE_CONFIG_TITLE_EN;
    machine_menu.marlin=FIRMWARE_TYPE_MARLIN_EN;
    machine_menu.repetier=FIRMWARE_TYPE_REPETIER_EN;
    machine_menu.smoothie=FIRMWARE_TYPE_SMOOTHIE_EN;

    machine_menu.BaudRateConfTitle = BAUD_RATE_CONFIG_TITLE_EN;
    machine_menu.rate1=BAUD_RATE_9600_EN;
    machine_menu.rate2=BAUD_RATE_57600_EN;
    machine_menu.rate3=BAUD_RATE_115200_EN;
	machine_menu.rate4=BAUD_RATE_250000_EN;

	machine_menu.wifiConfTile = WIFI_CONFIG_TILE_EN;
	machine_menu.WifiKey	  = WIFI_KEY_SET_EN;
	machine_menu.WifiMode	  = WIFI_MODE_SEL_EN;
	machine_menu.cloudEnable  = WIFI_CLOUD_ENABLE_EN;
	machine_menu.cloudHost 	  = WIFI_CLOUD_ADDR_EN;
	machine_menu.cloudPort    = WIFI_CLOUD_PORT_EN;
	machine_menu.WifiMode0	  = WIFI_MODE0_EN;
	machine_menu.WifiMode1	  = WIFI_MODE1_EN;
	machine_menu.WifiName	  = WIFI_NAME_SET_EN;
                    machine_menu.StrokeConfTitle=MACHINE_STROKE_CONF_TITLE_EN;
                    machine_menu.xStroke=X_MAX_LENGTH_EN;
                    machine_menu.yStroke=Y_MAX_LENGTH_EN;
                    machine_menu.zStroke=Z_MAX_LENGTH_EN;

			machine_menu.xmin=X_MIN_LENGTH_EN;
		       machine_menu.ymin=Y_MIN_LENGTH_EN;
		       machine_menu.zmin=Z_MIN_LENGTH_EN;		
            
                    machine_menu.HomeDirConfTitle=HOME_DIR_CONF_TITLE_EN;
                    machine_menu.xHomeDir=HOME_DIR_X_EN;
                    machine_menu.yHomeDir=HOME_DIR_Y_EN;
                    machine_menu.zHomeDir=HOME_DIR_Z_EN;
                    machine_menu.min=HOME_MIN_EN;
                    machine_menu.max=HOME_MAX_EN;
            
			machine_menu.PositionPuaseConfTitle=PAUSE_POSITION_CONF_TITLE_EN;
			machine_menu.xPosition=POSITION_X_EN;
			machine_menu.yPosition=POSITION_Y_EN;
			machine_menu.zPosition=POSITION_Z_EN;
                    machine_menu.EndstopConfTitle=ENDSTOP_CONF_TITLE_EN;
                    machine_menu.xEndstop_min=MIN_ENDSTOP_X_EN;
                    machine_menu.yEndstop_min=MIN_ENDSTOP_Y_EN;
                    machine_menu.zEndstop_min=MIN_ENDSTOP_Z_EN;
                    machine_menu.xEndstop_max=MAX_ENDSTOP_X_EN;
                    machine_menu.yEndstop_max=MAX_ENDSTOP_Y_EN;
                    machine_menu.zEndstop_max=MAX_ENDSTOP_Z_EN;            
                    machine_menu.FilamentEndstop=ENDSTOP_FIL_EN;
                    machine_menu.LevelingEndstop=ENDSTOP_LEVEL_EN;
                    machine_menu.opened=ENDSTOP_OPENED_EN;
                    machine_menu.closed=ENDSTOP_CLOSED_EN;
            
                    machine_menu.FilamentConfTitle=FILAMENT_CONF_TITLE_EN;
                    machine_menu.InTemperature=FILAMENT_IN_TEMPERATURE_EN;
                    machine_menu.InLength=FILAMENT_IN_LENGTH_EN;
                    machine_menu.InSpeed=FILAMENT_IN_SPEED_EN;
                    machine_menu.OutTemperature=FILAMENT_OUT_TEMPERATURE_EN;
                    machine_menu.OutLength=FILAMENT_OUT_LENGTH_EN;
                    machine_menu.OutSpeed=FILAMENT_OUT_SPEED_EN;
                                
                    machine_menu.LevelingParaConfTitle=LEVELING_CONF_TITLE_EN;
                    machine_menu.LevelingParaConf=LEVELING_PARA_CONF_EN;
                    machine_menu.DeltaLevelConf=LEVELING_DELTA_EN;
                    machine_menu.XYZLevelconf=LEVELING_XYZ_EN;
            
                    machine_menu.LevelingSubConfTitle=LEVELING_PARA_CONF_TITLE_EN;
                    machine_menu.AutoLevelEnable=AUTO_LEVELING_ENABLE_EN;
                    machine_menu.BLtouchEnable=BLTOUCH_LEVELING_ENABLE_EN;
                    machine_menu.ProbePort=PROBE_PORT_EN;
                    machine_menu.ProbeXoffset=PROBE_X_OFFSET_EN;
                    machine_menu.ProbeYoffset=PROBE_Y_OFFSET_EN;
                    machine_menu.ProbeZoffset=PROBE_Z_OFFSET_EN;
                    machine_menu.ProbeXYspeed=PROBE_XY_SPEED_EN;
                    machine_menu.ProbeZspeed=PROBE_Z_SPEED_EN;
                    machine_menu.enable = ENABLE_EN;
                    machine_menu.disable = DISABLE_EN;
                    machine_menu.z_min = Z_MIN_EN;
                    machine_menu.z_max = Z_MAX_EN;
					machine_menu.high_level = LEVEL_HIGH_EN;
					machine_menu.low_level = LEVEL_LOW_EN;
					machine_menu.pwr_saveMode = OFF_SAVE_MODE_EN;
					machine_menu.pwr_saveMode1 = OFF_SAVE_MODE1_EN;
					machine_menu.pwr_saveMode2 = OFF_SAVE_MODE2_EN;
					machine_menu.disable_PB0_PB1 = DISABLE_PB1_PB0_CONF_EN;
					machine_menu.level_PB0 = LEVEL_PB0_CONF_EN;
					machine_menu.level_PB1 = LEVEL_PB1_CONF_EN;
					machine_menu.z_error = BREAKPOINT_Z_ERROR_EN;
            	
			machine_menu.leveling_z_speed = LEVELING_Z_SPEED_EN;
			machine_menu.leveling_xy_speed = LEVELING_XY_SPEED_EN;
			machine_menu.leveling_z_high = LEVELING_Z_HIGH_EN;

                    machine_menu.LevelingSubDeltaConfTitle=DELTA_LEVEL_CONF_TITLE_EN;
                    machine_menu.MachineRadius=DELTA_MACHINE_RADIUS_EN;
                    machine_menu.DiagonalRod=DELTA_DIAGONAL_ROD_EN;
                    machine_menu.PrintableRadius=DELTA_PRINT_RADIUS_EN;
                    machine_menu.DeltaHeight=DELTA_HEIGHT_EN;
                    machine_menu.SmoothRodOffset=SMOOTH_ROD_OFFSET_EN;
                    machine_menu.EffectorOffset=EFFECTOR_OFFSET_EN;
                    machine_menu.CalibrationRadius=CALIBRATION_RADIUS_EN;
            
                    machine_menu.LevelingSubXYZConfTitle=XYZ_LEVEL_CONF_TITLE_EN;
                    //machine_menu.ProbeMaxLeft=PROBE_REACH_MAX_LEFT_EN;
                    //machine_menu.ProbeMaxRigh=PROBE_REACH_MAX_RIGHT_EN;
                    //machine_menu.ProbeMaxfront=PROBE_REACH_MAX_FRONT_EN;
                    //machine_menu.ProbeMaxback=PROBE_REACH_MAX_BACK_EN;
            
                    machine_menu.TemperatureConfTitle=TEMPERATURE_CONF_TITLE_EN;
                    machine_menu.NozzleConf=NOZZLE_CONF_EN;
                    machine_menu.HotBedConf=HOTBED_CONF_EN;
                    machine_menu.PreheatTemperConf=PREHEAT_TEMPER_EN;
            
                    machine_menu.NozzleConfTitle=NOZZLE_CONF_TITLE_EN;
                    machine_menu.NozzleCnt=NOZZLECNT_EN;
                    machine_menu.NozzleType=NOZZLE_TYPE_EN;
                    machine_menu.NozzleAdjustType=NOZZLE_ADJUST_TYPE_EN;
                    machine_menu.NozzleMinTemperature=NOZZLE_MIN_TEMPERATURE_EN;
                    machine_menu.NozzleMaxTemperature=NOZZLE_MAX_TEMPERATURE_EN;
                    machine_menu.Extrude_Min_Temper=EXTRUD_MIN_TEMPER_EN;

		    machine_menu.HotbedEnable=HOTBED_ENABLE_EN;
                    machine_menu.HotbedConfTitle=HOTBED_CONF_TITLE_EN;
                    machine_menu.HotbedAjustType=HOTBED_ADJUST_EN;
                    machine_menu.HotbedMinTemperature=HOTBED_MIN_TEMPERATURE_EN;
                    machine_menu.HotbedMaxTemperature=HOTBED_MAX_TEMPERATURE_EN;
            
                    machine_menu.MotorConfTitle=MOTOR_CONF_TITLE_EN;
                    machine_menu.MaxFeedRateConf=MAXFEEDRATE_CONF_EN;
                    machine_menu.AccelerationConf=ACCELERATION_CONF_EN;
                    machine_menu.JerkConf=JERKCONF_EN;
                    machine_menu.StepsConf=STEPSCONF_EN;
                    machine_menu.MotorDirConf=MOTORDIRCONF_EN;
                    machine_menu.HomeFeedRateConf=HOMEFEEDRATECONF_EN;
		    machine_menu.CurrentConf=CURRENTCONF_EN;	
		    machine_menu.GetInfo = GETEEPROM_EN;
		    machine_menu.SaveInfo =SAVETOEEPROM_EN;
		    machine_menu.TMCBumpSen = TMCBUMPCONF_EN;

		    machine_menu.TMCBumpTitle=TMC_CONF_TITLE_EN;
		    machine_menu.X_Sensivisity=X_SENSITIVITY_EN;
		    machine_menu.Y_Sensivisity=Y_SENSITIVITY_EN;
		    machine_menu.Z_Sensivisity=Z_SENSITIVITY_EN;
                    machine_menu.MaxFeedRateConfTitle=MAXFEEDRATE_CONF_TITLE_EN;
                    machine_menu.XMaxFeedRate=X_MAXFEEDRATE_EN;
                    machine_menu.YMaxFeedRate=Y_MAXFEEDRATE_EN;
                    machine_menu.ZMaxFeedRate=Z_MAXFEEDRATE_EN;
                    machine_menu.E0MaxFeedRate=E0_MAXFEEDRATE_EN;
                    machine_menu.E1MaxFeedRate=E1_MAXFEEDRATE_EN;
            
                    machine_menu.AccelerationConfTitle=ACCELERATION_CONF_TITLE_EN;
                    machine_menu.PrintAcceleration=PRINT_ACCELERATION_EN;
                    machine_menu.RetractAcceleration=RETRACT_ACCELERATION_EN;
                    machine_menu.TravelAcceleration=TRAVEL_ACCELERATION_EN;
                    machine_menu.X_Acceleration=X_ACCELERATION_EN;
                    machine_menu.Y_Acceleration=Y_ACCELERATION_EN;
                    machine_menu.Z_Acceleration=Z_ACCELERATION_EN;
                    machine_menu.E0_Acceleration=E0_ACCELERATION_EN;
                    machine_menu.E1_Acceleration=E1_ACCELERATION_EN;
            
                    machine_menu.JerkConfTitle=JERK_CONF_TITLE_EN;
                    machine_menu.X_Jerk=X_JERK_EN;
                    machine_menu.Y_Jerk=Y_JERK_EN;
                    machine_menu.Z_Jerk=Z_JERK_EN;
                    machine_menu.E_Jerk=E_JERK_EN;
            
                    machine_menu.StepsConfTitle=STEPS_CONF_TITLE_EN;
                    machine_menu.X_Steps=X_STEPS_EN;
                    machine_menu.Y_Steps=Y_STEPS_EN;
                    machine_menu.Z_Steps=Z_STEPS_EN;
                    machine_menu.E0_Steps=E0_STEPS_EN;
                    machine_menu.E1_Steps=E1_STEPS_EN;
            
		    machine_menu.CurrentConfTitle=CURRENT_CONF_TITLE_EN;
		    machine_menu.X_Current=X_CURRENT_EN;
		    machine_menu.Y_Current=Y_CURRENT_EN;
		    machine_menu.Z_Current=Z_CURRENT_EN;
		    machine_menu.E0_Current=E0_CURRENT_EN;
		    machine_menu.E1_Current=E1_CURRENT_EN;	
                    machine_menu.MotorDirConfTitle=MOTORDIR_CONF_TITLE_EN;
                    machine_menu.X_MotorDir=X_MOTORDIR_EN;
                    machine_menu.Y_MotorDir=Y_MOTORDIR_EN;
                    machine_menu.Z_MotorDir=Z_MOTORDIR_EN;
                    machine_menu.E0_MotorDir=E0_MOTORDIR_EN;
                    machine_menu.E1_MotorDir=E1_MOTORDIR_EN;
                    machine_menu.Invert_0=INVERT_P_EN;
                    machine_menu.Invert_1=INVERT_N_EN;
            
                    machine_menu.HomeFeedRateConfTitle=HOMEFEEDRATE_CONF_TITLE_EN;
                    machine_menu.XY_HomeFeedRate=X_HOMESPEED_EN;
                    //machine_menu.Y_HomeFeedRate=Y_HOMESPEED_EN;
                    machine_menu.Z_HomeFeedRate=Z_HOMESPEED_EN;
            
                    machine_menu.AdvancedConfTitle=ADVANCED_CONF_TITLE_EN;
                    machine_menu.PwrOffDection=PWROFF_DECTION_EN;
                    machine_menu.PwrOffAfterPrint=PWROFF_AFTER_PRINT_EN;
                    machine_menu.HaveUps=HAVE_UPS_EN;
                    machine_menu.Z2andZ2Endstop=Z2_AND_Z2ENDSTOP_CONF_EN;
                    machine_menu.EnablePinsInvert=ENABLE_PINS_CONF_EN;
            
                    machine_menu.Z2ConfTitle=Z2_AND_Z2ENDSTOP_CONF_TITLE_EN;
                    machine_menu.Z2Enable=Z2_ENABLE_EN;
                    machine_menu.Z2EndstopEnable=Z2_ENDSTOP_EN;
                    machine_menu.Z2Port=Z2_PORT_EN;
            
                    machine_menu.EnablePinsInvertTitle=ENABLE_PINS_CONF_TITLE_EN;
                    machine_menu.XInvert=X_ENABLE_PINS_INVERT_EN;
                    machine_menu.YInvert=Y_ENABLE_PINS_INVERT_EN;
                    machine_menu.ZInvert=Z_ENABLE_PINS_INVERT_EN;
                    machine_menu.EInvert=E_ENABLE_PINS_INVERT_EN;
            
                    machine_menu.key_back = KEY_BACK_EN;
                    machine_menu.key_rest = KEY_REST_EN;
                    machine_menu.key_confirm = KEY_CONFIRM_EN;
  		  set_menu.machine_para = MACHINE_PARA_EN;
					machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_EN;
					machine_menu.low_level = MOTOR_EN_LOW_LEVEL_EN;
	machine_menu.CustomConfTitle = CUSTOMCONF_TITLE_EN;
	machine_menu.display		 = DISPLAY_CONF_EN;
	machine_menu.button 		 = BUTTON_CONF_EN;
	
	machine_menu.DisplayConfTitle = DISPLAY_TITLE_EN;
	machine_menu.btn_3D_ecffects = BUTTON_3D_EN;
	machine_menu.btn_text_offset = BTN_TEXT_OFFSET_EN;
	machine_menu.screen_overturn = SCREEN_OVERTURN_EN;
	machine_menu.display_mode =    DISPLAY_MODE_EN;
	machine_menu.display_error_msg = ENABLE_ERROR_MSG_EN;
	machine_menu.simple_theme	= SIMPLETHEME_EN;
	machine_menu.classic_theme	= CLASSICTHEME_EN;
	//
	machine_menu.buttonConfTitle = BUTTON_TITLE_EN;
	machine_menu.function_btn1_display = DISPLAY_FUNCTIONBTN1_EN;
	machine_menu.function_btn1_cmd = FUNCTION_BTN1_TEXT_EN;
	machine_menu.quickStop_btn = DISPLAY_QUICKSTOP_EN;
	machine_menu.zoffset_btn_display = DISPLAY_ZOFFSET_EN;
	machine_menu.print_more_btn  = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.more_btn		 = MORE_BTN_TITLE_EN;
	machine_menu.MoreButtonConfTitle = MORE_BTN_TITLE_EN;
	machine_menu.moreItem_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_btn1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_btn2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_btn3 = BUTTON3_NAME_EN;			
	machine_menu.moreItem_btn4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_btn5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_btn6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_btn7 = BUTTON7_NAME_EN;
	
	machine_menu.MoreFunctionConfTitle = PRINT_MORE_BTN_TITLE_EN;
	machine_menu.morefunc_cnt = BUTTON_COUNT_EN;
	machine_menu.moreItem_func1 = BUTTON1_NAME_EN;
	machine_menu.moreItem_func2 = BUTTON2_NAME_EN;
	machine_menu.moreItem_func3 = BUTTON3_NAME_EN;			 
	machine_menu.moreItem_func4 = BUTTON4_NAME_EN;
	machine_menu.moreItem_func5 = BUTTON5_NAME_EN;
	machine_menu.moreItem_func6 = BUTTON6_NAME_EN;
	machine_menu.moreItem_func7 = BUTTON7_NAME_EN;

	machine_menu.AutoLevelCmd = AUTOLEVELCMD_EN;
					machine_menu.high_level = MOTOR_EN_HIGH_LEVEL_EN;
					machine_menu.low_level = MOTOR_EN_LOW_LEVEL_EN;
                    //

            
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_EN;
			common_menu.text_back=BACK_TEXT_EN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_EN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_EN;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;			
			//主页面
			main_menu.title=TITLE_READYPRINT_EN;
			main_menu.preheat=PREHEAT_TEXT_EN;
			main_menu.move=MOVE_TEXT_EN;
			main_menu.home=HOME_TEXT_EN;
			main_menu.print=PRINT_TEXT_EN;
			main_menu.extrude=EXTRUDE_TEXT_EN;
			main_menu.leveling=LEVELING_TEXT_EN;
			main_menu.autoleveling=AUTO_LEVELING_TEXT_EN;
			main_menu.fan = FAN_TEXT_EN;
			main_menu.set=SET_TEXT_EN;
			main_menu.more=MORE_TEXT_EN;
			main_menu.tool = TOOL_TEXT_EN;
			//TOOL
			tool_menu.title = TOOL_TEXT_EN;
			tool_menu.preheat = TOOL_PREHEAT_EN;
			tool_menu.extrude = TOOL_EXTRUDE_EN;
			tool_menu.move = TOOL_MOVE_EN;
			tool_menu.home= TOOL_HOME_EN;
			tool_menu.leveling = TOOL_LEVELING_EN;
			tool_menu.autoleveling = TOOL_AUTO_LEVELING_EN;
			tool_menu.filament = TOOL_FILAMENT_EN;
			tool_menu.more = TOOL_MORE_EN;				
			//预热
			preheat_menu.adjust_title = TITLE_ADJUST_EN;
			preheat_menu.title=TITLE_PREHEAT_EN;
			preheat_menu.add=ADD_TEXT_EN;
			preheat_menu.dec=DEC_TEXT_EN;
			preheat_menu.ext1=EXTRUDER_1_TEXT_EN;
			preheat_menu.ext2=EXTRUDER_2_TEXT_EN;
			preheat_menu.hotbed=HEATBED_TEXT_EN;
			preheat_menu.off=CLOSE_TEXT_EN;
			//移动
			move_menu.title = TITLE_MOVE_EN;
			//归零
			home_menu.title=TITLE_HOME_EN;
			home_menu.stopmove = HOME_STOPMOVE_EN;
			//文件目录
			file_menu.title=TITLE_CHOOSEFILE_EN;
			file_menu.page_up=PAGE_UP_TEXT_EN;
			file_menu.page_down=PAGE_DOWN_TEXT_EN;
			file_menu.file_loading = FILE_LOADING_EN;
			file_menu.no_file = NO_FILE_EN;
			file_menu.no_file_and_check = DIALOG_ERROR_TIPS1_EN;//NO_FILE_AND_CHECK_EN;			
			//挤出
			extrude_menu.title=TITLE_EXTRUDE_EN;
			extrude_menu.in=EXTRUDER_IN_TEXT_EN;
			extrude_menu.out=EXTRUDER_OUT_TEXT_EN;
			extrude_menu.ext1=EXTRUDER_1_TEXT_EN;
			extrude_menu.ext2=EXTRUDER_2_TEXT_EN;
			extrude_menu.low=EXTRUDE_LOW_SPEED_TEXT_EN;
			extrude_menu.normal=EXTRUDE_MEDIUM_SPEED_TEXT_EN;
			extrude_menu.high=EXTRUDE_HIGH_SPEED_TEXT_EN;
			extrude_menu.temper_text=EXTRUDER_TEMP_TEXT_EN;
			//调平
			leveling_menu.title=TITLE_LEVELING_EN;
			leveling_menu.position1=LEVELING_POINT1_TEXT_EN;
			leveling_menu.position2=LEVELING_POINT2_TEXT_EN;
			leveling_menu.position3=LEVELING_POINT3_TEXT_EN;
			leveling_menu.position4=LEVELING_POINT4_TEXT_EN;
			leveling_menu.position5=LEVELING_POINT5_TEXT_EN;
			leveling_menu.count = LEVELING_POINTS_TEXT_EN;

			//??
			set_menu.title=TITLE_SET_EN;
			set_menu.filesys=FILESYS_TEXT_EN;
			set_menu.wifi=WIFI_TEXT_EN;
			set_menu.about=ABOUT_TEXT_EN;
			set_menu.fan=FAN_TEXT_EN;
			set_menu.filament=FILAMENT_TEXT_EN;
			set_menu.breakpoint=BREAK_POINT_TEXT_EN;
			set_menu.motoroff=MOTOR_OFF_TEXT_EN;
			set_menu.language=LANGUAGE_TEXT_EN;
            set_menu.machine_para = MACHINE_PARA_EN;
			//??
			more_menu.title = TITLE_MORE_EN;
			more_menu.zoffset = ZOFFSET_EN;
			//????
			filesys_menu.title = TITLE_FILESYS_EN;
			filesys_menu.sd_sys = SD_CARD_TEXT_EN;
			filesys_menu.usb_sys = U_DISK_TEXT_EN;
			//WIFI
			wifi_menu.title=WIFI_TEXT;
			//wifi_menu.key = WIFI_KEY_TEXT_EN;
			//wifi_menu.ip = WIFI_IP_TEXT_EN;
			//wifi_menu.state= WIFI_STA_TEXT_EN;
			wifi_menu.cloud= CLOUD_TEXT_EN;
//			wifi_menu.reconnect = WIFI_RECONNECT_TEXT_EN;

			cloud_menu.title = TITLE_CLOUD_TEXT_EN;
			cloud_menu.bind = CLOUD_BINDED_EN;
			cloud_menu.binded = CLOUD_BINDED_EN;
			cloud_menu.unbind = CLOUD_UNBIND_EN;
			cloud_menu.unbinding = CLOUD_UNBINDED_EN;
			cloud_menu.disconnected = CLOUD_DISCONNECTED_EN;
			cloud_menu.disable = CLOUD_DISABLE_EN;
			//??
			about_menu.title = TITLE_ABOUT_EN;
			about_menu.type = ABOUT_TYPE_TEXT_EN;
			about_menu.version = ABOUT_VERSION_TEXT_EN;
			about_menu.wifi = ABOUT_WIFI_TEXT_EN;			
			//??
			fan_menu.title = TITLE_FAN_EN;
			fan_menu.add = FAN_ADD_TEXT_EN;
			fan_menu.dec = FAN_DEC_TEXT_EN;
			fan_menu.state = FAN_TIPS1_TEXT_EN;
			//??
			filament_menu.title = TITLE_FILAMENT_EN;
			filament_menu.in = FILAMENT_IN_TEXT_EN;
			filament_menu.out = FILAMENT_OUT_TEXT_EN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_EN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_EN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_EN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_EN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_EN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_EN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_EN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_EN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_EN;

			//??
			language_menu.title = TITLE_LANGUAGE_EN;
			language_menu.next = PAGE_DOWN_TEXT_EN;
			language_menu.up = PAGE_UP_TEXT_EN;			
			//??????
			printing_menu.title = TITLE_PRINTING_EN;
			printing_menu.option = PRINTING_OPERATION_EN;
			printing_menu.stop = PRINTING_STOP_EN;
			printing_menu.pause = PRINTING_PAUSE_EN;
			printing_menu.resume = PRINTING_RESUME_EN;

			//????
			operation_menu.title = TITLE_OPERATION_EN;
			operation_menu.pause = PRINTING_PAUSE_EN;
			operation_menu.stop = PRINTING_STOP_EN;
			operation_menu.temp = PRINTING_TEMP_EN;
			operation_menu.fan = FAN_TEXT_EN;
			operation_menu.extr = PRINTING_EXTRUDER_EN;
			operation_menu.speed = PRINTING_CHANGESPEED_EN;			
			operation_menu.filament= FILAMENT_TEXT_EN;
			operation_menu.more = PRINTING_MORE_EN;
			operation_menu.move = PRINTING_MOVE_EN;
			operation_menu.auto_off = AUTO_SHUTDOWN_EN;
			operation_menu.manual_off = MANUAL_SHUTDOWN_EN;			
			//????
			pause_menu.title= TITLE_PAUSE_EN;
			pause_menu.resume = PRINTING_RESUME_EN;
			pause_menu.stop = PRINTING_STOP_EN;
			pause_menu.extrude = PRINTING_EXTRUDER_EN;
			pause_menu.move = PRINTING_MOVE_EN;
			pause_menu.filament = FILAMENT_TEXT_EN;
			pause_menu.more = PRINTING_MORE_EN;

			//????
			speed_menu.title = TITLE_CHANGESPEED_EN;
			speed_menu.add = ADD_TEXT_EN;
			speed_menu.dec = DEC_TEXT_EN;
			speed_menu.move = MOVE_SPEED_EN;
			speed_menu.extrude = EXTRUDER_SPEED_EN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_EN;
			speed_menu.move_speed = MOVE_SPEED_STATE_EN;
			//???---????
			printing_more_menu.title = TITLE_MORE_EN;
			printing_more_menu.fan = FAN_TEXT_EN;
			printing_more_menu.auto_close = AUTO_SHUTDOWN_EN;
			printing_more_menu.manual = MANUAL_SHUTDOWN_EN;
			printing_more_menu.speed = PRINTING_CHANGESPEED_EN;
			printing_more_menu.temp = PRINTING_TEMP_EN;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_EN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_EN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_EN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_EN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_EN;
			print_file_dialog_menu.retry = DIALOG_RETRY_EN;
			print_file_dialog_menu.stop = DIALOG_STOP_EN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_EN;	
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_EN;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_EN;
            		print_file_dialog_menu.filament_no_press=DIALOG_FILAMENT_NO_PRESS_EN;
//			print_file_dialog_menu.print_finish=DIALOG_PRINT_FINISH_EN;
//			print_file_dialog_menu.print_time=DIALOG_PRINT_TIME_EN;
//			print_file_dialog_menu.reprint=DIALOG_REPRINT_EN;
			print_file_dialog_menu.wifi_enable_tips=DIALOG_WIFI_ENABLE_TIPS_EN;
			//ZOFFSET
			zoffset_menu.title = TITLE_ZOFFSET_EN;
			zoffset_menu.inc = ZOFFSET_INC_EN;
			zoffset_menu.dec = ZOFFSET_DEC_EN;
		break;
	}
}

