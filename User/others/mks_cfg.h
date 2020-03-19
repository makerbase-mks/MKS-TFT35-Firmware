#ifndef _MKS_CFG_H_
#define _MKS_CFG_H_

#include "stdint.h"
#include "fontLib.h"



#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef struct
{
	volatile int8_t custom_pic_flag;
	
	volatile int32_t background_color; //èƒŒæ™¯é¢œè‰²
	volatile int32_t title_color; //æ ‡é¢˜é¢œè‰²
	volatile int32_t state_background_color; //çŠ¶æ€æ˜¾ç¤ºèƒŒæ™¯é¢œè‰?
	volatile int32_t state_text_color; //çŠ¶æ€æ˜¾ç¤ºæ–‡å­—é¢œè‰²é¢œè‰?
	volatile int32_t filename_color; //æ–‡ä»¶åæ–‡å­—é¢œè‰?
	volatile int32_t filename_background_color; //æ–‡ä»¶åèƒŒæ™¯é¢œè‰?
	volatile int32_t printingstate_word_background_color;
	volatile int32_t printingstate_word_color;
	volatile int32_t btn_color;
	volatile int32_t btn_textcolor;
	volatile int32_t btn_state_color;
	volatile int32_t btn_state_textcolor;
	volatile int32_t btn_state_sel_color;
	volatile int32_t btn_state_sel_textcolor;
	volatile int32_t back_btn_color;
	volatile int32_t back_btn_textcolor;
	volatile int32_t printing_bar_color_left;
	volatile int32_t printing_bar_color_right;
	volatile int32_t printing_bar_text_color_left;
	volatile int32_t printing_bar_text_color_right;
	volatile int32_t dialog_btn_color;
	volatile int32_t dialog_btn_textcolor;
	volatile int32_t printfile_color;
	volatile int32_t printfile_textcolor;
	
	volatile float curPos[3];
	volatile float curSprayerTemp[2];	// 2¸öÅçÍ·ÎÂ¶È
	volatile float curBedTemp;	//ÈÈ´²ÎÂ¶È
	volatile float desireSprayerTemp[2];// 2¸öÅçÍ·Ä¿±êÎÂ¶È
	volatile float desireBedTemp;// ÈÈ´²Ä¿±êÎÂ¶È
	volatile float desireSprayerTempBak_1[2];

	volatile float preheat_desireSprayerTemp[2];// 2¸öÅçÍ·Ä¿±êÎÂ¶È
	volatile float preheat_desireBedTemp;// ÈÈ´²Ä¿±êÎÂ¶È


	volatile int8_t curSprayerChoose;	//µ±Ç°Ñ¡ÔñµÄÅçÍ·
	volatile int8_t curSprayerChoose_bak;
	volatile int8_t curTempType;		//ÅçÍ·1¡¢ÅçÍ·2¡¢ÈÈ´²
	volatile int8_t stepHeat;	//?¡è¨¨¨¨2???
	volatile int8_t fanOnoff; //·çÉÈ¿ª¹Ø
	volatile uint8_t fanSpeed;	//·çÉÈËÙ¶È
	volatile int8_t sprayerNum; // ÅçÍ·Êý
	volatile int8_t machineType; //»úÐÍ
	volatile uint16_t printSpeed;		//´òÓ¡ËÙ¶È
	volatile uint16_t printExtSpeed0;		//´òÓ¡ÆÚ¼ä¼·³öËÙ¶È
	volatile uint16_t printExtSpeed1;		//´òÓ¡ÆÚ¼ä¼·³öËÙ¶È
	volatile uint8_t stepPrintSpeed;	//´òÓ¡ËÙ¶Èµ÷Õû²½½ø
	volatile int8_t extruStep;	//?¡¤3??¨´?¨¨
	volatile int8_t extruSpeed;	//¼·³öËÙ¶È
	volatile int16_t moveSpeed;	//ÒÆ¶¯ËÙ¶È
	volatile float move_dist;		//ÒÆ¶¯¾àÀë
	volatile int8_t language;	//ÓïÑÔ
	volatile int8_t baud;		//²¨ÌØÂÊ
	
	volatile int8_t fileSysType; //ÎÄ¼þÏµÍ³ÀàÐÍ
	volatile uint8_t touch_adj_flag; //´¥ÃþÆÁÐ£Õý±êÖ¾Î»
	volatile int32_t touch_adj_xMin;
	volatile int32_t touch_adj_xMax;
	volatile int32_t touch_adj_yMin;
	volatile int32_t touch_adj_yMax;

	volatile uint8_t button_3d_effect_flag;
	volatile uint8_t have_ups;
	
	volatile int16_t	pause_xpos;
	volatile int16_t pause_ypos;
	volatile int16_t pause_zpos;

	volatile uint8_t MoreItem_pic_cnt;

	volatile uint8_t func_btn1_display_flag;
	volatile uint8_t func_btn2_display_flag;
	volatile uint8_t func_btn3_display_flag;

	volatile uint8_t extern_chinese_flg;//Íâ²¿×Ö¿â¡£

	volatile uint8_t print_finish_close_machine_flg;	

	//volatile uint32_t filamentchange_speed;//»»ÁÏËÙ¶È
	//volatile uint8_t filamentchange_step;//»»ÁÏ²½½ø	
	//volatile uint32_t filament_limit_temper;
	
	volatile uint8_t morefunc_cnt;
	
	volatile uint16_t filament_load_speed;//»»ÁÏËÙ¶È
	volatile uint16_t filament_load_length;//»»ÁÏ²½½ø
	//uint16_t filament_load_limit_temper;//»»ÁÏµÄ×îµÍÎÂ¶ÈÖµ
	volatile uint16_t filament_loading_time;
	volatile uint16_t filament_unload_speed;
	volatile uint16_t  filament_unload_length;
	volatile uint16_t filament_limit_temper;
	volatile uint16_t filament_unloading_time;

	volatile uint8_t leveling_mode;//µ÷Æ½Ä£Ê½0:ÊÖ¶¯µ÷Æ½£¬1:×Ô¶¯µ÷Æ½
	volatile uint8_t leveling_point_number;//ÊÖ¶¯µ÷Æ½ÉèÖÃ×ø±êÊý(¿ÉÉè3/4/5Èý¸öÖµ)
	
	volatile int32_t leveling_point1_x;
	volatile int32_t leveling_point1_y;
	volatile int32_t leveling_point2_x;
	volatile int32_t leveling_point2_y;
	volatile int32_t leveling_point3_x;
	volatile int32_t leveling_point3_y;
	volatile int32_t leveling_point4_x;
	volatile int32_t leveling_point4_y;
	volatile int32_t leveling_point5_x;
	volatile int32_t leveling_point5_y;		
	
	volatile int32_t leveling_z_speed;
	volatile int32_t leveling_xy_speed;

	//tan 
	volatile uint8_t temperature_ctrl_err;

	volatile uint8_t language_bak;
	volatile uint8_t sd_save_flg;
	volatile int16_t leveling_z_high;
	/******************************************add***************/
	volatile uint8_t rePrintFlag;
	volatile uint8_t pwrdn_mtrdn_level_flg;//¶ÏµçµçÁÏÂß¼­µçÆ½±êÖ¾£¬1:¶Ë¿ÚÄ¬ÈÏÎª¸ßµçÆ½£¬0:¶Ë¿ÚÄ¬ÈÏÎªµÍµçÆ½
	volatile int16_t Pause_ZADD;
	volatile int16_t Pause_XPOS;
	volatile int16_t Pause_YPOS;
	volatile uint8_t pre_fanSpeed;//Ô¤Éè·ç»úËÙ¶È
	//volatile uint8_t wifi_mode_sel;//wifiÄ£Ê½Ñ¡Ôñ¡£
	volatile uint8_t custom_bed_flag;//ÈÈ´²¶¨ÖÆ
	volatile uint8_t firmware_type;//Ö÷°å¹Ì¼þÀàÐÍ¡£1:marlin;2:repetier;3:smoothie
	volatile uint16_t preheat_max_desireSprayerTemp;//ÅçÍ·×î´óÄ¿±êÎÂ¶È
	volatile uint16_t preheat_max_desireBedTemp;//ÈÈ´²×î´óÄ¿±êÎÂ¶È
	volatile float curSprayerTempBak[2];
	volatile float desireSprayerTempBak[2];
	volatile float curBedTempBak;
	volatile volatile float desireBedTempBak;
	volatile uint8_t pwd_reprint_flg;
	volatile float breakpoint_z_error;

	volatile uint8_t findpoint_start;
	volatile float	z_current_position;
	volatile float	find_z_current_position;
	volatile unsigned char z_display_pos[21];
	volatile unsigned char z_display_pos_bak[21];
	unsigned char F_speed[21];
	volatile unsigned char pwroff_save_mode;
	volatile unsigned char sd_saving;
	volatile uint8_t getzpos_flg;
	volatile uint8_t getzpos_enable;
	volatile float zpos;//zÖá×ø±êÖµ
	volatile unsigned char move_z_coordinate[20];

	volatile uint8_t insert_det_module;// 1:½ÓÈë220detÄ£¿é£¬ÆäËûÖµ:½ÓPWC¹Ø»úÄ£¿é¡£PWC¿ÉÒÔÌæ´ú220detÄ£¿é¡£

	volatile uint8_t filament_det1_level_flg;// ¶ÏÁÏ¼ì²â1£»1:¸ßµçÆ½´¥·¢£¬0µÍµçÆ½´¥·¢¡£
	volatile uint8_t filament_det2_level_flg;// ¶ÏÁÏ¼ì²â2£»1:¸ßµçÆ½´¥·¢£¬0µÍµçÆ½´¥·¢¡
	volatile uint8_t multiple_language;
	volatile uint8_t overturn_180;	 //ÆÁÄ»·­×ª180¡ã

	volatile char wifi_ap[32];	//wifiÍøÂçÃû³Æ×Ö·û´®
	volatile char wifi_key[64]; //wifiÃÜÂë×Ö·û´®
	volatile uint8_t wifi_mode_sel;
	uint8_t wifi_type; // HLK: 0x01 , ESP: 0X02

	volatile char cloud_enable;	
	volatile char cloud_hostUrl[96];	//ÔÆÁ¬½ÓµØÖ·
	volatile int cloud_port;		//ÔÆÁ¬½Ó¶Ë¿Ú

	volatile float Zoffset;
	volatile float stepZoffset;
	volatile uint8_t zoffset_display_flg;
	volatile uint8_t quickstop_display_flg;

	volatile uint8_t display_style;
	volatile uint8_t mask_PB0_PB1_Function;
	volatile uint8_t btn_text_offset;//°´Å¥×ÖÌåÆ«ÒÆµ×±ßÎ»ÖÃ

	volatile uint8_t add_checkSum;   //M110ÊÇ·ñ¼ÓÐ£Ñé±êÖ¾Î»
	volatile uint8_t display_error;   //ÏÔÊ¾±¨´íÐÅÏ¢±êÖ¾Î» 
	volatile uint8_t restart_data_init; //resend 5´ÎºóÖØÐÂ³õÊ¼»¯SD¿¨±êÖ¾Î»
	volatile uint8_t has_flash_pre_view;//ÓÐÍ¼Æ¬Ô¤ÀÀ
	volatile uint8_t baby_step_display_flg;
	volatile uint8_t calibrate_disp_flag;

	volatile uint8_t zoffset_disp_flag;
	volatile uint8_t disp_zoffset_buf[30];
	/*******************************************end**************/

} CFG_ITMES;


