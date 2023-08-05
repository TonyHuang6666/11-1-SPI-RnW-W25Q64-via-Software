#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SPI.h"
#include "W25Q64.h"

int main(void)
{
	OLED_Init();
	OLED_ShowString(4,16,"T");
	while (1)
	{
		
	}
}
