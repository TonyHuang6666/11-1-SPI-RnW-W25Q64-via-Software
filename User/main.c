#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SPI.h"
#include "W25Q64.h"

uint8_t DataArray[]={0xA1,0xB2,0xC3,0xD4,0xE5,0xF6,0x07,0x08};
uint8_t ArrayRead[8]={0x00};
int main(void)
{
	OLED_Init();
	W25Q64_Init();
	Sector_Erase(0x000000);
	Page_Program(0x000000,DataArray,8);
	W25Q64_ReadData(0x000000,ArrayRead,8);
	OLED_ShowString(4,16,"T");
	OLED_ShowHexNum(1,1,ArrayRead[0],2);
	OLED_ShowHexNum(1,3,ArrayRead[1],2);
	OLED_ShowHexNum(1,5,ArrayRead[2],2);
	OLED_ShowHexNum(1,7,ArrayRead[3],2);
	OLED_ShowHexNum(1,9,ArrayRead[4],2);
	OLED_ShowHexNum(1,11,ArrayRead[5],2);
	OLED_ShowHexNum(1,13,ArrayRead[6],2);
	OLED_ShowHexNum(1,15,ArrayRead[7],2);
	while (1)
	{
		
	}
}
