#ifndef BLDC_DRIVER_3PWM_H
#define BLDC_DRIVER_3PWM_H

#include "../Common/BLDCDriver.h"
#include "../Common/math_utils.h"

class BLDCDriver3PWM : public BLDCDriver
{
public:
    explicit BLDCDriver3PWM (float _voltagePowerSupply) :
        BLDCDriver(_voltagePowerSupply)
    {}

    static constexpr uint32_t PWM_FREQUENCY = 20000;

    bool Init() override;
    void SetEnable(bool _enable) override;
    void SetVoltage(float Ua, float Ub, float Uc) override;

private:
    virtual bool ConfigTimerForPwm() = 0;
    virtual void SetPwmDutyByRegister(float _dutyA, float _dutyB, float _dutyC) = 0;
};

#endif