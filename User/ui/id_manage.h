#ifndef _ID_MANAGE_H_
#define _ID_MANAGE_H_

typedef struct
{
	uint32_t id;
	uint8_t flag;
} ID_STACK;

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void init_win_id(void);
extern uint32_t alloc_win_id(void);
extern void del_win_id(int32_t id);

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif

#endif

