#ifndef _DRAW_FILETRANSFER_H_
#define _DRAW_FILETRANSFER_H_
#include "stdint.h"


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void draw_filetansfer(uint8_t file_unzip_flg);
extern void disp_filetransfer_info(uint8_t FileTransferHandleType);
extern void setFileTransferBarValue(uint8_t fileprocess,uint32_t unzipsize);
extern void Clear_fileTransfer();
extern void draw_dialog_filetransfer(uint8_t WifiTransferDialogType);
extern void Clear_WifiFileTransferdialog();

#if defined(__cplusplus)
}     /* Make sure we have C-declarations in C++ programs */
#endif



#endif


