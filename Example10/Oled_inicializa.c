/*
 * OledClasse.c
 *
 *  Created on: 12 de set de 2016
 *      Author: Wanderson
 */

#include "oled.h"

#include "Oled_inicializa.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
//#include "lpc17xx_i2c.h"
#include "lpc17xx_ssp.h"
//#include "lpc17xx_adc.h"
#include "lpc17xx_timer.h"
#include "stdint.h"

static void init_ssp(void);

typedef struct tela_oled {

	uint8_t buf[10];
}telaOled;

telaOled ClassHandle;

void Oled_new(void) {

	init_ssp();
	oled_init();

}


static void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base)
{
    static const char* pAscii = "0123456789abcdefghijklmnopqrstuvwxyz";
    int pos = 0;
    int tmpValue = value;

    // the buffer must not be null and at least have a length of 2 to handle one
    // digit and null-terminator
    if (pBuf == NULL || len < 2)
    {
        return;
    }

    // a valid base cannot be less than 2 or larger than 36
    // a base value of 2 means binary representation. A value of 1 would mean only zeros
    // a base larger than 36 can only be used if a larger alphabet were used.
    if (base < 2 || base > 36)
    {
        return;
    }

    // negative value
    if (value < 0)
    {
        tmpValue = -tmpValue;
        value    = -value;
        pBuf[pos++] = '-';
    }

    // calculate the required length of the buffer
    do {
        pos++;
        tmpValue /= base;
    } while(tmpValue > 0);


    if (pos > len)
    {
        // the len parameter is invalid.
        return;
    }

    pBuf[pos] = '\0';

    do {
        pBuf[--pos] = pAscii[value % base];
        value /= base;
    } while(value > 0);

    return;

}

void imprimeOled(uint32_t lReceivedValue) {

	oled_clearScreen(OLED_COLOR_WHITE);
	oled_putString(1,1,  (uint8_t*)"Luz : ", OLED_COLOR_BLACK, OLED_COLOR_WHITE);
	oled_fillRect((1+9*6),9, 80, 16, OLED_COLOR_WHITE);
	intToString(lReceivedValue, ClassHandle.buf, 10, 10);
	oled_putString((1+9*6),1, ClassHandle.buf, OLED_COLOR_BLACK, OLED_COLOR_WHITE);

//	for (int i=0; i<= sizeof(ClassHandle.buf)/sizeof(ClassHandle.buf[0]); i++) {
//
//		ClassHandle.buf[i] = 0;
//	}
}

//static void Sensor_initI2c(void);
//
//int Sensor_leitura(void) {
//
//	ClassHandle.valorLuz = light_read();
////	if (ClassHandle.I2C_Interrupt_Done_Flag == 1) {
////		ClassHandle.I2C_Interrupt_Done_Flag = 0;
////		NVIC_EnableIRQ(TIMER0_IRQn);
////	}
//	return ClassHandle.valorLuz;
//}
//
//static void Sensor_initI2c(void)
//{
//	PINSEL_CFG_Type PinCfg;
//
//	/* Initialize I2C2 pin connect */
//	PinCfg.Funcnum = 2;
//	PinCfg.Pinnum = 10;
//	PinCfg.Portnum = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	PinCfg.Pinnum = 11;
//	PINSEL_ConfigPin(&PinCfg);
//
//	// Initialize I2C peripheral
//	I2C_Init(LPC_I2C2, 100000);
//
//	/* Enable I2C1 operation */
//	I2C_Cmd(LPC_I2C2, ENABLE);
//}
//
//void TIMER0_IRQHandler(void)
//{
//	//desabilita a interrupção timer0
//	NVIC_DisableIRQ(TIMER0_IRQn);
//	ClassHandle.I2C_Interrupt_Done_Flag = 1;
//}

static void init_ssp(void)
{
	SSP_CFG_Type SSP_ConfigStruct;
	PINSEL_CFG_Type PinCfg;

	/*
	 * Initialize SPI pin connect
	 * P0.7 - SCK;
	 * P0.8 - MISO
	 * P0.9 - MOSI
	 * P2.2 - SSEL - used as GPIO
	 */
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 7;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Funcnum = 0;
	PinCfg.Portnum = 2;
	PinCfg.Pinnum = 2;
	PINSEL_ConfigPin(&PinCfg);

	SSP_ConfigStructInit(&SSP_ConfigStruct);

	// Initialize SSP peripheral with parameter given in structure above
	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);

	// Enable SSP peripheral
	SSP_Cmd(LPC_SSP1, ENABLE);

}
