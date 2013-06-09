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
#include "config.h"

#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"

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
	usart1.initialize(115200);

  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();

	while (1) {
	}
}

