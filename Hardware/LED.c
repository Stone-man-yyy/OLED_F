#include "stm32f10x.h"                  // Device header

#define RCC_GPIO_CLK	RCC_APB2Periph_GPIOC
#define Group	GPIOC
#define	Pin		GPIO_Pin_13

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_CLK,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(Group,&GPIO_InitStruct);
	GPIO_WriteBit(Group,Pin,Bit_RESET);
}

void LED_ON(void)
{
	GPIO_WriteBit(Group,Pin,Bit_RESET);
}

void LED_OFF(void)
{
	GPIO_WriteBit(Group,Pin,Bit_SET);
}

void LED_Turn(void)
{
	if(GPIO_ReadOutputDataBit(Group,Pin) == 1)
	{
		GPIO_WriteBit(Group,Pin,Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(Group,Pin,Bit_SET);
	}
}

