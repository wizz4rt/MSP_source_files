/*
 * i2c.h
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */

#ifndef I2C_H_
#define I2C_H_

#define CLK BIT5
#define DATA BIT7

#include <stdint.h>
#include <msp430g2553.h>
#include <scm.h>

extern void i2c_init(void);
extern void i2c_send(uint8_t trans);


#endif /* I2C_H_ */
