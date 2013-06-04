/****************************************************************************

  (c) SYSTEC electronic GmbH, D-07973 Greiz, August-Bebel-Str. 29
      www.systec-electronic.de

  Project:      CANopen V5 / CAN driver

  Description:  target specific functions for Luminary Micro LM3S8971

  -------------------------------------------------------------------------

                $RCSfile: target.c,v $

                $Author: R.Dietzsch $

                $Revision: 1.1 $  $Date: 2010/06/18 12:32:17 $

                $State: Exp $

                Build Environment:
                    Keil RealView

  -------------------------------------------------------------------------

  Revision History:

  2010/03/11 a.s.:  start of implementation

****************************************************************************/

#include "stm32f10x.h"
#include "global.h"

#if !defined (STM32F10X_LD)    && \
    !defined (STM32F10X_LD_VL) && \
    !defined (STM32F10X_MD)    && \
    !defined (STM32F10X_MD_VL) && \
    !defined (STM32F10X_HD)    && \
    !defined (STM32F10X_CL)

    #error 'ERROR: Define one of the target device types in your toolchain compiler preprocessor.'

    // #define STM32F10X_LD      // !< STM32F10X_LD:    STM32 Low density devices
    // #define STM32F10X_LD_VL   // !< STM32F10X_LD_VL: STM32 Low density Value Line devices
    // #define STM32F10X_MD      // !< STM32F10X_MD:    STM32 Medium density devices
    // #define STM32F10X_MD_VL   // !< STM32F10X_MD_VL: STM32 Medium density Value Line devices
    // #define STM32F10X_HD      // !< STM32F10X_HD:    STM32 High density devices
    // #define STM32F10X_CL      // !< STM32F10X_CL:    STM32 Connectivity line devices

#endif


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

// define the CPU system clock
#define SYSCLK_FREQ_72MHz           72000000


//---------------------------------------------------------------------------
// modul global types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local vars
//---------------------------------------------------------------------------

#if (COP_MAX_INSTANCES > 1)
    tCopPtrInstance aCdrvInstancePtr[COP_MAX_INSTANCES];
#endif


//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

static void TgtSetSysClock (void);

#ifdef SYSCLK_FREQ_HSE
    static void TgtSetSysClockToHSE  (void);
#elif defined SYSCLK_FREQ_72MHz
    static void TgtSetSysClockTo72   (void);
#endif


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

void PUBLIC SystemInit (void)
{

    //--------------------------------------------------------------------------
    // Clock configuration für CPU clock
    TgtSetSysClock();

}


// ----------------------------------------------------------------------------
//
// Function:    TgtInit()
//
// Description: function initializes taget specific registers
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtInit (void)
{

    //--------------------------------------------------------------------------
    // Clock configuration für CPU clock
//    TgtSetSysClock();

    //--------------------------------------------------------------------------
    // Clock configuration for peripherals
    // GPIOB, GPIOD and AFIO clocks enable
    RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPBEN);

    //--------------------------------------------------------------------------
    // Initializing the CAN interface
//    TgtInitCanIsr ();

}


// ----------------------------------------------------------------------------
//
// Function:    TgtClearPRIMASK()
//
// Description: Function clears the PRIMASK (for activation of
//              all exceptions with configurable priority). The
//              function returns the state of PRIMASK befor changed.
//
// Parameters:  none
//
// Returns:     PRIMASK befor changed
//
// ----------------------------------------------------------------------------

__asm DWORD TgtClearPRIMASK(void)
{

    mrs     r0, PRIMASK // get the PRIMASK
    cpsie   i           // change processor state: i=clear the PRIMASK
    bx      lr          // return from function call

}


// ----------------------------------------------------------------------------
//
// Function:    TgtSetPRIMASK()
//
// Description: Function set the PRIMASK (prevents activation of
//              all exceptions with configurable priority). The
//              function returns the state of PRIMASK befor changed.
//
// Parameters:  none
//
// Returns:     PRIMASK befor changed
//
// ----------------------------------------------------------------------------

__asm DWORD TgtSetPRIMASK(void)
{

    mrs     r0, PRIMASK // get the PRIMASK
    cpsid   i           // change processor state: i=set the PRIMASK
    bx      lr          // return from function call

}


// ----------------------------------------------------------------------------
//
// Function:    TgtEnableGlobalInterrupt()
//
// Description: Function enables or disables the activation of all
//              exceptions with configurable priority.
//
// Parameters:  bEnable_p           = FALSE = disable / TRUE = enable
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtEnableGlobalInterrupt (BYTE bEnable_p)
{

    // The Cortex-M3 do not have a global interrupt bit for enable/disable
    // all interrupts. To prevent activation of all exceptions/interrupts
    // we change the processor priority mask register. This will not prevent
    // calling any fault exceptions handler. Calling of NMI exception handler
    // can never be prevent.

    if (bEnable_p == FALSE)
    {
        // disable global interrupt
        TgtSetPRIMASK();
        // __asm("cpsid   i");
    }
    else
    {
        // enable global interrupt
        TgtClearPRIMASK();
        // __asm("cpsie   i");
    }

}


//=========================================================================//
//                                                                         //
//          P R I V A T   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

// ...

/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <CAN Interface function>                            */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6

