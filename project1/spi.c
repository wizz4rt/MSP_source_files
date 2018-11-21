/*
 * spi.c
 *
 *  Created on: 20.11.2018
 *      Author: Jan-Niclas Nutt
 */

#include "spi.h"

/*
 * Initialise UCSI and configure Pins
 * note: pins have to be re-configured when the LCD whas used using
 */
void spi_init(void)
{
    UCB0CTL1 = UCSWRST; //reset

    UCB0CTL0 |= UCMSB + UCMST + UCSYNC; //MSB first, MSP is Master
    UCB0CTL1 |= UCSSEL_2;        //use SMCLK
    UCB0BR0 |= 0x02;
    UCB0BR1 = 0;

    //UCB0STAT |= UCLISTEN;     //test
    // Choose periphal function of used pins
    P1SEL |= BIT6;
    P1SEL2 |= BIT6;

    P1DIR |= BIT3;   //set P1.3 as output


    UCB0CTL1 &= ~UCSWRST; //reset SPI-module to save changes

    P1OUT |= BIT3;

    spi_send(0x80);
    while(UCB0STAT & UCBUSY);
    //__delay_cycles(150000);
    spi_send(0x00);
    while(UCB0STAT & UCBUSY);
    P1OUT &= ~BIT3;
    __delay_cycles(175000);



}


void spi_send(int8_t trans)
{
    UCB0TXBUF = trans;          //write byte in transmit buffer
}

int8_t spi_receive(void)
{
    int8_t temp;

    temp = UCB0RXBUF;           //return bytes from recieve buffer



    return temp;
}
