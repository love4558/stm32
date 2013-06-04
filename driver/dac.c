/*
 * FILE								: dac.c
 * DESCRIPTION				: --
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
#include "..\include\dac.h"

//---------------- Function Prototype -------------------//

static int initialize(void);
static int set(float);


//---------------- Variable -----------------------------//

DA_T dac = {
	.initialize = initialize,
	.set = set
};

//-----------------Function------------------------------//
/*
 * Name								: initialize
 * Description				: ---
 * Author							: XiaomaGee.
 *
 * History
 * ----------------------
 * Rev								: 0.00
 * Date								: 03/05/2012
 *
 * create.
 * ----------------------
 */
static int
initialize(void)
{
	RCC->APB1ENR.B.DACEN = 1;

	GPIOA->CRL.B.MODE4 = 0X3;         //PA4 as DAC output
	GPIOA->CRL.B.CNF4 = 2;

	DAC->CR.B.TEN1 = 1;
	DAC->CR.B.BOFF1 = 1;

	DAC->CR.B.TSEL1 = 7;              //software trig
	DAC->CR.B.EN1 = 1;

	return 0;
}
/*
 * Name										: set
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
set(float value)
{
	unsigned short int i;

	value /= 2.481;
	value *= 4095;
	i = value;

	DAC->DHR12R1.B.DACC1DHR = i;
	DAC->SWTRIGR.B.SWTRIG1 = 1;

	return 0;
}
