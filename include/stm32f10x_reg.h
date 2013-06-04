/*
 * STM32F10X register header file
 * Modify by WFJ.  2009.3.19
 */

//rev0.0.1
//FLASH->ACR.B.LATENCY
//volatile unsigned short CRCERR		:1;	//PS

#ifndef __STM32F10x_REG_H
#define __STM32F10x_REG_H

#define _ADC
#define _ADC1
#define _ADC2
#define _DAC
#define _BKP
#define _CAN
#define _DMA
#define _DMA_CHANNEL1
#define _DMA_CHANNEL2
#define _DMA_CHANNEL3
#define _DMA_CHANNEL4
#define _DMA_CHANNEL5
#define _DMA_CHANNEL6
#define _DMA_CHANNEL7
#define _EXTI
#define _FLASH
#define _FLASH_PROG
#define _GPIO
#define _GPIOA
#define _GPIOB
#define _GPIOC
#define _GPIOD
#define _GPIOE
#define _AFIO
#define _I2C
#define _I2C1
#define _I2C2
#define _IWDG
#define _NVIC
#define _PWR
#define _RCC
//#define _RTC
#define _SPI
#define _SPI1
#define _SPI2
#define _SYSTICK
#define _TIM1
#define _TIM
#define _TIM2
#define _TIM3
#define _TIM4
#define _USART
#define _USART1
#define _USART2
#define _USART3
#define _WWDG
#define _FSMC



/* typedef ------------------------------------------------------------*/
/******************************************************************************/
/*                         Peripheral registers structures                    */
/******************************************************************************/

