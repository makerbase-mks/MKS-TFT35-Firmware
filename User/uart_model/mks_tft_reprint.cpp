
#include "mks_tft_com.h"
//#include "printer.h"
//#include "draw_ui.h"
#include "mks_cfg.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_bak.h"
#include <stdlib.h>
#include "ili9320.h"
//#include "others.h"
#include "stm32f4xx_rcc.h"
#include "at24cxx.h"
#include "draw_ui.h"
//#include "repetier.h"
//#include "HAL.h"
#include "gpio.h"



//**#include "SZ_STM32F107VC_LIB.h"


#define PWDWN_FILE_FIFO_SIZE		0X600

extern unsigned char codebuff[100];

extern struct position Gcode_current_position[15];
extern void Print_finish_close_machine();
extern unsigned char z_file[COORDINATELENGTH];

uint8_t btn_putdown_time_flg;
uint32_t btn_putdown_cnt;

//FIL *fp;	//文件指针备份
extern PRINT_TIME  print_time;
extern CFG_ITMES gCfgItems;

uint32_t eepromWrite=0xc1c2c3c4;

RE_PRINT_STRUCT RePrintData;

unsigned char gcode[FIFO_SIZE];		//存储从udiskBuffer提取到的一条gcode
unsigned char *gp;					//指向gcode 的指针
unsigned char ulockCnt=0;			//长注释计数

__IO uint32_t dataToEeprom=0xa9000000;
//uint8_t dataToEeprom8;
unsigned long fileOffset;

unsigned char z_coordinate_bak[COORDINATELENGTH];

//#define	DIS_TEMPER	1000	//续打喷头温度标志(采用当前温度+1000的方式)



//unsigned char reLocalFlag;	//定位成功标志 1:success 0:fial
void pauseReGcode();
void rePrintSaveData();
unsigned char getGcode(void);
unsigned char RePrintLocal();

void copyCoordinate(unsigned char *src,unsigned char *dst)
{
		while(*src != ' ' && *src !='\n')
			*dst++ = *src++;
		*dst = '\n';
}

unsigned char reLocalFile(void)
{
	unsigned char *p;
	unsigned char check_xor;
	unsigned int check_sum;
	unsigned char dig_xor;
	unsigned char z_coordinate[COORDINATELENGTH];
	unsigned char *q;
	//
	
	getGcode();
	if(gp > gcode)		//读取到了gcode指令
	{
		while(*(--gp) == 32);	//去掉多余的空格
			gp++;
		*gp++='\n';

		p=&gcode[0];	
		check_xor=check_sum=dig_xor=0;		
		while(*p != '\n')
		{
			switch(*p)
			{
				case 'X':
					copyCoordinate(p,RePrintData.x_coordinate);
					break;
				case 'Y':
					copyCoordinate(p,RePrintData.y_coordinate);
					break;
				case 'Z':
					copyCoordinate(p,RePrintData.z_coordinate);
					break;
				case 'E':
					copyCoordinate(p,RePrintData.e_coordinate);
					break;
				case 'F':
					copyCoordinate(p,RePrintData.F);
					break;
				default : break;
			}
			/*
			if(f_tell(srcfp) >= fileOffset)
			{
				check_xor ^= *p;
				check_sum += *p;
				if((*p >= '0') && (*p <= '9'))
					dig_xor ^= (*p -0x30)*28;
			}*/
			p++;
		}
		
		//if((check_xor == RePrintData.checkXor) && (check_sum == RePrintData.checkSum) && (dig_xor == RePrintData.digxor))
		//if(f_tell(srcfp) >= fileOffset)
		RePrintData.offset =  f_tell(srcfp)-UDISKBUFLEN;
		if(udiskBuffer.state[(udiskBuffer.current+1)%2] == udisk_buf_full)
			RePrintData.offset -= UDISKBUFLEN;
		RePrintData.offset += udiskBuffer.p - udiskBuffer.buffer[udiskBuffer.current];
		
		if(RePrintData.offset >= fileOffset)	
			{
				
				{
					copyCoordinate(RePrintData.z_coordinate,z_coordinate_bak);	//保存Z轴移动前的位置
					
					p = RePrintData.z_coordinate;
					p++;
					q = z_coordinate;
					while(*p != '.' && *p != '\n')
						*q++ = *p++;
					*q++ = '\0';
					//check_sum = atoi(z_coordinate)+5;
					check_sum = atoi((const char *)z_coordinate)+gCfgItems.Pause_ZADD;
				
					q = z_coordinate;
					*q++ = 'Z';
					if(check_sum >= 1000)	
						{*q++ = check_sum/1000+48;		*q++ = (check_sum/100)%10 + 48; *q++ = (check_sum/10)%10 + 48;		*q++ = check_sum%10 + 48;}
					else if(check_sum >= 100)	
						{*q++ = check_sum/100+48;		*q++ = (check_sum/10)%10 + 48;		*q++ = check_sum%10 + 48;	}
					else	if(check_sum >= 10)
						{*q++ = check_sum/10+48;		*q++ = check_sum%10 + 48;	}
					else
						*q++ = check_sum%10 +48;
			
					while(*p != '\n')					*q++ = *p++;
					*q++ = '\n';
			
					p=RePrintData.z_coordinate;
					q=z_coordinate;
					while(*q != '\n' && *q != '\r') *p++ = *q++;
					*p++ = '\n';
				}
				return 1;
			}
		
	}
		return 0;
}

unsigned int fixPositionZ()
{
	unsigned int blockCnt=2;
	unsigned int readByteCnt=0;
	unsigned int readByteCnt_Mid=0;
	unsigned int i;
	unsigned char *p;
	DWORD   fptr_Int,fptr_remainder,srcfp_fptr;
	if(fileOffset < 3*UDISKBUFLEN)
		return 0;
	
	blockCnt = 1;
	while(1)
	{
		((srcfp)->fptr) = 0;
			
		#ifdef SAVE_FROM_SD
		if((RePrintData.printerStatus == printer_pwdwn_reprint)&&(gCfgItems.pwroff_save_mode == 0))
		{
			f_lseek(srcfp,(RePrintData.offset - blockCnt*UDISKBUFLEN));
		}
		else
		#endif
		{
			f_lseek(srcfp,(RePrintData.offset + PWDWN_FILE_FIFO_SIZE - blockCnt*UDISKBUFLEN));
		}
		
		//f_lseek(srcfp,(RePrintData.offset + PWDWN_FILE_FIFO_SIZE - blockCnt*UDISKBUFLEN));
		//**f_read(srcfp,udiskBuffer.buffer[0],UDISKBUFLEN,&readByteCnt);
		if((srcfp)->fptr % 512 !=0)
		{
			srcfp_fptr=(srcfp)->fptr ;
			fptr_Int=(srcfp)->fptr /UDISKBUFLEN;
			fptr_remainder=(srcfp)->fptr%UDISKBUFLEN;
			f_lseek(srcfp,fptr_Int*UDISKBUFLEN);
			f_read(srcfp,udiskBuffer.mid_buffer[0],UDISKBUFLEN,&readByteCnt_Mid);
			f_read(srcfp,udiskBuffer.mid_buffer[1],UDISKBUFLEN,&readByteCnt_Mid);
			for(int i=0;i<UDISKBUFLEN;i++)
			{
				if(i<(UDISKBUFLEN-fptr_remainder))udiskBuffer.buffer[0][i]=udiskBuffer.mid_buffer[0][i+fptr_remainder];
				else udiskBuffer.buffer[0][i]=udiskBuffer.mid_buffer[1][i-(UDISKBUFLEN-fptr_remainder)];
			}	
			f_lseek(srcfp,srcfp_fptr+UDISKBUFLEN);
		}
		else
		{
			f_read(srcfp,udiskBuffer.buffer[0],UDISKBUFLEN,&readByteCnt);
		}
		for(i=0;i<UDISKBUFLEN;i++)
			{
				if(udiskBuffer.buffer[0][i] == 'Z')
				{
					p = RePrintData.z_coordinate;
					while(udiskBuffer.buffer[0][i] != ' ' && udiskBuffer.buffer[0][i] != '\n' && i<UDISKBUFLEN)
					{
						*p++ = udiskBuffer.buffer[0][i];
						i++;
					}
					*p++ = '\n';
					
					if(RePrintData.offset <= blockCnt*UDISKBUFLEN) 
						return 0;
					else 
						//return (blockCnt+2);
						return (blockCnt+1);
					
				}
			}
		blockCnt++;
			
		if(RePrintData.offset < blockCnt*UDISKBUFLEN)
		{
			return 0;
		}
	}
	
}

uint16_t resume_time = 0;
extern int X_ADD,X_INTERVAL;   //**图片间隔


