#include "driver.h"
#include "tim.h"


inline float Constraint(float _val)
{
    if (_val > 1) _val = 1;
    else if (_val < 0) _val = 0;

    return _val;
}


bool Driver::ConfigTimerForPwm()
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);  // B
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  // A
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);  // C

    SetPwmDutyByRegister(0, 0, 0);
    
    return true;
}


void Driver::SetPwmDutyByRegister(float _dutyA, float _dutyB, float _dutyC)
{
    _dutyA = Constraint(_dutyA);
    _dutyB = Constraint(_dutyB);
    _dutyC = Constraint(_dutyC);

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (uint16_t) (_dutyA * PERIOD_COUNT));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (uint16_t) (_dutyB * PERIOD_COUNT));
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (uint16_t) (_dutyC * PERIOD_COUNT));
}
