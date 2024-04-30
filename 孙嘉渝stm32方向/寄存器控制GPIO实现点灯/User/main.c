#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define PERIPH_BASE           ((uint32_t)0x40000000)//片上外设基地址
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)//APB2在片上外设上
#define GPIOA_BASE           (APB2PERIPH_BASE + 0x0800)//GPIOA在APB2上
#define GPIOA_BSRR   		(GPIOA_BASE+0x10) 
#define GPIOA_CRL				(0x40010800)
#define GPIOA_LCKR			  (GPIOA_BASE+0x18)

#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)//AHB在片上外设上
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)//RCC时钟在AHB上
#define RCC_APB2ENR            (RCC_BASE+0x18)

int main(void)
{

	*(unsigned int*) RCC_APB2ENR  =(0x01<<(0+2));//开启时钟
	
	*(unsigned int*) GPIOA_BASE =(0x03);//PA0配置成推挽输出且速度为50mhz

	*(unsigned int*) GPIOA_LCKR	=(0x01<<(0+0));//锁定PA0
	
	

	while (1)
	{
	*(unsigned int*)GPIOA_BSRR =(0x01<<(16+0));//设置GPIOA_PIN0 
												//为低电平，32位到16位为设置低电平，16到0为设置高电平。16代表左移16位
												//0代表第0个引脚
	Delay_ms(500);
	*(unsigned int*)GPIOA_BSRR =(0x01<<(0+0));
	Delay_ms(500);
		
	}
}



