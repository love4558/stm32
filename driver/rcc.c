/*
 * FILE								: rcc.c
 * DESCRIPTION				: This file is iCore rcc driver demo.
 * Author							: 
 * Copyright					:
 *
 * History
 * --------------------
 * Rev								: 0.00
 * Date								:
 *
 * create.
 * --------------------
 */

//---------------- Include files ------------------------//

#include "..\include\hardware.h"
#include "..\include\rcc.h"

//---------------- Function Prototype -------------------//

static int initialize(void);

//---------------- Variable -----------------------------//

SYS_RCC_T rcc = {
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
static int
initialize(void)
{
	RCC->CR.B.HSEON = 1;              //Enable external high-speed clock

	while (!(RCC->CR.B.HSERDY == 1)) ;  //检测HSE时钟是否稳定
	RCC->CFGR.B.HPRE = 0;             //AHB预分频系数// 0不分频
	RCC->CFGR.B.PPRE2 = 0;            //APB2预分频系数//0不分频
	RCC->CFGR.B.PPRE1 = 4;            //APB1预分频系数100：HCLK 2分频//APB1 不超过36MHz
	RCC->CFGR.B.ADCPRE = 1;           //ADC预分频系数//01：PCLK2 4分频后作为ADC时钟
	RCC->CFGR.B.PLLSRC = 1;           //选择HSE还是HSI/2作为PLL输入//	1：HSE时钟作为PLL输入时钟。
	RCC->CFGR.B.PLLXTPRE = 0;         //HSE分频作为PLL输入
	//0：HSE不分频
	//1：HSE 2分频
	RCC->CFGR.B.PLLMUL = 7;           //PLL倍频倍数//0111：PLL 9倍频输出
	//PLLCLK = 8MHz * 9 = 72 MHz
	RCC->CR.B.PLLON = 1;              //使能PLL//
	while (!(RCC->CR.B.PLLRDY == 1)) ;  //检测PLL是否准备完毕//

	FLASH->ACR.B.LATENCY = 2;         //000：零等待状态，当 0 < SYSCLK < 24MHz
	//001：一个等待状态，当 24MHz < SYSCLK < 48MHz
	//010：两个等待状态，当 48MHz < SYSCLK < 72MHz

	RCC->CFGR.B.SW = 2;               //选择PLL输出作为系统时钟//	10：PLL输出作为系统时钟；
	while (!(RCC->CFGR.B.SWS == 2)) ;  //检测PLL是否已经作为系统时钟//  10：PLL输出作为系统时钟；


	RCC->APB2ENR.B.IOPAEN = 1;      //Enable GPIOA clocks
	RCC->APB2ENR.B.IOPBEN = 1;      //Enable GPIOB clocks
	RCC->APB2ENR.B.IOPCEN = 1;      //Enable GPIOC clocks
	RCC->APB2ENR.B.IOPDEN = 1; //Enable GPIOD clocks
	RCC->APB2ENR.B.IOPEEN = 1;      //Enable GPIOE clocks

	RCC->APB2ENR.B.AFIOEN = 1;

	RCC->APB2ENR.B.USART1EN = 1;    //Enable USART clocks
	RCC->AHBENR.B.FSMCEN = 1;         //Enable FSMC clocks

	RCC->APB1ENR.B.TIM2EN = 1;
	RCC->APB2ENR.B.TIM1EN = 1;



	return 0;
}

