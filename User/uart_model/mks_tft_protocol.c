
#include "mks_tft_com.h"
//#include "draw_ui.h"
#include "mks_cfg.h"

unsigned char okIndex;

unsigned char cmpLine(unsigned char cur,unsigned char res);
void reCheck();
void errLineProcess();
void setCurLine();
void setCurLine_repetier();


unsigned char resendProcess()	
{
	unsigned char i;
	unsigned char *p;
							/*--------------Resend------------------*/
		switch(usart2Data.resendFlag)
		{
			case resend_idle:
				if(usart2Data.usart2Rxbuf[0] =='E' &&  usart2Data.usart2Rxbuf[1] =='r' &&  usart2Data.usart2Rxbuf[2] =='r' &&  usart2Data.usart2Rxbuf[3] =='o'&&  usart2Data.usart2Rxbuf[3] =='r')
					return 1;
			
				
				if((usart2Data.usart2Rxbuf[0] =='r' &&  usart2Data.usart2Rxbuf[1] =='s')||(usart2Data.usart2Rxbuf[0] =='R' &&  usart2Data.usart2Rxbuf[1] =='e'&&  usart2Data.usart2Rxbuf[2] =='s'&&  usart2Data.usart2Rxbuf[3] =='e'&&  usart2Data.usart2Rxbuf[4] =='n'&&  usart2Data.usart2Rxbuf[5] =='d'))							
				{
					usart2Data.resendCnt++;
					usart2Data.resendFlag = resend_ready;
					i=0;
					while(usart2Data.usart2Rxbuf[i]!='\n' && usart2Data.usart2Rxbuf[i]!='\r') //??? usart2Data.usart2Rxbuf[i-1]
						i++;
					usart2Data.resendLine = usart2Data.usart2Rxbuf[i-1];
					i=0;
					while(usart2Data.usart2Txbuf[i++] != 32);			//???usart2Data.usart2Txbuf[i-2]
					usart2Data.curLine = usart2Data.usart2Txbuf[i-2];
					
					if(usart2Data.usart2Rxbuf[0] =='r' &&  usart2Data.usart2Rxbuf[1] =='s')		//smoothie
					{
						goto smoothie_lab1;
					}
					return 1;
				}
				return 0;
				break;
			case resend_ready:		//?? ok T:19.5 /0.0 B:19.4 /0.0 @:0 B@:0
				if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k' && (usart2Data.usart2Rxbuf[2]=='\n' ||usart2Data.usart2Rxbuf[2]=='\r'))
				{
smoothie_lab1:					
					if(usart2Data.resendCnt > 5)	
					{
						#if 1
						if(gCfgItems.fileSysType == 1)
						{
							//Restart_data_init();
							//使能标志位
							gCfgItems.restart_data_init = 1;
						}
						else
						#endif
						{
							usart2Data.resendCnt = 0;
							//usart2Data.resendLine =2;usart2Data.curLine=3;
							usart2Data.resendLine =31;usart2Data.curLine=21;
							setCurLine();

							//HC-chen 7.25     5次resend 重新定行，之后发送下一行
							usart2Data.timerCnt=0;
							usart2Data.txP = &usart2Data.usart2Txbak[0];
							usart2Data.txBase = usart2Data.txP;
							USART2_DR = *(usart2Data.txP++);
						}
						
						return 1;
						break;
			 		}
					
					switch(cmpLine(usart2Data.curLine,usart2Data.resendLine))
					{
						case 0:	//pre
							usart2Data.timerCnt=0;
							usart2Data.txP = &usart2Data.usart2Txbak[0];
							usart2Data.txBase = usart2Data.txP;
							usart2Data.resendFlag = resend_end;
							USART2_DR = *(usart2Data.txP++);
							break;
						case 1:	//cur
							reCheck();
							usart2TxStart();
							usart2Data.resendFlag = resend_idle;
							break;
						case 2:	//next
							usart2Data.txP = &usart2Data.usart2Txbuf[0];
							usart2Data.txBase = usart2Data.txP;
							p = &usart2Data.usart2Txbak[0];
							while(*(usart2Data.txP) != '\n')
								*p++ = *(usart2Data.txP++);
							*p++ = '\n';
							popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);
							usart2TxStart();
							usart2Data.resendFlag = resend_idle;
							break;
						//HC-chen 7.25
						case 3:   //setCurLine->next
							usart2Data.txP = &usart2Data.usart2Txbuf[0];
							usart2Data.txBase = usart2Data.txP;
							p = &usart2Data.usart2Txbak[0];
							while(*(usart2Data.txP) != '\n')
								*p++ = *(usart2Data.txP++);
							*p++ = '\n';
							popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);
							usart2TxStart();
							usart2Data.resendFlag = resend_idle;
							break;
						default : break;
					}//switch(cmpLine(usart2Data.curLine,usart2Data.resendLine))
				}
				return 1;
				break;
			case resend_end:	
					if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k' && (usart2Data.usart2Rxbuf[2]=='\n' ||usart2Data.usart2Rxbuf[2]=='\r'))					
					{
						usart2TxStart();
						usart2Data.resendFlag = resend_idle;
					}
					return 1;
				break;
			default :break;
		}//switch(usart2Data.resendFlag)
		
	return 0;
}


