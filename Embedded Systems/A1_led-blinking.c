//TODO 122022010 Shrayank Mistry
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

int main(void)
{
    //* configures the clocking of the device
    //* arguments (system clock divider, use of PLL, input crystal frequency, oscillator source)
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //* function enables a peripheral. they must be enabled in order to operate or respond to register reads/writes
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //* function enables pins to be properly configured in order to function as outputs
    //* GPIO_PORTF_BASE - base address of the port
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    while (1)
    {
        //* Writes the corresponding bit values to the output pin(s) 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0E); // blue 04, green 08, red 02. 0E white

        //* is the number of delay loop iterations to perform
        SysCtlDelay(20000000);

        //* Writes the corresponding bit values to the output pin(s) 
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

        //* is the number of delay loop iterations to perform
        SysCtlDelay(20000000);
    }
}