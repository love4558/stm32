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
#include "target.h"
#include "config.h"
#include <string.h>
#include <stdlib.h>


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
    TgtEnableGlobalInterrupt (FALSE);

    // init target (portpins, ...)
    TgtInit ();

    #ifdef INIT_SERIAL
    {
        // init the serial port
        TgtInitSerial ();
    }
    #endif

    // init the system timer
    TgtInitTimer ();

    // init the CAN ISR
    TgtInitCanIsr ();

    // enable global interrupts
    TgtEnableGlobalInterrupt (TRUE);
	SendChar("hello world\n");

	while (1) {
	}
}

