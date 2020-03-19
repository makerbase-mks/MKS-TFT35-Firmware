//**#include "draw_ui.h"


#include "mks_tft_function.h"
#include "mks_tft_com.h"
#include "mks_cfg.h"
unsigned char homeFlag = 0;
unsigned char heatFlag = 0;




unsigned char x_pauseBak[COORDINATELENGTH];
unsigned char y_pauseBak[COORDINATELENGTH];
unsigned char z_pauseBak[COORDINATELENGTH];
unsigned char e_pauseBak[COORDINATELENGTH];

unsigned char z_breakpoint[COORDINATELENGTH];
unsigned char z_file[COORDINATELENGTH];
unsigned char breakpoint_homeFlag=0;

volatile unsigned long BeeperFreq=0;
volatile unsigned char BeeperCnt=0;
volatile unsigned char mksBpAlrmEn=0;


extern volatile uint8_t get_temp_flag;

extern CFG_ITMES gCfgItems;
/*
unsigned char homeXY()
{
	volatile unsigned int i;
	unsigned char homeGcode0[5]="M116\n";
	unsigned char homeGcode1[4]="G91\n";
	unsigned char homeGcode2[7]="G1 E-1\n";
	unsigned char homeGcode3[6]="G1 Z5\n";
	//unsigned char homeGcode2[6]="G0 Z5\n";
	unsigned char homeGcode4[4]="G90\n";
	unsigned char homeGcode5[5]="M114\n";
	
	unsigned char *p;
	//unsigned char homeGcode4[10]="G28 X0 Y0\n";
	volatile unsigned int dlyCnt = 0;
	
	
	//return;
	
	if(homeFlag == 1)	return 0;
	if(heatFlag == 1) return 0;

	if(gcodeLineCnt < 50)	//防止热床或打印头加热，触屏无反应
		dlyCnt = 70;
	else
		dlyCnt = 580;		//280	//防止执行 需时间较长的GCODE ,等待时间不够
	
			i=0;
			while(1)
			{
				if(gcodeTxFIFO.count >(FIFO_NODE-6)) 	//gcodeTxFIFO.count >0
				{
					tftDelay(100);
					i++;
					if(i> dlyCnt) 
					{
						heatFlag = 1;
						return 0;
					}
				}
				else
					break;
			}
			

	//p = (gcodeTxFIFO.tail == gcodeTxFIFO.buffer[0])?  gcodeTxFIFO.buffer[FIFO_NODE-1]:gcodeTxFIFO.tail - FIFO_SIZE;
	//getCheck(p); //获取校验值
	if(firmwareType != repetier)
		pushFIFO(&gcodeTxFIFO,homeGcode0);
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode1);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode2);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode3);	
	pushFIFO(&gcodeTxFIFO,homeGcode4);	
	RePrintData.saveEnable = 1;
	pushFIFO(&gcodeTxFIFO,homeGcode5);
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	//pushFIFO(&gcodeTxFIFO,homeGcode4);	

	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		usart2Data.prWaitStatus = pr_wait_data;
		usart2TxStart();
	}
	
	homeFlag = 1;

	//while(RePrintData.saveEnable);	//delay
	
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
	
	//tftDelay(1000);
	if(RePrintData.saveEnable == 0)
	{
		x_pauseBak[0] = RePrintData.x_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			x_pauseBak[i] = RePrintData.x_coordinate[i+1];

		y_pauseBak[0] = RePrintData.y_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			y_pauseBak[i] = RePrintData.y_coordinate[i+1];

		z_pauseBak[0] = RePrintData.z_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			z_pauseBak[i] = RePrintData.z_coordinate[i+1];

		e_pauseBak[0] = RePrintData.e_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			e_pauseBak[i] = RePrintData.e_coordinate[i+1];
	}
	return 1;
}
*/


	unsigned char breakpoint_homeXY()
	{
		volatile unsigned int i,j;

		unsigned char homeGcode5[5]="M114\n";

		//unsigned char homeGcode_tmp0[15]="N-1 M110*15\n";
		
		if(breakpoint_homeFlag == 1) return 0;
	
		RePrintData.saveEnable = 1;
		pushFIFO(&gcodeCmdTxFIFO,homeGcode5);
	
		if(usart2Data.printer == printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
		{
			popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]); //发送数据
			usart2TxStart();
		}
		
		breakpoint_homeFlag = 1;
		
		i=0;
		while(1)
		{
			if(RePrintData.saveEnable == 1) //gcodeTxFIFO.count >0
			{
				tftDelay(50);
				i++;
				if(i> 200) break;
			}
			else
				break;
		}
	
		if(RePrintData.saveEnable == 0)
		{
			x_pauseBak[0] = RePrintData.x_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				x_pauseBak[i] = RePrintData.x_coordinate[i+1];
	
			y_pauseBak[0] = RePrintData.y_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				y_pauseBak[i] = RePrintData.y_coordinate[i+1];
	
			z_pauseBak[0] = RePrintData.z_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				z_pauseBak[i] = RePrintData.z_coordinate[i+1];
	
			e_pauseBak[0] = RePrintData.e_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				e_pauseBak[i] = RePrintData.e_coordinate[i+1];

			//计算Z轴当前位置
			if(gCfgItems.pwd_reprint_flg==1)
			{
				i=0;
				memset(z_breakpoint,0,sizeof(z_breakpoint));
				while((z_pauseBak[i+1]!='\r')&&(z_pauseBak[i+1]!='\n')&&(i<20))
				{
					z_breakpoint[i]= z_pauseBak[i+1];
					i++;
				}
				z_breakpoint[i]='\0';

				DecStr2Float(z_breakpoint,(float *)&gCfgItems.z_current_position);
				if(gCfgItems.z_current_position > 0)
				{
					gCfgItems.findpoint_start = 1;
					return 1;
				}
				else
				{
					GUI_DispStringAtCEOL("resume error",200, 0);
				}
			}
			
		}
		return 0;

	} 
	
	uint8_t homeFlag_second=0;	
	
