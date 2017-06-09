#include <stdio.h>
#include <string.h>
#include "LPC11xx.h"
#include "Display.h"
#include "ADC.h"
#include "KEY.h"
#include "Temp.h"
#include "UART.h"

extern volatile uint8_t UART_Flag;
extern uint8_t chance;
char AD_Data_Buff[20];



int main (void)
{
   float temp;
	uint32_t i;
	UART_IRQ_Init(9600);
	LED_Init();
	ADC_Init();
	KEY_Init();
	while(1)
	{
  temp= tem(ADC_GetData());
	if(chance==0) temp=temp*1.8+32;
	for(i=0;i<1000;i++)
		LED_Display(temp);
	if(UART_Flag==1){
		if(chance==1)
			sprintf (AD_Data_Buff,"TEMP:%4.2f  摄氏度\r\n",temp);  
		else 
			sprintf (AD_Data_Buff,"TEMP:%4.2f  华氏度\r\n",temp);
		UART_SendStr(AD_Data_Buff);  //数据发送到串口进行显示
		UART_Flag=0;
	}
	}
}
