/*
 * spi.c
 *
 *  Created on: 20.11.2018
 *      Author: Jan-Niclas Nutt
 */

#include "spi.h"

void spi_init(void)
{
    UCB0CTL0 |= UCMSB + UCMST + UCMODE0 + UCSYNC; //MSB first, MSP is Master
    UCB0CTL1 |= UCSSEL1;        //use SMCLK
    // Choose periphal function of used pins
    P1SEL = BIT5 | BIT6 | BIT7;
    P1SEL2 = BIT5 | BIT6 | BIT7;
    //set P1.3 to always high
    P1DIR = BIT3;
    P1OUT = BIT3;

    UCB0CTL1 &= ~UCSWRST; //reset SPI-module to save changes
}

void spi_send(uint8_t trans)
{
    P1OUT &= ~BIT3;             //turn P1.3 off to initiate Communication; start frame

    UCB0TXBUF = trans;          //write byte in transmit buffer
    while(UCB0STAT & UCBUSY);   //wait while  UCSI is busy...

    P1OUT &= ~BIT3;              //turn P1.3 on again; end frame
}

uint8_t spi_recieve(void)
{
    while(UCB0STAT & UCBUSY);   //wait while USCI is busy...
    return UCB0RXBUF;           //return bytes from recieve buffer
}
uint8_t spi_read_temp(void)
{
    spi_send(0x80);
    spi_send(BIT4);
    return spi_recieve();
}
