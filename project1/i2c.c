/*
 * i2c.c
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */
#define  d100 __delay_cycles(10000)

#include "i2c.h"

void i2c_init(void)
{
    // P1.5 ist hier auch die Clock, kann also so bleiben?
    P1DIR |= BIT5; // P1.5 as output
    P1DIR |= BIT7; // P1.7 as output

    P1SEL &= ~BIT5;
    P1SEL2 &= ~BIT5;
    P1SEL &= ~BIT7;
    P1SEL2 &= ~BIT7;
    // P1REN |= BIT7; activate pullup/pulldown
    // P1OUT |= BIT7; pull up
}

void i2c_send(uint8_t trans)
{
    P1DIR |= DATA + CLK;
    P1OUT |= CLK;
    d100;
    P1OUT |= DATA;

    P1OUT &= ~DATA;
    d100;
    int div = 128;
    for (int i = 0; i<8; i++)
    {

        P1OUT &= ~CLK;
        d100;

        if(trans>=div){
            P1OUT |= DATA;
            trans -= div;
            scm_putchar(49);
        }else{
            P1OUT &= ~DATA;
            scm_putchar(48);

        }
        d100;
        P1OUT |= CLK;
        d100;

        div = div/2;
    }

    P1DIR &= ~DATA;
    P1REN |= DATA;
    P1OUT |= DATA;
    d100;
    P1OUT &= ~CLK;
    d100;

    P1OUT |= CLK;
    d100;
    if(!(P1IN & DATA)) //Is PIN 7 low?
    {
        scm_print("acknowledged");
    }else
    {
        scm_print("fail");
    }

    for(int i = 0; i<8; i++)
    {
        P1OUT &= ~CLK;
        d100;
        P1OUT |= CLK;

        if(!(P1IN & DATA)) //Is PIN 7 low?
            {
                scm_putchar(49);
            }else
            {
                scm_putchar(48);
            }
        d100;
    }
    scm_putchar(32);
    P1DIR |= DATA;
    P1OUT &= ~(CLK + DATA);
    d100;
    P1OUT |= CLK;
    d100;

    P1DIR &= ~DATA;
    P1OUT |= DATA;

    for(int i = 0; i<8; i++)
    {
        P1OUT &= ~CLK;
        d100;
        P1OUT |= CLK;

        if(!(P1IN & DATA)) //Is PIN 7 low?
            {
                scm_putchar(49);
            }else
            {
                scm_putchar(48);
            }
        d100;
    }
    P1OUT &= ~CLK;
    d100;
    P1OUT |= CLK;
    d100;
    P1OUT &= ~CLK;
    P1REN &= ~DATA;
    d100;
    P1OUT |= CLK;
    d100;
    P1REN |= DATA;


}

