#ifndef __ADC_H__
#define __ADC_H__

//#include "..\include\hardware.h"
//#include "..\include\config.h"
/*-----------------------------------------------------------------------------
 *  Macro
 *-----------------------------------------------------------------------------*/
//8¸öADÍ¨µÀ
#define CHANNEL0        0
#define CHANNEL1        1
#define CHANNEL2        2
#define CHANNEL3        3
#define CHANNEL4        4
#define CHANNEL5        5
#define CHANNEL6        6
#define CHANNEL7        7

#define CH_AC   2
#define CH_DC   3

typedef  struct {
	int (* initialize)(void);
	int (* read)(int);
	float value;
}SYS_ADC_T;

extern SYS_ADC_T adc;


#endif //__ADC_H__
