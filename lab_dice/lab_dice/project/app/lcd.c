/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module lcd
 * --               Performs all the interactions with the lcd
 * --
 * -- $Id: lcd.c 5144 2020-09-01 06:17:21Z ruan $
 * ------------------------------------------------------------------
 */

/* standard includes */
#include <stdio.h>

/* user includes */
#include "lcd.h"
#include "reg_ctboard.h"

/* macros */
#define LCD_ADDR_LINE1      0u
#define LCD_ADDR_LINE2      20u

#define NR_OF_CHAR_PER_LINE 20u

#define LCD_CLEAR           "                    "

/// STUDENTS: To be programmed
/*
 * \brief  Writes 'value' to the indicated 'position' on the lcd
 * 
 * \param  slot_nr: A number between 1 and 6 indicating at which one of the 
 *         six available slots on the lcd the 'value' shall be printed. The 
 *         values at the other 5 slots remain unchanged.
 * 
 * \param  value: The value to be printed
 */
 #define MAX_BG_COLOR 65535
void lcd_write_value(uint8_t slot_nr, uint8_t value){
	char string[3];
	// 1; 0 1 
	// 2; 3 4
	// (slot-1)*3
	int pos1 = (slot_nr-1)*3;
	int pos2 = pos1 + 1;
	(void)snprintf(string,3,"%2i",value);
	CT_LCD->ASCII[pos1] = string[0];
	CT_LCD->ASCII[pos2] = string[1];
}

/*
 * \brief  Writes an explanatory string followed by 'total_value' on the lcd. 
 * 
 * \param  total_value: The value to be printed
 */
void lcd_write_total(uint8_t total_value){
	char string[NR_OF_CHAR_PER_LINE];
	int i;
	(void)snprintf(string,NR_OF_CHAR_PER_LINE,"total throws %4i",total_value);
	for(i = 0;i < NR_OF_CHAR_PER_LINE;i++){
		CT_LCD->ASCII[LCD_ADDR_LINE2 + i] = string[i];
	}
}

/*
 * \brief  Clears the lcd and switches it to light green. 
 */
void hal_ct_lcd_clear(void){
	int i;
	for(i = 0;i < NR_OF_CHAR_PER_LINE;i++){
		CT_LCD->ASCII[LCD_ADDR_LINE1 + i] = LCD_CLEAR[i];
		CT_LCD->ASCII[LCD_ADDR_LINE2 + i] = LCD_CLEAR[i];
	}
	CT_LCD->BG.RED = MAX_BG_COLOR;
	CT_LCD->BG.GREEN = MAX_BG_COLOR;
	CT_LCD->BG.BLUE = MAX_BG_COLOR;
}
/// END: To be programmed