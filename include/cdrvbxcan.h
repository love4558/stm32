/****************************************************************************

  (c) SYSTEC electronic GmbH, D-07973 Greiz, August-Bebel-Str. 29
      www.systec-electronic.com

  Project:      CAN driver

  Description:  interface for CAN driver for STM32F bxCAN

  -------------------------------------------------------------------------

                $RCSfile: CdrvbxCAN.h,v $

                $Author: R.Dietzsch $

                $Revision: 1.2 $  $Date: 2011/03/21 13:28:24 $

                $State: Exp $

                Build Environment:
                    Keil RealView

  -------------------------------------------------------------------------

  Revision History:

  2010/03/11 a.s.:  start of implementation

****************************************************************************/

#ifndef _CDRVBXCAN_H_
#define _CDRVBXCAN_H_


// =========================================================================
// includes
// =========================================================================


// =========================================================================
// CAN driver specific defines have to be redefined with generic defines
// =========================================================================

#define CDRV_AUTO_RTR         FALSE

// check the count of instances
#if (CDRV_MAX_INSTANCES > COP_MAX_INSTANCES)
    #error 'ERROR: to many instances in CAN driver'
#endif

#if (CDRV_MAX_INSTANCES > 2)
    #error 'ERROR: More than two Instance is not testet !'
#endif

#if (CDRV_USED_CAN_CONTROLLER > 1)
    #error 'ERROR: please set correct define for used CAN-controller !'
#endif

#if ((TARGET_HARDWARE & TGT_ADD_MASK_) == TGT_ADD_ISTM32F_BXCAN)
    #if ( ((TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_PL) || ((TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_CL))
    #else
        #error 'ERROR: You can not use this driver on the selected hardware'
    #endif
#else
    #error 'ERROR: You can not use this driver on the selected hardware'
#endif

//--------------------------------------------------------------------------

#ifndef CDRVBXCAN_USE_USERBUFF
    #define CDRVBXCAN_USE_USERBUFF  FALSE
#endif

// Enable or disable the automatic wake-up mode.
// This parameter can be set either to TRUE or FALSE in CopCfg.h.
#ifndef CDRVBXCAN_USE_AWUM
    #define CDRVBXCAN_USE_AWUM      FALSE
#endif

// Enable or disable the no-automatic retransmission mode.
// This parameter can be set either to TRUE or FALSE in CopCfg.h.
#ifndef CDRVBXCAN_USE_NART
    #define CDRVBXCAN_USE_NART      FALSE
#endif

// Enable or disable the time triggered communication mode.
// This parameter can be set either to TRUE or FALSE in CopCfg.h.
#ifndef CDRVBXCAN_USE_TTCM
    #define CDRVBXCAN_USE_TTCM      FALSE
#endif


// =========================================================================
// function names have to be renamed if number of instances of CAN driver
// is not equal to number of instances of CAN open
// =========================================================================

#if (COP_USE_CDRV_FUNCTION_POINTER != FALSE)

    #define CdrvInit                CdrvBxCanInit
    #define CdrvAddInstance         CdrvBxCanAddInstance
    #define CdrvDeleteInstance      CdrvBxCanDeleteInstance
    #define CdrvSetBaudrate         CdrvBxCanSetBaudrate
    #define CdrvReset               CdrvBxCanReset
    #define CdrvClearRtr            CdrvBxCanClearRtr
    #define CdrvDefineCanId         CdrvBxCanDefineCanId
    #define CdrvUndefineCanId       CdrvBxCanUndefineCanId
    #define CdrvWriteMsg            CdrvBxCanWriteMsg
    #define CdrvReadMsg             CdrvBxCanReadMsg
    #define CdrvReleaseMsg          CdrvBxCanReleaseMsg
    #define CdrvUpdateMsg           CdrvBxCanUpdateMsg
    #define CdrvInterruptHandler    CdrvBxCanInterruptHandler
    #define CdrvGetStatus           CdrvBxCanGetStatus
    #define CdrvResetStatus         CdrvBxCanResetStatus
    #define CdrvGetDiagnostic       CdrvBxCanGetDiagnostic

#endif


// =========================================================================
// this registers are defined for the STM32F bxCAN
// =========================================================================

#define     __IO    volatile

/*------- CAN TxMailBox -----------*/
typedef struct
{
    __IO DWORD TIR;
    __IO DWORD TDTR;
    __IO DWORD TDLR;
    __IO DWORD TDHR;
}
tTxMailBox;

