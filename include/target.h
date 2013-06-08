/****************************************************************************

  (c) SYSTEC electronic GmbH, D-07973 Greiz, August-Bebel-Str. 29
      www.systec-electronic.de

  Project:      CANopen V5

  Description:  interface for target specific functions

  -------------------------------------------------------------------------

                $RCSfile: Target.h,v $

                $Author: R.Dietzsch $

                $Revision: 1.131 $  $Date: 2011/06/30 08:05:30 $

                $State: Exp $

                Build Environment:
                    all

  -------------------------------------------------------------------------

  Revision History:
  2004/08/18 f.j.:  neue Funktion TgtGetBitrateTabPtr() fuer 1131-Anbindung
                    ergaenzt, um diese Targetabhaengigkeit aus dem CcmHor.c
                    zu entfernen.

  2004/10/13 f.j.:  include ARM7 target

****************************************************************************/

#ifndef _TARGET_H_
#define _TARGET_H_

// =========================================================================
// type definitions
// =========================================================================

// type tTime for all timer of CANopen
// If this type is defined to WORD then all timer only can run until
// 6.5536 seconds. All greater values will be cut without generating an error.
#if (COP_USE_SMALL_TIME != FALSE)

    typedef WORD tTime;

#else

    typedef DWORD tTime;

#endif


// =========================================================================
// defines for TARGET_HARDWARE
// =========================================================================

// information about the board manufacturer
#define TGT_BRD_MASK_               0xFF000000L     // board mask
    #define TGT_BRD_PKC             0x00000000L     // Phytec KitCON
    #define TGT_BRD_PMM             0x01000000L     // Phytec Mini Modul
    #define TGT_BRD_PNM             0x02000000L     // Phytec Nano Modul
    #define TGT_BRD_PPC             0x03000000L     // Phytec PHYCORE
    #define TGT_BRD_TCI             0x04000000L     // Systec TeleCANi
    #define TGT_BRD_FDK             0x05000000L     // Fujitsu DEV-Kits
    #define TGT_BRD_GLYN            0x06000000L     // Mitsubishi M306NAFGTFP
    #define TGT_BRD_SMC             0x07000000L     // Systec multiCOM/IO
    #define TGT_BRD_SDM             0x08000000L     // Systec DipModul
    #define TGT_BRD_SGW             0x09000000L     // Systec GW-003
    #define TGT_BRD_SSV             0x0A000000L     // SSV DILI/NetPC 5280
    #define TGT_BRD_SCIO            0x0B000000L     // Systec CANopen IO xyz
    #define TGT_BRD_PLC             0x0E000000L     // Systec PLCcore-xyz
    #define TGT_BRD_TRIBOARD        0x0F000000L     // Infineon TriBoard
    #define TGT_BRD_EXPLORER16      0x10000000L     // Microchip Explorer16 Development Board
    #define TGT_BRD_IEK             0x11000000L     // Infineon Easy Kits
    #define TGT_BRD_KEIL            0x12000000L     // Keil Kit
    #define TGT_BRD_RSKP            0x20000000L     // Renesas Starter Kit Plus
    #define TGT_BRD_ATMDVK          0x21000000L     // Atmel Development Kits
    #define TGT_BRD_SD_EZDSP        0x22000000L     // Spectrum Digital Incorporated eZdsp Board
    #define TGT_BRD_CODE_RED        0x79000000L     // Code Red Development Board
	#define TGT_BRD_ST              0x7A000000L     // ST Microelectronics Eval-Board
    #define TGT_BRD_BLDC_RDK        0x7B000000L     // Luminary Micro BLDC Motor Control RDK
    #define TGT_BRD_COLIBRI         0x7C000000L     // Toradex Colibri for WinCE
    #define TGT_BRD_NETBURNER       0x7D000000L     // NetBurner Board
    #define TGT_BRD_NETDCU          0x7E000000L     // NETDCU for WinCE
    #define TGT_BRD_PC              0x7F000000L     // personal computer
    #define TGT_BRD_KSP             0x80000000L     // Systec KSP till 0xFF000000L
    #define TGT_BRD_KSPS0211        (TGT_BRD_KSP + 0x01000000L) // KSPS-0211
    #define TGT_BRD_KSPS0305        (TGT_BRD_KSP + 0x02000000L) // KSPS-0305
    #define TGT_BRD_KSPS0609        (TGT_BRD_KSP + 0x03000000L) // KSPS-0609
    #define TGT_BRD_KSPS0806ZR      (TGT_BRD_KSP + 0x04000000L) // KSPS-0806 (ZR)
    #define TGT_BRD_KSPS0806BS      (TGT_BRD_KSP + 0x05000000L) // KSPS-0806 (BS)
    #define TGT_BRD_KSPS0806ABF     (TGT_BRD_KSP + 0x06000000L) // KSPS-0806 (ABF)
    #define TGT_BRD_KSPS0806PWR     (TGT_BRD_KSP + 0x07000000L) // KSPS-0806 (PWR)
    #define TGT_BRD_KSPS0806LC      (TGT_BRD_KSP + 0x08000000L) // KSPS-0806 (LC)

     // r.d.: please do not set any CPU specific information or board version information to the board name!!
    #define TGT_BRD_DK              TGT_BRD_FDK     // Fujitsu DEV-Kit16        (note: a define for a board type does not have any information about the CPU!)
    #define TGT_BRD_PLCCF54         TGT_BRD_PLC     // Systec ECUcore-5484      (note: a define for a board type does not have any information about the CPU!)
    #define TGT_BRD_SC12            TGT_BRD_SCIO    // Systec CANopen IO C12    (note: a define for a board type does not have any information about the CPU!)
    #define TGT_BRD_SC17            TGT_BRD_SCIO    // Systec CANopen IO C17    (note: a define for a board type does not have any information about the CPU!)
    #define TGT_BRD_SC14            TGT_BRD_SCIO    // Systec CANopen IO C14    (note: a define for a board type does not have any information about the CPU!)
    #define TGT_BRD_EKXE167F        TGT_BRD_IEK     // Infineon Easy Kit XE167F (note: a define for a board type does not have any information about the CPU!)

// information about the CPU manufacturer
#define TGT_MAN_MASK_               0x00F00000L     // manufacturer mask
    #define TGT_MAN_INF             0x00000000L     // Infineon
    #define TGT_MAN_PHI             0x00100000L     // Philips
    #define TGT_MAN_NXP             0x00100000L     // NXP (came from Philips)
    #define TGT_MAN_FUJ             0x00200000L     // Fujitsu
    #define TGT_MAN_MOT             0x00300000L     // Motorolla
    #define TGT_MAN_DAL             0x00400000L     // Dallas
    #define TGT_MAN_ATM             0x00500000L     // Atmel
    #define TGT_MAN_INT             0x00600000L     // Intel
    #define TGT_MAN_AMD             0x00700000L     // AMD
    #define TGT_MAN_MIT             0x00800000L     // Mitsubishi
    #define TGT_MAN_ADI             0x00900000L     // Analog Device
    #define TGT_MAN_BCK             0x00A00000L     // Beck IPC
    #define TGT_MAN_MCH             0x00B00000L     // Microchip Technology Inc.
    #define TGT_MAN_ALCH            0x00C00000L     // AMD Alchemy CPU
    #define TGT_MAN_RENE            0x00D00000L     // Renesas
    #define TGT_MAN_LUMINARY        0x00E00000L     // Luminary Micro
    #define TGT_MAN_TI              0x00F00000L     // Texas Instruments
    #define TGT_MAN_ST              0x00F00000L     // ST Microelectronics
    #define TGT_MAN_SL              0x00F00000L     // Silabs
    #define TGT_MAN_DUMMY           0x00F00000L     // dummy for any manufacturer

