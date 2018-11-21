#include <msp430.h> 
#include "analog_t.h"
#include "scm.h"
#include "LCD.h"
#include "spi.h"

//setup P1.5/7 to be used with the UCSI
#define SET_P1SEL_SPI       P1SEL |= BIT5 | BIT7 | BIT6
#define SET_P1SEL2_SPI      P1SEL2 |= BIT5 | BIT7| BIT6
//reset P1.5/7 to be used as GPIO again
#define RESET_P1SEL_SPI     P1SEL &= ~(BIT5 | BIT7| BIT6)
#define RESET_P1SEL2_SPI    P1SEL2 &= ~(BIT5 | BIT7| BIT6)



void clock_init(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //initialise Components
	clock_init();
	analog_t_adc_init();
	scm_init();
    spi_init();
	LCD_init();




	char analog_temp[7];
	uint16_t t = 0;

	while(1)
	{
	    __delay_cycles(100000);

	    get_SPI_temperature();


	    scm_decimal2string(analog_temp, 7, analog_t_temperature(), 2);  //write temperature from analog sensor in buffer
	    //scm_print("Analog: ");
	    //scm_print(analog_temp);                                         //print buffer to console
	    //scm_print("\r\n");


	    //print results to LCD
	    LCD_set_col(30);
	    LCD_set_page(0);
	    LCD_print("----- Temperatur -----");

	    LCD_set_page(2);
	    LCD_set_col(30);
	    LCD_print("Analog: ");
	    LCD_print(analog_temp);
	    LCD_print("C°     ");

	    LCD_set_page(3);
	    LCD_set_col(30);
	    LCD_print("SPI: ");
	    LCD_print(" ");
	    LCD_print("C°     ");

	    LCD_set_page(4);
	    LCD_set_col(30);
	    LCD_print("I²C: ");
	    LCD_print(" ");
	    LCD_print("C°     ");

	    LCD_set_page(5);
	    LCD_set_col(30);
	    LCD_print("OneWire: ");
	    LCD_print(" ");
	    LCD_print("C°     ");
	    }


	return 0;
}
void get_SPI_temperature()
{
    SET_P1SEL_SPI;
    SET_P1SEL2_SPI;

    P1OUT |= BIT3;

    spi_send(0x02);
    while(UCB0STAT & UCBUSY);
    spi_send(0xfd);
    while(UCB0STAT & UCBUSY);
    int8_t temp = UCB0RXBUF;

    char buffer[8];
    scm_int2string(buffer, 8, temp);
    scm_print(buffer);

    P1OUT &= ~BIT3;

    RESET_P1SEL_SPI;
    RESET_P1SEL2_SPI;
    P1OUT &= ~(BIT5 | BIT7);
}

void clock_init(void)
{
    // Set clock registers for frequency of 1 MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
