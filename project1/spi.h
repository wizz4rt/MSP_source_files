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

#include <stdint.h>
#include <msp430g2553.h>
#include <scm.h>

extern void spi_init(void);

extern void spi_send(int8_t trans);
extern int8_t spi_receive(void);
extern int16_t spi_temperatur(void);
extern void spi_send_data(uint8_t data);
extern uint8_t spi_receive_data(void);
extern void spi_get_temperatur(void);
extern void spi_init2(void);



#endif /* SPI_H_ */
