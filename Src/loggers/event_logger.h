#ifndef LOGGERS_EVENT_LOGGER_H_
#define LOGGERS_EVENT_LOGGER_H_

// #includes here... FLASH, Scheduler, RTC
#include <stdint.h>
/*
 * Each log is a 64 bit word with the following breakdown:
 *      - RTC Date-Time      - 22 bits (Date,Hr,Min,Sec in binary)
 *      - Current Mode       -  4 bits
 *      - Action-Detail Pair - 27 bits (Action-3, Details - 24)
 *      - Extra              - 11 bits (potential redundancy)
 *
 * Details on Action-Detail pairs can be found in the Intellisat Loggers document
 * There is 1 event buffer, which can hold [INSERT NUMBER HERE] logs.
 */

// 8 Bytes Each
struct __attribute__((packed)) EventLog
{
    unsigned int rtc_datetime: 22;
    unsigned int current_mode: 4;
    unsigned int action: 3;
    unsigned int details: 24;
    unsigned int extra: 11;
};

#define LOCAL_EVENT_LOG_COUNT 32

struct LocalEventLogs {
    uint32_t num_logs;
    uint32_t tail;
    struct EventLog logs[LOCAL_EVENT_LOG_COUNT];
};


/**
 * Responsible for handling an event overflow
 * @returns None
 */
void LOGGER_handle_event_overflow();


// NOT PROPERLY DEFINED YET.. They should take in Details as inputs
void LOGGER_log_system_oddity();
void LOGGER_log_intercom();
void LOGGER_log_mode_change();
void LOGGER_log_event_overflow();


uint8_t LOGGER_add_event_log( uint64_t event_log );


uint8_t LOGGER_build_and_add_event_log(
    unsigned int rtc_datetime,     // Date+Hr+Min+Sec
    unsigned int current_mode,
    unsigned int action,
    unsigned int details,
    unsigned int extra
);

#endif