/*------------------------ Analog to Digital Converter -----------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long AWD              : 1;
			volatile unsigned long EOC              : 1;
			volatile unsigned long JOC              : 1;
			volatile unsigned long JSTRT            : 1;
			volatile unsigned long STRT             : 1;
			volatile unsigned long NC               : 27;
		} B;
		volatile unsigned long W;
	} SR;
	union {
		struct {
			volatile unsigned long AWDCH            : 5;
			volatile unsigned long EOCIE            : 1;
			volatile unsigned long AWDIE            : 1;
			volatile unsigned long JEOCIE           : 1;
			volatile unsigned long SCAN             : 1;
			volatile unsigned long AWD_SGL  : 1;
			volatile unsigned long JAUTO            : 1;
			volatile unsigned long DISCEN           : 1;
			volatile unsigned long JDISCEN  : 1;
			volatile unsigned long DISCNUM  : 3;
			volatile unsigned long DUALMOD  : 4;
			volatile unsigned long NC1              : 2;
			volatile unsigned long JAWDEN           : 1;
			volatile unsigned long AWDEN            : 1;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} CR1;
	union {
		struct {
			volatile unsigned long ADON             : 1;
			volatile unsigned long CONT             : 1;
			volatile unsigned long CAL              : 1;
			volatile unsigned long RSTCAL           : 1;
			volatile unsigned long NC3              : 4;
			volatile unsigned long DMA              : 1;
			volatile unsigned long NC2              : 2;
			volatile unsigned long ALIGN            : 1;
			volatile unsigned long JEXTSEL  : 3;
			volatile unsigned long JEXTTRIG : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long EXTSEL           : 3;
			volatile unsigned long EXTTRIG  : 1;
			volatile unsigned long JSWSTART : 1;
			volatile unsigned long SWSTART  : 1;
			volatile unsigned long TSVREFE  : 1;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} CR2;
	union {
		struct {
			volatile unsigned long SMP10            : 3;
			volatile unsigned long SMP11            : 3;
			volatile unsigned long SMP12            : 3;
			volatile unsigned long SMP13            : 3;
			volatile unsigned long SMP14            : 3;
			volatile unsigned long SMP15            : 3;
			volatile unsigned long SMP16            : 3;
			volatile unsigned long SMP17            : 3;
			volatile unsigned long NC               : 8;
		} B;
		volatile unsigned long W;
	} SMPR1;
	union {
		struct {
			volatile unsigned long SMP0             : 3;
			volatile unsigned long SMP1             : 3;
			volatile unsigned long SMP2             : 3;
			volatile unsigned long SMP3             : 3;
			volatile unsigned long SMP4             : 3;
			volatile unsigned long SMP5             : 3;
			volatile unsigned long SMP6             : 3;
			volatile unsigned long SMP7             : 3;
			volatile unsigned long SMP8             : 3;
			volatile unsigned long SMP9             : 3;
			volatile unsigned long NC               : 2;
		} B;
		volatile unsigned long W;
	} SMPR2;
	union {
		struct {
			volatile unsigned long JOFFSET1         : 12;
			volatile unsigned long NC               : 20;
		} B;
		volatile unsigned long W;
	} JOFR1;
	union {
		struct {
			volatile unsigned long JOFFSET2         : 12;
			volatile unsigned long NC               : 20;
		} B;
		volatile unsigned long W;
	} JOFR2;
	union {
		struct {
			volatile unsigned long JOFFSET3 : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} JOFR3;
	union {
		struct {
			volatile unsigned long JOFFSET4 : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} JOFR4;
	union {
		struct {
			volatile unsigned long HT                       : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} HTR;
	union {
		struct {
			volatile unsigned long LT                       : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} LTR;
	union {
		struct {
			volatile unsigned long SQ13             : 5;
			volatile unsigned long SQ14             : 5;
			volatile unsigned long SQ15             : 5;
			volatile unsigned long SQ16             : 5;
			volatile unsigned long L                        : 4;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} SQR1;
	union {
		struct {
			volatile unsigned long SQ7              : 5;
			volatile unsigned long SQ8              : 5;
			volatile unsigned long SQ9              : 5;
			volatile unsigned long SQ10             : 5;
			volatile unsigned long SQ11             : 5;
			volatile unsigned long SQ12             : 5;
			volatile unsigned long NC                       : 2;
		} B;
		volatile unsigned long W;
	} SQR2;
	union {
		struct {
			volatile unsigned long SQ1              : 5;
			volatile unsigned long SQ2              : 5;
			volatile unsigned long SQ3              : 5;
			volatile unsigned long SQ4              : 5;
			volatile unsigned long SQ5              : 5;
			volatile unsigned long SQ6              : 5;
			volatile unsigned long NC                       : 2;
		} B;
		volatile unsigned long W;
	} SQR3;
	union {
		struct {
			volatile unsigned long JSQ1             : 5;
			volatile unsigned long JSQ2             : 5;
			volatile unsigned long JSQ3             : 5;
			volatile unsigned long JSQ4             : 5;
			volatile unsigned long JL                       : 2;
			volatile unsigned long NC                       : 10;
		} B;
		volatile unsigned long W;
	} JSQR;
	union {
		struct {
			volatile unsigned long JDATA            : 16;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} JDR1;
	union {
		struct {
			volatile unsigned long JDATA            : 16;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} JDR2;
	union {
		struct {
			volatile unsigned long JDATA            : 16;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} JDR3;
	union {
		struct {
			volatile unsigned long JDATA            : 16;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} JDR4;
	union {
		struct {
			volatile unsigned long DATA             : 16;
			volatile unsigned long ADC2DATA : 16;
		} B;
		volatile unsigned long W;
	} DR;
} ADC_T;

/*------------------------ Backup Registers ----------------------------------*/
typedef struct {
	unsigned long RESERVED0;
	volatile unsigned short DR1;
	unsigned short RESERVED1;
	volatile unsigned short DR2;
	unsigned short RESERVED2;
	volatile unsigned short DR3;
	unsigned short RESERVED3;
	volatile unsigned short DR4;
	unsigned short RESERVED4;
	volatile unsigned short DR5;
	unsigned short RESERVED5;
	volatile unsigned short DR6;
	unsigned short RESERVED6;
	volatile unsigned short DR7;
	unsigned short RESERVED7;
	volatile unsigned short DR8;
	unsigned short RESERVED8;
	volatile unsigned short DR9;
	unsigned short RESERVED9;
	volatile unsigned short DR10;
	unsigned short RESERVED10;
	union {
		struct {
			volatile unsigned short CAL             : 7;
			volatile unsigned short CCO             : 1;
			volatile unsigned short ASOE            : 1;
			volatile unsigned short ASOS            : 1;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	} RTCCR;
	unsigned short RESERVED11;
	union {
		struct {
			volatile unsigned short TPE             : 1;
			volatile unsigned short TPAL            : 1;
			volatile unsigned short NC                      : 14;
		} B;
		volatile unsigned short W;
	} CR;
	unsigned short RESERVED12;
	union {
		struct {
			volatile unsigned short CTE             : 1;
			volatile unsigned short CTI             : 1;
			volatile unsigned short TPIE            : 1;
			volatile unsigned short NC1             : 5;
			volatile unsigned short TEF             : 1;
			volatile unsigned short TIF             : 1;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	} CSR;

	unsigned short RESERVED13[5];
	volatile unsigned short DR11;
	unsigned short RESERVED14;
	volatile unsigned short DR12;
	unsigned short RESERVED15;
	volatile unsigned short DR13;
	unsigned short RESERVED16;
	volatile unsigned short DR14;
	unsigned short RESERVED17;
	volatile unsigned short DR15;
	unsigned short RESERVED18;
	volatile unsigned short DR16;
	unsigned short RESERVED19;
	volatile unsigned short DR17;
	unsigned short RESERVED20;
	volatile unsigned short DR18;
	unsigned short RESERVED21;
	volatile unsigned short DR19;
	unsigned short RESERVED22;
	volatile unsigned short DR20;
	unsigned short RESERVED23;
	volatile unsigned short DR21;
	unsigned short RESERVED24;
	volatile unsigned short DR22;
	unsigned short RESERVED25;
	volatile unsigned short DR23;
	unsigned short RESERVED26;
	volatile unsigned short DR24;
	unsigned short RESERVED27;
	volatile unsigned short DR25;
	unsigned short RESERVED28;
	volatile unsigned short DR26;
	unsigned short RESERVED29;
	volatile unsigned short DR27;
	unsigned short RESERVED30;
	volatile unsigned short DR28;
	unsigned short RESERVED31;
	volatile unsigned short DR29;
	unsigned short RESERVED32;
	volatile unsigned short DR30;
	unsigned short RESERVED33;
	volatile unsigned short DR31;
	unsigned short RESERVED34;
	volatile unsigned short DR32;
	unsigned short RESERVED35;
	volatile unsigned short DR33;
	unsigned short RESERVED36;
	volatile unsigned short DR34;
	unsigned short RESERVED37;
	volatile unsigned short DR35;
	unsigned short RESERVED38;
	volatile unsigned short DR36;
	unsigned short RESERVED39;
	volatile unsigned short DR37;
	unsigned short RESERVED40;
	volatile unsigned short DR38;
	unsigned short RESERVED41;
	volatile unsigned short DR39;
	unsigned short RESERVED42;
	volatile unsigned short DR40;
	unsigned short RESERVED43;
	volatile unsigned short DR41;
	unsigned short RESERVED44;
	volatile unsigned short DR42;
	unsigned short RESERVED45;
} BKP_T;

/*------------------------ Controller Area Network ---------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long TXRQ             : 1;
			volatile unsigned long RTR              : 1;
			volatile unsigned long IDE              : 1;
			volatile unsigned long EXID             : 29;
		} BExt;
		struct {
			volatile unsigned long TXRQ             : 1;
			volatile unsigned long RTR              : 1;
			volatile unsigned long IDE              : 1;
			volatile unsigned long NC                       : 18;
			volatile unsigned long STID             : 11;
		} B;
		volatile unsigned long W;
	} TIR;
	union {
		struct {
			volatile unsigned long DLC              : 4;
			volatile unsigned long NC1              : 4;
			volatile unsigned long TGT              : 1;
			volatile unsigned long NC                       : 7;
			volatile unsigned long TIME             : 16;
		} B;
		volatile unsigned long W;
	} TDTR;
	union {
		struct {
			volatile unsigned long DATA0            : 8;
			volatile unsigned long DATA1            : 8;
			volatile unsigned long DATA2            : 8;
			volatile unsigned long DATA3            : 8;
		} B;
		volatile unsigned long W;
	} TDLR;
	union {
		struct {
			volatile unsigned long DATA4            : 8;
			volatile unsigned long DATA5            : 8;
			volatile unsigned long DATA6            : 8;
			volatile unsigned long DATA7            : 8;
		} B;
		volatile unsigned long W;
	} TDHR;
} CAN_TxMailBox_T;

typedef struct {
	union {
		struct {
			volatile unsigned long NC                       : 1;
			volatile unsigned long RTR              : 1;
			volatile unsigned long IDE              : 1;
			volatile unsigned long EXID             : 29;
		} BExt;
		struct {
			volatile unsigned long NC                       : 1;
			volatile unsigned long RTR              : 1;
			volatile unsigned long IDE              : 1;
			volatile unsigned long NC1              : 18;
			volatile unsigned long STID             : 11;
		} B;
		volatile unsigned long W;
	} RIR;
	union {
		struct {
			volatile unsigned long DLC              : 4;
			volatile unsigned long NC2              : 4;
			volatile unsigned long FMI              : 8;
			volatile unsigned long TIME             : 16;
		} B;
		volatile unsigned long W;
	} RDTR;
	union {
		struct {
			volatile unsigned long DATA0            : 8;
			volatile unsigned long DATA1            : 8;
			volatile unsigned long DATA2            : 8;
			volatile unsigned long DATA3            : 8;
		} B;
		volatile unsigned long W;
	} RDLR;
	union {
		struct {
			volatile unsigned long DATA4            : 8;
			volatile unsigned long DATA5            : 8;
			volatile unsigned long DATA6            : 8;
			volatile unsigned long DATA7            : 8;
		} B;
		volatile unsigned long W;
	} RDHR;
} CAN_FIFOMailBox_T;

typedef struct {
	volatile unsigned long FR1;
	volatile unsigned long FR2;
} CAN_FilterRegister_T;

typedef struct {
	union {
		struct {
			volatile unsigned long INRQ             : 1;
			volatile unsigned long SLEEP            : 1;
			volatile unsigned long TXFP             : 1;
			volatile unsigned long RFLM             : 1;
			volatile unsigned long NART             : 1;
			volatile unsigned long AWUM             : 1;
			volatile unsigned long ABOM             : 1;
			volatile unsigned long TTCM             : 1;
			volatile unsigned long NC1              : 7;
			volatile unsigned long RESET            : 1;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} MCR;
	union {
		struct {
			volatile unsigned long INAK             : 1;
			volatile unsigned long SLAK             : 1;
			volatile unsigned long ERRI             : 1;
			volatile unsigned long WKUI             : 1;
			volatile unsigned long SLAKI            : 1;
			volatile unsigned long NC1              : 3;
			volatile unsigned long TXM              : 1;
			volatile unsigned long RXM              : 1;
			volatile unsigned long SAMP             : 1;
			volatile unsigned long RX                       : 1;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} MSR;
	union {
		struct {
			volatile unsigned long RQCP0            : 1;
			volatile unsigned long TXOK0            : 1;
			volatile unsigned long ALST0            : 1;
			volatile unsigned long TERR0            : 1;
			volatile unsigned long NC0              : 3;
			volatile unsigned long ABRQ0            : 1;
			volatile unsigned long RQCP1            : 1;
			volatile unsigned long TXOK1            : 1;
			volatile unsigned long ALST1            : 1;
			volatile unsigned long TERR1            : 1;
			volatile unsigned long NC1              : 3;
			volatile unsigned long ABRQ1            : 1;
			volatile unsigned long RQCP2            : 1;
			volatile unsigned long TXOK2            : 1;
			volatile unsigned long ALST2            : 1;
			volatile unsigned long TERR2            : 1;
			volatile unsigned long NC2              : 3;
			volatile unsigned long ABRQ2            : 1;
			volatile unsigned long CODE             : 2;
			volatile unsigned long TME0             : 1;
			volatile unsigned long TME1             : 1;
			volatile unsigned long TME2             : 1;
			volatile unsigned long LOW0             : 1;
			volatile unsigned long LOW1             : 1;
			volatile unsigned long LOW2             : 1;
		} B;
		volatile unsigned long W;
	} TSR;
	union {
		struct {
			volatile unsigned long FMP0             : 2;
			volatile unsigned long NC1              : 1;
			volatile unsigned long FULL0            : 1;
			volatile unsigned long FOVR0            : 1;
			volatile unsigned long RFOM0            : 1;
			volatile unsigned long NC                       : 26;
		} B;
		volatile unsigned long W;
	} RF0R;
	union {
		struct {
			volatile unsigned long FMP1             : 2;
			volatile unsigned long NC1              : 1;
			volatile unsigned long FULL1            : 1;
			volatile unsigned long FOVR1            : 1;
			volatile unsigned long RFOM1            : 1;
			volatile unsigned long NC                       : 26;
		} B;
		volatile unsigned long W;
	} RF1R;
	union {
		struct {
			volatile unsigned long TMEIE            : 1;
			volatile unsigned long FMPIE0           : 1;
			volatile unsigned long FFIE0            : 1;
			volatile unsigned long FOVIE0           : 1;
			volatile unsigned long FMPIE1           : 1;
			volatile unsigned long FFIE1            : 1;
			volatile unsigned long FOVIE1           : 1;
			volatile unsigned long NC2              : 1;
			volatile unsigned long EWGIE            : 1;
			volatile unsigned long EPVIE            : 1;
			volatile unsigned long BOFIE            : 1;
			volatile unsigned long LECIE            : 1;
			volatile unsigned long NC1              : 3;
			volatile unsigned long ERRIE            : 1;
			volatile unsigned long WKUIE            : 1;
			volatile unsigned long SLKIE            : 1;
			volatile unsigned long NC                       : 14;
		} B;
		volatile unsigned long W;
	} IER;
	union {
		struct {
			volatile unsigned long EWGF             : 1;
			volatile unsigned long EPVF             : 1;
			volatile unsigned long BOFF             : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long LEC              : 3;
			volatile unsigned long NC                       : 9;
			volatile unsigned long TEC              : 8;
			volatile unsigned long REC              : 8;
		} B;
		volatile unsigned long W;
	} ESR;
	union {
		struct {
			volatile unsigned long BRP              : 10;
			volatile unsigned long NC2              : 6;
			volatile unsigned long TS1              : 4;
			volatile unsigned long TS2              : 3;
			volatile unsigned long NC1              : 1;
			volatile unsigned long SJW              : 2;
			volatile unsigned long NC                       : 4;
			volatile unsigned long LBKM             : 1;
			volatile unsigned long SILM             : 1;
		} B;
		volatile unsigned long W;
	} BTR;
	unsigned long RESERVED0[88];
	CAN_TxMailBox_T sTxMailBox[3];
	CAN_FIFOMailBox_T sFIFOMailBox[2];
	unsigned long RESERVED1[12];
	union {
		struct {
			volatile unsigned long FINIT            : 1;
			volatile unsigned long NC                       : 31;
		} B;
		volatile unsigned long W;
	} FMR;
	union {
		struct {
			volatile unsigned long FBM0             : 1;
			volatile unsigned long FBM1             : 1;
			volatile unsigned long FBM2             : 1;
			volatile unsigned long FBM3             : 1;
			volatile unsigned long FBM4             : 1;
			volatile unsigned long FBM5             : 1;
			volatile unsigned long FBM6             : 1;
			volatile unsigned long FBM7             : 1;
			volatile unsigned long FBM8             : 1;
			volatile unsigned long FBM9             : 1;
			volatile unsigned long FBM10            : 1;
			volatile unsigned long FBM11            : 1;
			volatile unsigned long FBM12            : 1;
			volatile unsigned long FBM13            : 1;
			volatile unsigned long NC                       : 18;
		} B;
		volatile unsigned long W;
	} FM1R;
	unsigned long RESERVED2;
	union {
		struct {
			volatile unsigned long FSC0             : 1;
			volatile unsigned long FSC1             : 1;
			volatile unsigned long FSC2             : 1;
			volatile unsigned long FSC3             : 1;
			volatile unsigned long FSC4             : 1;
			volatile unsigned long FSC5             : 1;
			volatile unsigned long FSC6             : 1;
			volatile unsigned long FSC7             : 1;
			volatile unsigned long FSC8             : 1;
			volatile unsigned long FSC9             : 1;
			volatile unsigned long FSC10            : 1;
			volatile unsigned long FSC11            : 1;
			volatile unsigned long FSC12            : 1;
			volatile unsigned long FSC13            : 1;
			volatile unsigned long NC                       : 18;
		} B;
		volatile unsigned long W;
	} FS1R;
	unsigned long RESERVED3;
	union {
		struct {
			volatile unsigned long FFA0             : 1;
			volatile unsigned long FFA1             : 1;
			volatile unsigned long FFA2             : 1;
			volatile unsigned long FFA3             : 1;
			volatile unsigned long FFA4             : 1;
			volatile unsigned long FFA5             : 1;
			volatile unsigned long FFA6             : 1;
			volatile unsigned long FFA7             : 1;
			volatile unsigned long FFA8             : 1;
			volatile unsigned long FFA9             : 1;
			volatile unsigned long FFA10            : 1;
			volatile unsigned long FFA11            : 1;
			volatile unsigned long FFA12            : 1;
			volatile unsigned long FFA13            : 1;
			volatile unsigned long NC                       : 18;
		} B;
		volatile unsigned long W;
	} FFA1R;
	unsigned long RESERVED4;
	union {
		struct {
			volatile unsigned long FACT0            : 1;
			volatile unsigned long FACT1            : 1;
			volatile unsigned long FACT2            : 1;
			volatile unsigned long FACT3            : 1;
			volatile unsigned long FACT4            : 1;
			volatile unsigned long FACT5            : 1;
			volatile unsigned long FACT6            : 1;
			volatile unsigned long FACT7            : 1;
			volatile unsigned long FACT8            : 1;
			volatile unsigned long FACT9            : 1;
			volatile unsigned long FACT10           : 1;
			volatile unsigned long FACT11           : 1;
			volatile unsigned long FACT12           : 1;
			volatile unsigned long FACT13           : 1;
			volatile unsigned long NC                       : 18;
		} B;
		volatile unsigned long W;
	} FA1R;
	unsigned long RESERVED5[8];
	CAN_FilterRegister_T sFilterRegister[14];
} CAN_T;

/*------------------------ CRC calculation unit ------------------------------*/
typedef struct {
	volatile unsigned long DR;
	volatile unsigned char IDR;
	unsigned char RESERVED0;
	unsigned short RESERVED1;
	volatile unsigned long CR;
} CRC_T;


/*------------------------ Digital to Analog Converter -----------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long EN1              : 1;
			volatile unsigned long BOFF1            : 1;
			volatile unsigned long TEN1             : 1;
			volatile unsigned long TSEL1            : 3;
			volatile unsigned long WAVE1            : 2;
			volatile unsigned long MAMP1            : 4;
			volatile unsigned long DMAEN1           : 1;
			volatile unsigned long NC                       : 3;
			volatile unsigned long EN2              : 1;
			volatile unsigned long BOFF2            : 1;
			volatile unsigned long TEN2             : 1;
			volatile unsigned long TSEL2            : 3;
			volatile unsigned long WAVE2            : 2;
			volatile unsigned long MAMP2            : 4;
			volatile unsigned long DMAEN2           : 1;
			volatile unsigned long NC1              : 3;
		} B;
		volatile unsigned long W;
	} CR;
	union {
		struct {
			volatile unsigned long SWTRIG1  : 1;
			volatile unsigned long SWTRIG2  : 1;
			volatile unsigned long NC                       : 30;
		} B;
		volatile unsigned long W;
	} SWTRIGR;
	union {
		struct {
			volatile unsigned long DACC1DHR : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} DHR12R1;
	union {
		struct {
			volatile unsigned long NC                       : 4;
			volatile unsigned long DACC1DHR : 12;
			volatile unsigned long NC1              : 16;
		} B;
		volatile unsigned long W;
	} DHR12L1;
	union {
		struct {
			volatile unsigned long DACC1DHR : 8;
			volatile unsigned long NC                       : 24;
		} B;
		volatile unsigned long W;
	} DHR8R1;
	union {
		struct {
			volatile unsigned long DACC2DHR : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} DHR12R2;
	union {
		struct {
			volatile unsigned long NC                       : 4;
			volatile unsigned long DACC2DHR : 12;
			volatile unsigned long NC1              : 16;
		} B;
		volatile unsigned long W;
	} DHR12L2;
	union {
		struct {
			volatile unsigned long DACC2DHR : 8;
			volatile unsigned long NC                       : 24;
		} B;
		volatile unsigned long W;
	} DHR8R2;
	union {
		struct {
			volatile unsigned long DACC1DHR : 12;
			volatile unsigned long NC                       : 4;
			volatile unsigned long DACC2DHR : 12;
			volatile unsigned long NC1              : 4;
		} B;
		volatile unsigned long W;
	} DHR12RD;
	union {
		struct {
			volatile unsigned long NC                       : 4;
			volatile unsigned long DACC1DHR : 12;
			volatile unsigned long NC1              : 4;
			volatile unsigned long DACC2DHR : 12;
		} B;
		volatile unsigned long W;
	} DHR12LD;
	union {
		struct {
			volatile unsigned long DACC1DHR : 8;
			volatile unsigned long DACC2DHR : 8;
			volatile unsigned long NC1              : 16;
		} B;
		volatile unsigned long W;
	} DHR8RD;
	union {
		struct {
			volatile unsigned long DACC1DOR : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} DOR1;
	union {
		struct {
			volatile unsigned long DACC2DOR : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} DOR2;
} DAC_T;

/*------------------------ Debug MCU -----------------------------------------*/
typedef struct {
	volatile unsigned long IDCODE;
	volatile unsigned long CR;
}DBGMCU_T;

/*------------------------ DMA Controller ------------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long EN                       : 1;
			volatile unsigned long TCIE             : 1;
			volatile unsigned long HTIE             : 1;
			volatile unsigned long TEIE             : 1;
			volatile unsigned long DIR              : 1;
			volatile unsigned long CIRC             : 1;
			volatile unsigned long PINC             : 1;
			volatile unsigned long MINC             : 1;
			volatile unsigned long PSIZE            : 2;
			volatile unsigned long MSIZE            : 2;
			volatile unsigned long PL                       : 2;
			volatile unsigned long MEM2MEM  : 1;
			volatile unsigned long NC                       : 17;
		} B;
		volatile unsigned long W;
	} CCR;
	volatile unsigned long CNDTR;
	volatile unsigned long CPAR;
	volatile unsigned long CMAR;
} DMA_CHANNEL_T;

typedef struct {
	union {
		struct {
			volatile unsigned long GIF1             : 1;
			volatile unsigned long TCIF1            : 1;
			volatile unsigned long HTIF1            : 1;
			volatile unsigned long TEIF1            : 1;
			volatile unsigned long GIF2             : 1;
			volatile unsigned long TCIF2            : 1;
			volatile unsigned long HTIF2            : 1;
			volatile unsigned long TEIF2            : 1;
			volatile unsigned long GIF3             : 1;
			volatile unsigned long TCIF3            : 1;
			volatile unsigned long HTIF3            : 1;
			volatile unsigned long TEIF3            : 1;
			volatile unsigned long GIF4             : 1;
			volatile unsigned long TCIF4            : 1;
			volatile unsigned long HTIF4            : 1;
			volatile unsigned long TEIF4            : 1;
			volatile unsigned long GIF5             : 1;
			volatile unsigned long TCIF5            : 1;
			volatile unsigned long HTIF5            : 1;
			volatile unsigned long TEIF5            : 1;
			volatile unsigned long GIF6             : 1;
			volatile unsigned long TCIF6            : 1;
			volatile unsigned long HTIF6            : 1;
			volatile unsigned long TEIF6            : 1;
			volatile unsigned long GIF7             : 1;
			volatile unsigned long TCIF7            : 1;
			volatile unsigned long HTIF7            : 1;
			volatile unsigned long TEIF7            : 1;
			volatile unsigned long NC                       : 4;
		} B;
		volatile unsigned long W;
	} ISR;
	union {
		struct {
			volatile unsigned long CGIF1            : 1;
			volatile unsigned long CTCIF1           : 1;
			volatile unsigned long CHTIF1           : 1;
			volatile unsigned long CTEIF1           : 1;
			volatile unsigned long CGIF2            : 1;
			volatile unsigned long CTCIF2           : 1;
			volatile unsigned long CHTIF2           : 1;
			volatile unsigned long CTEIF2           : 1;
			volatile unsigned long CGIF3            : 1;
			volatile unsigned long CTCIF3           : 1;
			volatile unsigned long CHTIF3           : 1;
			volatile unsigned long CTEIF3           : 1;
			volatile unsigned long CGIF4            : 1;
			volatile unsigned long CTCIF4           : 1;
			volatile unsigned long CHTIF4           : 1;
			volatile unsigned long CTEIF4           : 1;
			volatile unsigned long CGIF5            : 1;
			volatile unsigned long CTCIF5           : 1;
			volatile unsigned long CHTIF5           : 1;
			volatile unsigned long CTEIF5           : 1;
			volatile unsigned long CGIF6            : 1;
			volatile unsigned long CTCIF6           : 1;
			volatile unsigned long CHTIF6           : 1;
			volatile unsigned long CTEIF6           : 1;
			volatile unsigned long CGIF7            : 1;
			volatile unsigned long CTCIF7           : 1;
			volatile unsigned long CHTIF7           : 1;
			volatile unsigned long CTEIF7           : 1;
			volatile unsigned long NC                       : 4;
		} B;
		volatile unsigned long W;
	} IFCR;
} DMA_T;

/*------------------------ External Interrupt/Event Controller ---------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long MR0              : 1;
			volatile unsigned long MR1              : 1;
			volatile unsigned long MR2              : 1;
			volatile unsigned long MR3              : 1;
			volatile unsigned long MR4              : 1;
			volatile unsigned long MR5              : 1;
			volatile unsigned long MR6              : 1;
			volatile unsigned long MR7              : 1;
			volatile unsigned long MR8              : 1;
			volatile unsigned long MR9              : 1;
			volatile unsigned long MR10             : 1;
			volatile unsigned long MR11             : 1;
			volatile unsigned long MR12             : 1;
			volatile unsigned long MR13             : 1;
			volatile unsigned long MR14             : 1;
			volatile unsigned long MR15             : 1;
			volatile unsigned long MR16             : 1;
			volatile unsigned long MR17             : 1;
			volatile unsigned long MR18             : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} IMR;
	union {
		struct {
			volatile unsigned long MR0              : 1;
			volatile unsigned long MR1              : 1;
			volatile unsigned long MR2              : 1;
			volatile unsigned long MR3              : 1;
			volatile unsigned long MR4              : 1;
			volatile unsigned long MR5              : 1;
			volatile unsigned long MR6              : 1;
			volatile unsigned long MR7              : 1;
			volatile unsigned long MR8              : 1;
			volatile unsigned long MR9              : 1;
			volatile unsigned long MR10             : 1;
			volatile unsigned long MR11             : 1;
			volatile unsigned long MR12             : 1;
			volatile unsigned long MR13             : 1;
			volatile unsigned long MR14             : 1;
			volatile unsigned long MR15             : 1;
			volatile unsigned long MR16             : 1;
			volatile unsigned long MR17             : 1;
			volatile unsigned long MR18             : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} EMR;
	union {
		struct {
			volatile unsigned long TR0              : 1;
			volatile unsigned long TR1              : 1;
			volatile unsigned long TR2              : 1;
			volatile unsigned long TR3              : 1;
			volatile unsigned long TR4              : 1;
			volatile unsigned long TR5              : 1;
			volatile unsigned long TR6              : 1;
			volatile unsigned long TR7              : 1;
			volatile unsigned long TR8              : 1;
			volatile unsigned long TR9              : 1;
			volatile unsigned long TR10             : 1;
			volatile unsigned long TR11             : 1;
			volatile unsigned long TR12             : 1;
			volatile unsigned long TR13             : 1;
			volatile unsigned long TR14             : 1;
			volatile unsigned long TR15             : 1;
			volatile unsigned long TR16             : 1;
			volatile unsigned long TR17             : 1;
			volatile unsigned long TR18             : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} RTSR;
	union {
		struct {
			volatile unsigned long TR0              : 1;
			volatile unsigned long TR1              : 1;
			volatile unsigned long TR2              : 1;
			volatile unsigned long TR3              : 1;
			volatile unsigned long TR4              : 1;
			volatile unsigned long TR5              : 1;
			volatile unsigned long TR6              : 1;
			volatile unsigned long TR7              : 1;
			volatile unsigned long TR8              : 1;
			volatile unsigned long TR9              : 1;
			volatile unsigned long TR10             : 1;
			volatile unsigned long TR11             : 1;
			volatile unsigned long TR12             : 1;
			volatile unsigned long TR13             : 1;
			volatile unsigned long TR14             : 1;
			volatile unsigned long TR15             : 1;
			volatile unsigned long TR16             : 1;
			volatile unsigned long TR17             : 1;
			volatile unsigned long TR18             : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} FTSR;
	union {
		struct {
			volatile unsigned long SWIER0           : 1;
			volatile unsigned long SWIER1           : 1;
			volatile unsigned long SWIER2           : 1;
			volatile unsigned long SWIER3           : 1;
			volatile unsigned long SWIER4           : 1;
			volatile unsigned long SWIER5           : 1;
			volatile unsigned long SWIER6           : 1;
			volatile unsigned long SWIER7           : 1;
			volatile unsigned long SWIER8           : 1;
			volatile unsigned long SWIER9           : 1;
			volatile unsigned long SWIER10  : 1;
			volatile unsigned long SWIER11  : 1;
			volatile unsigned long SWIER12  : 1;
			volatile unsigned long SWIER13  : 1;
			volatile unsigned long SWIER14  : 1;
			volatile unsigned long SWIER15  : 1;
			volatile unsigned long SWIER16  : 1;
			volatile unsigned long SWIER17  : 1;
			volatile unsigned long SWIER18  : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} SWIER;
	union {
		struct {
			volatile unsigned long PR0              : 1;
			volatile unsigned long PR1              : 1;
			volatile unsigned long PR2              : 1;
			volatile unsigned long PR3              : 1;
			volatile unsigned long PR4              : 1;
			volatile unsigned long PR5              : 1;
			volatile unsigned long PR6              : 1;
			volatile unsigned long PR7              : 1;
			volatile unsigned long PR8              : 1;
			volatile unsigned long PR9              : 1;
			volatile unsigned long PR10             : 1;
			volatile unsigned long PR11             : 1;
			volatile unsigned long PR12             : 1;
			volatile unsigned long PR13             : 1;
			volatile unsigned long PR14             : 1;
			volatile unsigned long PR15             : 1;
			volatile unsigned long PR16             : 1;
			volatile unsigned long PR17             : 1;
			volatile unsigned long PR18             : 1;
			volatile unsigned long NC                       : 13;
		} B;
		volatile unsigned long W;
	} PR;
} EXTI_T;

/*------------------------ FLASH and Option Bytes Registers ------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long LATENCY          : 3;
			volatile unsigned long HLFCYA           : 1;
			volatile unsigned long PRFTBE           : 1;
			volatile unsigned long PRFTBS           : 1;
			volatile unsigned long NC                       : 26;
		} B;
		volatile unsigned long W;
	} ACR;
	//volatile unsigned long ACR;	//PS
	volatile unsigned long KEYR;
	volatile unsigned long OPTKEYR;
	volatile unsigned long SR;
	volatile unsigned long CR;
	volatile unsigned long AR;
	volatile unsigned long RESERVED;
	volatile unsigned long OBR;
	volatile unsigned long WRPR;
} FLASH_T;

typedef struct {
	volatile unsigned short RDP;
	volatile unsigned short USER;
	volatile unsigned short Data0;
	volatile unsigned short Data1;
	volatile unsigned short WRP0;
	volatile unsigned short WRP1;
	volatile unsigned short WRP2;
	volatile unsigned short WRP3;
} OB_T;

/*------------------------ Flexible Static Memory Controller -----------------*/
typedef struct {
	volatile unsigned long BCR1;
	volatile unsigned long BTR1;
	volatile unsigned long BCR2;
	volatile unsigned long BTR2;
	volatile unsigned long BCR3;
	volatile unsigned long BTR3;
	volatile unsigned long BCR4;
	volatile unsigned long BTR4;
} FSMC_Bank1_T;

typedef struct {
	volatile unsigned long BWTR1;
	volatile unsigned long NC1;
	volatile unsigned long BWTR2;
	volatile unsigned long NC2;
	volatile unsigned long BWTR3;
	volatile unsigned long NC3;
	volatile unsigned long BWTR4;
	volatile unsigned long NC4;
} FSMC_Bank1E_T;

typedef struct {
	volatile unsigned long PCR2;
	volatile unsigned long SR2;
	volatile unsigned long PMEM2;
	volatile unsigned long PATT2;
	unsigned long RESERVED0;
	volatile unsigned long ECCR2;
} FSMC_Bank2_T;

typedef struct {
	volatile unsigned long PCR3;
	volatile unsigned long SR3;
	volatile unsigned long PMEM3;
	volatile unsigned long PATT3;
	unsigned long RESERVED0;
	volatile unsigned long ECCR3;
} FSMC_Bank3_T;

typedef struct {
	volatile unsigned long PCR4;
	volatile unsigned long SR4;
	volatile unsigned long PMEM4;
	volatile unsigned long PATT4;
	volatile unsigned long PIO4;
} FSMC_Bank4_T;

/*------------------------ General Purpose and Alternate Function IO ---------*/
typedef struct {
	union {
		struct {
			volatile unsigned long MODE0            : 2;
			volatile unsigned long CNF0             : 2;
			volatile unsigned long MODE1            : 2;
			volatile unsigned long CNF1             : 2;
			volatile unsigned long MODE2            : 2;
			volatile unsigned long CNF2             : 2;
			volatile unsigned long MODE3            : 2;
			volatile unsigned long CNF3             : 2;
			volatile unsigned long MODE4            : 2;
			volatile unsigned long CNF4             : 2;
			volatile unsigned long MODE5            : 2;
			volatile unsigned long CNF5             : 2;
			volatile unsigned long MODE6            : 2;
			volatile unsigned long CNF6             : 2;
			volatile unsigned long MODE7            : 2;
			volatile unsigned long CNF7             : 2;
		} B;
		volatile unsigned long W;
	} CRL;
	union {
		struct {
			volatile unsigned long MODE8            : 2;
			volatile unsigned long CNF8                     : 2;
			volatile unsigned long MODE9            : 2;
			volatile unsigned long CNF9                     : 2;
			volatile unsigned long MODE10           : 2;
			volatile unsigned long CNF10            : 2;
			volatile unsigned long MODE11           : 2;
			volatile unsigned long CNF11            : 2;
			volatile unsigned long MODE12           : 2;
			volatile unsigned long CNF12            : 2;
			volatile unsigned long MODE13           : 2;
			volatile unsigned long CNF13            : 2;
			volatile unsigned long MODE14           : 2;
			volatile unsigned long CNF14            : 2;
			volatile unsigned long MODE15           : 2;
			volatile unsigned long CNF15            : 2;
		} B;
		volatile unsigned long W;
	} CRH;
	union {
		struct {
			volatile unsigned long IO0              : 1;
			volatile unsigned long IO1              : 1;
			volatile unsigned long IO2              : 1;
			volatile unsigned long IO3              : 1;
			volatile unsigned long IO4              : 1;
			volatile unsigned long IO5              : 1;
			volatile unsigned long IO6              : 1;
			volatile unsigned long IO7              : 1;
			volatile unsigned long IO8              : 1;
			volatile unsigned long IO9              : 1;
			volatile unsigned long IO10             : 1;
			volatile unsigned long IO11             : 1;
			volatile unsigned long IO12             : 1;
			volatile unsigned long IO13             : 1;
			volatile unsigned long IO14             : 1;
			volatile unsigned long IO15             : 1;
			volatile unsigned long NC               : 16;
		} B;
		volatile unsigned long W;
	} IDR;
	union {
		struct {
			volatile unsigned long IO0              : 1;
			volatile unsigned long IO1              : 1;
			volatile unsigned long IO2              : 1;
			volatile unsigned long IO3              : 1;
			volatile unsigned long IO4              : 1;
			volatile unsigned long IO5              : 1;
			volatile unsigned long IO6              : 1;
			volatile unsigned long IO7              : 1;
			volatile unsigned long IO8              : 1;
			volatile unsigned long IO9              : 1;
			volatile unsigned long IO10             : 1;
			volatile unsigned long IO11             : 1;
			volatile unsigned long IO12             : 1;
			volatile unsigned long IO13             : 1;
			volatile unsigned long IO14             : 1;
			volatile unsigned long IO15             : 1;
			volatile unsigned long NC               : 16;
		} B;
		volatile unsigned long W;
	} ODR;
	union {
		struct {
			volatile unsigned long SETIO0           : 1;
			volatile unsigned long SETIO1           : 1;
			volatile unsigned long SETIO2           : 1;
			volatile unsigned long SETIO3           : 1;
			volatile unsigned long SETIO4           : 1;
			volatile unsigned long SETIO5           : 1;
			volatile unsigned long SETIO6           : 1;
			volatile unsigned long SETIO7           : 1;
			volatile unsigned long SETIO8           : 1;
			volatile unsigned long SETIO9           : 1;
			volatile unsigned long SETIO10          : 1;
			volatile unsigned long SETIO11          : 1;
			volatile unsigned long SETIO12          : 1;
			volatile unsigned long SETIO13          : 1;
			volatile unsigned long SETIO14          : 1;
			volatile unsigned long SETIO15          : 1;
			volatile unsigned long CLRIO0           : 1;
			volatile unsigned long CLRIO1           : 1;
			volatile unsigned long CLRIO2           : 1;
			volatile unsigned long CLRIO3           : 1;
			volatile unsigned long CLRIO4           : 1;
			volatile unsigned long CLRIO5           : 1;
			volatile unsigned long CLRIO6           : 1;
			volatile unsigned long CLRIO7           : 1;
			volatile unsigned long CLRIO8           : 1;
			volatile unsigned long CLRIO9           : 1;
			volatile unsigned long CLRIO10          : 1;
			volatile unsigned long CLRIO11          : 1;
			volatile unsigned long CLRIO12          : 1;
			volatile unsigned long CLRIO13          : 1;
			volatile unsigned long CLRIO14          : 1;
			volatile unsigned long CLRIO15          : 1;
		} B;
		volatile unsigned long W;
	} BSRR;
	union {
		struct {
			volatile unsigned long CLRIO0           : 1;
			volatile unsigned long CLRIO1           : 1;
			volatile unsigned long CLRIO2           : 1;
			volatile unsigned long CLRIO3           : 1;
			volatile unsigned long CLRIO4           : 1;
			volatile unsigned long CLRIO5           : 1;
			volatile unsigned long CLRIO6           : 1;
			volatile unsigned long CLRIO7           : 1;
			volatile unsigned long CLRIO8           : 1;
			volatile unsigned long CLRIO9           : 1;
			volatile unsigned long CLRIO10          : 1;
			volatile unsigned long CLRIO11          : 1;
			volatile unsigned long CLRIO12          : 1;
			volatile unsigned long CLRIO13          : 1;
			volatile unsigned long CLRIO14          : 1;
			volatile unsigned long CLRIO15          : 1;
			volatile unsigned long NC               : 16;
		} B;
		volatile unsigned long W;
	} BRR;
	union {
		struct {
			volatile unsigned long LCK0             : 1;
			volatile unsigned long LCK1             : 1;
			volatile unsigned long LCK2             : 1;
			volatile unsigned long LCK3             : 1;
			volatile unsigned long LCK4             : 1;
			volatile unsigned long LCK5             : 1;
			volatile unsigned long LCK6             : 1;
			volatile unsigned long LCK7             : 1;
			volatile unsigned long LCK8             : 1;
			volatile unsigned long LCK9             : 1;
			volatile unsigned long LCK10            : 1;
			volatile unsigned long LCK11            : 1;
			volatile unsigned long LCK12            : 1;
			volatile unsigned long LCK13            : 1;
			volatile unsigned long LCK14            : 1;
			volatile unsigned long LCK15            : 1;
			volatile unsigned long LCKK             : 1;
			volatile unsigned long NC               : 15;
		} B;
		volatile unsigned long W;
	} LCKR;
} GPIO_T;

typedef struct {
	union {
		struct {
			volatile unsigned long PIN              : 4;
			volatile unsigned long PORT             : 3;
			volatile unsigned long EVOE             : 1;
			volatile unsigned long NC               : 24;
		} B;
		volatile unsigned long W;
	} EVCR;
	union {
		struct {
			volatile unsigned long SPI1_REMAP                       : 1;
			volatile unsigned long I2C1_REMAP                       : 1;
			volatile unsigned long USART1_REMAP             : 1;
			volatile unsigned long USART2_REMAP             : 1;
			volatile unsigned long USART3_REMAP             : 2;
			volatile unsigned long TIM1_REMAP                       : 2;
			volatile unsigned long TIM2_REMAP                       : 2;
			volatile unsigned long TIM3_REMAP                       : 2;
			volatile unsigned long TIM4_REMAP                       : 1;
			volatile unsigned long CAN_REMAP                        : 2;
			volatile unsigned long PD01_REMAP                       : 1;
			volatile unsigned long TIM5CH4_IREMAP           : 1;
			volatile unsigned long ADC1_ETRGINJ_REMAP       : 1;
			volatile unsigned long ADC1_ETRGREG_REMAP       : 1;
			volatile unsigned long ADC2_ETRGINJ_REMAP       : 1;
			volatile unsigned long ADC2_ETRGREG_REMAP       : 1;
			volatile unsigned long NC1                              : 3;
			volatile unsigned long SWJ_CFG                  : 3;
			volatile unsigned long NC                                       : 5;
		} B;
		volatile unsigned long W;
	} MAPR;
	union {
		struct {
			volatile unsigned long EXTI0            : 4;
			volatile unsigned long EXTI1            : 4;
			volatile unsigned long EXTI2            : 4;
			volatile unsigned long EXTI3            : 4;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} EXTICR1;
	union {
		struct {
			volatile unsigned long EXTI4            : 4;
			volatile unsigned long EXTI5            : 4;
			volatile unsigned long EXTI6            : 4;
			volatile unsigned long EXTI7            : 4;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} EXTICR2;
	union {
		struct {
			volatile unsigned long EXTI8            : 4;
			volatile unsigned long EXTI9            : 4;
			volatile unsigned long EXTI10           : 4;
			volatile unsigned long EXTI11           : 4;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} EXTICR3;
	union {
		struct {
			volatile unsigned long EXTI12           : 4;
			volatile unsigned long EXTI13           : 4;
			volatile unsigned long EXTI14           : 4;
			volatile unsigned long EXTI15           : 4;
			volatile unsigned long NC               : 16;
		} B;
		volatile unsigned long W;
	} EXTICR4;
} AFIO_T;

/*------------------------ Inter-integrated Circuit Interface ----------------*/
typedef struct {
	union {
		struct {
			volatile unsigned short PE                      : 1;
			volatile unsigned short SMBUS           : 1;
			volatile unsigned short NC1             : 1;
			volatile unsigned short SMBTYPE : 1;
			volatile unsigned short ENARP           : 1;
			volatile unsigned short ENPEC           : 1;
			volatile unsigned short ENGC            : 1;
			volatile unsigned short NOSTRETCH       : 1;
			volatile unsigned short START           : 1;
			volatile unsigned short STOP            : 1;
			volatile unsigned short ACK             : 1;
			volatile unsigned short POS             : 1;
			volatile unsigned short PEC             : 1;
			volatile unsigned short ALERT           : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short SWRST           : 1;
		} B;
		volatile unsigned short W;
	} CR1;
	unsigned short RESERVED0;
	union {
		struct {
			volatile unsigned short FREQ            : 6;
			volatile unsigned short NC1             : 2;
			volatile unsigned short ITERREN : 1;
			volatile unsigned short ITEVTEN : 1;
			volatile unsigned short ITBUFEN : 1;
			volatile unsigned short DMAEN           : 1;
			volatile unsigned short LAST            : 1;
			volatile unsigned short NC                      : 3;
		} B;
		volatile unsigned short W;
	} CR2;
	unsigned short RESERVED1;
	union {
		struct {
			volatile unsigned short ADD             : 10;
			volatile unsigned short NC                      : 5;
			volatile unsigned short ADDMODE : 1;
		} B10bit;
		struct {
			volatile unsigned short NC1             : 1;
			volatile unsigned short ADD             : 7;
			volatile unsigned short NC                      : 7;
			volatile unsigned short ADDMODE : 1;
		} B7bit;
		volatile unsigned short W;
	} OAR1;
	unsigned short RESERVED2;
	union {
		struct {
			volatile unsigned short ENDUAL          : 1;
			volatile unsigned short ADD2            : 7;
			volatile unsigned short NC              : 8;
		} B;
		volatile unsigned short W;
	} OAR2;
	unsigned short RESERVED3;
	union {
		struct {
			volatile unsigned short DR                      : 8;
			volatile unsigned short NC                      : 8;
		} B;
		volatile unsigned short W;
	} DR;
	unsigned short RESERVED4;
	union {
		struct {
			volatile unsigned short SB                      : 1;
			volatile unsigned short ADDR            : 1;
			volatile unsigned short BTF             : 1;
			volatile unsigned short ADD10           : 1;
			volatile unsigned short STOPF           : 1;
			volatile unsigned short NC1             : 1;
			volatile unsigned short RXNE            : 1;
			volatile unsigned short TXE             : 1;
			volatile unsigned short BERR            : 1;
			volatile unsigned short ARLO            : 1;
			volatile unsigned short AF                      : 1;
			volatile unsigned short OVR             : 1;
			volatile unsigned short PECERR          : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short TIMEOUT : 1;
			volatile unsigned short SMBALERT        : 1;
		} B;
		volatile unsigned short W;
	} SR1;
	unsigned short RESERVED5;
	union {
		struct {
			volatile unsigned short MSL             : 1;
			volatile unsigned short BUSY            : 1;
			volatile unsigned short TRA             : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short GENCALL : 1;
			volatile unsigned short SMBDEFAULT      : 1;
			volatile unsigned short SMBHOST : 1;
			volatile unsigned short DUALF           : 1;
			volatile unsigned short PEC             : 8;
		} B;
		volatile unsigned short W;
	} SR2;
	unsigned short RESERVED6;
	union {
		struct {
			volatile unsigned short CCR             : 12;
			volatile unsigned short NC                      : 2;
			volatile unsigned short DUTY            : 1;
			volatile unsigned short F_S             : 1;
		} B;
		volatile unsigned short W;
	} CCR;
	unsigned short RESERVED7;
	union {
		struct {
			volatile unsigned short TRISE           : 6;
			volatile unsigned short NC                      : 10;
		} B;
		volatile unsigned short W;
	} TRISE;
	unsigned short RESERVED8;
} I2C_T;

/*------------------------ Independent WATCHDOG ------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long KEY              : 16;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} KR;
	union {
		struct {
			volatile unsigned long PR                       : 3;
			volatile unsigned long NC                       : 29;
		} B;
		volatile unsigned long W;
	} PR;
	union {
		struct {
			volatile unsigned long RL                       : 12;
			volatile unsigned long NC                       : 20;
		} B;
		volatile unsigned long W;
	} RLR;
	union {
		struct {
			volatile unsigned long PVU              : 1;
			volatile unsigned long RVU              : 1;
			volatile unsigned long NC                       : 30;
		} B;
		volatile unsigned long W;
	} SR;
} IWDG_T;

/*------------------------ Nested Vectored Interrupt Controller --------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long WWDG             : 1;
			volatile unsigned long PVD              : 1;
			volatile unsigned long TAMPER           : 1;
			volatile unsigned long RTC              : 1;
			volatile unsigned long FLASH            : 1;
			volatile unsigned long RCC              : 1;
			volatile unsigned long EXTI0            : 1;
			volatile unsigned long EXTI1            : 1;
			volatile unsigned long EXTI2            : 1;
			volatile unsigned long EXTI3            : 1;
			volatile unsigned long EXTI4            : 1;
			volatile unsigned long DMA1_CH1 : 1;
			volatile unsigned long DMA1_CH2 : 1;
			volatile unsigned long DMA1_CH3 : 1;
			volatile unsigned long DMA1_CH4 : 1;
			volatile unsigned long DMA1_CH5 : 1;
			volatile unsigned long DMA1_CH6 : 1;
			volatile unsigned long DMA1_CH7 : 1;
			volatile unsigned long ADC1_2           : 1;
			volatile unsigned long USB_HP_CAN_TX    : 1;
			volatile unsigned long USB_LP_CAN_RX0   : 1;
			volatile unsigned long CAN_RX1  : 1;
			volatile unsigned long CAN_SCE  : 1;
			volatile unsigned long EXTI9_5  : 1;
			volatile unsigned long TIM1_BRK : 1;
			volatile unsigned long TIM1_UP  : 1;
			volatile unsigned long TIM1_TRG_COM     : 1;
			volatile unsigned long TIM1_CC  : 1;
			volatile unsigned long TIM2             : 1;
			volatile unsigned long TIM3             : 1;
			volatile unsigned long TIM4             : 1;
			volatile unsigned long I2C1_EV  : 1;
		} B;
		volatile unsigned long W;
	} ISER1;
	union {
		struct {
			volatile unsigned long I2C1_ER  : 1;
			volatile unsigned long I2C2_EV  : 1;
			volatile unsigned long I2C2_ER  : 1;
			volatile unsigned long SPI1             : 1;
			volatile unsigned long SPI2             : 1;
			volatile unsigned long USART1_  : 1;
			volatile unsigned long USART2_  : 1;
			volatile unsigned long USART3_  : 1;
			volatile unsigned long EXTI15_10 : 1;
			volatile unsigned long RTCAlarm : 1;
			volatile unsigned long USBWakeUp : 1;
			volatile unsigned long TIM8_BRK : 1;
			volatile unsigned long TIM8_UP  : 1;
			volatile unsigned long TIM8_TRG_COM     : 1;
			volatile unsigned long TIM8_CC  : 1;
			volatile unsigned long ADC3             : 1;
			volatile unsigned long FSMC             : 1;
			volatile unsigned long SDIO             : 1;
			volatile unsigned long TIM5             : 1;
			volatile unsigned long SPI3             : 1;
			volatile unsigned long UART4            : 1;
			volatile unsigned long UART5            : 1;
			volatile unsigned long TIM6             : 1;
			volatile unsigned long TIM7             : 1;
			volatile unsigned long DMA2_CH1 : 1;
			volatile unsigned long DMA2_CH2 : 1;
			volatile unsigned long DMA2_CH3 : 1;
			volatile unsigned long DMA2_CH4_5       : 1;
			volatile unsigned long SETENA60 : 1;
			volatile unsigned long SETENA61 : 1;
			volatile unsigned long SETENA62 : 1;
			volatile unsigned long SETENA63 : 1;
		} B;
		volatile unsigned long W;
	} ISER2;
	unsigned long RESERVED0[30];
	union {
		struct {
			volatile unsigned long WWDG             : 1;
			volatile unsigned long PVD              : 1;
			volatile unsigned long TAMPER           : 1;
			volatile unsigned long RTC              : 1;
			volatile unsigned long FLASH            : 1;
			volatile unsigned long RCC              : 1;
			volatile unsigned long EXTI0            : 1;
			volatile unsigned long EXTI1            : 1;
			volatile unsigned long EXTI2            : 1;
			volatile unsigned long EXTI3            : 1;
			volatile unsigned long EXTI4            : 1;
			volatile unsigned long DMA1_CH1 : 1;
			volatile unsigned long DMA1_CH2 : 1;
			volatile unsigned long DMA1_CH3 : 1;
			volatile unsigned long DMA1_CH4 : 1;
			volatile unsigned long DMA1_CH5 : 1;
			volatile unsigned long DMA1_CH6 : 1;
			volatile unsigned long DMA1_CH7 : 1;
			volatile unsigned long ADC1_2           : 1;
			volatile unsigned long USB_HP_CAN_TX    : 1;
			volatile unsigned long USB_LP_CAN_RX0   : 1;
			volatile unsigned long CAN_RX1  : 1;
			volatile unsigned long CAN_SCE  : 1;
			volatile unsigned long EXTI9_5  : 1;
			volatile unsigned long TIM1_BRK : 1;
			volatile unsigned long TIM1_UP  : 1;
			volatile unsigned long TIM1_TRG_COM     : 1;
			volatile unsigned long TIM1_CC  : 1;
			volatile unsigned long TIM2             : 1;
			volatile unsigned long TIM3             : 1;
			volatile unsigned long TIM4             : 1;
			volatile unsigned long I2C1_EV  : 1;
		} B;
		volatile unsigned long W;
	} ICER1;
	union {
		struct {
			volatile unsigned long I2C1_ER  : 1;
			volatile unsigned long I2C2_EV  : 1;
			volatile unsigned long I2C2_ER  : 1;
			volatile unsigned long SPI1             : 1;
			volatile unsigned long SPI2             : 1;
			volatile unsigned long USART1           : 1;
			volatile unsigned long USART2           : 1;
			volatile unsigned long USART3           : 1;
			volatile unsigned long EXTI15_10        : 1;
			volatile unsigned long RTCAlarm : 1;
			volatile unsigned long USBWakeUp        : 1;
			volatile unsigned long TIM8_BRK : 1;
			volatile unsigned long TIM8_UP  : 1;
			volatile unsigned long TIM8_TRG_COM     : 1;
			volatile unsigned long TIM8_CC  : 1;
			volatile unsigned long ADC3             : 1;
			volatile unsigned long FSMC             : 1;
			volatile unsigned long SDIO             : 1;
			volatile unsigned long TIM5             : 1;
			volatile unsigned long SPI3             : 1;
			volatile unsigned long UART4            : 1;
			volatile unsigned long UART5            : 1;
			volatile unsigned long TIM6             : 1;
			volatile unsigned long TIM7             : 1;
			volatile unsigned long DMA2_CH1 : 1;
			volatile unsigned long DMA2_CH2 : 1;
			volatile unsigned long DMA2_CH3 : 1;
			volatile unsigned long DMA2_CH4_5       : 1;
			volatile unsigned long SETENA60 : 1;
			volatile unsigned long SETENA61 : 1;
			volatile unsigned long SETENA62 : 1;
			volatile unsigned long SETENA63 : 1;
		} B;
		volatile unsigned long W;
	} ICER2;
	unsigned long RSERVED1[30];
	union {
		struct {
			volatile unsigned long WWDG             : 1;
			volatile unsigned long PVD              : 1;
			volatile unsigned long TAMPER           : 1;
			volatile unsigned long RTC              : 1;
			volatile unsigned long FLASH            : 1;
			volatile unsigned long RCC              : 1;
			volatile unsigned long EXTI0            : 1;
			volatile unsigned long EXTI1            : 1;
			volatile unsigned long EXTI2            : 1;
			volatile unsigned long EXTI3            : 1;
			volatile unsigned long EXTI4            : 1;
			volatile unsigned long DMA1_CH1 : 1;
			volatile unsigned long DMA1_CH2 : 1;
			volatile unsigned long DMA1_CH3 : 1;
			volatile unsigned long DMA1_CH4 : 1;
			volatile unsigned long DMA1_CH5 : 1;
			volatile unsigned long DMA1_CH6 : 1;
			volatile unsigned long DMA1_CH7 : 1;
			volatile unsigned long ADC1_2           : 1;
			volatile unsigned long USB_HP_CAN_TX    : 1;
			volatile unsigned long USB_LP_CAN_RX0   : 1;
			volatile unsigned long CAN_RX1  : 1;
			volatile unsigned long CAN_SCE  : 1;
			volatile unsigned long EXTI9_5  : 1;
			volatile unsigned long TIM1_BRK : 1;
			volatile unsigned long TIM1_UP  : 1;
			volatile unsigned long TIM1_TRG_COM     : 1;
			volatile unsigned long TIM1_CC  : 1;
			volatile unsigned long TIM2             : 1;
			volatile unsigned long TIM3             : 1;
			volatile unsigned long TIM4             : 1;
			volatile unsigned long I2C1_EV  : 1;
		} B;
		volatile unsigned long W;
	} ISPR1;
	union {
		struct {
			volatile unsigned long I2C1_ER  : 1;
			volatile unsigned long I2C2_EV  : 1;
			volatile unsigned long I2C2_ER  : 1;
			volatile unsigned long SPI1             : 1;
			volatile unsigned long SPI2             : 1;
			volatile unsigned long USART1           : 1;
			volatile unsigned long USART2           : 1;
			volatile unsigned long USART3           : 1;
			volatile unsigned long EXTI15_10        : 1;
			volatile unsigned long RTCAlarm : 1;
			volatile unsigned long USBWakeUp        : 1;
			volatile unsigned long TIM8_BRK : 1;
			volatile unsigned long TIM8_UP  : 1;
			volatile unsigned long TIM8_TRG_COM     : 1;
			volatile unsigned long TIM8_CC  : 1;
			volatile unsigned long ADC3             : 1;
			volatile unsigned long FSMC             : 1;
			volatile unsigned long SDIO             : 1;
			volatile unsigned long TIM5             : 1;
			volatile unsigned long SPI3             : 1;
			volatile unsigned long UART4            : 1;
			volatile unsigned long UART5            : 1;
			volatile unsigned long TIM6             : 1;
			volatile unsigned long TIM7             : 1;
			volatile unsigned long DMA2_CH1 : 1;
			volatile unsigned long DMA2_CH2 : 1;
			volatile unsigned long DMA2_CH3 : 1;
			volatile unsigned long DMA2_CH4_5       : 1;
			volatile unsigned long SETENA60 : 1;
			volatile unsigned long SETENA61 : 1;
			volatile unsigned long SETENA62 : 1;
			volatile unsigned long SETENA63 : 1;
		} B;
		volatile unsigned long W;
	} ISPR2;
	unsigned long RESERVED2[30];
	union {
		struct {
			volatile unsigned long WWDG             : 1;
			volatile unsigned long PVD              : 1;
			volatile unsigned long TAMPER           : 1;
			volatile unsigned long RTC              : 1;
			volatile unsigned long FLASH            : 1;
			volatile unsigned long RCC              : 1;
			volatile unsigned long EXTI0            : 1;
			volatile unsigned long EXTI1            : 1;
			volatile unsigned long EXTI2            : 1;
			volatile unsigned long EXTI3            : 1;
			volatile unsigned long EXTI4            : 1;
			volatile unsigned long DMA1_CH1 : 1;
			volatile unsigned long DMA1_CH2 : 1;
			volatile unsigned long DMA1_CH3 : 1;
			volatile unsigned long DMA1_CH4 : 1;
			volatile unsigned long DMA1_CH5 : 1;
			volatile unsigned long DMA1_CH6 : 1;
			volatile unsigned long DMA1_CH7 : 1;
			volatile unsigned long ADC1_2           : 1;
			volatile unsigned long USB_HP_CAN_TX    : 1;
			volatile unsigned long USB_LP_CAN_RX0   : 1;
			volatile unsigned long CAN_RX1  : 1;
			volatile unsigned long CAN_SCE  : 1;
			volatile unsigned long EXTI9_5  : 1;
			volatile unsigned long TIM1_BRK : 1;
			volatile unsigned long TIM1_UP  : 1;
			volatile unsigned long TIM1_TRG_COM     : 1;
			volatile unsigned long TIM1_CC  : 1;
			volatile unsigned long TIM2             : 1;
			volatile unsigned long TIM3             : 1;
			volatile unsigned long TIM4             : 1;
			volatile unsigned long I2C1_EV  : 1;
		} B;
		volatile unsigned long W;
	} ICPR1;
	union {
		struct {
			volatile unsigned long I2C1_ER  : 1;
			volatile unsigned long I2C2_EV  : 1;
			volatile unsigned long I2C2_ER  : 1;
			volatile unsigned long SPI1             : 1;
			volatile unsigned long SPI2             : 1;
			volatile unsigned long USART1           : 1;
			volatile unsigned long USART2           : 1;
			volatile unsigned long USART3           : 1;
			volatile unsigned long EXTI15_10        : 1;
			volatile unsigned long RTCAlarm : 1;
			volatile unsigned long USBWakeUp        : 1;
			volatile unsigned long TIM8_BRK : 1;
			volatile unsigned long TIM8_UP  : 1;
			volatile unsigned long TIM8_TRG_COM     : 1;
			volatile unsigned long TIM8_CC  : 1;
			volatile unsigned long ADC3             : 1;
			volatile unsigned long FSMC             : 1;
			volatile unsigned long SDIO             : 1;
			volatile unsigned long TIM5             : 1;
			volatile unsigned long SPI3             : 1;
			volatile unsigned long UART4            : 1;
			volatile unsigned long UART5            : 1;
			volatile unsigned long TIM6             : 1;
			volatile unsigned long TIM7             : 1;
			volatile unsigned long DMA2_CH1 : 1;
			volatile unsigned long DMA2_CH2 : 1;
			volatile unsigned long DMA2_CH3 : 1;
			volatile unsigned long DMA2_CH4_5       : 1;
			volatile unsigned long SETENA60 : 1;
			volatile unsigned long SETENA61 : 1;
			volatile unsigned long SETENA62 : 1;
			volatile unsigned long SETENA63 : 1;
		} B;
		volatile unsigned long W;
	} ICPR2;
	unsigned long RESERVED3[30];
	union {
		struct {
			volatile unsigned long WWDG             : 1;
			volatile unsigned long PVD              : 1;
			volatile unsigned long TAMPER           : 1;
			volatile unsigned long RTC              : 1;
			volatile unsigned long FLASH            : 1;
			volatile unsigned long RCC              : 1;
			volatile unsigned long EXTI0            : 1;
			volatile unsigned long EXTI1            : 1;
			volatile unsigned long EXTI2            : 1;
			volatile unsigned long EXTI3            : 1;
			volatile unsigned long EXTI4            : 1;
			volatile unsigned long DMA1_CH1 : 1;
			volatile unsigned long DMA1_CH2 : 1;
			volatile unsigned long DMA1_CH3 : 1;
			volatile unsigned long DMA1_CH4 : 1;
			volatile unsigned long DMA1_CH5 : 1;
			volatile unsigned long DMA1_CH6 : 1;
			volatile unsigned long DMA1_CH7 : 1;
			volatile unsigned long ADC1_2           : 1;
			volatile unsigned long USB_HP_CAN_TX    : 1;
			volatile unsigned long USB_LP_CAN_RX0   : 1;
			volatile unsigned long CAN_RX1  : 1;
			volatile unsigned long CAN_SCE  : 1;
			volatile unsigned long EXTI9_5  : 1;
			volatile unsigned long TIM1_BRK : 1;
			volatile unsigned long TIM1_UP  : 1;
			volatile unsigned long TIM1_TRG_COM     : 1;
			volatile unsigned long TIM1_CC  : 1;
			volatile unsigned long TIM2             : 1;
			volatile unsigned long TIM3             : 1;
			volatile unsigned long TIM4             : 1;
			volatile unsigned long I2C1_EV  : 1;
		} B;
		volatile unsigned long W;
	} IABR1;
	union {
		struct {
			volatile unsigned long I2C1_ER  : 1;
			volatile unsigned long I2C2_EV  : 1;
			volatile unsigned long I2C2_ER  : 1;
			volatile unsigned long SPI1             : 1;
			volatile unsigned long SPI2             : 1;
			volatile unsigned long USART1           : 1;
			volatile unsigned long USART2           : 1;
			volatile unsigned long USART3           : 1;
			volatile unsigned long EXTI15_10        : 1;
			volatile unsigned long RTCAlarm : 1;
			volatile unsigned long USBWakeUp        : 1;
			volatile unsigned long TIM8_BRK : 1;
			volatile unsigned long TIM8_UP  : 1;
			volatile unsigned long TIM8_TRG_COM     : 1;
			volatile unsigned long TIM8_CC  : 1;
			volatile unsigned long ADC3             : 1;
			volatile unsigned long FSMC             : 1;
			volatile unsigned long SDIO             : 1;
			volatile unsigned long TIM5             : 1;
			volatile unsigned long SPI3             : 1;
			volatile unsigned long UART4            : 1;
			volatile unsigned long UART5            : 1;
			volatile unsigned long TIM6             : 1;
			volatile unsigned long TIM7             : 1;
			volatile unsigned long DMA2_CH1 : 1;
			volatile unsigned long DMA2_CH2 : 1;
			volatile unsigned long DMA2_CH3 : 1;
			volatile unsigned long DMA2_CH4_5       : 1;
			volatile unsigned long SETENA60 : 1;
			volatile unsigned long SETENA61 : 1;
			volatile unsigned long SETENA62 : 1;
			volatile unsigned long SETENA63 : 1;
		} B;
		volatile unsigned long W;
	} IABR2;
	unsigned long RESERVED4[62];
	union {
		struct {
			volatile unsigned long WWDG             : 8;
			volatile unsigned long PVD              : 8;
			volatile unsigned long TAMPER           : 8;
			volatile unsigned long RTC              : 8;
		} B;
		volatile unsigned long W;
	} IPR1;
	union {
		struct {
			volatile unsigned long FLASH            : 8;
			volatile unsigned long RCC              : 8;
			volatile unsigned long EXTI0            : 8;
			volatile unsigned long EXTI1            : 8;
		} B;
		volatile unsigned long W;
	} IPR2;
	union {
		struct {
			volatile unsigned long EXTI2            : 8;
			volatile unsigned long EXTI3            : 8;
			volatile unsigned long EXTI4            : 8;
			volatile unsigned long DMA1_CH1 : 8;
		} B;
		volatile unsigned long W;
	} IPR3;
	union {
		struct {
			volatile unsigned long DMA1_CH2 : 8;
			volatile unsigned long DMA1_CH3 : 8;
			volatile unsigned long DMA1_CH4 : 8;
			volatile unsigned long DMA1_CH5 : 8;
		} B;
		volatile unsigned long W;
	} IPR4;
	union {
		struct {
			volatile unsigned long DMA1_CH6 : 8;
			volatile unsigned long DMA1_CH7 : 8;
			volatile unsigned long ADC1_2           : 8;
			volatile unsigned long USB_HP_CAN_TX    : 8;
		} B;
		volatile unsigned long W;
	} IPR5;
	union {
		struct {
			volatile unsigned long USB_LP_CAN_RX0   : 8;
			volatile unsigned long CAN_RX1  : 8;
			volatile unsigned long CAN_SCE  : 8;
			volatile unsigned long EXTI9_5  : 8;
		} B;
		volatile unsigned long W;
	} IPR6;
	union {
		struct {
			volatile unsigned long TIM1_BRK : 8;
			volatile unsigned long TIM1_UP  : 8;
			volatile unsigned long TIM1_TRG_COM     : 8;
			volatile unsigned long TIM1_CC  : 8;
		} B;
		volatile unsigned long W;
	} IPR7;
	union {
		struct {
			volatile unsigned long TIM2             : 8;
			volatile unsigned long TIM3             : 8;
			volatile unsigned long TIM4             : 8;
			volatile unsigned long I2C1_EV  : 8;
		} B;
		volatile unsigned long W;
	} IPR8;

	union {
		struct {
			volatile unsigned long I2C1_ER  : 8;
			volatile unsigned long I2C2_EV  : 8;
			volatile unsigned long I2C2_ER  : 8;
			volatile unsigned long SPI1             : 8;
		} B;
		volatile unsigned long W;
	} IPR9;
	union {
		struct {
			volatile unsigned long SPI2             : 8;
			volatile unsigned long USART1           : 8;
			volatile unsigned long USART2           : 8;
			volatile unsigned long USART3           : 8;
		} B;
		volatile unsigned long W;
	} IPR10;
	union {
		struct {
			volatile unsigned long EXTI15_10        : 8;
			volatile unsigned long RTCAlarm : 8;
			volatile unsigned long USBWakeUp        : 8;
			volatile unsigned long TIM8_BRK : 8;
		} B;
		volatile unsigned long W;
	} IPR11;
	union {
		struct {
			volatile unsigned long TIM8_UP  : 8;
			volatile unsigned long TIM8_TRG_COM     : 8;
			volatile unsigned long TIM8_CC  : 8;
			volatile unsigned long ADC3             : 8;
		} B;
		volatile unsigned long W;
	} IPR12;
	union {
		struct {
			volatile unsigned long FSMC             : 8;
			volatile unsigned long SDIO             : 8;
			volatile unsigned long TIM5             : 8;
			volatile unsigned long SPI3             : 8;
		} B;
		volatile unsigned long W;
	} IPR13;
	union {
		struct {
			volatile unsigned long UART4            : 8;
			volatile unsigned long UART5            : 8;
			volatile unsigned long TIM6             : 8;
			volatile unsigned long TIM7             : 8;
		} B;
		volatile unsigned long W;
	} IPR14;
	union {
		struct {
			volatile unsigned long DMA2_CH1 : 8;
			volatile unsigned long DMA2_CH2 : 8;
			volatile unsigned long DMA2_CH3 : 8;
			volatile unsigned long DMA2_CH4_5       : 8;
		} B;
		volatile unsigned long W;
	} IPR15;
} NVIC_T;

typedef struct {
	union {
		struct {
			volatile unsigned long REVISION : 4;
			volatile unsigned long PARTNO           : 12;
			volatile unsigned long CONST            : 4;
			volatile unsigned long VARIANT  : 4;
			volatile unsigned long IMPLEMENTER      : 8;
		} B;
		volatile unsigned long W;
	} CPUID;
	union {
		struct {
			volatile unsigned long VECTACTIVE               : 9;
			volatile unsigned long NC                               : 2;
			volatile unsigned long RETTOBASE                : 1;
			volatile unsigned long VECTPENDING      : 10;
			volatile unsigned long ISRPENDING               : 1;
			volatile unsigned long ISRPREEMPT               : 1;
			volatile unsigned long NC1                      : 1;
			volatile unsigned long PENDSTCLR                : 1;
			volatile unsigned long PENDSTSET                : 1;
			volatile unsigned long PENDSVCLR                : 1;
			volatile unsigned long PENDSVSET                : 1;
			volatile unsigned long NC2                      : 2;
			volatile unsigned long NMIPENDSET               : 1;
		} B;
		volatile unsigned long W;
	} ICSR;
	union {
		struct {
			volatile unsigned long NC                               : 7;
			volatile unsigned long TBLOFF                   : 22;
			volatile unsigned long TBLBASE          : 1;
			volatile unsigned long NC1                      : 2;
		} B;
		volatile unsigned long W;
	} VTOR;
	union {
		struct {
			volatile unsigned long VECTRESET                : 1;
			volatile unsigned long VECTCLRACTIVE    : 1;
			volatile unsigned long SYSRESETREQ      : 1;
			volatile unsigned long NC                               : 5;
			volatile unsigned long PRIGROUP         : 3;
			volatile unsigned long NC1                      : 4;
			volatile unsigned long ENDIANESS                : 1;
			volatile unsigned long VECTKEY          : 16;
		} B;
		volatile unsigned long W;
	} AIRCR;
	union {
		struct {
			volatile unsigned long NC                               : 1;
			volatile unsigned long SLEEPONEXIT      : 1;
			volatile unsigned long SLEEPDEEP                : 1;
			volatile unsigned long NC1                      : 1;
			volatile unsigned long SEVONPEND                : 1;
			volatile unsigned long NC2                      : 27;
		} B;
		volatile unsigned long W;
	} SCR;
	union {
		struct {
			volatile unsigned long NONEBASETHRDENA  : 1;
			volatile unsigned long USERSETMPEND             : 1;
			volatile unsigned long NC                                       : 1;
			volatile unsigned long UNALIGN_TRP              : 1;
			volatile unsigned long DIV_0_TRP                        : 1;
			volatile unsigned long NC1                              : 3;
			volatile unsigned long BFHFNMIGN                        : 1;
			volatile unsigned long STKALIGN                 : 1;
			volatile unsigned long NC2                              : 22;
		} B;
		volatile unsigned long W;
	} CCR;


	union {
		struct {
			volatile unsigned long MemManage        : 8;
			volatile unsigned long BusFault : 8;
			volatile unsigned long UsageFault       : 8;
			volatile unsigned long RS                       : 8;
		} B;
		volatile unsigned long W;
	} SHPR1;
	union {
		struct {
			volatile unsigned long RS                       : 8;
			volatile unsigned long RS1              : 8;
			volatile unsigned long RS2              : 8;
			volatile unsigned long SVCall           : 8;
		} B;
		volatile unsigned long W;
	} SHPR2;
	union {
		struct {
			volatile unsigned long Debug            : 8;
			volatile unsigned long RS                       : 8;
			volatile unsigned long PendSV           : 8;
			volatile unsigned long SYSTICK  : 8;
		} B;
		volatile unsigned long W;
	} SHPR3;

	union {
		struct {
			volatile unsigned long MEMFAULTACT      : 1;
			volatile unsigned long BUSFAULTACT      : 1;
			volatile unsigned long NC                               : 1;
			volatile unsigned long USGFAULTACT      : 1;
			volatile unsigned long NC1                      : 3;
			volatile unsigned long SVCALLACT                : 1;
			volatile unsigned long MONITORACT               : 1;
			volatile unsigned long NC2                      : 1;
			volatile unsigned long PENDSVACT                : 1;
			volatile unsigned long SYSTICKACT               : 1;
			volatile unsigned long USGFAULTPENDED   : 1;
			volatile unsigned long MEMFAULTPENDED   : 1;
			volatile unsigned long BUSFAULTPENDED   : 1;
			volatile unsigned long SVCALLPENDED     : 1;
			volatile unsigned long MEMFAULTENA      : 1;
			volatile unsigned long BUSFAULTENA      : 1;
			volatile unsigned long USGFAULTENA      : 1;
			volatile unsigned long NC3                      : 13;
		} B;
		volatile unsigned long W;
	} SHCSR;
	union {
		struct {
			volatile unsigned long IACCVIOL         : 1;
			volatile unsigned long DACCVIOL         : 1;
			volatile unsigned long NC                               : 1;
			volatile unsigned long MUNSTKERR                : 1;
			volatile unsigned long MSTKERR          : 1;
			volatile unsigned long NC1                      : 2;
			volatile unsigned long MMARVALID                : 1;

			volatile unsigned long IBUSERR          : 1;
			volatile unsigned long PRECISERR                : 1;
			volatile unsigned long IMPRECISERR      : 1;
			volatile unsigned long UNSTKERR         : 1;
			volatile unsigned long STKERR                   : 1;
			volatile unsigned long NC2                      : 2;
			volatile unsigned long BFARVALID                : 1;

			volatile unsigned long UNDEFINSTR               : 1;
			volatile unsigned long INVSTATE         : 1;
			volatile unsigned long INVPC                    : 1;
			volatile unsigned long NOCP                     : 1;
			volatile unsigned long NC3                      : 4;
			volatile unsigned long UNALIGNED                : 1;
			volatile unsigned long DIVBYZERO                : 1;
			volatile unsigned long NC4                      : 6;
		} B;
		volatile unsigned long W;
	} CFSR;
	union {
		struct {
			volatile unsigned long NC                               : 1;
			volatile unsigned long VECTTBL          : 1;
			volatile unsigned long NC1                      : 28;
			volatile unsigned long FORCED                   : 1;
			volatile unsigned long DEBUGEVT         : 1;
		} B;
		volatile unsigned long W;
	} HFSR;
	union {
		struct {
			volatile unsigned long HALTED                   : 1;
			volatile unsigned long BKPT                     : 1;
			volatile unsigned long DWTTRAP          : 1;
			volatile unsigned long VCATCH                   : 1;
			volatile unsigned long EXTERNAL         : 1;
			volatile unsigned long NC                               : 27;
		} B;
		volatile unsigned long W;
	} DFSR;
	volatile unsigned long MMFAR;
	volatile unsigned long BFAR;
	volatile unsigned long AFSR;
} SCB_T;

/*------------------------ Power Control -------------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long LPDS             : 1;
			volatile unsigned long PDDS             : 1;
			volatile unsigned long CWUF             : 1;
			volatile unsigned long CSBF             : 1;
			volatile unsigned long PVDE             : 1;
			volatile unsigned long PLS              : 3;
			volatile unsigned long DBP              : 1;
			volatile unsigned long NC                       : 23;
		} B;
		volatile unsigned long W;
	} CR;
	union {
		struct {
			volatile unsigned long WUF              : 1;
			volatile unsigned long SBF              : 1;
			volatile unsigned long PVDO             : 1;
			volatile unsigned long NC1              : 5;
			volatile unsigned long EWUP             : 1;
			volatile unsigned long NC                       : 23;
		} B;
		volatile unsigned long W;
	} CSR;
} PWR_T;

/*------------------------ Reset and Clock Control ---------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long HSION            : 1;
			volatile unsigned long HSIRDY           : 1;
			volatile unsigned long NC2              : 1;
			volatile unsigned long HSITRIM  : 5;
			volatile unsigned long HSICAL           : 8;
			volatile unsigned long HSEON            : 1;
			volatile unsigned long HSERDY           : 1;
			volatile unsigned long HSEBYP           : 1;
			volatile unsigned long CSSON            : 1;
			volatile unsigned long NC1              : 4;
			volatile unsigned long PLLON            : 1;
			volatile unsigned long PLLRDY           : 1;
			volatile unsigned long NC                       : 6;
		} B;
		volatile unsigned long W;
	} CR;
	union {
		struct {
			volatile unsigned long SW                       : 2;
			volatile unsigned long SWS              : 2;
			volatile unsigned long HPRE             : 4;
			volatile unsigned long PPRE1            : 3;
			volatile unsigned long PPRE2            : 3;
			volatile unsigned long ADCPRE           : 2;
			volatile unsigned long PLLSRC           : 1;
			volatile unsigned long PLLXTPRE : 1;
			volatile unsigned long PLLMUL           : 4;
			volatile unsigned long USBPRE           : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long MCO              : 3;
			volatile unsigned long NC                       : 5;
		} B;
		volatile unsigned long W;
	} CFGR;
	union {
		struct {
			volatile unsigned long LSIRDYF  : 1;
			volatile unsigned long LSERDYF  : 1;
			volatile unsigned long HSIRDYF  : 1;
			volatile unsigned long HSERDYF  : 1;
			volatile unsigned long PLLRDYF  : 1;
			volatile unsigned long NC3              : 2;
			volatile unsigned long CSSF             : 1;
			volatile unsigned long LSIRDYIE : 1;
			volatile unsigned long LSERDYIE : 1;
			volatile unsigned long HSIRDYIE : 1;
			volatile unsigned long HSERDYIE : 1;
			volatile unsigned long PLLRDYIE : 1;
			volatile unsigned long NC2              : 3;
			volatile unsigned long LSIRDYC  : 1;
			volatile unsigned long LSERDYC  : 1;
			volatile unsigned long HSIRDYC  : 1;
			volatile unsigned long HSERDYC  : 1;
			volatile unsigned long PLLRDYC  : 1;
			volatile unsigned long NC1              : 2;
			volatile unsigned long CSSC             : 1;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} CIR;
	union {
		struct {
			volatile unsigned long AFIORST  : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long IOPARST  : 1;
			volatile unsigned long IOPBRST  : 1;
			volatile unsigned long IOPCRST  : 1;
			volatile unsigned long IOPDRST  : 1;
			volatile unsigned long IOPERST  : 1;
			volatile unsigned long IOPFRST  : 1;
			volatile unsigned long IOPGRST  : 1;
			volatile unsigned long ADC1RST  : 1;
			volatile unsigned long ADC2RST  : 1;
			volatile unsigned long TIM1RST  : 1;
			volatile unsigned long SPI1RST  : 1;
			volatile unsigned long TIM8RST  : 1;
			volatile unsigned long USART1RST        : 1;
			volatile unsigned long ADC3RST  : 1;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} APB2RSTR;
	union {
		struct {
			volatile unsigned long TIM2RST  : 1;
			volatile unsigned long TIM3RST  : 1;
			volatile unsigned long TIM4RST  : 1;
			volatile unsigned long TIM5RST  : 1;
			volatile unsigned long TIM6RST  : 1;
			volatile unsigned long TIM7RST  : 1;
			volatile unsigned long NC5              : 5;
			volatile unsigned long WWGDRST  : 1;
			volatile unsigned long NC4              : 2;
			volatile unsigned long SPI2RST  : 1;
			volatile unsigned long SPI3RST  : 1;
			volatile unsigned long NC3              : 1;
			volatile unsigned long USART2RST        : 1;
			volatile unsigned long USART3RST        : 1;
			volatile unsigned long USART4RST        : 1;
			volatile unsigned long USART5RST        : 1;
			volatile unsigned long I2C1RST  : 1;
			volatile unsigned long I2C2RST  : 1;
			volatile unsigned long USBRST           : 1;
			volatile unsigned long NC2              : 1;
			volatile unsigned long CANRST           : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long BKPRST           : 1;
			volatile unsigned long PWRRST           : 1;
			volatile unsigned long DACRST           : 1;
			volatile unsigned long NC                       : 2;
		} B;
		volatile unsigned long W;
	} APB1RSTR;
	union {
		struct {
			volatile unsigned long DMA1EN           : 1;
			volatile unsigned long DMA2EN           : 1;
			volatile unsigned long SRAMEN           : 1;
			volatile unsigned long NC4              : 1;
			volatile unsigned long FLITFEN  : 1;
			volatile unsigned long NC3              : 1;
			volatile unsigned long CRCEN            : 1;
			volatile unsigned long NC2              : 1;
			volatile unsigned long FSMCEN           : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long SDIOEN           : 1;
			volatile unsigned long NC                       : 21;
		} B;
		volatile unsigned long W;
	} AHBENR;
	union {
		struct {
			volatile unsigned long AFIOEN           : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long IOPAEN           : 1;
			volatile unsigned long IOPBEN           : 1;
			volatile unsigned long IOPCEN           : 1;
			volatile unsigned long IOPDEN           : 1;
			volatile unsigned long IOPEEN           : 1;
			volatile unsigned long IOPFEN           : 1;
			volatile unsigned long IOPGEN           : 1;
			volatile unsigned long ADC1EN           : 1;
			volatile unsigned long ADC2EN           : 1;
			volatile unsigned long TIM1EN           : 1;
			volatile unsigned long SPI1EN           : 1;
			volatile unsigned long TIM8EN           : 1;
			volatile unsigned long USART1EN : 1;
			volatile unsigned long ADC3EN           : 1;
			volatile unsigned long NC                       : 16;
		} B;
		volatile unsigned long W;
	} APB2ENR;
	union {
		struct {
			volatile unsigned long TIM2EN           : 1;
			volatile unsigned long TIM3EN           : 1;
			volatile unsigned long TIM4EN           : 1;
			volatile unsigned long TIM5EN           : 1;
			volatile unsigned long TIM6EN           : 1;
			volatile unsigned long TIM7EN           : 1;
			volatile unsigned long NC5              : 5;
			volatile unsigned long WWGDEN           : 1;
			volatile unsigned long NC4              : 2;
			volatile unsigned long SPI2EN           : 1;
			volatile unsigned long SPI3EN           : 1;
			volatile unsigned long NC3              : 1;
			volatile unsigned long USART2EN : 1;
			volatile unsigned long USART3EN : 1;
			volatile unsigned long USART4EN : 1;
			volatile unsigned long USART5EN : 1;
			volatile unsigned long I2C1EN           : 1;
			volatile unsigned long I2C2EN           : 1;
			volatile unsigned long USBEN            : 1;
			volatile unsigned long NC2              : 1;
			volatile unsigned long CANEN            : 1;
			volatile unsigned long NC1              : 1;
			volatile unsigned long BKPEN            : 1;
			volatile unsigned long PWREN            : 1;
			volatile unsigned long DACEN            : 1;
			volatile unsigned long NC                       : 2;
		} B;
		volatile unsigned long W;
	} APB1ENR;
	union {
		struct {
			volatile unsigned long LSEON            : 1;
			volatile unsigned long LSERDY           : 1;
			volatile unsigned long LSEBYP           : 1;
			volatile unsigned long NC2              : 5;
			volatile unsigned long RTCSEL           : 2;
			volatile unsigned long NC1              : 5;
			volatile unsigned long RTCEN            : 1;
			volatile unsigned long BDRST            : 1;
			volatile unsigned long NC                       : 15;
		} B;
		volatile unsigned long W;
	} BDCR;
	union {
		struct {
			volatile unsigned long LSION            : 1;
			volatile unsigned long LSIRDY           : 1;
			volatile unsigned long NC1              : 22;
			volatile unsigned long RMVF             : 1;
			volatile unsigned long NC                       : 1;
			volatile unsigned long PINRSTF  : 1;
			volatile unsigned long PORRSTF  : 1;
			volatile unsigned long SFTRSTF  : 1;
			volatile unsigned long IWDGRSTF : 1;
			volatile unsigned long WWDGRSTF : 1;
			volatile unsigned long LPWRRSTF : 1;
		} B;
		volatile unsigned long W;
	} CSR;
} RCC_T;

/*------------------------ Real-Time Clock -----------------------------------*/

/*
   typedef struct
   {
        union
        {
                struct
                {
                        volatile unsigned short SECIE		:1;
                        volatile unsigned short ALRIE		:1;
                        volatile unsigned short OWIE		:1;
                        volatile unsigned short NC			:13;
                } B;
                volatile unsigned short W;
        } CRH;
        unsigned short  RESERVED0;
        union
        {
                struct
                {
                        volatile unsigned short SECF		:1;
                        volatile unsigned short ALRF		:1;
                        volatile unsigned short OWF		:1;
                        volatile unsigned short RSF		:1;
                        volatile unsigned short CNF		:1;
                        volatile unsigned short RTOFF		:1;
                        volatile unsigned short NC			:10;
                } B;
                volatile unsigned short W;
        } CRL;
        unsigned short  RESERVED1;
        union
        {
                struct
                {
                        volatile unsigned short PRL		:4;
                        volatile unsigned short NC			:12;
                } B;
                volatile unsigned short W;
        } PRLH;
        unsigned short  RESERVED2;
        union
        {
                struct
                {
                        volatile unsigned short PRL		:16;
                } B;
                volatile unsigned short W;
        } PRLL;
        unsigned short  RESERVED3;
        union
        {
                struct
                {
                        volatile unsigned short RTC_DIV	:4;
                        volatile unsigned short NC			:12;
                } B;
                volatile unsigned short W;
        } DIVH;
        unsigned short  RESERVED4;
        union
        {
                struct
                {
                        volatile unsigned short RTC_DIV	:16;
                } B;
                volatile unsigned short W;
        } DIVL;
        unsigned short  RESERVED5;
        volatile unsigned short CNTH;
        unsigned short  RESERVED6;
        volatile unsigned short CNTL;
        unsigned short  RESERVED7;
        volatile unsigned short ALRH;
        unsigned short  RESERVED8;
        volatile unsigned short ALRL;
        unsigned short  RESERVED9;
   } RTC_T;
 */
/*------------------------ SD host Interface ---------------------------------*/
typedef struct {
	volatile unsigned long POWER;
	volatile unsigned long CLKCR;
	volatile unsigned long ARG;
	volatile unsigned long CMD;
	volatile unsigned long const RESPCMD;
	volatile unsigned long const RESP1;
	volatile unsigned long const RESP2;
	volatile unsigned long const RESP3;
	volatile unsigned long const RESP4;
	volatile unsigned long DTIMER;
	volatile unsigned long DLEN;
	volatile unsigned long DCTRL;
	volatile unsigned long const DCOUNT;
	volatile unsigned long const STA;
	volatile unsigned long ICR;
	volatile unsigned long MASK;
	unsigned long RESERVED0[2];
	volatile unsigned long const FIFOCNT;
	unsigned long RESERVED1[13];
	volatile unsigned long FIFO;
} SDIO_T;

/*------------------------ Serial Peripheral Interface -----------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned short CPHA            : 1;
			volatile unsigned short CPOL            : 1;
			volatile unsigned short MSTR            : 1;
			volatile unsigned short BR                      : 3;
			volatile unsigned short SPE             : 1;
			volatile unsigned short LSBFIRST        : 1;
			volatile unsigned short SSI             : 1;
			volatile unsigned short SSM             : 1;
			volatile unsigned short RXONLY          : 1;
			volatile unsigned short DFF             : 1;
			volatile unsigned short CRCNEXT : 1;
			volatile unsigned short CRCEN           : 1;
			volatile unsigned short BIDIOE          : 1;
			volatile unsigned short BIDIMODE        : 1;
		} B;
		volatile unsigned short W;
	} CR1;
	volatile unsigned short RESERVED0;

	union {
		struct {
			volatile unsigned short RXDMAEN : 1;
			volatile unsigned short TXDMAEN : 1;
			volatile unsigned short SSOE            : 1;
			volatile unsigned short NC1             : 2;
			volatile unsigned short ERRIE           : 1;
			volatile unsigned short RXNEIE          : 1;
			volatile unsigned short TXEIE           : 1;
			volatile unsigned short NC                      : 8;
		} B;
		volatile unsigned short W;
	}  CR2;
	volatile unsigned short RESERVED1;

	union {
		struct {
			volatile unsigned short RXNE            : 1;
			volatile unsigned short TXE             : 1;
			volatile unsigned short CHSIDE          : 1;
			volatile unsigned short UDR             : 1;
			volatile unsigned short CRCERR          : 1;     //PS
			volatile unsigned short MODF            : 1;
			volatile unsigned short OVR             : 1;
			volatile unsigned short BSY             : 1;
			volatile unsigned short NC                      : 8;
		} B;
		volatile unsigned short W;
	}  SR;
	volatile unsigned short RESERVED2;
	volatile unsigned short DR;
	volatile unsigned short RESERVED3;
	volatile unsigned short CRCPR;
	volatile unsigned short RESERVED4;
	volatile unsigned short RXCRCR;
	volatile unsigned short RESERVED5;
	volatile unsigned short TXCRCR;
	volatile unsigned short RESERVED6;
	union {
		struct {
			volatile unsigned short CHLEN           : 1;
			volatile unsigned short DATLEN          : 2;
			volatile unsigned short CKPOL           : 1;
			volatile unsigned short I2SSTD          : 1;
			volatile unsigned short NC1             : 1;
			volatile unsigned short PCMSYNC : 1;
			volatile unsigned short I2SCFG          : 2;
			volatile unsigned short I2SE            : 1;
			volatile unsigned short I2SMOD          : 1;
			volatile unsigned short NC                      : 4;
		} B;
		volatile unsigned short W;
	}  I2SCFGR;
	volatile unsigned short RESERVED7;
	union {
		struct {
			volatile unsigned short I2SDIV          : 8;
			volatile unsigned short ODD             : 1;
			volatile unsigned short MCKOE           : 1;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	}  I2SPR;
	volatile unsigned short RESERVED8;
} SPI_T;

/*------------------------ SystemTick ----------------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long ENABLE           : 1;
			volatile unsigned long TICKINT  : 1;
			volatile unsigned long CLKSOURCE        : 1;
			volatile unsigned long NC                       : 13;
			volatile unsigned long COUNTFLAG        : 1;
			volatile unsigned long NC1              : 15;
		} B;
		volatile unsigned long W;
	} CTRL;
	union {
		struct {
			volatile unsigned long RELOAD           : 24;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} LOAD;
	union {
		struct {
			volatile unsigned long CURRENT  : 24;
			volatile unsigned long NC                       : 8;
		} B;
		volatile unsigned long W;
	} VAL;
	union {
		struct {
			volatile unsigned long TENMS            : 24;
			volatile unsigned long NC                       : 6;
			volatile unsigned long SKEW             : 1;
			volatile unsigned long NOREF            : 1;
		} B;
		volatile unsigned long W;
	} CALIB;
} SYSTICK_T;

/*------------------------ TIM -----------------------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned short CEN             : 1;
			volatile unsigned short UDIS            : 1;
			volatile unsigned short URS             : 1;
			volatile unsigned short OPM             : 1;
			volatile unsigned short DIR             : 1;
			volatile unsigned short CMS             : 2;
			volatile unsigned short ARPE            : 1;
			volatile unsigned short CKD             : 2;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	} CR1;
	unsigned short RESERVED0;
	union {
		struct {
			volatile unsigned short CCPC            : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short CCUS            : 1;
			volatile unsigned short CCDS            : 1;
			volatile unsigned short MMS             : 3;
			volatile unsigned short TI1S            : 1;
			volatile unsigned short OIS1            : 1;
			volatile unsigned short OIS1N           : 1;
			volatile unsigned short OIS2            : 1;
			volatile unsigned short OIS2N           : 1;
			volatile unsigned short OIS3            : 1;
			volatile unsigned short OIS3N           : 1;
			volatile unsigned short OIS4            : 1;
			volatile unsigned short NC1             : 1;
		} B;
		volatile unsigned short W;
	} CR2;
	unsigned short RESERVED1;
	union {
		struct {
			volatile unsigned short SMS             : 3;
			volatile unsigned short NC                      : 1;
			volatile unsigned short TS                      : 3;
			volatile unsigned short MSM             : 1;
			volatile unsigned short ETF             : 4;
			volatile unsigned short ETPS            : 2;
			volatile unsigned short ECE             : 1;
			volatile unsigned short ETP             : 1;
		} B;
		volatile unsigned short W;
	} SMCR;
	unsigned short RESERVED2;
	union {
		struct {
			volatile unsigned short UIE             : 1;
			volatile unsigned short CC1IE           : 1;
			volatile unsigned short CC2IE           : 1;
			volatile unsigned short CC3IE           : 1;
			volatile unsigned short CC4IE           : 1;
			volatile unsigned short COMIE           : 1;
			volatile unsigned short TIE             : 1;
			volatile unsigned short BIE             : 1;
			volatile unsigned short UDE             : 1;
			volatile unsigned short CC1DE           : 1;
			volatile unsigned short CC2DE           : 1;
			volatile unsigned short CC3DE           : 1;
			volatile unsigned short CC4DE           : 1;
			volatile unsigned short COMDE           : 1;
			volatile unsigned short TDE             : 1;
			volatile unsigned short NC                      : 1;
		} B;
		volatile unsigned short W;
	} DIER;
	unsigned short RESERVED3;
	union {
		struct {
			volatile unsigned short UIF             : 1;
			volatile unsigned short CC1IF           : 1;
			volatile unsigned short CC2IF           : 1;
			volatile unsigned short CC3IF           : 1;
			volatile unsigned short CC4IF           : 1;
			volatile unsigned short COMIF           : 1;
			volatile unsigned short TIF             : 1;
			volatile unsigned short BIF             : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short CC1OF           : 1;
			volatile unsigned short CC2OF           : 1;
			volatile unsigned short CC3OF           : 1;
			volatile unsigned short CC4OF           : 1;
			volatile unsigned short NC1             : 3;
		} B;
		volatile unsigned short W;
	} SR;
	unsigned short RESERVED4;
	union {
		struct {
			volatile unsigned short UG                      : 1;
			volatile unsigned short CC1G            : 1;
			volatile unsigned short CC2G            : 1;
			volatile unsigned short CC3G            : 1;
			volatile unsigned short CC4G            : 1;
			volatile unsigned short COMG            : 1;
			volatile unsigned short TG                      : 1;
			volatile unsigned short BG                      : 1;
			volatile unsigned short NC                      : 8;
		} B;
		volatile unsigned short W;
	} EGR;
	unsigned short RESERVED5;
	union {
		struct {
			volatile unsigned short CC1S            : 2;
			volatile unsigned short OC1FE           : 1;
			volatile unsigned short OC1PE           : 1;
			volatile unsigned short OC1M            : 3;
			volatile unsigned short OC1CE           : 1;

			volatile unsigned short CC2S            : 2;
			volatile unsigned short OC2FE           : 1;
			volatile unsigned short OC2PE           : 1;
			volatile unsigned short OC2M            : 3;
			volatile unsigned short OC2CE           : 1;
		} B_COMP;
		struct {
			volatile unsigned short CC1S            : 2;
			volatile unsigned short IC1PSC          : 2;
			volatile unsigned short IC1F            : 4;
			volatile unsigned short CC2S            : 2;
			volatile unsigned short IC2PSC          : 2;
			volatile unsigned short IC2F            : 4;
		} B_CAP;
		volatile unsigned short W;
	} CCMR1;
	unsigned short RESERVED6;
	union {
		struct {
			volatile unsigned short CC3S            : 2;
			volatile unsigned short OC3FE           : 1;
			volatile unsigned short OC3PE           : 1;
			volatile unsigned short OC3M            : 3;
			volatile unsigned short OC3CE           : 1;
			volatile unsigned short CC4S            : 2;
			volatile unsigned short OC4FE           : 1;
			volatile unsigned short OC4PE           : 1;
			volatile unsigned short OC4M            : 3;
			volatile unsigned short OC4CE           : 1;
		} B_COMP;
		struct {
			volatile unsigned short CC3S            : 2;
			volatile unsigned short IC3PSC          : 2;
			volatile unsigned short IC3F            : 4;
			volatile unsigned short CC4S            : 2;
			volatile unsigned short IC4PSC          : 2;
			volatile unsigned short IC4F            : 4;
		} B_CAP;
		volatile unsigned short W;
	} CCMR2;
	unsigned short RESERVED7;
	union {
		struct {
			volatile unsigned short CC1E            : 1;
			volatile unsigned short CC1P            : 1;
			volatile unsigned short CC1NE           : 1;
			volatile unsigned short CC1NP           : 1;
			volatile unsigned short CC2E            : 1;
			volatile unsigned short CC2P            : 1;
			volatile unsigned short CC2NE           : 1;
			volatile unsigned short CC2NP           : 1;
			volatile unsigned short CC3E            : 1;
			volatile unsigned short CC3P            : 1;
			volatile unsigned short CC3NE           : 1;
			volatile unsigned short CC3NP           : 1;
			volatile unsigned short CC4E            : 1;
			volatile unsigned short CC4P            : 1;
			volatile unsigned short NC                      : 2;
		} B;
		volatile unsigned short W;
	} CCER;
	unsigned short RESERVED8;
	volatile unsigned short CNT;
	unsigned short RESERVED9;
	volatile unsigned short PSC;
	unsigned short RESERVED10;
	volatile unsigned short ARR;
	unsigned short RESERVED11;
	union {
		struct {
			volatile unsigned short REP             : 8;
			volatile unsigned short NC                      : 8;
		} B;
		volatile unsigned short W;
	} RCR;
	unsigned short RESERVED12;
	volatile unsigned short CCR1;
	unsigned short RESERVED13;
	volatile unsigned short CCR2;
	unsigned short RESERVED14;
	volatile unsigned short CCR3;
	unsigned short RESERVED15;
	volatile unsigned short CCR4;
	unsigned short RESERVED16;
	union {
		struct {
			volatile unsigned short DTG             : 8;
			volatile unsigned short LOCK            : 2;
			volatile unsigned short OSSI            : 1;
			volatile unsigned short OSSR            : 1;
			volatile unsigned short BKE             : 1;
			volatile unsigned short BKP             : 1;
			volatile unsigned short AOE             : 1;
			volatile unsigned short MOE             : 1;
		} B;
		volatile unsigned short W;
	} BDTR;
	unsigned short RESERVED17;
	union {
		struct {
			volatile unsigned short DBA             : 5;
			volatile unsigned short NC                      : 3;
			volatile unsigned short DBL             : 5;
			volatile unsigned short NC1             : 3;
		} B;
		volatile unsigned short W;
	} DCR;
	unsigned short RESERVED18;
	volatile unsigned short DMAR;
	unsigned short RESERVED19;
} TIM_T_A;



typedef struct {
	union {
		struct {
			volatile unsigned short CEN             : 1;
			volatile unsigned short UDIS            : 1;
			volatile unsigned short URS             : 1;
			volatile unsigned short OPM             : 1;
			volatile unsigned short DIR             : 1;
			volatile unsigned short CMS             : 2;
			volatile unsigned short ARPE            : 1;
			volatile unsigned short CKD             : 2;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	} CR1;
	unsigned short RESERVED0;
	union {
		struct {
			volatile unsigned short NC                      : 3;
			volatile unsigned short CCDS            : 1;
			volatile unsigned short MMS             : 3;
			volatile unsigned short TI1S            : 1;
			volatile unsigned short NC1             : 8;
		} B;
		volatile unsigned short W;
	} CR2;
	unsigned short RESERVED1;
	union {
		struct {
			volatile unsigned short SMS             : 3;
			volatile unsigned short NC                      : 1;
			volatile unsigned short TS                      : 3;
			volatile unsigned short MSM             : 1;
			volatile unsigned short ETF             : 4;
			volatile unsigned short ETPS            : 2;
			volatile unsigned short ECE             : 1;
			volatile unsigned short ETP             : 1;
		} B;
		volatile unsigned short W;
	} SMCR;
	unsigned short RESERVED2;
	union {
		struct {
			volatile unsigned short UIE             : 1;
			volatile unsigned short CC1IE           : 1;
			volatile unsigned short CC2IE           : 1;
			volatile unsigned short CC3IE           : 1;
			volatile unsigned short CC4IE           : 1;
			volatile unsigned short COMIE           : 1;
			volatile unsigned short TIE             : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short UDE             : 1;
			volatile unsigned short CC1DE           : 1;
			volatile unsigned short CC2DE           : 1;
			volatile unsigned short CC3DE           : 1;
			volatile unsigned short CC4DE           : 1;
			volatile unsigned short COMDE           : 1;
			volatile unsigned short TDE             : 1;
			volatile unsigned short NC1             : 1;
		} B;
		volatile unsigned short W;
	} DIER;
	unsigned short RESERVED3;
	union {
		struct {
			volatile unsigned short UIF             : 1;
			volatile unsigned short CC1IF           : 1;
			volatile unsigned short CC2IF           : 1;
			volatile unsigned short CC3IF           : 1;
			volatile unsigned short CC4IF           : 1;
			volatile unsigned short COMIF           : 1;
			volatile unsigned short TIF             : 1;
			volatile unsigned short NC                      : 2;
			volatile unsigned short CC1OF           : 1;
			volatile unsigned short CC2OF           : 1;
			volatile unsigned short CC3OF           : 1;
			volatile unsigned short CC4OF           : 1;
			volatile unsigned short NC1             : 3;
		} B;
		volatile unsigned short W;
	} SR;
	unsigned short RESERVED4;
	union {
		struct {
			volatile unsigned short UG                      : 1;
			volatile unsigned short CC1G            : 1;
			volatile unsigned short CC2G            : 1;
			volatile unsigned short CC3G            : 1;
			volatile unsigned short CC4G            : 1;
			volatile unsigned short NC                      : 1;
			volatile unsigned short TG                      : 1;
			volatile unsigned short NC1             : 9;
		} B;
		volatile unsigned short W;
	} EGR;
	unsigned short RESERVED5;
	union {
		struct {
			volatile unsigned short CC1S            : 2;
			volatile unsigned short OC1FE           : 1;
			volatile unsigned short OC1PE           : 1;
			volatile unsigned short OC1M            : 3;
			volatile unsigned short OC1CE           : 1;
			volatile unsigned short CC2S            : 2;
			volatile unsigned short OC2FE           : 1;
			volatile unsigned short OC2PE           : 1;
			volatile unsigned short OC2M            : 3;
			volatile unsigned short OC2CE           : 1;
		} B_COMP;
		struct {
			volatile unsigned short CC1S            : 2;
			volatile unsigned short IC1PSC          : 2;
			volatile unsigned short IC1F            : 4;
			volatile unsigned short CC2S            : 2;
			volatile unsigned short IC2PSC          : 2;
			volatile unsigned short IC2F            : 4;
		} B_CAP;
		volatile unsigned short W;
	} CCMR1;
	unsigned short RESERVED6;
	union {
		struct {
			volatile unsigned short CC3S            : 2;
			volatile unsigned short OC3FE           : 1;
			volatile unsigned short OC3PE           : 1;
			volatile unsigned short OC3M            : 3;
			volatile unsigned short OC3CE           : 1;
			volatile unsigned short CC4S            : 2;
			volatile unsigned short OC4FE           : 1;
			volatile unsigned short OC4PE           : 1;
			volatile unsigned short OC4M            : 3;
			volatile unsigned short OC4CE           : 1;
		} B_COMP;
		struct {
			volatile unsigned short CC3S            : 2;
			volatile unsigned short IC3PSC          : 2;
			volatile unsigned short IC3F            : 4;
			volatile unsigned short CC4S            : 2;
			volatile unsigned short IC4PSC          : 2;
			volatile unsigned short IC4F            : 4;
		} B_CAP;
		volatile unsigned short W;
	} CCMR2;
	unsigned short RESERVED7;
	union {
		struct {
			volatile unsigned short CC1E            : 1;
			volatile unsigned short CC1P            : 1;
			volatile unsigned short NC                      : 2;
			volatile unsigned short CC2E            : 1;
			volatile unsigned short CC2P            : 1;
			volatile unsigned short NC1             : 2;
			volatile unsigned short CC3E            : 1;
			volatile unsigned short CC3P            : 1;
			volatile unsigned short NC2             : 2;
			volatile unsigned short CC4E            : 1;
			volatile unsigned short CC4P            : 1;
			volatile unsigned short NC3             : 2;
		} B;
		volatile unsigned short W;
	} CCER;
	unsigned short RESERVED8;
	volatile unsigned short CNT;
	unsigned short RESERVED9;
	volatile unsigned short PSC;
	unsigned short RESERVED10;
	volatile unsigned short ARR;
	unsigned short RESERVED11;

	unsigned short RESERVED12[2];

	volatile unsigned short CCR1;
	unsigned short RESERVED13;
	volatile unsigned short CCR2;
	unsigned short RESERVED14;
	volatile unsigned short CCR3;
	unsigned short RESERVED15;
	volatile unsigned short CCR4;
	unsigned short RESERVED16;

	unsigned short RESERVED17[2];

	union {
		struct {
			volatile unsigned short DBA             : 5;
			volatile unsigned short NC                      : 3;
			volatile unsigned short DBL             : 5;
			volatile unsigned short NC1             : 3;
		} B;
		volatile unsigned short W;
	} DCR;
	unsigned short RESERVED18;
	volatile unsigned short DMAR;
	unsigned short RESERVED19;
} TIM_T_B;



typedef struct {
	union {
		struct {
			volatile unsigned short CEN             : 1;
			volatile unsigned short UDIS            : 1;
			volatile unsigned short URS             : 1;
			volatile unsigned short OPM             : 1;
			volatile unsigned short NC                      : 3;
			volatile unsigned short ARPE            : 1;
			volatile unsigned short NC1             : 8;
		} B;
		volatile unsigned short W;
	} CR1;
	unsigned short RESERVED0;
	union {
		struct {
			volatile unsigned short NC                      : 4;
			volatile unsigned short MMS             : 3;
			volatile unsigned short NC1             : 9;
		} B;
		volatile unsigned short W;
	} CR2;
	unsigned short RESERVED1;
	unsigned short RESERVED2[2];
	union {
		struct {
			volatile unsigned short UIE             : 1;
			volatile unsigned short NC                      : 7;
			volatile unsigned short UDE             : 1;
			volatile unsigned short NC1             : 7;
		} B;
		volatile unsigned short W;
	} DIER;
	unsigned short RESERVED3;
	union {
		struct {
			volatile unsigned short UIF             : 1;
			volatile unsigned short NC                      : 15;
		} B;
		volatile unsigned short W;
	} SR;
	unsigned short RESERVED4;
	union {
		struct {
			volatile unsigned short UG                      : 1;
			volatile unsigned short NC                      : 15;
		} B;
		volatile unsigned short W;
	} EGR;
	unsigned short RESERVED5;
	unsigned short RESERVED6[2];
	unsigned short RESERVED7[2];
	unsigned short RESERVED8[2];
	volatile unsigned short CNT;
	unsigned short RESERVED9;
	volatile unsigned short PSC;
	unsigned short RESERVED10;
	volatile unsigned short ARR;
	unsigned short RESERVED11;
} TIM_T_C;



/*----------------- Universal Synchronous Asynchronous Receiver Transmitter --*/
typedef struct {
	union {
		struct {
			volatile unsigned short PE                      : 1;
			volatile unsigned short FE                      : 1;
			volatile unsigned short NE                      : 1;
			volatile unsigned short ORE             : 1;
			volatile unsigned short IDLE            : 1;
			volatile unsigned short RXNE            : 1;
			volatile unsigned short TC                      : 1;
			volatile unsigned short TXE             : 1;
			volatile unsigned short LBD             : 1;
			volatile unsigned short CTS             : 1;
			volatile unsigned short NC                      : 6;
		} B;
		volatile unsigned short W;
	} SR;
	unsigned short RESERVED0;
	union {
		struct {
			volatile unsigned short DR                      : 9;
			volatile unsigned short NC                      : 7;
		} B;
		volatile unsigned short W;
	} DR;
	unsigned short RESERVED1;
	union {
		struct {
			volatile unsigned short DIV_Fraction    : 4;
			volatile unsigned short DIV_Mantissa    : 12;
		} B;
		volatile unsigned short W;
	} BRR;
	unsigned short RESERVED2;
	union {
		struct {
			volatile unsigned short SBK             : 1;
			volatile unsigned short RWU             : 1;
			volatile unsigned short RE                      : 1;
			volatile unsigned short TE                      : 1;
			volatile unsigned short IDLEIE          : 1;
			volatile unsigned short RXNEIE          : 1;
			volatile unsigned short TCIE            : 1;
			volatile unsigned short TXEIE           : 1;
			volatile unsigned short PEIE            : 1;
			volatile unsigned short PS                      : 1;
			volatile unsigned short PCE             : 1;
			volatile unsigned short WAKE            : 1;
			volatile unsigned short M                       : 1;
			volatile unsigned short UE                      : 1;
			volatile unsigned short NC                      : 2;
		} B;
		volatile unsigned short W;
	} CR1;
	unsigned short RESERVED3;
	union {
		struct {
			volatile unsigned short ADD             : 4;
			volatile unsigned short NC2             : 1;
			volatile unsigned short LBDL            : 1;
			volatile unsigned short LBDIE           : 1;
			volatile unsigned short NC1             : 1;
			volatile unsigned short LBCL            : 1;
			volatile unsigned short CPHA            : 1;
			volatile unsigned short CPOL            : 1;
			volatile unsigned short CLKEN           : 1;
			volatile unsigned short STOP            : 2;
			volatile unsigned short LINEN           : 1;
			volatile unsigned short NC                      : 1;
		} B;
		volatile unsigned short W;
	} CR2;
	unsigned short RESERVED4;
	union {
		struct {
			volatile unsigned short EIE             : 1;
			volatile unsigned short IREN            : 1;
			volatile unsigned short IRLP            : 1;
			volatile unsigned short HDSEL           : 1;
			volatile unsigned short NACK            : 1;
			volatile unsigned short SCEN            : 1;
			volatile unsigned short DMAR            : 1;
			volatile unsigned short DMAT            : 1;
			volatile unsigned short RTSE            : 1;
			volatile unsigned short CTSE            : 1;
			volatile unsigned short CTSIE           : 1;
			volatile unsigned short NC                      : 5;
		} B;
		volatile unsigned short W;
	} CR3;
	unsigned short RESERVED5;
	union {
		struct {
			volatile unsigned short PSC             : 8;
			volatile unsigned short GT                      : 8;
		} B;
		volatile unsigned short W;
	} GTPR;
	unsigned short RESERVED6;
} USART_T;

/*------------------------ Window WATCHDOG -----------------------------------*/
typedef struct {
	union {
		struct {
			volatile unsigned long T                        : 7;
			volatile unsigned long WDGA             : 1;
			volatile unsigned long NC                       : 24;
		} B;
		volatile unsigned long W;
	} CR;
	union {
		struct {
			volatile unsigned long W                        : 7;
			volatile unsigned long WDGTB            : 2;
			volatile unsigned long EWI              : 1;
			volatile unsigned long NC                       : 22;
		} B;
		volatile unsigned long W;
	} CFR;
	union {
		struct {
			volatile unsigned long EWIF             : 1;
			volatile unsigned long NC                       : 31;
		} B;
		volatile unsigned long W;
	} SR;
} WWDG_T;

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Peripheral and SRAM base address in the alias region */
#define PERIPH_BB_BASE        ((unsigned long)0x42000000)
#define SRAM_BB_BASE          ((unsigned long)0x22000000)

/* Peripheral and SRAM base address in the bit-band region */
#define SRAM_BASE             ((unsigned long)0x20000000)
#define PERIPH_BASE           ((unsigned long)0x40000000)

/* FSMC registers base address */
#define FSMC_R_BASE           ((unsigned long)0xA0000000)

/* Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define RTC_BASE              (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x3000)
#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)
#define UART4_BASE            (APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE            (APB1PERIPH_BASE + 0x5000)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE             (APB1PERIPH_BASE + 0x5800)
#define CAN_BASE              (APB1PERIPH_BASE + 0x6400)
#define BKP_BASE              (APB1PERIPH_BASE + 0x6C00)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000)
#define DAC_BASE              (APB1PERIPH_BASE + 0x7400)

#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x3400)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define ADC3_BASE             (APB2PERIPH_BASE + 0x3C00)

#define SDIO_BASE             (PERIPH_BASE + 0x18000)

#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define DMA1_CHANNEL1_BASE    (AHBPERIPH_BASE + 0x0008)
#define DMA1_CHANNEL2_BASE    (AHBPERIPH_BASE + 0x001C)
#define DMA1_CHANNEL3_BASE    (AHBPERIPH_BASE + 0x0030)
#define DMA1_CHANNEL4_BASE    (AHBPERIPH_BASE + 0x0044)
#define DMA1_CHANNEL5_BASE    (AHBPERIPH_BASE + 0x0058)
#define DMA1_CHANNEL6_BASE    (AHBPERIPH_BASE + 0x006C)
#define DMA1_CHANNEL7_BASE    (AHBPERIPH_BASE + 0x0080)
#define DMA2_BASE             (AHBPERIPH_BASE + 0x0400)
#define DMA2_CHANNEL1_BASE    (AHBPERIPH_BASE + 0x0408)
#define DMA2_CHANNEL2_BASE    (AHBPERIPH_BASE + 0x041C)
#define DMA2_CHANNEL3_BASE    (AHBPERIPH_BASE + 0x0430)
#define DMA2_CHANNEL4_BASE    (AHBPERIPH_BASE + 0x0444)
#define DMA2_CHANNEL5_BASE    (AHBPERIPH_BASE + 0x0458)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define CRC_BASE              (AHBPERIPH_BASE + 0x3000)

/* Flash registers base address */
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000)
/* Flash Option Bytes base address */
#define OB_BASE               ((unsigned long)0x1FFFF800)

/* FSMC Bankx registers base address */
#define FSMC_Bank1_R_BASE     (FSMC_R_BASE + 0x0000)
#define FSMC_Bank1E_R_BASE    (FSMC_R_BASE + 0x0104)
#define FSMC_Bank2_R_BASE     (FSMC_R_BASE + 0x0060)
#define FSMC_Bank3_R_BASE     (FSMC_R_BASE + 0x0080)
#define FSMC_Bank4_R_BASE     (FSMC_R_BASE + 0x00A0)

/* Debug MCU registers base address */
#define DBGMCU_BASE          ((unsigned long)0xE0042000)

/* System Control Space memory map */
#define SCS_BASE              ((unsigned long)0xE000E000)

#define SYSTICK_BASE          (SCS_BASE + 0x0010)
#define NVIC_BASE             (SCS_BASE + 0x0100)
#define SCB_BASE              (SCS_BASE + 0x0D00)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

#ifdef _TIM2
#define TIM2                ((TIM_T_B*)TIM2_BASE)
#endif /*_TIM2 */

#ifdef _TIM3
#define TIM3                ((TIM_T_B*)TIM3_BASE)
#endif /*_TIM3 */

#ifdef _TIM4
#define TIM4                ((TIM_T_B*)TIM4_BASE)
#endif /*_TIM4 */

#ifdef _TIM5
#define TIM5                ((TIM_T_B*)TIM5_BASE)
#endif /*_TIM5 */

#ifdef _TIM6
#define TIM6                ((TIM_T_C*)TIM6_BASE)
#endif /*_TIM6 */

#ifdef _TIM7
#define TIM7                ((TIM_T_C*)TIM7_BASE)
#endif /*_TIM7 */

#ifdef _RTC
#define RTC                 ((RTC_T*)RTC_BASE)
#endif /*_RTC */

#ifdef _WWDG
#define WWDG                ((WWDG_T*)WWDG_BASE)
#endif /*_WWDG */

#ifdef _IWDG
#define IWDG                ((IWDG_T*)IWDG_BASE)
#endif /*_IWDG */

#ifdef _SPI2
#define SPI2                ((SPI_T*)SPI2_BASE)
#endif /*_SPI2 */

#ifdef _SPI3
#define SPI3                ((SPI_T*)SPI3_BASE)
#endif /*_SPI3 */

#ifdef _USART2
#define USART2              ((USART_T*)USART2_BASE)
#endif /*_USART2 */

#ifdef _USART3
#define USART3              ((USART_T*)USART3_BASE)
#endif /*_USART3 */

#ifdef _UART4
#define UART4              ((USART_T*)UART4_BASE)
#endif /*_UART4 */

#ifdef _UART5
#define UART5              ((USART_T*)UART5_BASE)
#endif /*_USART5 */

#ifdef _I2C1
#define I2C1                ((I2C_T*)I2C1_BASE)
#endif /*_I2C1 */

#ifdef _I2C2
#define I2C2                ((I2C_T*)I2C2_BASE)
#endif /*_I2C2 */

#ifdef _CAN
#define CAN                 ((CAN_T*)CAN_BASE)
#endif /*_CAN */

#ifdef _BKP
#define BKP                 ((BKP_T*)BKP_BASE)
#endif /*_BKP */

#ifdef _PWR
#define PWR                 ((PWR_T*)PWR_BASE)
#endif /*_PWR */

#ifdef _DAC
#define DAC                 ((DAC_T*)DAC_BASE)
#endif /*_DAC */

#ifdef _AFIO
#define AFIO                ((AFIO_T*)AFIO_BASE)
#endif /*_AFIO */

#ifdef _EXTI
#define EXTI                ((EXTI_T*)EXTI_BASE)
#endif /*_EXTI */

#ifdef _GPIOA
#define GPIOA               ((GPIO_T*)GPIOA_BASE)
#endif /*_GPIOA */

#ifdef _GPIOB
#define GPIOB               ((GPIO_T*)GPIOB_BASE)
#endif /*_GPIOB */

#ifdef _GPIOC
#define GPIOC               ((GPIO_T*)GPIOC_BASE)
#endif /*_GPIOC */

#ifdef _GPIOD
#define GPIOD               ((GPIO_T*)GPIOD_BASE)
#endif /*_GPIOD */

#ifdef _GPIOE
#define GPIOE               ((GPIO_T*)GPIOE_BASE)
#endif /*_GPIOE */

#ifdef _GPIOF
#define GPIOF               ((GPIO_T*)GPIOF_BASE)
#endif /*_GPIOF */

#ifdef _GPIOG
#define GPIOG               ((GPIO_T*)GPIOG_BASE)
#endif /*_GPIOG */

#ifdef _ADC1
#define ADC1                ((ADC_T*)ADC1_BASE)
#endif /*_ADC1 */

#ifdef _ADC2
#define ADC2                ((ADC_T*)ADC2_BASE)
#endif /*_ADC2 */

#ifdef _TIM1
#define TIM1                ((TIM_T_A*)TIM1_BASE)
#endif /*_TIM1 */

#ifdef _SPI1
#define SPI1                ((SPI_T*)SPI1_BASE)
#endif /*_SPI1 */

#ifdef _TIM8
#define TIM8                ((TIM_T_A*)TIM8_BASE)
#endif /*_TIM8 */

#ifdef _USART1
#define USART1              ((USART_T*)USART1_BASE)
#endif /*_USART1 */

#ifdef _ADC3
#define ADC3                ((ADC_T*)ADC3_BASE)
#endif /*_ADC3 */

#ifdef _SDIO
#define SDIO                ((SDIO_T*)SDIO_BASE)
#endif /*_SDIO */

#ifdef _DMA
#define DMA1                ((DMA_T*)DMA1_BASE)
#define DMA2                ((DMA_T*)DMA2_BASE)
#endif /*_DMA */

#ifdef _DMA1_CHANNEL1
#define DMA1_CHANNEL1       ((DMA_CHANNEL_T*)DMA1_CHANNEL1_BASE)
#endif /*_DMA1_CHANNEL1 */

#ifdef _DMA1_CHANNEL2
#define DMA1_CHANNEL2       ((DMA_CHANNEL_T*)DMA1_CHANNEL2_BASE)
#endif /*_DMA1_CHANNEL2 */

#ifdef _DMA1_CHANNEL3
#define DMA1_CHANNEL3       ((DMA_CHANNEL_T*)DMA1_CHANNEL3_BASE)
#endif /*_DMA1_CHANNEL3 */

#ifdef _DMA1_CHANNEL4
#define DMA1_CHANNEL4       ((DMA_CHANNEL_T*)DMA1_CHANNEL4_BASE)
#endif /*_DMA1_CHANNEL4 */

#ifdef _DMA1_CHANNEL5
#define DMA1_CHANNEL5       ((DMA_CHANNEL_T*)DMA1_CHANNEL5_BASE)
#endif /*_DMA1_CHANNEL5 */

#ifdef _DMA1_CHANNEL6
#define DMA1_CHANNEL6       ((DMA_CHANNEL_T*)DMA1_CHANNEL6_BASE)
#endif /*_DMA1_CHANNEL6 */

#ifdef _DMA1_CHANNEL7
#define DMA1_CHANNEL7       ((DMA_CHANNEL_T*)DMA1_CHANNEL7_BASE)
#endif /*_DMA1_CHANNEL7 */

#ifdef _DMA2_CHANNEL1
#define DMA2_CHANNEL1       ((DMA_CHANNEL_T*)DMA2_CHANNEL1_BASE)
#endif /*_DMA2_CHANNEL1 */

#ifdef _DMA2_CHANNEL2
#define DMA2_CHANNEL2       ((DMA_CHANNEL_T*)DMA2_CHANNEL2_BASE)
#endif /*_DMA2_CHANNEL2 */

#ifdef _DMA2_CHANNEL3
#define DMA2_CHANNEL3       ((DMA_CHANNEL_T*)DMA2_CHANNEL3_BASE)
#endif /*_DMA2_CHANNEL3 */

#ifdef _DMA2_CHANNEL4
#define DMA2_CHANNEL4       ((DMA_CHANNEL_T*)DMA2_CHANNEL4_BASE)
#endif /*_DMA2_CHANNEL4 */

#ifdef _DMA2_CHANNEL5
#define DMA2_CHANNEL5       ((DMA_CHANNEL_T*)DMA2_CHANNEL5_BASE)
#endif /*_DMA2_CHANNEL5 */

#ifdef _RCC
#define RCC                 ((RCC_T*)RCC_BASE)
#endif /*_RCC */

#ifdef _CRC
#define CRC                 ((CRC_T*)CRC_BASE)
#endif /*_CRC */

#ifdef _FLASH
#define FLASH               ((FLASH_T*)FLASH_R_BASE)
#define OB                  ((OB_T*)OB_BASE)
#endif /*_FLASH */

#ifdef _FSMC
#define FSMC_Bank1          ((FSMC_Bank1_T*)FSMC_Bank1_R_BASE)
#define FSMC_Bank1E         ((FSMC_Bank1E_T*)FSMC_Bank1E_R_BASE)
#define FSMC_Bank2          ((FSMC_Bank2_T*)FSMC_Bank2_R_BASE)
#define FSMC_Bank3          ((FSMC_Bank3_T*)FSMC_Bank3_R_BASE)
#define FSMC_Bank4          ((FSMC_Bank4_T*)FSMC_Bank4_R_BASE)
#endif /*_FSMC */

#ifdef _DBGMCU
#define DBGMCU              ((DBGMCU_T*)DBGMCU_BASE)
#endif /*_DBGMCU */

#ifdef _SYSTICK
#define SYSTICK             ((SYSTICK_T*)SYSTICK_BASE)
#endif /*_SYSTICK */

#ifdef _NVIC
#define NVIC                ((NVIC_T*)NVIC_BASE)
#define SCB                 ((SCB_T*)SCB_BASE)
#endif /*_NVIC */


/*
 * GPIO BB MODE
 *
 */

#define GPIOA0SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384)) = 1
#define GPIOA1SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOA2SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOA3SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOA4SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOA5SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOA6SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOA7SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOA8SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOA9SET       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOA10SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOA11SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOA12SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOA13SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOA14SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOA15SET      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOA_CLR		ODR
#define GPIOA0CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384)) = 0
#define GPIOA1CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOA2CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOA3CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOA4CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOA5CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOA6CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOA7CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOA8CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOA9CLR       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOA10CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOA11CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOA12CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOA13CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOA14CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOA15CLR      *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOA_IN		IDR
#define GPIOA0IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256)) = 1
#define GPIOA1IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOA2IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOA3IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOA4IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOA5IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOA6IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOA7IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOA8IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOA9IN        *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOA10IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOA11IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOA12IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOA13IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOA14IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOA15IN       *((volatile unsigned long*)(GPIOA_BASE + 0x2000000 + 256 + 60)) = 1

//GPIOB_SET		ODR
#define GPIOB0SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384)) = 1
#define GPIOB1SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOB2SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOB3SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOB4SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOB5SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOB6SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOB7SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOB8SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOB9SET       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOB10SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOB11SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOB12SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOB13SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOB14SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOB15SET      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOB_CLR		ODR
#define GPIOB0CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384)) = 0
#define GPIOB1CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOB2CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOB3CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOB4CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOB5CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOB6CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOB7CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOB8CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOB9CLR       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOB10CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOB11CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOB12CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOB13CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOB14CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOB15CLR      *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOB_IN		IDR
#define GPIOB0IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256)) = 1
#define GPIOB1IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOB2IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOB3IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOB4IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOB5IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOB6IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOB7IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOB8IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOB9IN        *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOB10IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOB11IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOB12IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOB13IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOB14IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOB15IN       *((volatile unsigned long*)(GPIOB_BASE + 0x2000000 + 256 + 60)) = 1


//GPIOC_SET		ODR
#define GPIOC0SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384)) = 1
#define GPIOC1SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOC2SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOC3SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOC4SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOC5SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOC6SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOC7SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOC8SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOC9SET       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOC10SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOC11SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOC12SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOC13SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOC14SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOC15SET      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOC_CLR		ODR
#define GPIOC0CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384)) = 0
#define GPIOC1CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOC2CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOC3CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOC4CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOC5CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOC6CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOC7CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOC8CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOC9CLR       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOC10CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOC11CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOC12CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOC13CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOC14CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOC15CLR      *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOC_IN		IDR
#define GPIOC0IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256)) = 1
#define GPIOC1IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOC2IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOC3IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOC4IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOC5IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOC6IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOC7IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOC8IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOC9IN        *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOC10IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOC11IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOC12IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOC13IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOC14IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOC15IN       *((volatile unsigned long*)(GPIOC_BASE + 0x2000000 + 256 + 60)) = 1


//GPIOD_SET		ODR
#define GPIOD0SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384)) = 1
#define GPIOD1SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOD2SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOD3SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOD4SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOD5SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOD6SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOD7SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOD8SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOD9SET       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOD10SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOD11SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOD12SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOD13SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOD14SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOD15SET      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOD_CLR		ODR
#define GPIOD0CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384)) = 0
#define GPIOD1CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOD2CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOD3CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOD4CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOD5CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOD6CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOD7CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOD8CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOD9CLR       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOD10CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOD11CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOD12CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOD13CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOD14CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOD15CLR      *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOD_IN		IDR
#define GPIOD0IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256)) = 1
#define GPIOD1IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOD2IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOD3IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOD4IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOD5IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOD6IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOD7IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOD8IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOD9IN        *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOD10IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOD11IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOD12IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOD13IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOD14IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOD15IN       *((volatile unsigned long*)(GPIOD_BASE + 0x2000000 + 256 + 60)) = 1


//GPIOE_SET		ODR
#define GPIOE0SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384)) = 1
#define GPIOE1SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOE2SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOE3SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOE4SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOE5SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOE6SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOE7SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOE8SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOE9SET       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOE10SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOE11SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOE12SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOE13SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOE14SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOE15SET      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOE_CLR		ODR
#define GPIOE0CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384)) = 0
#define GPIOE1CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOE2CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOE3CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOE4CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOE5CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOE6CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOE7CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOE8CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOE9CLR       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOE10CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOE11CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOE12CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOE13CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOE14CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOE15CLR      *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOE_IN		IDR
#define GPIOE0IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256)) = 1
#define GPIOE1IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOE2IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOE3IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOE4IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOE5IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOE6IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOE7IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOE8IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOE9IN        *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOE10IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOE11IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOE12IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOE13IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOE14IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOE15IN       *((volatile unsigned long*)(GPIOE_BASE + 0x2000000 + 256 + 60)) = 1


//GPIOF_SET		ODR
#define GPIOF0SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384)) = 1
#define GPIOF1SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOF2SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOF3SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOF4SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOF5SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOF6SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOF7SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOF8SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOF9SET       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOF10SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOF11SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOF12SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOF13SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOF14SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOF15SET      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOF_CLR		ODR
#define GPIOF0CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384)) = 0
#define GPIOF1CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOF2CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOF3CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOF4CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOF5CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOF6CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOF7CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOF8CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOF9CLR       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOF10CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOF11CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOF12CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOF13CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOF14CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOF15CLR      *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOF_IN		IDR
#define GPIOF0IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256)) = 1
#define GPIOF1IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOF2IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOF3IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOF4IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOF5IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOF6IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOF7IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOF8IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOF9IN        *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOF10IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOF11IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOF12IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOF13IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOF14IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOF15IN       *((volatile unsigned long*)(GPIOF_BASE + 0x2000000 + 256 + 60)) = 1

//GPIOG_SET		ODR
#define GPIOG0SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384)) = 1
#define GPIOG1SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 4)) = 1
#define GPIOG2SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 8)) = 1
#define GPIOG3SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 12)) = 1
#define GPIOG4SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 16)) = 1
#define GPIOG5SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 20)) = 1
#define GPIOG6SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 24)) = 1
#define GPIOG7SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 28)) = 1
#define GPIOG8SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 32)) = 1
#define GPIOG9SET       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 36)) = 1
#define GPIOG10SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 40)) = 1
#define GPIOG11SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 44)) = 1
#define GPIOG12SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 48)) = 1
#define GPIOG13SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 52)) = 1
#define GPIOG14SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 56)) = 1
#define GPIOG15SET      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 60)) = 1

//GPIOG_CLR		ODR
#define GPIOG0CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384)) = 0
#define GPIOG1CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 4)) = 0
#define GPIOG2CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 8)) = 0
#define GPIOG3CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 12)) = 0
#define GPIOG4CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 16)) = 0
#define GPIOG5CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 20)) = 0
#define GPIOG6CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 24)) = 0
#define GPIOG7CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 28)) = 0
#define GPIOG8CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 32)) = 0
#define GPIOG9CLR       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 36)) = 0
#define GPIOG10CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 40)) = 0
#define GPIOG11CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 44)) = 0
#define GPIOG12CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 48)) = 0
#define GPIOG13CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 52)) = 0
#define GPIOG14CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 56)) = 0
#define GPIOG15CLR      *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 384 + 60)) = 0

//GPIOG_IN		IDR
#define GPIOG0IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256)) = 1
#define GPIOG1IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 4)) = 1
#define GPIOG2IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 8)) = 1
#define GPIOG3IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 12)) = 1
#define GPIOG4IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 16)) = 1
#define GPIOG5IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 20)) = 1
#define GPIOG6IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 24)) = 1
#define GPIOG7IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 28)) = 1
#define GPIOG8IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 32)) = 1
#define GPIOG9IN        *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 36)) = 1
#define GPIOG10IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 40)) = 1
#define GPIOG11IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 44)) = 1
#define GPIOG12IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 48)) = 1
#define GPIOG13IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 52)) = 1
#define GPIOG14IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 56)) = 1
#define GPIOG15IN       *((volatile unsigned long*)(GPIOG_BASE + 0x2000000 + 256 + 60)) = 1







#endif /* __STM32F10x_REG_H */