unsigned char breakpoint_fixPositionZ()
{
		static uint8_t cnt=1;
		volatile float differ;
		unsigned int j;

		unsigned char *p;
		unsigned char z_coordinate[COORDINATELENGTH];
		unsigned char *q;
		
		resume_time = 0;
		GUI_DispStringAtCEOL("resuming...",400, X_INTERVAL);
		RePrintData.break_offset = 0;
		udiskBufferInit();
		RePrintData.F[0] = '2';RePrintData.F[1] = '0';RePrintData.F[2] = '0';RePrintData.F[3] = '0';RePrintData.F[4] = '\n';
		f_lseek(srcfp,RePrintData.break_offset);
		while(RePrintData.break_offset != srcfp->fsize)
		{
			if(resume_time>=1000)
			{
				resume_time = 0;
				switch(cnt)
				{
					case 1:
						GUI_DispStringAtCEOL("            ",400, X_INTERVAL);
						GUI_DispStringAtCEOL("resuming.",400, X_INTERVAL);
						cnt++;
						break;
					case 2:
						GUI_DispStringAtCEOL("resuming..",400, X_INTERVAL);
						cnt++;
						break;
					case 3:
						GUI_DispStringAtCEOL("resuming...",400, X_INTERVAL);
						cnt=1;
						break;
					default:
						GUI_DispStringAtCEOL("resuming...",400,X_INTERVAL);
						break;
				}
			}
			udiskFileR(srcfp);
			
			getGcode();
			if(gp > gcode)		//读取到了gcode指令
			{
				while(*(--gp) == 32); //去掉多余的空格
					gp++;
				*gp++='\n';
		
				p=&gcode[0];		
				while(*p != '\n')
				{
					switch(*p)
					{
						//case 'X':
							//copyCoordinate(p,RePrintData.x_coordinate);
						//	break;
						//case 'Y':
							//copyCoordinate(p,RePrintData.y_coordinate);
						//	break;
						case 'Z':
							copyCoordinate(p,RePrintData.z_coordinate);
							break;
						case 'E':
							copyCoordinate(p,RePrintData.e_coordinate);
							break;
						//case 'F':
							//copyCoordinate(p,RePrintData.F);
						//	break;
						default : break;
					}
					p++;
				}
				RePrintData.break_offset =	f_tell(srcfp)-UDISKBUFLEN;
				if(udiskBuffer.state[(udiskBuffer.current+1)%2] == udisk_buf_full)
					RePrintData.break_offset -= UDISKBUFLEN;
				RePrintData.break_offset += udiskBuffer.p - udiskBuffer.buffer[udiskBuffer.current];

				j=0;
				while((RePrintData.z_coordinate[j+1] != '\r')&&(RePrintData.z_coordinate[j+1] != '\n')&&(j<19))
				{
					z_file[j]=RePrintData.z_coordinate[j+1];
					j++;
				}
				z_file[j]='\0';
				DecStr2Float((int8_t *)z_file,(float *)&gCfgItems.find_z_current_position);
				differ = gCfgItems.find_z_current_position - (gCfgItems.z_current_position);
				j=0;
				if((differ >= -gCfgItems.breakpoint_z_error)&&(differ <= gCfgItems.breakpoint_z_error)&&(RePrintData.break_offset > 3*UDISKBUFLEN))
				{
					while(RePrintData.z_coordinate[j+1] != '\n')
					{
						gCfgItems.z_display_pos[j] = RePrintData.z_coordinate[j+1];
						j++;
					}
					f_lseek(srcfp,RePrintData.break_offset);		

					GUI_DispStringAtCEOL("            ",300, X_INTERVAL);
					return 1;
				}
		}
}
		return 0;
}


void BreakPointReGcode()
{
	unsigned char tmpGcode[FIFO_SIZE];
	unsigned char *p;
	unsigned char *q;

	memset(tmpGcode, 0, sizeof(tmpGcode));
	p=tmpGcode;			//设置X,Y,Z,E当前位置
	*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
	q = RePrintData.e_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	#if 0
	memset(tmpGcode, 0, sizeof(tmpGcode));
	p=tmpGcode;			//
	*p++ = 'G';*p++ = '9';*p++ = '1';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;			//出丝  "G1 E2\n";
	*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'E';*p++ = '2';*p++ = '.';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	p=tmpGcode;			//
	*p++ = 'G';*p++ = '9';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	#endif
}

unsigned char RePrintLocal()
{
		
		unsigned int blockCnt;
		unsigned char relocalFlag;
	
		fileOffset = RePrintData.offset;
		blockCnt = 	fixPositionZ();
		((srcfp)->fptr) = 0;
		
		if(RePrintData.offset > blockCnt*UDISKBUFLEN && blockCnt>0)
			f_lseek(srcfp,(RePrintData.offset - blockCnt*UDISKBUFLEN));
	
		udiskBufferInit();
		RePrintData.F[0] = '2';RePrintData.F[1] = '0';RePrintData.F[2] = '0';RePrintData.F[3] = '0';RePrintData.F[4] = '\n';
		
		relocalFlag = 0;
		while(f_tell(srcfp) <= fileOffset + 2*UDISKBUFLEN)
		{
		
			udiskFileR(srcfp);
			relocalFlag = reLocalFile();
			if(relocalFlag) break;
		}
		
		
		if(relocalFlag == 0)	//定位失败
		{
				udiskFileStaus = udisk_file_end;
				printerStaus = pr_idle;		//打印结束
				usart2Data.printer = printer_idle;
				usart2Data.prWaitStatus = pr_wait_idle;
				usart2Data.timer = timer_stop;						//清除定时器

				HAL::AT24CXX_Read(BAK_REPRINT_INFO, (uint8_t *)&dataToEeprom,  4);
				dataToEeprom &= 0x00ffffff;
				RePrintData.printerStatus = printer_normal;
				dataToEeprom |= ((uint32_t)RePrintData.printerStatus << 24)&0xff000000;
				HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *)&dataToEeprom ,  4); 		// 续打标志(uint8_t) | checkXor(uint8_t) | checkSum(uint16_t)
		
				printerStop();	
				return 0;
		}
		else
			return 1;
			//pauseReGcode();
}

void getIntToChar(unsigned char *dst,unsigned long src,unsigned char flag)
{
	unsigned int intpart;
	*dst++ = flag;

	intpart = (src >> 16) & 0x0000ffff;
	
	if(intpart > 0x8000)	//负数
		{
		intpart &= 0x7fff ;
		*dst++ = '-';
		}

	if(intpart >= 1000)	
		{*dst++ = intpart/1000+48;		*dst++ = (intpart/100)%10 + 48; *dst++ = (intpart/10)%10 + 48;		*dst++ = intpart%10 + 48;}
	else if(intpart >= 100)	
		{*dst++ = intpart/100+48;		*dst++ = (intpart/10)%10 + 48;		*dst++ = intpart%10 + 48;	}
	else	if(intpart >=10)
		{*dst++ = intpart/10+48;		*dst++ = intpart%10 + 48;	}
	else
		*dst++ = intpart%10 +48;
	*dst++ = '.';

	*dst++ = (src >> 8) &0x000000ff;
	*dst++ = src  &0x000000ff;
	
	*dst++ = '\n';
	
}
void pauseSaveReGcode()
{
	unsigned char tmpGcode[FIFO_SIZE];
	unsigned char *p;
	unsigned char *q;

	RePrintData.saveFlag = SAVE_DIS;
	
	while(checkFIFO(&gcodeTxFIFO) != fifo_empty) 
		popFIFO(&gcodeTxFIFO,tmpGcode);	

	getIntToChar(x_pauseBak,RePrintData.saveX,'X');
	getIntToChar(y_pauseBak,RePrintData.saveY,'Y');
	getIntToChar(z_pauseBak,RePrintData.saveZ,'Z');
	
	
	p=tmpGcode;			//设置X,Y,Z,E当前位置
	*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
	//q = x_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++; 	*p++ = ' ';
	//q = y_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = z_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = RePrintData.e_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode; 		//
	*p++ = 'M';*p++ = '2';*p++ = '1';*p++ = '1';*p++ = ' ';*p++ = 'S';*p++ = '0';
	pushFIFO(&gcodeTxFIFO,tmpGcode);


#if 0
	p=tmpGcode;			//移动Z轴
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.z_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
#endif
	p=tmpGcode; 		//X,Y 回零 "G28 X0 Y0\n";
	*p++ = 'G';*p++ = '2';*p++ = '8';*p++ = ' ';*p++ = 'X';*p++ = '0';*p++ = ' ';*p++ = 'Y';*p++ = '0';*p++ = ' ';*p++ = 'F';*p++ = '5';*p++ = '0';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);