#define TGT_ADD_MASK_               0x000FF000L     // additional mask (TGT_ADD_IMASK and TGT_ADD_EMASK are obsolete - do not use for new projctes)
#define TGT_ADD_IMASK_              0x000F0000L     // additional mask (internal)
#define TGT_ADD_EMASK_              0x0000F000L     // additional mask  (external)
    #define TGT_ADD_E1000           0x00001000L     // external SJA1000
    #define TGT_ADD_E527            0x00002000L     // external FullCAN 527
    #define TGT_ADD_PEAK            0x00003000L     // Peak CAN hardware (PCI, Dongle, ISA, USB)
    #define TGT_ADD_WRAPP           0x00004000L     // systec CAN wrapper DLL
    #define TGT_ADD_PCIO_1000       0x00005000L     // SJA1000 in I/O of PC , e.g. phytec pcNetCAN/eNetCAN
    #define TGT_ADD_NETDCU          0x00006000L     // NETDCU-ADP/CAN2
    #define TGT_ADD_EPEAK           0x00007000L     // eCospro CAN driver for Peak PCI CAN card
    #define TGT_ADD_EMCP2515        0x00008000L     // external MicroChip 2515
    #define TGT_ADD_TORADEX         0x00009000L     // Toradex CAN driver at Colibri
    #define TGT_ADD_TDRV011         0x0000A000L     // TEWS CAN driver on 2 channel extended CAN "TPMC816"
    #define TGT_ADD_CDRVSER         0x0000B000L     // COM-Port of PC
    #define TGT_ADD_ESD_NTCAN       0x0000C000L     // NTCAN.DLL interface from ESD GmbH
    #define TGT_ADD_I1000           0x00010000L     // internal SJA1000
    #define TGT_ADD_I527            0x00020000L     // internal FullCAN 527
    #define TGT_ADD_I527_E1000      0x00021000L     // internal FullCAN 527 and external SJA1000
    #define TGT_ADD_ITOU_CAN        0x00030000L     // internal Motorola TouCAN for PPC5x5
    #define TGT_ADD_ITWIN           0x00040000L     // internal TwinCAN
    #define TGT_ADD_IFLEX_CAN       0x00050000L     // internal Motorola FlexCAN for MCF5282
    #define TGT_ADD_ICC03_CAN       0x00060000L     // internal Atmel CAN in T89C51CC03
    #define TGT_ADD_IFUJ16FX_CAN    0x00070000L     // internal Fujitsu CAN in 16FX series
    #define TGT_ADD_I7A3_CAN        0x00080000L     // internal Atmel CAN e.g. in AT91SAM7A3
    //#define TGT_ADD_ICAN128         0x00081000L     // internal Atmel CAN128 e.g. in AT90CAN128
    #define TGT_ADD_I306_CAN        0x00090000L     // internal Mitsubishi CAN
    #define TGT_ADD_IFUJ_CAN        0x000A0000L     // internal Fujitsu CAN
    #define TGT_ADD_ITRI_CAN        0x000B0000L     // internal Infineon MultiCAN (TriCore, XE16x)
    #define TGT_ADD_IECAN           0x000C0000L     // internal Microchip Enhanced CAN
    #define TGT_ADD_IM32C_CAN       0x000D0000L     // internal Renesas CAN
    #define TGT_ADD_ILPC22XX        0x000E0000L     // internal CAN controller of LPC21xx and LPC22xx families
    #define TGT_ADD_ISTELLARIS_CAN  0x000F0000L     // internal Stellaris CAN
    #define TGT_ADD_BOSCH_CAN       0x000F0000L     // Bosch CAN Controller
    #define TGT_ADD_ITMS            0x000F1000L     // internal eCAN of TI's TMS320Cxxxx families
    #define TGT_ADD_ISTM32F_BXCAN   0x000F2000L     // internal bxCAN-Controller for ST STM32F
    #define TGT_ADD_IPIC32MX_CAN    0x000F3000L     // internal CAN controller of Microchips PIC32MX series
    #define TGT_ADD_UCAN            0x000F4000L     // systec USBCAN32.DLL

#define TGT_CPU_MASK_               0x00000FFFL     // cpu mask
    #define TGT_CPU_ARM7            0x00000007L     // ARM7
    #define TGT_CPU_ARM9            0x00000009L     // ARM9
    #define TGT_CPU_51              0x00000051L     // 8051
    #define TGT_CPU_PIC32           0x00000032L     // Microchip PIC32
    #define TGT_CPU_CORTEX_M3       0x000000C3L     // CORTEX M3 CPU
    #define TGT_CPU_1130            0x00000113L     // Infineon TriCore 1130
    #define TGT_CPU_113             TGT_CPU_1130    // <-- r.d.: this is obsolete
    #define TGT_CPU_AVR8            0x00000128L     // Atmel AT90CAN128 (AVR)
    #define TGT_CPU_164             0x00000164L     // Infineon C164
    #define TGT_CPU_165             0x00000165L     // Infineon C165
    #define TGT_CPU_166             0x00000166L     // Infineon C166
    #define TGT_CPU_167             0x00000167L     // Infineon C167
    #define TGT_CPU_1766            0x00000176L     // Infineon TC1766
    #define TGT_CPU_1796            0x00000179L     // Infineon TriCore 1796
    #define TGT_CPU_179             TGT_CPU_1796    // <-- r.d.: this is obsolete
    #define TGT_CPU_186             0x00000186L     // Intel 186
    #define TGT_CPU_196             0x00000196L     // 196
    #define TGT_CPU_286             0x00000286L     // Intel 286
    #define TGT_CPU_306NA           0x00000306L     // Mitsubishi M306NAFGTFP
    #define TGT_CPU_320             0x00000320L     // Texas Instrument TMS320xxxx
    #define TGT_CPU_STM32F          0x0000032FL     // STM32F10xxx
    #define TGT_CPU_STM32F_CL       (TGT_CPU_STM32F + 0)     // STM32F10xxx Connectivity Line
    #define TGT_CPU_STM32F_PL       (TGT_CPU_STM32F + 0x800) // STM32F10xxx Performance Line
    #define TGT_CPU_340             0x00000340L     // Fujitsu MB90F340
    #define TGT_CPU_348             0x00000348L     // Fujitsu MB96F348HS
    #define TGT_CPU_350             0x00000350L     // Fujitsu MB90F350
    #define TGT_CPU_384FJ           0x00000384L     // Renesas M32C/84FJ
    #define TGT_CPU_386             0x00000386L     // Intel 386, 486, ...
    #define TGT_CPU_DSPIC33F        0x0000033FL     // Microchip dsPIC33F series
    //#define TGT_CPU_486             0x00000486L     // Intel 486
    #define TGT_CPU_495             0x00000495L     // 495
    #define TGT_CPU_505             0x00000505L     // Infineon C505
    #define TGT_CPU_515             0x00000515L     // Infineon C515
    #define TGT_CPU_527             0x00000527L     // Infineon 527
    #define TGT_CPU_543             0x00000543L     // Fujitsu 543
    #define TGT_CPU_586             0x00000586L     // Intel 586 (Pentium)
    #define TGT_CPU_590             0x00000590L     // Infineon 590
    #define TGT_CPU_591             0x00000591L     // Infineon 591
    #define TGT_CPU_592             0x00000592L     // Infineon 592
    #define TGT_CPU_CC01            0x00000CC1L     // Atmel 51CC01
    #define TGT_CPU_CC03            0x00000CC3L     // Atmel 51CC03
    #define TGT_CPU_7A3             0x000007A3L     // Atmel AT91SAM7A3
    #define TGT_CPU_555             0x00000555L     // Motorola PPC555
    #define TGT_CPU_565             0x00000565L     // Motorola PPC565
    #define TGT_CPU_5282            0x00000528L     // Motorola MCF5282
    #define TGT_CPU_5485            0x00000548L     // Motorola MCF5485
    #define TGT_CPU_812             0x00000812L     // Analog Device ADuC812
    #define TGT_CPU_AU1100          0x00000B00L     // Alchemy AU1100
    #define TGT_CPU_RESERVED1       0x00000B2FL     // reserved
    #define TGT_CPU_XE167           0x00000E67L     // Infineon XE167
    #define TGT_CPU_X161            0x00000F61L     // Infineon XC161
    #define TGT_CPU_X164            0x00000F64L     // Infineon XC164
    #define TGT_CPU_X167            0x00000F67L     // Infineon XC167
    #define TGT_CPU_MIPSII          0x00000F68L     // MIPSII-CPU
    #define TGT_CPU_DUMMY           0x00000FFFL     // dummy CPU


