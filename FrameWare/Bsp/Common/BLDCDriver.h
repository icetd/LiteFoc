#ifndef BLDC_DRIVER_H
#define BLDC_DRIVER_H

class BLDCDriver 
{
public:
    explicit BLDCDriver(float _voltagePowerSipply) : 
        voltagePowerSupply(_voltagePowerSipply)
    {}

    float voltagePowerSupply = 12;
    float dutyA = 0;
    float dutyB = 0;
    float dutyC = 0;

    virtual bool Init() = 0;
    virtual void SetEnable(bool _enable) = 0;
    virtual void SetVoltage(float Ua, float Ub, float Uc) = 0;
};

#endif