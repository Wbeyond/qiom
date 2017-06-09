#ifndef _COMMON_H
#define _COMMON_H

#include <lpc11xx.h>


#define G0DIR	 LPC_GPIO0->DIR   //G0方向配置寄存器
#define G1DIR	 LPC_GPIO1->DIR	  //G1方向配置寄存器
#define G2DIR	 LPC_GPIO2->DIR	  //G2方向配置寄存器
#define G3DIR	 LPC_GPIO3->DIR	  //G3方向配置寄存器
#define G0DATA LPC_GPIO0->DATA  //G0数据寄存器 
#define G1DATA LPC_GPIO1->DATA  //G1数据寄存器 
#define G2DATA LPC_GPIO2->DATA	//G2数据寄存器 
#define G3DATA LPC_GPIO3->DATA	//G3数据寄存器 

#define ENGPIO()  	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6)	//使能GPIO时钟
#define ENIOCON() 	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16)	//使能IOCON时钟
#define UNENIOCON() LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16)	//禁能IOCON时钟

extern void DelayMs(uint16_t t); //毫秒级延时函数

#endif