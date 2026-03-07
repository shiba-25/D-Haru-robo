#ifndef MECH_HPP_
#define MECH_HPP_

#include "mbed.h"
#include "FIRSTPENGUIN.hpp"
#include <cmath>
// #include <chrono>
// #include "controller.hpp"

class Mech
{
public:
    float is_control_change;
    int16_t encoder[4] = {0};
    int16_t pwm[4] = {0};
    Mech(int change) : is_control_change(change) {}
    void move(bool [6], float[4], int16_t (&)[4], int16_t[4]);
    void test(int16_t (&)[4]);
    void yume_belt(bool [4], int16_t &);
    void taityo_arm(bool [2], int16_t &, int16_t &);
    void taityo_rack(bool[2], int16_t &);
    void nebaarukun(bool[2], int16_t &);
    void control_change(bool);
private:
    const float wheel_max = 5000;
    const int slow_wheel_max = 5000;
    const int yume_belt_max = 7000;
    const int slow_yume_belt_max = 4000;
    const int taityo_single_arm_max = 3500;
    const int taityo_double_arm_max = 4500;
    const int always_taityo_single_arm = 1800;
    const int always_taityo_double_arm = 2000;
    const int taityo_rack_max = 18000;
    const int nebaarukun_max = 3000;
    const int goal_role = 3000;
    const int wheel_motor[4][4] = {{-1, -1, 1, 1}, {1, 1, -1, -1}, {-1, 1, 1, -1}, {1, -1, -1, 1}};
    float mecanum[4] = {0};
    float power = 0;
    float angle = 0;
    int r_dir = 0;
    int is_button_push = 0;
};

#endif // MECH_HPP_