#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SPI.h"
#include "W25Q64.h"

int main(void)
{
	OLED_Init();
	OLED_ShowString(4,16,"T");
	W25Q64_WriteEnable();
	uint32_t ID=W25Q64_ReadID();
	OLED_ShowHexNum(1,1,ID,16);
	while (1)
	{
		
	}
}
