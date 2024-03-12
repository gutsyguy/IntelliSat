#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_
#include <stdint.h>

#define FLASH_PAGE_SIZE 256
#define FLASH_SECTOR_SIZE 4096

void FLASH_sector_write(uint16_t sector, uint8_t* buffer);
void FLASH_sector_erase(uint16_t sector);
void FLASH_sector_read(uint16_t, uint8_t* buffer);

/**
Lets you write from 1-256 bytes of data
@bytes: The data to write. A buffer with size from 1-256 bytes
@num_bytes: The size of the `bytes` array
@page: The 24-bit address of the page to program. Ideally should be aligned to 256 byte boundary???
*/
void FLASH_page_program(uint8_t* bytes, uint16_t num_bytes, uint32_t page);

/**
Starting at `page`, read `num_bytes` from the flash and copy into `bytes`.
@bytes: Buffer of bytes to copy to
@num_bytes: The number of bytes to read in
@page: Address in flash to start reading from
*/
void FLASH_read_page(uint8_t* bytes, uint32_t num_bytes, uint32_t page);
#endif