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

void i2c_send_bit(uint8_t bit)
{
    clk_0;
    if(bit==1)
    {
        data_1;
        scm_putchar(49);
    }
    else
    {
        data_0;
        scm_putchar(48);
    }
    wait10;
    clk_1;
    wait10;
    clk_0;
    wait10;
}

uint8_t i2c_send_data(uint8_t data)
{
    clk_0;
    data_out;
    data_0;
    uint16_t div =128;
    uint8_t bit;
    for(uint8_t i = 0; i<8;i++)
    {
        bit = (uint8_t) data/div;
        i2c_send_bit(bit);
        data = data-(div*bit);
        div = div/2;
    }
    return bit;

}

uint16_t i2c_receive(void)
{
    clk_0;
    data_allowpullup;
    data_in;
    data_1;
    wait10;
    uint16_t temp=0;
    uint8_t mult=128;
    for(uint8_t i; i<8; i++)
    {
        clk_1;
        wait10;
        if(P1IN & BIT7)
        {
            temp = temp +mult;
        }
        mult = mult /2;
        wait10;
        clk_0;
        wait10;
    }
    return temp;
}

void i2c_ackn(void)
{
    clk_0;
    data_in;
    data_allowpullup;
    data_1;
    wait10;
    clk_1;

    if((P1IN & BIT7))
    {
        scm_print("//fail// ");
    }
    else
    {
        scm_print("//ackn// ");
    }
    wait10;
    clk_0;

}


void i2c_start_conv(uint8_t addr)
{
    clk_out;
    data_out;
    clk_1;
    data_1;
    wait10;
    data_0;
    wait10;
    clk_0;


    uint8_t op = i2c_send_data(addr);

    i2c_ackn();

    if(op == 1)
    {
    scm_print("Temperatur: ");
    uint16_t temp = i2c_receive();
    char* buffer[8];
    scm_int2string(buffer, 8, temp);
    scm_print(buffer);
    }
    else
    {
        i2c_send_data(0b00000000);
        i2c_ackn();
    }

}

void i2c_set(uint8_t addr, uint8_t data)
{

}

void i2c_send(uint8_t trans)
{



}

