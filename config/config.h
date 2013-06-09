/*
 * FILE								: config.h
 * DESCRIPTION				: This file is iHMI43 config file header.
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

//------------------define-------------------------------//

#ifndef __config_h__
#define __config_h__
//------------------define for CAN-------------------------------//

#define CDRV_MAX_INSTANCES		1
#define CDRVDLLEXPORT
//------------------define for USB-------------------------------//

#define ENDP1_TXADDR        (0xC0)

//-----------------Include files-------------------------//
#ifndef __GLOBAL_H__
	#define __GLOBAL_H__
	#include "global.h"
#endif

#ifndef __ERRORDEF_H__
	#define __ERRORDEF_H__
	#include "errordef.h"
#endif

#ifndef __DEBUG_H__
	#define __DEBUG_H__
	#include "debug.h"
#endif

#ifndef __CDRVDEF_H__
	#define __CDRVDEF_H__
	#include "cdrvdef.h"
#endif

#ifndef __INSTDEF_H__
	#define __INSTDEF_H__
	#include "instdef.h"
#endif

#ifndef __CDRV_H__
	#define __CDRV_H__
	#include "cdrv.h"
#endif


#ifndef __CDRVBXCAN_H__
	#define __CDRVBXCAN_H__
	#include "cdrvbxcan.h"
#endif

#ifndef __TARGET_H__
	#define __TARGET_H__
	#include "target.h"
#endif

//----------------- Typedef------------------------------//

#define BUFFER_SIZE	400
#define CPU_CLK	10000000*7

#endif //__config_h__