unsigned char homeXY()
{
	volatile unsigned int i;
	unsigned char homeGcode0[5]="M116\n";
	unsigned char homeGcode1[4]="G91\n";
	unsigned char homeGcode2[7]="G1 E-1\n";
	//unsigned char homeGcode3[6]="G1 Z5\n";
	unsigned char homeGcode3[15]="G1 Z";
	//unsigned char homeGcode2[6]="G0 Z5\n";
	unsigned char homeGcode4[4]="G90\n";
	unsigned char homeGcode5[5]="M114\n";
	unsigned char homeGcode6[15]="G1 X";
	unsigned char homeGcode7[15]="G1 Y";
	unsigned char *p;
	//unsigned char homeGcode4[10]="G28 X0 Y0\n";
	volatile unsigned int dlyCnt = 0;
	unsigned char homeGcode_tmp0[7];
	//return;
	if((RePrintData.saveEnable == 0)&&(homeFlag_second==1))
	{
		RePrintData.saveEnable = 1;
		pushFIFO(&gcodeCmdTxFIFO,homeGcode5);
		while(1)
		{
			if(RePrintData.saveEnable == 1) //gcodeTxFIFO.count >0
			{
				tftDelay(50);
				i++;
				if(i> 200) break;
			}
			else
				break;
		}
		if(RePrintData.saveEnable == 0)
		{
			x_pauseBak[0] = RePrintData.x_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				x_pauseBak[i] = RePrintData.x_coordinate[i+1];

			y_pauseBak[0] = RePrintData.y_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				y_pauseBak[i] = RePrintData.y_coordinate[i+1];

			z_pauseBak[0] = RePrintData.z_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				z_pauseBak[i] = RePrintData.z_coordinate[i+1];

			e_pauseBak[0] = RePrintData.e_coordinate[0];
			for(i=1;i<(COORDINATELENGTH-1);i++)
				e_pauseBak[i] = RePrintData.e_coordinate[i+1];	
		}
		homeFlag_second = 0;
	}
	
	if(homeFlag == 1) return 0;
	if(heatFlag == 1) return 0;

	//initFIFO(&gcodeCmdTxFIFO);
/*
	if(gcodeLineCnt < 50) //防止热床或打印头加热，触屏无反应
		dlyCnt = 70;
	else
		dlyCnt = 580; 	//280 //防止执行 需时间较长的GCODE ,等待时间不够
	
			i=0;
			while(1)
			{
				if(gcodeCmdTxFIFO.count >(FIFO_NODE-6))	//gcodeTxFIFO.count >0
				{
					tftDelay(100);
					i++;
					if(i> dlyCnt) 
					{
						heatFlag = 1;
						return 0;
					}
				}
				else
					break;
			}
*/
		if(gcodeLineCnt < 50) //防止热床或打印头加热，触屏无反应
		{
			heatFlag = 1;
			return 0;
		}

	//p = (gcodeTxFIFO.tail == gcodeTxFIFO.buffer[0])?	gcodeTxFIFO.buffer[FIFO_NODE-1]:gcodeTxFIFO.tail - FIFO_SIZE;
	//getCheck(p); //获取校验值
	if(firmwareType != repetier)
		pushFIFO(&gcodeCmdTxFIFO,homeGcode0);
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode1);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode2);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);

	memset(homeGcode3,0,sizeof(homeGcode_tmp0));
	sprintf(homeGcode3,"G1 Z%d\n",gCfgItems.Pause_ZADD);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode3);	
	
	pushFIFO(&gcodeCmdTxFIFO,homeGcode4);

	
	if(gCfgItems.Pause_XPOS != -1)
	{
		//sprintf(homeGcode_tmp0,"%d",gCfgItems.Pause_XPOS);
		//strcat(homeGcode6,homeGcode_tmp0);
		//strcat(homeGcode6,"\n");
		memset(homeGcode6,0,sizeof(homeGcode6));
		sprintf(homeGcode6,"G1 X%d\n",gCfgItems.Pause_XPOS);		
		pushFIFO(&gcodeCmdTxFIFO,homeGcode6);
		positionSaveFlag = 1;
	}
	if(gCfgItems.Pause_YPOS != -1)
	{
		//sprintf(homeGcode_tmp0,"%d",gCfgItems.Pause_YPOS);
		//strcat(homeGcode7,homeGcode_tmp0);
		//strcat(homeGcode7,"\n");	

		memset(homeGcode7,0,sizeof(homeGcode7));
		sprintf(homeGcode7,"G1 Y%d\n",gCfgItems.Pause_YPOS);
		pushFIFO(&gcodeCmdTxFIFO,homeGcode7);
		positionSaveFlag = 1;
	}
	RePrintData.saveEnable = 1;
	pushFIFO(&gcodeCmdTxFIFO,homeGcode5);
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	//pushFIFO(&gcodeTxFIFO,homeGcode4);	

	if(usart2Data.printer == printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]); //发送数据
		//usart2Data.prWaitStatus = pr_wait_data;
		usart2Data.prWaitStatus = pr_wait_cmd;
		usart2TxStart();
	}
	
	homeFlag = 1;

	//while(RePrintData.saveEnable);	//delay
	
	i=0;
	while(1)
	{
		if(RePrintData.saveEnable == 1) //gcodeTxFIFO.count >0
		{
			tftDelay(50);
			i++;
			if(i> 200) break;
		}
		else
			break;
	}
	homeFlag_second = 1;
	//tftDelay(1000);
	if(RePrintData.saveEnable == 0)
	{
		x_pauseBak[0] = RePrintData.x_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			x_pauseBak[i] = RePrintData.x_coordinate[i+1];

		y_pauseBak[0] = RePrintData.y_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			y_pauseBak[i] = RePrintData.y_coordinate[i+1];

		z_pauseBak[0] = RePrintData.z_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			z_pauseBak[i] = RePrintData.z_coordinate[i+1];

		e_pauseBak[0] = RePrintData.e_coordinate[0];
		for(i=1;i<(COORDINATELENGTH-1);i++)
			e_pauseBak[i] = RePrintData.e_coordinate[i+1];

		homeFlag_second = 0;
		return 1;		
	}
	return 1;
}

