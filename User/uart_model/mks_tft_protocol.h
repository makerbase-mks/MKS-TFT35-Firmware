#ifndef MKS_TFT_PROTOCOL_H
#define MKS_TFT_PROTOCOL_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif
extern unsigned char resendProcess(void);
extern unsigned char resendProcess_repetier(void);
extern void prTxNext(void);
extern void usart2TxStart(void);
extern void printerInit(void);
extern void pushInitGcode(void);
extern unsigned char recOkProcess(void );

#if defined(__cplusplus)
}
#endif

#endif


