#ifndef __AT24CXX_H_
#define __AT24CXX_H_
#ifdef __cplusplus
 extern "C" {
#endif


#include "i2c.h"


#define AT24C01		127		//PAGE_SIZE	8	byte
#define AT24C02		255		//PAGE_SIZE	8	byte
#define AT24C04		511		//PAGE_SIZE	16	byte
#define AT24C08		1023	//PAGE_SIZE	16	byte
#define AT24C16		2047	//PAGE_SIZE	16	byte
#define AT24C32		4095
#define AT24C64	        8191
#define AT24C128	16383
#define AT24C256	32767  

#define AT24CXX_TYPE		AT24C16
#define AT24CXX_ADDRESS		0XA0
#define AT24CXX_PAGE_SIZE	16//8

//#if (AT24CXX_TYPE < AT24C04)        //skyblue
#if (AT24CXX_TYPE < AT24C32)        //skyblue
#define AT24CXX_MEMADD_SIZE	I2C_MEMADD_SIZE_8BIT	
#else
#define AT24CXX_MEMADD_SIZE	I2C_MEMADD_SIZE_16BIT	
#endif

#if 0
void AT24CXX_Init(void);
void AT24CXX_WriteByte(uint8_t Reg, uint8_t Value);
uint8_t AT24CXX_ReadByte(uint8_t Reg);
HAL_StatusTypeDef AT24CXX_PageWrite(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef AT24CXX_Write(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef AT24CXX_Read(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef AT24CXX_IsDeviceReady(uint32_t Trials);

uint8_t AT24CXX_Check(void);
#endif
#undef F_CPU
#define F_CPU       21000000        // should be factor of F_CPU_TRUE
#define F_CPU_TRUE  168000000        // actual CPU clock frequency
#define EEPROM_BYTES 2048//4096  // bytes of eeprom we simulate
inline void memcopy2(void *dest,void *source) {
	*((int16_t*)dest) = *((int16_t*)source);
}
inline void memcopy4(void *dest,void *source) {
	*((int32_t*)dest) = *((int32_t*)source);
}
//add HC-chen 2017.7.25
#define EEPROM_BYTES 2048//4096  // bytes of eeprom we simulate

union eeval_t {
  uint8_t     b[4];
  float       f;
  uint32_t    i;
  uint16_t    s;
  long        l;
};
#pragma   pack()

class HAL
{
  public:
    // we use ram instead of eeprom, so reads are faster and safer. Writes store in real eeprom as well
    // as long as hal eeprom functions are used.
    static char virtualEeprom[EEPROM_BYTES];
    static bool wdPinged;
    
    HAL();
    virtual ~HAL();

    // do any hardware-specific initialization here
    static inline void hwSetup(void)
    {
     	//uint8_t tm[256];
#if EEPROM_MODE != 0			
      AT24CXX_Init();
      
     /*-------------------WRITE TEST------------------------*/
     /*
      u8 e2pr_Buf_Write[256];
	 for(int j=0;j<8;j++)
	{
		for(int i_e2pr=0;i_e2pr<256;i_e2pr++)
		{
			e2pr_Buf_Write[i_e2pr]=i_e2pr;
			if(i_e2pr == 0) e2pr_Buf_Write[i_e2pr] = j;
				
		}
		AT24CXX_Write(j*256,e2pr_Buf_Write,256);
	}
      
      eprSetLong(0,0xa1a2a3a4);
      eprSetLong(2044,0xa5a6a7a8);
*/
      /*------------------WRITE TEST-------------------------*/
		 /*
		 for(int j=0;j<256;j++)
		 	{
		 		tm[j]=0xff;
		 	}
		 for(int t=0;t<8;t++)
		 	{
		 		HAL::AT24CXX_Write(t*256, &tm[t*256], 256);
		 	}
      */
      for(int i=0;i<8;i++)
      {
	AT24CXX_Read(i*256,(u8 *)&virtualEeprom[i*256],256);
	//for(int j=0;j<256;j++)
        //  printf("0x%02X ", virtualEeprom[i*256+j]);
       // printf("\n\r\n");
      } 

			
      //while(1);
      /*
      u8 eepData[4];
      eprSetByte(0,0xa0);
      AT24CXX_Read(0,&eepData[0],1);
      printf("0x%02X ", eepData[0]);
      
      eprSetInt16(0,0xa1a2);
      AT24CXX_Read(1,&eepData[0],2);
      printf("0x%02X,0x%02X ", eepData[0],eepData[1]);
      */
      /*
      u8 eepData[4];
      eprSetLong(0,0xa1a2a3a4);
      AT24CXX_Read(0,&eepData[0],4);
      printf("0x%02X,0x%02X,0x%02X,0x%02X  ", eepData[0],eepData[1],eepData[2],eepData[3]);
      
      eprSetLong(2044,0xa5a6a7a8);
      AT24CXX_Read(2044,&eepData[0],4);
      printf("0x%02X,0x%02X,0x%02X,0x%02X  ", eepData[0],eepData[1],eepData[2],eepData[3]);
      */
 #endif     
    }

    static uint32_t integer64Sqrt(uint64_t a);
    // return val'val
    static inline unsigned long U16SquaredToU32(unsigned int val)
    {
      return (unsigned long) val * (unsigned long) val;
    }
    static inline unsigned int ComputeV(long timer, long accel)
    {
      return static_cast<unsigned int>((static_cast<int64_t>(timer) * static_cast<int64_t>(accel)) >> 18);
      //return ((timer>>8)*accel)>>10;
    }
    // Multiply two 16 bit values and return 32 bit result
    static inline unsigned long mulu16xu16to32(unsigned int a, unsigned int b)
    {
      return (unsigned long) a * (unsigned long) b;
    }
    // Multiply two 16 bit values and return 32 bit result
    static inline unsigned int mulu6xu16shift16(unsigned int a, unsigned int b)
    {
      return ((unsigned long)a * (unsigned long)b) >> 16;
    }
    static inline unsigned int Div4U2U(unsigned long a, unsigned int b)
    {
      return ((unsigned long)a / (unsigned long)b);
    }
    /*static inline void digitalWrite(uint8_t pin, uint8_t value)
    {
      WRITE_VAR(pin, value);
    }
    static inline uint8_t digitalRead(uint8_t pin)
    {
      return READ_VAR(pin);
    }
    static inline void pinMode(uint8_t pin, uint8_t mode)
    {
      if (mode == INPUT) {
        SET_INPUT(pin);
      }
      else SET_OUTPUT(pin);
    }*/
    static long CPUDivU2(speed_t divisor) {
      return F_CPU / divisor;
    }
    static inline void delayMicroseconds(uint32_t usec)
    { //usec += 3;
    //tan 20161128
    	//microsecondsWait(usec);
    	volatile uint32_t STEPPER_DELAY=0;
    	#if 0
    	uint32_t usec_bak;
			usec_bak = usec;
    	while(1)
    	{
    		usec = usec_bak;
	    	GPIOB->BRR = GPIO_Pin_3;
				while(usec--)
				{
	    		STEPPER_DELAY = 5;//usec;
	    		while(STEPPER_DELAY--);
				}
				GPIOB->BSRR = GPIO_Pin_3;
				usec = usec_bak;
				while(usec--)
				{
	    		STEPPER_DELAY = 5;//usec;
	    		while(STEPPER_DELAY--);
				}

    	}
			#endif
			
			if((usec != 0)&&(usec != 0xffffffff))
			{
				while(usec--)
				{
		    		STEPPER_DELAY = 5;//usec;
		    		while(STEPPER_DELAY--);
				}
			}
      /*uint32_t n = usec * (F_CPU_TRUE / 3000000);
      asm volatile(
        "L2_%=_delayMicroseconds:"       "\n\t"
        "subs   %0, #1"                 "\n\t"
        "bge    L2_%=_delayMicroseconds" "\n"
        : "+r" (n) :
      );*/
    }
    static inline void delayMilliseconds(unsigned int delayMs)
    {
      unsigned int del;
      while (delayMs > 0) {
        del = delayMs > 100 ? 100 : delayMs;
        delay(del);
        delayMs -= del;
#if FEATURE_WATCHDOG
        HAL::pingWatchdog();
#endif
      }
    }
    static inline void tone(uint8_t pin, int frequency) {
      // set up timer counter 1 channel 0 to generate interrupts for
      // toggling output pin.
      /*SET_OUTPUT(pin);
      tone_pin = pin;
      pmc_set_writeprotect(false);
      pmc_enable_periph_clk((uint32_t)BEEPER_TIMER_IRQ);
      // set interrupt to lowest possible priority
      NVIC_SetPriority((IRQn_Type)BEEPER_TIMER_IRQ, NVIC_EncodePriority(4, 6, 3));
      TC_Configure(BEEPER_TIMER, BEEPER_TIMER_CHANNEL, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC |
                   TC_CMR_TCCLKS_TIMER_CLOCK4);  // TIMER_CLOCK4 -> 128 divisor
      uint32_t rc = VARIANT_MCK / 128 / frequency;
      TC_SetRA(BEEPER_TIMER, BEEPER_TIMER_CHANNEL, rc / 2);                   // 50% duty cycle
      TC_SetRC(BEEPER_TIMER, BEEPER_TIMER_CHANNEL, rc);
      TC_Start(BEEPER_TIMER, BEEPER_TIMER_CHANNEL);
      BEEPER_TIMER->TC_CHANNEL[BEEPER_TIMER_CHANNEL].TC_IER = TC_IER_CPCS;
      BEEPER_TIMER->TC_CHANNEL[BEEPER_TIMER_CHANNEL].TC_IDR = ~TC_IER_CPCS;
      NVIC_EnableIRQ((IRQn_Type)BEEPER_TIMER_IRQ);*/
    }
    static inline void noTone(uint8_t pin) {
      /*TC_Stop(TC1, 0);
      WRITE_VAR(pin, LOW);*/
    }

    static inline void eprSetByte(unsigned int pos, uint8_t value)
    {
      eeval_t v;
      v.b[0] = value;
      eprBurnValue(pos, 1, v);
      *(uint8_t*)&virtualEeprom[pos] = value;
    }
    static inline void eprSetInt16(unsigned int pos, int16_t value)
    {
      eeval_t v;
      v.s = value;
      eprBurnValue(pos, 2, v);
      memcopy2(&virtualEeprom[pos],&value);
    }
    static inline void eprSetInt32(unsigned int pos, int32_t value)
    {
      eeval_t v;
			unsigned int pos1;
			pos1 = pos;
      v.i = value;
      eprBurnValue(pos, 4, v);
      memcopy4(&virtualEeprom[pos],&value);
			v = eprGetValue(pos1,4);
    }
    static inline void eprSetLong(unsigned int pos, long value)
    {
      eeval_t v;
      v.l = value;
      eprBurnValue(pos, sizeof(long), v);
      memcopy4(&virtualEeprom[pos],&value);
			v = eprGetValue(pos,sizeof(long));
    }
    static inline void eprSetFloat(unsigned int pos, float value)
    {
      eeval_t v;
      v.f = value;
      eprBurnValue(pos, sizeof(float), v);
      memcopy4(&virtualEeprom[pos],&value);
			v = eprGetValue(pos,sizeof(float));
    }
    static inline uint8_t eprGetByte(unsigned int pos)
    {
      return *(uint8_t*)&virtualEeprom[pos];
    }
    static inline int16_t eprGetInt16(unsigned int pos)
    {
      int16_t v;
      memcopy2(&v,&virtualEeprom[pos]);
      return v;
    }
    static inline int32_t eprGetInt32(unsigned int pos)
    {
      int32_t v;
      memcopy4(&v,&virtualEeprom[pos]);
      return v;
    }
    static inline long eprGetLong(unsigned int pos)
    {
      int32_t v;
      memcopy4(&v,&virtualEeprom[pos]);
      return v;
    }
    static inline float eprGetFloat(unsigned int pos) {
      float v;
      memcopy4(&v,&virtualEeprom[pos]);
      return v;
    }

    // Write any data type to EEPROM
    static inline void eprBurnValue(unsigned int pos, int size, union eeval_t newvalue)
    {
      //void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
      AT24CXX_Write(pos,&newvalue.b[0],size);

    }

    // Read any data type from EEPROM that was previously written by eprBurnValue
    static inline union eeval_t eprGetValue(unsigned int pos, int size)
    {
      eeval_t v;
    //void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
      AT24CXX_Read(pos,&v.b[0],size);
      return v;       
}
    static inline void allowInterrupts()
    {
      //TIM2->CR1 |= TIM_CR1_CEN;
      //TIM4->CR1 |= TIM_CR1_CEN;
      __ASM volatile("cpsie i");
      
    }
    static inline void forbidInterrupts()
    {
      //TIM2->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
      //TIM4->CR1 &= (uint16_t)(~((uint16_t)TIM_CR1_CEN));
      __ASM volatile("cpsid i");
    }
#if 0
    static inline unsigned long timeInMilliseconds()
    {
      //**return millis();
    }
    static inline char readFlashByte(PGM_P ptr)
    {
      //**return pgm_read_byte(ptr);
    }
    static inline void serialSetBaudrate(long baud)
    {
#if defined(BLUETOOTH_SERIAL) && BLUETOOTH_SERIAL > 0
      //**BTAdapter.begin(baud);
#else
     //** RFSERIAL.begin(baud);
#endif
    }
    static inline bool serialByteAvailable()
    {
#if defined(BLUETOOTH_SERIAL) && BLUETOOTH_SERIAL > 0
      //**return BTAdapter.available();
#else
      //**return RFSERIAL.available();
#endif
    }
    static inline uint8_t serialReadByte()
    {
#if defined(BLUETOOTH_SERIAL) && BLUETOOTH_SERIAL > 0
     //** return BTAdapter.read();
#else
      //**return RFSERIAL.read();
#endif
    }
    static inline void sdpause()
    {
      //**RFSERIAL.sdPause();
    }
    static inline void sdcontinue()
    {
      //**RFSERIAL.sdContinue();
    }
    static inline int Usartcheck()
    {
      //**return RFSERIAL.check();
    }

    static inline void serialWriteByte(char b)
    {
#if defined(BLUETOOTH_SERIAL) && BLUETOOTH_SERIAL > 0
      //**BTAdapter.write(b);
#else
      //**RFSERIAL.write(b);
#endif
    }
    static inline void serialFlush()
    {
#if defined(BLUETOOTH_SERIAL) && BLUETOOTH_SERIAL > 0
      //**BTAdapter.flush();
#else
      //**RFSERIAL.flush();
#endif
    }
		//tan 20160817
		static inline void MoremenuCmd(void)
		{
			//**RFSERIAL.MoremenuCmd();
		}
		
		static inline void Leveling_move_action(void)
		{
			//**RFSERIAL.Leveling_move_action();
		}
		static inline void filamentchange(void)
		{
			//**RFSERIAL.filamentchange();
		}

		
		//tan0906
		static void get_Temperature_ad_value();
		
    static void setupTimer();
    static void showStartReason();
    static int getFreeRam();
    static void resetHardware();
    static void  pinMode( uint32_t ulPin, uint32_t ulMode );
    static int digitalRead( uint32_t ulPin );
    static void digitalWrite( uint32_t ulPin, uint32_t ulVal );

    // SPI related functions

#ifdef DUE_SOFTWARE_SPI
    // bitbanging transfer
    // run at ~100KHz (necessary for init)
    static uint8_t spiTransfer(uint8_t b)  // using Mode 0
    {
      /*for (int bits = 0; bits < 8; bits++) {
        if (b & 0x80) {
          WRITE(MOSI_PIN, HIGH);
        } else {
          WRITE(MOSI_PIN, LOW);
        }
        b <<= 1;

        WRITE(SCK_PIN, HIGH);
        delayMicroseconds(5);

        if (READ(MISO_PIN)) {
          b |= 1;
        }
        WRITE(SCK_PIN, LOW);
        delayMicroseconds(5);
      }
      return b;*/   //**
    }
    static inline void spiBegin()
    {
     /* SET_OUTPUT(SDSS);
      WRITE(SDSS, HIGH);
      SET_OUTPUT(SCK_PIN);
      SET_INPUT(MISO_PIN);
      SET_OUTPUT(MOSI_PIN);*/  //**
    }

    static inline void spiInit(uint8_t spiClock)
    {
     /* WRITE(SDSS, HIGH);
      WRITE(MOSI_PIN, HIGH);
      WRITE(SCK_PIN, LOW);*/  //**
    }
    static inline uint8_t spiReceive()
    {
     /* WRITE(SDSS, LOW);
      uint8_t b = spiTransfer(0xff);
      WRITE(SDSS, HIGH);
      return b;*/    //**
    }
    static inline void spiReadBlock(uint8_t*buf, uint16_t nbyte)
    {
     /* if (nbyte == 0) return;
      WRITE(SDSS, LOW);
      for (int i = 0; i < nbyte; i++)
      {
        buf[i] = spiTransfer(0xff);
      }
      WRITE(SDSS, HIGH);*/   //**

    }
    static inline void spiSend(uint8_t b) {
      /*WRITE(SDSS, LOW);
      uint8_t response = spiTransfer(b);
      WRITE(SDSS, HIGH);*/  //**
    }

    static inline void spiSend(const uint8_t* buf , size_t n)
    {
     /* if (n == 0) return;
      WRITE(SDSS, LOW);
      for (uint16_t i = 0; i < n; i++) {
        spiTransfer(buf[i]);
      }
      WRITE(SDSS, HIGH);*/  //**
    }

    inline __attribute__((always_inline))
    static void spiSendBlock(uint8_t token, const uint8_t* buf)
    {
/*      WRITE(SDSS, LOW);
      spiTransfer(token);

      for (uint16_t i = 0; i < 512; i++)
      {
        spiTransfer(buf[i]);
      }
      WRITE(SDSS, HIGH);*/  //**
    }

#else

    // hardware SPI
    static void spiBegin();
    // spiClock is 0 to 6, relecting AVR clock dividers 2,4,8,16,32,64,128
    // Due can only go as slow as AVR divider 32 -- slowest Due clock is 329,412 Hz
    static void spiInit(uint8_t spiClock);
    // Write single byte to SPI
    static void spiSend(byte b);
    static void spiSend(const uint8_t* buf , size_t n);
#if MOTHERBOARD == 500 || MOTHERBOARD == 501
    static void spiSend(uint32_t chan , const uint8_t* buf , size_t n);
    static void spiSend(uint32_t chan, byte b);
    static uint8_t spiReceive(uint32_t chan);
#endif
    // Read single byte from SPI
    static uint8_t spiReceive();
    // Read from SPI into buffer
    static void spiReadBlock(uint8_t*buf, uint16_t nbyte);

    // Write from buffer to SPI

    static void spiSendBlock(uint8_t token, const uint8_t* buf);
#endif  /*DUE_SOFTWARE_SPI*/
#endif

    // I2C Support
//skyblue 2006-12-05
/*--------------------------MKS EEPROM-------------------------*/    
static void AT24CXX_Init(void);
static void AT24CXX_WriteByte(uint8_t Reg, uint8_t Value);
static uint8_t AT24CXX_ReadByte(uint8_t Reg);
static HAL_StatusTypeDef AT24CXX_PageWrite(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
static HAL_StatusTypeDef AT24CXX_Write(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
static HAL_StatusTypeDef AT24CXX_Read(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
static HAL_StatusTypeDef AT24CXX_IsDeviceReady(uint32_t Trials);
static uint8_t AT24CXX_Check(void);
static uint8_t I2Cx_Read(uint8_t Addr, uint8_t Reg, uint16_t MemAddSize);
static void I2Cx_Write(uint8_t Addr, uint8_t Reg, uint16_t MemAddSize, uint8_t Value);
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void I2Cx_Error(uint8_t Addr);

  static void delay_us(u32 nus);
/*--------------------------MKS EEPROM-------------------------*/

    // Watchdog support
    inline static void startWatchdog() {
      //WDT->WDT_MR = WDT_MR_WDRSTEN | WATCHDOG_INTERVAL | (WATCHDOG_INTERVAL << 16);
      //WDT->WDT_CR = 0xA5000001;
    };
    inline static void stopWatchdog() {}
    inline static void pingWatchdog() {
#if FEATURE_WATCHDOG
      wdPinged = true;
#endif
    };

    inline static float maxExtruderTimerFrequency() {
      return (float)F_CPU_TRUE/32;
    }
#if FEATURE_SERVO
    static unsigned int servoTimings[4];
    static void servoMicroseconds(uint8_t servo, int ms, uint16_t autoOff);
#endif

//#if ANALOG_INPUTS > 0
    static void analogStart(void);
//#endif
#if USE_ADVANCE
    static void resetExtruderDirection();
#endif
		static void microsecondsWait(uint32_t us);
    static volatile uint8_t insideTimer1;

};
/*---------------------GPIO--------------------------------*/

#if 0
/*-------------电机步进-----------------*/
#define	XSTEP_OP  PEout(6)
#define	YSTEP_OP  PEout(3)
#define	ZSTEP_OP  PEout(0)
#define	E0STEP_OP PGout(10)
#define	E1STEP_OP PDout(3)
/*-------------电机方向-----------------*/
#define	XDIR_OP  PEout(5)
#define	YDIR_OP  PEout(2)
#define	ZDIR_OP  PBout(9)
#define	E0DIR_OP PGout(9)
#define	E1DIR_OP PAout(15)

#define	XDIR_IP  PEin(5)
#define	YDIR_IP  PEin(2)
#define	ZDIR_IP  PBin(9)
#define	E0DIR_IP PGin(9)
#define	E1DIR_IP PAin(15)
/*-------------电机使能-----------------*/
#define	XENA_OP  PCout(13)
#define	YENA_OP  PEout(4)
#define	ZENA_OP  PEout(1)
#define	E0ENA_OP PBout(8)
#define	E1ENA_OP PDout(6)
/*-------------限位开关-----------------*/
#define XMIN_OP   PGin(8)              
#define XMAX_OP   PGin(7)      
#define YMIN_OP   PGin(6)      
#define YMAX_OP   PGin(5)      
#define ZMIN_OP   PGin(4)
#define ZMAX_OP   PGin(3)
#define Z_PROBE_OP	PGin(4)

/*-------------法拉电容-----------------*/

#define EXT3V3_ON       0
#define EXT3V3_OFF      1

#define FALA_5V_CTRL PAout(0)      //1-FALA5V ON;0- FALA5V OFF         //FALA
#define EXT_3V3_CTRL PAout(6)      //0-EXT3V3 ON;1- EXT3V3 OFF

//**#define SD_DET_IP PBin(0)



//#define TEST_OP   PBout(0)
#define MKS_TEST_OP  PBout(1)


//**#define SPEAKER   PFout(11) 



#define	MKS_FAN_OP          PFout(1)
#define	MKS_HEATER1_OP      PFout(3)
#define	MKS_HEATER2_OP      PFout(2)
#define	MKS_BED_OP          PFout(4)

#define	MKS_PW_OFF_OP       PGout(1)
#define	MKS_MT_DET1_OP      PFin(14)
#define	MKS_MT_DET2_OP      PFin(13)

/*-------------LCD CONTROL IO----------------*/
#define	MKS_LCD_RST            PDout(13)
#define	MKS_LCD_ON             PDout(12)
/*-------------WIFI CONTROL IO----------------*/
#define	MKS_WIFI_RST            PGout(2)
#define	MKS_WIFI_CS             PBout(12)
#endif
#ifdef __cplusplus
}
#endif

#endif












