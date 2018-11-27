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

#define WAIT1000            (__delay_cycles(1000))
#define CLK_1               (P1OUT |= BIT5)
#define CLK_0               (P1OUT &= ~BIT5)
#define DATA_1              (P1OUT |= BIT7)
#define DATA_0              (P1OUT &= ~BIT7)
#define DATA_IN             (P1DIR &= ~BIT7)
#define DATA_OUT            (P1DIR |= BIT7)
#define CLK_OUT             (P1DIR |= BIT5)
#define DATA_ALLOWPULLUP    (P1REN |= BIT7)
#define DATA_DENIEPULLUP    (P1REN &= ~BIT7)


void i2c_init(void);
void i2c_send(uint8_t trans);
uint8_t i2c_start_conv(uint8_t data);
void i2c_set(uint8_t addr, uint8_t data);
void i2c_send_bit(uint8_t bit);
uint8_t i2c_receive(void);
uint8_t i2c_send_data(uint8_t data);
void i2c_ackn(void);
uint8_t i2c_read_bit(void);
void i2c_get_temperature(void);
void i2c_get_temperature2(char* temp_buffer);
void i2c_send_data2(uint8_t data);
void i2c_send_startbit(void);


#endif /* I2C_H_ */
