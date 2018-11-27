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

void ow_test(char* buffer)
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
    uint8_t temp_LSB = ow_read_byte();
    uint8_t temp_MSB = ow_read_byte();

    temp_MSB = temp_MSB << 4;
    temp_MSB += temp_LSB >> 4;
    temp_LSB &= 0b00001111;

    uint8_t bit_mask = BIT3;
    uint16_t nachkomma = 0;
    uint16_t div = 500;
    for(uint8_t i = 0; i<4;i++)
    {
        nachkomma = nachkomma + (div*(temp_LSB & bit_mask));
        bit_mask = bit_mask >>1;
        div = div>>1;
    }

    uint8_t len = scm_int2string(buffer, 4, temp_MSB);
    buffer[len] = ',';

    char buffer2[4];
    scm_int2string(buffer2, 4, nachkomma);

    buffer[len+1] = buffer2[0];
    buffer[len+2] = buffer2[1];
    buffer[len+3] = '\0';
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
    while(P1IN & BIT4);
    //scm_print("ackn");
    pin_out;
    pin_deniepullup;
    pin_1;
    __delay_cycles(250);
}

void ow_send_1(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(10);
    pin_1;
    __delay_cycles(80);
}

void ow_send_0(void)
{
    pin_out;
    pin_deniepullup;
    pin_0;
    __delay_cycles(80);
    pin_1;
    __delay_cycles(2);
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
    return bit;
}

uint8_t ow_read_byte(void)
{
    uint8_t mul = 1;
    uint8_t data = 0;
    for(uint8_t i = 0;i<8;i++)
    {
        data = data + (mul*(ow_read_bit()));
        mul = mul<<1;
    }
    return data;
}
