#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "sI2C.h"
#include "Delay.h"


uint8_t OLED_Display[64][128] = {0};
uint8_t OLED_DisplayBuf[8][128] = {0};
void OLED_SetCursor(uint8_t Page, uint8_t X)
{
	/*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
	/*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
	/*屏幕的起始列接在了第2列，而不是第0列*/
	/*所以需要将X加2，才能正常显示*/
//	X += 2;
	
	/*通过指令设置页地址和列地址*/
	OLED_WriteCommand(0xB0 | Page);					//设置页位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置低4位
}

void OLED_Update(void)
{
	for(uint8_t j = 0; j < 8; j++) //换页
	{
		OLED_SetCursor(j,0);
		OLED_WriteDate(OLED_DisplayBuf[j],128);
	}	
}



void OLED_WriteDate(uint8_t* Data, uint8_t Count)
{
	sI2C_Start();
	sI2C_SendByte(0x78);
	sI2C_ReceiveAck();
	sI2C_SendByte(0x40);
	sI2C_ReceiveAck();
	for(uint8_t i = 0; i < Count; i++)
	{
		sI2C_SendByte(Data[i]);
		sI2C_ReceiveAck();
	}
	sI2C_Stop();
}

void OLED_WriteCommand(uint8_t Command)
{
	sI2C_Start();
	sI2C_SendByte(0x78);
	sI2C_ReceiveAck();
	sI2C_SendByte(0x00);
	sI2C_ReceiveAck();
	sI2C_SendByte(Command);
	sI2C_ReceiveAck();
	sI2C_Stop();
}

void OLED_Init(void)
{
	sI2C_Init();
	/*写入一系列的命令，对OLED进行初始化配置*/
	OLED_WriteCommand(0xAE);	//设置显示开启/关闭，0xAE关闭，0xAF开启
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);	//0x00~0xFF
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);	//0x0E~0x3F
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);	//0x00~0x7F
	
	OLED_WriteCommand(0x40);	//设置显示开始行，0x40~0x7F
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常，0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常，0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度
	OLED_WriteCommand(0xCF);	//0x00~0xFF

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/反色显示，0xA6正常，0xA7反色

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
}


void OLED_LightBit(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
	for(uint8_t i = X; i < X + Height; i++)
	{
		for(uint8_t j = Y; j < Y + Width; j++)
		{
			OLED_Display[i][j] = 0x01;
		}
	}
}

void OLED_Transfer(void)
{
	for(uint8_t j = 0; j < 128; j++)
	{
		for(uint8_t i = 0; i < 64; i++)
		{
			if(OLED_Display[i][j])
			{
				OLED_DisplayBuf[i/8][j] |= 0x01 << (i % 8); 
			}
		}
	}
}
