#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include "common.h"

extern KnobSimulator knob;
extern Motor motor;
void OnUart2Cmd(uint8_t* _data, uint16_t _len)
{
    uint16_t mode = 0;
    int16_t angle = 0;
    if (_data[0] == 'm' && _len == 3) {
        sscanf((char *)_data, "m:%d", &mode);
        knob.SetMode((KnobSimulator::Mode_t) mode); 
    } else if (_data[0] == 'a') {
        sscanf((char *)_data, "a:%d", &angle);
        motor.target = (float)angle / 180 * _PI;
    }
}