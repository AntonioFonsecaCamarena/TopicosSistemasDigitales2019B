/* PIT initialization header file */

#ifndef _PITINIT_H_
#define _PITINIT_H_

#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_pit.h"
#include "board.h"

/* PIT initialization definitions */
#define PIT_IRQ_ID PIT_IRQn
#define PIT_LED_HANDLER PIT_IRQHandler
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

#define PIT_TYPE PIT
#define PIT_MAIN_CHANNEL kPIT_Chnl_0

void pitInit(void);

#endif /* _PITINIT_H_ */
