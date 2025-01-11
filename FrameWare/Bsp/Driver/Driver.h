#ifndef DRIVER_H
#define DRIVER_H

#include "BLDCDriver3PWM.h"

class Driver : public BLDCDriver3PWM
{
public:
    static const int PERIOD_COUNT = 1799;

    explicit Driver (float _vlotagePowerSupply) :
        BLDCDriver3PWM(_vlotagePowerSupply)
    {}

private:
    bool ConfigTimerForPwm() override;
    void SetPwmDutyByRegister(float _dutyA, float _dutyB, float _dutyC) override;
};

#endif