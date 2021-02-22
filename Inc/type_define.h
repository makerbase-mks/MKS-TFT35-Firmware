#ifndef _TYPE_DEFINE_H_
#define _TYPE_DEFINE_H_

#if __GNUC__
    #include <stdint.h>
#endif

typedef unsigned int speed_t;

typedef unsigned long ticks_t;
typedef unsigned long millis_t;
typedef int flag8_t;

#ifndef __GNUC__
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
#endif

#endif
