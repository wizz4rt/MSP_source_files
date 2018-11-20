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
#define RESET_P1SEL     P1SEL &= ~(BIT5 | BIT6 | BIT7)
#define RESET_P1SEL2    P1SEL2 &= ~(BIT5 | BIT6 | BIT7)

#include <stdint.h>
#include <msp430g2553.h>

extern void spi_init(void);
extern void spi_reconf_pins(void);

extern void spi_send(uint8_t trans);
extern uint16_t spi_recieve(void);
extern uint16_t spi_read_temp(void);



#endif /* SPI_H_ */
