#ifndef _SD_USR_H_
#define _SD_USR_H_

#if 0
//flash信息有效的标志
#define FLASH_INF_VALID_FLAG			0xaa558761
//SD卡在flash中存储块的首地址
//#define	SD_INF_ADDR		0X1AB000//0x1f9000
#define	SD_INF_ADDR		0X000000//0x1f9000
//SD卡在flash中信息有效标志存储地址
#define FlASH_INF_VALID_ADDR	SD_INF_ADDR
//更多菜单flash地址
#define BUTTON_CMD1_ADDR	FlASH_INF_VALID_ADDR+4
#define BUTTON_CMD2_ADDR	BUTTON_CMD1_ADDR+201
#define BUTTON_CMD3_ADDR	BUTTON_CMD2_ADDR+201
#define BUTTON_CMD4_ADDR	BUTTON_CMD3_ADDR+201
#define BUTTON_CMD5_ADDR	BUTTON_CMD4_ADDR+201
#define BUTTON_CMD6_ADDR	BUTTON_CMD5_ADDR+201
#define BUTTON_CMD7_ADDR	BUTTON_CMD6_ADDR+201
//wifi的flash地址
#define WIFI_NAME_ADDR		BUTTON_CMD7_ADDR+201
#define WIFI_KEYCODE_ADDR	WIFI_NAME_ADDR+201
#define WIFI_IP_ADDR		WIFI_KEYCODE_ADDR+201
#define WIFI_MASK_ADDR		WIFI_IP_ADDR+16
#define	WIFI_GATE_ADDR		WIFI_MASK_ADDR+16
#define	WIFI_DHCP_FLAG_ADDR	WIFI_GATE_ADDR+16
#define WIFI_MODE_SEL_ADDR	WIFI_DHCP_FLAG_ADDR+1
#define WIFI_AP_START_IP_ADDR	WIFI_MODE_SEL_ADDR+1
#define WIFI_AP_END_IP_ADDR		WIFI_AP_START_IP_ADDR+16
#define WIFI_DNS_ADDR			WIFI_AP_END_IP_ADDR+16
//功能键flash地址
#define BUTTON_FUNCTION1_ADDR	WIFI_DNS_ADDR+201
#define BUTTON_FUNCTION2_ADDR	BUTTON_FUNCTION1_ADDR+201

//打印界面更多菜单flash地址
#define BUTTON_MOREFUNC1_ADDR		BUTTON_FUNCTION2_ADDR+201
#define BUTTON_MOREFUNC2_ADDR		BUTTON_MOREFUNC1_ADDR+201
#define BUTTON_MOREFUNC3_ADDR		BUTTON_MOREFUNC2_ADDR+201
#define BUTTON_MOREFUNC4_ADDR		BUTTON_MOREFUNC3_ADDR+201
#define BUTTON_MOREFUNC5_ADDR		BUTTON_MOREFUNC4_ADDR+201
#define BUTTON_MOREFUNC6_ADDR		BUTTON_MOREFUNC5_ADDR+201
//自动调平指令存储地址
#define BUTTON_AUTOLEVELING_ADDR		BUTTON_MOREFUNC6_ADDR+201
#endif
extern uint32_t Sd_file_offset;
extern uint32_t Sd_file_cnt;
//extern uint32_t Sd_display_file_cnt;

extern void ShowSDFiles(void);
extern void ShowUSBFiles(void);

//HC-chen  2017.7.26
#if 1
#define SDSUPPORT      true  //skyblue mask

#define SDPOWER 	   -1
#define SDSS		   70 // 4,10,52 if using HW SPI.
#define ORIG_SDCARDDETECT  69
//#define SDSS		   -1
//#define SDCARDDETECT   69
#define SDCARDDETECTINVERTED false
#endif
#if 1
#define PGM_P	const char *
#define FSTRINGPARAM(var) PGM_P var
#define PSTR(s) s
#define pgm_read_byte(x) (*(char*)x)
#endif
#if 1
#define MAX_VFAT_ENTRIES (2)
/** Total size of the buffer used to store the long filenames */
#define LONG_FILENAME_LENGTH (13*MAX_VFAT_ENTRIES+1)
#define SD_MAX_FOLDER_DEPTH 2
#if SDSUPPORT
extern char tempLongFilename[LONG_FILENAME_LENGTH+1];
extern char fullName[LONG_FILENAME_LENGTH*SD_MAX_FOLDER_DEPTH+
SD_MAX_FOLDER_DEPTH+1];
#define SHORT_FILENAME_LENGTH 14
#include "SdFat.h"
#define    MAX_FILES_ONE_LEVER	   6//30

