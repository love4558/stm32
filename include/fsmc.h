/*
 * FILE								: fsmc.h
 * DESCRIPTION				: This file is iCore fsmc file header.
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
#ifndef __fsmc_h__
#define __fsmc_h__

//-----------------Include files-------------------------//

#include "..\include\stm32f10x_reg.h"

//----------------- Define ------------------------------//

#define CS0_BASE                        (0x60000000 + (0 << 23))
#define CS1_BASE                        (0x60000000 + (1 << 23))
#define CS2_BASE                        (0x60000000 + (2 << 23))
#define CS3_BASE                        (0x60000000 + (3 << 23))

//----------------- Typedef -----------------------------//
typedef struct {
	int (* initialize)(void);
}FSMC_T;

//---------------- Extern -------------------------------//

extern FSMC_T fsmc;


#endif //__fsmc_h__
