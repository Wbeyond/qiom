#include "LPC11xx.h"
#include "ADC.h"

uint32_t ADCBuf , ADCFlag;
uint8_t Buff[20];                              

/*************************************************************************
*��������  ADC_Init
*�������ܣ���ʼ��ADC
**************************************************************************/

void ADC_Init (void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);               //ʹ��IOCONʱ��
	LPC_IOCON->R_PIO1_0 &=~0xbf;                        //����PI01_OΪģ������ģʽ
	LPC_IOCON->R_PIO1_0 |= 0x02;                        //PIO1_0ģ������ͨ��0
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);               //����IOCONʱ��
	LPC_SYSCON->PDRUNCFG &=~(0x01<<4);                  //ADCģ���ϵ�
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);	              //ʹ��ADCģ��ʱ��  
	LPC_ADC->CR = (0x01<<1)|                          //SEL=1��ѡ��ADC0
	              ((SystemCoreClock/1000000-1)<<8)|   // ת��ʱ��1MHz
               	(0<<16)|                            //BURST=1��ʹ��Burstģʽ
               	(0<<17)|                            //ʹ��11clocksת��
	              (0<<24)|                            //ADCת��ֹͣ
	              (0<<27);	                          //ֱ������ADCת������λ��Ч
}

/*******************************************
* ��������ADC_Read
* �������ܣ���ȡ��ѹֵ                   
********************************************/
uint32_t ADC_Read(uint8_t Channel)
{
	uint32_t adc_value=0;
	uint32_t ADCBuf=0;
	uint8_t i;
	
	for(i=0;i<50;i++)
	{
		adc_value = ((LPC_ADC->DR[Channel]>>6)&0x3FF);		   //��ȡͨ����ֵ�����λ�ڵ�6λ��ʼ����ʮλ
		ADCBuf += adc_value;
	}
	adc_value = ADCBuf / 50;
	adc_value = (adc_value*3300)/1024;                     // ת��Ϊ�����ĵ�ѹֵ
	
	return adc_value; 
}

/*************************************************************************
*��������  ADC_GetData
*�������ܣ�ADC ȡֵ��ʮ��ƽ����
**************************************************************************/
uint32_t ADC_GetData (void)
{
	uint32_t ADCDat=0 , ADCBuf=0;
	uint8_t i=0;

	for(i=0;i<10;i++)
	{ 
		LPC_ADC->CR |= (1<<24);                        //����ת��
		while((LPC_ADC->DR[1]&0x80000000) == 0);       //��ȡDR1��Done
		LPC_ADC->CR |= (1<<24);                        //��һ��ת���Ľ���������ٴ�ת��
		while((LPC_ADC->DR[1]&0x80000000) == 0);       //��ȡDR1��Done
		ADCBuf = LPC_ADC->DR[1];                       //��ȡ����Ĵ���
		ADCBuf = (ADCBuf>>6)&0x3ff;                    //�ӵ�6λ��ʼ��ȡ10λ����
		ADCDat += ADCBuf;                              //�����ۼ�
	}
	ADCDat = ADCDat / 10;                            //����ʮ�ν����˲�����
	ADCDat = (ADCDat*3300)/1024;                     //������תģ����
	
	return ADCDat;
}

/*************************************************************************
*��������  ADC_IRQHandler
*�������ܣ�ADC�жϷ�����
**************************************************************************/
void ADC_IRQHandler (void)
{
	ADCBuf = LPC_ADC->DR[1];
	ADCBuf = (ADCBuf>>6)&0x3ff;
	ADCFlag = 1;
}

