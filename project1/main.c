#include <msp430.h> 
#include "analog.h"
#include "scm.h"
#include "LCD.h"
#include "spi.h"
#include "i2c.h"
#include "onewire.h"

const char nonsense1[] = "_     __      __     __      __     __      _";
const char nonsense2[] = " \\__/  \\__/  \\__/  \\__/  \\__/  \\__/ ";
uint8_t nonsense3 = 0;


void clock_init(void);
void print_temps(void);

//strings used to store the temp values of each sensor
char analog_temp_string[8];
char spi_temp_string[8];
char i2c_temp_string[8];
char onewire_temp_string[8];


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //initialise Components
	clock_init();

	scm_init();
    spi_init();
	LCD_init();
	i2c_init();
	analog_adc_init();
	ow_init();



	while(1)
	{
	    //read temperatures and write them in corresponding buffers
        analog_get_temperature(analog_temp_string);
	    spi_get_temperature(spi_temp_string);
	    i2c_get_temperature_MSB(i2c_temp_string);
        ow_get_temperature(onewire_temp_string);


	    //print results to LCD
	    print_temps();
	    nonsense();
	}
	return 0;
}


void print_temps(void)
{
    LCD_set_col(30);
    LCD_set_page(0);
    LCD_print("----- Temperatur -----");
    LCD_set_page(2);
    LCD_set_col(30);

    LCD_print("Analog: ");
    LCD_set_col(90);
    LCD_print(analog_temp_string);
    LCD_print("C°     ");


    LCD_set_page(3);
    LCD_set_col(30);
    LCD_print("SPI: ");
    LCD_set_col(90);
    LCD_print(spi_temp_string);
    LCD_print("C°     ");


    LCD_set_page(4);
    LCD_set_col(30);
    LCD_print("I²C: ");
    LCD_set_col(90);
    LCD_print(i2c_temp_string);
    LCD_print("C°     ");

    LCD_set_page(5);
    LCD_set_col(30);
    LCD_print("OneWire: ");
    LCD_set_col(90);
    LCD_print(onewire_temp_string);
    LCD_print("C°     ");


}
void nonsense(void)
{
    //*nonsense*
    LCD_set_page(6);
    LCD_set_col(30-nonsense3);
    LCD_print(nonsense1);
    LCD_set_page(7);
    LCD_set_col(30-nonsense3);
    LCD_print(nonsense2);
    nonsense3++;
    if(nonsense3 >= 26){nonsense3 = 0;}

}

void clock_init(void)
{
    // Set clock registers for frequency of 1 MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
