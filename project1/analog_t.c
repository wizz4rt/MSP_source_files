
#include "analog_t.h"

void analog_t_adc_init(void)
{
    P1SEL |= BIT0; //configure P1.0 as input for ADC

    ADC10CTL0 = SREF_1 +REFON +REF2_5V + ADC10ON + ADC10SHT_3; //set V_ref
    ADC10CTL1 = INCH_0 + ADC10DIV_2; //channel 0, clock divider = 2,
    ADC10AE0 |= BIT0; //enable analog input on A0
}

int16_t analog_t_temperature(void)
{
    volatile int16_t t = 0;
    __delay_cycles(2000);               // wait for V_ref
    ADC10CTL0 |= ENC + ADC10SC;         // start conversion

    while(ADC10CTL1 & BUSY);           //wait while adc is busy

    t = ADC10MEM;
    ADC10CTL0 &= ~ENC;                     //disable conversion

    return (int16_t) ((12*t)-2000); // return temperatur in C

}
