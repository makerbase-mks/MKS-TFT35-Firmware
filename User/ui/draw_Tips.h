#ifndef _DRAW_TIPS_H_
#define _DRAW_TIPS_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void draw_Tips();
extern void Clear_Tips();



typedef enum
{
	TIPS_TYPE_JOINING,
	TIPS_TYPE_TAILED_JOIN,
	TIPS_TYPE_WIFI_CONECTED
}TIPS_TYPE;
extern TIPS_TYPE tips_type;

typedef struct
{
	unsigned char timer;
	unsigned char timer_count;
}TIPS_DISP;
extern TIPS_DISP tips_disp;

#define TIPS_TIMER_START 1
#define TIPS_TIMER_STOP 0

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif

#endif

