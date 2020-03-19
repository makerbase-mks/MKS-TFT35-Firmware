#ifndef _PIC_H_
#define _PIC_H_

#if defined(__cplusplus)
extern "C" { 
#endif

#define VERSION_WITH_PIC	1

//** extern unsigned char bmp_public_buf[16 * 1024];
extern unsigned char bmp_public_buf[32 * 1024];
extern GUI_BITMAP bmp_struct;
extern GUI_BITMAP bmp_struct_92;
extern GUI_BITMAP bmp_struct_50;
extern GUI_BITMAP bmp_struct_100;
extern GUI_BITMAP bmp_struct_150;
extern uint8_t drawicon_preview(char *path,int xsize_small,int ysize_small);
extern const unsigned char gImage_checkbos[200];
extern uint8_t have_pre_pic(char *path);

#if VERSION_WITH_PIC	
#if 0
//extern const unsigned char gImage_logo[76800];
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extructIn;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extructOut;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_fan;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_fan_move;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_machine;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_pause;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_stop;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_wifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_xAdd;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_xDec;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_yAdd;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_yDec;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zAdd;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zDec;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_about;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_preHeat;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_add;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_dec;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_dir;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extruct;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_file;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_mov;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_mov_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_pageDown;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_pageUp;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_printing;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_return;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_set;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zero;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_connect;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zeroA;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zeroX;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zeroY;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_zeroZ;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_step;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_connect;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru1;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru2;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_addH;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_decH;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_usb;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_sd;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_norm;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_delta;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_bed;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_bed_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_lang;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_speed;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_adj;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_menu;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru1H;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru2H;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_step_move;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_step_extru;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_speed_extru;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru1_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extru2_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_resume;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_norm_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_delta_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_speed127;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_speed255;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_speed0;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_sd_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_usb_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud115200;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud115200_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud250000;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud250000_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud9600;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_baud9600_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_en;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_en_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_simple;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_simple_sel;
extern GUI_CONST_STORAGE GUI_BITMAP bmbmp_extruct_sel;


#if 0
extern const unsigned char gImage_preHeatIcon[3024];

extern const unsigned char gImage_return[3024];

extern const unsigned char gImage_file[3024];

extern const unsigned char gImage_dir[3024];

extern const unsigned char gImage_print[3024];

extern const unsigned char gImage_pageDown[3024];

extern const unsigned char gImage_pageUp[3024];

extern const unsigned char gImage_set[3024];

extern const unsigned char gImage_add[3024];

extern const unsigned char gImage_dec[3024];

extern const unsigned char gImage_zero[3024];

extern const unsigned char gImage_move[3024];

extern const unsigned char gImage_extru[3024];

extern const unsigned char gImage_wifi[3024];
#endif

#endif

#endif
#if defined(__cplusplus)
}
#endif

#endif


