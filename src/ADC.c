#include "LPC11xx.h"
#include "ADC.h"

uint32_t ADCBuf , ADCFlag;
uint8_t Buff[20];                              

/*************************************************************************
*函数名：  ADC_Init
*函数功能：初始化ADC
**************************************************************************/

void ADC_Init (void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);               //使能IOCON时钟
	LPC_IOCON->R_PIO1_0 &=~0xbf;                        //配置PI01_O为模拟输入模式
	LPC_IOCON->R_PIO1_0 |= 0x02;                        //PIO1_0模拟输入通道0
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);               //禁能IOCON时钟
	LPC_SYSCON->PDRUNCFG &=~(0x01<<4);                  //ADC模块上电
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	              //使能ADC模块时钟  
	LPC_ADC->CR = (0x01<<1)|                          //SEL=1，选择ADC0
	              ((SystemCoreClock/1000000-1)<<8)|   // 转换时钟1MHz
               	(0<<16)|                            //BURST=1，使用Burst模式
               	(0<<17)|                            //使用11clocks转换
	              (0<<24)|                            //ADC转换停止
	              (0<<27);	                          //直接启动ADC转换，此位无效
}

/*******************************************
* 函数名：ADC_Read
* 函数功能：读取电压值                   
********************************************/
uint32_t ADC_Read(uint8_t Channel)
{
	uint32_t adc_value=0;
	uint32_t ADCBuf=0;
	uint8_t i;
	
	for(i=0;i<50;i++)
	{
		adc_value = ((LPC_ADC->DR[Channel]>>6)&0x3FF);		   //读取通道的值，结果位于第6位开始，共十位
		ADCBuf += adc_value;
	}
	adc_value = ADCBuf / 50;
	adc_value = (adc_value*3300)/1024;                     // 转换为真正的电压值
	
	return adc_value; 
}

/*************************************************************************
*函数名：  ADC_GetData
*函数功能：ADC 取值（十次平均）
**************************************************************************/
uint32_t ADC_GetData (void)
{
	uint32_t ADCDat=0 , ADCBuf=0;
	uint8_t i=0;

	for(i=0;i<10;i++)
	{ 
		LPC_ADC->CR |= (1<<24);                        //立即转换
		while((LPC_ADC->DR[1]&0x80000000) == 0);       //读取DR1的Done
		LPC_ADC->CR |= (1<<24);                        //第一次转换的结果丢弃，再次转换
		while((LPC_ADC->DR[1]&0x80000000) == 0);       //读取DR1的Done
		ADCBuf = LPC_ADC->DR[1];                       //读取结果寄存器
		ADCBuf = (ADCBuf>>6)&0x3ff;                    //从第6位开始，取10位数据
		ADCDat += ADCBuf;                              //数据累加
	}
	ADCDat = ADCDat / 10;                            //采样十次进行滤波处理
	ADCDat = (ADCDat*3300)/1024;                     //数字量转模拟量
	
	return ADCDat;
}

/*************************************************************************
*函数名：  ADC_IRQHandler
*函数功能：ADC中断服务函数
**************************************************************************/
void ADC_IRQHandler (void)
{
	ADCBuf = LPC_ADC->DR[1];
	ADCBuf = (ADCBuf>>6)&0x3ff;
	ADCFlag = 1;
}