// -------------------------------------------------------------------------
// use these defines to define TARGET_HARDWARE
// -------------------------------------------------------------------------

// NOTE:
// The definitions below are used to detect the differences between the hardware.
// Here you can define new definitions for your own target hardware. It should be set in CopCfg.h
// to define 'TARGET_HARDWARE'. Function CcmInitCANopen() prints out this define to help
// debuging your software application.

#define TGTHW_PKC_INF_505           (TGT_BRD_PKC        | TGT_MAN_INF      | TGT_ADD_I527            | TGT_CPU_505)       // kitCON-505
#define TGTHW_PKC_INF_515           (TGT_BRD_PKC        | TGT_MAN_INF      | TGT_ADD_I527            | TGT_CPU_515)       // kitCON-515
#define TGTHW_PKC_INF_515_EX        (TGT_BRD_PKC        | TGT_MAN_INF      | TGT_ADD_E527            | TGT_CPU_515)       // kitCON-515 with external 527
#define TGTHW_PKC_INF_167           (TGT_BRD_PKC        | TGT_MAN_INF      | TGT_ADD_I527            | TGT_CPU_167)       // kitCON-167
#define TGTHW_SDM_INF_164           (TGT_BRD_SDM        | TGT_MAN_INF      | TGT_ADD_I527            | TGT_CPU_164)       // DIPmodul-164
#define TGTHW_SDM_FUJ_497           (TGT_BRD_SDM        | TGT_MAN_FUJ      | TGT_ADD_IFUJ_CAN        | TGT_CPU_495)       // DIPmodul-F40 mit FUJITSU MB90F497
#define TGTHW_PPC_ATM_CC01          (TGT_BRD_PPC        | TGT_MAN_ATM      | TGT_ADD_ICC03_CAN       | TGT_CPU_CC01)      // phyCORE-CC01
#define TGTHW_PPC_MPC555            (TGT_BRD_PPC        | TGT_MAN_MOT      | TGT_ADD_ITOU_CAN        | TGT_CPU_555)       // phyCORE PowerPC 555
#define TGTHW_PPC_MPC565            (TGT_BRD_PPC        | TGT_MAN_MOT      | TGT_ADD_ITOU_CAN        | TGT_CPU_565)       // phyCORE PowerPC 565
#define TGTHW_PPC_MCF5282           (TGT_BRD_SSV        | TGT_MAN_MOT      | TGT_ADD_IFLEX_CAN       | TGT_CPU_5282)      // Motorola MCF5282 with internal FlexCAN
#define TGTHW_PPC_ADUC812           (TGT_BRD_PPC        | TGT_MAN_ADI      | TGT_ADD_E1000           | TGT_CPU_812)       // phyCore ADuC812
#define TGTHW_PPC_PHI_591           (TGT_BRD_PPC        | TGT_MAN_PHI      | TGT_ADD_I1000           | TGT_CPU_591)       // phyCORE-591
#define TGTHW_GLYN_MIT_306          (TGT_BRD_GLYN       | TGT_MAN_MIT      | TGT_ADD_I306_CAN        | TGT_CPU_306NA)     // Mitsubishi M16C/NA
#define TGTHW_KSPRS232_INF_167      (TGT_BRD_KSP        | TGT_MAN_INF      | TGT_ADD_E1000           | TGT_CPU_167)       // RS232-Gateway
#define TGTHW_KSPS0211_INF_167      (TGT_BRD_KSPS0211   | TGT_MAN_INF      | TGT_ADD_I527|TGT_ADD_E1000 | TGT_CPU_167)    // KSPS-0211 with CAN_I527 and CAN_SJA1000
#define TGTHW_SMC_INF_167           (TGT_BRD_SMC        | TGT_MAN_INF      | TGT_ADD_E1000           | TGT_CPU_167)       // Systec multiCOM/IO
#define TGTHW_TCI_INF_165           (TGT_BRD_TCI        | TGT_MAN_INF      | TGT_ADD_E1000           | TGT_CPU_165)       // TeleCANmodul-165
#define TGTHW_DK_FUJ_543            (TGT_BRD_DK         | TGT_MAN_FUJ      | TGT_ADD_IFUJ_CAN        | TGT_CPU_543)       // Fujitsu DEV-Kit16
#define TGTHW_PC_PEAK               (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_PEAK            | TGT_CPU_386)       // personal computer and Peak driver
#define TGTHW_PC_WRAPP              (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_WRAPP           | TGT_CPU_386)       // personal computer and wrapper DLL
#define TGTHW_PC_UCAN               (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_UCAN            | TGT_CPU_386)       // personal computer and USBCAN32.DLL
#define TGTHW_PPC_INF_X161          (TGT_BRD_PPC        | TGT_MAN_INF      | TGT_ADD_ITWIN           | TGT_CPU_X161)      // phyCORE-XC161
#define TGTHW_SGW_INF_X161          (TGT_BRD_SGW        | TGT_MAN_INF      | TGT_ADD_ITWIN           | TGT_CPU_X161)      // GW-003 CAN Ethernet Gateway
#define TGTHW_KSPS0305_INF_X161     (TGT_BRD_KSPS0305   | TGT_MAN_INF      | TGT_ADD_ITWIN           | TGT_CPU_X161)      // KSPS-0305-XC161
#define TGTHW_PCNETCAN_DOS          (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_PCIO_1000       | TGT_CPU_386)       // personal computer DOS and pcNetCAN
#define TGTHW_PPC_AMD_SC520         (TGT_BRD_PPC        | TGT_MAN_AMD      | TGT_ADD_PCIO_1000       | TGT_CPU_386)       // phyCORE-SC520 with eNetCAN
#define TGTHW_SC12_FUJ_543          (TGT_BRD_SC12       | TGT_MAN_FUJ      | 0                       | TGT_CPU_543)       // SYS TEC CANopen IO C12
#define TGTHW_SC17_INF_161          (TGT_BRD_SC17       | TGT_MAN_INF      | TGT_ADD_E1000           | TGT_CPU_161)       // SYS TEC CANopen IO C17
#define TGTHW_SDM_FUJ_350           (TGT_BRD_SDM        | TGT_MAN_FUJ      | TGT_ADD_IFUJ_CAN        | TGT_CPU_350)       // DIPmodul-F40 mit FUJITSU MB90F352
#define TGTHW_NETDCU_CANINTF        (TGT_BRD_NETDCU     | TGT_MAN_AMD      | TGT_ADD_NETDCU          | TGT_CPU_MIPSII)    // NETDCU 
#define TGTHW_PPC_PHI_LPC_2294      (TGT_BRD_PPC        | TGT_MAN_PHI      | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // phyCore LPC 2294
#define TGTHW_PPC_MCF5485           (TGT_BRD_PPC        | TGT_MAN_MOT      | TGT_ADD_IFLEX_CAN       | TGT_CPU_5485)      // phyCore Coldfire MCF5485 with internal FlexCAN
#define TGTHW_NB_MCF5282            (TGT_BRD_NETBURNER  | TGT_MAN_MOT      | TGT_ADD_IFLEX_CAN       | TGT_CPU_5282)      // NetBurner Coldfire MCF5282 with internal FlexCAN
#define TGTHW_SC14_INF_X161         (TGT_BRD_SCIO       | TGT_MAN_INF      | TGT_ADD_ITWIN           | TGT_CPU_X161)      // SYS TEC COMBImodul C14
#define TGTHW_PPC_ATM_CC03          (TGT_BRD_PPC        | TGT_MAN_ATM      | TGT_ADD_ICC03_CAN       | TGT_CPU_CC03)      // phyCORE-CC01/CC03
#define TGTHW_KSP_ATM_7A3           (TGT_BRD_KSP        | TGT_MAN_ATM      | TGT_ADD_I7A3_CAN        | TGT_CPU_7A3)       // SYS TEC Multiport CAN-to-USB
#define TGTHW_KSP_BCK_1X3           (TGT_BRD_KSP        | TGT_MAN_BCK      | TGT_ADD_I1000           | TGT_CPU_186)       // Beck IPC Chip 1x3 on DK60
#define TGTHW_PC_SERIAL             (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_CDRVSER         | TGT_CPU_386)       // personal computer and Peak driver
#define TGTHW_SPLC_CF54             (TGT_BRD_PLC        | TGT_MAN_MOT      | TGT_ADD_IFLEX_CAN       | TGT_CPU_5485)      // phyCore Coldfire MCF5485 with internal FlexCAN
#define TGTHW_PC_ECOS_PEAK_DRV      (TGT_BRD_PC         | TGT_MAN_DUMMY    | TGT_ADD_EPEAK           | TGT_CPU_386)       // personal computer and Peak driver for eCosPro
#define TGTHW_TRIBOARD_TC1796       (TGT_BRD_TRIBOARD   | TGT_MAN_INF      | TGT_ADD_ITRI_CAN        | TGT_CPU_1796)      // Infineon TriBoard-TC1796
#define TGTHW_TRIBOARD_TC1130       (TGT_BRD_TRIBOARD   | TGT_MAN_INF      | TGT_ADD_ITRI_CAN        | TGT_CPU_1130)      // Infineon TriBoard-TC1130
#define TGTHW_EXPLORER16_DSPIC33F   (TGT_BRD_EXPLORER16 | TGT_MAN_MCH      | TGT_ADD_IECAN           | TGT_CPU_DSPIC33F)  // Microchip Explorer16 Dev.-Board with dsPIC33F
#define TGTHW_KSPS0609_LINBOARD     (TGT_BRD_KSPS0609   | TGT_MAN_ALCH     | TGT_ADD_EMCP2515        | TGT_CPU_AU1100)    // KSPS-0609 Linux-Board
#define TGTHW_RENESAS_M32C84        (TGT_BRD_RSKP       | TGT_MAN_RENE     | TGT_ADD_IM32C_CAN       | TGT_CPU_384FJ)     // Renesas Starterkit Plus min M32C/84FJ
#define TGTHW_COLIBRI               (TGT_BRD_COLIBRI    | TGT_MAN_INT      | TGT_ADD_TORADEX         | TGT_CPU_ARM7)      // Toradex Colbri (added by Anton Paar)
#define TGTHW_LIS_IPC_TDRV011       (TGT_BRD_PC         | TGT_MAN_INT      | TGT_ADD_TDRV011         | TGT_CPU_386)       // LIS industry PC with TPMC816 CAN device
#define TGTHW_LIS_IPC_ESDNTCAN      (TGT_BRD_PC         | TGT_MAN_INT      | TGT_ADD_ESD_NTCAN       | TGT_CPU_386)       // LIS industry PC with NTCAN.DLL interface from ESD GmbH
#define TGTHW_FDK_FUJ_348           (TGT_BRD_FDK        | TGT_MAN_FUJ      | TGT_ADD_IFUJ16FX_CAN    | TGT_CPU_348)       // FUJITSU Starter Kit 16FX with MB96F348HS
#define TGTHW_EASYKIT_INF_XE167F    (TGT_BRD_IEK        | TGT_MAN_INF      | TGT_ADD_ITRI_CAN        | TGT_CPU_XE167)     // Infineon Easy Kit XE167F
#define TGTHW_BLDC_RDK_LM3S8971     (TGT_BRD_BLDC_RDK   | TGT_MAN_LUMINARY | TGT_ADD_ISTELLARIS_CAN  | TGT_CPU_CORTEX_M3) // Luminary Micro BLDC Motor Control RDK with LM3S8971
#define TGTHW_KSPS0806_ZR           (TGT_BRD_KSPS0806ZR | TGT_MAN_PHI      | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // KSPS-0806 (ZR) with LPC2292
#define TGTHW_KSPS0806_BS           (TGT_BRD_KSPS0806BS | TGT_MAN_PHI      | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // KSPS-0806 (BS) with LPC2129
#define TGTHW_KSPS0806_ABF          (TGT_BRD_KSPS0806ABF | TGT_MAN_PHI     | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // KSPS-0806 (ABF) with LPC2292
#define TGTHW_KSPS0806_PWR          (TGT_BRD_KSPS0806PWR | TGT_MAN_SL      | TGT_ADD_BOSCH_CAN       | TGT_CPU_51)        // KSPS-0806 (PWR) with Silabs 8051
#define TGTHW_KSPS0806_LC           (TGT_BRD_KSPS0806LC | TGT_MAN_PHI      | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // KSPS-0806 (LC) with LPC2129
#define TGTHW_ATM_DVK90CAN1         (TGT_BRD_ATMDVK     | TGT_MAN_ATM      | TGT_ADD_ICC03_CAN       | TGT_CPU_AVR8)      // Atmel's Development Kit DVK90CAN1 with AT90CAN128
#define TGTHW_KEIL_MCB2300          (TGT_BRD_KEIL       | TGT_MAN_PHI      | TGT_ADD_ILPC22XX        | TGT_CPU_ARM7)      // Keil Development Board MCB2300
#define TGTHW_SD_EZDSP_TMS320F2812  (TGT_BRD_SD_EZDSP   | TGT_MAN_TI       | TGT_ADD_ITMS            | TGT_CPU_320)       // Spectrum Digital eZdsp TMS320F2812
#define TGTHW_EXPLORER16_PIC32MX    (TGT_BRD_EXPLORER16 | TGT_MAN_MCH      | TGT_ADD_IPIC32MX_CAN    | TGT_CPU_PIC32)     // Microchip Explorer16 Dev.-Board with PIC32MX 
#define TGTHW_STM3210C_EVAL         (TGT_BRD_ST         | TGT_MAN_ST       | TGT_ADD_ISTM32F_BXCAN   | TGT_CPU_STM32F_CL) // STM3210C-EVAL Board for STM32F10xx Controller
#define TGTHW_STM3210B_EVAL         (TGT_BRD_ST         | TGT_MAN_ST       | TGT_ADD_ISTM32F_BXCAN   | TGT_CPU_STM32F_PL) // STM3210C-EVAL Board for STM32F10xx Controller
#define TGTHW_RDB_NXP_LPC1768       (TGT_BRD_CODE_RED   | TGT_MAN_NXP      | TGT_ADD_ILPC22XX        | TGT_CPU_CORTEX_M3)
#define TGTHW_TRIBOARD_TC1766       (TGT_BRD_TRIBOARD   | TGT_MAN_INF      | TGT_ADD_ITRI_CAN        | TGT_CPU_1766)      // Infineon TriBoard-TC1766

