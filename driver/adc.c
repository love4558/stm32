/*
 * FILE								: adc.c
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

//-----------------Include files-------------------------//
#include "..\include\stm32f10x_reg.h"
#include "..\config\config.h"
#include "..\include\adc.h"
#include "..\include\usart.h"
#include "..\include\hardware.h"
#include "..\include\dac.h"

//---------------- Function prototype -------------------//

static int initialize(void);
static int read_adc(int);

//-----------------Variable------------------------------//

SYS_ADC_T adc = {
	.initialize = initialize,
	.read = read_adc
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
	RCC->CFGR.B.ADCPRE = 3; //ADCPRE：ADC预分频
	//00：PCLK2 2分频后作为ADC时钟
	//01：PCLK2 4分频后作为ADC时钟
	//10：PCLK2 6分频后作为ADC时钟
	//11：PCLK2 8分频后作为ADC时钟


	RCC->APB2ENR.B.ADC1EN = 1;

	GPIOA->CRL.B.MODE0 = 0; //Configure PA.0 (ADC Channel1) as analog input
	GPIOA->CRL.B.CNF0 = 0;

	ADC1->SMPR2.B.SMP1 = 7;

	ADC1->CR2.B.TSVREFE = 0;
	ADC1->CR1.B.AWDEN = 1;

	ADC1->CR2.B.ADON = 0;

	ADC1->CR2.B.CAL = 1;

	ADC1->CR2.B.ADON = 1;   //ADC power on

	return 0;
}
/*
 * Name										: sort
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
void sort(unsigned short int a[], int n)
{
	int i, j, t;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	}
}
/*
 * Name										: read_adc
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
read_adc(int channel)
{
	int i;
	unsigned short int dat[300];


	ADC1->SQR1.B.L = 0;
	ADC1->SQR3.B.SQ1 = channel;
	ADC1->CR2.B.EXTSEL = 7;
	ADC1->CR2.B.SWSTART = 1;
	ADC1->CR2.B.CONT = 1;
	ADC1->CR2.B.ADON = 1;   //ADC power on

	for (i = 0; i < 200; i++) {
		while (ADC1->SR.B.EOC == 0) ;
		dat[i] = ADC1->DR.W;
	}
	sort(dat, 200);


	return dat[100];
}




