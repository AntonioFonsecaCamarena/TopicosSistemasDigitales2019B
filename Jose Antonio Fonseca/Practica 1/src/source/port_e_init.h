/* E Port initialization file */

#include "stdint.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "MKL25Z4.h"
#include "pin_mux.h"

/* GPIO pin definitions */
#define PORTSEQUENCE GPIOE
#define PORTSEQINIT  PORTE

#define PIN_S1							 5u
#define PIN_S2                           4u
#define PIN_S3							 3u
#define PIN_S4                           2u

#define BITE1                            0u
#define BITE2                            1u
#define BITE3                            2u
#define BITE4                            3u

#define PORT_SEQ_OFFSET 				 2u
#define PORTSEQMASK (uint32_t)((0x00000000)|(1u << PIN_S1)|(1u << PIN_S2)|(1u << PIN_S3)|(1u << PIN_S4))

#define WREPIN(pin, data) GPIO_WritePinOutput(PORTSEQUENCE, pin, data)

/* Function prototypes */
void port_e_init(void);
void write_port_e(uint16_t registerData);
