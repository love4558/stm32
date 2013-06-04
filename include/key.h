/*------------------------------------------------------
   FILE NAME   : key.h
   DESCRIPTION : event file header
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/
#ifndef __key_h__
#define __key_h__

//------------------- Define ---------------------------//
#define KEYA    1
#define KEYB    2
#define KEYC    3

#define PD2_INPUT  GPIOD->CRL.B.MODE2 = 0; \
	GPIOD->CRL.B.CNF2 = 2;
#define PD3_INPUT  GPIOD->CRL.B.MODE3 = 0; \
	GPIOD->CRL.B.CNF3 = 2;
#define PD6_INPUT  GPIOD->CRL.B.MODE6 = 0; \
	GPIOD->CRL.B.CNF6 = 2;

//----------------- Typedef------------------------------//
typedef struct {
	int (* initialize)(void);
	int (* read)(void);
}KEY_T;

//----------------- Extern ------------------------------//
extern KEY_T key;
extern int event;

#endif //__key_h__
