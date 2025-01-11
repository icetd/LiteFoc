#include <common.h>
#include <can.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

extern KnobSimulator knob;

void OnCanCmd(uint8_t _cmd, uint8_t *_data, uint32_t _len)
{
    uint16_t mode;
    int ret = 0;
    
    switch (_cmd) {
    case 0x11:
        ret = sscanf((char *)_data, "%d", &mode);
        knob.SetMode((KnobSimulator::Mode_t) mode); 
        break;
    default:
        break;
    }
}