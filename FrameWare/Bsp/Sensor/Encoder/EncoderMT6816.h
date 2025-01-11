#ifndef ENCODER_MT6816_H
#define ENCODER_MT6816_H

#include "Common/EncoderBase.h"
#include "Common/math_utils.h"

class EncoderMT6816 : public EncoderBase
{
public:
    EncoderMT6816() = default;
    void Init() override;

private:
    typedef struct
    {
        uint16_t rawTemp;       // SPI raw 16bits data
        uint16_t rawData;      // 14bits rawAngle in rawData
        bool noMagFlag;
        bool checksumFlag;
    } SpiRawData_t;


    SpiRawData_t spiRawData;
    uint16_t dataTx[2];
    uint16_t dataRx[2];
    uint8_t hCount;

    /*
     * Resolution is (2^14 = 16384), each state will use an uint16 data
     * as map, thus total need 32K-flash for calibration.
    */
    const int32_t RESOLUTION = ((int32_t) ((0x00000001U) << 14));


    float GetRawAngle() override;

    uint16_t GetRawData();

    virtual void SpiInit() = 0;
    virtual uint16_t SpiTransmitAndRead16Bits(uint16_t _dataTx) = 0;
};

#endif