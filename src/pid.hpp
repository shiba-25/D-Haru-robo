// #ifndef PID_HPP
// #define PID_HPP

// #include <iostream>
// #include "mbed.h"

// struct Pid_Gain
// {
//     float p_gain = 0.0;
//     float i_gain = 0.0;
//     float d_gain = 0.0;
// };

// class Pid
// {
// public:
//     Pid(const Pid_Gain pid_gain) : _pid_gain(pid_gain), _pre_error(0), _integral(0) {}
//     void pid_calc(float goal, float encoder)
//     {
//         float error = (goal - encoder) * 1000 / 20;
//         float p_control;
//         float i_control;
//         float d_control;

//         float output = _pid_gain.p_gain * p_control + _pid_gain.i_gain * i_control + _pid_gain.d_gain * d_control;
//         _pre_error = error;
//     };
// private:
//     Pid_Gain _pid_gain;
//     int _pre_error = 0;
//     int _integral = 0;
// };

// #endif