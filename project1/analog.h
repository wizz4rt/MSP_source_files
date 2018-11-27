/*
 * analog.h
 *
 *  Created on: 05.11.2018
 *      Author: tnellius
 */

#ifndef ANALOG_H_
#define ANALOG_H_

#include <stdint.h>
#include <msp430g2553.h>
#include "scm.h"


/*
 * initialize the adc
 */
void analog_adc_init(void);
/*
 * read and convert temperature and write it as a sting into buffer with two digits after comma.
 * \return temp*100 in degrees celsius, so you can set the comma afterwards
 */
int16_t analog_get_temperature(char* buffer);



#endif /* ANALOG_H_ */
