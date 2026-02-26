#ifndef MECH_HPP_
#define MECH_HPP_

#include "mbed.h"
#include "FIRSTPENGUIN.hpp"
#include <chrono>
// #include "controller.hpp"

class Mech
{
private:
    const int wheel_max = 7000;
    const int slow_wheel_max = 3500;
    const int yume_belt_max = 6000;
    const int taityo_single_arm_max = 3500;
    const int taityo_double_arm_max = 5500;
    const int taityo_rack_max = 18000;
    const int nabe_link_max = 5000;
    // const int decomposition = 1024;
    const int wheel_motor[6][4] = {{-1, -1, 1, 1}, {1, 1, -1, -1}, {-1, 1, 1, -1}, {1, -1, -1, 1}, {1, 1, 1, 1}, {-1, -1, -1, -1}};
    int r_dir = 0;
    int is_button_push = 0;
    // int before_error = 0;
    // int before_encoder = 0;
    // float dt = 10ms;
    // float p_control = 0;
    // float i_control = 0;
    // float d_control = 0;
    // float p_gain = 0.0f;
    // float i_gain = 0.0f;
    // float d_gain = 0.0f;
    // float revolutions = 2;
    
    public:
    int is_control_change;
    int16_t encoder[4] = {0};
    int16_t pwm[4] = {0};
    Mech(int change) : is_control_change(change) {}
    void move(bool [6], float[4], int16_t (&)[4]);
    void test(int16_t (&)[4]);
    void yume_belt(bool [2], int16_t &);
    void taityo_arm(bool [4], int16_t &, int16_t &);
    void taityo_rack(bool[2], int16_t &);
    void nabe_honmaru(bool [2], int16_t &);
    void v_goal(bool);
    void control_change(bool);
    // void pid_calc(int16_t &, int16_t, int16_t);
    // void pid_start();
    // void pid_starter();
};

#endif // MECH_HPP_