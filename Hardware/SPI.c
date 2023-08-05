#include "stm32f10x.h"
#include "Delay.h"
#define Delay_Time 1
void SPI_Initilize(void)
{
    //1.初始化SPI引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //2.SS引脚置高电平，SPI总线空闲状态
    GPIO_SetBits(GPIOA, GPIO_Pin_4);

}

//以下函数为对引脚操作的封装和改名，方便移植
void SPI_SS(uint8_t BitValue)//写SS引脚电平
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
    Delay_us(Delay_Time);
}

void SPI_SCK(uint8_t BitValue)//写SCK引脚电平
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
    Delay_us(Delay_Time);
}

void SPI_MOSI(uint8_t BitValue)//写MOSI引脚电平
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
    Delay_us(Delay_Time);
}

uint8_t SPI_MISO(void)//读MISO引脚电平
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
    Delay_us(Delay_Time);
    return BitValue;
}

//以下为SPI的三种基本条件：起始条件、终止条件、交换一个字节（模式0）

void SPI_Start(void)//起始条件
{
    SPI_SCK(0);//SCK引脚拉低,因为SPI总线模式0空闲状态为SCK低电平
    SPI_SS(0);//SS引脚拉低
}

void SPI_Pause(void)//终止条件
{
    SPI_SS(1);//SS引脚拉高
    SPI_SCK(0);//SCK引脚拉低
}

uint8_t SPI_ExchangeByte(uint8_t TxData)//交换一个字节
{
    uint8_t i, RxData = 0x00;
    for(i=0;i<8;i++)
    {
        //当i=0时，SS下降沿，MISO与MOSI都移出数据
        //MOSI移出数据
        if(TxData & 0x80)
            SPI_MOSI(1);//MOSI引脚拉高
        else
            SPI_MOSI(0);//MOSI引脚拉低
        TxData <<= 1;
        
        //SCK上升沿，数据移入
        SPI_SCK(1);//SCK引脚拉高
        //MISO读取数据
        if(SPI_MISO())
            RxData |= 0x01;
        RxData <<= 1;
        SPI_SCK(0);//SCK引脚拉低
    }
    return RxData;
}