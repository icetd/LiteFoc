#include "common.h"
#include "config.h"
#include <cstdio>


BoardConfig_t boardConfig;
Motor motor(7);
Encoder encoder(&hspi2);
Driver driver(12);
KnobSimulator knob;

void Main()
{
    boardConfig = {
        .canNodeId = 1,
    };

    can_init(&hcan);
    uart_init(&huart2);
    motor.AttachDriver(&driver);
    motor.AttachEncoder(&encoder);
    knob.Init(&motor);
    knob.SetEnable(true);
    knob.SetMode(KnobSimulator::MODE_DISABLE);

    HAL_Delay(100);
    HAL_TIM_Base_Start_IT(&htim4); // 2KHz for knob, depends on mcu freq

    for (;;) {
        usart_printf(&huart2, "v=%f, p=%f, t=%d\n", knob.GetVelocity(), knob.GetPosition(), knob.GetEncoderModePos());
        HAL_Delay(1);
    }
}

extern "C" void Tim4Callback2kHz()
{
    __HAL_TIM_CLEAR_IT(&htim4, TIM_IT_UPDATE);
    knob.Tick();
}