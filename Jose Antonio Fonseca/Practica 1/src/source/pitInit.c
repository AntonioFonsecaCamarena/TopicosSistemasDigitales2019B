/* Initialization of PIT */

#include "pitInit.h"

void pitInit(void)
{
	/* Structure of initialize PIT */
	pit_config_t pitConfig;

	/* Initialize PIT with default values */
	PIT_GetDefaultConfig(&pitConfig);

	/* Initialize PIT module */
	PIT_Init(PIT, &pitConfig);

	/* Set timer period for channel 0 */
	PIT_SetTimerPeriod(PIT, PIT_MAIN_CHANNEL, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));

	PIT_EnableInterrupts(PIT, PIT_MAIN_CHANNEL, kPIT_TimerInterruptEnable);

	/* Enable at the Nested Vectored Interrupt Controller */
	EnableIRQ(PIT_IRQ_ID);
}