void relocalZ(void)
{
	unsigned char homeGcode0[5]="M116\n";
	unsigned char homeGcode1[4]="G91\n";
	//unsigned char homeGcode2[7]="G1 Z-5\n";
	unsigned char homeGcode2[18]="G1 Z-";
	unsigned char homeGcode3[9]="G1 E1.5\n";
	//unsigned char homeGcode2[7]="G0 Z-5\n";
	unsigned char homeGcode4[4]="G90\n";	

	unsigned char homeGcode_tmp1[7];

	//unsigned char tmpBuf[FIFO_SIZE];
//	unsigned char i;

//	unsigned char *p;
//	unsigned char flag;
	
//	return;
	if(homeFlag ==0) return;
#if 0	
	while(checkFIFO(&gcodeCmdTxFIFO) != fifo_empty)
	{
		//防止串口停止发送，进入死循环
		if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
		{
			usart2Data.printer = printer_working;
			popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
			usart2Data.prWaitStatus = pr_wait_cmd;
			usart2TxStart();
		}	

	
		#if debug_flg == 1
		T_function(100,1);
		#endif
	}
#endif
	if(firmwareType != repetier)
		pushFIFO(&gcodeCmdTxFIFO,homeGcode0);
	
	pushFIFO(&gcodeCmdTxFIFO,homeGcode1);
	memset(homeGcode2, 0, sizeof(homeGcode2));
	sprintf(homeGcode2,"G1 Z-%d\n",gCfgItems.Pause_ZADD);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode2);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode3);
	pushFIFO(&gcodeCmdTxFIFO,homeGcode4);
	
	homeFlag = 0;

	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		//usart2Data.prWaitStatus = pr_wait_data;
		usart2Data.prWaitStatus = pr_wait_cmd;
		usart2TxStart();
	}	
	
	return;
}


