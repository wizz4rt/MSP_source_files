/** \file
 * \brief Definition of LCD functions.
 */

#include <stdint.h>

// Constants
#define STAY_LOW_RST    3       /**< Reset low pulse width at 1 MHz*/
#define WAIT_WR         6000    /**< Reset to WR pulse delay at 1 MHz*/

// Names of pins, Port 1
#define DATA    BIT7        /**< data pin*/
#define CLK     BIT5        /**< clock pin*/

// Names of pins, Port 2
#define CD      BIT5        /**< data or command decider pin*/
#define RST     BIT4        /**< reset pin*/
#define CS      BIT3        /**< chip selct pin*/

// Setting and clearing of bits
#define LCD_DATA_CLEAR  P1OUT &= ~DATA  /**< data pin gets low*/
#define LCD_DATA_SET    P1OUT |= DATA   /**< data pin gets high*/
#define LCD_CLK_CLEAR   P1OUT &= ~CLK   /**< clock pin gets low*/
#define LCD_CLK_SET     P1OUT |= CLK    /**< clock pin gets high*/
#define LCD_CD_CLEAR    P2OUT &= ~CD    /**< byte is a command*/
#define LCD_CD_SET      P2OUT |= CD     /**< byte is data*/
#define LCD_RST_CLEAR   P2OUT &= ~RST   /**< reset pin gets low*/
#define LCD_RST_SET     P2OUT |= RST    /**< reset pin gets high*/
#define LCD_CS_CLEAR    P2OUT &= ~CS    /**< chip select pin gets low*/
#define LCD_CS_SET      P2OUT |= CS     /**< chip select pin gets high*/

// Bits names for commands
#define PC0 BIT0 /**< Booster: 0 = OFF; 1 = ON*/
#define PC1 BIT1 /**< Regulator: 0 = OFF; 1 = ON*/
#define PC2 BIT2 /**< Follower: 0 = OFF; 1 = ON*/
#define C1  BIT0 /**< 0: show SRAM content, 1: set all SEG-Driver to ON*/
#define C0  BIT0 /**< 0: show SRAM  content, 1: show inverse SRAM contnet*/
#define C2  BIT0 /**< 0: disable Display, 1: enable Display*/
#define MX  BIT0 /**< SEG: 0 = normal (=0..131); 1 = mirror (131..0)*/
#define MY  BIT3 /**< COM: 0 = normal (0..63); 8 = mirror (63..0)*/
#define BR  BIT0 /**< Ratio: 0 = 1/9; 1 = 1/7*/
#define TC  BIT7 /**< Temp.-comp.: 0 = -0,05 %/°C; 128 = -0,11 %/°C*/
#define WC  BIT1 /**< Column wrap around 0 = OFF; 1 = ON*/
#define WP  BIT0 /**< Page wrap around 0 = OFF; 1 = ON*/

// Commands for LCD-Controller UC1701
#define SET_COLUMN_ADRESS_LSB       0x00
/**< load bits 3..0 with lower nibble of CA, CA = 0..131*/
#define SET_COLUMN_ADRESS_MSB       0x10
/**< load bits 3..0 with upper nibble of CA CA = 0..131*/
#define SET_POWER_CONTROL           0x28
/**< set or clear bits 2..0 with PC2, PC1, PC0*/
#define SET_SCROLL_LINE             0x40
/**< load bits 5..0 (0..63) with the scroll line*/
#define SET_PAGE_ADDRESS            0xB0
/**< load bits 0..7 with the SRAM page address*/
#define SET_VLCD_RESISTOR_RATIO     0x20
/**< load bits 2..0 with the Resistor ratio (0..7)*/
#define SET_ELECTRONIC_VOLUME_MSB   0x81
/**< electronic volume upper byte, constant command*/
#define SET_ELECTRONIC_VOLUME_LSB   0x00
/**< electronic volume lower byte, load bits 5..0 (0..63) with the volume*/
#define SET_ALL_PIXEL_ON            0xA4
/**< set bit C1 to switch all pixels on*/
#define SET_INVERSE_DISPLAY         0xA6
/**< set or clear bit C0 to show normal or inverse SRAM content*/
#define SET_DISPLAY_ENABLE          0xAE
/**< set bit C2 to enable the display, clear it for sleep*/
#define SET_SEG_DIRECTION           0xA0
/**< set or clear bit MX to show normal or inverse SEG*/
#define SET_COM_DIRECTION           0xC0
/**< set or clear bit MY to show normal or inverse COM*/
#define SET_SYSTEM_RESET            0xE2
/**< system reset, constant command*/
#define SET_LCD_BIAS_RATIO          0xA2
/**< set or clear bit BR to define Bias Ratio*/
#define SET_ADV_PROGRAM_CONTROL_MSB 0xFA
/**< advanced control upper byte, constant command*/
#define SET_ADV_PROGRAM_CONTROL_LSB 0x10
/**< advanced control lower byte, set or clear bits TC, WC,WP*/

struct font_info
{
    uint16_t size;          // size of data array
    uint8_t  width;         // (maximum) width of character
    uint8_t  height;        // height of character
    uint8_t  firstchar;     // the number of the first included
                            // character (often 0x20)
    uint8_t  lastchar;      // the last included character (often 0xFF)
    uint8_t* widthtable;    // Pointer to the table holding character
                            // widths (NULL for monospaced fonts)
    uint8_t* data;          // Pointer to data arrray
};
/**< Struct for font definition*/

extern const struct font_info font_proportional_8px;

/**
 * Writes command to the display
 * @param[in] cmd command to the display
 */
void LCD_write_cmd(int8_t cmd);

/**
 * Writes data to the display
 * @param[in] data
 */
void LCD_write_data(int8_t data);

/**
 * Set the current LCD page (= row)
 * @param[in] page Select the row
 */
void LCD_set_page(int8_t page);

/**
 * Set the current LCD column
 * @param[in] col Selcts the column
 */
void LCD_set_col(uint8_t col);

/**
 * Clear LCD
 */
void LCD_clear(void);

/**
 * Initialize LCD (includes IO-config)
 */
void LCD_init(void);

/**
 *  Write single char to the LCD
 *  @param[in] *font pointer to struct info
 *  @param[in] c char to print
 */
void LCD_put_char(struct font_info* font, char c);

/**
 *  Write text to the LCD
 *  @param[in] *str pointer to string
 */
void LCD_print(char* str);
