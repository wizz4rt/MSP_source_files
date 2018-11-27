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
    data_deniepullup;
}

void i2c_send_bit(uint8_t bit)
{
    clk_0;
    data_out;
    if(bit==1)
    {
        data_1;
    }
    else
    {
        data_0;
    }
    wait10;
    clk_1;
    wait10;
    clk_0;
    wait10;
}
/*
 * send a whole character
 * \return the last bit (read/write Operation)
 */
uint8_t i2c_send_data(uint8_t data)
{
    clk_0;
    data_out;
    data_0;
    uint16_t div =128;
    uint8_t bit;
    for(uint8_t i = 0; i<8;i++) // send each bit of data
    {
        bit = (uint8_t) data/div;
        i2c_send_bit(bit);
        data = data-(div*bit);
        div = div/2;
    }
    return bit;

}

/*
 * read a single bit from data line
 * \return its value
 */
uint8_t i2c_read_bit(void)
{
    clk_0;
    data_in;
    data_allowpullup;
    data_1;
    wait10;
    clk_1;
    wait10;
    if(P1IN & BIT7)
    {;
        wait10;
        clk_0;
        wait10;
        data_deniepullup;
        data_out;
        return 1;
    }
    wait10;
    clk_0;
    wait10;
    data_deniepullup;
    data_out;
    return 0;

}
/*
 * recieve whole characte
 * \return character
 */
uint8_t i2c_receive(void)
{
    clk_0;
    data_in;
    data_allowpullup;
    data_1;
    wait10;

    uint8_t temp=0;
    uint8_t mult=128;
    for(uint8_t j=0; j<8; j++)
    {
        temp = temp + (mult*i2c_read_bit());
        mult = mult/2;
    }

    data_deniepullup;
    data_out;
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

    if(!(P1IN & BIT7))
    {
    //scm_print("//ackn// ");
    }
    wait10;
    clk_0;

    data_deniepullup;
    data_out;

}


/*
 * start a conversation by sending a statrt bit and an address addr. Return the char thats recieved afterwards.
 * if next == 0 keep the conversation up, but dont recieve the next char
 */

uint8_t i2c_start_conv(uint8_t addr, uint8_t next)
{
    clk_out;
    data_out;
    data_deniepullup;
    clk_1;
    data_1;
    wait10;
    data_0;
    wait10;
    clk_0;


    uint8_t op = i2c_send_data(addr);



    if(op)
    {
    i2c_ackn();
    uint8_t temp = i2c_receive();
    i2c_send_bit(next);                    //änderung um LSB auch zu empfangen
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

uint8_t i2c_get_temperature_MSB(char* buffer)
{
    uint8_t temp_MSB;
    uint8_t temp_LSB;

    if(i2c_start_conv(0b10010000, 1))
    {
        uint8_t temp_MSB = i2c_start_conv(0b10010001, 0);
        uint8_t temp_LSB = i2c_receive();
        temp_LSB = temp_LSB >> 7;

        uint8_t len = scm_int2string(buffer, 4, temp_MSB);
        buffer[len] = ',';
        if(temp_LSB)
        {
            buffer[len+1] = '5';
        }else{
            buffer[len+1] = '0';
        }
        buffer[len+2] = '0';
        buffer[len+3] = '\0';
    }
    return temp_MSB;
}

