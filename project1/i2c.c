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

void i2c_send2(uint8_t addr)
{
    P1DIR |= DATA + CLK; // Data and Clk to output
    //P1OUT |= CLK;   // Clk 1

    int div = 128;
    for (int i = 0; i<8; i++)
    {

        P1OUT &= ~CLK;  //clock 0
        d100;

        if(addr>=div){
            P1OUT |= DATA;  //Data 1 if Bit 1
            addr -= div;
            scm_putchar(49);
        }else{
            P1OUT &= ~DATA; //Data 0 if Bit 0
            scm_putchar(48);

        }
        d100;   // wait
        P1OUT |= CLK;   //Clk 1
        d100;   //wait

        div = div/2;
    }
}

void i2c_set(uint8_t addr, uint8_t data)
{
    P1DIR |= DATA + CLK; // Data and Clk to output
    P1OUT |= CLK;
    P1OUT |= DATA;  // Data 1 //begin of startbit
    d100;   // wait
    P1OUT &= ~DATA; // Data 0
    d100; // wait

    i2c_send2(addr); //address sent
    P1OUT &= ~CLK;  //clk 0
    d100;
    P1OUT &= ~DATA; //Data 0
    d100;
    P1OUT |= CLK;   //Clk 1
    d100;           //MASTER ACKN
    scm_print("mst_ackn\n\r");
    P1OUT &= ~CLK;  //CLK 0
    d100;
    i2c_send2(data);    //Data sent

    P1OUT &= ~CLK;  //Clk 0
    P1DIR &= ~DATA; //Data as input
    P1REN |= DATA;  // allow Data pullup
    P1OUT |= DATA;  //Data pullup

    P1OUT &= ~CLK;  //Clk 0
    d100;

    P1OUT |= CLK;
    d100;
    if(!(P1IN & DATA)) //Is PIN 7 low?
    {
        scm_print("ackn\n\r");
    }else
    {
        scm_print("fail\n\r");
    }


}

void i2c_send(uint8_t trans)
{
    P1DIR |= DATA + CLK;
    P1OUT |= CLK;
    d100;
    P1OUT |= DATA;
    d100;
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