extern CFG_ITMES gCfgItems;

typedef struct
{
	volatile uint32_t cfg_baudrate;
	volatile uint8_t  cfg_drive_system;
	volatile uint8_t  cfg_ext0_tempsensor_type;
	volatile uint8_t  cfg_ext1_tempsensor_type;
	volatile uint8_t  cfg_heated_bed_sensor_type;

	volatile float cfg_axis_steps_per_mm;
	volatile float cfg_xaxis_steps_per_mm;
	volatile float cfg_yaxis_steps_per_mm;
	volatile float cfg_zaxis_steps_per_mm;
	volatile float cfg_ext0_steps_per_mm;
	volatile float cfg_ext1_steps_per_mm;

	volatile float cfg_max_feedrate_x;
	volatile float cfg_max_feedrate_y;
	volatile float cfg_max_feedrate_z;
	volatile float cfg_max_feedrate_e0;
	volatile float cfg_max_feedrate_e1;
	
	volatile float cfg_max_acceleration_units_per_sq_second_x;
	volatile float cfg_max_acceleration_units_per_sq_second_y;
	volatile float cfg_max_acceleration_units_per_sq_second_z;
	volatile float cfg_max_acceleration_e0;
	volatile float cfg_max_acceleration_e1;

	volatile float cfg_max_travel_acceleration_units_per_sq_second_x;
	volatile float cfg_max_travel_acceleration_units_per_sq_second_y;
	volatile float cfg_max_travel_acceleration_units_per_sq_second_z;

	volatile float cfg_homing_feedrate_x;
	volatile float cfg_homing_feedrate_y;
	volatile float cfg_homing_feedrate_z;
	
	volatile float cfg_ext_mintemp;	
	volatile float cfg_ext_maxtemp;
	volatile float cfg_heated_bed_maxtemp;
	
	volatile float cfg_ui_set_maxtemp;
	volatile float cfg_ui_set_heated_bed_maxtemp;

	volatile int8_t cfg_num_extruder;
	volatile int8_t cfg_have_heated_bed;

	volatile int8_t cfg_invert_x_dir;
	volatile int8_t cfg_invert_y_dir;
	volatile int8_t cfg_invert_z_dir;
	volatile int8_t cfg_invert_e0_dir;
	volatile int8_t cfg_invert_e1_dir;

	volatile int8_t cfg_homing_order;
	volatile int8_t cfg_x_home_dir;
	volatile int8_t cfg_y_home_dir;
	volatile int8_t cfg_z_home_dir;
				
	volatile float	cfg_x_max_length;
	volatile float	cfg_y_max_length;
	volatile float	cfg_z_max_length;
	volatile float	cfg_x_min_pos;
	volatile float	cfg_y_min_pos;
	volatile float	cfg_z_min_pos;	

	volatile uint8_t cfg_endstop_x_min_inverting;
	volatile uint8_t cfg_endstop_y_min_inverting;
	volatile uint8_t cfg_endstop_z_min_inverting;
	volatile uint8_t cfg_endstop_x_max_inverting;
	volatile uint8_t cfg_endstop_y_max_inverting;
	volatile uint8_t cfg_endstop_z_max_inverting;

	volatile uint8_t cfg_min_hardware_endstop_x;
	volatile uint8_t cfg_min_hardware_endstop_y;
	volatile uint8_t cfg_min_hardware_endstop_z;
	volatile uint8_t cfg_max_hardware_endstop_x;
	volatile uint8_t cfg_max_hardware_endstop_y;
	volatile uint8_t cfg_max_hardware_endstop_z;

	volatile uint8_t cfg_min_software_endstop_x;
	volatile uint8_t cfg_min_software_endstop_y;
	volatile uint8_t cfg_min_software_endstop_z;
	volatile uint8_t cfg_max_software_endstop_x;
	volatile uint8_t cfg_max_software_endstop_y;
	volatile uint8_t cfg_max_software_endstop_z;

	volatile float cfg_delta_max_radius;
	volatile float cfg_printer_radius;
	volatile float cfg_delta_diagonal_rod;
	volatile float cfg_delta_floor_safety_margin_mm;
	
	volatile uint8_t cfg_feature_z_probe;
	volatile uint8_t cfg_bed_leveling_method;
	volatile float cfg_z_probe_height;
	volatile float cfg_z_probe_x1;
	volatile float cfg_z_probe_y1;
	volatile float cfg_z_probe_x2;
	volatile float cfg_z_probe_y2;
	volatile float cfg_z_probe_x3;
	volatile float cfg_z_probe_y3;
	volatile float cfg_end_effector_horizontal_offset;
	volatile float cfg_carriage_horizontal_offset;
	volatile float cfg_rod_radius;
	volatile float cfg_bed_leveling_grid_size;
	volatile float cfg_z_probe_speed;
	volatile float cfg_z_probe_xy_speed;

	volatile uint32_t cfg_stepper_high_delay;
	volatile uint8_t cfg_print_auto_close;

	volatile uint8_t cfg_x_enable_on;
	volatile uint8_t cfg_y_enable_on;
	volatile uint8_t cfg_z_enable_on;
	volatile uint8_t cfg_e0_enable_on;
	volatile uint8_t cfg_e1_enable_on;
}CFG_PRINTER_ITMES;

