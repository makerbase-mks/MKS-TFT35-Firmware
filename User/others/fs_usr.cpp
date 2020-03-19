#include "fs_usr.h"
#include "ff.h"
#include "fatfs.h"

extern FATFS fs; 
void mount_file_sys(uint8_t disk_type)
{
	if(disk_type == DISK_SD)
	{
		//f_mount(1, &fs);
		f_mount(&fs, (TCHAR const*)SD_Path, 0);
	}
	else if(disk_type == DISK_USB)
	{
		//f_mount(0, &fs);
		f_mount(&fs, (TCHAR const*)USBH_Path, 0);
	}
}

