/********************   (C) COPYRIGHT 2014 www.makerbase.com.cn   ********************
 * 文件名  ：mks_tft_fifo.h
 * 描述    ：fifo基本操作 init,push,pop,check
 * 作者    : skyblue
**********************************************************************************/

#include <stdio.h>
#include <string.h>
#include "ff.h"
#include "mks_tft_com.h"
#include "stm32f4xx_usart.h"

static uint8_t PushFifo_flg = 0;

void initFIFO(TFT_FIFO *fifo)
{
	fifo->head = fifo->buffer[0];
	fifo->tail = fifo->buffer[0];
	fifo->status = fifo_empty;
	fifo->count = 0;
	memset(fifo->buffer,0,sizeof(fifo->buffer));
}

FIFO_STATUS pushFIFO(TFT_FIFO *fifo,unsigned char *src)
{
	if(fifo->count >= FIFO_NODE)
		return fifo_full;

	PushFifo_flg = 1;
	USART2_CR1 &= 0xff9f;
	fifo->p = fifo->tail;
	while(*src != '\n')
	{
		*(fifo->p)++ = *src++;
		if(fifo->p >= (fifo->tail + FIFO_SIZE))
		{
			USART2_CR1 |= 0x0060;
			return fifo_err;
		}
	}
	*(fifo->p)++ = '\n';

	fifo->count = (fifo->count + 1)%(FIFO_NODE+1) ;

	fifo->tail = (fifo->tail == fifo->buffer[FIFO_NODE-1])?  fifo->buffer[0]:fifo->tail + FIFO_SIZE;

	PushFifo_flg = 0;
	USART2_CR1 |= 0x0060;
	return fifo_ok;

	/*while (*src != '\n')    
    	{    
        	
		USART_SendData(USART3,*src);
        	src++;    
   	}   

	USART_SendData(USART3,0xee);*/
}


FIFO_STATUS popFIFO(TFT_FIFO *fifo,unsigned char *dst)
{
	if(fifo->count == 0)
		return fifo_empty;
	if(PushFifo_flg != 1)
	{
		fifo->p = fifo->head;
		while(*(fifo->p) != '\n')
		{
			*dst++ = *(fifo->p)++;
			if(fifo->p >= (fifo->head + FIFO_SIZE))
			{
				fifo->count--;
				fifo->head = (fifo->head == fifo->buffer[FIFO_NODE-1])? fifo->buffer[0]:fifo->head +FIFO_SIZE;
				return fifo_err;
			}
		}
		*dst++ = '\n';
		fifo->count--;
		fifo->head = (fifo->head == fifo->buffer[FIFO_NODE-1])? fifo->buffer[0]:fifo->head +FIFO_SIZE;

		return fifo_ok;
	}
}


FIFO_STATUS checkFIFO(TFT_FIFO *fifo)
{
	if(fifo->count == 0)
		return fifo_empty;
	else if(fifo->count == FIFO_NODE)
		return fifo_full;
	else
		return fifo_ok;
}
