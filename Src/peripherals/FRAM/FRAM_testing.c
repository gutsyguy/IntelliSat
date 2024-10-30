/*
 * FRAM_testing.c
 *
 *  Created on: Sep 3, 2024
 *      Author: green
 */

#include "MB85RS256B.h"
#include "print_scan.h"


void FRAMtest_write_enable() {

	uint8_t SR1 = FRAM_read_SR1();
	printMsg("\n\rSR1 initial: %c", SR1);

	FRAM_write_enable();

	SR1 = FRAM_read_SR1();
	printMsg("\n\rSR1 after WREn: %c", SR1);

}

// FRAM: Basic communications
// Currently, bytes 1~3 are getting the correct 0x04 0x7F 0x05 code. byte 0 seems to get gibberish
// Tried byte 5. Looks like that picks up the 0x09. Need to figure out why byte 0 is wasted currently
// but otherwise, GOOD!
void FRAMtest_read_deviceID() {
	uint8_t MOSI[5];
	FRAM_read_deviceID(MOSI);
	for (uint8_t i = 0; i < 5; ++i) {
		printMsg("\n%u", MOSI[i]);
	}
}

void testFunction_FRAM() {
	FRAMtest_read_deviceID();
}
