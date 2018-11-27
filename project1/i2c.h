/*
 * i2c.h
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */
//

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
//setup all pins and configure the sensor for continuously measurement

void i2c_send_bit(uint8_t bit);
//transmit a given logical value to the slave

uint8_t i2c_receive(void);
//read whole data-byte sent by the slave and give it back

void i2c_ackn(void);
//wait for the slave to acknowledge

uint8_t i2c_read_bit(void);
//read one logical value from the data line and give it back

void i2c_get_temperature(char* temp_buffer);
//read temperature from sensor and store it in buffer as decimal

void i2c_send_data(uint8_t data);
//transmit given data-byte to slave

void i2c_send_startbit(void);
//initiate interaction by sending startbit


#endif /* I2C_H_ */
