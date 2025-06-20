#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "sI2C.h"

int main(void)
{
	LED_Init();
	OLED_Init();
	while(1)
	{
		for(uint8_t i = 0; i < 64; i++)
		{	
			OLED_LightBit(i, i, 2, 1);
			OLED_Transfer();
			OLED_Update();
		}
		LED_Turn();
	}
}
