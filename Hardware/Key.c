#include "stm32f10x.h"                  // Device header

#define Key1_Pin GPIO_Pin_7
#define Key2_Pin GPIO_Pin_6


uint8_t Key_Num;

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = Key1_Pin | Key2_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
}

uint8_t Key_GetValue(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,Key1_Pin) == RESET)
	{
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA,Key2_Pin) == RESET)
	{
		return 2;
	}
	
	return 0;
}

uint8_t Key_GetNum(void)
{
	uint8_t Temp;
	if(Key_Num)
	{
		Temp = Key_Num;
		Key_Num = 0;
		return Temp;
	}
	return 0;
}

void Key_tick(void)
{
	static uint8_t Cur_Value;
	static uint8_t Pre_Value;
	Pre_Value = Cur_Value;
	Cur_Value = Key_GetValue();
	if(Cur_Value == 0 && Pre_Value != 0)
	{
		Key_Num = Pre_Value;
	}
}

