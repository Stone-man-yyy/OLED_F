#ifndef __OLED_H
#define __OLED_H

void OLED_WriteDate(uint8_t* Data, uint8_t Count);
void OLED_Update(void);
void OLED_SetCursor(uint8_t X, uint8_t Page);
void OLED_WriteCommand(uint8_t Command);
void OLED_Init(void);
void OLED_LightBit(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
void OLED_Transfer(void);

#endif