void relacalSave(void)
{
	unsigned char tmpGcode[FIFO_SIZE];
	unsigned char *p;
	unsigned char *q;

	unsigned char homeGcode_tmp2[20];


	if(homeFlag ==0) return;
#if 0		
	while(checkFIFO(&gcodeCmdTxFIFO) != fifo_empty)
	{
		//防止串口停止发送，进入死循环
		if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
		{
			usart2Data.printer = printer_working;
			popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
			usart2Data.prWaitStatus = pr_wait_cmd;
			usart2TxStart();
		}		
		
		#if debug_flg == 1
			T_function(150,1);
		#endif
	}
#endif
	
	p=tmpGcode;			//设置Z,E当前位置
	*p++ = 'G';*p++ = '9';*p++ = '2';*p++ = ' ';
	//20150708改
	//*p++ = 'Z';
	//q = RePrintData.z_coordinate + 2;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = e_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);

	p=tmpGcode;			//X,Y,Z回位，停在打印点上方5mm
	*p++ = 'G';*p++ = '1';*p++ = ' ';
	q = x_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = y_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = z_pauseBak;	while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = ' ';
	q = gCfgItems.F_speed;while(*q != '\n' && *q != '\r')		*p++ = *q++;	*p++ = '\n';
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);
		


	p=tmpGcode;			//Z轴归位		
	*p++ = 'G';*p++ = '9';*p++ = '1';*p++ = '\n';
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);
	//p=tmpGcode;			//Z轴归位
	//*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'Z';*p++ = '-';*p++ = '5';*p++ = '\n';
	memset(tmpGcode, 0, sizeof(tmpGcode));
	sprintf(tmpGcode,"G1 Z-%d\n",gCfgItems.Pause_ZADD);
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);

	p=tmpGcode;			//出丝  "G1 E1\n";
	*p++ = 'G';*p++ = '1';*p++ = ' ';*p++ = 'E';*p++ = '1';*p++ = '.';*p++ = '5';*p++ = '\n';
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);
	p=tmpGcode;			//Z轴归位
	*p++ = 'G';*p++ = '9';*p++ = '0';*p++ = '\n';
	pushFIFO(&gcodeCmdTxFIFO,tmpGcode);
		
	homeFlag = 0;
	
	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		//usart2Data.prWaitStatus = pr_wait_data;
		usart2Data.prWaitStatus = pr_wait_cmd;
		usart2TxStart();
	}
	
	RePrintData.saveFlag = SAVE_DIS;
	
	return;
}



