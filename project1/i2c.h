/*
 * i2c.h
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */
#include <stdint.h>
#include <msp430g2553.h>
#include <scm.h>

#ifndef I2C_H_
#define I2C_H_

#define CLK BIT5
#define DATA BIT7

#define wait10              (__delay_cycles(1000))
#define clk_1               (P1OUT |= BIT5)
#define clk_0               (P1OUT &= ~BIT5)
#define data_1              (P1OUT |= BIT7)
#define data_0              (P1OUT &= ~BIT7)
#define data_in             (P1DIR &= ~BIT7)
#define data_out            (P1DIR |= BIT7)
#define clk_out             (P1DIR |= BIT5)
#define data_allowpullup    (P1REN |= BIT7)


extern void i2c_init(void);
extern void i2c_send(uint8_t trans);
extern void i2c_start_read(uint8_t data);
extern void i2c_set(uint8_t addr, uint8_t data);


#endif /* I2C_H_ */
