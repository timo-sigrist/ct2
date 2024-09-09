/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zurich University of             -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                 -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Application for testing external memory
 * --
 * -- $Id: main.c 5317 2020-12-04 15:56:47Z ruan $
 * ------------------------------------------------------------------
 */

#include <stdint.h>
#include "hal_rcc.h"
#include "hal_fmc.h"
#include "hal_ct_lcd.h"
#include "reg_ctboard.h"
#include "hal_ct_buttons.h"
#include "hal_ct_seg7.h"

#define NR_OF_DATA_LINES           8
#define NR_OF_ADDRESS_LINES       11
#define CHECKER_BOARD           0xAA
#define INVERSE_CHECKER_BOARD   0x55
#define WALKING_ONES_ADDRESS    0x7FF

/* Set-up the macros (#defines) for your test */
/// STUDENTS: To be programmed
#define RAM(OFFSET) (*((uint8_t *)(0x64000000 + OFFSET)))

#define SRAM_BASE_ADDR  0x64000000

void show_addr_error(uint16_t addr){
	if (addr == 0x0000) addr = 0xF000;
	CT_LED->HWORD.LED31_16 |= addr;
}

void show_device_error(uint32_t adr){
	CT_SEG7->BIN.HWORD = adr;
	while (!hal_ct_button_is_pressed(HAL_CT_BUTTON_T0)) {}
}
/// END: To be programmed

int main(void)
{
    hal_fmc_sram_init_t init;
    hal_fmc_sram_timing_t timing;
    
    /* add your required automatic (local) variables here */ 
    /// STUDENTS: To be programmed

		uint8_t *base_addr = (uint8_t *) SRAM_BASE_ADDR;
		uint8_t *mem_ptr = ((uint8_t *) (SRAM_BASE_ADDR + WALKING_ONES_ADDRESS));
		uint16_t ones;
	  uint16_t address = (uint16_t) 0x01 << NR_OF_ADDRESS_LINES;
	
		uint16_t test_address = (uint16_t) 0x01 << NR_OF_ADDRESS_LINES;
	
		CT_LED->WORD = 0x00000000;



    /// END: To be programmed

    init.address_mux = DISABLE;                             // setup peripheral
    init.type = HAL_FMC_TYPE_SRAM;
    init.width = HAL_FMC_WIDTH_8B;
    init.write_enable = ENABLE;

    timing.address_setup = 0xFF;                            // all in HCLK
                                                            // cycles
    timing.address_hold = 0xFF;
    timing.data_setup = 0xFF;

    hal_fmc_init_sram(HAL_FMC_SRAM_BANK2, init, timing);    // init external bus
                                                            // bank 2 (NE2)
                                                            // asynch
    
    /* Data Bus Test - Walking ONES test */
    /// STUDENTS: To be programmed
		
    for(ones = 1;ones < (1 << NR_OF_DATA_LINES); ones = ones << 1){
			*(mem_ptr) = ones;
			if (ones != *(mem_ptr)){
				CT_LED->BYTE.LED7_0 |= ones;
			}
		}
		
    /// END: To be programmed
    
    /* Address Bus Test 
     * (1)  Write default values
     *
     *      Write the memory at all the power of 2 addresses (including 0x0000)
     *      to the default value of CHECKER_BOARD
     *
     * (2)  Perform tests
     *
     *      Select one power of 2 addresses after the other as test_address 
     *      (starting from the highest all the way down to 0x0000) --> 
     *          - Write the memory at test_address to INVERSE_CHECKER_BOARD
     *          - For all the power of 2 addresses including 0x0000
     *              o Read the memory content
     *              o Verify that the read value is either
     *                  (a) equal to CHECKER_BOARD in case a different address 
     *                      than test_addressed has been read or
     *                  (b) equal to INVERSE_CHECKER_BOARD in case the address
     *                      at test_address has been read
     *              o Errors found shall be indicated on LED31--16
     */
    
    /// STUDENTS: To be programmed
		// Write AA
		while (address) {
			address >>= 1;
			*(base_addr + address) = CHECKER_BOARD;
		}
		
		while (test_address) {
			test_address >>= 1;
		
			// write 55 to test
			*(base_addr + test_address) = INVERSE_CHECKER_BOARD;
			
			// check if error occured
			uint16_t read_addr = (uint16_t) 0x01 << NR_OF_ADDRESS_LINES;
		
			while (read_addr) {
				read_addr >>= 1;
		
				uint8_t value = *(base_addr + read_addr);
		
		
				if (test_address == read_addr && value != INVERSE_CHECKER_BOARD){
						show_addr_error(test_address);
						break;
				} else if (test_address != read_addr && value != CHECKER_BOARD){
						show_addr_error(test_address);
						break;
				}
			}
		
			// write AA to TEST
			*(base_addr + test_address) = CHECKER_BOARD;
		
		}

     /// END: To be programmed
    
    /* Device Test 
     * (1) Fill the whole memory with known increment pattern.
     *          Address     Data
     *          0x000       0x01
     *          0x001       0x02
     *          .....       ....
     *          0x0FE       0xFF
     *          0x0FF       0x00
     *          0x100       0x01
     *          .....       ....
     *
     * (2) First test: Read back each location and check pattern.
     *     In case of error, write address with wrong data to 7-segment and
     *     wait for press on button T0.
     *     Bitwise invert  the pattern in each location for the second test
     *
     * (3) Second test: Read back each location and check for new pattern.
     *     In case of error, write address with wrong data to 7-segment and
     *     wait for press on button T0.
     */
    /// STUDENTS: To be programmed
		
		uint32_t adr = 0;
		for(adr = 0;adr < (1<<NR_OF_ADDRESS_LINES); adr++) {
			*(base_addr + adr) = ((adr + 1) % 0x100);
		}
		
		for(adr = 0;adr < (1<<NR_OF_ADDRESS_LINES); adr++) {
			if (*(base_addr + adr) != ((adr + 1) % 0x100)){
				show_device_error(adr);
			}
			uint8_t v = ~(((adr + 1) % 0x100));
			*(base_addr + adr) = v;
		}
		
		for(adr = 0;adr < (1<<NR_OF_ADDRESS_LINES); adr++) {
			
			uint8_t v = ~(((adr + 1) % 0x100));
			
			uint8_t t = *(base_addr + adr);
			if (v != t){
				show_device_error(adr);
			}		
		}

		
    /// END: To be programmed
    
    // Write 'End'
    CT_SEG7->RAW.BYTE.DS0 = 0xA1;
    CT_SEG7->RAW.BYTE.DS1 = 0xAB;
    CT_SEG7->RAW.BYTE.DS2 = 0x86;
    CT_SEG7->RAW.BYTE.DS3 = 0xFF;
    
    while(1){
    }

}