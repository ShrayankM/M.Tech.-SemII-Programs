#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"

void systick_initialize(unsigned long reload_value)
{

    //* Systick control and Status register 
    //* 0: the counter is disabled
    NVIC_ST_CTRL_R = 0; // disable systick

    //* 24-bit reload value
    //* Systick Reload Value Register - This register acts like a bucket filled with a liquid that will be empty after some time duration
    NVIC_ST_RELOAD_R=reload_value ; // systick interupt time period= (SysTick_load+1)* Clock period

    //* 24-bit CURRENT value of SysTick counter
    //* Write to the NVIC_ST_CURRENT_R value to clear the counter
    NVIC_ST_CURRENT_R = 0;

    //* priority level of SysTick interrupts is controlled using 
    //* NVIC_SYS_PRI3_R register 0(highest) - 7(lowest)
    NVIC_SYS_PRI3_R = NVIC_SYS_PRI3_R&0x00FFFFFF; // priority 0

    //* enable the SysTick counter to begin countdown
    NVIC_ST_CTRL_R = 0x07; // enable systick
}

void systick_handler(void)
{

    //* Reads the values present of the specified pin(s)
    //TODO GPIO_PORTF_BASE - base address of GPIO port
    //TODO GPIO_PIN_1 - is the bit-packed representation of the pin(s)
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1))
    {
        //* Writes the corresponding bit values to the output pin(s) 
        //TODO GPIO_PORTF_BASE - base address of GPIO port
        //TODO (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3) - is the bit-packed representation of the pin(s)
        //TODO 0 - value to be written
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
    }
    else
    {
        //* Writes the corresponding bit values to the output pin(s) 
        //TODO GPIO_PORTF_BASE - base address of GPIO port
        //TODO GPIO_PIN_1 - is the bit-packed representation of the pin(s)
        //TODO 2 - value to be written
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
    }
}

int main(void)
{

    //* Function call to initialize the SysTick counter
    systick_initialize(12500000);

    //* configures the clocking of the device
    //* arguments (system clock divider, use of PLL, input crystal frequency, oscillator source)
    //TODO SYSCTL_SYSDIV_16 - system clock divider
    //TODO PLL - phase locked loop configuration for clock
    //TODO SYSCTL_XTAL_16MHZ - clock frequency
    //TODO SYSCTL_OSC_MAIN - oscillator source
    SysCtlClockSet(SYSCTL_SYSDIV_16|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);  //clock at 12.5MHZ

    
    //* function enables a peripheral. they must be enabled in order to operate or respond to register reads/writes
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //* function enables pins to be properly configured in order to function as outputs
    //TODO GPIO_PORTF_BASE - base address of the port
    //TODO GPIO_PIN_1 - is the bit-packed representation of the pin(s)
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

}