unsigned char resendProcess_repetier()
{
	unsigned char i;
	unsigned char *p;
							/*--------------Resend------------------*/
			//20151104
			//	if(usart2Data.resendFlag == resend_ready)	
			//		return 0;
				
			//Error:
				if(usart2Data.usart2Rxbuf[0] =='E' &&  usart2Data.usart2Rxbuf[1] =='r' &&  usart2Data.usart2Rxbuf[2] =='r' &&  usart2Data.usart2Rxbuf[3] =='o'&&  usart2Data.usart2Rxbuf[3] =='r')
					return 1;
			
				//Resend:3 or skip
				if((usart2Data.usart2Rxbuf[0] =='R' &&  usart2Data.usart2Rxbuf[1] =='e'&&  usart2Data.usart2Rxbuf[2] =='s'&&  usart2Data.usart2Rxbuf[3] =='e'&&  usart2Data.usart2Rxbuf[4] =='n'&&  usart2Data.usart2Rxbuf[5] =='d') || \
					(usart2Data.usart2Rxbuf[0] =='s' &&  usart2Data.usart2Rxbuf[1] =='k'&&  usart2Data.usart2Rxbuf[2] =='i'&&  usart2Data.usart2Rxbuf[3] =='p'))			
				{
					if(usart2Data.usart2Rxbuf[0] =='R')
					{
						i=0;
						while(usart2Data.usart2Rxbuf[i]!='\n' && usart2Data.usart2Rxbuf[i]!='\r') //??? usart2Data.usart2Rxbuf[i-1]
							i++;
						usart2Data.resendLine = usart2Data.usart2Rxbuf[i-1];
						i=0;
						while(usart2Data.usart2Txbuf[i++] != 32);			//???usart2Data.usart2Txbuf[i-2]
						usart2Data.curLine = usart2Data.usart2Txbuf[i-2];
						
					}
					else
					{
						usart2Data.curLine = 2;
						usart2Data.resendLine = 3;
					}

					switch(cmpLine(usart2Data.curLine,usart2Data.resendLine))
					{
						case 0:	//pre

							break;
						case 1:	//cur
							reCheck();
							usart2TxStart();
							usart2Data.resendFlag = resend_ready;
							break;
						case 2:	//next
							usart2Data.txP = &usart2Data.usart2Txbuf[0];
							usart2Data.txBase = usart2Data.txP;
							p = &usart2Data.usart2Txbak[0];
							while(*(usart2Data.txP) != '\n')
								*p++ = *(usart2Data.txP++);
							*p++ = '\n';
							popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]);
							usart2TxStart();
							usart2Data.resendFlag = resend_ready;
							break;
						default : break;
					}//switch(cmpLine(usart2Data.curLine,usart2Data.resendLine))
					return 1;
				}
				
		
	return 0;	
}

