#include "type_define.h"
#include "string.h"
#include "pic_manager.h"
#include "gui.h"
#include "spi_flash.h"
#include "draw_ui.h"
#include "wifi_module.h"

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
#if 1
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
#elif 
uint32_t pic_addr_offset;
uint16_t pic_row;
uint8_t little_image_flag=0;
	uint8_t Pic_cnt;
void Pic_Read(uint8_t *Pname,uint8_t *P_Rbuff,uint8_t part,uint8_t allcnt)
{
	uint8_t i, j;
	//uint8_t Pic_cnt;
	uint32_t tmp_cnt = 0;
	PIC_MSG PIC;
	uint16_t *tmp_16bit_addr;
	uint8_t *tmp_8bit_addr;  
	SPI_FLASH_BufferRead(&Pic_cnt,PIC_COUNTER_ADDR,1);
	if(Pic_cnt == 0xff)
	{
		Pic_cnt = 0;
	}	
    if(part==0)
    {
		for(i=0;i<Pic_cnt;i++)	
//		for(i=0;i<153;i++)	
    	{
    		//锟斤拷取图片锟斤拷锟斤拷
    		j = 0;
    		do
    		{
    			SPI_FLASH_BufferRead(&PIC.name[j],PIC_NAME_ADDR + tmp_cnt,1);
    			tmp_cnt++;
    		}while(PIC.name[j++] != '\0');

    		if((strcmp((char*)Pname,(char*)PIC.name))==0)
    		{
        		//锟斤拷取图片锟斤拷小值
        		SPI_FLASH_BufferRead(PIC.size.bytes,PIC_SIZE_ADDR+i*4,4);
				if(PIC.size.dwords < sizeof(bmp_public_buf))//小图片
				{
					little_image_flag=1;
				}
                pic_addr_offset=PIC.size.dwords>>2;   //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷示 		
    		    pic_row=i;
    		    break;
    		}
          }
    }

    if(little_image_flag == 1)
    {
    	SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+pic_row*PER_PIC_MAX_SPACE,PIC.size.dwords);
	if(DMA_ERRO_FLAG)
	{
		DMA_ERRO_FLAG = 0;
		SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+pic_row*PER_PIC_MAX_SPACE,PIC.size.dwords);
	}
    }
    else
    {
    	SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+pic_row*PER_PIC_MAX_SPACE+part*pic_addr_offset,pic_addr_offset);
    	if(DMA_ERRO_FLAG)
    	{
    		DMA_ERRO_FLAG = 0;
    		SPI_FLASH_BufferRead((uint8_t *)P_Rbuff,PIC_DATA_ADDR+pic_row*PER_PIC_MAX_SPACE+part*pic_addr_offset,pic_addr_offset);
    	}
    }	
	
}

#endif
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

