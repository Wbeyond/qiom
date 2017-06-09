#ifndef __ADC_H__
#define __ADC_H__

#include "LPC11xx.h"

void ADC_Init (void);
extern uint32_t ADC_Read(uint8_t Channel);
uint32_t ADC_GetData (void);

#endif