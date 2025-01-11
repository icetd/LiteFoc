#ifndef CTRL_STEP_FW_AS5047_M0_STM32_H
#define CTRL_STEP_FW_AS5047_M0_STM32_H

#include "EncoderMT6816.h"


class Encoder : public EncoderMT6816
{
public:
    explicit Encoder(SPI_HandleTypeDef* _spi) : EncoderMT6816()
    {
        spiHandle = _spi;
    }

    SPI_HandleTypeDef* spiHandle = nullptr;


private:
    void SpiInit() override;

    uint16_t SpiTransmitAndRead16Bits(uint16_t _data) override;
};

#endif
