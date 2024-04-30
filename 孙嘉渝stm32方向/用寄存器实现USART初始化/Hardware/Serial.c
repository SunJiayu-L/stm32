#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

#define PERIPH_BASE           ((uint32_t)0x40000000)//片上外设基地址
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)//APB2在片上外设上
#define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800)//GPIOA在APB2上//同时也是GPIOA_CRL的地址
#define GPIOA_CRH			  (GPIOA_BASE+0x04)
#define GPIOA_LCKR			  (GPIOA_BASE+0x18)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)
#define USART1_BASE_BRR             (USART1_BASE+0x08)
#define USART1_BASE_CR1           (USART1_BASE+0x0C)
#define USART1_BASE_CR2           (USART1_BASE+0x10)

//时钟
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)//AHB在片上外设上
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)//RCC时钟在AHB上
#define RCC_APB2ENR            (RCC_BASE+0x18)


uint32_t USART_CalBote (uint32_t Hz,uint32_t bote){
	float usartdiv=0;
	uint16_t mantissa=0;//装入波特率寄存器的整数部分
	uint16_t fraction=0;//装入波特率寄存器的小数部分
	usartdiv=(float)(Hz*1000000)/(bote*16);
	mantissa=usartdiv;
	fraction=(usartdiv-mantissa)*16;
	mantissa<<=4;
	mantissa+=fraction;
	return mantissa;
}

void Serial_Init(void)
{
	uint32_t brr= USART_CalBote(72,9600);
	*(unsigned int*) RCC_APB2ENR  =(0x01<<(0+14))|(0x01<<(0+2));//开启时钟(USART与GPIOA)
	
	*(unsigned int*) GPIOA_CRH  =(0x01<<(0+11))|(0xB0);//PA9配置成复用推挽输出且速度为50mhz;PA10为上拉输入
	*(unsigned int*) GPIOA_LCKR	=(0x01<<(0+10))|(0x01<<(0+9));//锁定PA10 PA9

	*(unsigned int*)  USART1_BASE_CR1  = (0x01<<(0+13))|(0x01<<(0+3));
	*(unsigned int*)  USART1_BASE_CR2 = 0x00;
	*(unsigned int*)  USART1_BASE_BRR = brr;
}

void Serial_SendByte(uint8_t Byte)//发送一个字节
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);
		Serial_RxFlag = 1;
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}