//	p=tmpGcode;			//打印头加热
//	*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
		if(gCfgItems.sprayerNum == 2)
		{
				if(RePrintData.spayerchoose == 1)
				{
					p=tmpGcode; 		//打印头0 加热,不等待
					*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
					if((RePrintData.t0Temp) >= 100) 
					{
						*p++ = (RePrintData.t0Temp)/100+48; 	
						*p++ = ((RePrintData.t0Temp)/10)%10 + 48; 	
						*p++ = (RePrintData.t0Temp)%10 + 48;	
					}
					else	
					{
						*p++ = (RePrintData.t0Temp)/10+48;		
						*p++ = (RePrintData.t0Temp)%10 + 48;	
					}
							
					*p++ = '\n';
					pushFIFO(&gcodeTxFIFO,tmpGcode);
					
					p=tmpGcode; 		//打印头1 加热
					*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
					if((RePrintData.t1Temp) >= 100) 
					{
						*p++ = (RePrintData.t1Temp)/100+48; 	
						*p++ = ((RePrintData.t1Temp)/10)%10 + 48; 	
						*p++ = (RePrintData.t1Temp)%10 + 48;	
					}
					else	
					{
						*p++ = (RePrintData.t1Temp)/10+48;		
						*p++ = (RePrintData.t1Temp)%10 + 48;	
					} 
					*p++ = '\n';
					pushFIFO(&gcodeTxFIFO,tmpGcode);

					pushFIFO(&gcodeTxFIFO,(unsigned char *)"T1\n");
					
				}
				else
				{
					p=tmpGcode; 		//打印头1 加热，不等待
					*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
					if((RePrintData.t1Temp) >= 100) 
					{
						*p++ = (RePrintData.t1Temp)/100+48; 	
						*p++ = ((RePrintData.t1Temp)/10)%10 + 48; 	
						*p++ = (RePrintData.t1Temp)%10 + 48;	
					}
					else	
					{
						*p++ = (RePrintData.t1Temp)/10+48;		
						*p++ = (RePrintData.t1Temp)%10 + 48;	
					}
							
					*p++ = '\n';
					pushFIFO((_FIFO *)&gcodeTxFIFO,tmpGcode);
					
					p=tmpGcode; 		//打印头1 加热
					*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
					if((RePrintData.t0Temp) >= 100) 
					{
						*p++ = (RePrintData.t0Temp)/100+48; 	
						*p++ = ((RePrintData.t0Temp)/10)%10 + 48; 	
						*p++ = (RePrintData.t0Temp)%10 + 48;	
					}
					else	
					{
						*p++ = (RePrintData.t0Temp)/10+48;		
						*p++ = (RePrintData.t0Temp)%10 + 48;	
					} 
					*p++ = '\n';
					pushFIFO(&gcodeTxFIFO,tmpGcode);
				
					pushFIFO(&gcodeTxFIFO,(unsigned char *)"T0\n");	
				}

		}
		else
		{
				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t0Temp) >= 100) 
				{
					*p++ = (RePrintData.t0Temp)/100+48; 	
					*p++ = ((RePrintData.t0Temp)/10)%10 + 48; 	
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t0Temp)/10+48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				} 
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);
		}


	if(RePrintData.bedTemp > 0)
	{
		p=tmpGcode;			//热床加热
		*p++ = 'M';*p++ = '1';*p++ = '9';*p++ = '0';*p++ = ' ';*p++ = 'S';
		if(RePrintData.bedTemp >= 100)	{*p++ = RePrintData.bedTemp/100+48;		*p++ = (RePrintData.bedTemp/10)%10 + 48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		else	{*p++ = RePrintData.bedTemp/10+48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
	}

/*
	p=tmpGcode;			
	*p++ = 'G';*p++ = '9';*p++ = '1';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	p=tmpGcode;			//出丝  "G1 E1\n";
	*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'E';*p++ = '1';*p++ = '.';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	p=tmpGcode;			
	*p++ = 'G';*p++ = '9';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
*/

	p=tmpGcode;		//定位X,Y, Z
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = z_coordinate_bak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);


	p=tmpGcode; 	//设置风扇	M106 S247
	*p++ = 'M';*p++ = '1';*p++ = '0';
	if(RePrintData.fanOnoff) 	
	{
		*p++ = '6';
		if(RePrintData.fanSpeed > 0)
		{
			*p++ = ' ';*p++ = 'S';
			if(RePrintData.fanSpeed >= 100)	{*p++ = RePrintData.fanSpeed/100+48;		*p++ = (RePrintData.fanSpeed/10)%10 + 48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
			else	{*p++ = RePrintData.fanSpeed/10+48; 	*p++ = RePrintData.fanSpeed%10 + 48;	}
		}
	}		
	else 
		*p++ = '7';
	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode; 	//"N-1 M110*15\n";
	*p++ = 'N';*p++ = '-';*p++ = '1';*p++ = ' ';*p++ = 'M';*p++ = '1';*p++ = '1';*p++ = '0';*p++ = '*';*p++ = '1';*p++ = '5';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	pushFIFO(&gcodeTxFIFO,tmpGcode);


	
}
void pauseReGcode()
{
	unsigned char tmpGcode[FIFO_SIZE];
	unsigned char *p;
	unsigned char *q;
	
	unsigned char homeGcode_tmp3[20];

	while(checkFIFO(&gcodeTxFIFO) != fifo_empty) 
		popFIFO(&gcodeTxFIFO,tmpGcode);	
	/*
	p=tmpGcode;	//设置单位 mm or inch		//0 mm G21 ,1 inch G20
	*p++ = 'G';*p++ = '2';
	if(RePrintData.unit) *p++ = '0'; else *p++ = '1';
	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	*/
	
//	p=tmpGcode;			//打印头预热，不等待
//	*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'S';

	if(gCfgItems.sprayerNum == 2)
	{
		p=tmpGcode;			//打印头预热，不等待
		*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
		if((RePrintData.t0Temp) >= 100)	
		{
			*p++ = (RePrintData.t0Temp)/100+48;		
			*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
			*p++ = (RePrintData.t0Temp)%10 + 48;	
		}
		else	
		{
			*p++ = (RePrintData.t0Temp)/10+48;		
			*p++ = (RePrintData.t0Temp)%10 + 48;	
		}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);			

		p=tmpGcode;			//打印头预热，不等待
		*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
		if((RePrintData.t1Temp) >= 100)	
		{
			*p++ = (RePrintData.t1Temp)/100+48;		
			*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
			*p++ = (RePrintData.t1Temp)%10 + 48;	
		}
		else	
		{
			*p++ = (RePrintData.t1Temp)/10+48;		
			*p++ = (RePrintData.t1Temp)%10 + 48;	
		}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);	
		
		//判断喷头0或喷头1动作
		if(RePrintData.spayerchoose == 1)
		{
			pushFIFO(&gcodeTxFIFO,(unsigned char *)"T1\n");
		}
		else
		{
			pushFIFO(&gcodeTxFIFO,(unsigned char *)"T0\n");	
		} 		
	}
	else
	{
			p=tmpGcode;			//打印头预热，不等待
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t0Temp)/100+48;		
				*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t0Temp)/10+48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);	
	}


	if(RePrintData.bedTemp > 0)
	{
		p=tmpGcode;			//热床加热
		*p++ = 'M';*p++ = '1';*p++ = '9';*p++ = '0';*p++ = ' ';*p++ = 'S';
		if(RePrintData.bedTemp >= 100)	{*p++ = RePrintData.bedTemp/100+48;		*p++ = (RePrintData.bedTemp/10)%10 + 48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		else	{*p++ = RePrintData.bedTemp/10+48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
	}

//	p=tmpGcode;			//打印头加热
//	*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
	
	if(gCfgItems.sprayerNum == 2)
	{
			if(RePrintData.spayerchoose == 1)
			{
				p=tmpGcode;			//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t1Temp) >= 100)	
				{
					*p++ = (RePrintData.t1Temp)/100+48;		
					*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t1Temp)/10+48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);			
			}
			else
			{
				p=tmpGcode;			//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t0Temp) >= 100)	
				{
					*p++ = (RePrintData.t0Temp)/100+48;		
					*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t0Temp)/10+48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);	
			}

	}
	else
	{
			p=tmpGcode;			//打印头加热
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t0Temp)/100+48;		
				*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t0Temp)/10+48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);

	}
	
//	*p++ = '\n';
//	pushFIFO(&gcodeTxFIFO,tmpGcode);


	p=tmpGcode;			//设置X,Y,Z,E当前位置
	*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
	//q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++; *p++ = ' ';
	//q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = RePrintData.z_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = RePrintData.e_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode; 		//
	*p++ = 'M';*p++ = '2';*p++ = '1';*p++ = '1';*p++ = ' ';*p++ = 'S';*p++ = '0';
	pushFIFO(&gcodeTxFIFO,tmpGcode);


