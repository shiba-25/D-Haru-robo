#ifndef MECH_HPP_
#define MECH_HPP_

#include "mbed.h"
#include "FIRSTPENGUIN.hpp"
// #include "controller.hpp"

class Mech
{
private:
    const int wheel_max = 7000;
    const int yume_belt_max = 8000;
    const int taityo_single_arm_max = 10000;
    const int taityo_double_arm_max = 5000;
    const int taityo_rack_max = 10000;
    const int nabe_link_max = 5000;
    const int wheel_motor[4][4] = {{-1, -1, 1, 1}, {1, 1, -1, -1}, {1, -1, -1, 1}, {-1, 1, 1, -1}};
    int is_button_push = 0;
    int is_control_change = 1;


public:
    void move(bool [6], int16_t (&)[4]);
    void test(int16_t (&)[4]);
    void yume_belt(bool [2], int16_t &);
    void taityo_arm(bool [4], int16_t &, int16_t &);
    void taityo_rack(bool[2], int16_t &);
    void nabe_link(bool [2], int16_t &);
    void control_change(bool);
};

#endif // MECH_HPP_