#ifndef PID_HPP
#define PID_HPP

#include <iostream>
#include "mbed.h"

struct Pid_Gain
{
    float p_gain = 0.5;
    float i_gain = 0.0;
    float d_gain = 0.0;
};

class Pid
{
public:
    void calc(float goal, int16_t &encoder,  int16_t &pwm)
    {
        int error = goal - (encoder - pre_encoder);
        int p_control = error - _pre_error;
        float i_control = 0;
        float d_control = 0;

        int output = _pid_gain.p_gain * p_control + _pid_gain.i_gain * i_control + _pid_gain.d_gain * d_control;
        pwm_value += output;
        pwm = min(max(pwm_value, -8000), 8000);
        // printf("pgain: %f pcontrol: %f\n", _pid_gain.p_gain, p_control);
        _pre_error = error;
        pre_encoder = encoder;
        encoder = 0;
    };

private:
    Pid_Gain _pid_gain;
    int _pre_error = 0;
    int16_t pre_encoder = 0;
    int _integral = 0;
    int pwm_value = 0;
};
#endif