/*
	p=tmpGcode;	//设置 M82   去掉
	*p++ = 'M';*p++ = '8';*p++ = '2';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
*/
	p=tmpGcode;			//X,Y 回零 "G28 X0 Y0\n";
	*p++ = 'G';*p++ = '2';*p++ = '8';*p++ = ' ';*p++ = 'X';*p++ = '0';*p++ = ' ';*p++ = 'Y';*p++ = '0';*p++ = ' ';*p++ = 'F';*p++ = '5';*p++ = '0';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;		//定位 X,Y
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++; *p++ = ' ';
	q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	////*p++ = 'F'; *p++ = '2';*p++ = '0';*p++ = '0';*p++ = '0';
	*p++ = '\n';
	//q = z_coordinate_bak;	while(*q != '\n')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);		

	p=tmpGcode;			//Z轴归位		是否用 G0
	*p++ = 'G';*p++ = '9';*p++ = '1';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;			//出丝  "G1 E1\n";
	*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'E';*p++ = '1';*p++ = '.';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	//p=tmpGcode;			//Z轴归位
	//*p++ = 'G';*p++ = '1';*p++ = ' ';	//G1 OR G0
	//*p++ = 'Z';*p++ = '-';*p++ = '5';
	//*p++ = '\n';
	#if 0
	memset(tmpGcode, 0, sizeof(tmpGcode));
	tmpGcode[0] = 'G';
	tmpGcode[1] = '1';
	tmpGcode[2] = ' ';
	tmpGcode[3] = 'Z';
	tmpGcode[4] = '-';
	sprintf((char *)homeGcode_tmp3,"%d",gCfgItems.Pause_ZADD);
	strcat((char *)tmpGcode,(const char *)homeGcode_tmp3);
	strcat((char *)tmpGcode,"\n");
	#endif
	sprintf((char *)tmpGcode,"G1 Z-%d\n",gCfgItems.Pause_ZADD);
	pushFIFO(&gcodeTxFIFO,tmpGcode);	
	
	//p=tmpGcode;			//出丝  "G1 E1\n";
	//*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'E';*p++ = '1';*p++ = '.';*p++ = '0';*p++ = '\n';
	//pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	 
	p=tmpGcode;			//Z轴归位
	*p++ = 'G';*p++ = '9';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	p=tmpGcode;		//设置风扇  M106 S247
	*p++ = 'M';*p++ = '1';*p++ = '0';
	if(RePrintData.fanOnoff) 
	{
		*p++ = '6';
		if(RePrintData.fanSpeed > 0)
		{
			*p++ = ' ';*p++ = 'S';
			if(RePrintData.fanSpeed >= 100)	{*p++ = RePrintData.fanSpeed/100+48;		*p++ = (RePrintData.fanSpeed/10)%10 + 48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
			else	{*p++ = RePrintData.fanSpeed/10+48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
		}
	}		
	else 
		*p++ = '7';
	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;		//"N-1 M110*15\n";
	*p++ = 'N';*p++ = '-';*p++ = '1';*p++ = ' ';*p++ = 'M';*p++ = '1';*p++ = '1';*p++ = '0';*p++ = '*';*p++ = '1';*p++ = '5';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
}
void deltaPauseReGcode()
{
		unsigned char tmpGcode[FIFO_SIZE];
		unsigned char *p;
		unsigned char *q;
		
		while(checkFIFO(&gcodeTxFIFO) != fifo_empty) 
			popFIFO(&gcodeTxFIFO,tmpGcode); 

		
//		p=tmpGcode; 		//打印头加热
//		*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
		if(gCfgItems.sprayerNum == 2)
		{
			if(RePrintData.spayerchoose == 1)
			{
				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t0Temp) >= 100)	
				{
					*p++ = (RePrintData.t0Temp)/100+48;		
					*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t0Temp)/10+48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);

				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t1Temp) >= 100)	
				{
					*p++ = (RePrintData.t1Temp)/100+48;		
					*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t1Temp)/10+48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}	
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);
				
				pushFIFO((_FIFO *)&gcodeTxFIFO,(unsigned char *)"T1\n");			
			}
			else
			{
				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t1Temp) >= 100)	
				{
					*p++ = (RePrintData.t1Temp)/100+48;		
					*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t1Temp)/10+48;		
					*p++ = (RePrintData.t1Temp)%10 + 48;	
				}
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);

				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t0Temp) >= 100)	
				{
					*p++ = (RePrintData.t0Temp)/100+48;		
					*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t0Temp)/10+48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}	
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);

				pushFIFO((_FIFO *)&gcodeTxFIFO,(unsigned char *)"T0\n");				
			}
		}
		else
		{
				p=tmpGcode; 		//打印头加热
				*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
				if((RePrintData.t0Temp) >= 100) 
				{
					*p++ = (RePrintData.t0Temp)/100+48; 	
					*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				else	
				{
					*p++ = (RePrintData.t0Temp)/10+48;		
					*p++ = (RePrintData.t0Temp)%10 + 48;	
				}
				*p++ = '\n';
				pushFIFO(&gcodeTxFIFO,tmpGcode);
		}
//		*p++ = '\n';
//		pushFIFO(&gcodeTxFIFO,tmpGcode);

//		pushFIFO(&gcodeTxFIFO,tmpGcode);
		
	
		if(RePrintData.bedTemp > 0)
		{
			p=tmpGcode; 		//热床加热
			*p++ = 'M';*p++ = '1';*p++ = '9';*p++ = '0';*p++ = ' ';*p++ = 'S';
			if(RePrintData.bedTemp >= 100)	{*p++ = RePrintData.bedTemp/100+48; 	*p++ = (RePrintData.bedTemp/10)%10 + 48;		*p++ = RePrintData.bedTemp%10 + 48; }
			else	{*p++ = RePrintData.bedTemp/10+48;		*p++ = RePrintData.bedTemp%10 + 48; }
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);
		}
	

		p=tmpGcode; 		//X,Y,Z归零
		*p++ = 'G';*p++ = '2';*p++ = '8';*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
		
		 
		p=tmpGcode; 		//Use Absolute Coordinates
		*p++ = 'G';*p++ = '9';*p++ = '0';*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
		
		p=tmpGcode; 		//设置E位置	
		*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
		q = RePrintData.e_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);

//2015.11.09
/*	
		//移动到X,Y,Z, ,设置F
		p=tmpGcode; 		
		*p++ = 'G';*p++ = '1';*p++ = ' ';
		q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++; *p++ = ' ';
		q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
		q = z_coordinate_bak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
		q = RePrintData.F;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';

		pushFIFO(&gcodeTxFIFO,tmpGcode);
*/
	//移动到Z
	p=tmpGcode; 		
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = z_coordinate_bak; while(*q != '\n' && *q != '\r') 	*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	//移动到X,Y ,设置F
	p=tmpGcode; 		
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.x_coordinate; while(*q != '\n' && *q != '\r') 	*p++ = *q++; *p++ = ' ';
	q = RePrintData.y_coordinate; while(*q != '\n' && *q != '\r') 	*p++ = *q++;	*p++ = ' ';
	q = z_coordinate_bak; while(*q != '\n' && *q != '\r') 	*p++ = *q++;	*p++ = ' ';
	q = RePrintData.F;	while(*q != '\n' && *q != '\r') 	*p++ = *q++;	*p++ = '\n';
	
	pushFIFO(&gcodeTxFIFO,tmpGcode);

		
		p=tmpGcode; 	//设置风扇	M106 S247
		*p++ = 'M';*p++ = '1';*p++ = '0';
		if(RePrintData.fanOnoff) 
		{
			*p++ = '6';
			if(RePrintData.fanSpeed > 0)
			{
				*p++ = ' ';*p++ = 'S';
				if(RePrintData.fanSpeed >= 100)	{*p++ = RePrintData.fanSpeed/100+48;		*p++ = (RePrintData.fanSpeed/10)%10 + 48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
				else	{*p++ = RePrintData.fanSpeed/10+48; 	*p++ = RePrintData.fanSpeed%10 + 48;	}
			}
		}		
		else 
		*p++ = '7';
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);

		p=tmpGcode; 	//"N-1 M110*15\n";
		*p++ = 'N';*p++ = '-';*p++ = '1';*p++ = ' ';*p++ = 'M';*p++ = '1';*p++ = '1';*p++ = '0';*p++ = '*';*p++ = '1';*p++ = '5';*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
		pushFIFO(&gcodeTxFIFO,tmpGcode);

}
	

void pwdwnReGcode()
{
	unsigned char tmpGcode[FIFO_SIZE];
	unsigned char *p;
	unsigned char *q;
	
	while(checkFIFO(&gcodeTxFIFO) != fifo_empty) 
		popFIFO(&gcodeTxFIFO,tmpGcode);	
/*
	p=tmpGcode;	//设置单位 mm or inch		//0 mm G21 ,1 inch G20
	*p++ = 'G';*p++ = '2';
	if(RePrintData.unit) *p++ = '0'; else *p++ = '1';
	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	*/
/*
	if(RePrintData.bedTemp > 0)
		{
		p=tmpGcode;						// M140设置热床温度，不等待
		*p++ = 'M';*p++ = '1';*p++ = '4';*p++ = '0';*p++ = ' ';*p++ = 'S';
		if(RePrintData.bedTemp >= 100)	{*p++ = RePrintData.bedTemp/100+48;		*p++ = (RePrintData.bedTemp/10)%10 + 48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		else	{*p++ = RePrintData.bedTemp/10+48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
		}
	*/
	//p=tmpGcode;			//打印头加热
	//*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';

	//chen 9.20
	//pushFIFO((_FIFO *)&gcodeTxFIFO,(unsigned char *)GET_CUR_TEM_COMMAND);

	if(gCfgItems.sprayerNum == 2)
	{
		if(RePrintData.spayerchoose == 1)
		{
			p=tmpGcode;			//打印头0 加热
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t0Temp)/100+48;		
				*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t0Temp)/10+48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
					
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);
			
			p=tmpGcode;			//打印头1 加热
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t1Temp) >= 100)	
			{
				*p++ = (RePrintData.t1Temp)/100+48;		
				*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t1Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t1Temp)/10+48;		
				*p++ = (RePrintData.t1Temp)%10 + 48;	
			}	
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);

			pushFIFO((_FIFO *)&gcodeTxFIFO,(unsigned char *)"T1\n");
		}
		else
		{
			p=tmpGcode;			//打印头1 加热，不等待
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '4';*p++ = ' ';*p++ = 'T';*p++ = '1';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t1Temp)/100+48;		
				*p++ = ((RePrintData.t1Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t1Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t1Temp)/10+48;		
				*p++ = (RePrintData.t1Temp)%10 + 48;	
			}
					
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);
			
			p=tmpGcode;			//打印头1 加热
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'T';*p++ = '0';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t0Temp)/100+48;		
				*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t0Temp)/10+48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}	
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);

		
			pushFIFO((_FIFO *)&gcodeTxFIFO,(unsigned char *)"T0\n");	
		}
	}
	else
	{
			p=tmpGcode;			//打印头加热
			*p++ = 'M';*p++ = '1';*p++ = '0';*p++ = '9';*p++ = ' ';*p++ = 'S';
			if((RePrintData.t0Temp) >= 100)	
			{
				*p++ = (RePrintData.t0Temp)/100+48;		
				*p++ = ((RePrintData.t0Temp)/10)%10 + 48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}
			else	
			{
				*p++ = (RePrintData.t0Temp)/10+48;		
				*p++ = (RePrintData.t0Temp)%10 + 48;	
			}	
			*p++ = '\n';
			pushFIFO(&gcodeTxFIFO,tmpGcode);
	}
	
