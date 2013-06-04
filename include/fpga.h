/*
 * FILE								: fpga.h
 * DESCRIPTION				: This file is iCore fpga file header.
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
#ifndef __fpga_h__
#define __fpga_h__

//-----------------Include files-------------------------//

#include "..\include\fsmc.h"
//----------------- Define ------------------------------//

#define fpga_write(offset, data) *((volatile unsigned short int*)(CS0_BASE + (offset << 17))) = data

#define fpga_read(offset)       *((volatile unsigned short int*)(CS0_BASE + (offset << 17)))

//----------------- Typedef -----------------------------//
typedef struct {
	int (* initialize)(void);
}FPGA_T;

//---------------- Extern -------------------------------//

extern FPGA_T fpga;

#endif //__fpga_h__
