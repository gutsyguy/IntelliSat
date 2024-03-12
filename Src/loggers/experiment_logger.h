#ifndef LOGGERS_EXPERIMENT_LOGGER_H_
#define LOGGERS_EXPERIMENT_LOGGER_H_

#include "mockup_flash/flash_driver.h"

#include <stdint.h>
#include <stdio.h>
#include <assert.h>


// 128 bits == 16 bytes
#pragma pack(push,1)
struct ExperimentLog
{
    uint16_t rtc_time: 12;
    int16_t gyro_x: 16, gyro_y: 16, gyro_z: 16;
    int16_t dgyro_x: 16, dgyro_y: 16, dgyro_z: 16;
    uint32_t  extra: 20;
};
#pragma pack(pop)

#define LOCAL_EXP_LOG_COUNT FLASH_SECTOR_SIZE/16

struct LocalExpLogs {
    unsigned int num_logs;
    unsigned int tail;
    struct ExperimentLog logs[LOCAL_EXP_LOG_COUNT];
};

void LOGGER_start_exp_logging();

void LOGGER_stop_exp_logging(int experiment_status);

uint8_t LOGGER_log_exp(
    unsigned int rtc_time,     // Date+Hr+Min+Sec
    int16_t  gyro_x,
    int16_t  gyro_y,
    int16_t  gyro_z,
    int16_t  dgyro_x,
    int16_t  dgyro_y,
    int16_t  dgyro_z,
    unsigned int parity
);

#endif