//	*p++ = '\n';
//	pushFIFO(&gcodeTxFIFO,tmpGcode);

//	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	p=tmpGcode;			//设置X,Y,Z,E当前位置
	*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
	//20150909
	//q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++; *p++ = ' ';
	//q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = z_coordinate_bak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = RePrintData.e_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;		//Z轴下降5mm
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.z_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	
	p=tmpGcode;			//X,Y 回零 "G28 X0 Y0\n";
	*p++ = 'G';*p++ = '2';*p++ = '8';*p++ = ' ';*p++ = 'X';*p++ = '0';*p++ = ' ';*p++ = 'Y';*p++ = '0';*p++ = ' ';*p++ = 'F';*p++ = '5';*p++ = '0';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);


	if(RePrintData.bedTemp > 0)
		{
		p=tmpGcode;			//热床加热
		*p++ = 'M';*p++ = '1';*p++ = '9';*p++ = '0';*p++ = ' ';*p++ = 'S';
		if(RePrintData.bedTemp >= 100)	{*p++ = RePrintData.bedTemp/100+48;		*p++ = (RePrintData.bedTemp/10)%10 + 48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		else	{*p++ = RePrintData.bedTemp/10+48;		*p++ = RePrintData.bedTemp%10 + 48;	}
		*p++ = '\n';
		pushFIFO(&gcodeTxFIFO,tmpGcode);
		}
	p=tmpGcode;		//定位 X,Y
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = RePrintData.x_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++; *p++ = ' ';
	q = RePrintData.y_coordinate;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	*p++ = 'F'; *p++ = '2';*p++ = '0';*p++ = '0';*p++ = '0';*p++ = '\n';
	//q = z_coordinate_bak;	while(*q != '\n')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	
	p=tmpGcode;		//定位 Z
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	//q = RePrintData.x_coordinate;	while(*q != '\n')		*p++ = *q++; *p++ = ' ';
	//q = RePrintData.y_coordinate;	while(*q != '\n')		*p++ = *q++;	*p++ = ' ';
	q = z_coordinate_bak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;		//设置风扇  M106 S247
	*p++ = 'M';*p++ = '1';*p++ = '0';
	if(RePrintData.fanOnoff) 
	{
		*p++ = '6';
		if(RePrintData.fanSpeed > 0)
		{
			*p++ = ' ';*p++ = 'S';
			if(RePrintData.fanSpeed >= 100)	{*p++ = RePrintData.fanSpeed/100+48;		*p++ = (RePrintData.fanSpeed/10)%10 + 48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
			else	{*p++ = RePrintData.fanSpeed/10+48;		*p++ = RePrintData.fanSpeed%10 + 48;	}
		}
	}		
	else 
		*p++ = '7';
	*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);

	p=tmpGcode;		//"N-1 M110*15\n";
	*p++ = 'N';*p++ = '-';*p++ = '1';*p++ = ' ';*p++ = 'M';*p++ = '1';*p++ = '1';*p++ = '0';*p++ = '*';*p++ = '1';*p++ = '5';*p++ = '\n';
	pushFIFO(&gcodeTxFIFO,tmpGcode);
	pushFIFO(&gcodeTxFIFO,tmpGcode);
}


#ifdef SAVE_FROM_SD

void rePrintProcess_pwrdwn()
{	
	volatile uint32_t dataFrEeprom_pwr=0xc1c2c3c4;

	if(RePrintData.printerStatus == printer_normal)	
		return;

	if(RePrintData.printerStatus != printer_pwdwn_reprint)
		return;

	if(RePrintData.offset > f_size(srcfp))		//打开文件错误
		return ;
	
	//E2PROM恢复默认值
	dataFrEeprom_pwr = (uint32_t)(printer_normal << 24 ) & 0xffffffff;
	HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *) &dataFrEeprom_pwr,4); 		// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)

	RePrintData.spayerchoose= gCfgItems.curSprayerChoose;
	RePrintData.fanOnoff = gCfgItems.fanOnoff;
	RePrintData.fanSpeed = gCfgItems.fanSpeed;
	RePrintData.bedTemp = gCfgItems.desireBedTemp;
	RePrintData.t0Temp = gCfgItems.desireSprayerTemp[0];
	RePrintData.t1Temp = gCfgItems.desireSprayerTemp[1];

	if(RePrintData.printerStatus == printer_pwdwn_reprint)
		//RePrintData.offset -= 0x200;	//断电时有gcode 未执行，回退0X200
		if(RePrintData.offset >0x400)
			RePrintData.offset += 0x400;	//断电时有gcode 未执行，回退0X300
			
	((srcfp)->fptr) = 0;	//重置文件指针
	if(RePrintLocal() == 0) 
		return;				//定位失败
	
	usart2Data.printer = printer_waiting;

	switch(RePrintData.printerStatus)
	{
		case printer_normal:
			break;
		case printer_pause_reprint:
			break;
		case printer_pwdwn_reprint:
			if(gCfgItems.machineType == 2)
				deltaPauseReGcode();
			else
				pwdwnReGcode();
			break;
		default :break;
	}
	
	RePrintData.printerStatus = printer_normal;
	
}
#endif

void rePrintProcess()
{	
	volatile uint32_t dataFrEeprom=0xc1c2c3c4;
	//uint8_t dataToEeprom8;
	volatile unsigned char saveFlagR;
	volatile uint32_t time;
	volatile uint8_t icnt;
	
	if(RePrintData.printerStatus == printer_normal)	
		return;
	
	HAL::AT24CXX_Read(BAK_REPRINT_INFO,(uint8_t *)&dataFrEeprom,4);	// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)
	RePrintData.printerStatus =(RE_PRINT_STATUS )( (dataFrEeprom >> 24)&0x000000ff);
	RePrintData.spayerchoose= (uint8_t)((dataFrEeprom >> 20)&0x0000000f);
	RePrintData.fanOnoff = (dataFrEeprom >> 16)&0x0000000f;
	RePrintData.fanSpeed = (dataFrEeprom >> 8)&0x000000ff;
	RePrintData.bedTemp = (dataFrEeprom)&0x000000ff;

	//RePrintData.unit = (dataFrEeprom >> 16)&0x000000ff; //0 mm,1 inch
	
	//RePrintData.checkXor = (dataFrEeprom >> 16)&0x000000ff;
	//RePrintData.checkSum = dataFrEeprom & 0x0000ffff;

	/*--------------normal used--------------------*/
	//E2PROM恢复默认值
	dataToEeprom = (uint32_t)(printer_normal << 24 ) & 0xffffffff;
	HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *)&dataToEeprom ,4); 		// 续打标志(uint8_t) | 单位unit (uint8_t) | saveFlag(uint8_t)| null(uint8_t)
	

	HAL::AT24CXX_Read(BAK_REPRINT_S,(uint8_t *)&dataFrEeprom,4);	//null(uint24_t) | saveFlag(uint8_t)
	saveFlagR = (unsigned char)(dataFrEeprom&0x000000ff);

	dataToEeprom = 0;	//SAVE_DIS
	HAL::AT24CXX_Write(BAK_REPRINT_S,(uint8_t *)&dataToEeprom ,  4);		//null(uint24_t) | saveFlag(uint8_t)

	
	/*----------------------------------*/

	
	if((RePrintData.printerStatus != printer_pause_reprint) && (RePrintData.printerStatus != printer_pwdwn_reprint))
		return;

	HAL::AT24CXX_Read(BAK_REPRINT_OFFSET,(uint8_t *)&dataFrEeprom,4);
	RePrintData.offset = dataFrEeprom;
	if(RePrintData.offset > f_size(srcfp))		//打开文件错误
		return ;
	//清除E2PROM中偏移值。
	dataToEeprom = 0xffffffff;
	HAL::AT24CXX_Write(BAK_REPRINT_OFFSET,(uint8_t *)&dataToEeprom,4);

	HAL::AT24CXX_Read(BAK_REPRINT_TIME,(uint8_t *)&time ,  4);
	print_time.hours = (time >> 16)  & 0xffff;
	print_time.minutes = (time >> 8)  & 0xff;
	
	if((print_time.hours == 0xffff)&&(print_time.minutes == 0xff))
	{
		print_time.hours = 0;
		print_time.minutes = 0;
	}

	//清除E2PROM
	dataToEeprom = 0xffffffff;
	HAL::AT24CXX_Write(BAK_REPRINT_TIME,(uint8_t *)&dataToEeprom ,  4);


	if(RePrintData.printerStatus == printer_pwdwn_reprint)
		//RePrintData.offset -= 0x200;	//断电时有gcode 未执行，回退0X200
		if(RePrintData.offset > PWDWN_FILE_FIFO_SIZE)
			RePrintData.offset -= PWDWN_FILE_FIFO_SIZE;	//断电时有gcode 未执行，回退0X300
			
	HAL::AT24CXX_Read(BAK_REPRINT_HTEMP,(uint8_t *)&dataFrEeprom,4);
	RePrintData.t0Temp = (dataFrEeprom >> 16) & 0x0000ffff;
	RePrintData.t1Temp = dataFrEeprom  & 0x0000ffff;
	if((RePrintData.t0Temp == 0xffff)&&(RePrintData.t1Temp == 0xffff))
	{
		RePrintData.t0Temp = 0;
		RePrintData.t1Temp = 0;
	}	
	//清除E2PROM
	dataToEeprom = 0xffffffff;
	HAL::AT24CXX_Write(BAK_REPRINT_HTEMP,(uint8_t *)&dataToEeprom , 4);
