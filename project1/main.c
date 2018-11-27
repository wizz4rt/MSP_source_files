#include <msp430.h> 
#include "analog.h"
#include "scm.h"
#include "LCD.h"
#include "spi.h"
#include "i2c.h"
#include "onewire.h"

//setup P1.5/7 to be used with the UCSI
//#define SET_P1SEL_SPI       P1SEL |= (BIT5 | BIT7); P1DIR |= (BIT5 + BIT7)
//#define SET_P1SEL2_SPI      P1SEL2 |= (BIT5 | BIT7); P1DIR |= (BIT5 + BIT7)
//reset P1.5/7 to be used as GPIO again
//#define RESET_P1SEL_SPI     P1SEL &= ~(BIT5 | BIT7); P1DIR |= (BIT5 + BIT7)
//#define RESET_P1SEL2_SPI    P1SEL2 &= ~(BIT5 | BIT7); P1DIR |= (BIT5 + BIT7)



void clock_init(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //initialise Components
	clock_init();

	scm_init();
    //spi_init();
	LCD_init();
	i2c_init();
	analog_adc_init();
	ow_init();


	int16_t analog_temp = 0;
    uint8_t spi_temp = 0;

	char analog_temp_string[9];
    char spi_temp_string[7];
    char i2c_temp_string[7];
    char onewire_temp_string[7];

	while(1)
	{
	    //read temperatures
        analog_temp = analog_get_temperature(analog_temp_string);
	    //spi_temp = spi_get_temperature();
	    i2c_get_temperature_MSB(i2c_temp_string);

	    __delay_cycles(10000);

	    //write temperatures in corresponding buffers

	    scm_int2string(spi_temp_string, 7, spi_temp);

	    ow_test(onewire_temp_string);


	    P1SEL &= ~(BIT5 + BIT7);
	    P1SEL2 &= ~(BIT5 + BIT7);
	    //print results to LCD
	    LCD_set_col(30);
	    LCD_set_page(0);
	    LCD_print("----- Temperatur -----");
	    LCD_set_page(2);
	    LCD_set_col(30);

	    LCD_print("Analog: ");
	    LCD_print(analog_temp_string);
        scm_print(analog_temp_string);
	    LCD_print("C°     ");
        scm_print("\n\r");


	    LCD_set_page(3);
	    LCD_set_col(30);
	    LCD_print("SPI: ");
	    LCD_print(spi_temp_string);
	    scm_print(spi_temp_string);
	    LCD_print("C°     ");
        scm_print("\n\r");


	    LCD_set_page(4);
	    LCD_set_col(30);
	    LCD_print("I²C: ");
	    LCD_print(i2c_temp_string);
	    scm_print(i2c_temp_string);
	    LCD_print("C°     ");
        scm_print("\n\r");

	    LCD_set_page(5);
	    LCD_set_col(30);
	    LCD_print("OneWire: ");
	    LCD_print(onewire_temp_string);
	    LCD_print("C°     ");
	    }

	return 0;
}


void clock_init(void)
{
    // Set clock registers for frequency of 1 MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
