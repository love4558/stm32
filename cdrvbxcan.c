/****************************************************************************

  (c) SYSTEC electronic GmbH, D-07973 Greiz, August-Bebel-Str. 29
      www.systec-electronic.com

  Project:      CAN driver

  Description:  CAN driver for STM32F bxCAN-Controller

  -------------------------------------------------------------------------

                $RCSfile: CdrvbxCAN.c,v $

                $Author: R.Dietzsch $

                $Revision: 1.1 $  $Date: 2010/06/18 09:10:37 $

                $State: Exp $

                Build Environment:
                KEIL RealView

  -------------------------------------------------------------------------

  Revision History:

  2010/03/11 a.s.:  start of implementation

****************************************************************************/



/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          G L O B A L   D E F I N I T I O N S                            */
/*                                                                         */
/*                                                                         */
/***************************************************************************/

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

#if (CDRV_USE_IDVALID != FALSE)
    //  The driver supports an identifier list filter mode. This can be done
    //  by an identifier list defined in software (bit field array) or by an
    //  identifier list defined in hardware (bxCAN filter mode).
    #if (CDRV_IDINFO_ALGO == CDRV_IDINFO_ALGO_BXCAN)
        // The identifier filter is supported by hardware in bxCAN.
        #define CDRV_ID_FILTER_IN_HW    TRUE
    #elif (CDRV_IDINFO_ALGO == CDRV_IDINFO_ALGO_BITFIELD)
        // The identifier filter uses an software algorithm. This algorithm
        // supports only 11Bit identifier.
        #define CDRV_ID_FILTER_IN_SW    TRUE
    #elif (CDRV_IDINFO_ALGO == CDRV_IDINFO_ALGO_IDLISTEXT)
        // The identifier filter uses an software algorithm. This algorithm
        // supports 29Bit identifier too.
        #define CDRV_ID_FILTER_IN_SW    TRUE
    #else
        // The permitted algorithms are:
        // - CDRV_IDINFO_ALGO_BITFIELD
        // - CDRV_IDINFO_ALGO_BXCAN
        #error 'This configuration is not supported. Select the right value in file CopCfg.h.'
    #endif
#endif

#if (CDRV_USE_BASIC_CAN == FALSE)

    #error 'This configuration is not supported. Set CDRV_USE_BASIC_CAN to TRUE.'

#endif // (CDRV_USE_BASIC_CAN != FALSE)


//---------------------------------------------------------------------------
// Define the interrupt source depending of the configuration.
// If CDRVBXCAN_USE_USERBUFF != FALSE, then the second FIFO is used as
// message queue for the user defined messages.
#if (CDRVBXCAN_USE_USERBUFF != FALSE)
    #define CAN_USER_INT    CAN_RF1_INT
#else
    #define CAN_USER_INT    (0)
#endif

// If CDRV_USE_ERROR_ISR == FALSE, then only RX und TX interrupts
// are enabled.
#if (CDRV_USE_ERROR_ISR != FALSE)
    // do enable status change and error interrupt
    // so TxOK, RxOK, LEC, EWARN and BOFF generates an interrupt
    #define CAN_INTERRUPT_ENABLE   (CAN_ERR_INT  | CAN_RF0_INT | \
                                    CAN_USER_INT | CAN_TXM_INT)

#else
    // do not enable status change and error interrupt
    #define CAN_INTERRUPT_ENABLE   (CAN_RF0_INT | CAN_USER_INT | \
                                                  CAN_TXM_INT)

#endif

#define CAN1            ((tCanRegister *) CAN1_BASE_ADR)
#define CAN2            ((tCanRegister *) CAN2_BASE_ADR)


//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------

// struct for internal variables which depends on CAN driver
typedef struct
{
    DWORD m_dwOldState;
    DWORD m_dwChannelState;

    #if (CDRV_MAX_INSTANCES > 1)
        DWORD    m_dwCanBase;
    #endif // (CDRV_MAX_INSTANCES > 1)

    CDRV_DEFINE_LAST_TX (tCdrvMsg MEM* m_pLastLowMsg)

    #if (CDRV_USE_HIGHBUFF != FALSE)
    CDRV_DEFINE_LAST_TX (tCdrvMsg MEM* m_pLastHighMsg)
    #endif

} tCdrvIntern;

// This struct must have a fixed name.
// For callback access to other moduls the function needs the instance index
// of own instance because the instance pointer of the other modul is not
// known.
// Static vars, also if only temporarly used, must be defined in this struct. The
// reason is that each instance can run as each thread under RTOS!! In this
// case each thread must have the own vars (threads can run parallel).
//
// IMPORTANT:
// If more than one instance defined then define the Instance Table instead
// of globale vars! But size of instance table defines the const CDRV_MAX_INSTANCES.

// struct for instance table
INSTANCE_TYPE_BEGIN

    MCO_DECL_INSTANCE_MEMBER ()

    STATIC      tCdrvInitParam                m_InitParam;
    STATIC      tCdrvStatus       INST_NEAR   m_Status;
    STATIC      tCdrvIntern       INST_NEAR   m_Intern;
    STATIC      BYTE              INST_NEAR   m_fBusContact;

    #if (CDRVBXCAN_USE_USERBUFF != FALSE)
        STATIC  tCdrvBuff         INST_NEAR   m_RxBuffHigh;
    #endif

    #if (CDRV_USE_HIGHBUFF != FALSE)
        STATIC  tCdrvBuff         INST_NEAR   m_TxBuffHigh;
    #endif

    STATIC      tCdrvBuff         INST_NEAR   m_RxBuffLow;
    STATIC      tCdrvBuff         INST_NEAR   m_TxBuffLow;

    #if (CDRV_ID_FILTER_IN_SW != FALSE)

    STATIC tCdrvIdInfo     INST_FAR     m_IdInfo;

    #endif // (CDRV_ID_FILTER_IN_SW != FALSE)


INSTANCE_TYPE_END


//---------------------------------------------------------------------------
// modul globale vars
//---------------------------------------------------------------------------

#if (CDRV_MAX_INSTANCES > 1)

    // CAN-controller adresses
    // If more than one Cdrv instances used than at least two COP
    // instances must be defined. But if two COP instances defined
    // only one Cdrv instance of drivers can be used.
    // In this case of two instances of this driver the access to
    // the bxCAN parts depends from the base address of each part.
    const struct
    {
        DWORD m_dwCanBase;       // CAN Controller

    } CanControllerAdrDefine[] =
    {
        //CAN-Contr address
        { CAN1_BASE_ADR },
        { CAN2_BASE_ADR }
    };
#endif

#if (COP_MAX_INSTANCES > 1)

    // This macro replace the unspecific pointer to an instance through
    // the modul specific type for the local instance table. This macro
    // must defined in each modul.
    #define tCopPtrInstance                        tCopInstanceInfo MEM*

    // -------------------------------------------------------------------------
    // Global variables
    // There must exist also one global array. The number of entries corresponds
    // to the number of instances. For Win95, Win98, WinNT etc. one instance
    // works only in one thread. These threads are not synchronize to other
    // thread. For that reason there must not global vars!! All global vars
    // can be embedded in aCopInstanceTable_g.

    static tCopInstanceInfo MEM aCopInstanceTable_g [CDRV_MAX_INSTANCES];

#endif  // End of defining INSTANCE-VAR

// This vars is global and used for both bxCAN instances to save
// the state of filter number assignment.
static DWORD dwFilterAssignment_l[4];


//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

MCO_DEFINE_INSTANCE_FCT ()

static tCopKernel CdrvSetBaudrateIntern     (MCO_DECL_INSTANCE_PTR);
static void       CdrvWriteCanMsgToCanCtrl  (MCO_DECL_INSTANCE_PTR_ DWORD dwChannel_p, tCdrvMsg MEM* pCanMsg_p);
static void       CdrvCheckTransmitLow      (MCO_DECL_INSTANCE_PTR_ DWORD dwChannel_p);
static void       CdrvCheckErrorRegister    (MCO_DECL_INSTANCE_PTR);
static tCopKernel CdrvResetIntern           (MCO_DECL_INSTANCE_PTR_ tCdrvResetCode ResetCode_p);
static tCopKernel CdrvGetEmptyMailbox       (MCO_DECL_INSTANCE_PTR_ tMsgTyp MsgType_p, DWORD* pdwChannel_p);
static void       CdrvTxInterruptHandler    (MCO_DECL_INSTANCE_PTR);
static void       CdrvErrInterruptHandler   (MCO_DECL_INSTANCE_PTR);
static void       CdrvRxInterruptHandler    (MCO_DECL_INSTANCE_PTR);
static void       CdrvInitIdFilter          (MCO_DECL_INSTANCE_PTR_ DWORD dwAmr_p, DWORD dwAcr_p);
static void       CdrvClearInterruptState   (MCO_DECL_INSTANCE_PTR);

#if (CDRV_USE_HIGHBUFF != FALSE)
  static void     CdrvCheckTransmitHigh     (MCO_DECL_INSTANCE_PTR_ DWORD dwChannel_p);
#endif

#if (CDRV_ID_FILTER_IN_HW != FALSE)
    static tCopKernel CdrvSetIdFilter       (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p);
    static tCopKernel CdrvResetIdFilter     (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p);
#endif

#if (CDRVBXCAN_USE_USERBUFF != FALSE)
    static tCopKernel CdrvSetUserIdFilter   (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p);
    static void       CdrvRxUserIntHandler  (MCO_DECL_INSTANCE_PTR);