/*	
	I2C_EE_BufferRead(&dataFrEeprom,BAK_REPRINT_FAN,4);
	RePrintData.bedTemp = (dataFrEeprom >> 24)&0x000000ff;
	RePrintData.fanOnoff = (dataFrEeprom >> 16)&0x000000ff;
	RePrintData.fanSpeed = (dataFrEeprom >> 8)&0x000000ff;
	if((RePrintData.bedTemp == 0xff)&&(RePrintData.fanOnoff == 0xff)&&(RePrintData.fanSpeed == 0xff))
	{
		RePrintData.bedTemp = 0;
		RePrintData.fanOnoff = 0;
		RePrintData.fanSpeed = 0;
	}	
	//清除E2PROM
	dataToEeprom = 0xffffffff;
	I2C_EE_BufferWrite(&dataToEeprom, BAK_REPRINT_FAN, 4);
*/
	if((RePrintData.bedTemp == 0xff)&&(RePrintData.fanOnoff == 0x0f)&&(RePrintData.fanSpeed == 0xff))
	{
		RePrintData.bedTemp = 0;
		RePrintData.fanOnoff = 0;
		RePrintData.fanSpeed = 0;
	}	


	HAL::AT24CXX_Read(BAK_REPRINT_X,(uint8_t *)&RePrintData.saveX,4);
	HAL::AT24CXX_Read(BAK_REPRINT_Y,(uint8_t *)&RePrintData.saveY,4);
	HAL::AT24CXX_Read(BAK_REPRINT_Z,(uint8_t *)&RePrintData.saveZ,4);
	
	//RePrintData.digxor = dataFrEeprom & 0x000000ff;
	((srcfp)->fptr) = 0;	//重置文件指针
	if(RePrintLocal() == 0) 
		return;				//定位失败
	

/*---------------------------------------*/	
	//printerStaus = pr_working;		//print test
	usart2Data.printer = printer_waiting;
/*---------------------------------------*/

	gCfgItems.desireBedTemp = RePrintData.bedTemp;
	gCfgItems.fanOnoff = RePrintData.fanOnoff;
	gCfgItems.fanSpeed= RePrintData.fanSpeed;
	
/*--------------获取目标温度-------*/

	gCfgItems.desireSprayerTemp[0] = RePrintData.t0Temp;
	gCfgItems.desireSprayerTemp[1] = RePrintData.t1Temp;

/*---------------------------------------*/
	switch(RePrintData.printerStatus)
	{
		case printer_normal:
			break;
		case printer_pause_reprint:
			if(gCfgItems.machineType == 2)
				deltaPauseReGcode();
			else
				{
					switch(saveFlagR)
					{
						case 0xa5:
							pauseSaveReGcode();
							break;
						case 0:
							pauseReGcode();
							break;
						default :
							deltaPauseReGcode();
							break;
					}
				}
			
			break;
		case printer_pwdwn_reprint:
			if(gCfgItems.machineType == 2)
				deltaPauseReGcode();
			else
				pwdwnReGcode();
			break;
		default :break;
	}
	
	RePrintData.printerStatus = printer_normal;
	
}

void rePrintdata_show()
{
	volatile uint32_t dataFrEeprom_tmp=0xc1c2c3c4;
	volatile uint32_t time;
//时间
	HAL::AT24CXX_Read(BAK_REPRINT_TIME,(uint8_t *)&time,  4);
	print_time.hours = (time >> 16)  & 0xffff;
	print_time.minutes = (time >> 8)  & 0xff;
	
	if((print_time.hours == 0xffff)&&(print_time.minutes == 0xff))
	{
		print_time.hours = 0;
		print_time.minutes = 0;
	}

//喷头温度
	HAL::AT24CXX_Read(BAK_REPRINT_HTEMP,(uint8_t *)&dataFrEeprom_tmp,4);
	RePrintData.t0Temp = (dataFrEeprom_tmp >> 16) & 0x0000ffff;
	RePrintData.t1Temp = dataFrEeprom_tmp  & 0x0000ffff;
	if((RePrintData.t0Temp == 0xffff)&&(RePrintData.t1Temp == 0xffff))
	{
		RePrintData.t0Temp = 0;
		RePrintData.t1Temp = 0;
	}	
//热床风扇	
	HAL::AT24CXX_Read(BAK_REPRINT_INFO,(uint8_t *)&dataFrEeprom_tmp,4);
	RePrintData.fanOnoff = (dataFrEeprom_tmp >> 16)&0x0000000f;
	RePrintData.fanSpeed = (dataFrEeprom_tmp >> 8)&0x000000ff;
	RePrintData.bedTemp = (dataFrEeprom_tmp)&0x000000ff;
	if((RePrintData.bedTemp == 0xff)&&(RePrintData.fanOnoff == 0x0f)&&(RePrintData.fanSpeed == 0xff))
	{
		RePrintData.bedTemp = 0;
		RePrintData.fanOnoff = 0;
		RePrintData.fanSpeed = 0;
	}	
	/*---------------------------------------*/
	gCfgItems.desireBedTemp = RePrintData.bedTemp;
	gCfgItems.fanOnoff = RePrintData.fanOnoff;
	gCfgItems.fanSpeed= RePrintData.fanSpeed;
		
	/*--------------获取目标温度-------*/
	gCfgItems.desireSprayerTemp[0] = RePrintData.t0Temp;
	gCfgItems.desireSprayerTemp[1] = RePrintData.t1Temp;

}

/*
void getCheck(unsigned char *txBuf)	
{
		unsigned char *p;
		p= txBuf;
		RePrintData.checkXor = 0;
		RePrintData.checkSum = 0;
		RePrintData.digxor = 0;
		if(*p != 'N')	return;				
		while(*p++ != ' ');

		while(*p != '*')
		{
			RePrintData.checkXor ^= *p;
			RePrintData.checkSum += *p;
			if((*p >= '0') && (*p <= '9'))
				RePrintData.digxor ^= (*p -0x30)*28;
			
			p++;
		}
		
}
*/
#if 0
volatile uint32_t store_pwdwn_data[4]={0};

void rePrintSaveData()
{

		volatile uint8_t record_cnt;
		volatile uint32_t dataToEeprom=0xc1c2c3c4;
		
		if(printerStaus == pr_idle) 
			return;
		if(RePrintData.printerStatus != printer_normal)
			return; //防止pause时多次保存参数
		if(RePrintData.offset < 3072) //打印太少，防止正在加热时断电
			return;
		 
		__set_PRIMASK(1); 		 //关闭总中断
		__set_FAULTMASK(1);
				 
		switch(printerStaus)
		{
			case	pr_working:
				RePrintData.printerStatus = printer_pwdwn_reprint;
				break;
			case	pr_pause:
				dataToEeprom = 0; //SAVE_DIS
				HAL::AT24CXX_Write( BAK_REPRINT_S,(uint8_t *)&dataToEeprom,	4); 	//null(uint24_t) | saveFlag(uint8_t)
				RePrintData.printerStatus = printer_pause_reprint;
				break;
			case pr_idle:
				RePrintData.printerStatus = printer_normal;
				break;
			default :break;
		} 
		store_pwdwn_data[0] = (((uint32_t)RePrintData.printerStatus << 24)&0xff000000)\
								|(((uint32_t)RePrintData.spayerchoose<<20) & 0x00f00000)\
								|(((uint32_t)gCfgItems.fanOnoff<<16) & 0x000f0000)\
								|(((uint32_t)gCfgItems.fanSpeed<<8) & 0x0000ff00)\
								|(((uint32_t)gCfgItems.desireBedTemp) & 0x000000ff);
			
		if(RePrintData.printerStatus == printer_pause_reprint)
		{
				for(record_cnt=0;record_cnt<30;record_cnt++)
				{
					if(Gcode_current_position[record_cnt].Gcode_LineNumb == (RePrintData.record_line))
					{
							store_pwdwn_data[1] = Gcode_current_position[record_cnt].Gcode_fileOffset;
							break;
					}
				}
		}
		else
		{
			store_pwdwn_data[1] = RePrintData.offset;
		}

		store_pwdwn_data[2] = (((uint32_t)gCfgItems.desireSprayerTemp[0]<< 16) & 0xffff0000) | ((uint32_t)gCfgItems.desireSprayerTemp[1]& 0x0000ffff);
		
		store_pwdwn_data[3] = (((uint32_t)print_time.hours << 16) & 0xffff0000) | (((uint32_t)print_time.minutes << 8) & 0x0000ff00);

		HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *)&store_pwdwn_data , 16);
		
		__set_PRIMASK(0); 		//开放总中断
		__set_FAULTMASK(0);

}

#endif
volatile uint32_t store_pwdwn_data[4]={0};
/*
*store_pwdwn_data[0]: 		续打标志(uint8_t) | 喷头选择(高4位) 风扇开关状态(低四位)|风速8位| 热床温度8位
*store_pwdwn_data[1]: 	offset(uint32_t)
*store_pwdwn_data[2]: 	T0Temp(uint16_t)	| T1Temp(uint16_t)
*store_pwdwn_data[3]: 	hours(int16_t) | minutes(int8_t) ;
*store_pwdwn_data[4]: 	
*store_pwdwn_data[5]: 	
*store_pwdwn_data[6]: 	
*store_pwdwn_data[7]: 	
*store_pwdwn_data[8]:
*store_pwdwn_data[8]:
*/

