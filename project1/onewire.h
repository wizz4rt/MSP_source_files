/*
 * onewire.h
 *
 *  Created on: 26.11.2018
 *      Author: tnellius
 */

#include <stdint.h>
#include <msp430g2553.h>
#include <scm.h>

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#define PIN_IN              P1DIR &= ~BIT4
#define PIN_OUT             P1DIR |= BIT4
#define PIN_1               P1OUT |= BIT4
#define PIN_0               P1OUT &= ~BIT4
#define PIN_ALLOWPULLUP     P1REN |= BIT4
#define PIN_DENIEPULLUP     P1REN &= ~BIT4
#define PIN_PULLUP          P1OUT |= BIT4
#define PIN_PULLDOWN        P1OUT &= ~BIT4

void ow_init(void);
void ow_reset(void);
void ow_send_1(void);
void ow_send_0(void);
void ow_send_data(uint8_t data);
uint8_t ow_read_bit(void);
uint8_t ow_read_data(void);
void ow_test(char* buffer);
void ow_get_temperature(char* buffer);
uint8_t ow_calculate_predec(uint8_t msb, uint8_t lsb);
uint8_t ow_calculate_dec(uint8_t lsb);
void ow_reset(void);


#endif /* ONEWIRE_H_ */
