#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"


uint8_t RxData;

int main(){
	OLED_Init();
    Serial_Init();
	Key_Init();
	
	uint8_t KeyNum=Key_GetNum();

    while(1)
    {
	uint8_t KeyNum=Key_GetNum();
    if(KeyNum==1){
	OLED_ShowString(1, 3, "HelloWorld!");
	Serial_SendString("2023091602024");
	Serial_SendString("sjy");
		}
    }
}