void rePrintSaveData()
{
	volatile uint8_t record_cnt;
	volatile uint32_t dataToEeprom=0xc1c2c3c4;
	//uint8_t dataToEeprom8;
	//static uint8_t hours_temp1,hours_temp2;

	if(printerStaus == pr_idle)	
		return;
	 
	 if(RePrintData.printerStatus != printer_normal)
		return; //防止pause时多次保存参数
	
	 if(RePrintData.offset < 3*UDISKBUFLEN)	//打印太少，防止正在加热时断电
	 {
		 return;
		 /*
		 if(printerStaus == pr_working)	
		 {
				FALACTL = FALA_OFF;		//关电容
				while(1);							
		 }
		 else
			 return;
		 */
	 }
	__set_PRIMASK(1);				//关闭总中断
	__set_FAULTMASK(1);
	
	switch(printerStaus)
	{
		case  pr_working:
			RePrintData.printerStatus = printer_pwdwn_reprint;
			break;
		case  pr_pause:
			dataToEeprom = 0;	//SAVE_DIS
			HAL::AT24CXX_Write(BAK_REPRINT_S, (uint8_t *)&dataToEeprom,  4);		//null(uint24_t) | saveFlag(uint8_t)
			RePrintData.printerStatus = printer_pause_reprint;
			break;
		case pr_idle:
			RePrintData.printerStatus = printer_normal;
			break;
		default :break;
	}
	#if 0
	//dataToEeprom = (((uint32_t)RePrintData.printerStatus << 24)&0xff000000)| (((uint32_t)RePrintData.unit<<16) & 0x00ff0000) | (((uint32_t)RePrintData.saveFlag << 8) & 0x0000ff00);

	dataToEeprom = (((uint32_t)RePrintData.printerStatus << 24)&0xff000000)\
					|(((uint32_t)RePrintData.spayerchoose<<20) & 0x00f00000)\
					|(((uint32_t)gCfgItems.fanOnoff<<16) & 0x000f0000)\
					|(((uint32_t)gCfgItems.fanSpeed<<8) & 0x0000ff00)\
					|(((uint32_t)gCfgItems.desireBedTemp) & 0x000000ff);
	HAL::AT24CXX_Write(BAK_REPRINT_INFO, (uint8_t *)&dataToEeprom,  4); 		// 续打标志(uint8_t) | unit (uint8_t) | checkSum(uint16_t)
//	dataToEeprom = RePrintData.offset;
//	I2C_EE_BufferWrite(&dataToEeprom, BAK_REPRINT_OFFSET,  4);	// offset(uint32_t)
#endif
	store_pwdwn_data[0] = (((uint32_t)RePrintData.printerStatus << 24)&0xff000000)\
							|(((uint32_t)RePrintData.spayerchoose<<20) & 0x00f00000)\
							|(((uint32_t)gCfgItems.fanOnoff<<16) & 0x000f0000)\
							|(((uint32_t)gCfgItems.fanSpeed<<8) & 0x0000ff00)\
							|(((uint32_t)gCfgItems.desireBedTemp) & 0x000000ff);

if(RePrintData.printerStatus == printer_pause_reprint)
{
	for(record_cnt=0;record_cnt<30;record_cnt++)
	{
		if(Gcode_current_position[record_cnt].Gcode_LineNumb == (RePrintData.record_line))
		{
				//dataToEeprom = Gcode_current_position[record_cnt].Gcode_fileOffset;
				//HAL::AT24CXX_Write(BAK_REPRINT_OFFSET, (uint8_t *)&dataToEeprom,  4);	// line_numb(uint32_t)
				store_pwdwn_data[1] = Gcode_current_position[record_cnt].Gcode_fileOffset;
				break;
		}
	}
}
else
{
	#if 0
	dataToEeprom = RePrintData.offset;
	HAL::AT24CXX_Write(BAK_REPRINT_OFFSET,(uint8_t *)&dataToEeprom ,  4);	// offset(uint32_t)	
	#endif
	store_pwdwn_data[1] = RePrintData.offset;
}

	#if 0
	//dataToEeprom = (((uint32_t)RePrintData.t0Temp << 16) & 0xffff0000) | ((uint32_t)RePrintData.t1Temp & 0x0000ffff);
	dataToEeprom = (((uint32_t)gCfgItems.desireSprayerTemp[0]<< 16) & 0xffff0000) | ((uint32_t)gCfgItems.desireSprayerTemp[1]& 0x0000ffff);
	HAL::AT24CXX_Write(BAK_REPRINT_HTEMP, (uint8_t *)&dataToEeprom,  4);		// T0Temp(uint16_t)	| T1Temp(uint16_t)
	
	//RePrintData.bedTemp = gCfgItems.curBedTemp;
	//RePrintData.fanOnoff = gCfgItems.fanOnoff;
	//RePrintData.fanSpeed = gCfgItems.fanSpeed;
	
	//dataToEeprom = (((uint32_t)RePrintData.bedTemp << 24)&0xff000000) | (((uint32_t)RePrintData.fanOnoff << 16) & 0x00ff0000) | (((uint32_t)RePrintData.fanSpeed << 8) & 0x0000ff00 );
	//I2C_EE_BufferWrite(&dataToEeprom, BAK_REPRINT_FAN,  4);			// BedTemp(uint8_t)	| fanOnoff(uint8_t) |fanSpeed(uint8_t) |digxor(uint8_t)
	
	//RePrintData.hours = print_time.hours;
	//RePrintData.minutes = print_time.minutes;
	
	//dataToEeprom = (((uint32_t)RePrintData.hours << 16) & 0xffff0000) | (((uint32_t)RePrintData.minutes << 8) & 0x0000ff00);
	//I2C_EE_BufferWrite((uint8_t*)&dataToEeprom, BAK_REPRINT_TIME,  4);	////hours(int16_t) | minutes(int8_t) 
	
	dataToEeprom = (((uint32_t)print_time.hours << 16) & 0xffff0000) | (((uint32_t)print_time.minutes << 8) & 0x0000ff00);
	HAL::AT24CXX_Write(BAK_REPRINT_TIME,(uint8_t *)&dataToEeprom ,  4);	////hours(int16_t) | minutes(int8_t) 	
	//	gCfgItems.machineType

	/*	
	if(printerStaus == pr_working)
	{
		FALACTL = FALA_OFF;		//关电容
		while(1);							
		NVIC_SystemReset();		//复位
	}
	*/
	#endif
	store_pwdwn_data[2] = (((uint32_t)gCfgItems.desireSprayerTemp[0]<< 16) & 0xffff0000) | ((uint32_t)gCfgItems.desireSprayerTemp[1]& 0x0000ffff);
	
	store_pwdwn_data[3] = (((uint32_t)print_time.hours << 16) & 0xffff0000) | (((uint32_t)print_time.minutes << 8) & 0x0000ff00);

	HAL::AT24CXX_Write(BAK_REPRINT_INFO,(uint8_t *)&store_pwdwn_data, 16);	
	
	__set_PRIMASK(0);			//开放总中断
	__set_FAULTMASK(0);
	//BACKLIGHT = BACKLIGHT_ON;

}
/*-------------------------------------------*/


void EXTIX_Init(void)
{
#if 0
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef_TFT GPIO_InitStructure;

	// 开启AFIO的时钟 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		if(gCfgItems.print_finish_close_machine_flg == 1)
		{
			// 开启AFIO的时钟 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init_TFT(GPIOB, &GPIO_InitStructure);

			GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

			EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
	    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	    EXTI_Init(&EXTI_InitStructure);
		}
		else
		{

		// 将KEY4 按键对应的管脚连接到内部中断线    
	    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
		
    // 将KEY4 按键配置为中断模式，下降沿触发中断    
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

		}

    // 将KEY4 按键的中断优先级配置为最低   
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
#endif	
}


void tftGPIOCfg()
{
	/*GPIO_InitTypeDef_TFT GPIO_InitStructure;
	#if (debug_flg != 1)
			RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	 //PORTB时钟使能 
		  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4;//PB0 PB1 PB4
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init_TFT (GPIOB, &GPIO_InitStructure);
	#endif*/				
}


void rePrintInit()
{
	uint32_t eepromRead;
	
	RePrintData.printerStatus	= (RE_PRINT_STATUS)0xff;
	RePrintData.unit = 0;	//0 mm, 1 inch
	
	tftGPIOCfg();
	
	#if defined(TFT35)
	
	#ifdef SAVE_FROM_SD
	if(gCfgItems.pwroff_save_mode != 0)
	#endif
	{
		FALACTL = FALA_ON;			//debug
	}
	#ifdef SAVE_FROM_SD
	else
	{
		FALACTL = FALA_OFF;
	}
	
	//SPEAKER = SPEAKER_ON;		//sky_test
	if(gCfgItems.pwroff_save_mode != 0)
	#endif
	{
		//EXTIX_Init();
		exit_PA0_init();
	}
	#endif	

}
/**-------------------------------------------------------
  * @函数名 EXTI0_IRQHandler
  * @功能   处理外部中断线0的中断，按键4中断处理函数
  * @参数   无
  * @返回值 无
***------------------------------------------------------*/

extern "C" void EXTI0_IRQHandler(void);   //**

