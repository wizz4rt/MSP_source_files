/*
 * analog_t.h
 *
 *  Created on: 05.11.2018
 *      Author: tnellius
 */

#ifndef ANALOG_T_H_
#define ANALOG_T_H_

#include <stdint.h>
#include <msp430g2553.h>

extern void analog_t_adc_init(void);
extern int16_t analog_t_temperature(void);





#endif /* ANALOG_T_H_ */
