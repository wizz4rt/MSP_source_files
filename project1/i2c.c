/*
 * i2c.c
 *
 *  Created on: 22.11.2018
 *      Author: Jan-Niclas
 */


#include "i2c.h"


void i2c_init(void)
{
    //pin setup
    CLK_OUT;
    DATA_OUT;
    DATA_DENIEPULLUP;

    //sensor setup
    i2c_send_startbit();
    i2c_send_data(0b10010000);      //initiate write-action
    i2c_send_bit(0);
    i2c_send_data(0b00000000);      //put sensor in continuously-measure-mode
    i2c_ackn();
    i2c_send_bit(1);                //master-acknowledge
}

void i2c_send_bit(uint8_t bit)
{
    CLK_0;
    DATA_OUT;
    if(bit==1)
    {
        DATA_1;         //send logical 1
    }
    else
    {
        DATA_0;         //send logical 0
    }
    WAIT1000;
    CLK_1;
    WAIT1000;
    CLK_0;
    WAIT1000;
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
    if(P1IN & BIT7)         //read a logical 1?
    {
        WAIT1000;
        CLK_0;
        WAIT1000;
        DATA_DENIEPULLUP;
        DATA_OUT;
        return 1;           //give back logical 1
    }
    WAIT1000;
    CLK_0;
    WAIT1000;
    DATA_DENIEPULLUP;
    DATA_OUT;
    return 0;               //give back logical 0

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
    for(uint8_t j=0; j<8; j++)                  //receive a byte, bit by bit
    {
        temp = temp + (mult*i2c_read_bit());    //if 1 was read: add mult to temp
        mult = mult>>1;                         //divide mult by 2
    }
    DATA_DENIEPULLUP;
    DATA_OUT;
    return temp;        //return received byte
}

void i2c_ackn(void)
{
    CLK_0;
    DATA_IN;
    DATA_ALLOWPULLUP;
    DATA_1;
    WAIT1000;
    CLK_1;

    if(!(P1IN & BIT7));     //wait for slave to acknowledge
    WAIT1000;
    CLK_0;

    DATA_DENIEPULLUP;
    DATA_OUT;

}

void i2c_send_startbit(void)
{
    //startbit_sequence
    CLK_OUT;
    DATA_OUT;
    DATA_DENIEPULLUP;
    CLK_1;
    DATA_1;
    WAIT1000;
    DATA_0;         //set startbit
    WAIT1000;
    CLK_0;
}

void i2c_send_data(uint8_t data)
{
    DATA_OUT;
    DATA_0;
    uint8_t div =128;
    for(uint8_t i = 0; i<8; i++)
    {
        if(div & data)
        {
            i2c_send_bit(1);
        }
        else
        {
            i2c_send_bit(0);
        }
        div = div>>1;
    }
}

void i2c_get_temperature(char* temp_buffer)
{
    i2c_send_startbit();
    i2c_send_data(0b10010001);
    i2c_ackn();
    uint8_t temp_MSB = i2c_receive();
    i2c_send_bit(0);
    uint8_t temp_LSB = i2c_receive();

    uint8_t predec_len = scm_int2string(temp_buffer, 8, temp_MSB);
    temp_buffer[predec_len] = ',';
    if(temp_LSB & BIT7)
    {
        temp_buffer[predec_len+1] = '5';
        temp_buffer[predec_len+2] = '0';
    }
    else
    {
        temp_buffer[predec_len+1] = '0';
        temp_buffer[predec_len+2] = '0';
    }
    temp_buffer[predec_len+3] = '\0';
}
