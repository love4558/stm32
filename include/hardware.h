/*
 * FILE								: hardware.h
 * DESCRIPTION				: This file is iCore hardware file header.
 * Author							: XiaomaGee@Gmail.com
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								: 03/05/2012
 *
 * create.
 * --------------------
 */

//-----------------define-------------------------------//

#ifndef __hardware_h__
#define __hardware_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//-------------- --- Define -----------------------------//

#define U_ID0   *((volatile unsigned long*)(0X1FFFF7E8))
#define U_ID1   *((volatile unsigned long*)(0X1FFFF7E8 + 4))
#define U_ID2   *((volatile unsigned long*)(0X1FFFF7E8 + 8))

#define  LED_OUTPUT       GPIOC->CRH.B.MODE10 = 0X3; \
	GPIOC->CRH.B.CNF10 = 0

#define LED_ON          GPIOC->BSRR.B.SETIO10 = 1
#define LED_OFF         GPIOC->BSRR.B.CLRIO10 = 1



#endif //__hardware_h__
















