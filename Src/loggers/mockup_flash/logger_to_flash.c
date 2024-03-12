#include "logger_to_flash.h"
#include "flash_driver.h"

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

#define MOCK_EVENT_LOG_SECTORS 2
#define MOCK_EXP_LOG_SECTORS 2

#define EVENT_LOG_START 1

#define EXP_LOG_1_START EVENT_LOG_START + MOCK_EVENT_LOG_SECTORS
#define EXP_LOG_1_END EXP_LOG_1_START + MOCK_EXP_LOG_SECTORS

#define EXP_LOG_2_START EXP_LOG_1_START + MOCK_EXP_LOG_SECTORS
#define EXP_LOG_2_END EXP_LOG_2_START + MOCK_EXP_LOG_SECTORS

const struct FlashHeader default_flash_header = {
    .events_header = {
        .start_sector_num = EVENT_LOG_START,
        .end_sector_num = EVENT_LOG_START + MOCK_EVENT_LOG_SECTORS,
        .tail = EVENT_LOG_START,
        .oldest_sector_num = EVENT_LOG_START
    },
    .exp1_header = {
        .start_sector_num = EXP_LOG_1_START,
        .end_sector_num = EXP_LOG_1_END,
        .tail = EXP_LOG_1_START,
        .oldest_sector_num = EXP_LOG_1_START
    },
    .exp2_header = {
        .start_sector_num = EXP_LOG_2_START,
        .end_sector_num = EXP_LOG_2_END,
        .tail = EXP_LOG_2_START,
        .oldest_sector_num = EXP_LOG_2_START
    },
    .current_exp_num = 1
};


// A global struct representing our flash header
struct FlashHeader FLASH_header;

void FLASH_init_header() {
    FLASH_page_program((uint8_t*) &default_flash_header, 256, 0);
    memcpy(&FLASH_header, &default_flash_header, sizeof(default_flash_header));
}

void FLASH_fetch_header() {
    // memcpy(&flash_header, mock_flash_buff, sizeof(struct FlashHeader));
    FLASH_read_page((uint8_t*) &FLASH_header, 256, 0);
}

void FLASH_update_header() {
    // memcpy(mock_flash_buff, &flash_header, sizeof(struct FlashHeader));
    FLASH_page_program((uint8_t*) &FLASH_header, 256, 0);
}

static uint32_t advance_addr(
    const uint32_t start,
    const uint32_t end,
    const uint32_t addr_to_advance,
    const uint32_t increment
) {
    uint32_t offset_from_start = addr_to_advance - start;
    return start + (offset_from_start + increment) % (end - start);
}

static void FLASH_advance_oldest_event_block() {
    FLASH_header.events_header.oldest_sector_num = advance_addr(
        FLASH_header.events_header.start_sector_num,
        FLASH_header.events_header.end_sector_num,
        FLASH_header.events_header.oldest_sector_num,
        1
    );
}

static void LOGGER_advance_oldest_exp_block(struct ExperimentLogHeader * exp_log_header) {
    exp_log_header->oldest_sector_num = advance_addr(
        exp_log_header->start_sector_num,
        exp_log_header->end_sector_num,
        exp_log_header->oldest_sector_num,
        1
    );
}

enum LogType LOGGER_get_oldest_page(uint8_t sector_buff[FLASH_SECTOR_SIZE]) {
    static enum LogType oldest_block_type = EVENT;
    uint32_t oldest_sector_num;
    switch(oldest_block_type) {
        case EVENT: {
            oldest_sector_num = FLASH_header.events_header.oldest_sector_num;
            FLASH_advance_oldest_event_block();
        } break;

        case EXP1: {
            oldest_sector_num = FLASH_header.exp1_header.oldest_sector_num;
            FLASH_advance_oldest_exp_block(&FLASH_header.exp1_header);

        } break;

        case EXP2: {
            oldest_sector_num = FLASH_header.exp2_header.oldest_sector_num;
            FLASH_advance_oldest_exp_block(&FLASH_header.exp2_header);
        } break;
    }

    FLASH_update_header();
    
    FLASH_sector_read(oldest_sector_num, sector_buff);

    enum LogType block_type = oldest_block_type;

    oldest_block_type++;
    if(oldest_block_type > EXP2) oldest_block_type = EVENT;

    return block_type;
}

/**
If the local buffer is longer than remaining space in mock flash buffer, this will write too much.

Potential solutions:
    1. Make the size of block a multiple of local buffer size, and only transfer when local buffer is full
    2. Check if size of block being transfered > remaining space in buffer and wrap around to start.
*/
uint8_t FLASH_push_event_logs_to_flash() {
    // memcpy(mock_flash_buff + flash_header.events_header.tail, local_event_logs->logs, sizeof(local_event_logs->logs));
    FLASH_header.events_header.tail = advance_addr(
        FLASH_header.events_header.start_sector_num,
        FLASH_header.events_header.end_sector_num,
        FLASH_header.events_header.tail,
        1
    );

    return 0;
}

uint8_t FLASH_push_exp_logs_to_flash(struct LocalExpLogs * local_exp_logs, struct ExperimentLogHeader * current_exp_header) {
    FLASH_page_program((uint8_t*) local_exp_logs->logs, 256, current_exp_header->tail);
    current_exp_header->tail = advance_addr(
        current_exp_header->start_sector_num,
        current_exp_header->end_sector_num,
        current_exp_header->tail,
        1
    ); 

    return 0;
}
