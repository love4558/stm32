/*
 * FILE								: nvic
 * DESCRIPTION				: This file is iHMI43 nvic driver file header.
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

//-----------------define-------------------------------//

#ifndef __nvic_h__
#define __nvic_h__

//-----------------Include files-------------------------//

//----------------- Typedef------------------------------//

typedef  struct {
	int (* initialize)(void);
}SYSNVIC_T;

//----------------- Extern ------------------------------//

extern SYSNVIC_T nvic;

#endif //__nvic_h__
