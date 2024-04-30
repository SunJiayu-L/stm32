#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Serial.h"
#include <stdio.h>

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	Serial_Init();

	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 4, ID, 2);

	while (1)
	{
		
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
		
		if(Serial_GetRxFlag()==1){
				char str[20]; 
				switch (Serial_RxPacket[0]){
					
				case 01:
				sprintf(str, "%d", AX);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
				
				case 02:
				sprintf(str, "%d", AY);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
					
				case 03:
				sprintf(str, "%d", AZ);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
				
				case 04:
				sprintf(str, "%d", GX);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
				
				case 05:
				sprintf(str, "%d", GY);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
			
				case 06:
				sprintf(str, "%d", GZ);
				OLED_ShowString(1, 5, str);
				Serial_SendString(str);
				break;
			}
		}
		
	}
}




