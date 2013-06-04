/*
 * FILE								: main.c
 * DESCRIPTION				: This file is main files.
 * Author							:
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								
 *
 * create.
 * --------------------
 */

//-----------------Include files-------------------------//

#include "..\include\rcc.h"
#include "..\include\hardware.h"
#include "..\include\usart.h"
#include "..\include\terminal.h"

#include <string.h>
#include <stdlib.h>

//-----------------Function------------------------------//
/*
 * Name										: SystemInit
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

void SystemInit(void)
{
}
/*
 * Name										: main
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
int main(void)
{
	rcc.initialize();

	LED_OUTPUT;
	LED_ON;

	usart1.initialize(115200);
	terminal.initialize();

	while (1) {
		terminal.ci();
		LED_OFF;
		sleep(20);
		LED_ON;
		sleep(5);
	}
}

