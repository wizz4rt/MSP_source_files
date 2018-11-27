#include "scm.h"

int16_t pow(int8_t basis,int8_t exponent)
{
    int16_t bas = 1;
    for(int8_t i = 0; i<exponent;i++)
    {
        bas = bas*basis;
    }
    return bas;
}

/*
 * Initialisation of the uart
 */
void scm_init(void)
{
    // Choose periphal function of used pins
    P1SEL = BIT1 | BIT2 ;
    P1SEL2 = BIT1 | BIT2;

    UCA0CTL1 = UCSWRST; // disable module

    // Configuration for 9600 Baud at 1 MHz clock
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;

    UCA0CTL1 &= ~UCSWRST; // enable module
}

/**
 * Send a character with the hardware UART
 * @param[in] c byte to send
 */
void scm_putchar(char c)
{
    while (!(IFG2 & UCA0TXIFG)); // Buffer ready?
    UCA0TXBUF = c; // Write byte
}


/**
 * Get a character from the hardware UART
 * \return received byte
 */
char scm_getchar(void)
{
    while (!(IFG2 & UCA0RXIFG)); // Wait for data
    return UCA0RXBUF; // Return received byte

}
/*
 * Prints a character Array starting at "buffer" which terminates with '\0'
 */
void scm_print(char* buffer)
{
    while(!(*buffer=='\0'))
    {
        scm_putchar(*buffer);
        buffer++;
    }
}
/*
 * Write string from terminal to an array starting at buffer. End if "Enter" is pressed.
 * \return length of array
 */
int8_t scm_getchars(char* buffer)
{
    int8_t length = 0;
    while (1)
    {
        int8_t input = scm_getchar();   //read single char

        if(input==13)                   // stop writing when reading "Enter"(=13 in ASCII) and end buffer with NULL
        {
            *buffer = '\0';
            break;
        }
        *buffer = input;                //write char in array
        buffer++;
        length++;
    }
    return length;
}
/*
 * Get integer and save as string in buffer
 * decimal is the number of decimal digits after ','.
 * \return length of string
 */
int8_t scm_int2string(char* buffer, uint8_t buffer_size, int16_t number)
{
    int32_t vergleich = 1;
    int8_t laenge = 1;

    if(number < 0)                  //write '-' if number is less than 0
    {
        *buffer = '-';
        buffer++;
        laenge++;
        number = number * (-1);
    }

    while (number>=vergleich*10)    //calculate length of the number
    {
        laenge++;
        vergleich = vergleich*10;
    }
    while (vergleich!=0)            //write digits into buffer
    {
        int16_t ziffer = number/vergleich;
        *buffer = ziffer+48;
        buffer++;
        number = number-(ziffer*vergleich);
        vergleich = vergleich/10;
    }
    *buffer = '\0';                 //'\0' at the end to end string properly
    return laenge;
}

/*
 * use int2string to convert number into a string in buffer and set a commma so you get "decimal"-decimal digits
 * \return length of number
 */
int8_t scm_decimal2string(char* buffer, uint8_t buffer_size, int16_t number, int8_t decimal)
{
    int len = scm_int2string(buffer, buffer_size, number);

    for (int i = len; i>=(len-decimal); i--) //shift every char behind the comma to the right
    {
        buffer[i+1] = buffer[i];
    }
    buffer[len-decimal] = ',';              //set comma
    return len;
}

/*
 * Convert number from terminal to integer
 * \return integer
 */
int16_t scm_getint(void)
{
    char buffer[10];
    int8_t length = scm_getchars(buffer);
    int16_t sum = 0;
    int8_t factor = 1;
    for (int i = length-1;i>-1;i--)
    {
        sum += (buffer[i]-48)*factor;
        factor = factor *10;
    }
    scm_putchar(sum);
    return sum;
}

void scm_float2string(char* buffer, float floatvalue, uint8_t digits)
{
    uint8_t i = digits;
    uint16_t divider_1 = 10000; // for integer part
    uint16_t divider_2 = 1; // for decimal place
    int16_t value = 0;
    int16_t fraction = 0;

    while (i > 0)
    {
        divider_2 *= 10;
        i--;
    }

    /*
     * if value < 0: make it positive and store '-'
     * as first element in the string
     */
    i = 0;
    if (floatvalue < 0)
    {
        floatvalue = -floatvalue;
        buffer[0] = '-';
        i++;
    }

    // integer part
    value = (int16_t)floatvalue;

    // fractional part, add 5 for rounding
    fraction = (int16_t)((floatvalue - value) * divider_2 * 10 + 5);
    if (fraction > 10*divider_2)
    {
        value++;
    }

    // avoid leading zeros in dividing the divider by 10
    while ((divider_1 >= 10) && ((value / divider_1) == 0))
    {
        divider_1 /= 10;
    }

    while (divider_1 != 0)
    {
        buffer[i] = value / divider_1 + 0x30;
        value -= ((buffer[i] - 0x30) * divider_1);
        divider_1 /= 10;
        i++;
    }

    if (digits != 0)
    {
        buffer[i] = '.'; // add decimal separator
        i++;
    }

    while (divider_2 != 0)
    {
        buffer[i] = fraction / divider_2 + 0x30;
        fraction -= ((buffer[i] - 0x30) * divider_2);
        divider_2 /= 10;
        i++;
    }

    buffer[i - 1] = 0; // replace last char with NULL
}
