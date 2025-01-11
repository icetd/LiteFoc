#ifndef __COMMON_H
#define __COMMON_H

#include <stdint-gcc.h>

#ifdef __cplusplus
extern "C" {
#endif

void Main();
void OnCanCmd(uint8_t _cmd, uint8_t *_data, uint32_t _len);
void OnUart2Cmd(uint8_t* _data, uint16_t _len);

#ifdef __cplusplus

#include "Commuication/interface_uart.h"
#include "Commuication/interface_can.h"
#include "adc.h"
#include "tim.h"
#include "spi.h"
#include "can.h"
#include "Utils/retarget.h"

}

#include "Common/BLDCDriver.h"
#include "Common/CurrentSenseBase.h"
#include "Common/EncoderBase.h"
#include "Sensor/Encoder/Encoder.h"
#include "Driver/Driver.h"
#include "Common/motor.h"
#include "Common/knob.h"


#endif

#endif