// CAN1 Alternate Function mapping
// Remap 00: PA11=CAN_RX0, PA12=CAN_TX0
//       01: not used
//       10: PB8=CAN_RX0, PB9=CAN_TX0
//       11: PD0=CAN_RX0, PD1=CAN_TX0 (STM3210C-EVAL-Board)
//
// Coding:
// High-WORD = 0x0010xxxx: Remap-Value defines the bit position (0xD)
// Low-WORD  = 0xXXXX6000: That is the Remap-Value
#define GPIO_Remap1_CAN1        ((DWORD)0x001D4000)
#define GPIO_Remap2_CAN1        ((DWORD)0x001D6000)

// CAN2 Alternate Function mapping (only connectivity line)
// Remap 0: PB12=CAN_RX1, PB13=CAN_TX1
//       1: PB5 =CAN_RX1, PB6 =CAN_TX1 (STM3210C-EVAL-Board)
#define GPIO_Remap_CAN2         ((DWORD)0x00200040)

// define interrupt priority
#define NVIC_PRIORITY_GROUP     6
#define CAN1_RX0_PRIORITY       0
#define CAN1_RX1_PRIORITY       1
#define CAN1_SCE_PRIORITY       2
#define CAN1_TX_PRIORITY        3

#define NVIC_PRIORITY_GROUP     6
#define CAN2_RX0_PRIORITY       0
#define CAN2_RX1_PRIORITY       1
#define CAN2_SCE_PRIORITY       2
#define CAN2_TX_PRIORITY        3

#if ( (TARGET_HARDWARE & TGT_CPU_MASK_) == TGT_CPU_STM32F_PL)

    #define CAN1_RX0_IRQn       USB_LP_CAN1_RX0_IRQn
    #define CAN1_TX_IRQn        USB_HP_CAN1_TX_IRQn

#endif


//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------

typedef enum
{
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz,
    GPIO_Speed_50MHz

} tGPIOSpeedDef;

typedef enum
{
    GPIO_Mode_AIN         = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD         = 0x28,
    GPIO_Mode_IPU         = 0x48,
    GPIO_Mode_Out_OD      = 0x14,
    GPIO_Mode_Out_PP      = 0x10,
    GPIO_Mode_AF_OD       = 0x1C,
    GPIO_Mode_AF_PP       = 0x18

} tGPIOModeDef;

typedef struct
{
    // Specifies the GPIO pins to be configured.
    // This parameter can be any value of GPIO_pins.
    WORD m_GPIO_Pin;

    // Specifies the speed for the selected pins.
    // This parameter can be a value of tGPIOSpeedDef.
    tGPIOSpeedDef m_GPIO_Speed;

    // Specifies the operating mode for the selected pins.
    // This parameter can be a value of tGPIOModeDef.
    tGPIOModeDef  m_GPIO_Mode;

} tGPIOInit;


//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

static void TgtGPIOInit(GPIO_TypeDef* GPIOx_p, tGPIOInit* GPIOInit_p);
static void TgtGPIOPinRemapConfig(DWORD GPIO_Remap, WORD NewState);


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//