#define TGTHW_ZR_NXP_LPC_2292       TGTHW_KSPS0806_ZR
#define TGTHW_LIS_IPC               TGTHW_LIS_IPC_TDRV011

#define TGTHW_USER_HARDWARE         0xFFFFFFFFL     // should be used by customers for own hardware which does not match with settings above


// =========================================================================
// macros for memory access (depends on target system)
// =========================================================================

// NOTE:
// The following macros are used to combine standard library definitions. Some
// applications needs to use one common library function (e.g. memcpy()). So
// you can set (or change) it here.

#if (DEV_SYSTEM == _DEV_KEIL_C16X_)

    #include <stdlib.h>
    #include <stdio.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));
    #define COP_MALLOC(dwMemSize_p)         (void FAR*)LzsEnvMemAlloc((DWORD)dwMemSize_p)
    #define COP_FREE(pMem_p)                LzsEnvMemFree((void FAR*)pMem_p)

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_KEIL_C51X_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_MPLAB_DSPIC33F_)

//    #include <string.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
//        #define PRINTF                      printf
        #define PRINTF                      
    #endif

#elif (DEV_SYSTEM == _DEV_MPLAB_PIC32_)

//    #include <string.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
//        #define PRINTF                      printf
        #define PRINTF                      
    #endif