extern CFG_PRINTER_ITMES CfgPrinterItems;

typedef struct 
{
	volatile uint8_t def_ENDSTOP_X_MIN_INVERTING;
	volatile uint8_t def_ENDSTOP_Y_MIN_INVERTING;
	volatile uint8_t def_ENDSTOP_Z_MIN_INVERTING;
	volatile uint8_t def_ENDSTOP_X_MAX_INVERTING;
	volatile uint8_t def_ENDSTOP_Y_MAX_INVERTING;
	volatile uint8_t def_ENDSTOP_Z_MAX_INVERTING;

	volatile uint8_t def_MIN_HARDWARE_ENDSTOP_X;
	volatile uint8_t def_MIN_HARDWARE_ENDSTOP_Y;
	volatile uint8_t def_MIN_HARDWARE_ENDSTOP_Z;
	volatile uint8_t def_MAX_HARDWARE_ENDSTOP_X;
	volatile uint8_t def_MAX_HARDWARE_ENDSTOP_Y;
	volatile uint8_t def_MAX_HARDWARE_ENDSTOP_Z;

	volatile uint8_t def_min_software_endstop_x;
	volatile uint8_t def_min_software_endstop_y;
	volatile uint8_t def_min_software_endstop_z;
	volatile uint8_t def_max_software_endstop_x;
	volatile uint8_t def_max_software_endstop_y;
	volatile uint8_t def_max_software_endstop_z;	

	volatile uint8_t def_SUPPORT_MAX6675;
	volatile uint8_t def_SUPPORT_MAX31855;


	volatile uint8_t def_ANALOG_INPUTS;
	volatile uint8_t def_EXT0_ANALOG_INPUTS;
	volatile uint8_t def_EXT0_SENSOR_INDEX;
	volatile uint8_t def_EXT0_ANALOG_CHANNEL;
	
	volatile uint8_t def_EXT1_ANALOG_INPUTS;
	volatile uint8_t def_EXT1_SENSOR_INDEX;
	volatile uint8_t def_EXT1_ANALOG_CHANNEL;
	
	volatile uint8_t def_EXT2_ANALOG_INPUTS;
	volatile uint8_t def_EXT2_SENSOR_INDEX;
	volatile uint8_t def_EXT2_ANALOG_CHANNEL;
	
	volatile uint8_t def_EXT3_ANALOG_INPUTS;
	volatile uint8_t def_EXT3_SENSOR_INDEX;
	volatile uint8_t def_EXT3_ANALOG_CHANNEL;
	
	volatile uint8_t def_EXT4_ANALOG_INPUTS;
	volatile uint8_t def_EXT4_SENSOR_INDEX;
	volatile uint8_t def_EXT4_ANALOG_CHANNEL;
	
	volatile uint8_t def_EXT5_ANALOG_INPUTS;
	volatile uint8_t def_EXT5_SENSOR_INDEX;
	volatile uint8_t def_EXT5_ANALOG_CHANNEL;	
	
	volatile uint8_t def_BED_ANALOG_INPUTS;
	volatile uint8_t def_BED_SENSOR_INDEX;
	volatile uint8_t def_BED_ANALOG_CHANNEL;
	
	volatile uint8_t def_THERMO_ANALOG_INDEX;
	volatile uint8_t def_THERMO_ANALOG_INPUTS;
	volatile uint8_t def_THERMO_ANALOG_CHANNEL;
	
	volatile uint8_t def_KEYPAD_ANALOG_INPUTS;
	volatile uint8_t def_KEYPAD_ANALOG_INDEX;
	volatile uint8_t def_KEYPAD_ANALOG_CHANNEL;

	volatile uint8_t def_PWM_BOARD_FAN;
	volatile uint8_t def_PWM_FAN1;
	volatile uint8_t def_PWM_FAN2;
	volatile uint8_t def_PWM_FAN_THERMO;

	volatile uint8_t def_NUM_TEMPERATURE_LOOPS;

	
	volatile float def_DELTA_DIAGONAL_ROD;
	volatile float	def_DELTA_ALPHA_A;
	volatile float	def_DELTA_ALPHA_B;
	volatile float	def_DELTA_ALPHA_C;
	volatile float	def_DELTA_RADIUS_CORRECTION_A;
	volatile float	def_DELTA_RADIUS_CORRECTION_B;
	volatile float	def_DELTA_RADIUS_CORRECTION_C;
	volatile float	def_DELTA_DIAGONAL_CORRECTION_A;
	volatile float	def_DELTA_DIAGONAL_CORRECTION_B;
	volatile float	def_DELTA_DIAGONAL_CORRECTION_C;
	volatile float	def_DELTA_MAX_RADIUS;
	volatile float	def_DELTA_FLOOR_SAFETY_MARGIN_MM;
	volatile float	def_END_EFFECTOR_HORIZONTAL_OFFSET;
	volatile float	def_CARRIAGE_HORIZONTAL_OFFSET;
	volatile float	def_PRINTER_RADIUS;
	volatile float	def_DELTA_HOME_ON_POWER;
	volatile float	def_DELTA_X_ENDSTOP_OFFSET_STEPS;
	volatile float	def_DELTA_Y_ENDSTOP_OFFSET_STEPS;
	volatile float	def_DELTA_Z_ENDSTOP_OFFSET_STEPS;

	volatile uint8_t def_NONLINEAR_SYSTEM;

	volatile float def_ENDSTOP_X_BACK_MOVE;
	volatile float def_ENDSTOP_Y_BACK_MOVE;
	volatile float def_ENDSTOP_Z_BACK_MOVE;
	volatile float def_ENDSTOP_X_BACK_ON_HOME;
	volatile float def_ENDSTOP_Y_BACK_ON_HOME;
	volatile float def_ENDSTOP_Z_BACK_ON_HOME;
	
}PRINTER_DEFINE;