/*------- CAN FIFOMailBox -----------*/
typedef struct
{
    __IO DWORD RIR;
    __IO DWORD RDTR;
    __IO DWORD RDLR;
    __IO DWORD RDHR;
}
tRxMailBox;

/*------- CAN Filter Register -----------*/

typedef struct
{
    __IO DWORD  m_dwFR1;
    __IO DWORD  m_dwFR2;
}
tFilterReg;

/*------- CAN Register -----------*/
typedef struct
{
    __IO DWORD MCR;
    __IO DWORD MSR;
    __IO DWORD TSR;
    __IO DWORD RF0R;
    __IO DWORD RF1R;
    __IO DWORD IER;
    __IO DWORD ESR;
    __IO DWORD BTR;
         DWORD RESERVED0[88];
    tTxMailBox sTxMailBox[3];
    tRxMailBox sFIFOMailBox[2];
         DWORD RESERVED1[12];
    __IO DWORD FMR;
    __IO DWORD FM1R;
         DWORD RESERVED2;
    __IO DWORD FS1R;
         DWORD RESERVED3;
    __IO DWORD FFA1R;
         DWORD RESERVED4;
    __IO DWORD FA1R;
         DWORD RESERVED5[8];

#if ((TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_PL)
    // 14 filter banks (CAN1) in STM32 performance line devices
    tFilterReg sFilterRegister[14];
#endif

#if ((TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_CL)
    // 28 filter banks shared between CAN1 and CAN2 in STM32 connectivity line devices
    tFilterReg sFilterRegister[28];
#endif /* (CDRV_MAX_INSTANCES < 2) */
}
tCanRegister;


// =========================================================================
// this base addresses are defined for the STM32FbxCAN CAN-Controller
// =========================================================================

#define CAN1_BASE_ADR               (0x40000000 + 0x6400)
#define CAN2_BASE_ADR               (0x40000000 + 0x6800)

#define FIFO0                       0   // CAN FIFO0 is used to receive
                                        // messages to low priority buffer
#define FIFO1                       1   // CAN FIFO1 is used to receive
                                        // messages to high priority buffer

// =========================================================================
// define the filter bank start number for the second instance
// =========================================================================
// In connectivity line devices the bxCAN Controller provides 28 configurable
// and scalable filter banks (27-0) to the application. In other devices the
// bxCAN Controller provides 14 configurable and scalable filter banks (13-0)
// to the application in order to receive only the messages the software needs.

#if ((TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_CL)

    #define NO_OF_FILTERS           (28)

    #if (CDRV_MAX_INSTANCES < 2)
        // If only one CDRV instance used then the number of
        // available filter banks depends from the controller
        // derivate. In Connectivity line 28 filter banks are
        // available instead of 14 filter banks in performance
        // line.
        // only CAN0 = CDRV instance 0
        // CL: 28 filter banks, 0 .. 26 can used for the first
        //     bxCAN controller, filter bank 27 reserved to
        //     second bxCAN controller
        // PL: 14 filter banks
        #define CAN1_MAX_FILTERS    (1)
    #else
        //  We reserved a number of filter banks to the second
        //  bxCAN controller.
        #define CAN1_MAX_FILTERS    (14)
    #endif

#else
    #define NO_OF_FILTERS           (14)
    #define CAN1_MAX_FILTERS        (0)
#endif

#define CAN0_START_FILTER           (0)
#define CAN1_START_FILTER           (NO_OF_FILTERS - CAN1_MAX_FILTERS)

#if (CAN0_START_FILTER != 0)
    #error 'ERROR: Start number must be 0 for the first bxCAN instance!'
#endif

#if (CAN1_START_FILTER < 1) || (CAN1_START_FILTER > 27)
    #error 'ERROR: The number of filter banks of CAN1 must be 1 .. 27.controller.
#endif


// =========================================================================
// this bits are defined for registers of the STM32F bxCAN
// =========================================================================

/* CAN Master Control Register bits */
#define MCR_INRQ            (0x00000001)    /* Initialization request */
#define MCR_SLEEP           (0x00000002)    /* Sleep mode request */
#define MCR_TXFP            (0x00000004)    /* Transmit FIFO priority */
#define MCR_RFLM            (0x00000008)    /* Receive FIFO locked mode */
#define MCR_NART            (0x00000010)    /* No automatic retransmission */
#define MCR_AWUM            (0x00000020)    /* Automatic wake up mode */
#define MCR_ABOM            (0x00000040)    /* Automatic bus-off management */
#define MCR_TTCM            (0x00000080)    /* time triggered communication */
#define MCR_RESET           (0x00008000)    /* time triggered communication */
#define MCR_DBF             (0x00010000)    /* software master reset */

