#include "LPC11xx.h"
#include "Display.h"

uint8_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

void LED_Delay (void)
{
	uint32_t time=100;
	while(time--);
}

void LED_Init (void)
{
	LPC_GPIO2->DIR = 0xfff;
}

void LED_Display (uint16_t Num)
{
	if(Num<10)
	{
		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else if(Num<100)
	{
		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else if(Num<1000)
	{
		LPC_GPIO2->DATA = 0xd00 + table[Num%1000/100];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;
	}
	else
	{
		LPC_GPIO2->DATA = 0xe00 + table[Num/1000];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xd00 + table[Num%1000/100];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0xb00 + table[Num%1000%100/10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;

		LPC_GPIO2->DATA = 0x700 + table[Num%10];
		LED_Delay();
		LPC_GPIO2->DATA = 0xfff;
	}

}

