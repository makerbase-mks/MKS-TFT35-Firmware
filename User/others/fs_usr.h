#ifndef _FS_USR_H_
#define _FS_USR_H_
#include "stdint.h"



#define DISK_USB	0
#define DISK_SD		1

extern void mount_file_sys(uint8_t disk_type);

#endif

