
#include "analog_t.h"

void analog_t_adc_init(void)
{
    P1SEL |= BIT0; //configure P1.0 as input for ADC

    ADC10CTL0 = SREF_1 +REFON +REF2_5V + ADC10ON + ADC10SHT_3; //
    ADC10CTL1 = INCH_0 + ADC10DIV_2; //channel 0, clock divider = 2,
    ADC10AE0 |= BIT0; //enable analog input on A0
}

int16_t analog_t_temperature(void)
{
    volatile int t = 0;
    __delay_cycles(1000);               // Wait for ADC Ref to settle
    ADC10CTL0 |= ENC + ADC10SC;         // Sampling and conversion start
    while(ADC10CTL1 & BUSY)             //wait..i am converting..pum..pum..
    {
        t=ADC10MEM;                       //store val in t
    }
    ADC10CTL0&=~ENC;                     //disable adc conv
    return (int16_t) ((0.24*t)-(0.4*100))/0.0179;
}