void EXTI0_IRQHandler(void)  
{
#if 1
	//static uint8_t hours_temp1,hours_temp2;
	EXTI_ClearITPendingBit(EXTI_Line0);		//清除中断

	__ASM volatile("cpsid i");            //禁止中断  
	
	/*---------test----------------*/
	//for(int i=0;i<10;i++)
		//4byte//
		//while(1);
	/*---------test----------------*/



	
  	//__HAL_RCC_GPIOC_CLK_DISABLE();
  	//__HAL_RCC_GPIOD_CLK_DISABLE();
	
	


	//关闭串口2/3模块，节省功耗
	//USART_Cmd(USART3, DISABLE);
	//USART_Cmd(USART2, DISABLE);

    //GPIO_InitStructure_com3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //GPIO_InitStructure_com3.GPIO_Pin |= GPIO_Pin_8|GPIO_Pin_9;
    //GPIO_Init(GPIOD, &GPIO_InitStructure_com3);

    //GPIO_InitStructure_com3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //GPIO_InitStructure_com3.GPIO_Pin |= GPIO_Pin_8;
    //GPIO_Init(GPIOA, &GPIO_InitStructure_com3);
	/*if(gCfgItems.print_finish_close_machine_flg == 1)
	{
		btn_putdown_time_flg = 1;
		btn_putdown_cnt = 0;

		//Print_finish_close_machine();
	}*/

	BACKLIGHT = BACKLIGHT_OFF;
	rePrintSaveData();    //暂时不开放!
  	__ASM volatile("cpsie i");    //允许中断	
//	__set_PRIMASK(0);			//开放总中断
//	__set_FAULTMASK(0);
	//SPEAKER = 1;
	//BACKLIGHT = BACKLIGHT_ON;				
#if defined(TFT70)
	FALACTL = FALA_OFF;
	RESET_1963=0;
    RESET_1963=1;
	while(1);
#endif	
  #endif
}



unsigned char getGcode(void)
{
	gp=gcode;
	ulockCnt=0;

	if(udiskBuffer.state[udiskBuffer.current] == udisk_buf_empty)	//buffer?
		return 0;

			while(*udiskBuffer.p != '\n'  && *udiskBuffer.p != '\r')	//???
			{
				if(gp-gcode > (FIFO_SIZE-10))	//??????,??,????????
				{
					*(udiskBuffer.p +1)= ';';
					break;
				}

				if(ulockCnt++ > FIFO_SIZE && gp == gcode)		//????? ????
					return 0;

				if(*udiskBuffer.p == ';')	//?? ';' ?????
					note_flag =  0;

				if(note_flag)
					*gp++ = *udiskBuffer.p++;	//????gcode??
				else
					udiskBuffer.p++;

				if(udiskBuffer.p == udiskBuffer.buffer[udiskBuffer.current]+ UDISKBUFLEN)	//??buffer ????,?????buffer
				{
					memset(udiskBuffer.buffer[udiskBuffer.current],'\n',sizeof(udiskBuffer.buffer[0]));		//buffer ???'\n'
					udiskBuffer.state[udiskBuffer.current] = udisk_buf_empty;								//buffer ???empty
					udiskBuffer.current = (udiskBuffer.current+1)%2;										//????buffer
					udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];								//???????buffer
				}

			}
			udiskBuffer.p++;	//??'\n'??
			if(udiskBuffer.p == udiskBuffer.buffer[udiskBuffer.current]+ UDISKBUFLEN)	//??buffer ????,?????buffer
				{
					memset(udiskBuffer.buffer[udiskBuffer.current],'\n',sizeof(udiskBuffer.buffer[0]));		//buffer ???'\n'
					udiskBuffer.state[udiskBuffer.current] = udisk_buf_empty;								//buffer ???empty
					udiskBuffer.current = (udiskBuffer.current+1)%2;										//????buffer
					udiskBuffer.p = udiskBuffer.buffer[udiskBuffer.current];								//???????buffer
				}
			

			note_flag = 1;		

}

void saveCharToInt(unsigned char *src, unsigned char EppAddr)
{
	unsigned int intPart;
	//unsigned char fltPart[2];
	unsigned char tmpStrPst[10];
	unsigned char *p=tmpStrPst;
	volatile unsigned char negativeFlag = 0; 
	
	while(*src < '0' || *src > '9')
		src++;

	negativeFlag = 0; 
	if(*(src-1) == '-')	//负数
		negativeFlag = 1;
	
	p=tmpStrPst;
	//while(*src != '.' && *src !='\n' && *src !=' ' )
	while(*src >= '0' && *src <='9')
		{
			*p++ = *src++; 
			if(p > (tmpStrPst + 8)) break;
		}
	
	*p = '\0';
	intPart = atoi((const char *)&tmpStrPst[0]);
	if(negativeFlag == 1)
		intPart |= 0x8000;
	
	
	while(*src < '0' || *src > '9')
		src++;
	
	p=tmpStrPst;
	while(*src >= '0' && *src <='9')
		{
		*p++ = *src++;
		if(p > (tmpStrPst + 8)) break;		
		}
	//*p = '\0';
	//fltPart = atoi(&tmpStrPst[0]);

	dataToEeprom = (((uint32_t)intPart << 16) & 0xffff0000) | (((uint32_t)tmpStrPst[0] << 8) & 0x0000ff00) |((uint32_t)tmpStrPst[1]  & 0x000000ff);
	HAL::AT24CXX_Write(EppAddr,(uint8_t *)&dataToEeprom , 4);		
	
}
void positionSaveProcess()
{
	unsigned char M114Gode[6]="M114\n";
	volatile unsigned int i=0;
	
	while(checkFIFO(&gcodeCmdTxFIFO) == fifo_full)
	{
		//防止死循环
		popFIFO(&gcodeCmdTxFIFO,codebuff);//复用全局变量codebuff，减少空间
	}

	RePrintData.saveEnable = 1;

	pushFIFO(&gcodeCmdTxFIFO,M114Gode);
	
	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		//usart2Data.prWaitStatus = pr_wait_data;		
		usart2Data.prWaitStatus = pr_wait_cmd;
		usart2TxStart();
	}
	

	//while(RePrintData.saveEnable);	

	i=0;
	while(1)
	{
		if(RePrintData.saveEnable == 1)	//gcodeTxFIFO.count >0
		{
			tftDelay(50);
			i++;
			if(i> 200) break;
		}
		else
			break;
	}


	
	if(RePrintData.saveEnable ==0)
	{
		RePrintData.saveFlag = SAVE_ENA;
		dataToEeprom = 0xa5;	//SAVE_ENA
		HAL::AT24CXX_Write(BAK_REPRINT_S,(uint8_t *)&dataToEeprom ,  4); 		//null(uint24_t) | saveFlag(uint8_t)
		//RePrintData.saveFlag = SAVE_DIS;
	

		saveCharToInt(RePrintData.x_coordinate, BAK_REPRINT_X);
		saveCharToInt(RePrintData.y_coordinate, BAK_REPRINT_Y);
		saveCharToInt(RePrintData.z_coordinate, BAK_REPRINT_Z);
	}
}


void Get_Z_Pos_display_value()
{
	unsigned char M114Gode[6]="M114\n";
	volatile unsigned int i=0;
	
	while(checkFIFO(&gcodeCmdTxFIFO) == fifo_full)
	{
		//防止死循环
		popFIFO(&gcodeCmdTxFIFO,codebuff);//复用全局变量codebuff，减少空间
	}

	gCfgItems.getzpos_enable= 1;

	pushFIFO(&gcodeCmdTxFIFO,M114Gode);
	
	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		//usart2Data.prWaitStatus = pr_wait_data;		
		usart2Data.prWaitStatus = pr_wait_cmd;
		usart2TxStart();
	}
/*
	i=0;
	while(1)
	{
		if(gCfgItems.getzpos_enable == 1)	//gcodeTxFIFO.count >0
		{
			tftDelay(50);
			i++;
			if(i> 200) break;
		}
		else
			break;
	}
	*/
	/*
	if(RePrintData.saveEnable ==0)
	{
		i=0;
		while(RePrintData.mov_z_coordinate[i]!= '\n')
		{
			gCfgItems.move_z_coordinate[i] = RePrintData.mov_z_coordinate[i];
			i++;
			if(i>20)break;
		}
		gCfgItems.move_z_coordinate[i] = 0;
		//gCfgItems.zpos = atof(gCfgItems.move_z_coordinate);
		//GUI_DispStringAtCEOL(gCfgItems.move_z_coordinate,220, 0);
	}
*/
}

void getZPosition()         
{
	unsigned char *p = &usart2Data.usart2Rxbuf[0];
	unsigned char positionCnt = 0;

	while(*p != '\n')
	{
		switch(*p)
		{
			case 'X':
				
				if(positionCnt == 0) 
					{
					copySaveCoordinate(p,RePrintData.mov_x_coordinate);
					positionCnt++;
					}
				break;
			case 'Y':
				if(positionCnt == 1) 
					{
					copySaveCoordinate(p,RePrintData.mov_y_coordinate);
					positionCnt++;
					}
				break;
			case 'Z':
				if(positionCnt == 2) 
					{
					copySaveCoordinate(p,RePrintData.mov_z_coordinate);
					positionCnt++;
					}
				break;
			case 'E':
				if(positionCnt == 3)
					{
					copySaveCoordinate(p,RePrintData.mov_e_coordinate);
					positionCnt++;
					}
				break;
				
			default : break;
		}
		p++;
		if(positionCnt > 3) break;
			
	}

	if(positionCnt > 3)
	{
		gCfgItems.getzpos_enable = 0;
	}
}

