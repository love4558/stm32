/*
 * FILE								: fpga.c
 * DESCRIPTION				: This file is iCore fpga(fsmc) driver.
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
#include "..\include\fpga.h"

//---------------- Function Prototype -------------------//

static int initialize(void);


//---------------- Variable -----------------------------//

FPGA_T fpga = {
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
	fsmc.initialize();

	return 0;
}


