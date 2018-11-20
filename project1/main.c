#include <msp430.h> 
#include "analog_t.h"
#include "scm.h"
#include "LCD.h"

//fuckinf hell

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	clock_init();
	analog_t_adc_init();
	scm_init();
	LCD_init();

	LCD_set_col(30);
	LCD_set_page(0);

	char buffer[10];

	while(1)
	{
	    __delay_cycles(100000);
	    //scm_int2string(buffer, 10, analog_t_temperature());
	    scm_decimal2string(buffer, 10, analog_t_temperature(), 2);
	    scm_print(buffer);
	    scm_print("\r\n");
	    LCD_set_col(30);
	    LCD_set_page(0);
	    LCD_print("Temperatur: ");
	    LCD_print(buffer);
	    LCD_print("C°  ");
	    }

    /*clock_init();
    scm_init();
    scm_print("fucking nigga ylfha");
	char buffer[10];
	scm_int3string(buffer, 10,32);
	scm_print(buffer);
	*/

	return 0;
}
void clock_init(void)
{
    // Set clock registers for frequency of 1 MHz
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
