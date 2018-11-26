/*
 * onewire.c
 *
 *  Created on: 26.11.2018
 *      Author: tnellius
 */
#include <onewire.h>

void ow_init(void)
{
    P1SEL &= ~BIT4;
    P1SEL2 &= ~BIT4;
    pin_out;
    pin_deniepullup;
    pin_1;
}

void ow_test(void)
{
    ow_start_conv();
    ow_send_byte(0xCC);
    ow_send_byte(0x44);
    pin_in;
    pin_allowpullup;
    pin_pullup;
    __delay_cycles(1000000);
    pin_out;
    pin_deniepullup;
    pin_1;
    ow_start_conv();
    ow_send_byte(0xCC);
    ow_send_byte(0xBE);
    ow_read_byte();
    uint8_t temp = ow_read_byte();
    char buffer[4];
    scm_int2string(buffer, 4, temp);
    scm_print(buffer);
}

void ow_start_conv(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(500);
    pin_in;
    pin_allowpullup;
    pin_pullup;
    while(P1IN & BIT4)
    {
        scm_putchar(46);
    }
    scm_print("ackn");
    pin_out;
    pin_deniepullup;
    pin_1;
    __delay_cycles(240);
}

void ow_send_1(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(2);
    pin_1;
    __delay_cycles(60);
}

void ow_send_0(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(60);
    pin_1;
}




void ow_send_byte(uint8_t data)
{
    uint8_t div = 1;
    for(uint8_t i=0; i<8;i++)
    {
        if(data & div)
        {
            ow_send_1();
        }
        else
        {
            ow_send_0();
        }
        div = div<<1;
    }
}

uint8_t ow_read_bit(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(5);
    pin_in;
    pin_allowpullup;
    pin_pullup;
    __delay_cycles(20);
    uint8_t bit;
    if(P1IN & BIT4)
    {
        bit = 1;
    }
    else
    {
        bit = 0;
    }
    pin_out;
    pin_deniepullup;
    pin_1;
    __delay_cycles(60);
}

uint8_t ow_read_byte(void)
{
    uint8_t mul = 1;
    uint8_t data = 0;
    for(uint8_t i = 0;i<8;i++)
    {
        data = data + (mul*(ow_read_bit()));
        mul = mul>>2;
    }
    return data;
}
