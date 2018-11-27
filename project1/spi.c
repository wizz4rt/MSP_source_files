/*
 * spi.c
 *
 *  Created on: 27.11.2018
 *      Author: tomne
 */
#include "spi.h"


void spi_init(void)
{
    P1DIR |= BIT3;

    UCB0CTL1 = UCSWRST;                     //enable configuration

    UCB0CTL0 |= UCMSB + UCMST + UCSYNC;     //MSB first, Mastermode, 4pin-mode with active high, synchronus
    UCB0CTL1 |= UCSSEL_2;                   //use SMCLK

    UCB0BR0 = 0x04;                         //set clock divider

    UCB0CTL1 &= ~UCSWRST;                   //save changes
    __delay_cycles(100);
}
void spi_transmit_data(char addr, char data)
{
    UCB0TXBUF = addr;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = data;
    while (UCB0STAT & UCBUSY);

}
char spi_receive_data(char addr)
{
    char rec;
    UCB0TXBUF = addr;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = 0x00;               //dummy
    while (UCB0STAT & UCBUSY);

    rec = UCB0RXBUF;                //read rxbuffer
    return rec;                     //return value

}
void spi_get_temperature(char* buffer)
{
    uint8_t temp_MSB;
    uint8_t temp_LSB;


    SET_P1SEL;
    SET_P1SEL2;

    CE_1;
    spi_transmit_data(0x80, 0x00);
    CE_0;
    __delay_cycles(170000);         //wait for control register to save changes
    CE_1;
    temp_MSB = spi_receive_data(0x02); //receive MSB
    CE_0;
    __delay_cycles(2);
    CE_1;
    temp_LSB = spi_receive_data(0x01); //receive LSB
    CE_0;
    __delay_cycles(2);

    uint8_t len = scm_int2string(buffer, 10, temp_MSB); //write MSB into buffer
    buffer[len] = ',';                                  //set comma after MSB's last digit
    if(temp_LSB & BIT7)                                 //write the two next digits depending on the LSB
    {
        if(temp_LSB & BIT6)
        {
            //case: LSB is '11'
            buffer[len+1] = '7';
            buffer[len+2] = '5';
        }
        else
        {
            //case: LSB is '10'
            buffer[len+1] = '5';
            buffer[len+2] = '0';
        }
    }
    else
    {
        if(temp_LSB & BIT6)
        {
            //case: LSB is '01'
            buffer[len+1] = '2';
            buffer[len+2] = '5';
        }
        else
        {
            //case: LSB is '00'
            buffer[len+1] = '0';
            buffer[len+2] = '0';
        }
    }
    buffer[len+3] = '\0';                               //write '\0' to end string properly

    RESET_P1SEL;
    RESET_P1SEL2;
}


