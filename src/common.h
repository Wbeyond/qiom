#ifndef _COMMON_H
#define _COMMON_H

#include <lpc11xx.h>


#define G0DIR	 LPC_GPIO0->DIR   //G0�������üĴ���
#define G1DIR	 LPC_GPIO1->DIR	  //G1�������üĴ���
#define G2DIR	 LPC_GPIO2->DIR	  //G2�������üĴ���
#define G3DIR	 LPC_GPIO3->DIR	  //G3�������üĴ���
#define G0DATA LPC_GPIO0->DATA  //G0���ݼĴ��� 
#define G1DATA LPC_GPIO1->DATA  //G1���ݼĴ��� 
#define G2DATA LPC_GPIO2->DATA	//G2���ݼĴ��� 
#define G3DATA LPC_GPIO3->DATA	//G3���ݼĴ��� 

#define ENGPIO()  	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6)	//ʹ��GPIOʱ��
#define ENIOCON() 	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16)	//ʹ��IOCONʱ��
#define UNENIOCON() LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16)	//����IOCONʱ��

extern void DelayMs(uint16_t t); //���뼶��ʱ����

#endif