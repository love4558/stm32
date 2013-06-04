/*------------------------------------------------------
   FILE NAME   : dac.h
   DESCRIPTION : nvic driver file header
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/
#ifndef __dac_h__
#define __dac_h__

//------------------- Define ---------------------------//



#define VREF 2.482

//----------------- Typedef------------------------------//

typedef  struct {
	int (* initialize)(void);
	int (* set)(float);
}DA_T;

//----------------- Extern ------------------------------//

extern DA_T dac;


#endif //__dac_h__

