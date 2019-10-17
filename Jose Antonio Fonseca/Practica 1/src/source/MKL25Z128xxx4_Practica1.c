/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Practica1.c
 * @brief   Application entry point.
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

/* Program include files. */
#include "fsl_pit.h"
#include "pitInit.h"
#include "port_e_init.h"

/* Program definitions and declarations. */
#define RING_CTR	  0x0008
#define JOHNSON_CTR   0x000F
#define SHIFTER       0x0078

#define CYCLECOUNT 2u

/* Global variables */
static volatile uint16_t sequenceState;
static volatile bool pitIsrFlag = false;

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */

	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* Force the counter to be placed into memory. */
    pitInit();
    port_e_init();

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
    	changeSeqState(RING_CTR, 4u, CYCLECOUNT);
    	changeSeqState(JOHNSON_CTR, 4u, CYCLECOUNT);
    	changeSeqState(SHIFTER, 7u, CYCLECOUNT);
    }
    return 0 ;
}

void PIT_LED_HANDLER(void)
{
	/* Indicator of 1 second time lapse */
	LED_RED_TOGGLE();
    /* Polling delay flag */
	pitIsrFlag = true;
	/* Clear interrupt flag.*/
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
}

void changeSeqState(uint16_t seqBits, unsigned char steps, unsigned char cycles)
{
	for(int i = 0; i < cycles; i++)
	{
		for (int j = 0; j <= steps; j++)
		{
			/* Shifting action */
			sequenceState = (seqBits >> (steps - j));
			/* Start PIT */
			PIT_StartTimer(PIT_TYPE, PIT_MAIN_CHANNEL);
			/* Poling cycle that waits PIT interruption */
			while(!pitIsrFlag)
			{
				__asm volatile ("nop");
			}
			/* Stops Timer */
			PIT_StopTimer(PIT_TYPE, PIT_MAIN_CHANNEL);
			/* Set port output */
			write_port_e(sequenceState);
			pitIsrFlag = false;
		}
	}
}
