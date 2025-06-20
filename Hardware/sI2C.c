#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/*引脚配置*/
#define RCC_GPIO_CLK	RCC_APB2Periph_GPIOB
#define SCL_Group		GPIOB
#define SCL_Pin 		GPIO_Pin_8
#define SDA_Group 		GPIOB
#define SDA_Pin 		GPIO_Pin_9
#define H				Bit_SET
#define L				Bit_RESET
/**/

/*延时配置*/
#define delay(x)		Delay_us(x)
#define sI2C_Delay		delay(10)						
/**/

/*引脚操作*/
#define sI2C_W(x,y,z)	GPIO_WriteBit(x,y,z)
#define sI2C_R(x,y)		GPIO_ReadInputDataBit(x,y)

#define GPIO_W(x,y,z)	GPIO_WriteBit(x,y,z)
#define GPIO_R(x,y)		GPIO_ReadInputDataBit(x,y)
#define SCL_W_H			GPIO_W(SCL_Group,SCL_Pin,H)
#define SCL_W_L 		GPIO_W(SCL_Group,SCL_Pin,L)
#define SDA_W_H			GPIO_W(SDA_Group,SDA_Pin,H)
#define SDA_W_L			GPIO_W(SDA_Group,SDA_Pin,L)
/**/

#define TransLevel(x)	(BitAction)(x)

void sI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_CLK,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = SCL_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCL_Group,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SDA_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SDA_Group,&GPIO_InitStruct);
	
	sI2C_W(SCL_Group,SCL_Pin,H);
	sI2C_W(SDA_Group,SDA_Pin,H);
}

void sI2C_W_SCL(uint8_t BitValue)
{
	sI2C_W(SCL_Group,SCL_Pin,TransLevel(BitValue));
	sI2C_Delay;
}

void sI2C_W_SDA(uint8_t BitValue)
{
	sI2C_W(SDA_Group,SDA_Pin,TransLevel(BitValue));
	sI2C_Delay;
}

uint8_t sI2C_R_SDA(void)
{
	uint8_t Byte;
	Byte = sI2C_R(SDA_Group,SDA_Pin);
	sI2C_Delay;
	return Byte;
}

uint8_t sI2C_R_SCL(void)
{
	uint8_t Byte;
	Byte = sI2C_R(SCL_Group,SCL_Pin);
	sI2C_Delay;
	return Byte;
}

void sI2C_Start(void)
{
	sI2C_W_SDA(1);
	sI2C_W_SCL(1);
	sI2C_W_SDA(0);
	sI2C_W_SCL(0);
}

void sI2C_Stop(void)
{
	sI2C_W_SDA(0);
	sI2C_W_SCL(1);
	sI2C_W_SDA(1);
}

void sI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		sI2C_W_SDA(!!(Byte & (0x80 >> i)));
		sI2C_W_SCL(1);
		sI2C_W_SCL(0);
	}
}

uint8_t sI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00;
	uint8_t i;
	sI2C_W_SDA(1);
	for(i = 0; i < 8; i++)
	{
		sI2C_W_SCL(1);
		if(sI2C_R_SDA())
		{
			Byte |= (0x80 >> i);
		}
		sI2C_W_SCL(0);
	}
	return Byte;
}

void sI2C_SendAck(uint8_t Ack)
{
	sI2C_W_SDA(Ack);
	sI2C_W_SCL(1);
	sI2C_W_SCL(0);
//	sI2C_W_SDA(1);
}

uint8_t sI2C_ReceiveAck(void)
{
	uint8_t Ack;
	sI2C_W_SDA(1);
	sI2C_W_SCL(1);
	Ack = sI2C_R_SDA();
	sI2C_W_SCL(0);
	return Ack;
}
