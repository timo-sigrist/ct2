/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Description:  Implementation of module dice_counter
 * --               The module provides a counter that can be used as
 * --               pseudo random number generator for a dice.
 * --
 * -- $Id: dice_counter.c 2977 2016-02-15 16:05:50Z ruan $
 * ------------------------------------------------------------------
 */

/* user includes */
#include "dice_counter.h"

/* variables visible within the whole module*/
static uint8_t dice_counter = 1;

/* function definitions */

/// STUDENTS: To be programmed
/*
 * Increments the module internal counter; The function has to be called
 * regularly in a loop to allow generation of a pseudo random number
 */
void dice_counter_increment(void){
	dice_counter = dice_counter%NR_OF_DICE_VALUES +1;
}

/*
 * Returns the current value of the module internal counter. The return
 * value can be used as a pseudo random number.
 */
uint8_t dice_counter_read(void){
	return dice_counter;
}
/// END: To be programmed