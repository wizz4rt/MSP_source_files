/*
 * onewire.c
 *
 *  Created on: 26.11.2018
 *      Author: tnellius
 */
#include <onewire.h>

void ow_init(void)
{
    //pin-setup
    P1SEL &= ~BIT4;         //reset pin-select for pin4
    P1SEL2 &= ~BIT4;
    PIN_OUT;                //pin4 as output
    PIN_DENIEPULLUP;        //disable pullup
    PIN_1;                  //set pin4 to high

    //sensor-setup
    ow_reset();                 //initiate interaction
    ow_send_data(0xCC);         //skip rom-command
    ow_send_data(0x4E);         //write scratchpad
    ow_send_data(0xFF);         //set TH
    ow_send_data(0xFF);         //set TL
    ow_send_data(0b01011111);   //choose 11-Bit resolution
}

void ow_get_temperature(char* temp_buffer)
{
    ow_reset();                 //initiate interaction
    ow_send_data(0xCC);         //skip rom-command
    ow_send_data(0x44);         //initiate temperature-conversion
    PIN_IN;
    PIN_ALLOWPULLUP;
    PIN_PULLUP;
    __delay_cycles(400000);     //provide power to sensor during conversion
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_1;

    ow_reset();                         //initiate interaction
    ow_send_data(0xCC);                 //skip rom-command
    ow_send_data(0xBE);                 //initiate receive-transmission from scratchpad
    uint8_t temp_LSB = ow_read_data();  //receive and store LS-Byte
    uint8_t temp_MSB = ow_read_data();  //receive and store MS-Byte

    uint16_t temp_dec = (ow_calculate_predec(temp_MSB, temp_LSB)*100) + ow_calculate_dec(temp_LSB);
    //calculate full temperature without comma

    scm_decimal2string(temp_buffer, 8, temp_dec, 2);    //write temperature to buffer with comma
}

uint8_t ow_calculate_predec(uint8_t msb, uint8_t lsb)
{
    msb = msb<<4;       //last 4 bits of MSB as first bits of predecimal
    lsb = lsb>>4;       //first 4 bits of LSB as last bits of predecimal
    return (msb|lsb);   //return predecimal
}

uint8_t ow_calculate_dec(uint8_t lsb)
{
    uint16_t dec = 0;               //decimal
    if(lsb & BIT3){dec += 50;}
    if(lsb & BIT2){dec += 25;}
    if(lsb & BIT1){dec += 13;}
    if(lsb & BIT0){dec += 6;}
    return (uint8_t) dec;        //return two decimal-digits
}

void ow_reset(void)
{
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_0;
    __delay_cycles(500);    //reset pulse for 500µs
    PIN_IN;
    PIN_ALLOWPULLUP;
    PIN_PULLUP;
    while(P1IN & BIT4);     //wait for presence-pulse by slave
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_1;
    __delay_cycles(250);    //wait for sequence to end
}

void ow_send_1(void)
{
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_0;                  //initiate send-slot
    __delay_cycles(10);
    PIN_1;                  //send logical 1
    __delay_cycles(80);
}

void ow_send_0(void)
{
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_0;                  //initiate send-slot
    __delay_cycles(80);
    PIN_1;                  //send logical 0
    __delay_cycles(2);
}

void ow_send_data(uint8_t data)
{
    uint8_t div = 1;
    for(uint8_t i=0; i<8; i++)      //transmit whole data-byte, bit by bit //LS-Bit first
    {
        if(data & div)
        {
            ow_send_1();            //send logical 1
        }
        else
        {
            ow_send_0();            //sen logical 0
        }
        div = div<<1;
    }
}

uint8_t ow_read_bit(void)
{
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_0;              //initiate read-slot
    __delay_cycles(5);
    PIN_IN;
    PIN_ALLOWPULLUP;
    PIN_PULLUP;
    uint8_t bit;
    if(P1IN & BIT4)     //read a logical 1?
    {
        bit = 1;        //store value in bit
    }
    else
    {
        bit = 0;        //store value in bit
    }
    PIN_OUT;
    PIN_DENIEPULLUP;
    PIN_1;
    __delay_cycles(60); //wait for read-slot to end
    return bit;
}

uint8_t ow_read_data(void)
{
    uint8_t mul = 1;
    uint8_t data = 0;
    for(uint8_t i = 0;i<8;i++)                  //receive whole byte, bit by bit //LS-Bit first
    {
        data = data + (mul*(ow_read_bit()));    //store byte in data
        mul = mul<<1;
    }
    return data;
}