// ----------------------------------------------------------------------------
//
// Function:    TgtInitCanIsr()
//
// Description: function initializes CAN interrupt
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtInitCanIsr (void)
{
BYTE  bPriority;
tGPIOInit  GPIO_InitStructure;

    //================================================================================
    // Enable peripheral clocks for CAN controller
    #if (CDRV_USED_CAN_CONTROLLER == 0) || (CDRV_MAX_INSTANCES == 2)
    {
        // CAN1 Periph clocks enable
        RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

        // Remap CAN1 and CAN2 GPIOs
        TgtGPIOPinRemapConfig(GPIO_Remap2_CAN1 , ENABLE);

        // ---------------------------------------------------------------------
        // GPIO configuration (Enable Port Pins) for CAN signal lines

        // Configure CAN1 RX pin
        GPIO_InitStructure.m_GPIO_Pin = GPIO_PIN_0;
        GPIO_InitStructure.m_GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.m_GPIO_Speed = GPIO_Speed_50MHz;
        TgtGPIOInit(GPIOD, &GPIO_InitStructure);

        // Configure CAN1 TX pin
        GPIO_InitStructure.m_GPIO_Pin = GPIO_PIN_1;
        GPIO_InitStructure.m_GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.m_GPIO_Speed = GPIO_Speed_50MHz;
        TgtGPIOInit(GPIOD, &GPIO_InitStructure);

        // ---------------------------------------------------------------------
        // Reset bxCAN-Peripheral
        RCC->APB1RSTR |= RCC_APB1RSTR_CAN1RST;  // set RESET state for CAN1
        RCC->APB1RSTR &= ~RCC_APB1RSTR_CAN1RST; // release RESET state for CAN1

        // ---------------------------------------------------------------------
        // Set Interrupt Vector and interrupt priority
        NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP);

        // ==================== CAN1: RX0 interrupt ==========================
        // Compute the Corresponding IRQ Priority -----------------------------
        bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN1_RX0_PRIORITY, 0);

        // Set Priority: The lower the value the greater the priority.
        NVIC_SetPriority(CAN1_RX0_IRQn, bPriority);

        // Enable the Selected IRQ Channels ------------------------------------
        NVIC_EnableIRQ(CAN1_RX0_IRQn);

        // ==================== CAN1: TX interrupt ===========================
        // Compute the Corresponding IRQ Priority -----------------------------
        bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN1_TX_PRIORITY, 0);

        // Set Priority: The lower the value the greater the priority.
        NVIC_SetPriority(CAN1_TX_IRQn, bPriority);

        // Enable the Selected IRQ Channels ------------------------------------
        NVIC_EnableIRQ(CAN1_TX_IRQn);

        // ==================== CAN1: Error interrupt ==========================
        #if (CDRV_USE_ERROR_ISR != FALSE)
        {
            // Compute the Corresponding IRQ Priority -----------------------------
            bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN1_SCE_PRIORITY, 0);

            // Set Priority: The lower the value the greater the priority.
            NVIC_SetPriority(CAN1_SCE_IRQn, bPriority);

            // Enable the Selected IRQ Channels ------------------------------------
            NVIC_EnableIRQ(CAN1_SCE_IRQn);
        }
        #endif
    }
    #endif  // (CDRV_USED_CAN_CONTROLLER == 0) || (CDRV_MAX_INSTANCES == 2)

    //================================================================================
    #if (CDRV_USED_CAN_CONTROLLER == 1) || (CDRV_MAX_INSTANCES == 2)
    {
        // CAN2 Periph clocks enable
        RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;

        // Remap CAN2 GPIOs
        TgtGPIOPinRemapConfig(GPIO_Remap_CAN2, ENABLE);

        // ---------------------------------------------------------------------
        // GPIO configuration (Enable Port Pins) for CAN signal lines

        // Configure CAN2 RX pin
        GPIO_InitStructure.m_GPIO_Pin = GPIO_PIN_5;
        GPIO_InitStructure.m_GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.m_GPIO_Speed = GPIO_Speed_50MHz;
        TgtGPIOInit(GPIOB, &GPIO_InitStructure);

        // Configure CAN2 TX pin
        GPIO_InitStructure.m_GPIO_Pin = GPIO_PIN_6;
        GPIO_InitStructure.m_GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.m_GPIO_Speed = GPIO_Speed_50MHz;
        TgtGPIOInit(GPIOB, &GPIO_InitStructure);

        // ---------------------------------------------------------------------
        // Reset bxCAN-Peripheral
        RCC->APB1RSTR |= RCC_APB1RSTR_CAN2RST;  // set RESET state for CAN2
        RCC->APB1RSTR &= ~RCC_APB1RSTR_CAN2RST; // release RESET state for CAN2

        // ---------------------------------------------------------------------
        // Set Interrupt Vector and interrupt priority
        NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP);

        // ==================== CAN2: RX0 interrupt ==========================
        // Compute the Corresponding IRQ Priority -----------------------------
        bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN2_RX0_PRIORITY, 0);

        // Set Priority: The lower the value the greater the priority.
        NVIC_SetPriority(CAN2_RX0_IRQn, bPriority);

        // Enable the Selected IRQ Channels ------------------------------------
        NVIC_EnableIRQ(CAN2_RX0_IRQn);

        // ==================== CAN2: TX interrupt ===========================
        // Compute the Corresponding IRQ Priority -----------------------------
        bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN2_TX_PRIORITY, 0);

        // Set Priority: The lower the value the greater the priority.
        NVIC_SetPriority(CAN2_TX_IRQn, bPriority);

        // Enable the Selected IRQ Channels ------------------------------------
        NVIC_EnableIRQ(CAN2_TX_IRQn);


        // ==================== CAN2: Error interrupt ==========================
        #if (CDRV_USE_ERROR_ISR != FALSE)
        {
            // Compute the Corresponding IRQ Priority -----------------------------
            bPriority = NVIC_EncodePriority(NVIC_GetPriorityGrouping(), CAN2_SCE_PRIORITY, 0);

            // Set Priority: The lower the value the greater the priority.
            NVIC_SetPriority(CAN2_SCE_IRQn, bPriority);

            // Enable the Selected IRQ Channels ------------------------------------
            NVIC_EnableIRQ(CAN2_SCE_IRQn);
        }
        #endif
    }
    #endif // (CDRV_USED_CAN_CONTROLLER == 1) || (CDRV_MAX_INSTANCES == 2)

}


// -------------------------------------------------------------------------
//
// Function:    TgtRegisterInstance()
//
// Description: function registers instance pointers for CAN driver
//
// Parameters:  InstanceHdl_p       = instance handle of CAN driver
//              InstancePtr_p       = instance pointer of CAN driver
//
// Returns:     void
//
// -------------------------------------------------------------------------
#if (COP_MAX_INSTANCES > 1)

void PUBLIC TgtRegisterInstance (tCopInstanceHdl InstanceHdl_p, tCopPtrInstance InstancePtr_p)
{

    // register instance pointer for this instance
    aCdrvInstancePtr[InstanceHdl_p] = InstancePtr_p;

}

#endif // (COP_MAX_INSTANCES > 1)


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN1RX0Isr()
//
// Description: CAN interrupt service routine for first CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtCAN1RX0Isr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[0])
        (tCdrvIsrType) kCdrvRxFIFO0Isr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN1RX1Isr()
//
// Description: CAN interrupt service routine for first CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------
void TgtCAN1RX1Isr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[0])
        (tCdrvIsrType) kCdrvRxFIFO1Isr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN1TXIsr()
//
// Description: CAN interrupt service routine for first CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------
void TgtCAN1TXIsr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[0])
        (tCdrvIsrType) kCdrvTxIsr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN1ErrIsr()
