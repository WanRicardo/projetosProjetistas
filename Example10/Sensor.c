/*
 * Sensor.c
 *
 *  Created on: 12 de set de 2016
 *      Author: Wanderson
 */

#include "Sensor.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_gpio.h"
#include "light.h"

static void Sensor_initI2c(void);

typedef struct light_sensor {

	int valorLuz;
	int I2C_Interrupt_Done_Flag;
}lightSensor;

lightSensor ClassHandle;

void Sensor_new(void) {

	Sensor_initI2c();
	ClassHandle.I2C_Interrupt_Done_Flag = 0;
	ClassHandle.valorLuz = 0;


	light_init();
	light_enable();
	light_setRange(LIGHT_RANGE_4000);
}

int Sensor_leitura(void) {

	ClassHandle.valorLuz = light_read();
//	if (ClassHandle.I2C_Interrupt_Done_Flag == 1) {
//		ClassHandle.I2C_Interrupt_Done_Flag = 0;
//		NVIC_EnableIRQ(TIMER0_IRQn);
//	}
	return ClassHandle.valorLuz;
}

static void Sensor_initI2c(void)
{
	PINSEL_CFG_Type PinCfg;

	/* Initialize I2C2 pin connect */
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);

	// Initialize I2C peripheral
	I2C_Init(LPC_I2C2, 100000);

	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C2, ENABLE);
}

void TIMER0_IRQHandler(void)
{
	//desabilita a interrupção timer0
	NVIC_DisableIRQ(TIMER0_IRQn);
	ClassHandle.I2C_Interrupt_Done_Flag = 1;
}
