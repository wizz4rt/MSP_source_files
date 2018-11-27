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
//setup pin and configure sensor to 11-Bit resolution

void ow_reset(void);
//initiate interaction with slave

void ow_send_1(void);
//transmit logical 1 to slave

void ow_send_0(void);
//transmit logical 0 to slave

void ow_send_data(uint8_t data);
//transmit given data-byte to slave

uint8_t ow_read_bit(void);
//read logical value sent by slave and give it back

uint8_t ow_read_data(void);
//receive whole data-byte from slave and give it back

void ow_get_temperature(char* buffer);
//initiate temperature-conversion, receive temperature from sensor, store temperatur in buffer

uint8_t ow_calculate_predec(uint8_t msb, uint8_t lsb);
//calculate temperature-predecimal-digits from given temp-MSByte and -LSByte and give it back

uint8_t ow_calculate_dec(uint8_t lsb);
//calculate temperature-decimal-digits from given LSByte and give it back

void ow_reset(void);
//initiate interaction with slave


#endif /* ONEWIRE_H_ */