#elif (DEV_SYSTEM == _DEV_GNU_CODE_RED_)

    #include <string.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
        int TgtMyPrintf (const char *fmtstr_p, ...);
        #define PRINTF                      TgtMyPrintf
    #endif

#elif (DEV_SYSTEM == _DEV_TASKING_TCXXXX_)

    #include <string.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    int TgtMyPrintf (const char *fmtstr_p, ...);
    #ifndef PRINTF
        #define PRINTF                      TgtMyPrintf
    #endif

    #ifdef TRACE
        #undef TRACE
    #endif

    #define TRACE                           TgtMyPrintf

#elif (DEV_SYSTEM == _DEV_GNU_ARM7_) && (TARGET_SYSTEM != _ECOSPRO_)

    #include <string.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_KEIL_CARM_)

    #include <string.h>
    #include <stdio.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_RVCT_CARM_)

    #include <string.h>

//    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
//    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #ifndef PRINTF
        #include <stdio.h>                  // prototype printf()
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_IAR_CARM_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void*)(dst),(void*)(src),(int)(siz));    //memcpy
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void*)(dst),(char)(val),(int)(siz));     //memset

    #include <stdio.h>

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_FUJITSU_F590_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
      #ifndef ACC_MON
        #define PRINTF                      printf
      #else
        int TgtPrintf (char* pszBuff_p, ...);
        #define PRINTF                      TgtPrintf
      #endif
    #endif

/* this does not exist (obsolete) - _DEV_FUJITSU_F590_ is used instead of it
#elif (DEV_SYSTEM == _DEV_FUJITSU_F495_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif
*/
#elif (DEV_SYSTEM == _DEV_MCW_MCF5XXX_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_CCS_TMS_)

    #define TGT_CAST_TO_BYTE(_val_)         (BYTE)((_val_) & 0xFF)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        //#include <stdio.h>              // prototype printf() (for TRACE)
        int TgtPrintf (const char *format, ...);
        #define PRINTF                      TgtPrintf
    #endif

#elif (DEV_SYSTEM == _DEV_GNU_MPC5X5_)

    #include <stdlib.h>

    #define COP_MALLOC(dwMemSize_p)         malloc (dwMemSize_p); // LzsEnvMemAlloc ((DWORD) dwMemSize_p)
    #define COP_FREE(pMem_p)                free (pMem_p) // LzsEnvMemFree  ((void FAR*) pMem_p)

    #ifndef PRINTF
        #define PRINTF                      // §§§ to be defined
    #endif

    #ifdef PXROS

        void AppPrintMsg (char* szString_p, ...);

        #ifndef NDEBUG

            #undef ASSERT
            #define ASSERT(expr)            if (!(expr)) {\
                                                AppPrintMsg ("assertion failed: (" #expr "), file: %s, line: %s\n", __FILE__, __LINE__);\
                                                PxPanic ();}

            #undef ASSERTMSG
            #define ASSERTMSG(expr,string)  if (!(expr)) {\
                                                AppPrintMsg (string);\
                                                PxPanic ();}

            #undef TRACE
            #undef TRACE0
            #undef TRACE1
            #undef TRACE2
            #undef TRACE3
            #undef TRACE4

            #define TRACE                   AppPrintMsg
            #define TRACE0(str)             TRACE (str);
            #define TRACE1(str,p1)          TRACE (str, p1);
            #define TRACE2(str,p1,p2)       TRACE (str, p1, p2);
            #define TRACE3(str,p1,p2,p3)    TRACE (str, p1, p2, p3);
            #define TRACE4(str,p1,p2,p3,p4) TRACE (str, p1, p2, p3, p4);

        #endif // NDEBUG

        #undef PRINTF
        #define PRINTF                      AppPrintMsg

    #endif // PXROS

#elif (DEV_SYSTEM == _DEV_HIGHTEC_X86_)

    void AppPrintMsg (char* szString_p, ...);

    #include <stdlib.h>
    #include <stdio.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));
    #define COP_MALLOC(dwMemSize_p)         (void FAR*)LzsEnvMemAlloc((DWORD)dwMemSize_p)
    #define COP_FREE(pMem_p)                LzsEnvMemFree((void FAR*)pMem_p)

    #ifndef PRINTF
        #define PRINTF
//      #define PRINTF                      AppPrintMsg
    #endif

    #ifndef NDEBUG

        #undef ASSERT
        #define ASSERT(expr)            if (!(expr)) {\
                                            PRINTF ("assertion failed: (" #expr "), file: %s, line: %s\n", __FILE__, __LINE__);\
                                            PxPanic ();}

        #undef ASSERTMSG
        #define ASSERTMSG(expr,string)  if (!(expr)) {\
                                            PRINTF (string);\
                                            PxPanic ();}

        #undef TRACE
        #undef TRACE0
        #undef TRACE1
        #undef TRACE2
        #undef TRACE3
        #undef TRACE4
        #define TRACE                   PRINTF
        #define TRACE0(str)             TRACE (str);
        #define TRACE1(str,p1)          TRACE (str, p1);
        #define TRACE2(str,p1,p2)       TRACE (str, p1, p2);
        #define TRACE3(str,p1,p2,p3)    TRACE (str, p1, p2, p3);
        #define TRACE4(str,p1,p2,p3,p4) TRACE (str, p1, p2, p3, p4);
    #endif