#endif


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
//
// Function:    CdrvInit()
//
// Description: initializes the first instance
//
// Parameters:  pInitParam_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvInit (MCO_DECL_PTR_INSTANCE_PTR_
    tCdrvInitParam MEM* pInitParam_p)
{
tCopKernel Ret;
MCO_DELETE_INSTANCE_TABLE ();

    if (pInitParam_p == NULL)
    {
        Ret = kCopSuccessful;
        goto Exit;
    }

    // create the first instance
    Ret = CdrvAddInstance (MCO_PTR_INSTANCE_PTR_
        pInitParam_p);

Exit:
    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvAddInstance()
//
// Description: adds a new instance
//
// Parameters:  pInitParam_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvAddInstance (MCO_DECL_PTR_INSTANCE_PTR_
    tCdrvInitParam MEM* pInitParam_p)
{
MCO_DECL_INSTANCE_PTR_LOCAL
tCopKernel    Ret = kCopSuccessful;
tTime         dwTimeoutAck;
//tMcbxCANParam bxCANParam;

#if (CDRV_MAX_INSTANCES > 1) // more than one instance of CAN-driver
    BYTE      bCanNo;
#endif // (CDRV_MAX_INSTANCES > 1)

    // check if pointer to instance pointer valid
    // get free instance and set the globale instance pointer
    // set also the instance addr to parameterlist
    MCO_CHECK_PTR_INSTANCE_PTR ();
    MCO_GET_FREE_INSTANCE_PTR ();
    MCO_SET_PTR_INSTANCE_PTR ();

    // -------- init instance parameters --------------------------------------------
    COP_MEMCPY (&MCO_GLB_VAR (m_InitParam), pInitParam_p, sizeof (MCO_GLB_VAR (m_InitParam)));
    //bxCANParam = MCO_GLB_VAR(m_InitParam.m_HwParam.m_McbxCANParam);

    // clear CAN driver status and sending flag
    #if (CDRV_MAX_INSTANCES > 1)
    {
        bCanNo = MCO_GLB_VAR(m_InitParam.m_HwParam.m_McbxCANParam.m_bCanNo);
        MCO_GLB_VAR(m_Intern.m_dwCanBase) = CanControllerAdrDefine[bCanNo].m_dwCanBase;
    }
    #endif // (CDRV_MAX_INSTANCES > 1)

    MCO_GLB_VAR(m_Intern.m_dwChannelState)  = 0x000000000;
    MCO_GLB_VAR(m_Intern.m_dwOldState)      = 0x000000000;
    MCO_GLB_VAR(m_Status)                   = kCdrvNoError;
    // clear flag "bus contact" to note that no bus contact is available
    MCO_GLB_VAR(m_fBusContact)              = FALSE;

    // reset all CAN message buffers
    CdrvResetIntern (MCO_INSTANCE_PTR_
        (kResetTxBuffHigh | kResetRxBuffHigh | kResetTxBuffLow | kResetRxBuffLow));

    // -------- init CAN controller -------------------------------------------------

    // set reset mode and wait until it is set
    CCI_bxCANx_REG->MCR |= MCR_RESET;
    while(CCI_bxCANx_REG->MCR & MCR_RESET);

    // exit from sleep mode
    CCI_bxCANx_REG->MCR &= ~MCR_SLEEP;

    // --------- switch to init mode ------------------------------------------------
    CCI_bxCANx_REG->MCR |= MCR_INRQ ;

    // Software sets this bit to request the CAN hardware to enter initialization mode.
    // Once software has set the INRQ bit, the CAN hardware waits until the current CAN
    // activity (transmission or reception) is completed before entering the initia-
    // lization mode. Hardware signals this event by setting the INAK bit in the CAN_MSR
    // register. Max. Timout: 150 Bits * 1/(5kBit/s) = 30ms
    dwTimeoutAck = TgtGetTickCount();

    // Wait the acknowledge for enter initialisation mode
    while (((CCI_bxCANx_REG->MSR & MSR_INAK) != MSR_INAK)
              && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

    // ...and check acknowledged
    if ((CCI_bxCANx_REG->MSR & MSR_INAK) != MSR_INAK)
    {
        Ret = kCopCdrvInitError;
        goto Exit;
    }

    // -------- init operation mode -------------------------------------------------
    // Set the automatic bus-off management
    // Notice: This requires that the flag m_fBusContact is reset when
    // the CAN controllers goes in state bus off and the firmware had detect
    // this state.
    CCI_bxCANx_REG->MCR |= MCR_ABOM;
/*    if (bxCANParam.m_CAN_ABOM == ENABLE)
    {
        CCI_bxCANx_REG->MCR |= MCR_ABOM;
    }
    else
    {
        CCI_bxCANx_REG->MCR &= ~MCR_ABOM;
    }
*/

    // Set the automatic wake-up mode
    #if (CDRVBXCAN_USE_AWUM != FALSE)
    {
        CCI_bxCANx_REG->MCR |= MCR_AWUM;
    }
    #else
    {
        CCI_bxCANx_REG->MCR &= ~MCR_AWUM;
    }
    #endif

    // Set the no automatic retransmission
    #if (CDRVBXCAN_USE_NART != FALSE)
    {
        CCI_bxCANx_REG->MCR |= MCR_NART;
    }
    #else
    {
        CCI_bxCANx_REG->MCR &= ~MCR_NART;
    }
    #endif

    // Set the receive FIFO locked mode:
    // Receive FIFO locked against overrun. Once a receive
    // FIFO is full the next incoming message will be discarded.
    // (The same proceeding like other CAN controllers).
    CCI_bxCANx_REG->MCR |= MCR_RFLM;

    #if (CDRV_USE_HIGHBUFF != FALSE)
    {
        // Set the transmit priority by identifier
        CCI_bxCANx_REG->MCR &= ~MCR_TXFP;
    }
    #else
    {
        // Set the transmit priority by transmit request order (chronologically)
        CCI_bxCANx_REG->MCR |= MCR_TXFP;
    }
    #endif

    // Set the Time triggered communication mode
    #if (CDRVBXCAN_USE_TTCM != FALSE)
    {
        CCI_bxCANx_REG->MCR |= MCR_TTCM;
    }
    #else
    {
        CCI_bxCANx_REG->MCR &= ~MCR_TTCM;
    }
    #endif


    // -------- init baudrate -------------------------------------------------------
    // set baudrate (bit timing register)
    Ret = CdrvSetBaudrateIntern (MCO_INSTANCE_PTR);
    if (Ret != kCopSuccessful)
    {
        goto Exit;
    }

    // --------- switch to normal mode ------------------------------------------------
    CCI_bxCANx_REG->MCR &= ~MCR_INRQ;
    // The software clears this bit to switch the hardware into normal mode. Once 11
    // consecutive recessive bits have been monitored on the Rx signal the CAN hardware
    // is synchronized and ready for transmission and reception. Hardware signals this
    // event by clearing the INAK bit in the CAN_MSR register.
    dwTimeoutAck = TgtGetTickCount();
    while (((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
             && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

    // ...and check acknowledged
    if ((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
    {
        Ret = kCopCdrvInitError;
        goto Exit;
    }

    // -------- init Message filter -------------------------------------------------
    // Quotation from STM32F10xxx Reference Manual (RM0008):
    // In connectivity line devices the bxCAN Controller provides 28 configurable and
    // scalable filter banks (27-0) to the application. In other devices the bxCAN
    // Controller provides 14 configurable and scalable filter banks (13-0) to the
    // application in order to receive only the messages the software needs.
    //
    // To optimize and adapt the filters to the application needs, each filter bank can
    // be scaled independently. Depending on the filter scale a filter bank provides:
    // - One 32-bit filter for the STDID[10:0], EXTID[17:0], IDE and RTR bits.
    // - Two 16-bit filters for the STDID[10:0], RTR, IDE and EXTID[17:15] bits.
    // Furthermore, the filters can be configured in mask mode or in identifier list mode.
    // We uses the filter banks in following configuration:
    // Filter bank 0: Used in mask mode, scaled as 32 bit filter
    // Filter bank 1-n: Used in identifier list mode, scaled according to the
    //                  CDRV_CAN_SPEC value.
    //                  CAN20A: scaled as 16bit filter (11 bit identifier only)
    //                  CAN20B: scaled as 32bit filter (11/29 bit identifier)

    #if (CDRV_ID_FILTER_IN_SW != FALSE)
    {
        // The default value of filter is set to accept any message. The identifier
        // is filter by an software algorithm. To reduce the interrupts because
        // unrelevant received messages the acceptance filter can restrict to
        // relevant identifier bits (for example, only identifier with nodeid included
        // are accept)
        // clear IdInfo table
        CdrvInitIdInfo (&MCO_GLB_VAR (m_IdInfo));
    }
    #endif  //  (CDRV_ID_FILTER_IN_SW != FALSE)

    // Notice: A set bit in AMR means, the ID bit is acceptated regarless
    //         of the state of ACR bit. To adapt to the meaning of filter bank
    //         bits the AMR value must be inverted.

    // set identifier filter: invert the AMR value
    CdrvInitIdFilter(MCO_INSTANCE_PTR_ ~MCO_GLB_VAR (m_InitParam.m_dwAmr), MCO_GLB_VAR (m_InitParam.m_dwAcr));

    // -------- init pointer to TX message buffer -----------------------------------
    CDRV_SAVE_LAST_TX (MCO_GLB_VAR (m_Intern.m_pLastMsg), NULL);

    #if (CDRV_USE_HIGHBUFF != FALSE)
    {
        CDRV_SAVE_LAST_TX (MCO_GLB_VAR (m_Intern.m_pLastHighMsg), NULL);
    }
    #endif

    CDRV_SAVE_LAST_TX (MCO_GLB_VAR (m_Intern.m_pLastLowMsg), NULL);

    // -------- init interrupt flags ------------------------------------------------
    // The following interrupt sources are used (CAN_IER):
    // TME:     Transmit mailbox empty interrupt
    // FMP0:    FIFO 0 message pending interrupt
    // FMP1:    FIFO 1 message pending interrupt
    // EWG:     Error warning interrupt
    // EPV:     Error passive interrupt
    // BOF:     Bus-off interrupt
    // LEC:     Last error code interrupt
    // ERR:     Error interrupt
    //
    // The following interrupt sources are not used (CAN_IER):
    // WKU:     Wake-up
    // SLK:     Sleep
    // FF0:     FIFO 0 full
    // FOV0:    FIFO 0 overrun
    // FF1:     FIFO 1 full
    // FOV1:    FIFO 1 overrun

    CCI_bxCANx_REG->IER = CAN_INTERRUPT_ENABLE;

    // enable CAN interrupt for this instance
    MCO_GLB_VAR(m_InitParam.m_fpEnableInterrupt) (TRUE);

    // -------- Declare this CANopen instance as "In use" ---------------------------
    MCO_WRITE_INSTANCE_STATE (kCdrvInstStateUsed);

Exit:
    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvDeleteInstance()
//
// Description: delete instance
//
// Parameters:  MCO_DECL_INSTANCE_PTR
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------
#if (CDRV_USE_DELETEINST_FUNC != FALSE)

tCopKernel PUBLIC CdrvDeleteInstance (MCO_DECL_INSTANCE_PTR)
{

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // disable CAN interrupt
    MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (FALSE);

    // -------- Reset CAN controller ------------------------------------------------
    // At this stage it must reset only the part of CAN controller
    // that is used for this CANopen instance.

    // set reset mode and wait until it is set
    CCI_bxCANx_REG->MCR |= MCR_RESET;
    while(CCI_bxCANx_REG->MCR & MCR_RESET);


    // -------- Declare this CANopen instance as "NOT in use" -----------------------
    MCO_WRITE_INSTANCE_STATE (kCdrvInstStateUnused);

    return kCopSuccessful;

}

#endif // (CDRV_USE_DELETEINST_FUNC != FALSE)


//---------------------------------------------------------------------------
//
// Function:    CdrvSetBaudrate()
//
// Description: sets new baudrate to CAN controller
//
// Parameters:  pBdiTable_p
//              wSizeOfBdiTab_p
//              bBdiIndex_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvSetBaudrate (MCO_DECL_INSTANCE_PTR_
    CONST void ROM* pBdiTable_p,
    WORD wSizeOfBdiTab_p,
    BYTE bBdiIndex_p)
{
tCopKernel  Ret;
tTime       dwTimeoutAck;

    // check if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // set new values to initialisation parameter structure
    MCO_GLB_VAR (m_InitParam.m_pBdiTable)     = pBdiTable_p;
    MCO_GLB_VAR (m_InitParam.m_wSizeOfBdiTab) = wSizeOfBdiTab_p;
    MCO_GLB_VAR (m_InitParam.m_BaudIndex)     = (tCdrvBaudIndex) bBdiIndex_p;

    // --------- switch to init mode ------------------------------------------------
    CCI_bxCANx_REG->MCR |= MCR_INRQ ;

    // Software sets this bit to request the CAN hardware to enter initialization mode.
    // Once software has set the INRQ bit, the CAN hardware waits until the current CAN
    // activity (transmission or reception) is completed before entering the initia-
    // lization mode. Hardware signals this event by setting the INAK bit in the CAN_MSR
    // register. Max. Timout: 150 Bits * 1/(5kBit/s) = 30ms
    dwTimeoutAck = TgtGetTickCount();

    // Wait the acknowledge for enter initialisation mode
    while (((CCI_bxCANx_REG->MSR & MSR_INAK) != MSR_INAK)
              && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

    // ...and check acknowledged
    if ((CCI_bxCANx_REG->MSR & MSR_INAK) != MSR_INAK)
    {
        Ret = kCopCdrvInitError;
        goto Exit;
    }

    // --------- set new baudrate ---------------------------------------------------
    Ret = CdrvSetBaudrateIntern (MCO_INSTANCE_PTR);

    // --------- switch to normal mode ------------------------------------------------
    CCI_bxCANx_REG->MCR &= ~MCR_INRQ;

    // The software clears this bit to switch the hardware into normal mode. Once 11
    // consecutive recessive bits have been monitored on the Rx signal the CAN hardware
    // is synchronized and ready for transmission and reception. Hardware signals this
    // event by clearing the INAK bit in the CAN_MSR register.
    dwTimeoutAck = TgtGetTickCount();
    while (((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
             && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

    // ...and check acknowledged
    if ((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
    {
        Ret = kCopCdrvInitError;
        goto Exit;
    }

Exit:
    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvReset()
//
// Description: resets specific parts of CAN driver
//              (it call internal reset function)
//
// Parameters:  MCO_DECL_INSTANCE_PTR_  = (pointer to instance)
//              ResetCode_p             = parts to reset
//
// Returns:     tCopKernel = error code
//                  from function CdrvResetIntern()
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvReset (MCO_DECL_INSTANCE_PTR_
    tCdrvResetCode ResetCode_p)
{
tCopKernel Ret;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // reset CAN controller (Interrupt has to be disabled before)
    MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (FALSE);

    // call internal reset function
    Ret = CdrvResetIntern (MCO_INSTANCE_PTR_
        ResetCode_p);

    // enable CAN interrupt
    MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);

    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvClearRtr()
//
// Description: clears RTR Channels in FullCAN drivers
//
// Parameters:  bChannel_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvClearRtr (MCO_DECL_INSTANCE_PTR_
    BYTE bChannel_p)
{

    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvDefineCanId()
//
// Description: defines a CAN-ID for receiving a CAN message form CAN controller
//
// Parameters:  pCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvDefineCanId (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* pCanMsg_p)
{
tCopKernel          Ret = kCopSuccessful;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // check messagetype
    switch (pCanMsg_p->m_MsgType & kMtbFilter)  // mask other unused bits
    {
        // -------------------------------------------------------------------
        case kMsgTypSend:
            // The channel (TX Mailbox) and the identifier used for the message
            // is defined before the message is written to mailbox.
            goto Exit; // do not carry out the code after switch()

        // -------------------------------------------------------------------
        case kMsgTypSendRtrReq:
            // The channel (TX Mailbox) and the identifier used for the message
            // is defined before the message is written to mailbox.
            // A CAN message which will be sent as Remote Request Frame
            // causes an answer frame which will be received.
            break;

        // -------------------------------------------------------------------
        case kMsgTypRecv:
            break;

        // -------------------------------------------------------------------
        case kMsgTypRecvRtrReq:
            break;

        // -------------------------------------------------------------------
        default:
            // unknown type: --->>> do nothing, because all possible types are defined
            Ret = kCopCdrvInvalidParam;
            goto Exit;
    }

    //------------------------------------------------------------------------
    // For the messages which will received prepare the incoming filter according
    // to the selected algorithm.

    #if (CDRV_ID_FILTER_IN_SW != FALSE)
    {
        // prepare IdInfo
        tIdInfo IdInfo = 0;

        //----------------------------------------------------
        #if (CDRV_USE_IDVALID != FALSE)
        {
            // set ID-Valid
            IdInfo |= kIdInfoValid;
        }
        #endif // (CDRV_USE_IDVALID != FALSE)

/*-as: This feature is not supported.
        //----------------------------------------------------
        // Is the identifier an identifier of an high priority
        // message?
        #if (CDRV_USE_HIGHBUFF != FALSE) // false -> no highbuff
        {
            // CAN message comes in high priority buffer
            if ((pCanMsg_p->m_MsgType & kMtbHighPrio) != 0)
            {
                IdInfo |= kIdInfoHighBuff;
            }
        }
        #endif // (CDRV_USE_HIGHBUFF != FALSE)
*/
        //----------------------------------------------------
        // Is identifier an extended identifier?
        #if (CDRV_CAN_SPEC == CAN20B)
        {
            // CAN message comes in high priority buffer
            if ((pCanMsg_p->m_MsgType & kMtbExtend) != 0)
            {
                IdInfo |= kIdInfoExtend;
            }
        }
        #endif

        // set IdInfo with special algorithm
        CdrvSetIdInfo (&MCO_GLB_VAR(m_IdInfo), pCanMsg_p->m_CanId, IdInfo);
    }
    #endif

    //------------------------------------------------------------------------
    // We take the identifier list to filter incoming messages. Depending on
    // the used buffer we must select the right set-function.
    #if (CDRV_ID_FILTER_IN_HW != FALSE)
    {
/*-as: This feature is not supported.
        #if (CDRV_USE_HIGHBUFF != FALSE) // false -> no highbuff
        {
            if ((pCanMsg_p->m_MsgType & kMtbHighPrio) != 0)
            {
               Ret = CdrvSetHighBuffIdFilter(MCO_INSTANCE_PTR_ pCanMsg_p->m_CanId, pCanMsg_p->m_MsgType);
               goto Exit;
            }
        }
        #endif
*/
        // To prevent that an identifier is set a further one, search and reset a
        // set value.
        CdrvResetIdFilter (MCO_INSTANCE_PTR_ pCanMsg_p->m_CanId, pCanMsg_p->m_MsgType);
        // set the new one
        Ret = CdrvSetIdFilter (MCO_INSTANCE_PTR_ pCanMsg_p->m_CanId, pCanMsg_p->m_MsgType);

        if (Ret != kCopSuccessful)
        {
            ASSERT(FALSE);
        }
    }
    #endif // (CDRV_ID_FILTER_IN_HW != FALSE)

Exit:
    return (Ret);

}


//---------------------------------------------------------------------------
//
// Function:    CdrvUndefineCanId()
//
// Description: undefines a CAN-ID for receiving a CAN message form CAN controller
//
// Parameters:  pCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvUndefineCanId (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* pCanMsg_p)
{

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE();

    #if (CDRV_ID_FILTER_IN_SW != FALSE)
    {
        // reset id info for this CAN-ID
        CdrvResetIdInfo (&MCO_GLB_VAR(m_IdInfo), pCanMsg_p->m_CanId, kIdInfoAll);
    }
    #endif

    #if (CDRV_ID_FILTER_IN_HW != FALSE)
    {
        CdrvResetIdFilter (MCO_INSTANCE_PTR_ pCanMsg_p->m_CanId, pCanMsg_p->m_MsgType);
    }
    #endif // (CDRV_ID_FILTER_IN_HW != FALSE)

    return kCopSuccessful;
}


//---------------------------------------------------------------------------
//
// Function:    CdrvWriteMsg()
//
// Description: writes a CAN message to the CAN bus or buffer
//
// Parameters:  pCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvWriteMsg (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* pCanMsg_p)
{
tCdrvBuffIndex     MaxEntries;
tCdrvBuffIndex     Index;
tCdrvMsg MEM       *pBuffer;
tCopKernel         Ret = kCopSuccessful;
DWORD              dwChannel;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // ............................................................................................
    // write CAN message to CAN controller
    // ............................................................................................

    // CAN interrupt has to disabled early because after checking m_bSending
    // can occur an interrupt although this fuction has not copied the message in buffer
    MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (FALSE);

    //-------------------------------------------------------------------------------------------
    #if (CDRV_USE_HIGHBUFF != FALSE)
    {
        if ((pCanMsg_p->m_MsgType & kMtbHighPrio) != 0)
        {
            // try to send message direct into CAN controller if buffer is empty
            if (MCO_GLB_VAR(m_TxBuffHigh.m_Count) == 0)
            {
                // If TX Mailbox/message object of CAN controller is empty
                // then copy message direct to CAN controller.
                if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMtbHighPrio, &dwChannel))
                {
                    CdrvWriteCanMsgToCanCtrl (MCO_INSTANCE_PARAM_(pInstance)  dwChannel, pCanMsg_p);

                    MCO_GLB_VAR(m_InitParam.m_fpEnableInterrupt) (TRUE);

                    Ret = kCopSuccessful;
                    goto Exit;
                }
            }

            // Buffer is not empty --> write new message to buffer
            // and increment buffer pointer and count of messages in buffer.
            // Notice: Don't change this lines! They are optimized for high speed.
            // ............................................................................................
            // check if buffer is full
            MaxEntries = MCO_GLB_VAR (m_InitParam.m_TxBuffHigh.m_MaxEntries);
            if (MCO_GLB_VAR (m_TxBuffHigh.m_Count) >= MaxEntries)
            {
                MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);
                Ret = kCopCdrvTxBuffHighOverrun;
                goto Exit;
            }

            // get index and pointer to current CAN message in buffer
            Index   = MCO_GLB_VAR (m_TxBuffHigh.m_WriteIndex);
            pBuffer = MCO_GLB_VAR (m_TxBuffHigh.m_pWritePtr);

            // copy whole struct to buffer and increment count of messages
            *pBuffer = *pCanMsg_p;
            MCO_GLB_VAR (m_TxBuffHigh.m_Count) += 1;

            // CAN interrupt can be enabled here because message is set to buffer
            // and count of messages is incremented. Read and Write index/pointer
            // are not compared. The Write buffer pointer and index can't be changed
            // by the interrupt handler.
            MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);

            // increment pointer and index
            pBuffer++;
            Index++;

            // check if end of buffer is reached - set buffer to begin if so
            if (Index >= MaxEntries)
            {
                pBuffer = MCO_GLB_VAR (m_InitParam.m_TxBuffHigh.m_pBufferBase);
                Index   = 0;
            }

            // write index and pointer back to instance tabel
            MCO_GLB_VAR (m_TxBuffHigh.m_pWritePtr)  = pBuffer;
            MCO_GLB_VAR (m_TxBuffHigh.m_WriteIndex) = Index;

//          DEBUG_TRACE0 (CDRV_DBGLVL_CDRV, "message in high buffer\n");

            goto Exit;
        }
    }
    #endif

    //-------------------------------------------------------------------------------------------
    // This part runs if the message was not processd as high priority message.
    // Try to send message direct into CAN controller if buffer is empty
    if (MCO_GLB_VAR(m_TxBuffLow.m_Count) == 0)
    {
        // If TX Mailbox/message object of CAN controller is empty
        // then copy message direct to CAN controller.
        if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMsgTypSend, &dwChannel))
        {
            CdrvWriteCanMsgToCanCtrl (MCO_INSTANCE_PARAM_(pInstance)  dwChannel, pCanMsg_p);

            // In difference to CAN controller without an transmit FIFO in hardware
            // the interrupt enable flag must release after the write to the fifo to
            // prevent that an tx interrupt is occured and overwrite the written parts
            // of new message.
            MCO_GLB_VAR(m_InitParam.m_fpEnableInterrupt) (TRUE);

            Ret = kCopSuccessful;
            goto Exit;
        }
    }

    // ............................................................................................
    // This part runs if the message was not processed as high priority message or was not written
    // direkt to the Mailbox. Now the message will be set in a TX message buffer, the buffer
    // pointer and count of messages in buffer is incremented.
    // Notice: Don't change this lines! They are optimized for high speed.
    // ...........................................................................................
    // check if buffer is full
    MaxEntries = MCO_GLB_VAR (m_InitParam.m_TxBuffLow.m_MaxEntries);
    if (MCO_GLB_VAR (m_TxBuffLow.m_Count) >= MaxEntries)
    {
        MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);
        Ret = kCopCdrvTxBuffLowOverrun;
        goto Exit;
    }

    // get index and pointer to current CAN message in buffer
    Index   = MCO_GLB_VAR (m_TxBuffLow.m_WriteIndex);
    pBuffer = MCO_GLB_VAR (m_TxBuffLow.m_pWritePtr);

    // copy whole struct to buffer and increment count of messages
    *pBuffer = *pCanMsg_p;
    MCO_GLB_VAR (m_TxBuffLow.m_Count) += 1;

    // CAN interrupt can be enabled here because message is set to buffer
    // and count of messages is incremented. Read and Write index/pointer
    // are not compared. The Write buffer pointer and index can't be changed
    // by the interrupt handler.
    MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);

    // increment pointer and index
    pBuffer++;
    Index++;

    // check if end of buffer is reached - set buffer to begin if so
    if (Index >= MaxEntries)
    {
        pBuffer = MCO_GLB_VAR (m_InitParam.m_TxBuffLow.m_pBufferBase);
        Index   = 0;
    }

    // write index and pointer back to instance tabel
    MCO_GLB_VAR (m_TxBuffLow.m_pWritePtr)  = pBuffer;
    MCO_GLB_VAR (m_TxBuffLow.m_WriteIndex) = Index;

//  DEBUG_TRACE0 (CDRV_DBGLVL_CDRV, "message in low buffer\n");


Exit:
    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvReadMsg()
//
// Description: reads a CAN message from buffer
//
// Parameters:  ppCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvReadMsg (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* MEM* ppCanMsg_p)
{
tCdrvMsg MEM* pCanMsg;
tMsgTyp       MsgTyp;
tCopKernel    Ret;

    Ret =  kCopCdrvNoMsg;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

/*-as: This feature is not supported.
    #if (CDRV_USE_HIGHBUFF != FALSE)
    // check if there are messages in high priority buffer
    // (don't change buffer pointer or count of messages in buffer)
    if (MCO_GLB_VAR (m_RxBuffHigh.m_Count) > 0)
    {
        pCanMsg = MCO_GLB_VAR (m_RxBuffHigh.m_pReadPtr);
        MsgTyp  = pCanMsg->m_MsgType | kMtbHighPrio;

        // write new message type to message entry and write pointer to calling function
        pCanMsg->m_MsgType = MsgTyp;
        *ppCanMsg_p = pCanMsg;

        Ret = kCopCdrvMsgHigh;
    }
    else
    #endif
    {
*/
    // check if there are messages in low priority buffer
    // (don't change buffer pointer or count of messages in buffer)
    if (MCO_GLB_VAR (m_RxBuffLow.m_Count) > 0)
    {
        pCanMsg = MCO_GLB_VAR (m_RxBuffLow.m_pReadPtr);
        MsgTyp  = pCanMsg->m_MsgType;

        // write new message type to message entry and write pointer to calling function
        pCanMsg->m_MsgType = MsgTyp;
        *ppCanMsg_p = pCanMsg;

        Ret = kCopCdrvMsgLow;
    }

    return Ret;
}


//---------------------------------------------------------------------------
//
// Function:    CdrvReleaseMsg()
//
// Description: updates buffer pointer after reading a CAN message from it
//
// Parameters:  pCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvReleaseMsg (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* pCanMsg_p)
{
tCdrvBuffIndex         Index;
tCdrvMsg MEM          *pBuffer;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

/*-as: This feature is not supported.
    #if (CDRV_USE_HIGHBUFF != FALSE)
    // if high priority message then increment high priority buffer
    if ((pCanMsg_p->m_MsgType & kMtbHighPrio) != 0)
    {
        // increment buffer pointer and decrement count of messages in buffer
        Index   = MCO_GLB_VAR (m_RxBuffHigh.m_ReadIndex);
        pBuffer = MCO_GLB_VAR (m_RxBuffHigh.m_pReadPtr);

        pBuffer++;
        Index++;

        if (Index >= MCO_GLB_VAR (m_InitParam.m_RxBuffHigh.m_MaxEntries))
        {
            pBuffer = MCO_GLB_VAR (m_InitParam.m_RxBuffHigh.m_pBufferBase);
            Index   = 0;
        }

        MCO_GLB_VAR (m_RxBuffHigh.m_ReadIndex) = Index;
        MCO_GLB_VAR (m_RxBuffHigh.m_pReadPtr)  = pBuffer;

        // before drecrementing counter CAN interrupt has to be disabled
        MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (FALSE);
        MCO_GLB_VAR (m_RxBuffHigh.m_Count) -= 1;
        MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);
    }
    else
    #endif
*/
    {
        // increment buffer pointer and decrement count of messages in buffer
        Index   = MCO_GLB_VAR (m_RxBuffLow.m_ReadIndex);
        pBuffer = MCO_GLB_VAR (m_RxBuffLow.m_pReadPtr);

        pBuffer++;
        Index++;

        if (Index >= MCO_GLB_VAR (m_InitParam.m_RxBuffLow.m_MaxEntries))
        {
            pBuffer = MCO_GLB_VAR (m_InitParam.m_RxBuffLow.m_pBufferBase);
            Index   = 0;
        }

        MCO_GLB_VAR (m_RxBuffLow.m_ReadIndex) = Index;
        MCO_GLB_VAR (m_RxBuffLow.m_pReadPtr)  = pBuffer;

        // before drecrementing counter CAN interrupt has to be disabled
        MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (FALSE);
        MCO_GLB_VAR (m_RxBuffLow.m_Count) -= 1;
        MCO_GLB_VAR (m_InitParam.m_fpEnableInterrupt) (TRUE);
    }

    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvUpdateMsg()
//
// Description: updates data for RTR messages
//
// Parameters:  pCanMsg_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvUpdateMsg (MCO_DECL_INSTANCE_PTR_
    tCdrvMsg MEM* pCanMsg_p)
{

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE();

    // nothing to do, because rtr are not automatically answered
    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvInterruptHandler()
//
// Description: CAN interrupt handler
//
// Parameters:  Instance Pointer
//              IsrType_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvInterruptHandler (MCO_DECL_INSTANCE_PTR_
    tCdrvIsrType IsrType_p)
{
    CDRV_START_MEASUREMENT();

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // According to the type of interrupt (RX, TX, ERROR)
    // select the interrupt handler
    switch (IsrType_p)
    {
        // -------------------------------------------------------------
        // The bxCAN have two receive FIFOs. The first FIFO (FIFO0) is
        // assigned fix to receiving messages for the LOW_BUFFER.
        case kCdrvRxIsr:
        case kCdrvRxFIFO0Isr:
            CdrvRxInterruptHandler (MCO_INSTANCE_PTR);
            break;

        // -------------------------------------------------------------
        // The bxCAN have two receive FIFOs. If CDRVBXCAN_USE_USERBUFF enabled
        // the second FIFO (FIFO1) is assigned fix to receiving messages
        // for the user defined identifier list.
        #if (CDRVBXCAN_USE_USERBUFF != FALSE)
        case kCdrvRxFIFO1Isr:
            CdrvRxUserIntHandler (MCO_INSTANCE_PTR);
            break;
        #endif

        // -------------------------------------------------------------
        case kCdrvTxIsr:
            CdrvTxInterruptHandler(MCO_INSTANCE_PTR);
            break;

        // -------------------------------------------------------------
        case kCdrvErrorIsr:
            CdrvErrInterruptHandler(MCO_INSTANCE_PTR);
            break;

        // -------------------------------------------------------------
        default:
            break;
    }

    CDRV_STOPP_MEASUREMENT();

    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvErrInterruptHandler()
//
// Description: CAN Error interrupt handler
//
// Parameters:  Instance pointer
//
// Return:      none
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvErrInterruptHandler (MCO_DECL_INSTANCE_PTR)
{

    #if (CDRV_USE_ERROR_ISR != FALSE)
    {
        // check error register of CAN controller
        CdrvCheckErrorRegister (MCO_INSTANCE_PTR);
    }
    #endif // (CDRV_USE_ERROR_ISR != FALSE)

    // Clear ERRI in register CAN_MSR
    CCI_bxCANx_REG->MSR = MSR_ERRI;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvRxInterruptHandler()
//
// Description: CAN RX interrupt handler for FIFO0
//              FIFO0 is used to receive messages to the Low priority
//              buffer.
//
// Parameters:  Instance pointer
//
// Return:      none
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvRxInterruptHandler (MCO_DECL_INSTANCE_PTR)
{
DWORD            dwCANID;
tCdrvMsg   MEM*  pMsgEntry;
tCdrvBuffIndex   MaxEntries;
tCdrvBuffIndex   Index;

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // ---------------------------------------------------------------------------
    // check if no bus contact was detected before
    if (MCO_GLB_VAR (m_fBusContact) == FALSE)
    {
        // set flag "first bus contact" in CAN driver state
        MCO_GLB_VAR (m_Status) |= kCdrvFirstBusContact;

        // set flag "bus contact" to note that this node is not the only one at the CAN bus
        MCO_GLB_VAR (m_fBusContact) = TRUE;
    }

    // ---------------------------------------------------------------------------
    // Up to three messages stored in the FIFO. Therefore the functions reads
    // the FIFO until the FIFO is empty.
    while (CCI_bxCANx_REG->RF0R & RF0R_FMP0)
    {
        // check message object for overrun ----
        if ((CCI_bxCANx_REG->RF0R & RF0R_FOVR0) != 0)
        {
            MCO_GLB_VAR(m_Status) |= kCdrvOverrun;
            // clear status flag
            CCI_bxCANx_REG->RF0R = RF0R_FOVR0;
        }

        //------------------------------------------------------------------------
        // Read message: save identifier
        if ( (RMIDxR_IDE & CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RIR) == CAN_ID_STD)
        {
            // Standard Frame Format: 11Bit identifier
            dwCANID = (DWORD)0x000007FF & (CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RIR >> 21);
        }
        else
        {
            // Extended Frame Format: 29Bit identifier
            // Is this frame format enabled?
            #if (CDRV_CAN_SPEC == CAN20B)
            {
                dwCANID = (DWORD)0x1FFFFFFF & (CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RIR >> 3);
            }
            #else
            {
                // Release FIFO 0
                CCI_bxCANx_REG->RF0R = RF0R_RFOM0;
                // Check the next message in FIFO if not empty
                continue;
            }
            #endif
        }

        //------------------------------------------------------------------------
        // Read message: check up if message object relevant to save data bytes
        #if (CDRV_ID_FILTER_IN_SW != FALSE)
        {
            tIdInfo  IdInfo;

            // Check up if message object relevant for this node
            IdInfo = CdrvGetIdInfo (&MCO_GLB_VAR(m_IdInfo), dwCANID);

            #if (CDRV_USE_IDVALID != FALSE)
            {
                // check if CAN-ID is not known for this node
                if ((IdInfo & kIdInfoValid) == 0)
                {
                    // The message object is not relevant for
                    // this node. Discard the message and check
                    // the FIFO if empty.
                    CCI_bxCANx_REG->RF0R = RF0R_RFOM0;
                    continue;
                }
            }
            #endif // (CDRV_ID_FILTER_IN_SW != FALSE)
        }
        #endif

        //------------------------------------------------------------------------
        // Read message: Check up buffer size and save message if buffer not full
        MaxEntries  = MCO_GLB_VAR(m_InitParam.m_RxBuffLow.m_MaxEntries);
        if (MCO_GLB_VAR(m_RxBuffLow.m_Count) >= MaxEntries)
        {
            MCO_GLB_VAR(m_Status) |= kCdrvRxBuffLowOverrun;
            CCI_bxCANx_REG->RF0R = RF0R_RFOM0;
            continue;
        }
        else
        {
            Index     = MCO_GLB_VAR(m_RxBuffLow.m_WriteIndex);
            pMsgEntry = MCO_GLB_VAR(m_RxBuffLow.m_pWritePtr);

            //------------------------------------------------------------------------
            // Read message: save message type
            pMsgEntry->m_MsgType = kMtbRecv;

            #if (CDRV_CAN_SPEC == CAN20B)
            // set extended flag in MsgType if set in frame formate
            if ( (RMIDxR_IDE & CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RIR) == CAN_ID_STD)
            {
                pMsgEntry->m_MsgType |= kMtbExtend;
            }
            #endif

            //------------------------------------------------------------------------
            // Read message: save CAN identifier
            pMsgEntry->m_CanId   = dwCANID;

            //------------------------------------------------------------------------
            // Read message: save DLC
            pMsgEntry->m_bSize   = (BYTE)0x0F & CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RDTR;

            //------------------------------------------------------------------------
            // Read message: save receive timestamp
            #if CDRV_TIMESTAMP != FALSE
                pMsgEntry->m_Time = TgtGetTickCount();
            #endif // CDRV_TIMESTAMP != FALSE

            //--------------------------------------------------------------------
            // Read message: save RTR Flag
            if ((BYTE)RMIDxR_RTR & CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RIR)
            {
                pMsgEntry->m_MsgType |= kMtbRtr;
            }
            //--------------------------------------------------------------------
            // Read message: save data bytes
            else
            {
                // read data bytes from CAN controller
                *((DWORD*)&pMsgEntry->m_bData[0]) = CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RDLR;
                *((DWORD*)&pMsgEntry->m_bData[4]) = CCI_bxCANx_REG->sFIFOMailBox[FIFO0].RDHR;
            }

            //--------------------------------------------------------------------
            // Read message: process SYNC message
            CDRV_CHECK_RX_MSG (pMsgEntry);

            //--------------------------------------------------------------------
            // Increment the buffer pointer
            pMsgEntry++;
            Index++;

            if (Index >= MaxEntries)
            {
                pMsgEntry = MCO_GLB_VAR(m_InitParam.m_RxBuffLow.m_pBufferBase);
                Index     = 0;
            }

            MCO_GLB_VAR(m_RxBuffLow.m_pWritePtr)  = pMsgEntry;
            MCO_GLB_VAR(m_RxBuffLow.m_WriteIndex) = Index;
            MCO_GLB_VAR(m_RxBuffLow.m_Count)     += 1;
        }

        //------------------------------------------------------------------------
        // Read message: Release FIFO 0
        CCI_bxCANx_REG->RF0R = RF0R_RFOM0;

    } // while (CCI_bxCANx_REG->RF0R & RF0R_FMP0)

}


//---------------------------------------------------------------------------
//
// Function:    CdrvRxUserIntHandler()
//
// Description: CAN RX interrupt handler for FIFO1
//              FIFO1 is used to receive messages to the user
//              buffer.
//
// Parameters:  Instance pointer
//
// Return:      none
//
// State:
//
//---------------------------------------------------------------------------

#if (CDRVBXCAN_USE_USERBUFF != FALSE)

static void CdrvRxUserIntHandler (MCO_DECL_INSTANCE_PTR)
{
DWORD            dwCANID;
tCdrvMsg   MEM*  pMsgEntry;
tCdrvBuffIndex   MaxEntries;
tCdrvBuffIndex   Index;

    // ---------------------------------------------------------------------------
    // check if no bus contact was detected before
    if (MCO_GLB_VAR (m_fBusContact) == FALSE)
    {
        // set flag "first bus contact" in CAN driver state
        MCO_GLB_VAR (m_Status) |= kCdrvFirstBusContact;

        // set flag "bus contact" to note that this node is not the only one at the CAN bus
        MCO_GLB_VAR (m_fBusContact) = TRUE;
    }

    // ---------------------------------------------------------------------------
    // Up to three messages stored in the FIFO. Therefore the functions reads
    // the FIFO until the FIFO is empty.
    while (CCI_bxCANx_REG->RF1R & RF1R_FMP1)
    {
        // check message object for overrun ----
        if ((CCI_bxCANx_REG->RF1R & RF1R_FOVR1) != 0)
        {
            MCO_GLB_VAR(m_Status) |= kCdrvOverrun;
            // clear status flag
            CCI_bxCANx_REG->RF1R = RF1R_FOVR1;
        }

        //------------------------------------------------------------------------
        // Read message: save identifier
        if ( (RMIDxR_IDE & CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RIR) == CAN_ID_STD)
        {
            // Standard Frame Format: 11Bit identifier
            dwCANID = (DWORD)0x000007FF & (CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RIR >> 21);
        }
        else
        {
            // Extended Frame Format: 29Bit identifier
            // Is this frame format enabled?
            #if (CDRV_CAN_SPEC == CAN20B)
            {
                dwCANID = (DWORD)0x1FFFFFFF & (CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RIR >> 3);
            }
            #else
            {
                // Release FIFO 0
                CCI_bxCANx_REG->RF1R = RF1R_RFOM1;
                // Check the next message in FIFO if not empty
                continue;
            }
            #endif
        }

        //------------------------------------------------------------------------
        // Read message: Check up buffer size and save message if buffer not full
        MaxEntries  = MCO_GLB_VAR(m_InitParam.m_RxBuffHigh.m_MaxEntries);
        if (MCO_GLB_VAR(m_RxBuffHigh.m_Count) >= MaxEntries)
        {
            MCO_GLB_VAR(m_Status) |= kCdrvRxBuffHighOverrun;
            CCI_bxCANx_REG->RF1R = RF1R_RFOM1;
            continue;
        }
        else
        {
            Index     = MCO_GLB_VAR(m_RxBuffHigh.m_WriteIndex);
            pMsgEntry = MCO_GLB_VAR(m_RxBuffHigh.m_pWritePtr);

            //------------------------------------------------------------------------
            // Read message: save message type
            pMsgEntry->m_MsgType = kMtbRecv;

            #if (CDRV_CAN_SPEC == CAN20B)
            // set extended flag in MsgType if set in frame formate
            if ( (RMIDxR_IDE & CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RIR) == CAN_ID_STD)
            {
                pMsgEntry->m_MsgType |= kMtbExtend;
            }
            #endif

            //------------------------------------------------------------------------
            // Read message: save CAN identifier
            pMsgEntry->m_CanId   = dwCANID;

            //------------------------------------------------------------------------
            // Read message: save DLC
            pMsgEntry->m_bSize   = (BYTE)0x0F & CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RDTR;

            //------------------------------------------------------------------------
            // Read message: save receive timestamp
            #if CDRV_TIMESTAMP != FALSE
            {
                pMsgEntry->m_Time = TgtGetTickCount();
            }
            #endif // CDRV_TIMESTAMP != FALSE

            //--------------------------------------------------------------------
            // Read message: save RTR Flag
            if ((BYTE)RMIDxR_RTR & CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RIR)
            {
                pMsgEntry->m_MsgType |= kMtbRtr;
            }
            //--------------------------------------------------------------------
            // Read message: save data bytes
            else
            {
                // read data bytes from CAN controller
                *((DWORD*)&pMsgEntry->m_bData[0]) = CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RDLR;
                *((DWORD*)&pMsgEntry->m_bData[4]) = CCI_bxCANx_REG->sFIFOMailBox[FIFO1].RDHR;
            }

            //--------------------------------------------------------------------
            // Read message: process SYNC message
            CDRV_CHECK_RX_MSG (pMsgEntry);

            //--------------------------------------------------------------------
            // Increment the buffer pointer
            pMsgEntry++;
            Index++;

            if (Index >= MaxEntries)
            {
                pMsgEntry = MCO_GLB_VAR(m_InitParam.m_RxBuffHigh.m_pBufferBase);
                Index     = 0;
            }

            MCO_GLB_VAR(m_RxBuffHigh.m_pWritePtr)  = pMsgEntry;
            MCO_GLB_VAR(m_RxBuffHigh.m_WriteIndex) = Index;
            MCO_GLB_VAR(m_RxBuffHigh.m_Count)     += 1;
        }

        //------------------------------------------------------------------------
        // Read message: Release FIFO 1
        CCI_bxCANx_REG->RF1R = RF1R_RFOM1;

    } // while (CCI_bxCANx_REG->RF0R & RF0R_FMP0)

}

#endif // (CDRVBXCAN_USE_USERBUFF != FALSE)

//---------------------------------------------------------------------------
//
// Function:    CdrvTxInterruptHandler()
//
// Description: CAN TX interrupt handler
//              The function checks up if another message must be sent.
//
// Parameters:  Instance pointer
//
// Return:      none
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvTxInterruptHandler (MCO_DECL_INSTANCE_PTR)
{
DWORD dwChannel;

    // ---------------------------------------------------------------------------
    // check if no bus contact was detected before
    if (MCO_GLB_VAR (m_fBusContact) == FALSE)
    {
        // set flag "first bus contact" in CAN driver state
        MCO_GLB_VAR (m_Status) |= kCdrvFirstBusContact;

        // set flag "bus contact" to note that this node is not the only one at the CAN bus
        MCO_GLB_VAR (m_fBusContact) = TRUE;
    }

    // ---------------------------------------------------------------------------
    // clear the interrupt status flags
    CdrvClearInterruptState(MCO_INSTANCE_PTR);

    // ---------------------------------------------------------------------------
    // Someone of the Mailboxes goes empty. Now we set the channel to the next
    // free Mailbox and checks up, if another message is stored in the message
    // buffer to transmit.
    // Which Mailboxes was sent? The same channel can be used for the
    // next message stored in the TX Buffer.
    #if (CDRV_USE_HIGHBUFF != FALSE)
    // Is this Mailbox empty?
    if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMtbHighPrio, &dwChannel))
    {
        // Is a message stored in message buffer? --> If yes then transmit.
        CdrvCheckTransmitHigh (MCO_INSTANCE_PTR_ dwChannel);
    }
    #endif

    // ---------------------------------------------------------------------------
    // Is this Mailbox empty?
    if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMsgTypSend, &dwChannel))
    {
        // Is a message stored in message buffer? --> If yes then transmit.
        CdrvCheckTransmitLow (MCO_INSTANCE_PTR_ dwChannel);
    }

}


//---------------------------------------------------------------------------
//
// Function:    CdrvGetStatus()
//
// Description: gets status of CAN driver
//
// Parameters:  pStatus_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvGetStatus (MCO_DECL_INSTANCE_PTR_
    tCdrvStatus MEM* pStatus_p)
{

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    #if (CDRV_USE_ERROR_ISR == FALSE)
    {
        // Interrupt must not be disabled because
        // an error interrupt service function is
        // not used.

        // check error register of CAN controller
        CdrvCheckErrorRegister (MCO_INSTANCE_PTR);
    }
    #endif // (CDRV_USE_ERROR_ISR == FALSE)

    // write status to calling function
    *pStatus_p = MCO_GLB_VAR (m_Status);

    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvResetStatus()
//
// Description: resets individual bits of CAN driver status
//
// Parameters:  ResetStatus_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvResetStatus (MCO_DECL_INSTANCE_PTR_
    tCdrvStatus ResetStatus_p)
{

    // check for all API function if instance is valid
    MCO_CHECK_INSTANCE_STATE ();

    // only reset flag if the bit set (in this case
    // this code is not a critical section)
    // clear status bits, if set
    MCO_GLB_VAR (m_Status) &= ~(ResetStatus_p & MCO_GLB_VAR (m_Status));

    return kCopSuccessful;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvGetDiagnostic()
//
// Description: gets diagnostic informations of CAN driver
//
// Parameters:  pDiagnostic_p
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

tCopKernel PUBLIC CdrvGetDiagnostic (MCO_DECL_INSTANCE_PTR_
    tCdrvDiagnostic MEM* pDiagnostic_p)
{

    //pDiagnostic_p->m_bREC = (CCI_bxCANx_REG->ESR & ESR_REC) >> 24;
    //pDiagnostic_p->m_bTEC = (CCI_bxCANx_REG->ESR & ESR_TEC) >> 16;

    return kCopSuccessful;

}


//=========================================================================//
//                                                                         //
//          P R I V A T E   F U N C T I O N S                              //
//                                                                         //
//=========================================================================//

MCO_DECL_INSTANCE_FCT ()


//---------------------------------------------------------------------------
//
// Function:    CdrvSetBaudrateIntern()
//
// Description: function sets baudrate to CAN controller
//
// Parameters:  MCO_DECL_INSTANCE_PTR
//
// Return:      tCopKernel
//
// State:
//
//---------------------------------------------------------------------------

static tCopKernel CdrvSetBaudrateIntern (MCO_DECL_INSTANCE_PTR)
{
DWORD       dwBtr;
tCopKernel  Ret = kCopSuccessful;

    // check pointer to baud rate table
    if (MCO_GLB_VAR (m_InitParam.m_pBdiTable) == NULL)
    {
        Ret = kCopCdrvIllegalBdi;
        goto Exit;
    }

    // get values for baud rate registers and check if available
    dwBtr = MCO_GLB_VAR (m_InitParam.m_BaudIndex);
    dwBtr = ((CONST DWORD ROM*) MCO_GLB_VAR (m_InitParam.m_pBdiTable))[dwBtr];
    if (dwBtr == 0xFFFFFFFF)
    {
        Ret = kCopCdrvIllegalBdi;
        goto Exit;
    }

    // set the bit timing register
    CCI_bxCANx_REG->BTR = dwBtr;

Exit:
    return Ret;

}



//---------------------------------------------------------------------------
//
// Function:    CdrvWriteCanMsgToCanCtrl()
//
// Description: writes a CAN message to the CAN controller (for ISR and PUBLIC fcts)
//
// Parameters:  pCanMsg_p
//
// Return:      void
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvWriteCanMsgToCanCtrl  (MCO_DECL_INSTANCE_PTR_
    DWORD dwChannel_p, tCdrvMsg MEM* pCanMsg_p)
{
DWORD       dwId;

    // -------------------------------------------------------------------------------
    // Setup the Identifier (copy the prepared value)
    dwId = pCanMsg_p->m_CanId;

    #if (CDRV_CAN_SPEC == CAN20B)
    // set extended bit if necessary
    if ((pCanMsg_p->m_MsgType & kMtbExtend) != 0)
    {  // Extended Frame identifier
        dwId = ((dwId<<3) | TMIDxR_IDE);
    }
    else
    #endif
    {   // Standard Frame identifier
        dwId = dwId << 21;
    }

    // Prepare Remote Request Frame ?
    if ((pCanMsg_p->m_MsgType & kMtbFilter) == kMsgTypSendRtrReq)
    {
        dwId |= TMIDxR_RTR;
    }

    CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TIR &= TMIDxR_TXRQ; // clear the last ID
    CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TIR |= dwId;        // set the new ID

    // Set up the DLC
    CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TDTR &= 0xFFFFFFF0;
    CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TDTR |= (DWORD)pCanMsg_p->m_bSize;

    // Set up the data field if no Remote Request Frame
    if ((pCanMsg_p->m_MsgType & kMtbFilter) != kMsgTypSendRtrReq)
    {
        DWORD *pdwData;

        pdwData = (DWORD*) &pCanMsg_p->m_bData[0];
        CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TDLR = *pdwData;
        pdwData++;
        CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TDHR = *pdwData;
    }

    // Request transmission
    CCI_bxCANx_REG->sTxMailBox[dwChannel_p].TIR |= TMIDxR_TXRQ;

}


// ----------------------------------------------------------------------------
//
// Function:     CdrvCheckTransmitHigh
//
// Description:  check if it is a message in buffer to send
//
// Parameters:   MCO_DECL_INSTANCE_PTR = (pointer to instance)
//
// Returns:      tCopKernel = error code
//
// State:
//
// ----------------------------------------------------------------------------
#if (CDRV_USE_HIGHBUFF != FALSE)

static void CdrvCheckTransmitHigh (MCO_DECL_INSTANCE_PTR_
             DWORD dwChannel_p) CDRV_REENTRANT
{
tCdrvMsg MEM*  pMsgEntry;
tCdrvBuffIndex Index;

    // There are messages in high priority buffer then put them into CAN controller,
    // increment buffer pointer and decrement count of messages in buffer
    // dont change this lines! they are optimized for speed

    if (MCO_GLB_VAR(m_TxBuffHigh.m_Count) > 0)
    {
        Index     = MCO_GLB_VAR(m_TxBuffHigh.m_ReadIndex);
        pMsgEntry = MCO_GLB_VAR(m_TxBuffHigh.m_pReadPtr);

        CdrvWriteCanMsgToCanCtrl (MCO_INSTANCE_PARAM_(pInstance)  dwChannel_p, pMsgEntry);

        pMsgEntry++;
        Index++;

        if ( Index >= MCO_GLB_VAR(m_InitParam.m_TxBuffHigh.m_MaxEntries) )
        {
            pMsgEntry = MCO_GLB_VAR(m_InitParam.m_TxBuffHigh.m_pBufferBase);
            Index     = 0;
        }

        MCO_GLB_VAR(m_TxBuffHigh.m_ReadIndex) = Index;
        MCO_GLB_VAR(m_TxBuffHigh.m_pReadPtr)  = pMsgEntry;
        MCO_GLB_VAR(m_TxBuffHigh.m_Count)    -= 1;
    }

}

#endif // (CDRV_USE_HIGHBUFF != FALSE)


// ----------------------------------------------------------------------------
//
// Function:     CdrvCheckTransmitLow
//
// Description:  check if it is a message in buffer to send
//
// Parameters:   MCO_DECL_INSTANCE_PTR = (pointer to instance)
//
// Returns:      tCopKernel = error code
//
// State:
//
// ----------------------------------------------------------------------------

static void CdrvCheckTransmitLow (MCO_DECL_INSTANCE_PTR_
             DWORD dwChannel_p) CDRV_REENTRANT
{
tCdrvMsg MEM*  pMsgEntry;
tCdrvBuffIndex Index;

    // are there messages in low priority buffer then put them into CAN controller,
    // increment buffer pointer and decrement count of messages in buffer
    // dont change this lines! they are optimized for speed

    if (MCO_GLB_VAR(m_TxBuffLow.m_Count) > 0)
    {
        Index     = MCO_GLB_VAR(m_TxBuffLow.m_ReadIndex);
        pMsgEntry = MCO_GLB_VAR(m_TxBuffLow.m_pReadPtr);

        CdrvWriteCanMsgToCanCtrl (MCO_INSTANCE_PARAM_(pInstance)  dwChannel_p, pMsgEntry);

        pMsgEntry++;
        Index++;

        if (Index >= MCO_GLB_VAR(m_InitParam.m_TxBuffLow.m_MaxEntries) )
        {
            pMsgEntry = MCO_GLB_VAR(m_InitParam.m_TxBuffLow.m_pBufferBase);
            Index   = 0;
        }

        MCO_GLB_VAR(m_TxBuffLow.m_ReadIndex) = Index;
        MCO_GLB_VAR(m_TxBuffLow.m_pReadPtr)  = pMsgEntry;
        MCO_GLB_VAR(m_TxBuffLow.m_Count)    -= 1;
    }

}


//---------------------------------------------------------------------------
//
// Function:    CdrvCheckErrorRegister()
//
// Description: checks the error register of the CAN controller and writes
//              errors to state variable m_Status of instance table.
//
// Parameters:  MCO_DECL_INSTANCE_PTR_  = (pointer to instance)
//              pCanCtrlBase_p          = base address of CAN controller
//
// Returns:     tCdrvStatus = new CAN driver status bits
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvCheckErrorRegister (MCO_DECL_INSTANCE_PTR)
{
DWORD dwState;
DWORD dwOldState       = MCO_GLB_VAR (m_Intern.m_dwOldState);
tCdrvStatus CdrvStatus = MCO_GLB_VAR (m_Status);

    // TEC and REC values are not stored
    dwState = CCI_bxCANx_REG->ESR & (ESR_EWGF | ESR_EPVF | ESR_BOFF | ESR_LEC);

    //---------------------------------------------------------------------
    // check if Last error code has been changed
    if ( (dwState & ESR_LEC) != ESR_LEC )
    {
        // check LEC of state register of CAN controller
        switch ((dwState & ESR_LEC) >> 4)
        {
            case ESR_LEC_STUFF_ERR: // stuff error
                CdrvStatus |= kCdrvStuffError;
                break;

            case ESR_LEC_FORM_ERR: // form error
                CdrvStatus |= kCdrvFormError;
                break;

            case ESR_LEC_ACK_ERR: // ack error
                CdrvStatus |= kCdrvAckError;
                break;

            case ESR_LEC_CRC_ERR: // crc error
                CdrvStatus |= kCdrvCrcError;
                break;

            case ESR_LEC_BIT1_ERR:    // bit1 error
                // not support by Cdrv interface
                break;

            case ESR_LEC_BIT0_ERR:    // bit0 error
                // not support by Cdrv interface
                break;

            case ESR_LEC_NO_ERR:    // no error
            default: // do nothing because all possible cases are handled
                break;
        }
        // Set Last error code to 111 to detect changes
        // to a newer state
        CCI_bxCANx_REG->ESR |= ESR_LEC;
    }

    //---------------------------------------------------------------------
    // clear Last error code bits
    dwState &= ~ESR_LEC;

    // check if state register has been changed
    if (dwOldState != dwState)
    {
        // save new state of state register
        MCO_GLB_VAR (m_Intern.m_dwOldState) = dwState;

        // check warning limit set
        if ((dwState & ESR_EWGF) != 0)
        {
            CdrvStatus |= kCdrvWarningLimitSet;
        }
        // check warning limit reset
        else if ((dwOldState & ESR_EWGF) != 0)
        {
            CdrvStatus |= kCdrvWarningLimitReset;
        }

        // check error passive set
        if ((dwState & ESR_EPVF) != 0)
        {
            CdrvStatus |= kCdrvErrorPassiveSet;
        }
        // check error passive reset
        else if ((dwOldState & ESR_EPVF) != 0)
        {
            CdrvStatus |= kCdrvErrorPassiveReset;
        }

        // check busoff
        if ((dwState & ESR_BOFF) != 0)
        {
            CdrvStatus |= kCdrvBusOff;
            // The CAN controller is not able to send or
            // receive a message. This flag signals the
            // application when this state was left.
            MCO_GLB_VAR(m_fBusContact) = FALSE;
        }
        // check busoff reset
        else if ((dwOldState & ESR_BOFF) != 0)
        {
            CdrvStatus = (CdrvStatus & ~kCdrvBusOff) | kCdrvBusOffReset;
        }
    }

    MCO_GLB_VAR (m_Status) = CdrvStatus;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvResetIntern()
//
// Description: resets specific parts of CAN driver
//              (without dis- and enabling CAN interrupt)
//
// Parameters:  MCO_DECL_INSTANCE_PTR_  = (pointer to instance)
//              ResetCode_p             = contains flags what is to reset
//
// Returns:     tCopKernel = error code
//                  kCopSuccessful
//
// State:
//
//---------------------------------------------------------------------------

static tCopKernel CdrvResetIntern (MCO_DECL_INSTANCE_PTR_
    tCdrvResetCode ResetCode_p)
{
tCopKernel    Ret = kCopSuccessful;
tCdrvMsg MEM* pBuffer;

    //-----------------------------------------------------------------------------------------
    #if (CDRV_USE_HIGHBUFF != FALSE)
    {
        // Tx buffer (high prio.) should be reseted?
        if ((ResetCode_p & kResetTxBuffHigh) != 0)
        {
            COP_MEMSET (&MCO_GLB_VAR (m_TxBuffHigh), 0, sizeof (tCdrvBuff));

            // set read and write pointer to begin of high priority sending buffer
            pBuffer = MCO_GLB_VAR (m_InitParam.m_TxBuffHigh.m_pBufferBase);
            MCO_GLB_VAR (m_TxBuffHigh.m_pReadPtr)   = pBuffer;
            MCO_GLB_VAR (m_TxBuffHigh.m_pWritePtr)  = pBuffer;
            MCO_GLB_VAR (m_TxBuffHigh.m_ReadIndex)  = 0;
            MCO_GLB_VAR (m_TxBuffHigh.m_WriteIndex) = 0;
            MCO_GLB_VAR (m_TxBuffHigh.m_Count)      = 0;
        }
    }
    #endif

    #if (CDRVBXCAN_USE_USERBUFF != FALSE)
    {
        // Rx buffer (high prio.) should be reseted?
        if ((ResetCode_p & kResetRxBuffHigh) != 0)
        {
            COP_MEMSET (&MCO_GLB_VAR (m_RxBuffHigh), 0, sizeof (tCdrvBuff));

            // set read and write pointer to begin of high priority receiving buffer
            pBuffer = MCO_GLB_VAR (m_InitParam.m_RxBuffHigh.m_pBufferBase);
            MCO_GLB_VAR (m_RxBuffHigh.m_pReadPtr)   = pBuffer;
            MCO_GLB_VAR (m_RxBuffHigh.m_pWritePtr)  = pBuffer;
            MCO_GLB_VAR (m_RxBuffHigh.m_ReadIndex)  = 0;
            MCO_GLB_VAR (m_RxBuffHigh.m_WriteIndex) = 0;
            MCO_GLB_VAR (m_RxBuffHigh.m_Count)      = 0;
        }
    }
    #endif

    //-----------------------------------------------------------------------------------------
    // Tx buffer (low prio.) should be reseted?
    if ((ResetCode_p & kResetTxBuffLow) != 0)
    {
        COP_MEMSET (&MCO_GLB_VAR (m_TxBuffLow), 0, sizeof (tCdrvBuff));

        // set read and write pointer to begin of low priority sending buffer
        pBuffer = MCO_GLB_VAR (m_InitParam.m_TxBuffLow.m_pBufferBase);
        MCO_GLB_VAR (m_TxBuffLow.m_pReadPtr)   = pBuffer;
        MCO_GLB_VAR (m_TxBuffLow.m_pWritePtr)  = pBuffer;
        MCO_GLB_VAR (m_TxBuffLow.m_ReadIndex)  = 0;
        MCO_GLB_VAR (m_TxBuffLow.m_WriteIndex) = 0;
        MCO_GLB_VAR (m_TxBuffLow.m_Count)      = 0;
    }

    // Rx buffer (low prio.) should be reseted?
    if ((ResetCode_p & kResetRxBuffLow) != 0)
    {
        COP_MEMSET (&MCO_GLB_VAR (m_RxBuffLow), 0, sizeof (tCdrvBuff));

        // set read and write pointer to begin of low priority receiving buffer
        pBuffer = MCO_GLB_VAR (m_InitParam.m_RxBuffLow.m_pBufferBase);
        MCO_GLB_VAR (m_RxBuffLow.m_pReadPtr)   = pBuffer;
        MCO_GLB_VAR (m_RxBuffLow.m_pWritePtr)  = pBuffer;
        MCO_GLB_VAR (m_RxBuffLow.m_ReadIndex)  = 0;
        MCO_GLB_VAR (m_RxBuffLow.m_WriteIndex) = 0;
        MCO_GLB_VAR (m_RxBuffLow.m_Count)      = 0;
    }

    //-----------------------------------------------------------------------------------------
    // CAN controller should be reseted?
    if ((ResetCode_p & kResetCanCtrl) != 0)
    {
        // This part should be run if CAN-Controller stay in Bus-off state.
        // For the bxCAN there are two modes to recover from Bus-off-State:
        //
        // (1) Automatically: If CAN_MCR.ABOM is set, the bxCAN start the
        //                    recovering sequence after it has entered Bus-
        //                    -off state.
        //
        // (2) Software request: If CAN_MCR.ABOM is cleared, the software must
        //                       initiate the recovering sequence by requesting
        //                       bxCAN to enter and to leave initialization mode.
        //
        // But in both cases the bxCAN has to wait at least for the recovery sequence
        // specified in the CAN standard (128 occurrences of 11 consecutive recessive
        // bits monitored on CANRX). To recover, the bxCAN must be switch to Normal mode.
/* -as: The CAN controller starts automaticaly the Bus-off recovery sequence. Therefore
        this part is not necessary.

        tTime         dwTimeoutAck;

        // --------- switch to init mode ------------------------------------------------
        CCI_bxCANx_REG->MCR |= MCR_INRQ ;
        // Software sets this bit to request the CAN hardware to enter initialization mode.
        // Once software has set the INRQ bit, the CAN hardware waits until the current CAN
        // activity (transmission or reception) is completed before entering the initia-
        // lization mode. Hardware signals this event by setting the INAK bit in the CAN_MSR
        // register. Max. Timout: 150 Bits * 1/(5kBit/s) = 30ms
        // In case of Busoff state the ack time is very short.
        dwTimeoutAck = TgtGetTickCount();
        // Wait the acknowledge for enter initialisation mode
        while (((CCI_bxCANx_REG->MSR & MSR_INAK) != MSR_INAK)
                  && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

        // --------- switch to normal mode ------------------------------------------------
        CCI_bxCANx_REG->MCR &= ~MCR_INRQ;
        // The software clears this bit to switch the hardware into normal mode. Once 11
        // consecutive recessive bits have been monitored on the Rx signal the CAN hardware
        // is synchronized and ready for transmission and reception. Hardware signals this
        // event by clearing the INAK bit in the CAN_MSR register.
        dwTimeoutAck = TgtGetTickCount();
        while (((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
                 && ( (TgtGetTickCount() - dwTimeoutAck) < INAK_TIMEOUT));

        // ...and check acknowledged
        if ((CCI_bxCANx_REG->MSR & MSR_INAK) == MSR_INAK)
        {
            Ret = kCopCdrvInitError;
            goto Exit;
        }

        // --------------------------------------------------------------------------------
        // clear flag "bus contact" to note that no bus contact is available
        MCO_GLB_VAR (m_fBusContact) = FALSE;

        // --------------------------------------------------------------------------------
        // There may be messages in Tx buffer. If Tx buffer was not cleared, next Tx message
        // can be set from buffer in CAN controller.
        // -as: This part could be unnecessary because a node can only go to bus off if
        // this node is a transmitter. In this case a pending message is in TX mailbox.
        // After transmission the CAN-controller request the TX interrupt to process the
        // next messages in TX buffer.
        if ((ResetCode_p & kResetTxBuffer) == 0)
        {
            DWORD dwChannel;
            // CdrvCheckTransmitXxx() can be called here because CAN interrupt is disabled
            #if (CDRV_USE_HIGHBUFF != FALSE)
            {
                if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMtbHighPrio, &dwChannel))
                {
                   CdrvCheckTransmitHigh (MCO_INSTANCE_PARAM_(pInstance) dwChannel);
                }
            }
            #endif // (CDRV_USE_HIGHBUFF != FALSE)

            if ( kCopSuccessful == CdrvGetEmptyMailbox(MCO_INSTANCE_PTR_ kMsgTypSend, &dwChannel))
            {
                CdrvCheckTransmitLow (MCO_INSTANCE_PARAM_(pInstance) dwChannel);
            }
        }
*/
    }

    return Ret;
}

//---------------------------------------------------------------------------
//
// Function:    CdrvGetEmptyMailbox()
//
// Description: Function checks up if an empty mailbox or message object exist.
//
// Parameters:  MCO_DECL_INSTANCE_PTR_  = (pointer to instance)
//              MsgType_p               = contains the type of message
//                                        kMtbHighPrio --> High Priority Puffer
//                                                         should be used
//                                        kMsgTypSend  --> Low Priority Puffer
//                                                         must uesed
//              pdwChannel_p            = Pointer to channel
//
// Returns:
//              tCopKernel = kCopSuccessful --> The Number of empty channel is
//                                              returned at pdwChannel_p.
//              tCopKernel = kCopCdrvNoFreeChannel --> No empty channel found.
//
// State:
//
//---------------------------------------------------------------------------

static tCopKernel CdrvGetEmptyMailbox(MCO_DECL_INSTANCE_PTR_
                               tMsgTyp MsgType_p, DWORD* pdwChannel_p)
{
tCopKernel Ret = kCopSuccessful;

    #if (CDRV_USE_HIGHBUFF != FALSE)
    if ( (MsgType_p & kMtbHighPrio) == kMtbHighPrio)
    {
       // For High Priority Buffer a fix Mailbox 0 is used. The transmit
       // priority is defined by the identifier value and mailbox number
       // when more than one transmit mailboxes are pending. The lower the
       // identifier or mailbox number will be schedulded first.
       if ((CCI_bxCANx_REG->TSR&TSR_TME0) == TSR_TME0)
       {
          *pdwChannel_p = TX_HIGH_PRIO_FRM_MBOX;
       }
       else
       {
           Ret = kCopCdrvNoFreeChannel;
       }
    }
    else
    {
       // For Low Priority Buffer a fix Mailbox 1 is used. The transmit
       // priority is defined by the identifier value and mailbox number
       // when more than one transmit mailboxes are pending. The lower the
       // identifier or mailbox number will be schedulded first.
       if ((CCI_bxCANx_REG->TSR&TSR_TME1) == TSR_TME1)
       {
          *pdwChannel_p = TX_LOW_PRIO_FRM_MBOX;
       }
       else
       {
           Ret = kCopCdrvNoFreeChannel;
       }
    }
    #else
    {
        // If Low Priority Message is sent or a high priority buffer was
        // not configered then select the next empty mailbox. The transmit
        // mailboxes must be configured as a transmit FIFO by setting the
        // TXFP bit in the CAN_MCR register. In this mode the priority is
        // given by the transmit request order.
        if ((CCI_bxCANx_REG->TSR&TSR_TME0) == TSR_TME0)
        {
            *pdwChannel_p = TX_MAILBOX_0;
        }
        else if ((CCI_bxCANx_REG->TSR&TSR_TME1) == TSR_TME1)
        {
            *pdwChannel_p = TX_MAILBOX_1;
        }
        else if ((CCI_bxCANx_REG->TSR&TSR_TME2) == TSR_TME2)
        {
            *pdwChannel_p = TX_MAILBOX_2;
        }
        else
        {
            Ret = kCopCdrvNoFreeChannel;
        }
    }
    #endif

    return Ret;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvClearInterruptState()
//
// Description: Function checks up if an empty mailbox or message object exist.
//
// Parameters:  MCO_DECL_INSTANCE_PTR_  = (pointer to instance)
//              MsgType_p               = contains the type of message
//                                        kMtbHighPrio --> High Priority Puffer
//                                                         should be used
//                                        kMsgTypSend  --> Low Priority Puffer
//                                                         must uesed
//              pdwChannel_p            = Pointer to channel
//
// Returns:
//              tCopKernel = kCopSuccessful --> The Number of empty channel is
//                                              returned at pdwChannel_p.
//              tCopKernel = kCopCdrvNoFreeChannel --> No empty channel found.
//
// State:
//
//---------------------------------------------------------------------------

static void CdrvClearInterruptState(MCO_DECL_INSTANCE_PTR)
{

    // If RQCPx is set then the last request has been performed.
    // Cleared by writing a 1 to this bit. Clearing this bit
    // clears all status bit (TXOK, ALSTx, TERRx).
    if ((CCI_bxCANx_REG->TSR & TSR_RQCP0) == TSR_RQCP0)
    {
        CCI_bxCANx_REG->TSR |= TSR_RQCP0;
    }

    if ((CCI_bxCANx_REG->TSR & TSR_RQCP1) == TSR_RQCP1)
    {
        CCI_bxCANx_REG->TSR |= TSR_RQCP1;
    }

    if ((CCI_bxCANx_REG->TSR & TSR_RQCP2) == TSR_RQCP2)
    {
        CCI_bxCANx_REG->TSR |= TSR_RQCP2;
    }

}


//---------------------------------------------------------------------------
//
// Function:    CdrvInitIdFilter()
//
// Description: Initializes the CAN peripheral according to the specified
//              parameters in the CAN_FilterInitStruct.
//
//              Notice:
//              In connectivity line all filter bank registers are assigned
//              to the adress region of the first bxCAN controller.
//
//
// Parameters:  Acceptance Mask register
//              Acceptance Code register
//
//              Notice:
//              A set bit in the acceptance mask means, that the identifier bit
//              will be acepted regardless of the bit state (0 or 1). If a bit
//              in the acceptance mask set to 0, then the identifier bit must match
//              to the bit state of the acceptance code register. This is contrary
//              to the use of bxCAN filter bank mask and identifier.
//
// Returns:
//
//
// State:
//
//---------------------------------------------------------------------------
// Filter bank scale and mode configuration
// The filter banks are configured by means of the corresponding CAN_FMR
// register. To configure a filter bank it must be deactivated by clearing
// the FACT bit in the CAN_FAR register. The filter scale is configured by
// means of the corresponding FSCx bit in the CAN_FS1R register. The
// identifier list or identifier mask mode for the corresponding Mask/Identifier
// registers is configured by means of the FBMx bits in the CAN_FMR register.
// To filter a group of identifiers, configure the Mask/Identifier registers in
// mask mode.
// To select single identifiers, configure the Mask/Identifier registers in
// identifier list mode.
// Filters not used by the application should be left deactivated.
// Each filter within a filter bank is numbered (called the Filter Number)
// from 0 to a maximum dependent on the mode and the scale of each of the
// filter banks.
//
// Filter bank uses and assignment per bxCAN instance
//
// Filter bank 0:  Identifier mask mode
//                 The mask based on the user defined value.
// Filter bank 1:  Identifier list mode
//                 This bank is reserved for message identifier which will be
//                 assigned to the second FIFO (High priority buffer messages)
// Filter bank 2:  Identifier list mode
// ...
// Filter bank 13: Identifier list mode
//
// In connectivity line, only one CDRV instance:
//
// Filter bank 26: Identifier list mode
//
// Filter bank 27: reserved to second bxCAN, Identifier mask mode
//---------------------------------------------------------------------------

static void CdrvInitIdFilter(MCO_DECL_INSTANCE_PTR_ DWORD dwAmr_p, DWORD dwAcr_p)
{
BYTE  i;
BYTE  bFilterNo;
BYTE  bMaxFilterNo;
DWORD dwIdMask, dwFilterPos;

    //------------------------------------------------------------------------
    // set the number of filter bank
    bFilterNo    = (CCI_bxCANx_REG == CAN2)?CAN1_START_FILTER:CAN0_START_FILTER;
    // The first filter bank number is equal to the number of filter banks
    // of first bxCAN instance.
    bMaxFilterNo = (CCI_bxCANx_REG == CAN2)?NO_OF_FILTERS:CAN1_START_FILTER;

    //------------------------------------------------------------------------
    #if ( (TGTHW_STM3210C_EVAL & TGT_CPU_MASK_) == TGT_CPU_STM32F_CL)
    {
        // In connectivity line only the second bxCAN instance must be set
        // to filter start bank value.
        CAN1->FMR &= ~FMR_CAN2SB;
        CAN1->FMR |= ((DWORD)CAN1_START_FILTER << 8) & FMR_CAN2SB;
    }
    #endif

    //----------------------------------------------------------------------
    // Initialisation mode for the filter
    CAN1->FMR |= FMR_FINIT;

    //----------------------------------------------------------------------
    // Initialisation of the acceptance filter for the message identifier
    // which contents the node ID. This filter is assigned fix to filter
    // bank 0.
    // Filter Deactivation:
    // Bit-Position = 0 -> filter not activated
    // Bit-Position = 1 -> filter activated
    CAN1->FA1R &= ~((DWORD)0x0000001 << bFilterNo); // filter deactivated

    // Filter scaling:
    // Bit-Position = 0: filter register scaled as 16 bit register
    // Bit-Position = 1: filter register scaled as 32 bit register
    CAN1->FS1R |= (DWORD)0x0000001 << bFilterNo; // scaled as 32 bit register

    //-----------------------------------------------------------------------
    // Set the Filter identifier
    // The ACR and AMR is defined according to the SJA1000 acceptance filter:
    // 11Bit ID: Bit 21 ... 31, Bit20 = RTR, Bit[19:0]=reserved
    // 29Bit ID: Bit 3 ... 31, Bit2=RTR, Bit[1:0]=reserved
    dwIdMask = dwAcr_p;

    // Copy RTR bit value
    #if (CDRV_CAN_SPEC == CAN20A)
    {
        dwIdMask &= 0xFFE00000;
        dwIdMask |= (dwAcr_p & 0x00100000)?RMIDxR_RTR:0;
    }
    #else
    {
        dwIdMask &= 0xFFFFFFF8;
        dwIdMask |= (dwAcr_p & 0x00000004)?RMIDxR_RTR:0;
    }
    #endif

    // RTR Flag is don't care
    // IDE Flag must match to 0 (CAN20A)
    CAN1->sFilterRegister[bFilterNo].m_dwFR1 = dwIdMask;  // Filter ID

    //-----------------------------------------------------------------------
    // Set the Filter mask
    dwIdMask = dwAmr_p;

    // Copy RTR mask bit
    #if (CDRV_CAN_SPEC == CAN20A)
    {
        dwIdMask &= 0xFFE00000;
        dwIdMask |= (dwAmr_p & 0x00100000)?RMIDxR_RTR:0;
        // IDE Flag must match to 0 (CAN20A)
        dwIdMask |= RMIDxR_IDE;
    }
    #else
    {
        dwIdMask &= 0xFFFFFFF8;
        dwIdMask |= (dwAmr_p & 0x00000004)?RMIDxR_RTR:0;
        // IDE Flag don't care
    }
    #endif

    CAN1->sFilterRegister[bFilterNo].m_dwFR2 = dwIdMask;  // Filter Mask

    //-----------------------------------------------------------------------
    // Filter Mode:
    // Bit-Position = 0 -> ID/Mask mode
    // Bit-Position = 1 -> ID List mode
    CAN1->FM1R &= ~((DWORD)0x0000001 << bFilterNo); // --> ID/Mask mode

    // Filter FIFO Assignment:
    // Bit-Position = 0 -> assigned to FIFO0
    // Bit-Position = 1 -> assigned to FIFO1
    CAN1->FFA1R &= ~((DWORD)0x0000001 << bFilterNo);

    // Filter activation:
    // Bit-Position = 0 -> filter not activated
    // Bit-Position = 1 -> filter activated
    CAN1->FA1R |= (DWORD)0x0000001 << bFilterNo;

    //------------------------------------------------------------------
    // Set the another filter banks to the identifier list mode
    // Scale the another filter banks according to the used configuration
    // CAN0: 0 ...13 (PL, CL) or 0 .. 27 (CL)
    // CAN1: 14 .. 27 (CL)
    for (i=bFilterNo+1; i < bMaxFilterNo; i++)
    {
        dwFilterPos = (DWORD)0x0000000F << ((i * 4) % 32);
        dwFilterAssignment_l[(i*4)/32] &= ~dwFilterPos;

        // Deactivation the filter before set the new mode
        CAN1->FA1R &= ~((DWORD)0x0000001 << i); // filter deactivated

        // Scale the another filter banks according to the used configuration
        #if (CDRV_CAN_SPEC == CAN20A)
        {
            // Filter scaling:
            // Bit-Position = 0: filter register scaled as 16 bit register
            CAN1->FS1R &= ~((DWORD)0x0000001 << i); // scaled as 16 bit register
        }
        #else
        {
            // Filter scaling:
            // Bit-Position = 1: filter register scaled as 32 bit register
            CAN1->FS1R |= (DWORD)0x0000001 << i; // scaled as 32 bit register
        }
        #endif

        // Identifier liste löschen: Dadurch wird beim Aktivieren der Identifier
        // 0 stets akzeptiert, das ist sicher ok so, da diese Nachricht bei CANopen
        // Slaves stets benötigt wird und beim Master in der Cob-Schicht ausgefiltert
        // wird. Gibt es einen anderen Wert, der als Identifier niemals auftritt?
        CAN1->sFilterRegister[i].m_dwFR1 = 0;  // ID = 0
        CAN1->sFilterRegister[i].m_dwFR2 = 0;  // ID = 0

        // Filter Mode: Bit-Position = 1 -> ID List mode
        CAN1->FM1R |= ((DWORD)0x0000001 << i);

        // Filter assignment to FIFO, filter identifier setting and filter
        // activation will be done if identifier will be defined.
    }

    //------------------------------------------------------------------
    // Leave the initialisation mode for the filter
    CAN1->FMR &= ~FMR_FINIT;

}


//---------------------------------------------------------------------------
//
// Function:    CdrvSetIdFilter()
//
// Description: Defines a message filter in the identifier list of bxCAN
//              controller, filter bank must be in identifier list mode.
//
//              Notice:
//              In connectivity line all filter bank registers are assigned
//              to the adress region of the first bxCAN controller.
//
//
// Parameters:  Instance pointer
//              message identifier
//              message type
//
// Returns:     tCopKernel
//
//
// State:
//
//---------------------------------------------------------------------------
#if (CDRV_ID_FILTER_IN_HW != FALSE)

static tCopKernel CdrvSetIdFilter (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p)
{
BYTE       bFilterBankNo, bMaxFilterBankNo;
BYTE       bFilterIndex;
DWORD      dwFilterPos, dwFilterReg;
DWORD      dwGlobalId, dwGlobalMask;
#if (CDRV_CAN_SPEC == CAN20A)
   DWORD   dwCanIDScaled16Bit;
#endif
DWORD      dwCanIDScaled32Bit;
tCopKernel Ret = kCopSuccessful;

    //------------------------------------------------------------------------
    // set the number of filter bank
    bFilterBankNo = (CCI_bxCANx_REG == CAN2)?CAN1_START_FILTER:CAN0_START_FILTER;
    // The first filter bank number is equal to the number of filter banks
    // of first bxCAN instance.
    bMaxFilterBankNo = (CCI_bxCANx_REG == CAN2)?NO_OF_FILTERS:CAN1_START_FILTER;

    //----------------------------------------------------------------------
    // convert the message identifier to format of filter bank register
    dwCanIDScaled32Bit = dwCanId_p;

    // only 11 bit identifier --> filter scaled as 16 bit
    #if (CDRV_CAN_SPEC == CAN20A)
    {
        // register scaled as 16 bit
        dwCanIDScaled16Bit  = dwCanId_p << 2;
        dwCanIDScaled16Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;
        dwCanIDScaled16Bit <<= 3;
        dwCanIDScaled16Bit &= 0x0000FFFF;
        // setup the value to compare with global mask and id
        dwCanIDScaled32Bit <<= 21; // setup 11Bit identifier
    }
    #else
    {
        // CDRV_CAN_SPEC == CAN20B
        // 11/29 Bit value
        if ((MsgType_p & kMtbExtend) == kMtbExtend)
        {
            dwCanIDScaled32Bit <<= 3;  // setup 29Bit identifier
            dwCanIDScaled32Bit |= RMIDxR_IDE;
        }
        else
        {
            // setup the value to compare with global mask and id
            dwCanIDScaled32Bit <<= 21; // setup 11Bit identifier
        }
    }
    #endif

    // Remote Frame?
    dwCanIDScaled32Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;

    //----------------------------------------------------------------------
    // check up if the message identifier can pass the first filter bank
    // which is configured in identifier mask mode
    dwGlobalId   = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1; // Id
    dwGlobalMask = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2; // Mask
    // Identifier pass the filter?
    if ( (dwCanIDScaled32Bit & dwGlobalMask) == dwGlobalId)
    {
        goto Exit; // yes --> we need no entry to identifier list
    }

    //----------------------------------------------------------------------
    // search an empty identifier list entry
    // starts with the second filter bank, the first is reserved to
    // identifier mask mode
    bFilterBankNo += 1;

    // Each filter bank has up to 4 identifier list entries. Set start value
    // for the filter index.
    bFilterIndex = bFilterBankNo * 4;

    do
    {
        dwFilterPos = (DWORD)0x00000001 << (bFilterIndex % 32);
        // Find the empty entry
        if ( (dwFilterAssignment_l[bFilterIndex/32] & dwFilterPos) == 0)
        {
            // entry is empty
            dwFilterAssignment_l[bFilterIndex/32] |= dwFilterPos;
            //----------------------------------------------------------------------
            // set the initialisation mode for the filter to get write access
            CAN1->FMR |= FMR_FINIT;
            // Filter deactivation
            CAN1->FA1R &= ~((DWORD)0x0000001 << bFilterBankNo);

            //----------------------------------------------------------------------
            // write identifier
            if ( (bFilterIndex%4) < 2)
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1;
                #if (CDRV_CAN_SPEC == CAN20A)
                {
                    // Filter bank 16bit scaled
                    // first 16Bit value --> clear low halfword
                    // second 16Bit value --> clear high halfword
                    dwFilterReg &= ((bFilterIndex%4)==0)?0xFFFF0000:0x0000FFFF;
                    dwFilterReg |= ((bFilterIndex%4)==0)?(dwCanIDScaled16Bit):(dwCanIDScaled16Bit<<16);
                }
                #else
                {
                    dwFilterReg = dwCanIDScaled32Bit;
                }
                #endif

                // write back to identifier list
                CAN1->sFilterRegister[bFilterBankNo].m_dwFR1 = dwFilterReg;
            }
            else
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2;
                #if (CDRV_CAN_SPEC == CAN20A)
                {
                    // Filter bank 16bit scaled
                    // first 16Bit value --> clear low halfword
                    // second 16Bit value --> clear high halfword
                    dwFilterReg &= ((bFilterIndex%4)==2)?0xFFFF0000:0x0000FFFF;
                    dwFilterReg |= ((bFilterIndex%4)==2)?(dwCanIDScaled16Bit):(dwCanIDScaled16Bit<<16);
                }
                #else
                {
                    dwFilterReg = dwCanIDScaled32Bit;
                }
                #endif

                // write back to identifier list
                CAN1->sFilterRegister[bFilterBankNo].m_dwFR2 = dwFilterReg;
            }

            //------------------------------------------------------------------
            // set FIFO assignment: FIFO 0
            // Bit = 0: filter bank assigned to FIFO 0 (low priority buffer)
            // Bit = 1: filter bank assigned to FIFO 1 (high priority buffer)
            CAN1->FFA1R &= ~((DWORD)0x0000001 << bFilterBankNo);

            //------------------------------------------------------------------
            // Filter activation
            CAN1->FA1R |= ((DWORD)0x0000001 << bFilterBankNo);

            // Leave the initialisation mode for the filter
            CAN1->FMR &= ~FMR_FINIT;
            break;
        }

        // If no entry is set then go to the next 32th part
        if ( dwFilterAssignment_l[bFilterIndex/32] == 0xFFFFFFFF)
        {
            bFilterIndex += (32 - (bFilterIndex % 32));
        }
        else
        {
            #if (CDRV_CAN_SPEC == CAN20A)
            {
                bFilterIndex++;
            }
            #else
            {
                bFilterIndex += 2;
            }
            #endif
        }

        bFilterBankNo += (bFilterIndex - (bFilterBankNo * 4)) / 4;

    } while (bFilterBankNo < bMaxFilterBankNo);

    if (bFilterBankNo >= bMaxFilterBankNo)
    {
       // no empty entry found
       Ret = kCopCdrvInitError;
    }

Exit:
    return Ret;

}

#endif

//---------------------------------------------------------------------------
//
// Function:    CdrvSetUserIdFilter()
//
// Description: Defines a message filter in the identifier list of bxCAN
//              controller, filter bank must be in identifier list mode.
//
//              Notice:
//              In connectivity line all filter bank registers are assigned
//              to the adress region of the first bxCAN controller.
//
//
// Parameters:  Instance pointer
//              message identifier
//              message type
//
// Returns:     tCopKernel
//
//
// State:
//
//---------------------------------------------------------------------------
#if (CDRVBXCAN_USE_USERBUFF != FALSE)

Es sollte jeweils die letzte Filterbank einer Instanz für dieses Filter verwendet werden.

static tCopKernel CdrvSetUserIdFilter (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p)
{
BYTE       bFilterBankNo, bMaxFilterBankNo;
BYTE       bFilterIndex;
DWORD      dwFilterPos, dwFilterReg;
DWORD      dwCanIDScaled16Bit, dwCanIDScaled32Bit;
tCopKernel Ret = kCopSuccessful;

    //------------------------------------------------------------------------
    // set the number of filter bank
    bFilterBankNo = (CCI_bxCANx_REG == CAN2)?CAN1_START_FILTER:CAN0_START_FILTER;

    //----------------------------------------------------------------------
    // convert the message identifier to format of filter bank register
    // only 11 bit identifier --> filter scaled as 16 bit
    #if (CDRV_CAN_SPEC == CAN20A)
    {
        // register scaled as 16 bit
        dwCanIDScaled16Bit  = dwCanId_p << 2;
        dwCanIDScaled16Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;
        dwCanIDScaled16Bit <<= 3;
        dwCanIDScaled16Bit &= 0x0000FFFF;
    }
    #endif

    // 11/29 Bit value
    dwCanIDScaled32Bit = dwCanId_p;
    if ((MsgType_p & kMtbExtend) == kMtbExtend)
    {
        dwCanIDScaled32Bit <<= 3;  // setup 29Bit identifier
        dwCanIDScaled32Bit |= RMIDxR_IDE;
    }
    else
    {
        dwCanIDScaled32Bit <<= 21; // setup 11Bit identifier
    }

    // Remote Frame?
    dwCanIDScaled32Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;

    //----------------------------------------------------------------------
    // Because for the hig buffer there are no filter in mask mode. Therefor
    // the identifier must set to the identifier list.
    // The second filter bank is reserved for high buffer message identifier
    // list.
    bFilterBankNo = 1;

    // Each filter bank has up to 4 identifier list entries. Set start value
    // for the filter index.
    bFilterIndex = bFilterBankNo * 4;

    // For the high buffer only one filter bank is reserved.
    bMaxFilterBankNo = bFilterBankNo + 1;

    //----------------------------------------------------------------------
    // search an empty identifier list entry
    do
    {
        dwFilterPos = (DWORD)0x00000001 << (bFilterIndex % 32);
        // Find the empty entry
        if ( (dwFilterAssignment_l[bFilterIndex/32] & dwFilterPos) == 0)
        {
            // entry is empty
            dwFilterAssignment_l[bFilterIndex/32] |= dwFilterPos;

            //----------------------------------------------------------------------
            // set the initialisation mode for the filter to get write access
            CAN1->FMR |= FMR_FINIT;

            // Filter deactivation
            CAN1->FA1R &= ~((DWORD)0x0000001 << bFilterBankNo);

            //----------------------------------------------------------------------
            // write identifier
            if ( (bFilterIndex%4) < 2)
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1;
                #if (CDRV_CAN_SPEC == CAN20A)
                {
                    // Filter bank 16bit scaled
                    // first 16Bit value --> clear low halfword
                    // second 16Bit value --> clear high halfword
                    dwFilterReg &= ((bFilterIndex%4)==0)?0xFFFF0000:0x0000FFFF;
                    dwFilterReg |= ((bFilterIndex%4)==0)?(dwCanIDScaled16Bit):(dwCanIDScaled16Bit<<16);
                }
                #else
                {
                    dwFilterReg = dwCanIDScaled32Bit;
                }
                #endif

                // write back to identifier list
                CAN1->sFilterRegister[bFilterBankNo].m_dwFR1 = dwFilterReg;
            }
            else
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2;
                #if (CDRV_CAN_SPEC == CAN20A)
                {
                    // Filter bank 16bit scaled
                    // first 16Bit value --> clear low halfword
                    // second 16Bit value --> clear high halfword
                    dwFilterReg &= ((bFilterIndex%4)==2)?0xFFFF0000:0x0000FFFF;
                    dwFilterReg |= ((bFilterIndex%4)==2)?(dwCanIDScaled16Bit):(dwCanIDScaled16Bit<<16);
                }
                #else
                {
                    dwFilterReg = dwCanIDScaled32Bit;
                }
                #endif

                // write back to identifier list
                CAN1->sFilterRegister[bFilterBankNo].m_dwFR2 = dwFilterReg;
            }

            //------------------------------------------------------------------
            // set FIFO assignment: FIFO 1
            // Bit = 0: filter bank assigned to FIFO 0 (low priority buffer)
            // Bit = 1: filter bank assigned to FIFO 1 (high priority buffer)
            CAN1->FFA1R |= ((DWORD)0x0000001 << bFilterBankNo);

            //------------------------------------------------------------------
            // Filter activation
            CAN1->FA1R |= ((DWORD)0x0000001 << bFilterBankNo);

            // Leave the initialisation mode for the filter
            CAN1->FMR &= ~FMR_FINIT;
            break;
        }

        #if (CDRV_CAN_SPEC == CAN20A)
        {
            bFilterIndex++;
        }
        #else
        {
            bFilterIndex += 2;
        }
        #endif

        bFilterBankNo += (bFilterIndex - (bFilterBankNo * 4)) / 4;

    } while (bFilterBankNo < bMaxFilterBankNo);

    if (bFilterBankNo >= bMaxFilterBankNo)
    {
        // no empty entry found
        Ret = kCopCdrvInitError;
    }

    return Ret;

}

#endif


//---------------------------------------------------------------------------
//
// Function:    CdrvResetIdFilter()
//
// Description: Defines a message filter in the identifier list of bxCAN
//              controller, filter bank must be in identifier list mode.
//
//              Notice:
//              In connectivity line all filter bank registers are assigned
//              to the adress region of the first bxCAN controller.
//
//
// Parameters:  Instance pointer
//              message identifier
//              message type
//
// Returns:     tCopKernel
//
//
// State:
//
//---------------------------------------------------------------------------
#if (CDRV_ID_FILTER_IN_HW != FALSE)

static tCopKernel CdrvResetIdFilter (MCO_DECL_INSTANCE_PTR_ DWORD dwCanId_p, tMsgTyp MsgType_p)
{
BYTE       bFilterBankNo, bMaxFilterBankNo;
BYTE       bFilterIndex;
DWORD      dwFilterPos, dwFilterReg;
DWORD      dwGlobalId, dwGlobalMask;
#if (CDRV_CAN_SPEC == CAN20A)
    DWORD  dwCanIDScaled16Bit;
#endif
DWORD      dwCanIDScaled32Bit;
tCopKernel Ret = kCopSuccessful;

    //------------------------------------------------------------------------
    // set the number of filter bank
    bFilterBankNo = (CCI_bxCANx_REG == CAN2)?CAN1_START_FILTER:CAN0_START_FILTER;

    // The first filter bank number is equal to the number of filter banks
    // of first bxCAN instance.
    bMaxFilterBankNo = (CCI_bxCANx_REG == CAN2)?NO_OF_FILTERS:CAN1_START_FILTER;

    //----------------------------------------------------------------------
    // convert the message identifier to format of filter bank register
    dwCanIDScaled32Bit = dwCanId_p;

    // only 11 bit identifier --> filter scaled as 16 bit
    #if (CDRV_CAN_SPEC == CAN20A)
    {
        // register scaled as 16 bit
        dwCanIDScaled16Bit = dwCanId_p << 2;
        dwCanIDScaled16Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;
        dwCanIDScaled16Bit <<= 3;
        // setup the value to compare with global mask and id
        dwCanIDScaled32Bit <<= 21; // setup 11Bit identifier
    }
    #else
    {
        // CDRV_CAN_SPEC == CAN20B
        // 11/29 Bit value
        if ((MsgType_p & kMtbExtend) == kMtbExtend)
        {
            dwCanIDScaled32Bit <<= 3;  // setup 29Bit identifier
            dwCanIDScaled32Bit |= RMIDxR_IDE;
        }
        else
        {
            dwCanIDScaled32Bit <<= 21; // setup 11Bit identifier
        }
    }
    #endif

    // Remote Frame?
    dwCanIDScaled32Bit |= (MsgType_p & kMtbRtr)?RMIDxR_RTR:0;

    //----------------------------------------------------------------------
    // check up if the message identifier can pass the first filter bank
    // which is configured in identifier mask mode
    dwGlobalId   = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1; // Id
    dwGlobalMask = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2; // Mask
    // Identifier pass the filter?
    if ( (dwCanIDScaled32Bit & dwGlobalMask) == dwGlobalId)
    {
        goto Exit;  // yes --> the message identifier is not included in
                    //         identifier list
    }

    //----------------------------------------------------------------------
    // The message identifier was written to the identifier list. Now
    // searchs the list entry.
    // starts with the second filter bank, the first is reserved to
    // identifier mask mode
    bFilterBankNo += 1;

    // Each filter bank has up to 4 identifier list entries. Set start value
    // for the filter index.
    bFilterIndex = bFilterBankNo * 4;

    do
    {
        dwFilterPos = (DWORD)0x00000001 << (bFilterIndex % 32);

        // Only signed entries are relevant
        if ( (dwFilterAssignment_l[bFilterIndex/32] & dwFilterPos) != 0)
        {
            if ( (bFilterIndex %4) < 2)
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1;
            }
            else
            {
                dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2;
            }

            #if (CDRV_CAN_SPEC == CAN20A)
            {
                dwFilterReg &= ((bFilterIndex%4)&0x01)?0xFFFF0000:0x0000FFFF;
                dwCanIDScaled32Bit  =  ((bFilterIndex%4)&0x01)?(dwCanIDScaled16Bit<<16):(dwCanIDScaled16Bit&0x0000FFFF);
            }
            #endif

            if (dwFilterReg == dwCanIDScaled32Bit)
            {
                dwFilterAssignment_l[bFilterIndex/32] &= ~dwFilterPos;

                //----------------------------------------------------------------------
                // set the initialisation mode for the filter to get write access
                CAN1->FMR |= FMR_FINIT;

                // Filter deactivation
                CAN1->FA1R &= ~((DWORD)0x0000001 << bFilterBankNo);

                //----------------------------------------------------------------------
                // clear identifier
                if ( (bFilterIndex %4) < 2)
                {
                    dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR1;
                    dwFilterReg &= ~dwCanIDScaled32Bit;
                    CAN1->sFilterRegister[bFilterBankNo].m_dwFR1 = dwFilterReg;
                }
                else
                {
                    dwFilterReg = CAN1->sFilterRegister[bFilterBankNo].m_dwFR2;
                    dwFilterReg &= ~dwCanIDScaled32Bit;
                    CAN1->sFilterRegister[bFilterBankNo].m_dwFR2 = dwFilterReg;
                }

                //------------------------------------------------------------------
                // set FIFO assignment: FIFO 0
                // Bit = 0: filter bank assigned to FIFO 0 (low priority buffer)
                // Bit = 1: filter bank assigned to FIFO 1 (high priority buffer)
                CAN1->FFA1R &= ~((DWORD)0x0000001 << bFilterBankNo);

                //------------------------------------------------------------------
                // Filter activation
                CAN1->FA1R |= ((DWORD)0x0000001 << bFilterBankNo);

                // Leave the initialisation mode for the filter
                CAN1->FMR &= ~FMR_FINIT;

                break;
            }
        }

        // If no entry is set then go to the next 32th part
        if ( dwFilterAssignment_l[bFilterIndex/32] == 0)
        {
            bFilterIndex += (32 - (bFilterIndex % 32));
        }
        else
        {
            #if (CDRV_CAN_SPEC == CAN20A)
            {
                bFilterIndex++;
            }
            #else
            {
                bFilterIndex += 2;
            }
            #endif
        }

        bFilterBankNo += (bFilterIndex - (bFilterBankNo * 4)) / 4;

    } while (bFilterBankNo < bMaxFilterBankNo);

    if (bFilterBankNo >= bMaxFilterBankNo)
    {
        // no entry found
        Ret = kCopCdrvInitError;
    }

Exit:
    return Ret;

}

#endif


// EOF