extern PRINTER_DEFINE Change_Repetier_Define;

extern void cfg_init();
//extern void define_value_init();
extern uint8_t  DecStr2Float(int8_t * buf,  float  *result);

#if 0
#define LANG_SIMPLE_CHINESE		1
#define LANG_COMPLEX_CHINESE	2
#define LANG_ENGLISH			3
#endif

#define FONT_BUTTON	GUI_FontHZ_fontHz14
#define FONT_STATE_INF	GUI_FontHZ_fontHz14
#define FONT_TITLE		GUI_FontHZ_fontHz14


void printer_init();
void get_sd_cfg();

void recover_cfg_inf_tft();
#define MAX_SPRAYER_TEMP			270//300
#define MAX_BED_TEMP				150

#ifndef  _BAK_CFG_INF_H_
#define  _BAK_CFG_INF_H_

#define  BAK_INF_VALID_FLAG			0x76313136//acsii --> V115   //0xaa558761

#define  BAK_VALID_FLAG_ADDR			0
#define  BAK_BAUDRATE_ADDR				BAK_VALID_FLAG_ADDR + 4
#define  BAK_LANGUARY_ADDR				BAK_BAUDRATE_ADDR + 1
#define  BAK_MOV_SPEED_ADDR			BAK_LANGUARY_ADDR + 1
#define  BAK_MOV_DIST_ADDR				BAK_MOV_SPEED_ADDR + 2
#define  BAK_EXTRU_SPEED_ADDR		BAK_MOV_DIST_ADDR + 2
#define  BAK_MACHINE_TYPE_ADDR	BAK_EXTRU_SPEED_ADDR + 2
#define  BAK_SPRAYER_NUM_ADDR		BAK_MACHINE_TYPE_ADDR + 1
#define  BAK_FAN_SPEED_ADDR			BAK_SPRAYER_NUM_ADDR + 1
#define  BAK_FILE_SYS_ADDR				BAK_FAN_SPEED_ADDR + 1

