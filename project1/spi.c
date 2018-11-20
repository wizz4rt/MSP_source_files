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

    UCB0CTL0 |= UCMSB + UCMST + UCMODE0 + UCSYNC; //MSB first, MSP is Master
    UCB0CTL1 |= UCSSEL1;        //use SMCLK
    UCB0BR0 |= 0x02;
    UCB0BR1 |= 0;
    // Choose periphal function of used pins
    P1SEL = BIT6;
    P1SEL2 = BIT6;

    P1DIR = BIT3;   //set P1.3 as output


    UCB0CTL1 &= ~UCSWRST; //reset SPI-module to save changes

    P1OUT = BIT3;

    spi_send(0x80);
    __delay_cycles(150000);
    spi_send(0x11);
    __delay_cycles(150000);

    P1OUT &= ~BIT3;

}


void spi_send(uint8_t trans)
{
    //P1OUT = BIT3;             //turn P1.3 on to initiate Communication; start frame

    UCB0TXBUF = trans;          //write byte in transmit buffer
    while(UCB0STAT & UCBUSY);   //wait while  UCSI is busy...

    //P1OUT &= ~BIT3;              //turn P1.3 off again; end frame

}

uint8_t spi_recieve(void)
{
    uint8_t temp;
    temp = UCB0RXBUF;           //return bytes from recieve buffer



    return temp;
}
uint8_t spi_read_temp(void)
{
    return spi_recieve();
}
