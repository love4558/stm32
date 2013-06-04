/*
 * FILE								: key.c
 * DESCRIPTION				: This file is iCore key driver.
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
#include "..\include\systick.h"
#include "..\include\key.h"

#include <stdlib.h>
#include <string.h>

//---------------- Function Prototype -------------------//

static int initialize(void);
static int read(void);

//---------------- Variable -----------------------------//

KEY_T key = {
	.initialize = initialize,
	.read = read
};
int event = 0;

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
static int
initialize(void)
{
	PD2_INPUT;
	PD3_INPUT;
	PD6_INPUT;

	return 0;
}
/*
 * Name										: read
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
static int
read(void)
{
	if ((GPIOD->IDR.W & 1 << 2) == 0) return KEYA;
	else if ((GPIOD->IDR.W & 1 << 3) == 0) return KEYB;
	else if ((GPIOD->IDR.W & 1 << 6) == 0) return KEYC;
	else return 0;
}
