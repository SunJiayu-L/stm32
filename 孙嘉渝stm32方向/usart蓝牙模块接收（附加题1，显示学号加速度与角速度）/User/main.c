#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Serial.h"


int16_t AX, AY, AZ, GX, GY, GZ;
int main(void)
{
	OLED_Init();
	MPU6050_Init();
	Serial_Init();

	
	while (1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		if(Serial_GetRxFlag()==1){
			if(Serial_RxPacket[0]==01){
				OLED_Clear();
				OLED_ShowString(1,1,"1.Student");
				OLED_ShowString(2,1,"2023091602024");
			
		}else if (Serial_RxPacket[0]==02){
			OLED_Clear();
			OLED_ShowString(1,1,"2:ACC");
			OLED_ShowSignedNum(2,1,AX,5);
			OLED_ShowSignedNum(3,1,AY,5);
			OLED_ShowSignedNum(4,1,AZ,5);
			
		}else if(Serial_RxPacket[0]==03){
			OLED_Clear();
			OLED_ShowString(1,1,"3:GYRO");
			OLED_ShowSignedNum(2,1,GX,5);
			OLED_ShowSignedNum(3,1,GY,5);
			OLED_ShowSignedNum(4,1,GZ,5);
		
			}
		}
	}
}