void prTxNext()
{
		unsigned char *p;
		if(usart2Data.usart2Txbuf[0] == 'N' || (usart2Data.usart2Txbuf[0] == '\n' && usart2Data.usart2Txbuf[1] == 'N'))	//保存上一次发送的数据 包括"\nNxxxxx"的数据
		{
			usart2Data.txP = &usart2Data.usart2Txbuf[0];
			usart2Data.txBase = usart2Data.txP;
			p = &usart2Data.usart2Txbak[0];
			while(*(usart2Data.txP) != '\n')
			*p++ = *(usart2Data.txP++);
			*p++ = '\n';

			//20151008
			//记录已发送的行数。
			if(usart2Data.usart2Txbuf[0] == '\n')
			{
				if(usart2Data.usart2Txbuf[2] != '-')
				{
					RePrintData.record_line++;
				}				
			}
			else
			{
				if(usart2Data.usart2Txbuf[1] != '-')
				{
					RePrintData.record_line++;
				}
			}
		}
			
		//发送命令
		if(popFIFO(&gcodeCmdTxFIFO,&usart2Data.usart2Txbuf[0]) == fifo_ok)			//usart2Data.prWaitStatus != pr_wait_data 可以覆盖usart2Data.usart2Txbuf
		{
			usart2Data.prWaitStatus = pr_wait_cmd;
			usart2TxStart();
		}
		else 
		{
			if((checkFIFO(&gcodeTxFIFO) != fifo_empty)&&(printerStaus != pr_pause))
			{
				if(popFIFO(&gcodeTxFIFO,&usart2Data.usart2Txbuf[0]) == fifo_err)	//fifo_err
					{
						errLineProcess();
					}	
					usart2Data.prWaitStatus = pr_wait_data;
					usart2TxStart();
			}
			else
				usart2Data.printer = printer_waiting;
				
		}
			
	
}



void usart2TxStart()
{
		usart2Data.timerCnt=0;
		usart2Data.txP = &usart2Data.usart2Txbuf[0];
		usart2Data.txBase = usart2Data.txP;
		USART2_DR = *(usart2Data.txP++);
		
}
void printerInit()
{
		usart2Data.usart2Txbuf[0]='N';usart2Data.usart2Txbuf[1]='-';usart2Data.usart2Txbuf[2]='1';usart2Data.usart2Txbuf[3]=' ';
		usart2Data.usart2Txbuf[4]='M';usart2Data.usart2Txbuf[5]='1';usart2Data.usart2Txbuf[6]='1';usart2Data.usart2Txbuf[7]='0';
		usart2Data.usart2Txbuf[8]='*';usart2Data.usart2Txbuf[9]='1';usart2Data.usart2Txbuf[10]='5';usart2Data.usart2Txbuf[11]='\n';		
		usart2Data.prWaitStatus = pr_wait_data;
		usart2Data.resendFlag = resend_idle;
		usart2Data.resendCnt = 0;
		usart2TxStart();
}
void pushInitGcode()
{
	unsigned char initGcodeBuf[15]="N-1 M110*15\n";
	
	while(checkFIFO(&gcodeTxFIFO) == fifo_full);
	
	pushFIFO(&gcodeTxFIFO,&initGcodeBuf[0]);
	
}

//0 - pre; 1-cur; 2-next
unsigned char cmpLine(unsigned char cur,unsigned char res)
{
		if(res == 21 && cur == 31)	
			return 3;
							
		if(res == '9' && cur == '0')	//发送上一行
			return 0;
								
		if((res == '0' && cur == '9') || (res >  cur))	//发送下一行
			return 2;
		
		if(res < cur)	//发送上一行
			return 0;
		
		if(res == cur)
			return 1;
		
		return 1;
}

void reCheck()
{
	unsigned char *p;
	unsigned char checkSum = 0;
	
				p = &usart2Data.usart2Txbuf[0];

				while(*p != '*')
					checkSum ^= *p++;
				p++;
				
				if(checkSum/100 != 0)				
				{
					*p++ = checkSum/100 + 48;
					*p++ = (checkSum/10)%10 + 48;
					*p++ = checkSum%10 + 48;
				}
				else if(checkSum/10 != 0)
				{
					*p++ = checkSum/10 + 48;
					*p++ = checkSum%10 + 48;
				}
				else
					*p++ = checkSum%10 + 48;
				
				*p++ = '\n';								//加'\n'
}


