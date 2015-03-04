//*****************************************************************************
// Declaration of the default fault handlers
//*****************************************************************************

#define WEAK __attribute__ ((weak))

void WEAK  ResetHandler(void);
void WEAK  NMIIntHandler(void);
void WEAK  HardFaultIntHandler(void);
void WEAK  MemManageIntHandler(void);
void WEAK  BusFaultIntHandler(void);
void WEAK  UsageFaultIntHandler(void);
void WEAK  SVCIntHandler(void);
void WEAK  DebugMonIntHandler(void);
void WEAK  PendSVIntHandler(void);
void WEAK  SysTickIntHandler(void);
void WEAK  DMA0IntHandler(void);
void WEAK  DMA1IntHandler(void);
void WEAK  DMA2IntHandler(void);
void WEAK  DMA3IntHandler(void);
void WEAK  FTFAIntHandler(void);
void WEAK  LVDIntHandler(void);
void WEAK  LLWUIntHandler(void);
void WEAK  I2C0IntHandler(void);
void WEAK  I2C1IntHandler(void);
void WEAK  SPI0IntHandler(void);
void WEAK  SPI1IntHandler(void);
void WEAK  UART0SEIntHandler(void);
void WEAK  UART1SEIntHandler(void);
void WEAK  UART2SEIntHandler(void);
void WEAK  ADCIntHandler(void);
void WEAK  ACMPIntHandler(void);
void WEAK  FTM0IntHandler(void);
void WEAK  FTM1IntHandler(void);
void WEAK  FTM2IntHandler(void);
void WEAK  RTCAIntHandler(void);
void WEAK  RTCSIntHandler(void);
void WEAK  PITIntHandler(void);
void WEAK  USBOTGIntHandler(void);
void WEAK  DACIntHandler(void);
void WEAK  TSIIntHandler(void);
void WEAK  MCGIntHandler(void);
void WEAK  LPTMRIntHandler(void);
void WEAK  PORTAIntHandler(void);
void WEAK  PORTDIntHandler(void);

//*****************************************************************************
// Symbols defined in linker script
//*****************************************************************************

// Start address for the initialization values of the .data section.
extern unsigned long _sidata;

// Start address for the .data section
extern unsigned long _sdata;

// End address for the .data section
extern unsigned long _edata;

// Start address for the .bss section
extern unsigned long _sbss;

// End address for the .bss section
extern unsigned long _ebss;

// End address for ram
extern void _eram;

// Stack start address
extern unsigned long _start_of_stack;

//*****************************************************************************
// Function prototypes
//*****************************************************************************
extern int main(void);
void ResetHandler(void);
static void DefaultIntHandler(void);

//*****************************************************************************
// The minimal vector table for a Cortex M0+.  Note that the proper constructs
// must be placed on this to ensure that it ends up at physical address
// 0x00000000.
//*****************************************************************************
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    (void *)&_start_of_stack,
    ResetHandler,                           // The reset handler
    NMIIntHandler,                          // The NMI handler
    HardFaultIntHandler,                    // The hard fault handler
    0, 0, 0, 0, 0, 0, 0,                    // Reserved
    SVCIntHandler,                          // SVCall handler
    0, 0,                                   // Reserved
    PendSVIntHandler,                       // The PendSV handler
    SysTickIntHandler,                      // The SysTick handler

    DMA0IntHandler,                         // DMA channel 0 transfer complete
                                            // and error handler
    DMA1IntHandler,                         // DMA channel 1 transfer complete
                                            // and error handler
    DMA2IntHandler,                         // DMA channel 2 transfer complete
                                            // and error handler
    DMA3IntHandler,                         // DMA channel 3 transfer complete
                                            // and error handler
    0,                                      // Reserved
    FTFAIntHandler,                         // Command complete and read collision
    LVDIntHandler,                          // Low-voltage detect, low-voltage warning
    LLWUIntHandler,                         // Low Leakage Wakeup
    I2C0IntHandler,                         // I2C0 handler
    I2C1IntHandler,                         // I2C1 handler
    SPI0IntHandler,                         // SPI0 handler
    SPI1IntHandler,                         // SPI1 handler
    UART0SEIntHandler,                      // UART0SE handler
    UART1SEIntHandler,                      // UART1SE handler
    UART2SEIntHandler,                      // UART2SE handler
    ADCIntHandler,                          // ADC handler
    ACMPIntHandler,                         // ACMP handler
    FTM0IntHandler,                         // FTM0 handler
    FTM1IntHandler,                         // FTM1 handler
    FTM2IntHandler,                         // FTM2 handler
    RTCAIntHandler,                         // RTCA handler
    RTCSIntHandler,                         // RTCS handler
    PITIntHandler,                          // PIT handler
    0,                                      // Reserved
    USBOTGIntHandler,                       // USBOTG handler
    DACIntHandler,                          // DAC handler
    TSIIntHandler,                          // TSI handler
    MCGIntHandler,                          // MCG handler
    LPTMRIntHandler,                        // PIT handler
    0,                                      // Reserved
    PORTAIntHandler,                        // PORTA handler
    PORTDIntHandler,                        // PORTC/PORTD handler
};