#elif (DEV_SYSTEM == _DEV_MCW_MPC5X5_)

    #include <stdlib.h>
    #include <stdio.h>

    // 26.04.04 r.d.: bitte prüfen welches von beiden richtig ist !!!
    //#define COP_MEMCPY(dst,src,siz)     memcpy((void*)(dst),(const void*)(src),(size_t)(siz));
    //#define COP_MEMSET(dst,val,siz)     memset((void*)(dst),(int)(val),(size_t)(siz));
    // oder
    //#define COP_MALLOC(dwMemSize_p)     LzsEnvMemAlloc ((DWORD) dwMemSize_p)
    //#define COP_FREE(pMem_p)            LzsEnvMemFree  ((void FAR*) pMem_p)

    #define COP_MALLOC(siz)                 malloc((size_t)(siz))
    #define COP_FREE(ptr)                   free((void *)ptr)

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_WIN_CE_)

    #include <stdlib.h>
    #include <stdio.h>

    #define COP_MALLOC(siz)                 malloc((size_t)(siz))
    #define COP_FREE(ptr)                   free((void *)ptr)

    #ifndef PRINTF
        void trace (const char* fmt, ...);
        #define PRINTF                      TRACE
        //#define PRINTF                      printf
    #endif

/*
    #ifdef ASSERTMSG
        #undef ASSERTMSG
    #endif

    #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                        MessageBox (NULL, string, "Assertion failed", MB_OK | MB_ICONERROR); \
                                        exit (-1);}
wird in global.h zu printf definiert
*/
#elif (DEV_SYSTEM == _DEV_WIN32_)

    #ifndef _WIN32_WINDOWS
        #define _WIN32_WINDOWS 0x0401
    #endif
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT   0x0400
    #endif

    #include <stdlib.h>
    #include <stdio.h>

    //29.11.2004 f.j. sonst ist memcpy und memset unbekannt
    #include <string.h>

    // f.j.: die Funktionen für <MemAlloc> und <MemFree> sind in WinMem.c definiert
    //definition der Prototypen
    void FAR*  MemAlloc (DWORD dwMemSize_p);
    void       MemFree (void FAR* pMem_p);

    #define COP_MALLOC(siz)             malloc((size_t)(siz))
    #define COP_FREE(ptr)               free((void *)ptr)

    #ifndef PRINTF
        void trace (const char* fmt, ...);
        #define PRINTF                      TRACE
        //#define PRINTF                      printf
    #endif

    #ifndef NDEBUG
        #ifdef ASSERTMSG
            #undef ASSERTMSG
        #endif

        #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                            MessageBoxA (NULL, string, "Assertion failed", MB_OK | MB_ICONERROR); \
                                            exit (-1);}
    #endif

#elif (DEV_SYSTEM == _DEV_BORLAND_DOS_)

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    // 26.04.04 r.d.: bitte prüfen welches von beiden richtig ist !!!
    //#define COP_MALLOC(siz)             malloc((size_t)(siz))
    //#define COP_FREE(ptr)               free((void *)ptr)
    // oder
    //#define COP_MALLOC(dwMemSize_p)     LzsEnvMemAlloc ((DWORD) dwMemSize_p)
    //#define COP_FREE(pMem_p)            LzsEnvMemFree  ((void FAR*) pMem_p)

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#elif (DEV_SYSTEM == _DEV_MSVC_DOS_)

    #ifdef _WINDOWS
        #undef _WINDOWS
    #endif

    #include <dos.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <conio.h>

    #define inportb                         _inp
    #define outportb                        _outp

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

    // This macro doesn't print out C-file and line number of the failed assertion
    // but a string, which exactly names the mistake.
    #ifndef NDEBUG
        // 2006/08/23k.t.: change MessageBox to printf because no MessageBox possible under DOS
        #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                            PRINTF0 ("Assertion failed: " string ); \
                                            while (1);}                                            
    #else
        #define ASSERTMSG(expr,string)
    #endif

#elif (DEV_SYSTEM == _DEV_LINUX_)

    #ifdef __KERNEL__
        #include <asm/uaccess.h>
    #else
        #include <stdio.h>
        #include <string.h>
    #endif

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

//    #define LOCKDBG(arg) printf(arg)
    #define LOCKDBG(arg)

//    #define TRDEVDBG(arg) printf(arg)
    #define TRDEVDBG(arg)

#elif (DEV_SYSTEM == _DEV_GNU_MIPSEL_)

    #ifdef __KERNEL__
        #include <asm/uaccess.h>
    #else
        #include <stdio.h>
        #include <string.h>
    #endif

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

//    #define LOCKDBG(arg) printf(arg)
    #define LOCKDBG(arg)

//    #define TRDEVDBG(arg) printf(arg)
    #define TRDEVDBG(arg)


#elif (DEV_SYSTEM == _DEV_GNU_CF5282_)

    //#include "xuartdrv.h"

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      //mprintf
    #endif

#elif (DEV_SYSTEM == _DEV_GNU_C16X_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
    //    #define PRINTF                      printf
        #define PRINTF
    #endif

#elif (DEV_SYSTEM == _DEV_TASKING_C16X_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      printf  // 16.04.2003 r.d. muß für Auslieferungsversion eingeschalten sein !!!
    //    #define PRINTF
    #endif

#elif (DEV_SYSTEM == _DEV_TASKING_M16C_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      //printf
    #endif

#elif (DEV_SYSTEM == _DEV_MITSUBISHI_M16C_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      //printf
    #endif

#elif (DEV_SYSTEM == _DEV_RENESAS_M32C_)

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF                      //printf
    #endif

#elif (DEV_SYSTEM == _DEV_WIN32_RTX_)

    #include <stdlib.h>
    #include <stdio.h>
    #include <rtapi.h>

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*)(dst),(void GENERIC*)(src),(WORD)(siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*)(dst),(BYTE)(val),(WORD)(siz));

    #ifndef PRINTF
        #define PRINTF                      RtPrintf
    #endif

    #ifdef ASSERTMSG
        #undef ASSERTMSG
    #endif

    #ifndef NDEBUG
        #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                            PRINTF0 ("Assertion failed: " string ); \
                                            while (1);}
                                            // $$$ while(1) ??? gegebenfalls anpassen !!!
                                            // Unter Windows kann an dieser Stelle das System hängen bleiben
                                            // (evtl. Sleep() hinzufügen).
    #else
        #define ASSERTMSG(expr,string)
    #endif

#elif (DEV_SYSTEM == _DEV_PAR_BECK1X3_)

    #include <dos.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <conio.h>

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

    #ifdef ASSERTMSG
        #undef ASSERTMSG
    #endif

    #ifndef NDEBUG
        #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                            PRINTF0 ("Assertion failed: " string ); \
                                            while (1);}
                                            // $$$ while(1) ??? gegebenfalls anpassen !!!
                                            // Unter Windows kann an dieser Stelle das System hängen bleiben
                                            // (evtl. Sleep() hinzufügen).
    #else
        #define ASSERTMSG(expr,string)
    #endif

#elif (DEV_SYSTEM == _DEV_GNU_I386_)

    #include <stdio.h>
    #include <string.h>

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

    #ifdef ASSERTMSG
        #undef ASSERTMSG
    #endif

    #ifndef NDEBUG
        #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                            PRINTF0 ("Assertion failed: " string ); \
                                            while (1);}
                                            // $$$ while(1) ??? gegebenfalls anpassen !!!
                                            // Unter Windows kann an dieser Stelle das System hängen bleiben
                                            // (evtl. Sleep() hinzufügen).
    #else
        #define ASSERTMSG(expr,string)
    #endif

