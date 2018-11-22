/*
 * i2c.c
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */

void i2c_init(void)
{
    // P1.5 ist hier auch die Clock, kann also so bleiben?
    P1DIR |= BIT7; // P1.7 as output

    P1SEL |= BIT7;
    P1SEL2 |= BIT7;

}
