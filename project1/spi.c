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
    //while(UCB0STAT & UCBUSY);
}

uint8_t spi_receive_data(void)
{
    char rec;
    spi_send_data(0b00000000);
    while(!(IFG2 & UCB0RXIFG));
    //while(UCB0STAT & UCBUSY);
    rec = UCB0RXBUF;
    return rec;
}


uint8_t spi_get_temperature(char* buffer)
{
    SET_P1SEL;
    SET_P1SEL;

    CE_1;
    spi_send_data(0b10000000);
    spi_send_data(0b00000000);
    CE_0;
    //WAIT1000;
    CE_1;
    spi_send_data(0b00000010);
    uint8_t temp_MSB = spi_receive_data();
    CE_0;
    CE_1;
    spi_send_data(0b00000001);
    uint8_t temp_LSB = spi_receive_data();
    CE_0;

    scm_int2string(buffer, 8, temp_MSB);
    scm_print(buffer);
    scm_print("\n\r");
    char buffer2[4];
    scm_int2string(buffer2, 8, temp_LSB);
    scm_print(buffer2);
    scm_print("\n\r");

    RESET_P1SEL;
    RESET_P1SEL2;

    return temp_MSB;

}