#elif (DEV_SYSTEM == _DEV_GNU_TRICORE_)

    #ifdef PXROS

        #define COP_MEMCPY(dst,src,siz)         PxBcopy ((PxUChar_t*)src,(PxUChar_t*)dst,(PxSize_t)siz) //TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
        #define COP_MEMSET(dst,val,siz)         TgtMemSet ((void GENERIC*)(dst),(BYTE)(val),(WORD)(siz)) //memset(dst,val,siz)
        #define COP_MALLOC(dwMemSize_p)         TgtMemAlloc ((DWORD) dwMemSize_p)
        #define COP_FREE(pMem_p)                TgtMemFree ((void MEM*) pMem_p)

        void TgtPrintMsg (char* szString_p, ...);

        #ifndef NDEBUG

            #undef ASSERT
            #define ASSERT(expr)            if (!(expr)) { \
                                                TgtPrintMsg ("assertion failed: (" #expr "), file: %s, line: %s\n", __FILE__, __LINE__); \
                                                PxPanic ();}

            #undef ASSERTMSG
            #define ASSERTMSG(expr,string)  if (!(expr)) { \
                                                TgtPrintMsg (string); \
                                                PxPanic ();}

            #undef TRACE
            #undef TRACE0
            #undef TRACE1
            #undef TRACE2
            #undef TRACE3
            #undef TRACE4

            #define TRACE                       TgtPrintMsg
            #define TRACE0(str)                 TRACE(str);
            #define TRACE1(str,p1)              TRACE(str,p1);
            #define TRACE2(str,p1,p2)           TRACE(str,p1,p2);
            #define TRACE3(str,p1,p2,p3)        TRACE(str,p1,p2,p3);
            #define TRACE4(str,p1,p2,p3,p4)     TRACE(str,p1,p2,p3,p4);

        #endif

        #ifndef PRINTF
            #define PRINTF                      TgtPrintMsg
        #endif

    #else

        #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
        #define COP_MEMSET(dst,val,siz)         TgtMemSet ((void GENERIC*)(dst),(BYTE)(val),(WORD)(siz)) //memset(dst,val,siz)
        #define COP_MALLOC(dwMemSize_p)         TgtMemAlloc ((DWORD) dwMemSize_p)
        #define COP_FREE(pMem_p)                TgtMemFree ((void MEM*) pMem_p)

        // currently only definitions for PxROS are available
        #error "ERROR: missing definitions!"

    #endif

