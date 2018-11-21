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


    UCB0CTL0 |= UCMSB + UCMST + UCMODE_1 + UCSYNC; //MSB first, MSP is Master
    UCB0CTL1 |= UCSSEL_2;        //use SMCLK
    UCB0BR0 |= 0x02;
    UCB0BR1 = 0;

    //UCB0STAT |= UCLISTEN;     //test
    // Choose periphal function of used pins

    UCB0CTL1 &= ~UCSWRST; //reset SPI-module to save changes

    P1SEL |= BIT5;
    P1SEL2 |= BIT5;
    P1SEL |= BIT6;
    P1SEL2 |= BIT6;
    P1SEL |= BIT7;
    P1SEL2 |= BIT7;

    P1DIR |= BIT7;
    P1DIR |= BIT5;
    P1DIR |= BIT3; //set P1.3 as output

    P1OUT |= BIT3;

    UCB0TXBUF = 0x80;
    while(UCB0STAT & UCBUSY);
    UCB0TXBUF = 0x00;
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
int16_t spi_temperatur(void)
{
    P1OUT |= BIT3;
    UCB0TXBUF = 0x02;
    while(UCB0STAT & UCBUSY);
    __delay_cycles(175000);
    UCB0TXBUF = 0xdf;
    while(UCB0STAT & UCBUSY);
    UCB0TXBUF = 0xdf;
    while(UCB0STAT & UCBUSY);
    int16_t temp = UCB0RXBUF;
    P1OUT &= ~BIT3;
    return temp;
}













