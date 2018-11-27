/*
 * spi.h
 *
 *  Created on: 27.11.2018
 *      Author: tomne
 */

#ifndef SPI_H_
#define SPI_H_

//setup P1.5/6/7 to be used with the UCSI
#define SET_P1SEL       P1SEL |= BIT5 | BIT6 | BIT7
#define SET_P1SEL2      P1SEL2 |= BIT5 | BIT6 | BIT7

//reset P1.5/6/7 to be used as GPIO again
#define RESET_P1SEL     P1SEL &= ~(BIT5 | BIT6 | BIT7)
#define RESET_P1SEL2    P1SEL2 &= ~(BIT5 | BIT6 | BIT7)

//used to set P1.3 on high or low;
#define CE_1 P1OUT |= BIT3
#define CE_0 P1OUT &= ~BIT3


#include <stdint.h>
#include <msp430g2553.h>
#include "scm.h"


/*
 * initialize USCI module
 */
void spi_init(void);
/*
 * writes data to a slave
 * addr = address of the slave
 * data = data to send
 */
void spi_transmit_data(char addr, char data);
/*
 * recieves data from slave
 * addr = address of the slave
 * \return the received data
 */
char spi_receive_data(char addr);
/*
 * get the Temperature from TC72 and write it into buffer with two digits after comma
 */
void spi_get_temperature(char* buffer);

#endif /* SPI_H_ */
