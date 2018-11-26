/*
 * spi.c
 *
 *  Created on: 20.11.2018
 *      Author: Jan-Niclas Nutt
 */

#include "spi.h"
#define wait10 __delay_cycles(150000)

/*
 * Initialise UCSI and configure Pins
 * note: pins have to be re-configured when the LCD whas used using
 */

void spi_init2(void)
{
    P1DIR |= BIT3; //| BIT5 | BIT7;                // P1.3, P1.5, P1.7 as output
    //P1DIR &= ~BIT6;                              //P1.6 as input
    P1SEL |= BIT6 | BIT7 | BIT5;                       //P1.6, P1.7 P-select 1
    P1SEL2 |= BIT6 |BIT7 | BIT5;                       //P1.6, P1.7 P-select2 1

    //P1OUT |= BIT3;

    UCB0CTL1 = UCSWRST;                    //enable configuration

    UCB0CTL0 |= UCMSB + UCMST + UCSYNC;         //MSB first, Mastermode, 4pin-mode with active high, synchronus
    UCB0CTL1 |= UCSSEL_2;                       //use SMCLK

    UCB0BR0 = 0x04;
    UCB0BR1 = 0;

    UCB0CTL1 &= ~UCSWRST;                    //save changes

}

void spi_send_data(uint8_t data)
{
    UCB0TXBUF = data;
    while(!(IFG2 & UCB0TXIFG))
    {
        scm_putchar(46);
    }
}

uint8_t spi_receive_data(void)
{
    spi_send_data(0b00000000);
    while(!(IFG2 & UCB0RXIFG))
    {
        scm_putchar(33);
    }

    return UCB0RXBUF;
}

void spi_test(void)
{
    P1OUT |= BIT3;
    spi_send_data(0b00000000);
    uint8_t temp = spi_receive_data();
    char* buffer[4];
    scm_int2string(buffer, 4, temp);
    scm_print(buffer);
    scm_print("\n\r");
    P1OUT &= ~BIT3;
}

void spi_get_temperature(void)
{
    CE_1;
    spi_send_data(0b10000000);
    spi_send_data(0b00000100);
    CE_0;
    wait10;
    CE_1;
    spi_send_data(0b00000010);
    uint8_t temp = spi_receive_data();
    CE_0;
    char buffer[4];
    scm_int2string(buffer, 4, temp);
    scm_print(buffer);
    scm_print("\n\r");

}

void spi_init(void)
{
    UCB0CTL1 = UCSWRST; //reset


    UCB0CTL0 |= UCMSB + UCMST + UCMODE_1 + UCSYNC; //MSB first, MSP is Master
    UCB0CTL1 |= BIT7;        //use SMCLK
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
    scm_putchar(32);
    return temp;
}