//
// Description: CAN interrupt service routine for first CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------
void TgtCAN1ErrIsr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[0])
        (tCdrvIsrType) kCdrvErrorIsr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtEnableCanInterrupt1()
//
// Description: function enables or disables the CAN interrupt 1
//
// Parameters:  bEnable_p           = FALSE = disable / TRUE = enable
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtEnableCanInterrupt1 (BYTE bEnable_p)
{

    if (bEnable_p == FALSE)
    {
        // disable CAN interrupt
        NVIC_DisableIRQ(CAN1_RX0_IRQn);
        NVIC_DisableIRQ(CAN1_RX1_IRQn);
        NVIC_DisableIRQ(CAN1_TX_IRQn);
        NVIC_DisableIRQ(CAN1_SCE_IRQn);
    }
    else
    {
        // enable CAN interrupt
        NVIC_EnableIRQ(CAN1_RX0_IRQn);
        NVIC_EnableIRQ(CAN1_RX1_IRQn);
        NVIC_EnableIRQ(CAN1_TX_IRQn);
        NVIC_EnableIRQ(CAN1_SCE_IRQn);
    }
}

#if ( (TGTHW_STM3210C_EVAL & TGT_CPU_MASK_) == TGT_CPU_STM32F_CL)

// ----------------------------------------------------------------------------
//
// Function:    TgtCAN2RX0Isr()
//
// Description: CAN interrupt service routine for second CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtCAN2RX0Isr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[1])
        (tCdrvIsrType) kCdrvRxFIFO0Isr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN2RX1Isr()
//
// Description: CAN interrupt service routine for second CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtCAN2RX1Isr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[1])
        (tCdrvIsrType) kCdrvRxFIFO1Isr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN2TXIsr()
//
// Description: CAN interrupt service routine for second CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtCAN2TXIsr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[1])
        (tCdrvIsrType) kCdrvTxIsr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtCAN2ErrIsr()
