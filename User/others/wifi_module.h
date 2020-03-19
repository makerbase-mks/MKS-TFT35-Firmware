#ifndef _WIFI_MODULE_H_
#define _WIFI_MODULE_H_


#undef ESP_MODEL

#define UART_RX_BUFFER_SIZE   1024
#define UART_FIFO_BUFFER_SIZE 1024

#define HLK_WIFI		0x01
#define ESP_WIFI		0x02

#define WIFI_DECODE_TYPE	1				//AUTO

#define IP_DHCP_FLAG	1

#define WIFI_AP_NAME		"TP-LINK_MKS"
#define WIFI_KEY_CODE		"makerbase"
//Client模式下的IP配置
#define IP_ADDR 	 	"192.168.3.100"
#define IP_MASK 	 	"255.255.255.0"
#define IP_GATE 	 	"192.168.3.1"
#define IP_DNS 	 	 	"192.168.3.1"

//AP模式下的IP配置
#define AP_IP_DHCP_FLAG	1
#define AP_IP_ADDR		"192.168.3.100"
#define AP_IP_MASK		"255.255.255.0"
#define AP_IP_GATE		"192.168.3.1"
#define AP_IP_DNS		"192.168.3.1"
#define IP_START_IP		"192.168.3.1"
#define IP_END_IP		"192.168.3.255"
//-------tan 20171008 modify begin------
#if 0
#define WIFI_SET()        GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define WIFI_RESET()      GPIO_ResetBits(GPIOA, GPIO_Pin_8);
#define WIFI_IO1_SET()    GPIO_SetBits(GPIOD, GPIO_Pin_8)      
#define WIFI_IO1_RESET()  GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#endif
#define WIFI_SET()        HAL_GPIO_WritePin(GPIOA, GPIO_Pin_8, GPIO_PIN_SET)
#define WIFI_RESET()      HAL_GPIO_WritePin(GPIOA, GPIO_Pin_8, GPIO_PIN_RESET)
#define WIFI_IO1_SET()    HAL_GPIO_WritePin(GPIOC, GPIO_Pin_6, GPIO_PIN_SET)
#define WIFI_IO1_RESET()  HAL_GPIO_WritePin(GPIOC, GPIO_Pin_6, GPIO_PIN_RESET);
//-------tan 20171008 modify endif------

typedef  struct
{
	char ap_name[32];	//wifi网络名称字符串
	char keyCode[64]; //wifi密码字符串
	int   decodeType; //加密类型（1：auto，2：aes）
	int baud;
	int mode;
} WIFI_PARA;

typedef  struct
{
	char state;	//云连接状态：0x12:云连接使能，并连接上，已绑定;0x11:云连接使能，并连接上,未绑定;0x10：云连接使能，但未连接;0x00:云连接禁用
	char hostUrlLen; //云连接地址长度（最大值为96）
	char hostUrl[96];	//云连接地址
	int port;		//云连接端口
	char id[21];
} CLOUD_PARA;

typedef struct
{
	char  dhcp_flag;	//动态获取IP标志位，若为1则不需要静态设置，//为0，则采用静态设置
	char  ip_addr[16];	//静态ip地址数组，如192,168,0,23
	char  mask[16];	//静态子网掩码，如255,255,255,0
	char  gate[16];	//静态网关，如192,168,0,1
	char  dns[16];		//dns
	
	char  dhcpd_flag; //ap模式下，DHCP服务器配置
	char  dhcpd_ip[16];//DHCP服务器IP地址
	char  dhcpd_mask[16];//DHCP服务器掩码
	char  dhcpd_gate[16];//DHCP服务器网关
	char  dhcpd_dns[16];//DHCP服务器DNS地址	
	char  start_ip_addr[16];//起始地址
	char  end_ip_addr[16];//结束地址
} IP_PARA;


typedef enum
{
	WIFI_NOT_CONFIG,
	WIFI_CONFIG_MODE,
	WIFI_CONFIG_DHCP,
	WIFI_CONFIG_AP,
	WIFI_CONFIG_IP_INF,
	WIFI_CONFIG_DNS,
	WIFI_CONFIG_TCP,
	WIFI_CONFIG_SERVER,
	WIFI_CONFIG_REMOTE_PORT,
	WIFI_CONFIG_BAUD,
	WIFI_CONFIG_COMMINT,
	WIFI_CONFIG_OK,
	WIFI_GET_IP_OK,
	WIFI_RECONN,
	WIFI_CONNECTED,
	WIFI_WAIT_TRANS_START,
	WIFI_TRANS_FILE,
	WIFI_CONFIG_DHCPD,
	WIFI_COFIG_DHCPD_IP,
	WIFI_COFIG_DHCPD_DNS,
	WIFI_EXCEPTION,
} WIFI_STATE;

typedef enum
{
	TRANSFER_IDLE,
	TRANSFERING,
	TRANSFER_STORE,
} TRANSFER_STATE;
typedef struct
{
	char buf[20][80];
	int rd_index;
	int wt_index;
} QUEUE;


typedef enum
{
	WIFI_PARA_SET, 	//0x0:设置网络参数
	WIFI_PRINT_INF, 	//0x1:打印机信息
	WIFI_TRANS_INF, 	//0x2:透传信息
	WIFI_EXCEP_INF,	 //0x3:异常信息
	WIFI_CLOUD_CFG,	//0x4:云端配置
	WIFI_CLOUD_UNBIND, //0x5：解绑ID
} WIFI_RET_TYPE;


typedef struct 
{  
  uint32_t uart_read_point;
  uint32_t uart_write_point;
  uint8_t uartTxBuffer[UART_FIFO_BUFFER_SIZE];
} SZ_USART_FIFO;

extern volatile WIFI_STATE wifi_link_state;
extern WIFI_PARA wifiPara;
extern IP_PARA ipPara;
extern CLOUD_PARA cloud_para;

extern uint32_t  getWifiTick();
extern uint32_t  getWifiTickDiff(int32_t lastTick, int32_t  curTick);

void wifi_init();

extern char wifi_loop_time;

extern int cfg_wifi_flag;
extern int cfg_cloud_flag;
extern int send_to_wifi(char *buf, int len);

#endif

