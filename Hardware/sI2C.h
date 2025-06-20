#ifndef __SI2C_H
#define __SI2C_H

void sI2C_Init(void);					//引脚初始化	
void sI2C_Start(void); 					//发送起始位
void sI2C_Stop(void);					//发送停止位
void sI2C_SendByte(uint8_t Byte);		//发送一个字节
uint8_t sI2C_ReceiveByte(void);			//接收一个字节
void sI2C_SendAck(uint8_t Ack);			//发送一个Ack
uint8_t sI2C_ReceiveAck(void);			//接收一个Ack

#endif
