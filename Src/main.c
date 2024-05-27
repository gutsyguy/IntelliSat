#include "platform_init.h"
#include "tools/print_scan.h"
#include "loggers/experiment_logger.h"

/*
 * For now this won't be implemented on the main branch
 * Therefore, the main branch cannot be built.
 * Each development / feature branch has it's own implementation
 * which is used for testing specific features.
 */
void branch_main() {
	printMsg("Starting Experiment Logging");
	LOGGER_exp_logger_init();
	LOGGER_start_exp_logging();

	delay_ms(30000);

	LOGGER_stop_exp_logging(1);
	printMsg("COMPLETED");
}

int main() {
	init_platform();
	branch_main();
}
