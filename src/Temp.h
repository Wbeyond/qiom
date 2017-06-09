#ifndef __Temp_H
#define __Temp_H


#include "LPC11xx.h"	//LPC11xx?????
#include <stdio.h>
#include <string.h>
extern uint32_t  ulADCBuf;
extern uint32_t  ADCFlag;
extern uint32_t  ulADCData; 
extern uint32_t res_value;  //电阻
extern uint32_t temp;  //	温度  摄氏度
extern uint32_t tempF; // 华氏度

extern void ADC_Init( void );
extern void ADC_IRQHandler(void);
extern uint32_t ADC_To_Res(uint32_t adc_value);
extern uint32_t Res_To_Temp(uint32_t res_value);
extern uint32_t TempC_To_TempF(uint32_t temp);

#endif