void printerStop()
{
	//unsigned char stopGcode0[12]="N-1 M110*15\n";
	unsigned char stopGcode1[5]="M116\n";
	unsigned char stopGcode4[4]="G91\n";
	unsigned char stopGcode5[6]="G1 Z5\n";
	//unsigned char stopGcode5[6]="G0 Z5\n";
	unsigned char stopGcode6[4]="G90\n";	
	unsigned char stopGcode7[10]="G28 X0 Y0\n";
	unsigned char stopGcode9[5]="M107\n";	
	unsigned char stopGcode2[8]="M104 S0\n";
	unsigned char stopGcode3[8]="M140 S0\n";
	unsigned char stopGcode8[4]="M84\n";	
	unsigned char stopGcode10[12]="N-1 M110*15\n";
	//20150911
	unsigned char stopGcode11[10]="G92 X0 Y0\n";

	unsigned char stopGcode12[11]="M104 T0 S0\n";
	unsigned char stopGcode13[11]="M104 T1 S0\n";
	
	unsigned char stopGcode14[5]="M108\n";
	/*
	while(checkFIFO(&gcodeTxFIFO) != fifo_empty)
		popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);

	
	while(checkFIFO(&gcodeCmdTxFIFO) != fifo_empty)
		popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]);
	*/
	initFIFO(&gcodeTxFIFO);
	initFIFO(&gcodeCmdTxFIFO);
	
	pushFIFO(&gcodeCmdTxFIFO,stopGcode14);
	
	if(firmwareType != repetier)
		pushFIFO(&gcodeCmdTxFIFO,stopGcode1);
	

	if(gCfgItems.sprayerNum == 2)
	{
		pushFIFO(&gcodeCmdTxFIFO,stopGcode12);
		pushFIFO(&gcodeCmdTxFIFO,stopGcode13);		
	}
	else
	{
		pushFIFO(&gcodeCmdTxFIFO,stopGcode2);
	}
	pushFIFO(&gcodeCmdTxFIFO,stopGcode3);
	
	pushFIFO(&gcodeCmdTxFIFO,stopGcode4);
	pushFIFO(&gcodeCmdTxFIFO,stopGcode5);
	pushFIFO(&gcodeCmdTxFIFO,stopGcode6);
	pushFIFO(&gcodeCmdTxFIFO,stopGcode7);
	//20150911
	if(firmwareType == repetier)
	{
		pushFIFO(&gcodeCmdTxFIFO,stopGcode11);
	}
	
	pushFIFO(&gcodeCmdTxFIFO,stopGcode8);
	pushFIFO(&gcodeCmdTxFIFO,stopGcode9);
	
	pushFIFO(&gcodeCmdTxFIFO,stopGcode10);

	
	
}