#elif (DEV_SYSTEM == _DEV_GNU_WINAVR8_)

    #define __TGT_READ_BYTE__(addr)         \
    (__extension__({                    \
        WORD __addr16 = (WORD)(addr);   \
        BYTE __result;                  \
        __asm__                         \
        (                               \
            "lpm" "\n\t"                \
            "mov %0, r0" "\n\t"         \
            : "=r" (__result)           \
            : "z" (__addr16)            \
            : "r0"                      \
        );                              \
        __result;                       \
    }))

    #define __TGT_READ_WORD__(addr)         \
    (__extension__({                    \
        WORD __addr16 = (WORD)(addr);   \
        WORD __result;                  \
        __asm__                         \
        (                               \
            "lpm"           "\n\t"      \
            "mov %A0, r0"   "\n\t"      \
            "adiw r30, 1"   "\n\t"      \
            "lpm"           "\n\t"      \
            "mov %B0, r0"   "\n\t"      \
            : "=r" (__result), "=z" (__addr16)  \
            : "1" (__addr16)            \
            : "r0"                      \
        );                              \
        __result;                       \
    }))

    #define __TGT_READ_DWORD__(addr)        \
    (__extension__({                    \
        WORD __addr16 = (WORD)(addr);   \
        DWORD __result;                 \
        __asm__                         \
        (                               \
            "lpm"           "\n\t"      \
            "mov %A0, r0"   "\n\t"      \
            "adiw r30, 1"   "\n\t"      \
            "lpm"           "\n\t"      \
            "mov %B0, r0"   "\n\t"      \
            "adiw r30, 1"   "\n\t"      \
            "lpm"           "\n\t"      \
            "mov %C0, r0"   "\n\t"      \
            "adiw r30, 1"   "\n\t"      \
            "lpm"           "\n\t"      \
            "mov %D0, r0"   "\n\t"      \
            : "=r" (__result), "=z" (__addr16)  \
            : "1" (__addr16)            \
            : "r0"                      \
        );                              \
        __result;                       \
    }))

    #define COP_READ_ROM_BYTE(addr)         __TGT_READ_BYTE__(addr)
    #define COP_READ_ROM_WORD(addr)         __TGT_READ_WORD__(addr)
    #define COP_READ_ROM_DWORD(addr)        __TGT_READ_DWORD__(addr)
    //#undef ROM_INIT
    //#define ROM_INIT

    void TgtRomMemCpy (void MEM* pDst_p, CONST void ROM* pSrc_p, WORD wSiz_p);
    #define COP_ROM_MEMCPY(dst,src,siz)     TgtRomMemCpy((void MEM*) (dst), (CONST void ROM*) (src), (WORD) (siz));

    #define COP_MEMCPY(dst,src,siz)         TgtMemCpy((void GENERIC*) (dst), (void GENERIC*) (src), (WORD) (siz));
    #define COP_MEMSET(dst,val,siz)         TgtMemSet((void GENERIC*) (dst), (BYTE) (val), (WORD) (siz));

    #ifndef PRINTF
        #define PRINTF(arg, ...)            do { static char __s[] ROM_INIT = (arg); \
                                            printf_P(__s, ## __VA_ARGS__); } while (0)
    #endif

#else   // default

    #ifndef PRINTF
        #define PRINTF                      printf
    #endif

#endif

#ifndef PRINTF0
    #ifndef NO_PRINTF
        #define PRINTF0(arg)                PRINTF(arg)
        #define PRINTF1(arg,p1)             PRINTF(arg,p1)
        #define PRINTF2(arg,p1,p2)          PRINTF(arg,p1,p2)
        #define PRINTF3(arg,p1,p2,p3)       PRINTF(arg,p1,p2,p3)
        #define PRINTF4(arg,p1,p2,p3,p4)    PRINTF(arg,p1,p2,p3,p4)
    #else
        #define PRINTF0(arg)
        #define PRINTF1(arg,p1)
        #define PRINTF2(arg,p1,p2)
        #define PRINTF3(arg,p1,p2,p3)
        #define PRINTF4(arg,p1,p2,p3,p4)
    #endif
#endif

// 27-mar-2009: r.d.: DSP TSM320xxxx from TI using Code Composer implements a BYTE as 16 bit variable.
// So this macro is already defined above with "(BYTE)((_val_) & 0xFF)"
#ifndef TGT_CAST_TO_BYTE
    #define TGT_CAST_TO_BYTE(_val_)         (BYTE)(_val_)
#endif


// 21-oct-2008 r.d.: There is a problem using WinAVR compiler when using const variables.
// All const variables are loated in RAM wich are initialized once at startup.
// But internal RAM has only 4kByte so it is not effective for our CANopen Stack.
// There is no posibility to specify a generic memory attribute so that functions
// can read from RAM or ROM memory. This attribute is set in ROM_INIT.
// But variables which are predefined with ROM_INIT has to be read with the new Macros
// COP_READ_ROM_xxx() or copied with COP_ROM_MEMCPY().
#ifndef COP_READ_ROM_BYTE
    #define COP_READ_ROM_BYTE(addr)         *(addr)
    #define COP_READ_ROM_WORD(addr)         *(addr)
    #define COP_READ_ROM_DWORD(addr)        *(addr)
#endif

#if !defined(COP_MEMCPY) || !defined(COP_MEMSET)

    #ifndef __KERNEL__
        #include <string.h>
    #endif

    #ifndef COP_MEMCPY
        #define COP_MEMCPY(dst,src,siz)     memcpy((void*)(dst),(void*)(src),(size_t)(siz));
    #endif

    #ifndef COP_MEMSET
        #define COP_MEMSET(dst,val,siz)     memset((void*)(dst),(int)(val),(size_t)(siz));
    #endif
#endif

#ifndef COP_MALLOC
    #define COP_MALLOC(dwMemSize_p)         LzsEnvMemAlloc ((DWORD) dwMemSize_p)
#endif

#ifndef COP_FREE
    #define COP_FREE(pMem_p)                LzsEnvMemFree  ((void FAR*) pMem_p)
#endif

#ifndef COP_ROM_MEMCPY
    #define COP_ROM_MEMCPY(a,b,c)           COP_MEMCPY(a,b,c)
#endif

typedef union
{
    WORD    m_wValue;
    BYTE    m_abValue[2];
}
tTgtWord;
typedef union
{
    DWORD   m_dwValue;
    WORD    m_awValue[2];
    BYTE    m_abValue[4];
}
tTgtDword;
#if ((DEV_SYSTEM & _DEV_BIGEND_) != 0)
    #define TGT_WORD_LSB(_w_)       ((tTgtWord*) &(_w_) )->m_abValue[1]
    #define TGT_WORD_MSB(_w_)       ((tTgtWord*) &(_w_) )->m_abValue[0]
    #define TGT_DWORD_LSB(_dw_)     ((tTgtDword*)&(_dw_))->m_abValue[3]
    #define TGT_DWORD_MSB(_dw_)     ((tTgtDword*)&(_dw_))->m_abValue[0]
    #define TGT_DWORD_LSW(_dw_)     ((tTgtDword*)&(_dw_))->m_awValue[1]
    #define TGT_DWORD_MSW(_dw_)     ((tTgtDword*)&(_dw_))->m_awValue[0]
#else
    #define TGT_WORD_LSB(_w_)       ((tTgtWord*) &(_w_) )->m_abValue[0]
    #define TGT_WORD_MSB(_w_)       ((tTgtWord*) &(_w_) )->m_abValue[1]
    #define TGT_DWORD_LSB(_dw_)     ((tTgtDword*)&(_dw_))->m_abValue[0]
    #define TGT_DWORD_MSB(_dw_)     ((tTgtDword*)&(_dw_))->m_abValue[3]
    #define TGT_DWORD_LSW(_dw_)     ((tTgtDword*)&(_dw_))->m_awValue[0]
    #define TGT_DWORD_MSW(_dw_)     ((tTgtDword*)&(_dw_))->m_awValue[1]
#endif

#if ((DEV_SYSTEM & _DEV_MASK_BITCOUNT) >= _DEV_BIT16_)
    #define TGT_DWORD_CHECKBIT_MSB(_dw_,_bit_)      ((_dw_) & (_bit_))
    #define TGT_DWORD_MASKBIT_MSB(_dw_,_bit_)       (_dw_) &= ~(_bit_)
    #define TGT_DWORD_SETBIT_MSB(_dw_,_bit_)        (_dw_) |=  (_bit_)
#else
    #define TGT_DWORD_CHECKBIT_MSB(_dw_,_bit_)      (TGT_DWORD_MSB (_dw_) & (BYTE) ((_bit_) >> 24))
    #define TGT_DWORD_MASKBIT_MSB(_dw_,_bit_)       TGT_DWORD_MSB (_dw_) &= (BYTE) (~(_bit_) >> 24)
    #define TGT_DWORD_SETBIT_MSB(_dw_,_bit_)        TGT_DWORD_MSB (_dw_) |= (BYTE) ( (_bit_) >> 24)
#endif


// =========================================================================
// function prototypes
// =========================================================================

// 20-oct-2008 r.d.: included for TgtTimer.c because copinc.h should not be included there
#ifndef TGT_EXCLUDE_PROTOTYPES

#ifdef __cplusplus
extern "C"
{
#endif
// generic function to initialize target interface
void  PUBLIC  TgtInit (void);
void  PUBLIC  TgtEnableGlobalInterrupt (BYTE bEnable_p);
void  PUBLIC  TgtInitSerial (void);

// function to initialize CAN-controller
void  PUBLIC  TgtInitCanIsr (void);
void  PUBLIC  TgtFreeCanIsr (void);
void  HWACC*  PUBLIC TgtGetCanBase (BYTE bCanContr_p);

// registers CAN driver instance (only for more instances than one)
void  PUBLIC  TgtRegisterInstance (tCopInstanceHdl InstanceHdl_p, tCopPtrInstance InstancePtr_p);

// if there are more CAN controllers than one, there shold also
// be more functions to enable CAN interrupts
void  PUBLIC  TgtEnableCanInterrupt0 (BYTE bEnable_p); // 2006/03/30 -rs: Linux-Kernel-Driver needs it because instance number is zero-based
void  PUBLIC  TgtEnableCanInterrupt1 (BYTE bEnable_p);
void  PUBLIC  TgtEnableCanInterrupt2 (BYTE bEnable_p);
void  PUBLIC  TgtEnableCanInterrupt3 (BYTE bEnable_p);
void  PUBLIC  TgtEnableCanInterrupt4 (BYTE bEnable_p);
void  PUBLIC  TgtEnableCanInterrupt  (BYTE bEnable_p);

// function for target specific and optimized data copy and set
void  PUBLIC  TgtMemCpy (void GENERIC* dst, void GENERIC* src, WORD siz);
void  PUBLIC  TgtMemSet (void GENERIC* dst, BYTE val, WORD siz);
WORD  PUBLIC  TgtGetAlignOffset (BYTE MEM* pbData_p, WORD wDataSize_p);
CONST WORD ROM* PUBLIC TgtGetBitrateTabPtr (BYTE bParameter_p);

// function prototypes from runtime system memory functions
void FAR*     LzsEnvMemAlloc (DWORD dwMemSize_p);
void          LzsEnvMemFree  (void FAR* pMem_p);

void MEM* PUBLIC TgtMemAlloc (DWORD dwSiz_p);
void PUBLIC TgtMemFree (void MEM* pData_p);

// hardware management for MMU-based runtime systems
tCopKernel  PUBLIC  TgtAllocHwRessource   (BYTE bDevNumber_p, BYTE HWACC** ppHwBaseAddr_p);
tCopKernel  PUBLIC  TgtReleaseHwRessource (BYTE bDevNumber_p);
tCopKernel  PUBLIC  TgtGetBitrateTable    (BYTE bDevNumber_p, CONST void ROM** ppBdiTable_p, WORD* wSizeOfBdiTab_p);


// event signaling for multitasking runtime systems
void  PUBLIC  TgtSignalEvent (BYTE bDevNumber_p, DWORD dwEventMask_p);

void PUBLIC TgtSetLed (DWORD dwLedState_p);

#ifdef __cplusplus
}
#endif
#endif // TGT_EXCLUDE_PROTOTYPES


// 20-oct-2008 r.d.: this class of functions always has to be defined
#ifdef __cplusplus
extern "C"
{
#endif

// function for CANopen system time
void  PUBLIC  TgtInitTimer (void);
void  PUBLIC  TgtStopTimer (void);
tTime PUBLIC  TgtGetTickCount (void);

#ifdef __cplusplus
}
#endif



#include "tgtos.h"


#endif //_TARGET_H_

// EOF

