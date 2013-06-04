/*------------------------------------------------------
   FILE NAME   : systick.h
   DESCRIPTION : systick driver file header
   VERSION     : 0.0.0 (C)XiaomaGee
   AUTHOR      : XiaomaGee
   CREATE DATE : 2010-6-3
   MODIFY DATE :
   LOGS        :-\
   --------------------------------------------------------*/
#ifndef __systick_h__
#define __systick_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef -----------------------------//
#define EVENT_CLEAR     0


typedef  struct {
	int (* initialize)(void);
	int flash_trig;
}SYS_TICK_T;


//----------------- Extern ------------------------------//

extern SYS_TICK_T systick;
extern int event;
extern int flash_trig;
extern const int f_event_queue[];


#endif //__systick_h__


