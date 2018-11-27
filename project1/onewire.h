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

#define pin_in  P1DIR &= ~BIT4
#define pin_out P1DIR |= BIT4
#define pin_1               P1OUT |= BIT4
#define pin_0               P1OUT &= ~BIT4
#define pin_allowpullup     P1REN |= BIT4
#define pin_deniepullup     P1REN &= ~BIT4
#define pin_pullup          P1OUT |= BIT4
#define pin_pulldown        P1OUT &= ~BIT4

extern void ow_init(void);
extern void ow_start_conv(void);
extern void ow_send_1(void);
extern void ow_send_0(void);
extern void ow_send_byte(uint8_t data);
extern uint8_t ow_read_bit(void);
extern uint8_t ow_read_byte(void);
extern void ow_test(char* buffer);


#endif /* ONEWIRE_H_ */
