/*
 * spi.h
 *
 *  Created on: 20.11.2018
 *      Author: Jan-Niclas Nutt
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <msp430g2553.h>

extern void spi_init(void);
extern void spi_send(uint8_t trans);
extern uint8_t spi_recieve(void);
extern uint8_t spi_read_temp(void);



#endif /* SPI_H_ */
