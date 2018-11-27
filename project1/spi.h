/*
 * spi.h
 *
 *  Created on: 20.11.2018
 *      Author: Jan-Niclas Nutt
 */

#ifndef SPI_H_
#define SPI_H_

//setup P1.5/6/7 to be used with the UCSI
#define SET_P1SEL       P1SEL = BIT5 | BIT7
#define SET_P1SEL2      P1SEL2 = BIT5 | BIT7
//reset P1.5/6/7 to be used as GPIO again
#define RESET_P1SEL     P1SEL &= ~(BIT5 | BIT7)
#define RESET_P1SEL2    P1SEL2 &= ~(BIT5 | BIT7)
//used to set P1.3 on high or low;
#define CE_1 P1OUT |= BIT3
#define CE_0 P1OUT &= ~BIT3

#include <stdint.h>
#include <msp430g2553.h>
#include <scm.h>

extern void spi_init(void);
extern void spi_send_data(uint8_t data);
extern uint8_t spi_receive_data(void);
extern uint8_t spi_get_temperatur(void);



#endif /* SPI_H_ */
