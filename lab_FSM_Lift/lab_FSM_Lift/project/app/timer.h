/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Description:  Interface of module timer.
 * --
 * -- $Id: timer.h 5605 2023-01-05 15:52:42Z frtt $
 * ------------------------------------------------------------------------- */

/* re-definition guard */
#ifndef _TIMER_H
#define _TIMER_H

/* standard includes */
#include <stdint.h>


/* -- Public function declarations
 * ------------------------------------------------------------------------- */

/* 
 * Interrupt service routines
 */
void TIM4_IRQHandler(void);


/*
 * Initialize hardware timer
 */
void timer_init(void);

/*
 * Start timer with specified duration (clocks of 100 Hz).
 */
void timer_start(uint16_t duration);

/*
 * Stop timer.
 */
void timer_stop(void);


/*
 * Returns actual value of timer variable.
 */
uint16_t timer_read(void);

#endif

