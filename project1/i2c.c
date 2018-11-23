/*
 * i2c.c
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */


#include "i2c.h"

void i2c_init(void)
{
    clk_out;
    data_out;
    data_allowpullup;
}

void i2c_start_read(uint8_t addr)
{
    clk_1;
    data_1;
    wait10;
    data_0;
    wait10;
    clk_0;

    uint16_t div =128;
    for(uint8_t i = 0; i<8;i++)
    {
        wait10;
        if(addr>=div)
        {
            data_1;
            addr -= div;
            scm_putchar(49);
        }
        else
        {
            data_0;
            scm_putchar(48);
        }
        div = (uint16_t) div/2;
        wait10;
        clk_1;
        wait10;
        clk_0;

    }
    data_in;
    data_allowpullup;
    data_1;
    wait10;
    clk_1;
    for(uint8_t j = 0; j<10; j++)
    {
        if(P1IN & BIT7)
        {
            scm_putchar(46);
        }
        else
        {
            scm_print("ackn");
            break;
        }
        wait10;
    }
    scm_putchar(35);
    clk_0;
}

void i2c_set(uint8_t addr, uint8_t data)
{

}

void i2c_send(uint8_t trans)
{



}

