#ifndef KNOB_H
#define KNOB_H

#include "Common/motor.h"

class KnobSimulator
{
public:
    KnobSimulator() = default;;

    enum Mode_t
    {
        MODE_DISABLE = 0,
        MODE_INERTIA,
        MODE_ENCODER,
        MODE_SPRING,
        MODE_DAMPED,
        MODE_SPIN
    };

    void Init(Motor* _motor);
    void Tick();
    void SetEnable(bool _en);
    void ApplyZeroPos(float _angle = 0);
    void SetMode(Mode_t _mode);
    void SetLimitPos(float _min, float _max);
    float GetPosition();
    float GetVelocity();
    int GetEncoderModePos();


private:
    Motor* motor{};
    Mode_t mode = MODE_DISABLE;
    float zeroPosition = 0;
    float limitPositionMax = _PI_2;
    float limitPositionMin = 0;
    int encoderDivides = 12;
    int encoderPosition = 0;

    float lastAngle{};
    float lastVelocity{};
};

#endif //HELLOWORD_DYNAMIC_FW_KNOB_H