/*
unsigned char homeXY()
{
	unsigned char i;
	unsigned char homeGcode0[5]="M116\n";
	unsigned char homeGcode1[4]="G91\n";
	unsigned char homeGcode2[6]="G1 Z5\n";
	unsigned char homeGcode3[4]="G90\n";	
	unsigned char homeGcode4[10]="G28 X0 Y0\n";
	
	
	//return;
	
	if(homeFlag == 1)	return 0;
	if(heatFlag == 1) return 0;
	i=0;
	while(1)
	{
		if(gcodeTxFIFO.count >5) 	//gcodeTxFIFO.count >0
		{
			tftDelay(50);
			i++;
			if(i>20) 
			{
				heatFlag = 1;
				return 0;
			}
		}
		else
			break;
	}
	
	//tftDelay(1000);
	
	pushFIFO(&gcodeTxFIFO,homeGcode0);
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode1);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode2);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode3);	
//	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	pushFIFO(&gcodeTxFIFO,homeGcode4);	

	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		usart2Data.prWaitStatus = pr_wait_data;
		usart2TxStart();
	}
	
	homeFlag = 1;
	return 1;
}

void relocalZ(void)
{
	unsigned char tmpBuf[FIFO_SIZE];
	unsigned char i;

	unsigned char *p;
	unsigned char flag;
	
//	return;
	if(homeFlag ==0) return;
	
	while(checkFIFO(&gcodeTxFIFO) != fifo_empty);

	i=0;
	p=usart2Data.usart2Txbuf;
	flag = 0;
	
	while(*p++ != ' ')
		if(*p == '\n')	{flag = 0;break;}
			
	if(*p == 'G' && *(p+1) == '1')
	{	
		flag = 1;
		while(*p != 'E')
		{
			tmpBuf[i++] = *p++;
			if(*p == '\n')	{flag = 0;break;}
		}
		tmpBuf[i++]= '\n';
	}
	if(*p == 'G' && *(p+1) == '0')
	{
		flag = 1;
		while(*p != '*')
			tmpBuf[i++] = *p++;
		tmpBuf[i++]= '\n';
	}
	if(flag) pushFIFO(&gcodeTxFIFO,&tmpBuf[0]);
	
	
	if(flag == 0)
	{
		i=0;
		p=usart2Data.usart2Txbak;
		flag = 0;
		while(*p++ != ' ')
			if(*p == '\n')	{flag = 0;break;}
			
		if(*p == 'G' && *(p+1) == '1')
		{	
			flag = 1;
			while(*p != 'E')
			{
				tmpBuf[i++] = *p++;
				if(*p == '\n')	{flag = 0;break;}
			}
			tmpBuf[i++]= '\n';
		}
		if(*p == 'G' && *(p+1) == '0')
		{
			flag = 1;
			while(*p != '*')
				tmpBuf[i++] = *p++;
			tmpBuf[i++]= '\n';
		}
		if(flag) pushFIFO(&gcodeTxFIFO,&tmpBuf[0]);
	}
	
	
	tmpBuf[0] = 'G';tmpBuf[1] = '9';tmpBuf[2] = '1';tmpBuf[3] = '\n';
	pushFIFO(&gcodeTxFIFO,&tmpBuf[0]);	
		
	tmpBuf[0] = 'G';tmpBuf[1] = '1';tmpBuf[2] = ' ';tmpBuf[3] = 'Z';tmpBuf[4] = '-';tmpBuf[5] = '5';tmpBuf[6] = '\n';
	pushFIFO(&gcodeTxFIFO,&tmpBuf[0]);	
	
	tmpBuf[0] = 'G';tmpBuf[1] = '9';tmpBuf[2] = '0';tmpBuf[3] = '\n';
	pushFIFO(&gcodeTxFIFO,&tmpBuf[0]);
	
	homeFlag = 0;

	if(usart2Data.printer	== printer_waiting && usart2Data.prWaitStatus == pr_wait_idle)
	{
		usart2Data.printer = printer_working;
		popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);	//发送数据
		usart2Data.prWaitStatus = pr_wait_data;
		usart2TxStart();
	}	
	
	return;
}
*/

