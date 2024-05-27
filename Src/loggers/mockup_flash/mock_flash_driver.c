#include "flash_driver.h"

#include <string.h>

#define MOCK_FLASH_BUFF_SIZE 4096
static uint8_t mock_flash_buff[MOCK_FLASH_BUFF_SIZE];

void FLASH_sector_write(uint16_t sector, uint8_t* buffer) {
    memcpy(mock_flash_buff + (sector * FLASH_SECTOR_SIZE), buffer, FLASH_SECTOR_SIZE);
}

void FLASH_sector_erase(uint16_t sector) {
    memset(mock_flash_buff + (sector * FLASH_SECTOR_SIZE), (uint8_t) 0, FLASH_SECTOR_SIZE);
}

void FLASH_sector_read(uint16_t sector, uint8_t* buffer) {
    memcpy(buffer, mock_flash_buff + (sector * FLASH_SECTOR_SIZE), FLASH_SECTOR_SIZE);
}


// void FLASH_clear_page();

void FLASH_page_program(uint8_t* bytes, uint16_t num_bytes, uint32_t page) {
    int page_start_addr = page * 256;
    // assert(offset_from_page_start == 0);
    memcpy(mock_flash_buff + page_start_addr, bytes, num_bytes);
}

void FLASH_read_page(uint8_t* bytes, uint32_t num_bytes, uint32_t page) {
    memcpy(bytes, mock_flash_buff + (page * 256), num_bytes);
}