/* E port initialization source file */

#include "port_e_init.h"

void port_e_init()
{
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinMux(PORTSEQINIT, PIN_S1, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTSEQINIT, PIN_S2, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTSEQINIT, PIN_S3, kPORT_MuxAsGpio);
	PORT_SetPinMux(PORTSEQINIT, PIN_S4, kPORT_MuxAsGpio);

	GPIO_PinInit(PORTSEQUENCE, PIN_S1, (gpio_pin_config_t *)kGPIO_DigitalOutput);
	GPIO_PinInit(PORTSEQUENCE, PIN_S2, (gpio_pin_config_t *)kGPIO_DigitalOutput);
	GPIO_PinInit(PORTSEQUENCE, PIN_S3, (gpio_pin_config_t *)kGPIO_DigitalOutput);
	GPIO_PinInit(PORTSEQUENCE, PIN_S4, (gpio_pin_config_t *)kGPIO_DigitalOutput);

	GPIO_ClearPinsOutput(PORTSEQUENCE, PORTSEQMASK);
}

void write_port_e(uint16_t registerData)
{
	WREPIN(PIN_S4, (registerData & (1u << BITE1)));
	WREPIN(PIN_S3, (registerData & (1u << BITE2)));
	WREPIN(PIN_S2, (registerData & (1u << BITE3)));
	WREPIN(PIN_S1, (registerData & (1u << BITE4)));
}


void prendeLed1(){
	WREPIN(PIN_S1, 1);
}

void apagaLed1(){

	WREPIN(PIN_S1, 0);
}
void prendeLed2(){
	WREPIN(PIN_S2, 1);
}

void apagaLed2(){

	WREPIN(PIN_S2, 0);
}
void prendeLed3(){
	WREPIN(PIN_S3, 1);
}

void apagaLed3(){

	WREPIN(PIN_S3, 0);
}
void prendeLed4(){
	WREPIN(PIN_S4, 1);
}

void apagaLed4(){

	WREPIN(PIN_S4, 0);
}