void flash_reWriteInf(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
	uint32_t flash_inf_valid_flg;
//	uint8_t testLen = 0;
	uint8_t autoLevelCmd[201] = {0};
	uint8_t FuncBtn1Cmd[201] = {0};
	uint8_t moreItem1Cmd[201]={0};	
	uint8_t moreItem2Cmd[201]={0};
	uint8_t moreItem3Cmd[201]={0};
	uint8_t moreItem4Cmd[201]={0};
	uint8_t moreItem5Cmd[201]={0};
	uint8_t moreItem6Cmd[201]={0};
	uint8_t moreItem7Cmd[201]={0};	
	uint8_t morefunc1Cmd[201]={0};
	uint8_t morefunc2Cmd[201]={0};
	uint8_t morefunc3Cmd[201]={0};	
	uint8_t morefunc4Cmd[201]={0};
	uint8_t morefunc5Cmd[201]={0};
	uint8_t morefunc6Cmd[201]={0};
	uint8_t morefunc7Cmd[201]={0};
	uint8_t wifi_ap_sta = 0;
	char ap_name[32] = {0};
	char keyCode[64] = {0};
	char ip_addr[16] = {0};
	char mask[16] 	 = {0};
	char gate[16]  	 = {0};
	char dhcp_flag = 0;
	char wifi_type = 0;
 //       testLen=strlen((char const*)pBuffer)+1;
	SPI_FLASH_BufferRead((uint8_t *)ap_name,WIFI_NAME_ADDR,32);
	SPI_FLASH_BufferRead((uint8_t *)keyCode,WIFI_KEYCODE_ADDR,64);
	SPI_FLASH_BufferRead((uint8_t *)ip_addr,WIFI_IP_ADDR,15);
	SPI_FLASH_BufferRead((uint8_t *)mask,WIFI_MASK_ADDR,15);
	SPI_FLASH_BufferRead((uint8_t *)gate,WIFI_GATE_ADDR,15);
	SPI_FLASH_BufferRead((uint8_t*)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
	SPI_FLASH_BufferRead((uint8_t*)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
	SPI_FLASH_BufferRead((uint8_t*)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
	SPI_FLASH_BufferRead((uint8_t*)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,201);
	SPI_FLASH_BufferRead((uint8_t*)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem1Cmd,BUTTON_CMD1_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)&moreItem2Cmd,BUTTON_CMD2_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem3Cmd,BUTTON_CMD3_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem4Cmd,BUTTON_CMD4_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem5Cmd,BUTTON_CMD5_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem6Cmd,BUTTON_CMD6_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)moreItem7Cmd,BUTTON_CMD7_ADDR,201);		
	SPI_FLASH_BufferRead((uint8_t*)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,201);	
	SPI_FLASH_BufferRead((uint8_t*)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,201);	
	
	SPI_FLASH_SectorErase(SD_INF_ADDR);
	
	flash_inf_valid_flg = FLASH_INF_VALID_FLAG;
	SPI_FLASH_BufferWrite((uint8_t*)&flash_inf_valid_flg,FlASH_INF_VALID_ADDR,4);
	
	switch(WriteAddr)
	{
	case WIFI_NAME_ADDR:	
//		SPI_FLASH_BufferWrite((u8 *)pBuffer,WIFI_NAME_ADDR,(strlen((char const*)pBuffer)+1));
//		SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
//		SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
//		SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
//		SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
//		SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
//		SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
//		SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
//		SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
//		SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
//		SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
//		SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

		break;
		case WIFI_KEYCODE_ADDR:	
//			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
//			SPI_FLASH_BufferWrite((u8 *)pBuffer,WIFI_KEYCODE_ADDR,(strlen((char const*)pBuffer)+1));
//			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
//			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
//			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
//			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
//			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
//			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

			break;
			case WIFI_IP_ADDR:
//				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
//				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
//				SPI_FLASH_BufferWrite((u8 *)pBuffer,WIFI_IP_ADDR,(strlen((char const*)pBuffer)+1));
//				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
//				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
//				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
//				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
//				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
//				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
//				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
//				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
//				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

			break;
//		case WIFI_MODE_SEL_ADDR:
//			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
//			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
//			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
//			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
//			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
//			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)pBuffer,WIFI_MODE_SEL_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
//			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
//			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
//			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
//			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

//			break;
		case BUTTON_AUTOLEVELING_ADDR:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)pBuffer)+1));
			//test
 //                       testLen =(uint8_t) strlen((char const*)pBuffer);
