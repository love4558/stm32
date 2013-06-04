/*
 * FILE								: fsmc.c
 * DESCRIPTION				: This file is iCore fsmc driver.
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

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\fsmc.h"

//---------------- Function Prototype -------------------//

static int initialize(void);


//---------------- Variable -----------------------------//

FSMC_T fsmc = {
	.initialize = initialize
};


//-----------------Function------------------------------//
/*
 * Name										: initialize
 * Description						: ---
 * Author									: XiaomaGee.
 *
 * History
 * ----------------------
 * Rev										: 0.00
 * Date										: 03/05/2012
 *
 * create.
 * ----------------------
 */
static int initialize(void)
{
	GPIOD->CRH.W = 0xbbbbbbbb;
	GPIOD->CRL.W = 0xbbbbbbbb;

	GPIOE->CRH.W = 0xbbbbbbbb;
	GPIOE->CRL.W = 0xbbbbbbbb;

	FSMC_Bank1->BCR1 &= ~(1 << 1 | 1 << 2 | 1 << 3);

	FSMC_Bank1->BCR1 |= 1 << 14; //EXTMOD

	FSMC_Bank1->BTR1 = 0x606;

	FSMC_Bank1E->BWTR1 = 0X606;

	return 0;
}