//*****************************************************************************
//! \brief This is the code that gets called when the processor first
//! starts execution following a reset event.
//!
//! \param None.
//!
//! Only the absolutely necessary set is performed, after which the
//! application supplied main() routine is called.
//!
//! \return None.
//*****************************************************************************
void Default_ResetHandler(void)
{
    unsigned long *pulSrc, *pulDest;

    /* copy the data segment initializers from flash to SRAM */
    pulSrc = &_sidata;
    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    /* zero fill the bss segment */
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    /* call the application's entry point */
    main();
}

//*****************************************************************************
// Provide weak aliases for each Exception handler to the DefaultIntHandler.
// As they are weak aliases, any function with the same name will override
// this definition.
//*****************************************************************************
#pragma weak ResetHandler = Default_ResetHandler
#pragma weak NMIIntHandler = DefaultIntHandler
#pragma weak HardFaultIntHandler = DefaultIntHandler
#pragma weak MemManageIntHandler = DefaultIntHandler
#pragma weak BusFaultIntHandler = DefaultIntHandler
#pragma weak UsageFaultIntHandler = DefaultIntHandler
#pragma weak SVCIntHandler = DefaultIntHandler
#pragma weak DebugMonIntHandler = DefaultIntHandler
#pragma weak PendSVIntHandler = DefaultIntHandler
#pragma weak SysTickIntHandler = DefaultIntHandler
#pragma weak DMA0IntHandler = Default_ResetHandler
#pragma weak DMA1IntHandler = Default_ResetHandler
#pragma weak DMA2IntHandler = Default_ResetHandler
#pragma weak DMA3IntHandler = Default_ResetHandler
#pragma weak FTFAIntHandler = Default_ResetHandler
#pragma weak LVDIntHandler = Default_ResetHandler
#pragma weak LLWUIntHandler = Default_ResetHandler
#pragma weak I2C0IntHandler = Default_ResetHandler
#pragma weak I2C1IntHandler = Default_ResetHandler
#pragma weak SPI0IntHandler = Default_ResetHandler
#pragma weak SPI1IntHandler = Default_ResetHandler
#pragma weak UART0SEIntHandler = Default_ResetHandler
#pragma weak UART1SEIntHandler = Default_ResetHandler
#pragma weak UART2SEIntHandler = Default_ResetHandler
#pragma weak ADCIntHandler = Default_ResetHandler
#pragma weak ACMPIntHandler = Default_ResetHandler
#pragma weak FTM0IntHandler = Default_ResetHandler
#pragma weak FTM1IntHandler = Default_ResetHandler
#pragma weak FTM2IntHandler = Default_ResetHandler
#pragma weak RTCAIntHandler = Default_ResetHandler
#pragma weak RTCSIntHandler = Default_ResetHandler
#pragma weak PITIntHandler = Default_ResetHandler
#pragma weak USBOTGIntHandler = Default_ResetHandler
#pragma weak DACIntHandler = Default_ResetHandler
#pragma weak TSIIntHandler = Default_ResetHandler
#pragma weak MCGIntHandler = Default_ResetHandler
#pragma weak LPTMRIntHandler = Default_ResetHandler
#pragma weak PORTAIntHandler = Default_ResetHandler
#pragma weak PORTDIntHandler = Default_ResetHandler

//*****************************************************************************
//! \brief This is the code that gets called when the processor receives an
//! unexpected interrupt.
//!
//! \param None.
//!
//! This simply enters an infinite loop, preserving the system state for
//! examination by a debugger.
//!
//! \return None.
//*****************************************************************************
static void DefaultIntHandler(void)
{
	for(;;);
}