//#define  BAK_TOUCH_ADJ_FLAG_ADDR		BAK_FILE_SYS_ADDR + 1
//#define  BAK_TOUCH_ADJ_XMAX_ADDR		BAK_TOUCH_ADJ_FLAG_ADDR + 1
//#define  BAK_TOUCH_ADJ_XMIN_ADDR		BAK_TOUCH_ADJ_XMAX_ADDR + 4
//#define  BAK_TOUCH_ADJ_YMAX_ADDR		BAK_TOUCH_ADJ_XMIN_ADDR + 4
//#define  BAK_TOUCH_ADJ_YMIN_ADDR		BAK_TOUCH_ADJ_YMAX_ADDR + 4

//#define  BAK_CUSTOM_PIC_ADDR			BAK_TOUCH_ADJ_YMIN_ADDR + 4

#define  BAK_BACKGROUND_COLOR_ADD							BAK_FILE_SYS_ADDR + 1
#define  BAK_TITIL_COLOR_ADD									BAK_BACKGROUND_COLOR_ADD + 4
#define  BAK_STATE_BKCOLOR_ADD							BAK_TITIL_COLOR_ADD + 4
#define  BAK_STATE_TEXTCOLOR_ADD						BAK_STATE_BKCOLOR_ADD + 4
#define  BAK_FILENAME_BKCOLOR_ADD						BAK_STATE_TEXTCOLOR_ADD + 4
#define  BAK_FILENAME_TEXTCOLOR_ADD					BAK_FILENAME_BKCOLOR_ADD + 4
#define  BAK_BTN_BKCOLOR_ADD									BAK_FILENAME_TEXTCOLOR_ADD + 4	
#define  BAK_BTN_TEXTCOLOR_ADD							BAK_BTN_BKCOLOR_ADD + 4
#define  BAK_STATE_BTN_BKCOLOR_ADD					BAK_BTN_TEXTCOLOR_ADD + 4
#define  BAK_STATE_BTN_TEXTCOLOR_ADD				BAK_STATE_BTN_BKCOLOR_ADD + 4
#define  BAK_BACK_BTN_BKCOLOR_ADD						BAK_STATE_BTN_TEXTCOLOR_ADD + 4
#define  BAK_BACK_BTN_TEXTCOLOR_ADD					BAK_BACK_BTN_BKCOLOR_ADD + 4
#define  BAK_SEL_BTN_BKCOLOR_ADD						BAK_BACK_BTN_TEXTCOLOR_ADD + 4
#define  BAK_SEL_BTN_TEXTCOLOR_ADD					BAK_SEL_BTN_BKCOLOR_ADD + 4
#define  BAK_DIALOG_BTN_BKCOLOR_ADD					BAK_SEL_BTN_TEXTCOLOR_ADD + 4
#define  BAK_DIALOG_BTN_TEXTCOLOR_ADD				BAK_DIALOG_BTN_BKCOLOR_ADD + 4

#define  BAK_MOREITEM_PIC_CNT					BAK_DIALOG_BTN_TEXTCOLOR_ADD + 4
#define	 BAK_CUSTOM_BED_FLAG_ADDR			BAK_MOREITEM_PIC_CNT+1
#define	 BAK_BUTTON_3D_EFFECT_FLAG		BAK_CUSTOM_BED_FLAG_ADDR+1
#define	 BAK_FIRMWARETYPE_ADDR				BAK_BUTTON_3D_EFFECT_FLAG+1

#define	 BAK_PAUSE_XPOS_ADDR						BAK_FIRMWARETYPE_ADDR+1
#define	 BAK_PAUSE_YPOS_ADDR						BAK_PAUSE_XPOS_ADDR+2
#define	 BAK_PAUSE_ZADD_ADDR						BAK_PAUSE_YPOS_ADDR+2

