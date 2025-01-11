#include "Encoder.h"
#include "spi.h"


void Encoder::SpiInit()
{
    MX_SPI2_Init();
}

uint16_t Encoder::SpiTransmitAndRead16Bits(uint16_t _dataTx)
{
    uint16_t dataRx;

    SPI2_CS_GPIO_Port->BRR = SPI2_CS_Pin; // Chip select
    HAL_SPI_TransmitReceive(spiHandle, (uint8_t*) &_dataTx, (uint8_t*) &dataRx, 1, HAL_MAX_DELAY);
    SPI2_CS_GPIO_Port->BSRR = SPI2_CS_Pin;
    return dataRx;
}