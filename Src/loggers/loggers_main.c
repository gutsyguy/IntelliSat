#include "experiment_logger.h"
#include "logger_to_flash.h"
#include "../tools/print_scan.h"
// #include "../globals.h"
//#define printMsg(x) printf(x)

#include <stdio.h>
int loggers_main() {
    printf("testing 0.5 loggers\r\n");
//    LOGGER_init_header();

    LOGGER_start_exp_logging();

    for (int i = 0; i < 128; ++i) {
        LOGGER_log_exp(
            i,
            1,
            2, 3, 4,
             5,  6,  7,
            8,
            9,
            10,
            11,
            12,
            13,
            14
        );
        // nop(100000);
    }

    printf("Completed Logging\r\n");

//    for(int i = 0; i < 128; ++i) {
//        uint8_t sector_buff[4096];
//        printf("Doing read #%d\n", i);
//        LOGGER_get_oldest_sector(sector_buff);
//    }

    printf("Completed reading\r\n");
}

//int main(){
//    loggers_main();
//}