//
// Description: CAN interrupt service routine for second CAN controller
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtCAN2ErrIsr (void)
{

    CdrvInterruptHandler (MCO_INSTANCE_PARAM_ (aCdrvInstancePtr[1])
        (tCdrvIsrType) kCdrvErrorIsr) CDRV_REENTRANT;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtEnableCanInterrupt2()
//
// Description: function enables or disables the CAN interrupt 2
//
// Parameters:  bEnable_p           = FALSE = disable / TRUE = enable
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtEnableCanInterrupt2 (BYTE bEnable_p)
{

    if (bEnable_p == FALSE)
    {
        // disable CAN interrupt
        NVIC_DisableIRQ(CAN2_RX0_IRQn);
        NVIC_DisableIRQ(CAN2_RX1_IRQn);
        NVIC_DisableIRQ(CAN2_TX_IRQn);
        NVIC_DisableIRQ(CAN2_SCE_IRQn);
    }
    else
    {
        // enable CAN interrupt
        NVIC_EnableIRQ(CAN2_RX0_IRQn);
        NVIC_EnableIRQ(CAN2_RX1_IRQn);
        NVIC_EnableIRQ(CAN2_TX_IRQn);
        NVIC_EnableIRQ(CAN2_SCE_IRQn);
    }
}

#endif


/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <System Timer Function>                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

#define SYSTEM_CLOCK            SYSCLK_FREQ_72MHz
#define TICKS_PER_SECOND        1000
#define TgtTimerIsr             SysTick_Handler


//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------

static tTime NEAR TimerValue_g;


//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

// ----------------------------------------------------------------------------
//
// Function:    TgtInitTimer()
//
// Description: function initializes timer
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtInitTimer (void)
{

    // set system clock
    SysTick_Config(SYSTEM_CLOCK / TICKS_PER_SECOND);

    TimerValue_g = 0;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtTimerIsr()
//
// Description: interrupt service routine for timer
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------
void TgtTimerIsr (void)
{

    TimerValue_g += 10;

}


// ----------------------------------------------------------------------------
//
// Function:    TgtGetTickCount()
//
// Description: function returns timer tick (based by 100us)
//
// Parameters:  void
//
// Returns:     tTime               = timer tick
//
// ----------------------------------------------------------------------------

tTime PUBLIC TgtGetTickCount (void)
{

    // Declaration of variables in functions should be initialize it with an value.
    // Like: tTime TimerTickTemp = 0;
    // But at this place time is critical. We have to prevent much code memory for
    // faster speed.
    tTime TimerTickTemp;

    // get tick count from global variable
    TimerTickTemp = TimerValue_g;

    return TimerTickTemp;

}


/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <Serial line interface>                             */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

#define TGT_USED_UART           2
#define __USART_BAUDRATE        115200
#define __USART_DATABITS        0x00000000
#define __USART_STOPBITS        0x00000000
#define __USART_PARITY          0x00000000
#define __USART_FLOWCTRL        0x00000000
#define __PCLK2                 SYSCLK_FREQ_72MHz
#define __PCLK1                 SYSCLK_FREQ_72MHz


#if (TGT_USED_UART == 2)
    #define __USART_BASE        USART2
    #define __USART_PCLK        (__PCLK1 >> 1)
    #define __USART2_REMAP      0x08
    #define __USART_GPIO_ENABLE() { \
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;         /* enable clock for Alternate Function          */ \
        AFIO->MAPR   |= __USART2_REMAP;             /* set   USART2 remap                           */ \
        RCC->APB2ENR |=  RCC_APB2ENR_IOPDEN;        /* enable clock for GPIOD                       */ \
        GPIOD->CRL   &= ~(0xFFUL  << 20);           /* Clear PD5, PD6                               */ \
        GPIOD->CRL   |=  (0x0BUL  << 20);           /* USART2 Tx (PD5)  alternate output push-pull  */ \
        GPIOD->CRL   |=  (0x04UL  << 24);           /* USART2 Rx (PD6)  input floating              */ \
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN; }     /* enable clock for USART2 */
#else
    #error 'ERROR: wrong USART configuration!'
#endif


//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

// ----------------------------------------------------------------------------
//
// Function:    TgtInitSerial()
//
// Description: function initializes serial interface
//
// Parameters:  void
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void PUBLIC TgtInitSerial (void)
{

    __USART_GPIO_ENABLE ();

    __USART_BASE->BRR  = __USART_BRR(__USART_PCLK, __USART_BAUDRATE);  // set baudrate
    __USART_BASE->CR1  = __USART_DATABITS;                        // set Data bits
    __USART_BASE->CR2  = __USART_STOPBITS;                        // set Stop bits
    __USART_BASE->CR1 |= __USART_PARITY;                          // set Parity
    __USART_BASE->CR3  = __USART_FLOWCTRL;                        // Set Flow Control

    __USART_BASE->CR1 |= (USART_CR1_RE | USART_CR1_TE);           // RX, TX enable
    __USART_BASE->CR1 |= USART_CR1_UE;                            // USART enable

}

#if defined(INIT_SERIAL) && (!defined(USE_SERIAL_BUFFER) || (USE_SERIAL_BUFFER == FALSE))

//---------------------------------------------------------------------------
//
// Function:    SendChar()
//
// Description: Write character to Serial Port
//
// Parameters:  ch
//
// Return:      int
//
// State:       tested r.d.
//
//---------------------------------------------------------------------------

int SendChar (int ch)
{

    if (ch == '\n')
        SendChar ('\r');

    while (!(__USART_BASE->SR & USART_SR_TXE));
    __USART_BASE->DR = (ch & 0x1FF);

    return (ch);

}


//---------------------------------------------------------------------------
//
// Function:    GetKey()
//
// Description: Read character from Serial Port
//
// Parameters:  void
//
// Return:      int
//
// State:       tested r.d.
//
//---------------------------------------------------------------------------

int GetKey (void)
{

    while (!(__USART_BASE->SR & USART_SR_RXNE));

    return ((int)(__USART_BASE->DR & 0x1FF));

}

#endif


/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <GPIO INIT Function>                                */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

#define LSB_MASK                    ((DWORD)0x0000FFFF)
#define DBGAFR_POSITION_MASK        ((DWORD)0x000F0000)
#define DBGAFR_SWJCFG_MASK          ((DWORD)0xF0FFFFFF)
#define DBGAFR_LOCATION_MASK        ((DWORD)0x00200000)
#define DBGAFR_NUMBITS_MASK         ((DWORD)0x00100000)


//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
//
// Function:    TgtGPIOInit()
//
// Description: Initializes the GPIOx peripheral according to the specified
//              parameters in the GPIO_InitStruct.
//
// Parameters:  GPIOx: where x can be (A..G) to select the GPIO peripheral.
//              GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
//                               contains the configuration information for
//                               the specified GPIO peripheral.
// Return:      none
//
// State:       not tested
//
//---------------------------------------------------------------------------

static void TgtGPIOInit(GPIO_TypeDef* GPIOx_p, tGPIOInit* GPIOInit_p)
{
DWORD currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
DWORD tmpreg = 0x00, pinmask = 0x00;

    //---------------------------- GPIO Mode Configuration -----------------------
    currentmode = ((DWORD)GPIOInit_p->m_GPIO_Mode) & ((DWORD)0x0F);
    if ((((DWORD)GPIOInit_p->m_GPIO_Mode) & ((DWORD)0x10)) != 0x00)
    {
        // Output mode
        currentmode |= (DWORD)GPIOInit_p->m_GPIO_Speed;
    }

    //---------------------------- GPIO CRL Configuration ------------------------
    // Configure the eight low port pins
    if (((DWORD)GPIOInit_p->m_GPIO_Pin & ((DWORD)0x00FF)) != 0x00)
    {
        // read old value
        tmpreg = GPIOx_p->CRL;
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = ((DWORD)0x01) << pinpos;
            // Get the port pins position
            currentpin = (GPIOInit_p->m_GPIO_Pin) & pos;
            if (currentpin == pos)
            {
                pos = pinpos << 2;

                // Clear the corresponding low control register bits
                pinmask = ((DWORD)0x0F) << pos;
                tmpreg &= ~pinmask;

                // Write the mode configuration in the corresponding bits
                tmpreg |= (currentmode << pos);

                // Reset the corresponding ODR bit
                if (GPIOInit_p->m_GPIO_Mode == GPIO_Mode_IPD)
                {
                   GPIOx_p->BRR = (((DWORD)0x01) << pinpos);
                }
                else
                {
                    // Set the corresponding ODR bit
                    if (GPIOInit_p->m_GPIO_Mode == GPIO_Mode_IPU)
                    {
                        GPIOx_p->BSRR = (((DWORD)0x01) << pinpos);
                    }
                }
            }
        }
        // set new value
        GPIOx_p->CRL = tmpreg;
    }

    //---------------------------- GPIO CRH Configuration ------------------------
    // Configure the eight high port pins
    if (GPIOInit_p->m_GPIO_Pin > 0x00FF)
    {
        tmpreg = GPIOx_p->CRH;
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((DWORD)0x01) << (pinpos + 0x08));

            // Get the port pins position
            currentpin = ((GPIOInit_p->m_GPIO_Pin) & pos);
            if (currentpin == pos)
            {
                pos = pinpos << 2;

                // Clear the corresponding high control register bits
                pinmask = ((DWORD)0x0F) << pos;
                tmpreg &= ~pinmask;

                // Write the mode configuration in the corresponding bits
                tmpreg |= (currentmode << pos);

                // Reset the corresponding ODR bit
                if (GPIOInit_p->m_GPIO_Mode == GPIO_Mode_IPD)
                {
                    GPIOx_p->BRR = (((DWORD)0x01) << (pinpos + 0x08));
                }

                // Set the corresponding ODR bit
                if (GPIOInit_p->m_GPIO_Mode == GPIO_Mode_IPU)
                {
                    GPIOx_p->BSRR = (((DWORD)0x01) << (pinpos + 0x08));
                }
            }
        }
        GPIOx_p->CRH = tmpreg;
    }

}