/* CAN Master Status Register bits */
#define MSR_INAK            (0x00000001)    /* Initialization acknowledge */
#define MSR_WKUI            (0x00000008)    /* Wake-up interrupt */
#define MSR_SLAKI           (0x00000010)    /* Sleep acknowledge interrupt */
#define MSR_ERRI            (0x00000004)    /* Error interrupt */

/* CAN Transmit Status Register bits */
#define TSR_RQCP0           (0x00000001)    /* Request completed mailbox0 */
#define TSR_TXOK0           (0x00000002)    /* Transmission OK of mailbox0 */
#define TSR_ABRQ0           (0x00000080)    /* Abort request for mailbox0 */
#define TSR_RQCP1           (0x00000100)    /* Request completed mailbox1 */
#define TSR_TXOK1           (0x00000200)    /* Transmission OK of mailbox1 */
#define TSR_ABRQ1           (0x00008000)    /* Abort request for mailbox1 */
#define TSR_RQCP2           (0x00010000)    /* Request completed mailbox2 */
#define TSR_TXOK2           (0x00020000)    /* Transmission OK of mailbox2 */
#define TSR_ABRQ2           (0x00800000)    /* Abort request for mailbox2 */
#define TSR_TME0            (0x04000000)    /* Transmit mailbox 0 empty */
#define TSR_TME1            (0x08000000)    /* Transmit mailbox 1 empty */
#define TSR_TME2            (0x10000000)    /* Transmit mailbox 2 empty */

/* CAN Receive FIFO 0 Register bits */
#define RF0R_FULL0          (0x00000008)    /* FIFO 0 full */
#define RF0R_FOVR0          (0x00000010)    /* FIFO 0 overrun */
#define RF0R_RFOM0          (0x00000020)    /* Release FIFO 0 output mailbox */
#define RF0R_FMP0           (0x00000003)    /* FIFO 0 message pending */

/* CAN Receive FIFO 1 Register bits */
#define RF1R_FULL1          (0x00000008)    /* FIFO 1 full */
#define RF1R_FOVR1          (0x00000010)    /* FIFO 1 overrun */
#define RF1R_RFOM1          (0x00000020)    /* Release FIFO 1 output mailbox */
#define RF1R_FMP1           (0x00000003)    /* FIFO 1 message pending */

/* CAN Error Status Register bits */
#define ESR_EWGF            (0x00000001)    /* Error warning flag */
#define ESR_EPVF            (0x00000002)    /* Error passive flag */
#define ESR_BOFF            (0x00000004)    /* Bus-off flag */
#define ESR_LEC             (0x00000070)    /* LEC mask bits */
#define ESR_REC             (0xFF000000)    /* Receive Error counter */
#define ESR_TEC             (0x00FF0000)    /* Receive Error counter */

#define ESR_LEC_NO_ERR      (0)             /* No error */
#define ESR_LEC_STUFF_ERR   (1)             /* Stuff error */
#define ESR_LEC_FORM_ERR    (2)             /* Form error */
#define ESR_LEC_ACK_ERR     (3)             /* Acknowledgment Error */
#define ESR_LEC_BIT1_ERR    (4)             /* Bit recessive Error */
#define ESR_LEC_BIT0_ERR    (5)             /* Bit dominant Error */
#define ESR_LEC_CRC_ERR     (6)             /* CRC Error */
#define ESR_LEC_CLEAR_ERR   (7)             /* Set by software */

/* CAN Mailbox Transmit */
#define TMIDxR_TXRQ         (0x00000001)    /* Transmit mailbox request */
#define TMIDxR_RTR          (0x00000002)    /* Transmit mailbox RTR bit */
#define TMIDxR_IDE          (0x00000004)    /* Transmit mailbox IDE bit */

/* CAN Mailbox Receive */
#define RMIDxR_RTR          (0x00000002)    /* Receive mailbox RTR bit */
#define RMIDxR_IDE          (0x00000004)    /* Receive mailbox IDE bit */