#define	 BAK_FUNC1_DISPLAY_ADDR				BAK_PAUSE_ZADD_ADDR+2
#define	 BAK_FUNC2_DISPLAY_ADDR				BAK_FUNC1_DISPLAY_ADDR+1

//#define	 BAK_PREHEAT_SPRAYER1_TEMP_ADDR		BAK_FUNC2_DISPLAY_ADDR+1
//#define	 BAK_PREHEAT_SPRAYER2_TEMP_ADDR				BAK_PREHEAT_SPRAYER1_TEMP_ADDR+4
//#define	 BAK_PREHEAT_BED_TEMP_ADDR				BAK_PREHEAT_SPRAYER2_TEMP_ADDR+4
#define	 BAK_SPRAYER1_MAXTEMP_ADDR		BAK_FUNC2_DISPLAY_ADDR+1
//#define	 BAK_SPRAYER2_MAXTEMP_ADDR		BAK_SPRAYER1_MAXTEMP_ADDR+4
#define	 BAK_BED_MAXTEMP_ADDR					BAK_SPRAYER1_MAXTEMP_ADDR+2

#define	 BAK_FILAMENT_DET1_FLAG_ADDR					BAK_BED_MAXTEMP_ADDR+2
#define	 BAK_PRINT_FINISH_CLOASE_MACHINE_ADDR		BAK_FILAMENT_DET1_FLAG_ADDR+1
#define  BAK_PRINTING_MOREFUNC_CNT_ADDR					BAK_PRINT_FINISH_CLOASE_MACHINE_ADDR+1

#define BAK_FILAMENT_LOAD_SPEED_ADDR			BAK_PRINTING_MOREFUNC_CNT_ADDR+1
#define BAK_FILAMENT_UNLOAD_SPEED_ADDR		BAK_FILAMENT_LOAD_SPEED_ADDR+2
#define BAK_FILAMENT_LOAD_LENGTH_ADDR			BAK_FILAMENT_UNLOAD_SPEED_ADDR+2
#define BAK_FILAMENT_UNLOAD_LENGTH_ADDR	BAK_FILAMENT_LOAD_LENGTH_ADDR+2
#define BAK_FILAMENT_LIMIT_TERMPER_ADDR 	BAK_FILAMENT_UNLOAD_LENGTH_ADDR+2

#define BAK_LEVELING_POINT_NUMBER_ADDR				BAK_FILAMENT_LIMIT_TERMPER_ADDR+2
#define BAK_LEVELING_POINT1_X_ADDR						BAK_LEVELING_POINT_NUMBER_ADDR+2
#define BAK_LEVELING_POINT1_Y_ADDR						BAK_LEVELING_POINT1_X_ADDR+2
#define BAK_LEVELING_POINT2_X_ADDR						BAK_LEVELING_POINT1_Y_ADDR+2
#define BAK_LEVELING_POINT2_Y_ADDR						BAK_LEVELING_POINT2_X_ADDR+2
#define BAK_LEVELING_POINT3_X_ADDR						BAK_LEVELING_POINT2_Y_ADDR+2
#define BAK_LEVELING_POINT3_Y_ADDR						BAK_LEVELING_POINT3_X_ADDR+2
#define BAK_LEVELING_POINT4_X_ADDR						BAK_LEVELING_POINT3_Y_ADDR+2
#define BAK_LEVELING_POINT4_Y_ADDR						BAK_LEVELING_POINT4_X_ADDR+2
#define BAK_LEVELING_POINT5_X_ADDR						BAK_LEVELING_POINT4_Y_ADDR+2
#define BAK_LEVELING_POINT5_Y_ADDR						BAK_LEVELING_POINT5_X_ADDR+2
#define BAK_LEVELING_Z_SPEED_ADDR							BAK_LEVELING_POINT5_Y_ADDR+2
#define BAK_LEVELING_XY_SPEED_ADDR						BAK_LEVELING_Z_SPEED_ADDR+2
#define BAK_PWROFF_SAVE_MODE_ADDR							BAK_LEVELING_XY_SPEED_ADDR+2
#define BAK_BREAKPOINT_Z_ERROR_ADDR						BAK_PWROFF_SAVE_MODE_ADDR+1
#define BAK_AUTOLEVELING_DISPLAY_ADDR					BAK_BREAKPOINT_Z_ERROR_ADDR+4
#define BAK_FILAMENT_DET2_FLAG_ADDR						BAK_AUTOLEVELING_DISPLAY_ADDR+1
#define BAK_HAVE_UPS_ADDR											BAK_FILAMENT_DET2_FLAG_ADDR+1
#define BAK_INSERT_MODULE_ADDR								BAK_HAVE_UPS_ADDR+1
#define BAK_LEVELING_MODE_ADDR								BAK_INSERT_MODULE_ADDR+1			
#define BAK_PREVIEW_FROM_FLASH_ADDR						BAK_LEVELING_MODE_ADDR+1
#define BAK_MULTIPLE_LANGUAGE_ADDR						BAK_PREVIEW_FROM_FLASH_ADDR+1
#define BAK_QUICKSTOP_DISPLAY_FLG_ADDR				BAK_MULTIPLE_LANGUAGE_ADDR+1
#define BAK_ZOFFSET_DISPLAY_FLG_ADDR					BAK_QUICKSTOP_DISPLAY_FLG_ADDR+1
#define BAK_LEVELING_Z_HIGH_ADDR							BAK_ZOFFSET_DISPLAY_FLG_ADDR+1
#define BAK_SCREEN_DISPLAY_MODE_ADDR					BAK_LEVELING_Z_HIGH_ADDR+4
#define BAK_MASK_PB0_PB1_FUNCTION_ADDR				BAK_SCREEN_DISPLAY_MODE_ADDR+1
#define BAK_BTN_TEXT_OFFSET_ADDR							BAK_MASK_PB0_PB1_FUNCTION_ADDR+1
#define BAK_SCREEN_OVERTURN_180_ADDR					BAK_BTN_TEXT_OFFSET_ADDR+1
#define BAK_CLOUD_FLAG_ADDR                                                    BAK_SCREEN_OVERTURN_180_ADDR+1
#define BAK_M110_ADD_CHECKSUM_ADDR                                    BAK_CLOUD_FLAG_ADDR+1
#define BAK_DISP_EEROR_ADDR  								BAK_M110_ADD_CHECKSUM_ADDR+1
#define BAK_BABY_STEP_DISP_ADDR  								BAK_DISP_EEROR_ADDR+1
#define BAK_CALIBRATE_DISP_FLAG_ADDR						BAK_BABY_STEP_DISP_ADDR+1