//---------------------------------------------------------------------------
//
// Function:    TgtGPIOPinRemapConfig()
//
// Description: Changes the mapping of the specified pin.
//
// Parameters:  This parameter can be one of the following values:
//              GPIO_Remap_SPI1
//              GPIO_Remap_I2C1
//              GPIO_Remap_USART1
//              GPIO_Remap_USART2
//              GPIO_PartialRemap_USART3
//              GPIO_FullRemap_USART3
//              GPIO_PartialRemap_TIM1
//              GPIO_FullRemap_TIM1
//              GPIO_PartialRemap1_TIM2
//              GPIO_PartialRemap2_TIM2
//              GPIO_FullRemap_TIM2
//              GPIO_PartialRemap_TIM3
//              GPIO_FullRemap_TIM3
//              GPIO_Remap_TIM4
//              GPIO_Remap1_CAN1
//              GPIO_Remap2_CAN1
//              GPIO_Remap_PD01
//              GPIO_Remap_TIM5CH4_LSI
//              GPIO_Remap_ADC1_ETRGINJ
//              GPIO_Remap_ADC1_ETRGREG
//              GPIO_Remap_ADC2_ETRGINJ
//              GPIO_Remap_ADC2_ETRGREG
//              GPIO_Remap_ETH
//              GPIO_Remap_CAN2
//              GPIO_Remap_SWJ_NoJTRST
//              GPIO_Remap_SWJ_JTAGDisable
//              GPIO_Remap_SWJ_Disable
//              GPIO_Remap_SPI3
//              GPIO_Remap_TIM2ITR1_PTP_SOF
//              GPIO_Remap_PTP_PPS
//              GPIO_Remap_TIM15
//              GPIO_Remap_TIM16
//              GPIO_Remap_TIM17
//              GPIO_Remap_CEC
//              GPIO_Remap_TIM1_DMA
//
//       Note:  If the GPIO_Remap_TIM2ITR1_PTP_SOF is enabled
//              the TIM2 ITR1 is connected to Ethernet PTP output.
//              When Reset TIM2 ITR1 is connected to USB OTG SOF output.
//
//              NewState: new state of the port pin remapping.
//                        This parameter can be: ENABLE or DISABLE.
//
// Return:      none
//
// State:       not tested
//
//---------------------------------------------------------------------------

static void TgtGPIOPinRemapConfig(DWORD GPIO_Remap, WORD NewState)
{
DWORD tmp = 0x00, tmp1 = 0x00, tmpreg = 0x00, tmpmask = 0x00;

    if((GPIO_Remap & 0x80000000) == 0x80000000)
    {
        tmpreg = AFIO->MAPR2;
    }
    else
    {
        tmpreg = AFIO->MAPR;
    }

    tmpmask = (GPIO_Remap & DBGAFR_POSITION_MASK) >> 0x10;
    tmp = GPIO_Remap & LSB_MASK;

    if ((GPIO_Remap & (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK)) == (DBGAFR_LOCATION_MASK | DBGAFR_NUMBITS_MASK))
    {
        tmpreg &= DBGAFR_SWJCFG_MASK;
        AFIO->MAPR &= DBGAFR_SWJCFG_MASK;
    }
    else if ((GPIO_Remap & DBGAFR_NUMBITS_MASK) == DBGAFR_NUMBITS_MASK)
    {
        tmp1 = ((DWORD)0x03) << tmpmask;
        tmpreg &= ~tmp1;
        tmpreg |= ~DBGAFR_SWJCFG_MASK;
    }
    else
    {
        tmpreg &= ~(tmp << ((GPIO_Remap >> 0x15)*0x10));
        tmpreg |= ~DBGAFR_SWJCFG_MASK;
    }

    if (NewState != DISABLE)
    {
        tmpreg |= (tmp << ((GPIO_Remap >> 0x15)*0x10));
    }

    if((GPIO_Remap & 0x80000000) == 0x80000000)
    {
        AFIO->MAPR2 = tmpreg;
    }
    else
    {
        AFIO->MAPR = tmpreg;
    }

}


