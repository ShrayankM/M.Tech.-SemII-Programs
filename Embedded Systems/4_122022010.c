#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/sysctl.h"
#include"driverlib/gpio.h"
#include"driverlib/debug.h"
#include"driverlib/pwm.h"
#include"driverlib/pin_map.h"
#include"inc/hw_gpio.h"
#include"driverlib/rom.h"

//MAIN FUNCTION
int main(void)
{

    int i=0;

    volatile uint8_t ui8Adjust; //VARIABLE FOR PWM_WIDTH SET AS % FROM 0 TO 100

    //CLOCK SETTINGS - SET SYSTEM CLOCK TO 40MHz
    //* configures the clocking of the device
    //* arguments (system clock divider, use of PLL, input crystal frequency, oscillator source)
    //TODO SYSCTL_SYSDIV_5 - system clock divider
    //TODO PLL - phase locked loop configuration for clock
    //TODO SYSCTL_XTAL_16MHZ - clock frequency
    //TODO SYSCTL_OSC_MAIN - oscillator source  
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    //SET PWM CLOCK AS SYSTEM CLOCK DIVIDED BY 64
    //* function configures the rate of the clock provided to the PWM (pulse width modulation) module as a ratio of the processor clock
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

    //PERIPHERAL CONFIGURATION
    //* function enables a peripheral. they must be enabled in order to operate or respond to register reads/writes
    //TODO SYSCTL_PERIPH_PWM1 - pulse width modulation peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);     //PWM PERIPHERAL ENABLE

    //TODO enable general purpose input output
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);    //GPIO FOR PWM1

    //* PWM pins must be properly configured for the PWM peripheral to function correctly
    //TODO GPIO_PORTA_BASE - base address of the port
    //TODO (GPIO_PIN_1 / GPIO_PIN_2 / GPIO_PIN_3) - is the bit-packed representation of the pin(s)
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);    //GPIO PF1 FOR PWM1

    //* function configures the pin mux that selects the peripheral function associated with a
    //* particular GPIO pin
    GPIOPinConfigure(GPIO_PF1_M1PWM5);          //PF1 AS M1PWM5

    //* function is used to set the mode of operation for a PWM generator
    //TODO PWM1_BASE - is the base address of the PWM module
    //TODO PWM_GEN_2 - PWM generator to configure
    //TODO PWM_GEN_MODE_DOWN - is the configuration for the PWM generator 
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);

    //SET PWM GENERATOR WITH MODEOF OPERATION AS COUNTING
    //* function sets the period of the specified PWM generator block
    //TODO PWM1_BASE - is the base address of the PWM module
    //TODO PWM_GEN_2 - PWM generator to configure
    //TODO 100 - specifies the period of PWM generator output, measured in clock ticks
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2,100);          //SET PERIOD OF PWM GENERATOR

    //* function enables or disables the selected PWM outputs
    //TODO PWM1_BASE - is the base address of the PWM module
    //TODO PWM_OUT_5_BIT - are the PWM outputs to be modified
    //TODO bEnable(true) determines if the signal is enabled or disabled
    PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);     //ENABLE BIT5 OUTPUT as PWM is 5

    //* function allows the PWM clock to drive the timer/counter for the specified generator block
    //TODO PWM1_BASE - is the base address of the PWM module
    //TODO PWM_GEN_2 - is the PWM generator to be enabled
    PWMGenEnable(PWM1_BASE, PWM_GEN_2);             //ENABLE PWM_GEN_2 GENERATOR

    while(1)
    {

        // PWM_WIDTH CHANGE FROM 0% - 100% IN STEPS OF 10%
        for(i=1;i<11;i++)
        {
            ui8Adjust = i*10;       //Step size of 10%

            //GPIO FOR PWM1
            //* function sets the pulse width for the specified PWM output, where the pulse width is defined as the number of PWM clock ticks
            //TODO PWM1_BASE - is the base address of the PWM module
            //TODO PWM_OUT_5 - is the PWM output to modify
            //TODO ui8Adjust - specifies the width of the positive portion of the pulse
            PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, ui8Adjust);      //SET THE PULSE WIDTH

            //* is the number of delay loop iterations to perform
            //TODO 4000000 - is the number of delay loop iterations to perform
            SysCtlDelay(4000000);       //DELAY OF 300MILLISECONDS
        }
    }
}