//			memset(cmd_code,0,sizeof(cmd_code));
//			SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
//			
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));		
			break;
			case BUTTON_FUNCTION1_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_FUNCTION1_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_CMD1_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD1_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_CMD2_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD2_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_CMD3_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD3_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_CMD4_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD4_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
		case BUTTON_CMD5_ADDR:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD5_ADDR,(strlen((char const*)pBuffer)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

			break;
			case BUTTON_CMD6_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD6_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_CMD7_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_CMD7_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_MOREFUNC1_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_MOREFUNC2_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;

			case BUTTON_MOREFUNC3_ADDR:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)pBuffer)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));		
				break;
			case BUTTON_MOREFUNC4_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)pBuffer)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
			case BUTTON_MOREFUNC5_ADDR:
				SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
				SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
				SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
				SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
				SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
				SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
				SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
				SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)pBuffer)+1));
				SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
				SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

				break;
		case BUTTON_MOREFUNC6_ADDR:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)pBuffer)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	

			break;
		case BUTTON_MOREFUNC7_ADDR:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)pBuffer,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)pBuffer)+1));	

			break;
		default:
			SPI_FLASH_BufferWrite((u8 *)ap_name,WIFI_NAME_ADDR,(strlen((char const*)ap_name)+1));
			SPI_FLASH_BufferWrite((u8 *)keyCode,WIFI_KEYCODE_ADDR,(strlen((char const*)keyCode)+1));
			SPI_FLASH_BufferWrite((u8 *)ip_addr,WIFI_IP_ADDR,(strlen((char const*)ip_addr)+1));
			SPI_FLASH_BufferWrite((u8 *)mask,WIFI_MASK_ADDR,(strlen((char const*)mask)+1));
			SPI_FLASH_BufferWrite((u8 *)gate,WIFI_GATE_ADDR,(strlen((char const*)gate)+1));
			SPI_FLASH_BufferWrite((u8 *)&dhcp_flag,WIFI_DHCP_FLAG_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_ap_sta,WIFI_MODE_SEL_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)&wifi_type,WIFI_MODE_TYPE_ADDR,1);
			SPI_FLASH_BufferWrite((u8 *)autoLevelCmd,BUTTON_AUTOLEVELING_ADDR,(strlen((char const*)autoLevelCmd)+1));
			SPI_FLASH_BufferWrite((u8 *)FuncBtn1Cmd,BUTTON_FUNCTION1_ADDR,(strlen((char const*)FuncBtn1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem1Cmd,BUTTON_CMD1_ADDR,(strlen((char const*)moreItem1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem2Cmd,BUTTON_CMD2_ADDR,(strlen((char const*)moreItem2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem3Cmd,BUTTON_CMD3_ADDR,(strlen((char const*)moreItem3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem4Cmd,BUTTON_CMD4_ADDR,(strlen((char const*)moreItem4Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem5Cmd,BUTTON_CMD5_ADDR,(strlen((char const*)moreItem5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem6Cmd,BUTTON_CMD6_ADDR,(strlen((char const*)moreItem6Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)moreItem7Cmd,BUTTON_CMD7_ADDR,(strlen((char const*)moreItem7Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc1Cmd,BUTTON_MOREFUNC1_ADDR,(strlen((char const*)morefunc1Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc2Cmd,BUTTON_MOREFUNC2_ADDR,(strlen((char const*)morefunc2Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc3Cmd,BUTTON_MOREFUNC3_ADDR,(strlen((char const*)morefunc3Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc4Cmd,BUTTON_MOREFUNC4_ADDR,(strlen((char const*)morefunc4Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc5Cmd,BUTTON_MOREFUNC5_ADDR,(strlen((char const*)morefunc5Cmd)+1));
			SPI_FLASH_BufferWrite((u8 *)morefunc6Cmd,BUTTON_MOREFUNC6_ADDR,(strlen((char const*)morefunc6Cmd)+1));			
			SPI_FLASH_BufferWrite((u8 *)morefunc7Cmd,BUTTON_MOREFUNC7_ADDR,(strlen((char const*)morefunc7Cmd)+1));	
			break;
	}

//				SPI_FLASH_BufferRead((uint8_t*)&test,WIFI_MODE_SEL_ADDR,1);
        		//test
//		memset(cmd_code,0,sizeof(cmd_code));
//		SPI_FLASH_BufferRead((u8 *)cmd_code,BUTTON_AUTOLEVELING_ADDR,201);
}

