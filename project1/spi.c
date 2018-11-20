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
}

void spi_write(int8_t trans)
{
    while(UCB0STAT & UCBUSY);
    UCB0TXBUF = trans;          //write byte in transmit buffer
}

int8_t spi_read(void)
{
    while(UCB0STAT & UCBUSY);
    return UCB0RXBUF;
}
int8_t spi_read_temp(void)
{
    spi_write(0x80);
    spi_write(BIT4);
    return spi_read();
}