void errLineProcess()
{
	unsigned char *p;
	p = &usart2Data.usart2Txbuf[0];

	while(*p != ' ')
	{
		p++;
		if(p > &usart2Data.usart2Txbuf[0] + FIFO_SIZE -2)
			break;
	}
	p++;
	
	*p++ = 'M';*p++ = '1';*p++ = '1';*p++ = '6';*p++ = '*';		//waiting
	
	reCheck();
}

//HC-chen 2018.7.24
extern CFG_ITMES gCfgItems;
void setCurLine()
{
	unsigned char *p;
	unsigned char *p_bak;
	unsigned char *q;
	unsigned long setLineNum = 0;
	unsigned char lineCntBuf[20];
	unsigned char checkSum=0;

	p = &usart2Data.usart2Txbuf[1];
	q = &lineCntBuf[0];
	while(*p != ' ')
		*q++ = *p++;
	*q = '\0';

	setLineNum = atoi(&lineCntBuf[0]);
	//setLineNum--;


	p = &lineCntBuf[0];
	*p++ = setLineNum%10 + 48;
	setLineNum /= 10;
	while(setLineNum!=0)
		{
			*p++=setLineNum%10 + 48;
			setLineNum /= 10;
		}
	//M110N
	//sean 12.25
	#if 0
	usart2Data.usart2Txbak[0] = 'M';usart2Data.usart2Txbak[1] = '1';usart2Data.usart2Txbak[2] = '1';usart2Data.usart2Txbak[3] = '0';usart2Data.usart2Txbak[4] = ' ';usart2Data.usart2Txbak[5] = 'N';
	
	q = &usart2Data.usart2Txbak[6];
	while(p>lineCntBuf)
		*q++ = *--p;
		if(gCfgItems.add_checkSum != 0)
			*q++ = '*';	
		else
			*q++ = '\n';
	#else
	usart2Data.usart2Txbak[0] = 'N';
	
	q = &usart2Data.usart2Txbak[1];
	while(p>lineCntBuf)
		*q++ = *--p;
			*q++ = ' ';
			*q++ = 'M';
			*q++ = '1';
			*q++ = '1';
			*q++ = '0';
			*q++ = '*';
	#endif

	//usart2Data.usart2Txbak[0] = 'N';//usart2Data.usart2Txbak[1] = '1';usart2Data.usart2Txbak[2] = '1';usart2Data.usart2Txbak[3] = '0';usart2Data.usart2Txbak[4] = ' ';usart2Data.usart2Txbak[5] = 'N';
	//HC-chen 2017.7.24
	
	//p_bak = p;
	
	//q = &usart2Data.usart2Txbak[1];
	/*while(p>lineCntBuf)
		*q++ = *--p;

		*q++ = ' ';	
		*q++ = 'M';
		*q++ = '1';
		*q++ = '1';
		*q++ = '0';
		*q++ = ' ';
		*q++ = 'N';
	while(p_bak>lineCntBuf)
		*q++ = *--p_bak;	
		*q++ = '*';*/
	//sean 12.25
	//if(gCfgItems.add_checkSum != 0)
	{
		p = &usart2Data.usart2Txbak[0];
		while(*p != '*')
			checkSum ^= *p++;
		p++;

		if(checkSum/100 != 0)				
		{
			*p++ = checkSum/100 + 48;
			*p++ = (checkSum/10)%10 + 48;
			*p++ = checkSum%10 + 48;
		}
		else if(checkSum/10 != 0)
		{
			*p++ = checkSum/10 + 48;
			*p++ = checkSum%10 + 48;
		}
		else
			*p++ = checkSum%10 + 48;
					
		*p++ = '\n';								
	
	}
}


