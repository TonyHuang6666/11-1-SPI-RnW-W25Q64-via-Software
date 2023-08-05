#include "stm32f10x.h"
#include "W25Q64_Order.h"
#include "SPI.h"

//W25Q64写使能
void W25Q64_WriteEnable(void)
{
    SPI_Initilize();
    SPI_Start();
    SPI_ExchangeByte(W25Q64_WRITE_ENABLE);
    SPI_Stop();
}

//返回W25Q64的ID
uint32_t W25Q64_ReadID(void)
{
    uint32_t Temp = 0;
    SPI_Start();
    SPI_ExchangeByte(W25Q64_JEDEC_ID);
    Temp |= SPI_ExchangeByte(0x00) << 16;
    Temp |= SPI_ExchangeByte(0x00) << 8;
    Temp |= SPI_ExchangeByte(0x00);
    SPI_Stop();
    return Temp;
}
