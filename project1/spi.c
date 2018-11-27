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

void spi_init(void)
{
    P1SEL |= BIT5 + BIT6 + BIT7;
    P1SEL2 |= BIT5 + BIT6 + BIT7;
    P1SEL &= ~BIT3;
    P1SEL2 &= ~BIT3;
    //P1DIR &= ~BIT6;
    P1DIR |= BIT3;


    CE_0;
    wait10;

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
    while(!(IFG2 & UCB0TXIFG));
}

uint8_t spi_receive_data(void)
{
    spi_send_data(0b00000000);
    while(!(IFG2 & UCB0RXIFG));

    return UCB0RXBUF;
}


uint8_t spi_get_temperature(void)
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
    //wait10;
    //CE_1;
    //spi_send_data(0b00000001);
    //uint8_t temp_LSB = spi_receive_data();
    //CE_0;
    char buffer[4];
    scm_int2string(buffer, 4, temp);
    scm_print(buffer);
    scm_print("\n\r");

    //P1SEL &= ~(BIT5 + BIT6 + BIT7);
    //P1SEL2 &= ~(BIT5 + BIT6 + BIT7);

    //spi_deactivate();

    return temp;

}
void spi_deactivate()
{
     P1SEL &= ~(BIT5 | BIT6 | BIT7); //Reset SPI routing for periphery
     P1SEL2 &= ~(BIT5 | BIT6 | BIT7);


     UCB0CTL1 = UCSWRST;   //Reset USCI
     UCB0CTL0 &=  ~UCMSB | ~UCMST | ~UCSYNC;
     UCB0CTL1 |= UCSSEL_0;
     UCB0BR0 = 0x01;
     UCB0CTL1 &= ~UCSWRST;
}