void tftDelay(__IO u16 n)		//delay nms
{
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	tftDelayCnt = n/TICK_CYCLE;
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
		
	while(tftDelayCnt != 0)
	{
		#if debug_flg == 1
			T_function(200,1);
		#endif
	}

}


static uint8_t beeper_cnt;
static uint8_t check_beeper_cnt;
void mksBeeperAlarm(void)
{
		if((gCfgItems.filament_det1_level_flg==1)||(gCfgItems.filament_det2_level_flg==1))
		{
			//由于高电平触发时，
			//比较难通过管脚电平来判断
			//信号脚的电平使其立即停止鸣响，
			//所以默认每次断料鸣响5次。
			beeper_cnt = 10;
		}
		else
		{
			if((MKS_PWRDN == 1) && (MKS_MTRDN == 1))
			{
				check_beeper_cnt++;
			}
			if(check_beeper_cnt >=5)
			{
					mksBpAlrmEn = 0;
					BeeperFreq = 0;
					BeeperCnt = 0;	
					SPEAKER = 0;
					check_beeper_cnt = 0;
			}
			beeper_cnt = 20;
		}

		if(mksBpAlrmEn)
		{
			BeeperFreq++;
			
			
			if(BeeperFreq%3000 == 0)
			{
				BeeperCnt++;
				SPEAKER = BeeperCnt%2;
				//HAL_Delay(3000);
			}
		
			if(BeeperCnt > beeper_cnt)	
			{	
				SPEAKER = 0;
				mksBpAlrmEn=0;
				BeeperCnt=0;
				BeeperFreq = 0;
			}
		}
}
#if 0
void mksBeeperAlarm(void)
{
	if(gCfgItems.pwrdn_mtrdn_level_flg == 1)
	{
		if((MKS_PWRDN == 0 || MKS_MTRDN == 0))
		{
			if(mksBpAlrmEn)
			{
				BeeperFreq++;
				
				
				if(BeeperFreq%20000 == 0)
				{
					BeeperCnt++;
					SPEAKER = BeeperCnt%2;
				}
			
				if(BeeperCnt > 20)	
				{	
					SPEAKER = 0;
					mksBpAlrmEn=0;
					BeeperCnt=0;
					BeeperFreq = 0;
				}
			}

		}
		else
		{
			SPEAKER = 0;
			mksBpAlrmEn=0;
			BeeperCnt=0;
			BeeperFreq = 0;
		}
	}
	else
	{
		//断电PB0
		if(MKS_PWRDN == 0)
		{
			if(mksBpAlrmEn)
			{
				BeeperFreq++;
				
				if(BeeperFreq%20000 == 0)
				{
					BeeperCnt++;
					SPEAKER = BeeperCnt%2;
				}
			
				if(BeeperCnt > 20)	
				{	
					SPEAKER = 0;
					mksBpAlrmEn=0;
					BeeperCnt=0;
					BeeperFreq = 0;
				}
			}

		}

		//断料PB1
		if(MKS_MTRDN == 1)
		{
			if(mksBpAlrmEn)
			{
				BeeperFreq++;	
				if(BeeperFreq%20000 == 0)
				{
					BeeperCnt++;
					SPEAKER = BeeperCnt%2;
				}
				if(BeeperCnt > 20)	
				{	
					SPEAKER = 0;
					mksBpAlrmEn=0;
					BeeperCnt=0;
					BeeperFreq = 0;
				}
			}

		}

		if((MKS_PWRDN == 1)&&(MKS_MTRDN == 0))
		{
			SPEAKER = 0;
			mksBpAlrmEn=0;
			BeeperCnt=0;
			BeeperFreq = 0;
		}
			
	}
}

#endif

