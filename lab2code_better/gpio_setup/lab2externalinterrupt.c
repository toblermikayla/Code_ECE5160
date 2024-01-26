
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Function Prototypes
//
__interrupt void xint1_isr(void); //handler for the xint

//
// Globals
//
volatile Uint32 XintCount;
Uint32 LoopCount;
volatile Uint32 Hall_A;
volatile Uint32 Hall_B;
volatile Uint32 Hall_C;
volatile Uint32 temp;

//
// Define
//
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

//
// Main
//
void main(void)
{
    Uint32 TempXCount;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2806x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.XINT1 = &xint1_isr;
    PieVectTable.XINT2 = &xint1_isr;
    PieVectTable.XINT3 = &xint1_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Clear the counters
    //
    XintCount = 0;     // Count XINT1 interrupts

    LoopCount = 0;      // Count times through idle loop

    // Enable XINT1, XINT2, and XINT3 in the PIE: Group 1 interrupt 4 & 5 and Group12 interrupt 2
    // Enable INT1 which is connected to WAKEINT
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Group 1 INT4
    PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Group 1 INT5
    PieCtrlRegs.PIEIER12.bit.INTx1 = 1;          // Enable PIE Group 12 INT1
    IER |= M_INT1;                              // Enable CPU INT1
    IER |= M_INT12;                             // Enable CPU INT12
    EINT;                                       // Enable Global Interrupts


    //
    // GPIO0 and GPIO1 are inputs
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;         // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;       // XINT1 Synch to SYSCLKOUT only

    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;         // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 2;       // XINT2 Qual using 6 samples

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;        // GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;         // input
    GpioCtrlRegs.GPAQSEL1.bit.GPIO2 = 0;       // XINT1 Synch to SYSCLKOUT only
    //
    // Each sampling window is 510*SYSCLKOUT
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0xFF;
    EDIS;

    //
    // GPIO0 is XINT1, GPIO1 is XINT2
    //
    EALLOW;
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // XINT1 is GPIO0
    GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
    GpioIntRegs.GPIOXINT3SEL.bit.GPIOSEL = 2;   // XINT3 is GPIO2
    EDIS;

    //
    // Configure XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.POLARITY = 3;      // Falling edge and Rising edge interrupt
    XIntruptRegs.XINT2CR.bit.POLARITY = 3;      //
    XIntruptRegs.XINT2CR.bit.POLARITY = 3;      //
    //
    // Enable XINT1 and XINT2
    //
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2
    XIntruptRegs.XINT3CR.bit.ENABLE = 1;        // Enable XINT3

    //
    // Step 6. IDLE loop
    //
    for(;;)
    {
        TempXCount = XintCount;

        while(XintCount == TempXCount)
        {

        }


        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if(XintCount == TempXCount+1 )
        {
            LoopCount++;
        }
        else
        {
            __asm("      ESTOP0"); // stop here
        }
    }
}

//
// xint1_isr - Step 7. Insert all local Interrupt Service Routines (ISRs)
// and functions here: If local ISRs are used, reassign vector addresses in
// vector table as shown in Step 5
//
__interrupt void
xint1_isr(void)
{

    XintCount++;

    Hall_A  = GpioDataRegs.GPADAT.bit.GPIO0;
    Hall_B  = GpioDataRegs.GPADAT.bit.GPIO1;
    Hall_C  = GpioDataRegs.GPADAT.bit.GPIO2;

    GpioDataRegs.GPASET.all |= 0x00000FC0; // turn off all Inverter board switches
    temp = 0x00000000;

    if(Hall_A & Hall_B){ // A_up
        temp |= 0x00000080;
    }
    if (!Hall_A & Hall_B){ // A_lo
        temp |= 0x00000040;
    }
    if (Hall_B & !Hall_C){ // B_up
        temp |= 0x00000200;
    }
    if (!Hall_B & Hall_C){ // B_lo
        temp |= 0x00000100;
    }
    if (Hall_C & !Hall_A){ // C_hi
        temp |= 0x00000800;
    }
    if (Hall_A & !Hall_C){ // C_lo
        temp |= 0x00000400;
    }

    //GpioDataRegs.GPACLEAR.all |= temp;

    //
    // Acknowledge this interrupt to get more from group 1 and group 12
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1 | PIEACK_GROUP12 ;

}

//
// End of File
//

