#include "EncoderMT6816.h"

void EncoderMT6816::Init()
{
    SpiInit();
    VarInit();
}

float EncoderMT6816::GetRawAngle()
{
    return ((float) GetRawData()) / (float) RESOLUTION * _2PI;
}

uint16_t EncoderMT6816::GetRawData()
{
    dataTx[0] = (0x80 | 0x03) << 8;
    dataTx[1] = (0x80 | 0x04) << 8;

    for (uint8_t i = 0; i < 3; i++)
    {
        dataRx[0] = SpiTransmitAndRead16Bits(dataTx[0]);
        dataRx[1] = SpiTransmitAndRead16Bits(dataTx[1]);

        spiRawData.rawTemp = ((dataRx[0] & 0x00FF) << 8) | (dataRx[1] & 0x00FF);

        //奇偶校验
        hCount = 0;
        for (uint8_t j = 0; j < 16; j++) {
            if (spiRawData.rawTemp & (0x0001 << j))
                hCount++;
        }
        if (hCount & 0x01) {
            spiRawData.checksumFlag = false;
        } else {
            spiRawData.checksumFlag = true;
            break;
        }
    }

    if (spiRawData.checksumFlag)
    {
        spiRawData.rawData = spiRawData.rawTemp >> 2;
        spiRawData.noMagFlag = (bool) (spiRawData.rawTemp & (0x0001 << 1));
    }

    return spiRawData.rawData;
}