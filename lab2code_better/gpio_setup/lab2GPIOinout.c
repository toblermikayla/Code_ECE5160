
//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
// Defines that select the example to compile in.
// Only one example should be set as 1 the rest should be set as 0.
//
#define EXAMPLE1 1  // Basic pinout configuration example

// Function Prototypes
//
void Gpio_setup1(void);
/**
 * main.c
 */
/*
int main(void)

{
        // Step 1. Initialize System Control:
        // PLL, WatchDog, enable Peripheral Clocks
        // This example function is found in the F2806x_SysCtrl.c file.
        //
        InitSysCtrl();
        // Step 2. Initalize GPIO:
        // This example function is found in the F2806x_Gpio.c file and
        // illustrates how to set the GPIO to it's default state.
        //
        // InitGpio(); Skipped for this example
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
        // Step 4. Initialize all the Device Peripherals:
        // This function is found in F2806x_InitPeripherals.c
        //
        // InitPeripherals(); // Not required for this example

        //
        // Step 5. User specific code
        //
        #if EXAMPLE1
            //
            // This example is a basic pinout
            //
            Gpio_setup1();
        #endif  // - EXAMPLE1
    return 0;
}
//
// Gpio_setup1 -Example 1: Basic Pinout.
//
void
Gpio_setup1(void)
{
    EALLOW; //probably allows editing of GPIO stuff
    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;  // Disable pullup on GPIO0
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;  // GPIO0 = input

    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;  // Disable pullup on GPIO1
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; // GPIO1 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;  // GPIO1 = input

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;  // Disable pullup on GPIO2
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; // GPIO2 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;  // GPIO2 = input

    //GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Disable pullup on GPIO6
    //GpioDataRegs.GPACLEAR.bit.GPIO6 = 1; // drive the pin low and clears the latch

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch

    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;   // Disable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO7 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  // GPIO6 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;   // GPIO6 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 1;   // Disable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 1;   // Disable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO6 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1;   // Disable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO10 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;   // GPIO6 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;   // Disable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO11 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;   // GPIO6 = output
    //THE FOLLOWING IS CODE FROM A TI EXAMPLE GPIOSETUP AND IS FOR REFERENCE
    // These can be combined into single statements for improved
    // code efficiency.
    //

    //
    // Enable PWM1-3 on GPIO0-GPIO5
    //
    /* EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B

    //
    // Enable an GPIO output on GPIO6, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
    GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output


    //
    // Enable GPIO outputs on GPIO8 - GPIO11, set it high
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
    GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO8
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
    GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO9 = GPIO9
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO9 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;  // Enable pullup on GPIO10
    GpioDataRegs.GPASET.bit.GPIO10 = 1;  // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // GPIO10 = GPIO10
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;   // GPIO10 = output

    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  // Enable pullup on GPIO11
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // GPIO11 = GPIO11
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // GPIO11 = output

    //
    // Set input qualifcation period for GPIO25 & GPIO26
    //
    GpioCtrlRegs.GPACTRL.bit.QUALPRD3=1;  // Qual period = SYSCLKOUT/2
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25=2;   // 6 samples
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26=2;   // 6 samples

    //
    // Make GPIO25 the input source for XINT1
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;  // GPIO25 = GPIO25
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;   // GPIO25 = input
    GpioIntRegs.GPIOXINT1SEL.all = 25;    // XINT1 connected to GPIO25

    //
    // Make GPIO34 an input
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // GPIO34 = input
    EDIS;


}
*/

