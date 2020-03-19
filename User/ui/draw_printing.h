#ifndef _DRAW_PRINTING_H_
#define _DRAW_PRINTING_H_
#include "stdint.h"


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
extern int once_flag;

extern void draw_printing();
extern void Clear_printing();
extern void setProBarValue(int added);
extern void disp_print_time();
extern void disp_printing_speed();
extern void disp_sprayer_tem_printing();
extern void disp_bed_temp_printing();
extern void disp_fan_speed_printing();
extern void disp_printing_speed();
extern void reset_print_time();
extern void setProBarRate(int rate);
extern void disp_fan_move_printing();
extern void start_print_time();
extern void stop_print_time();
extern void print_time_run();
extern void reset_file_info();

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif

#endif