#define  BAK_TOUCH_ADJ_FLAG_ADDR		BAK_CALIBRATE_DISP_FLAG_ADDR + 1
#define  BAK_TOUCH_ADJ_XMAX_ADDR		BAK_TOUCH_ADJ_FLAG_ADDR + 1
#define  BAK_TOUCH_ADJ_XMIN_ADDR		BAK_TOUCH_ADJ_XMAX_ADDR + 4
#define  BAK_TOUCH_ADJ_YMAX_ADDR		BAK_TOUCH_ADJ_XMIN_ADDR + 4
#define  BAK_TOUCH_ADJ_YMIN_ADDR		BAK_TOUCH_ADJ_YMAX_ADDR + 4

#define  BAK_FILE_PATH_LEN_ADDR		BAK_TOUCH_ADJ_YMIN_ADDR + 4				
#define  BAK_FILE_PATH_ADDR				BAK_FILE_PATH_LEN_ADDR + 1			

#define MIN_SPRAYER_TEMP			0   //**
#define MIN_BED_TEMP				0
#define MIN_SPRAYER_TEMP			0
#define MAX_SPRAYER_TEMP			270//300
#define MIN_BED_TEMP				0
#define MAX_BED_TEMP				150
#define MIN_EXT_SPEED_PERCENT		10
#define MAX_EXT_SPEED_PERCENT		999

// HC-chen 2017.7.25
#define ON      1
#define OFF     0
#define SD_DET_IP PDin(3)
#define FALA_ON         1
#define FALA_OFF        0
#define SPEAKER   PAout(2)
#define RESET_1963   PDout(6)
#define PULLUP(IO,v)            //{pinMode(IO, (v!=LOW ? INPUT_PULLUP : INPUT)); }
#define ARDUINO 101//?a¨¢?¨¨?¡À¨¤3¨¬¨ª¡§1y¡ê??a¨º?ARDUINO¦Ì?¡ã?¡À?o?

// HC-chen 2017.7.26
#if 0
#define NO_CONTROLLER 0
#define UICONFIG_CONTROLLER 1
#define CONTROLLER_SMARTRAMPS 2
#define CONTROLLER_ADAFRUIT 3
#define CONTROLLER_FOLTYN 4
#define CONTROLLER_VIKI 5
#define CONTROLLER_MEGATRONIC 6
#define CONTROLLER_RADDS 7
#define CONTROLLER_PIBOT20X4 8
#define CONTROLLER_PIBOT16X2 9
#define CONTROLLER_GADGETS3D_SHIELD 10
#define CONTROLLER_REPRAPDISCOUNT_GLCD 11
#define CONTROLLER_FELIX 12
#define CONTROLLER_RAMBO 13
#define CONTROLLER_OPENHARDWARE_LCD2004 14
#define CONTROLLER_SANGUINOLOLU_PANELOLU2 15
#define CONTROLLER_GAMEDUINO2 16
#define CONTROLLER_MIREGLI 17
#define CONTROLLER_GATE_3NOVATICA 18
#define CONTROLLER_SPARKLCD 19
#define CONTROLLER_BAM_DICE_DUE 20
#define CONTROLLER_VIKI2 21
#define CONTROLLER_LCD_MP_PHARAOH_DUE 22
#define CONTROLLER_SPARKLCD_ADAPTER 23
#define CONTROLLER_ZONESTAR 24
#define CONTROLLER_FELIX_DUE 405
#endif

#if 1
/*Gcode command define*/
#define	MOVE_X_COMMAN(buf, x, v)		sprintf(buf, "G1 X%3.1f F%d\n", x, v)
#define	MOVE_Y_COMMAN(buf, y, v)		sprintf(buf, "G1 Y%3.1f F%d\n", y, v)
#define	MOVE_Z_COMMAN(buf, z, v)		sprintf(buf, "G1 Z%3.1f F%d\n", z, v)
#define	MOVE_E_COMMAN(buf, e, v)		sprintf(buf, "G1 E%d F%d\n", e, v)

#define	BABY_STEP_X_COMMAN(buf, x)		sprintf(buf, "M290 X%.2f\n", x)
#define	BABY_STEP_Y_COMMAN(buf, y)		sprintf(buf, "M290 Y%.2f\n", y)
#define	BABY_STEP_Z_COMMAN(buf, z)		sprintf(buf, "M290 Z%.2f\n", z)

#define	SET_EXTRUD_TEM_COMMAND(buf, t)	sprintf(buf, "M104 S%.1f\n", t)
#define	SET_BED_TEM_COMMAND(buf, t)	sprintf(buf, "M140 S%.1f\n", t)
#define	SET_FAN_SPEED_COMMAND(buf, sp)	sprintf(buf, "M106 S%d\n", sp)
#define	SET_MOVE_SPEED_COMMAND(buf, rate)	sprintf(buf, "M220 S%d\n", rate)
#define	SET_EXTRU_SPEED_COMMAND(buf, rate)	sprintf(buf, "M221 S%d\n", rate)