typedef struct
{
	TCHAR fileName[MAX_FILES_ONE_LEVER][200];//fileName[MAX_FILES_ONE_LEVER][50];
	uint8_t fileAttr[MAX_FILES_ONE_LEVER];	//0?agcode???t?ê?1?a????
	uint8_t index;
	uint8_t listVaild;	//flag of valid
	
} fileNameList;

enum LsAction {LS_SerialPrint,LS_Count,LS_GetFilename};
class SDCard;
class SDCard
{
public:
    //SdFat fat;
    //Sd2Card card; // ~14 Byte
    //SdVolume volume;
    //SdFile root;
    //SdFile dir[SD_MAX_FOLDER_DEPTH+1];
    //SdFile file;
#if JSON_OUTPUT
    GCodeFileInfo fileInfo;
#endif
  FIL curFile;
  FATFS fs;

    uint32_t filesize;
    uint32_t sdpos;
    //char fullName[13*SD_MAX_FOLDER_DEPTH+13]; // Fill name
    char *shortname; // Pointer to start of filename itself
    char *pathend; // File to char where pathname in fullname ends
    uint8_t sdmode;  // true if we are printing from sd card, 2 = stop 
//accepting new commands
    bool sdactive;
    bool usbactive;
    //int16_t n;
    bool savetosd;
    SdBaseFile parentFound;
  uint32_t Sd_file_offset;
  uint32_t Sd_file_cnt;
  TCHAR gCurDir[100];
  fileNameList gcodeFileList;

    SDCard();
    void initsd();
    //void writeCommand(GCode *code);
    //bool selectFile(const char *filename,bool silent=false);
    bool selectFile(char *filename,bool silent=false);
    void mount();
    void unmount();
    void startPrint();
    void pausePrint(bool intern = false);       //暂停打印
    void continuePrint(bool intern = false);    //继续打印
    void stopPrint();                           //停止打印
    void operatePrint();
    
    void mksWriteToEpr();             //暂停、断电后保存数据，以备断电后续打
    void mksReadFrEpr();              //暂停、断电后读取数据
    void mksContiuePrint();           //暂停、断电后续打
    void mksContiuePrint_interface(); //续打提示界面
    void printStatusCheck();            //检查是否续打
    void savecurFileName();             //保存文件名
    void deltaContinuePrint();          //delta 机型暂停，断电续打前处理
    void CartesianContinuePrint();      //cartesian 机型暂停，断电续打前处理 
//    uint32_t sdposbuf[SDPOS_BUF_LEN];   //sdpos 位置BUF
    uint32_t *sdposbufP;   //sdbuf 位置BUF指针
    void saveSdpos();
    void mksRecoverXYE();        //直接断电时恢复X,Y坐标
    void mksCalculateSdpos();
    void mksUpdateXYZE();
    void mksFalaInit();
    //void mksFastPause();
    /*inline void setIndex(uint32_t  newpos)
    {
        if(!sdactive) return;
        sdpos = newpos;
        file.seekSet(sdpos);
    }*/
    void printStatus();
    void ls();
#if JSON_OUTPUT
    void lsJSON(const char *filename);
    void JSONFileInfo(const char *filename);
    static void printEscapeChars(const char *s);
#endif
    void startWrite(char *filename);
    void deleteFile(char *filename);
    void finishWrite();
    char *createFilename(char *buffer,const dir_t &p);
    void makeDirectory(char *filename);
    bool showFilename(const uint8_t *name);
    void automount();
  void get_file_list(char *path);
  uint8_t Explore_Disk (char* path , uint8_t recu_level);
  void ShowSDFiles(void);
  void ShowUSBFiles(void);	
	int ascii2dec(char *ascii, char width);
	void get_sd_cfg(void);
    	void get_sd_cfg2(void);    //**
#ifdef GLENN_DEBUG
    void writeToFile();
#endif
private:
    uint8_t lsRecursive(SdBaseFile *parent,uint8_t level,char *findFilename);
// SdFile *getDirectory(char* name);
};

extern SDCard sd;
#endif
#endif
#endif
