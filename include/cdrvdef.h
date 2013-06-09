/****************************************************************************

  (c) SYSTEC electronic GmbH, D-07973 Greiz, August-Bebel-Str. 29
      www.systec-electronic.de

  Project:      CANopen V5

  Description:  default definitions for CAN driver module

  -------------------------------------------------------------------------

                $RCSfile: Cdrvdef.h,v $

                $Author: R.Dietzsch $

                $Revision: 1.9 $  $Date: 2010/02/24 12:51:06 $

                $State: Exp $

                Build Environment:
                    ...

  -------------------------------------------------------------------------

  Revision History:

****************************************************************************/


#ifndef _CDRVDEF_H_
#define _CDRVDEF_H_


// =========================================================================
// types and enums
// =========================================================================

// -------------------------------------------------------------------------
// type for faster access to varalbles (depends on target system)
// -------------------------------------------------------------------------
// 14.02.03 r.d.:
// Es wurde beschlossen, den Typ tFast nach tFastByte umzubenennen. Ich
// lasse jedoch den Typ tFast noch bestehen, bis alle anderen Dateien
// umgestellt sind.

#if ((DEV_SYSTEM & _DEV_MASK_BITCOUNT) == _DEV_BIT8_)

    typedef BYTE tFast;
    typedef BYTE tFastByte;
    typedef WORD tFastWord;

#elif ((DEV_SYSTEM & _DEV_MASK_BITCOUNT) == _DEV_BIT16_)

    typedef WORD tFast;
    typedef WORD tFastByte;
    typedef WORD tFastWord;

#elif ((DEV_SYSTEM & _DEV_MASK_BITCOUNT) == _DEV_BIT32_)

    typedef DWORD tFast;
    typedef DWORD tFastByte;
    typedef DWORD tFastWord;

#else

    #error 'ERROR: tFastByte not defined!'

#endif


// -------------------------------------------------------------------------
// values vor instance state in CAN driver instance table
// -------------------------------------------------------------------------

typedef tFastByte tCdrvInstState;

#define kCdrvInstStateUnused    0
#define kCdrvInstStateDeleted   1
#define kCdrvInstStateUsed      0xFF


// -------------------------------------------------------------------------
// type for index of CAN message buffer
// -------------------------------------------------------------------------

typedef tFastByte tCdrvBuffIndex;


// -------------------------------------------------------------------------
// type for the CAN-Identifiere
// -------------------------------------------------------------------------

#define CAN20A      1
#define CAN20B      2

#if (CDRV_CAN_SPEC == CAN20B)

    typedef DWORD tCanId;

#else

    typedef tFastWord tCanId; 

#endif



#endif //_CDRVDEF_H_

// EOF
