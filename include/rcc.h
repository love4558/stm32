/*
 * FILE								: rcc.h
 * DESCRIPTION				: This file is iHMI43 rcc driver file header.
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


//-----------------Define--------------------------------//

#ifndef __rcc_h__
#define __rcc_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Typedef------------------------------//

typedef  struct {
	int (* initialize)(void);
}SYS_RCC_T;

//----------------- Extern ------------------------------//

extern SYS_RCC_T rcc;

#endif //__rcc_h__

