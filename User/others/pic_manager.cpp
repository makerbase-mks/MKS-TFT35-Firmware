#include "type_define.h"
#include "string.h"
#include "pic_manager.h"
#include "gui.h"
#include "spi_flash.h"
#include "draw_ui.h"
//#define Bank1_NOR2_ADDR       ((uint32_t)0x64000000)
//extern void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

extern uint8_t DMA_ERRO_FLAG;
//定义图片结构体数组
//PIC_MSG PIC[PIC_MAX_CN];

#if 0
GUI_BITMAP bmp_struct = {
  78,//80, /* XSize */
  104,//50, /* YSize */
  160, /* BytesPerLine */
  16, /* BitsPerPixel */
  NULL,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMPM565
};
#endif

/***************************************************************************
 函数名：PicMsg_Init()
输入参数：无
输出参数：无
功能描述：实现读取存储在flash中的图片信息，进行初始化赋值
****************************************************************************/
/*
void PicMsg_Init(void)
{
	uint8_t i,j;
	uint32_t tmp_cnt = 0;
	uint8_t Pic_cnt1;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;
	
	W25QXX_Read(&Pic_cnt1,PIC_COUNTER_ADDR,1);
	if(Pic_cnt1 == 0xff)
	{
		Pic_cnt1 = 0;
	}

	for(i = 0;i < Pic_cnt1;i++)
	{
		//读取图片名称
		j = 0;
		do
		{
			W25QXX_Read(&PIC[i].name[j],PIC_NAME_ADDR + tmp_cnt,1);
			tmp_cnt++;
		}while(PIC[i].name[j++] != '\0');
		//读取图片大小值
		W25QXX_Read(PIC[i].size.bytes,PIC_SIZE_ADDR+i*4,4);
	}
	
}
*/

void Pic_Read(uint8_t *Pname,uint8_t *P_Rbuff)
{
	uint8_t i, j;
	uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;
  //void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

	SPI_FLASH_BufferRead(&Pic_cnt,PIC_COUNTER_ADDR,1);
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}
	
	for(i=0;i<Pic_cnt;i++)
	{
		//读取图片名称
		j = 0;
		do
		{
			SPI_FLASH_BufferRead(&PIC.name[j],PIC_NAME_ADDR + tmp_cnt,1);
			tmp_cnt++;
		}while(PIC.name[j++] != '\0');
		//读取图片大小值
		SPI_FLASH_BufferRead(PIC.size.bytes,PIC_SIZE_ADDR+i*4,4);
		
		if((strcmp((char*)Pname,(char*)PIC.name))==0)
		{
			SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
			if(DMA_ERRO_FLAG)
			{
				DMA_ERRO_FLAG = 0;
				SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC.size.dwords);
			}
			break;
		}
	}
}

uint32_t logo_addroffset = 0;
void Pic_Logo_Read(uint8_t *LogoName,uint8_t *Logo_Rbuff,uint32_t LogoReadsize)
{
	SPI_FLASH_BufferRead(Logo_Rbuff,PIC_LOGO_ADDR+logo_addroffset,LogoReadsize);
	logo_addroffset += LogoReadsize;
	if(logo_addroffset >= LOGO_MAX_SIZE)
	{
		logo_addroffset = 0;
	}

}

uint32_t default_view_addroffset = 0;
void default_view_Read(uint8_t *default_view_Rbuff,uint32_t default_view_Readsize)
{
	SPI_FLASH_BufferRead(default_view_Rbuff,DEFAULT_VIEW_ADDR+default_view_addroffset,default_view_Readsize);
	default_view_addroffset += default_view_Readsize;
	if(default_view_addroffset >= DEFAULT_VIEW_MAX_SIZE)
	{
		default_view_addroffset = 0;
	}

}

uint32_t flash_view_addroffset = 0;
void flash_view_Read(uint8_t *flash_view_Rbuff,uint32_t flash_view_Readsize)
{
	SPI_FLASH_BufferRead(flash_view_Rbuff,BAK_VIEW_ADDR+flash_view_addroffset,flash_view_Readsize);
	flash_view_addroffset += flash_view_Readsize;
	if(flash_view_addroffset >= FLASH_VIEW_MAX_SIZE)
	{
		flash_view_addroffset = 0;
	}

}

#if 0
extern unsigned char bmp_public_buf[1280];

void bindBmpFileData(const uint8_t **pBuf, uint8_t *pName)
{
	uint8_t i, j;
	uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC1;
	
	if(pName == 0)
		return;

	W25QXX_Read(&Pic_cnt,PIC_COUNTER_ADDR,1);
	//tmp_16bit_addr = (uint16_t *)(Bank1_NOR2_ADDR + PIC_COUNTER_ADDR);
	//Pic_cnt = *tmp_16bit_addr;
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}
	
	
	for(i=0;i<Pic_cnt;i++)
    {
      //读取图片名称
      j = 0;
      do
      {
          W25QXX_Read(&PIC1.name[j],PIC_NAME_ADDR + tmp_cnt,1);
          tmp_cnt++;
      }while(PIC1.name[j++] != '\0');
      //读取图片大小值
      W25QXX_Read(PIC1.size.bytes,PIC_SIZE_ADDR+i*4,4);
      
      if((strcmp((char*)pName,(char*)PIC1.name))==0)
      {
          W25QXX_Read((uint8_t *)*pBuf,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC1.size.dwords);
        //W25QXX_Read((uint8_t *)bmp_public_buf,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,1280);
          break;
      }
  }
  /*
	{
		if((strcmp((char*)pName,(char*)PIC[i].name))==0)
		{
			W25QXX_Read((uint8_t *)*pBuf,PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE,PIC[i].size.dwords);
			// *pBuf = (const uint8_t *)(Bank1_NOR2_ADDR + PIC_DATA_ADDR+i*PER_PIC_MAX_SPACE);
			break;
		}
	}
  */
}
#endif

