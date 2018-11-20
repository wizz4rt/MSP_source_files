/*
 * scm.h
 *
 *  Created on: 31.10.2018
 *      Author: tnellius
 */

#ifndef SCM_H_
#define SCM_H_

#include <stdint.h>
#include <msp430g2553.h>


extern void scm_init(void);
extern void scm_putchar(char c);
extern char scm_getchar(void);
extern void scm_print(char* buffer);
extern int8_t scm_getchars(char* buffer);
extern int16_t scm_getint(void);
extern int8_t scm_int2string(char* buffer, uint8_t buffer_size, int16_t number);
extern int8_t scm_decimal2string(char* buffer, uint8_t buffer_size, int16_t number, int8_t decimal);


#endif /* SCM_H_ */
