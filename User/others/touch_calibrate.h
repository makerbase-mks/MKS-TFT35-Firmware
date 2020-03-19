#ifndef _TOUCH_CALIBRATE_H_
#define _TOUCH_CALIBRATE_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void Touch_Adjust();
extern void setTouchBound(int32_t x0, int32_t x1, int32_t y0, int32_t y1 );
extern void draw_calibrate();

#if defined(__cplusplus)
}
#endif


#endif