#define	QUICKSTOP_COMMAND		"M410\n"

#define	HOME_X_COMMAND				"G28 X0\n"
#define	HOME_Y_COMMAND				"G28 Y0\n"
#define	HOME_Z_COMMAND				"G28 Z0\n"
#define	HOME_A_COMMAND				"G28\n"
#define	ABSOLUTE_COORD_COMMAN		"G90\n"
#define	RELATIVE_COORD_COMMAN		"G91\n"

#define	GET_CUR_TEM_COMMAND			"M105\n"
#define	SET_FAN_OFF_COMMAND			"M107\n"
#define	WAIT_EXTRUD_TEM_COMMAND	"M109\n"
#define	DISP_CUR_POS_COMMAND		"M114\n"
#define	SAVE_EEPROM_COMMAND			"M500\n"
#define	GET_BABY_ZOFFSET_COMMAND  "M851\n"
#define	GET_BABY_STEP_VALUE_COMMAND  "M290\n"
#endif

//#define SAVE_FROM_SD

typedef enum
{
	BAK_BAUD_ID,
	BAK_LANG_ID,
	BAK_MOV_SPEED_ID,
	BAK_MOV_DIST_ID,
	BAK_EXTRU_SPEED_ID,
	BAK_MACH_TYPE_ID,
	BAK_SPRAY_NUM_ID,
	BAK_FAN_SPEED_ID,
	BAK_FILE_SYS_ID,
	BAK_TOUCH_ADJ_FLAG_ID,
	BAK_TOUCH_ADJ_XMAX_ID,
	BAK_TOUCH_ADJ_XMIN_ID,
	BAK_TOUCH_ADJ_YMAX_ID,
	BAK_TOUCH_ADJ_YMIN_ID,
	BAK_CUSTOM_PIC_ID,
} BAK_INF_ITEM_ID;

void bakup_cfg_inf(BAK_INF_ITEM_ID  cfgItemId, uint32_t  value);//**
void bakup_file_path(uint8_t *path, uint32_t  len);
#define PUTDOWN_TIME	50

//#define OFFSETLENGTH	0x100000	 	//1M
#define OFFSETLENGTH	0x19000	 	//100K	»ØËÝ³¤¶È
	 
#define COORDINATELENGTH	20

#if 0	 
#define  EEPROM_HIGH_ADDR			256
#define  BAK_REPRINT_INFO				EEPROM_HIGH_ADDR - 4			// Ðø´ò±êÖ¾(uint8_t) | ÅçÍ·Ñ¡Ôñ(¸ß4Î») ·çÉÈ¿ª¹Ø×´Ì¬(µÍËÄÎ»)|·çËÙ8Î»| ÈÈ´²ÎÂ¶È8Î»
#define  BAK_REPRINT_OFFSET		BAK_REPRINT_INFO - 4			// offset(uint32_t)
#define  BAK_REPRINT_HTEMP			BAK_REPRINT_OFFSET - 4		// T0Temp(uint16_t)	| T1Temp(uint16_t)
#define  BAK_REPRINT_FAN				BAK_REPRINT_HTEMP - 4		 // BedTemp(uint8_t)	| fanOnoff(uint8_t) |fanSpeed(uint8_t)| null(uint8_t)
#define  BAK_REPRINT_TIME				BAK_REPRINT_FAN - 4			 //hours(int16_t) | minutes(int8_t) ;
#define  BAK_REPRINT_X					BAK_REPRINT_TIME - 4		 // X position
#define  BAK_REPRINT_Y					BAK_REPRINT_X - 4			 //Y position
#define  BAK_REPRINT_Z					BAK_REPRINT_Y - 4			 //Z position
#define  BAK_REPRINT_S					BAK_REPRINT_Z - 4			//null(uint24_t) | saveFlag(uint8_t)
#endif
#endif
//²ÉÓÃÁ¬ÐøÐ´e2promµÄ·½Ê½£¬
//ÖØÐÂ¶¨ÒåÁË¶ÏµçÊý¾ÝµÄ´æ´¢Î»ÖÃ
#define  EEPROM_HIGH_ADDR			256
#define  BAK_REPRINT_TIME			EEPROM_HIGH_ADDR - 4		//hours(int16_t) | minutes(int8_t) ;
#define  BAK_REPRINT_HTEMP		BAK_REPRINT_TIME - 4		// T0Temp(uint16_t)	| T1Temp(uint16_t)
#define  BAK_REPRINT_OFFSET 	BAK_REPRINT_HTEMP - 4		// offset(uint32_t)
#define  BAK_REPRINT_INFO		  BAK_REPRINT_OFFSET - 4	// Ðø´ò±êÖ¾(uint8_t) | ÅçÍ·Ñ¡Ôñ(¸ß4Î») ·çÉÈ¿ª¹Ø×´Ì¬(µÍËÄÎ»)|·çËÙ8Î»| ÈÈ´²ÎÂ¶È8Î»
#define  BAK_REPRINT_X					BAK_REPRINT_INFO - 4		 // X position
#define  BAK_REPRINT_Y					BAK_REPRINT_X - 4			 //Y position
#define  BAK_REPRINT_Z					BAK_REPRINT_Y - 4			 //Z position
#define  BAK_REPRINT_S					BAK_REPRINT_Z - 4			//null(uint24_t) | saveFlag(uint8_t)
#define  BAK_REPRINT_E					BAK_REPRINT_S - 4

#define  BAK_TEST_ADDR					BAK_REPRINT_E-4
#if defined(__cplusplus)
}
#endif

#endif