/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <System Clock Configuration>                        */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//   IMPORTANT NOTE:
//   ==============
//   1. After each device reset the HSI is used as System clock source.
//
//   2. Please make sure that the selected System clock doesn't exceed your device's
//      maximum frequency.
//
//   3. If none of the define below is enabled, the HSI is used as System clock
//    source.
//
//   4. The System clock configuration functions provided within this file assume that:
//        - For Low and Medium density Value line devices an external 8MHz crystal
//          is used to drive the System clock.
//        - For Low, Medium and High density devices an external 8MHz crystal is
//          used to drive the System clock.
//        - For Connectivity line devices an external 25MHz crystal is used to drive
//          the System clock.
//     If you are using different crystal you have to adapt those functions accordingly.
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

#ifdef SYSCLK_FREQ_HSE
    static void TgtSetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_72MHz
    static void TgtSetSysClockTo72(void);
#endif


//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
//
// Function:    TgtSetSysClock()
//
// Description: Configures the System clock frequency, HCLK, PCLK2 and
//              PCLK1 prescalers.
//
//              Three different clock sources cab be used to drive the
//              system clock (SYSCLK):
//              - HSI (high speed internal clock)
//              - HSE (high speed external clock)
//              - PLL clock
//
//              Performance and Connectivity line supports 72MHz SYSCLK.
//
// Parameters:  none
//
// Return:      none
//
// State:       not tested
//
//---------------------------------------------------------------------------

static void TgtSetSysClock(void)
{

    //----------------------------------------------------------------------
    // Reset the RCC clock configuration to the default reset state(for debug purpose)
    // Set HSION bit
    RCC->CR |= (DWORD)0x00000001;

    // Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits
    #ifndef STM32F10X_CL
    {
        RCC->CFGR &= (DWORD)0xF8FF0000;
    }
    #else
    {
        RCC->CFGR &= (DWORD)0xF0FF0000;
    }
    #endif // STM32F10X_CL

    // Reset HSEON, CSSON and PLLON bits
    RCC->CR &= (DWORD)0xFEF6FFFF;

    // Reset HSEBYP bit
    RCC->CR &= (DWORD)0xFFFBFFFF;

    // Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits
    RCC->CFGR &= (DWORD)0xFF80FFFF;

    #ifdef STM32F10X_CL
    {
        //  Reset PLL2ON and PLL3ON bits
        RCC->CR &= (DWORD)0xEBFFFFFF;

        // Disable all clock interrupts and clear pending bits
        RCC->CIR = 0x00FF0000;

        // Reset CFGR2 register
        RCC->CFGR2 = 0x00000000;
    }
    #elif defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL)
    {
        // Disable all clock interrupts and clear pending bits
        RCC->CIR = 0x009F0000;

        // Reset CFGR2 register
        RCC->CFGR2 = 0x00000000;
    }
    #else
    {
        // Disable all interrupts and clear pending bits
        RCC->CIR = 0x009F0000;
    }
    #endif // STM32F10X_CL

    //----------------------------------------------------------------------
    #ifdef SYSCLK_FREQ_HSE
    {
        TgtSetSysClockToHSE();
    }
    #elif defined (SYSCLK_FREQ_72MHz)
    {
        TgtSetSysClockTo72();
    }
    #endif

    // If none of the define above is enabled, the HSI is used as System clock
    // source (default after reset)
}

#ifdef SYSCLK_FREQ_HSE

//---------------------------------------------------------------------------
//
// Function:    TgtSetSysClockToHSE()
//
// Description: Selects HSE as System clock source and configure HCLK, PCLK2
//              and PCLK1 prescalers.
//
//        Note: This function should be used only after reset.
//
// Parameters:  none
//
// Return:      none
//
// State:       not tested
//
//---------------------------------------------------------------------------

static void TgtSetSysClockToHSE(void)
{
__IO DWORD StartUpCounter = 0, HSEStatus = 0;

    // SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    // Enable HSE
    RCC->CR |= ((DWORD)RCC_CR_HSEON);

    // Wait till HSE is ready and if Time out is reached exit
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    }
    while((HSEStatus == 0) && (StartUpCounter != HSEStartUp_TimeOut));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (DWORD)0x01;
    }
    else
    {
        HSEStatus = (DWORD)0x00;
    }

    if (HSEStatus == (DWORD)0x01)
    {
        #if !defined (STM32F10X_LD_VL) && !defined (STM32F10X_MD_VL)
        {
            // Enable Prefetch Buffer
            FLASH->ACR |= FLASH_ACR_PRFTBE;

            // Flash 0 wait state
            FLASH->ACR &= (DWORD)((DWORD)~FLASH_ACR_LATENCY);

            #ifndef STM32F10X_CL
            {
                FLASH->ACR |= (DWORD)FLASH_ACR_LATENCY_0;
            }
            #else
            if (HSE_Value <= 24000000)
            {
                FLASH->ACR |= (DWORD)FLASH_ACR_LATENCY_0;
            }
            else
            {
                FLASH->ACR |= (DWORD)FLASH_ACR_LATENCY_1;
            }
            #endif // STM32F10X_CL
        }
        #endif

        // HCLK = SYSCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_HPRE_DIV1;

        // PCLK2 = HCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_PPRE2_DIV1;

        // PCLK1 = HCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_PPRE1_DIV1;

        // Select HSE as system clock source
        RCC->CFGR &= (DWORD)((DWORD)~(RCC_CFGR_SW));
        RCC->CFGR |= (DWORD)RCC_CFGR_SW_HSE;

        // Wait till HSE is used as system clock source
        while ((RCC->CFGR & (DWORD)RCC_CFGR_SWS) != (DWORD)0x04)
            ;
    }
    else
    {
        // If HSE fails to start-up, the application will have wrong clock
        // configuration. User can add here some code to deal with this error
    }

}