/* CAN interrupt enbale register */
#define CAN_IT_RQCP0        (0x00000005)    /* Request completed mailbox 0 */
#define CAN_IT_RQCP1        (0x00000006)    /* Request completed mailbox 1 */
#define CAN_IT_RQCP2        (0x00000007)    /* Request completed mailbox 2 */
#define CAN_IT_TME          (0x00000001)    /* Transmit mailbox empty */
#define CAN_IT_FMP0         (0x00000002)    /* FIFO 0 message pending */
#define CAN_IT_FF0          (0x00000004)    /* FIFO 0 full */
#define CAN_IT_FOV0         (0x00000008)    /* FIFO 0 overrun */
#define CAN_IT_FMP1         (0x00000010)    /* FIFO 1 message pending */
#define CAN_IT_FF1          (0x00000020)    /* FIFO 1 full */
#define CAN_IT_FOV1         (0x00000040)    /* FIFO 1 overrun */
#define CAN_IT_EWG          (0x00000100)    /* Error warning */
#define CAN_IT_EPV          (0x00000200)    /* Error passive */
#define CAN_IT_BOF          (0x00000400)    /* Bus-off */
#define CAN_IT_LEC          (0x00000800)    /* Last error code */
#define CAN_IT_ERR          (0x00008000)    /* Error */
#define CAN_IT_WKU          (0x00010000)    /* Wake-up */
#define CAN_IT_SLK          (0x00020000)    /* Sleep */

#define CAN_ERR_INT         (CAN_IT_ERR | CAN_IT_LEC | \
                             CAN_IT_BOF | CAN_IT_EPV | \
                             CAN_IT_EWG)
#define CAN_RF0_INT         (CAN_IT_FMP0)
#define CAN_TXM_INT         (CAN_IT_TME)

#if (CDRV_USE_HIGHBUFF != FALSE)
    #define CAN_RF1_INT     (CAN_IT_FMP1)
#else
    #define CAN_RF1_INT     (0)
#endif


/* CAN Filter Master Register bits */
#define FMR_FINIT           (0x00000001)    /* Filter init mode */
#define FMR_CAN2SB          (0x00003F00)    /* CAN2 start bank */
#define FMR_MASK_DONT_CARE  (0x00000000)    /* Mask for don't care */
#define FMR_NODE_ID_MASK    (0x0000007F)


/* Time out for INAK bit */
/* The max. time depends on the selected baudrate. For a baudrate
   of 5kBit/s the time should be about 150 Bits * 1/(5kBit/s) = 30ms */
#define INAK_TIMEOUT        (0x0000FFFF)

/* Time out for SLAK bit */
#define SLAK_TIMEOUT        (0x0000FFFF)

#define CAN_ID_STD          (0)


// =========================================================================
// additional includes
// =========================================================================

#include "cdrv.h"


// =========================================================================
// macros for access to CAN controller
// =========================================================================

#if ((TARGET_HARDWARE & TGT_ADD_MASK_) == TGT_ADD_ISTM32F_BXCAN)

    //----------------------------------------------------------------------
    #if (CDRV_MAX_INSTANCES > 1) // more than one instance of Cdrv driver

        #define CCI_bxCANx_REG   ((tCanRegister*) (MCO_GLB_VAR(m_Intern.m_dwCanBase)))

    #else // (CDRV_MAX_INSTANCES > 1) // more than one instance of CANopen

        #if (CDRV_USED_CAN_CONTROLLER == 0)
            #define CCI_bxCANx_REG   ((tCanRegister*) (CAN1_BASE_ADR))
        #elif (CDRV_USED_CAN_CONTROLLER == 1)
            #define CCI_bxCANx_REG   ((tCanRegister*) (CAN2_BASE_ADR))
        #else
            #error 'Only Use CAN-Controller 0 or 1!'
        #endif // (CDRV_USED_CAN_CONTROLLER == 0/1)

    #endif //(CDRV_MAX_INSTANCES > 1) // more than one instance of CANopen

    //----------------------------------------------------------------------
    // If High priority buffer enabled then the mailboxes transmit priority is
    // defined by the identifier priority.
    #if (CDRV_USE_HIGHBUFF != FALSE)

        #define TX_HIGH_PRIO_FRM_MBOX   0
        #define TX_LOW_PRIO_FRM_MBOX    1

    #else
    // If High priority buffer disbaled then the mailboxes transmit priority
    // is defined by the order of entry request.
        #define TX_MAILBOX_0            0
        #define TX_MAILBOX_1            1
        #define TX_MAILBOX_2            2
    #endif

#else

    #error 'ERROR: Target was never implemented!'

#endif

#endif //_CDRVBXCAN_H_

// EOF
