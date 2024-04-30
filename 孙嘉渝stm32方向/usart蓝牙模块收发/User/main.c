#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Serial.h"



int main(void)
{
	OLED_Init();
	MPU6050_Init();
	Serial_Init();
    uint8_t arr[4]={0x41,0x42,0x43,0x44};
	
	while (1)
	{
		
		if(Serial_GetRxFlag()==1){
		Serial_SendByte(Serial_RxPacket[0]);//发送 FF x  FE 返回x（x可以100以内的两位数）

			//Serial_SendArray(arr, 4);发送FF X FE ,返回数组；
			//Serial_SendString("hello");发送FF X FE ,返回hello，但返回的是HEX类型，我的手机调试不支持文本模式
		

		}
	}
}