#elif defined SYSCLK_FREQ_72MHz


//---------------------------------------------------------------------------
//
// Function:    TgtSetSysClockTo72()
//
// Description: Sets System clock frequency to 72MHz and configure HCLK, PCLK2
//              and PCLK1 prescalers.
//
//        Note: This function should be used only after reset.
//
// Parameters:  none
//
// Return:      none
//
// State:       not tested
//
//---------------------------------------------------------------------------

static void TgtSetSysClockTo72(void)
{
__IO DWORD StartUpCounter = 0, HSEStatus = 0;

    // SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------
    // Enable HSE
    RCC->CR |= ((DWORD)RCC_CR_HSEON);

    // Wait till HSE is ready and if Time out is reached exit
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSEStartUp_TimeOut));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (DWORD)0x01;
    }
    else
    {
        HSEStatus = (DWORD)0x00;
    }

    if (HSEStatus == (DWORD)0x01)
    {
        // Enable Prefetch Buffer
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        // Flash 2 wait state
        FLASH->ACR &= (DWORD)((DWORD)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (DWORD)FLASH_ACR_LATENCY_2;

        // HCLK = SYSCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_HPRE_DIV1;

        // PCLK2 = HCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_PPRE2_DIV1;

        // PCLK1 = HCLK
        RCC->CFGR |= (DWORD)RCC_CFGR_PPRE1_DIV2;

        #ifdef STM32F10X_CL
        {
            // Configure PLLs ------------------------------------------------------
            // PLL2 configuration: PLL2CLK = (HSE / 5) * 8 = 40 MHz
            // PREDIV1 configuration: PREDIV1CLK = PLL2 / 5 = 8 MHz

            /*RCC->CFGR2 &= (DWORD)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL |
                                      RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
            RCC->CFGR2 |= (DWORD)(RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PLL2MUL8 |
                                     RCC_CFGR2_PREDIV1SRC_PLL2 | RCC_CFGR2_PREDIV1_DIV5);

            // Enable PLL2
            RCC->CR |= RCC_CR_PLL2ON;

            // Wait till PLL2 is ready
            while((RCC->CR & RCC_CR_PLL2RDY) == 0)
                ;
			*/
            // PLL configuration: PLLCLK = PREDIV1 * 9 = 72 MHz
            RCC->CFGR &= (DWORD)~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL);
            RCC->CFGR |= (DWORD)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 |
                                    RCC_CFGR_PLLMULL9);
        }
        #else
        {
            //  PLL configuration: PLLCLK = HSE * 9 = 72 MHz
            RCC->CFGR &= (DWORD)((DWORD)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                                RCC_CFGR_PLLMULL));
            RCC->CFGR |= (DWORD)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
        }
        #endif // STM32F10X_CL

        // Enable PLL
        RCC->CR |= RCC_CR_PLLON;

        // Wait till PLL is ready
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
            ;

        // Select PLL as system clock source
        RCC->CFGR &= (DWORD)((DWORD)~(RCC_CFGR_SW));
        RCC->CFGR |= (DWORD)RCC_CFGR_SW_PLL;

        // Wait till PLL is used as system clock source
        while ((RCC->CFGR & (DWORD)RCC_CFGR_SWS) != (DWORD)0x08)
            ;
    }
    else
    {
        // If HSE fails to start-up, the application will have wrong clock
        // configuration. User can add here some code to deal with this error
    }

}

#endif




/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          C L A S S  <MISC>                                              */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
//
//  Description:
//
//
/***************************************************************************/


//=========================================================================//
//                                                                         //
//          P R I V A T E   D E F I N I T I O N S                          //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
// const defines
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// lokale vars
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// local function prototypes
//---------------------------------------------------------------------------

//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

// ----------------------------------------------------------------------------
//
// Function:    TgtMemCpy()
//
// Description: function copies a buffer to an other one
//
// Parameters:  pDst_p              = desination pointer
//              pSrc_p              = source pointer
//              wSiz_p              = number of bytes to copy (max. 65535)
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtMemCpy (void GENERIC* pDst_p, void GENERIC* pSrc_p, WORD wSiz_p)
{
BYTE GENERIC* dst   = pDst_p;
BYTE GENERIC* src   = pSrc_p;

    while (wSiz_p > 0)
    {
        *dst = *src;
        src++;
        dst++;
        wSiz_p--;
    }

}


// ----------------------------------------------------------------------------
//
// Function:    TgtMemSet()
//
// Description: function sets a value to a buffer
//
// Parameters:  pDst_p              = desination pointer
//              bVal_p              = value to be filled in
//              wSiz_p              = number of bytes in buffer (max. 65535)
//
// Returns:     void
//
// ----------------------------------------------------------------------------

void TgtMemSet (void GENERIC* pDst_p, BYTE bVal_p, WORD wSiz_p)
{
BYTE GENERIC* dst   = pDst_p;

    while (wSiz_p > 0)
    {
        *dst = bVal_p;
        dst++;
        wSiz_p--;
    }

}


// EOF
