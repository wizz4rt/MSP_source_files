/*
 * i2c.c
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */


#include "i2c.h"


void i2c_init(void)
{
    CLK_OUT;
    DATA_OUT;
    DATA_DENIEPULLUP;
}

void i2c_send_bit(uint8_t bit)
{
    CLK_0;
    DATA_OUT;
    if(bit==1)
    {
        DATA_1;
        //scm_putchar(49);
    }
    else
    {
        DATA_0;
        //scm_putchar(48);
    }
    WAIT1000;
    CLK_1;
    WAIT1000;
    CLK_0;
    WAIT1000;
}

uint8_t i2c_send_data(uint8_t data)
{
    CLK_0;
    DATA_OUT;
    DATA_0;
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

uint8_t i2c_read_bit(void)
{
    CLK_0;
    DATA_IN;
    DATA_ALLOWPULLUP;
    DATA_1;
    WAIT1000;
    CLK_1;
    WAIT1000;
    if(P1IN & BIT7)
    {
        scm_putchar(49);
        WAIT1000;
        CLK_0;
        WAIT1000;
        DATA_DENIEPULLUP;
        DATA_OUT;
        return 1;
    }
    scm_putchar(48);
    WAIT1000;
    CLK_0;
    WAIT1000;
    DATA_DENIEPULLUP;
    DATA_OUT;
    return 0;

}

uint8_t i2c_receive(void)
{
    CLK_0;
    DATA_IN;
    DATA_ALLOWPULLUP;
    DATA_1;
    WAIT1000;
    uint8_t temp=0;
    uint8_t mult=128;
    for(uint8_t j=0; j<8; j++)
    {
        temp = temp + (mult*i2c_read_bit());
        mult = mult/2;
    }
    scm_putchar(9);
    DATA_DENIEPULLUP;
    DATA_OUT;
    return temp;
}

void i2c_ackn(void)
{
    CLK_0;
    DATA_IN;
    DATA_ALLOWPULLUP;
    DATA_1;
    WAIT1000;
    CLK_1;

    if(!(P1IN & BIT7));
    WAIT1000;
    CLK_0;

    DATA_DENIEPULLUP;
    DATA_OUT;

}

uint8_t i2c_start_conv(uint8_t addr)
{
    CLK_OUT;
    DATA_OUT;
    DATA_DENIEPULLUP;
    CLK_1;
    DATA_1;
    WAIT1000;
    DATA_0;
    WAIT1000;
    CLK_0;

    uint8_t op = i2c_send_data(addr);

    if(op)
    {
    i2c_ackn();
    uint8_t temp = i2c_receive();
    i2c_send_bit(1);
    return temp;
    }
    else
    {
        i2c_send_bit(0);
        i2c_send_data(0b00000000);
        i2c_ackn();
        i2c_send_bit(1);
        return 1;
    }

}

void i2c_get_temperature(void)
{
    if(i2c_start_conv(0b10010000))
    {
        char* buffer[4];
        scm_int2string(buffer, 4, i2c_start_conv(0b10010001));
        scm_print("Es sind: ");
        scm_print(buffer);
        scm_print("C°\n\r");
    }
}

void i2c_set(uint8_t addr, uint8_t data)
{

}

void i2c_send(uint8_t trans)
{



}