/*
												if(usart2Data.usart2Rxbuf[0] =='o' &&  usart2Data.usart2Rxbuf[1] =='k')	
												{
													//收到ok 或者ok 123
													//if((usart2Data.usart2Rxbuf[2] =='\n' ||  usart2Data.usart2Rxbuf[2] == '\r') ||(usart2Data.usart2Rxbuf[2] == ' ' &&  usart2Data.usart2Rxbuf[3] >= '0' &&  usart2Data.usart2Rxbuf[3] <= '9'))
													if(firmwareType != repetier)
													{
														if(usart2Data.usart2Rxbuf[2] =='\n' ||  usart2Data.usart2Rxbuf[2] == '\r')
														{
														usart2Data.resendCnt = 0;
														usart2Data.prWaitStatus = pr_wait_idle;
														prTxNext();
														}
														else //ok : T xxx
															pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
													}
													else	//repetier
													{
														if ((usart2Data.usart2Txbuf[1]='-' && (usart2Data.usart2Rxbuf[2] =='\n' ||  usart2Data.usart2Rxbuf[2] == '\r')) || ( usart2Data.usart2Txbuf[1]!='-' && usart2Data.usart2Rxbuf[3] >= '0' && usart2Data.usart2Rxbuf[3] <= '9'))
														{
														//usart2Data.resendCnt = 0;
														usart2Data.resendFlag = resend_idle;
														usart2Data.prWaitStatus = pr_wait_idle;
														prTxNext();
														}
														else
															pushFIFO(&gcodeCmdRxFIFO,&usart2Data.usart2Rxbuf[0]);
													}														

*/

unsigned char repetierCmpLine(unsigned char *src,unsigned char *dst)
{
	while(*src != ' ' && *src != '\n')
		{
		if(*src != *dst)
			return 0;
		src++;
		dst++;
		}
	return 1;
}

unsigned char recOkProcess(void )
{
	switch(firmwareType) 
	{
		case marlin:
		case smoothie:
			if(usart2Data.usart2Rxbuf[2] =='\n' ||  usart2Data.usart2Rxbuf[2] == '\r')
				return 1;
			else
				return 0;
			break;
		case repetier:
			if(usart2Data.usart2Txbuf[1]=='-')
			{
				if(usart2Data.usart2Rxbuf[2] =='\n' ||  usart2Data.usart2Rxbuf[2] == '\r')
					return 1;
				else
					return 0;
			}
			else
			{
				if(usart2Data.usart2Rxbuf[3] >= '0' && usart2Data.usart2Rxbuf[3] <= '9')
				{	
					usart2Data.timerCnt = 0; //定时器清零
					if(usart2Data.usart2Txbuf[0] != 'N')
					{
						usart2Data.resendFlag = resend_idle;
						return 1;
					}
					
					if(*(usart2Data.rxP-3) != okIndex && repetierCmpLine(&usart2Data.usart2Txbuf[1],&usart2Data.usart2Rxbuf[3]) == 1)
					{
						usart2Data.resendFlag = resend_idle;
						okIndex = *(usart2Data.rxP-3);
						return 1;
					}
					else
						return 0;
				}
				else
					return 0;
			}
			break;
		default : break;
	}
	return 0;
}

void copySaveCoordinate(unsigned char *src,unsigned char *dst)
{
		while(*src != ' ' && *src !='\n')
			{
			*dst++ = *src++;
			if(*src == 'Y' || *src == 'Z' ||*src == 'E' ||*src == 'A')
				break;
			}
		*dst = '\n';
}



void getSavePosition()         
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
					copySaveCoordinate(p,RePrintData.x_coordinate);
					positionCnt++;
					}
				break;
			case 'Y':
				if(positionCnt == 1) 
					{
					copySaveCoordinate(p,RePrintData.y_coordinate);
					positionCnt++;
					}
				break;
			case 'Z':
				if(positionCnt == 2) 
					{
					copySaveCoordinate(p,RePrintData.z_coordinate);
					positionCnt++;
					}
				break;
			case 'E':
				if(positionCnt == 3)
					{
					copySaveCoordinate(p,RePrintData.e_coordinate);
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
		RePrintData.saveEnable = 0;
		if(usart2Data.usart2Rxbuf[0]=='o' && usart2Data.usart2Rxbuf[1] == 'k')	//smoothie
			{
			usart2Data.prWaitStatus = pr_wait_idle;
			prTxNext();
			}
		}
}
