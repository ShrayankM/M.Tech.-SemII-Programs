#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#define GPIO_PA0_U0RX 0x00000001 // UART PIN ADDRESS FOR UART RX
#define GPIO_PA1_U0TX 0x00000401 // UART PIN ADDRESS FOR UART TX
int main(void)
{

// SYSTEM CLOCK AT 40 MHZ
//* configures the clocking of the device
//* arguments (system clock divider, use of PLL, input crystal frequency, oscillator source)
//TODO SYSCTL_SYSDIV_5 - system clock divider
//TODO PLL - phase locked loop configuration for clock
//TODO SYSCTL_XTAL_16MHZ - clock frequency
//TODO SYSCTL_OSC_MAIN - oscillator source
SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

// ENABLE PERIPHERAL UART 0
//* function enables a peripheral. they must be enabled in order to operate or respond to register reads/writes
//TODO Universal Asynchronous Receiver Transmitter (UART) module - enable UART 0
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

//TODO enable general purpose input output port A (GPIOA)
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

// ENABLE GPIO PORT A,FOR UART
//* function configures the pin mux that selects the peripheral function associated with a
//* particular GPIO pin
GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX

//* UART pins must be properly configured for the UART peripheral to function correctly
//TODO GPIO_PORTA_BASE - base address of the port
//TODO (GPIO_PIN_0 / GPIO_PIN_1) - is the bit-packed representation of the pin(s)
GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);


// CONFIGURE UART, BAUD RATE 115200, DATA BITS 8, STOP BIT 1, PARITY NONE ,range for baud rate 115200 is max
//* function configures the UART for operation in the specified data format
//TODO UART0_BASE - is the base address of the UART port
//TODO SysCtlClockGet() - clock supplies to UART
//TODO BAUD RATE 115200
//TODO (UART_CONFIG_WLEN_8 |UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)- is the data format for the port (number of data bits, number of stop bits, and parity)
UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 |UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

//* function sends the respective character specified in argument to the transmit FIFO for the specified port
UARTCharPut(UART0_BASE, 'T');
UARTCharPut(UART0_BASE, 'E');
UARTCharPut(UART0_BASE, 'X');
UARTCharPut(UART0_BASE, 'A');  // SEND "Echo Output: " IN UART
UARTCharPut(UART0_BASE, 'S');/*
UARTCharPut(UART0_BASE, ' ');
UARTCharPut(UART0_BASE, 'I');
UARTCharPut(UART0_BASE, 'T');
UARTCharPut(UART0_BASE, 'S');
UARTCharPut(UART0_BASE, 'T');
UARTCharPut(UART0_BASE, 'R');
UARTCharPut(UART0_BASE, 'U');
UARTCharPut(UART0_BASE, 'M');
UARTCharPut(UART0_BASE, 'E');
UARTCharPut(UART0_BASE, 'N');
UARTCharPut(UART0_BASE, 'T');
UARTCharPut(UART0_BASE, 'S');
UARTCharPut(UART0_BASE, ' :  ');
UARTCharPut(UART0_BASE, ' ');
//UARTCharPut(UART0_BASE, ' \n');*/

while (1)
 {
//UART ECHO - what is received is transmitted back //
//* function returns a flag indicating whether or not there is data available in the receive FIFO.
if (UARTCharsAvail(UART0_BASE)) {

//* function sends the respective character specified in argument to the transmit FIFO for the specified port
UARTCharPut(UART0_BASE,UARTCharGet(UART0_BASE));
      }
   }
}