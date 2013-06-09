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

	while (!(RCC->CR.B.HSERDY == 1)) ;  //���HSEʱ���Ƿ��ȶ�
	RCC->CFGR.B.HPRE = 0;             //AHBԤ��Ƶϵ��// 0����Ƶ
	RCC->CFGR.B.PPRE2 = 0;            //APB2Ԥ��Ƶϵ��//0����Ƶ
	RCC->CFGR.B.PPRE1 = 4;            //APB1Ԥ��Ƶϵ��100��HCLK 2��Ƶ//APB1 ������36MHz
	RCC->CFGR.B.ADCPRE = 1;           //ADCԤ��Ƶϵ��//01��PCLK2 4��Ƶ����ΪADCʱ��
	RCC->CFGR.B.PLLSRC = 1;           //ѡ��HSE����HSI/2��ΪPLL����//	1��HSEʱ����ΪPLL����ʱ�ӡ�
	RCC->CFGR.B.PLLXTPRE = 0;         //HSE��Ƶ��ΪPLL����
	//0��HSE����Ƶ
	//1��HSE 2��Ƶ
	RCC->CFGR.B.PLLMUL = 7;           //PLL��Ƶ����//0111��PLL 9��Ƶ���
	//PLLCLK = 8MHz * 9 = 72 MHz
	RCC->CR.B.PLLON = 1;              //ʹ��PLL//
	while (!(RCC->CR.B.PLLRDY == 1)) ;  //���PLL�Ƿ�׼�����//

	FLASH->ACR.B.LATENCY = 2;         //000����ȴ�״̬���� 0 < SYSCLK < 24MHz
	//001��һ���ȴ�״̬���� 24MHz < SYSCLK < 48MHz
	//010�������ȴ�״̬���� 48MHz < SYSCLK < 72MHz

	RCC->CFGR.B.SW = 2;               //ѡ��PLL�����Ϊϵͳʱ��//	10��PLL�����Ϊϵͳʱ�ӣ�
	while (!(RCC->CFGR.B.SWS == 2)) ;  //���PLL�Ƿ��Ѿ���Ϊϵͳʱ��//  10��PLL�����Ϊϵͳʱ�ӣ�


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

