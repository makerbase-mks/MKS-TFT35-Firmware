#ifndef _DRAW_WIFI_LIST_H_
#define _DRAW_WIFI_LIST_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void draw_Wifi_list();
extern void Clear_Wifi_list();
extern void disp_wifi_list(void);
extern void cutWifiName(char *name, int len,char *outStr);

#define NUMBER_OF_PAGE 5

#define WIFI_TOTAL_NUMBER 20
#define WIFI_NAME_BUFFER_SIZE 33

typedef struct 
{  
  int8_t getNameNum;
  int8_t nameIndex;
  int8_t currentWifipage;
  int8_t getPage;
  int8_t RSSI[WIFI_TOTAL_NUMBER];
  uint8_t wifiName[WIFI_TOTAL_NUMBER][WIFI_NAME_BUFFER_SIZE];
  uint8_t wifiConnectedName[WIFI_NAME_BUFFER_SIZE];
} WIFI_LIST;
extern WIFI_LIST wifi_list;

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif

#endif
