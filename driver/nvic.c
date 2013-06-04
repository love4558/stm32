/*
 * FILE								: nvic.c
 * DESCRIPTION				: This file is iHMI43 nvic driver demo.
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
#include "..\include\nvic.h"

//---------------- Function Prototype -------------------//

static int initialize(void);

//---------------- Variable -----------------------------//

SYSNVIC_T nvic = {
	.initialize = initialize,
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
	SCB->VTOR.W = ((unsigned long)0x08000000); //Set the Vector Table base location at 0x08000000

	NVIC->IPR10.W = 0x00000000;

	NVIC->ISER2.B.USART1_ = 1;

	return 0;
}


