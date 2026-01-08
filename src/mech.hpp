#ifndef MECH_HPP_
#define MECH_HPP_

#include "mbed.h"
#include "FIRSTPENGUIN.hpp"

class Mech
{
private:
    const int wheel_max = 7000;
    const int yume_belt_max = 5000;
    const int taityo_single_arm_max = 5000;
    const int taityo_double_arm_max = 5000;
    const int taityo_rack_max = 5000;
    const int nabe_link_max = 5000;
    const int wheel_motor[4][4] = {{-1, -1, 1, 1}, {1, 1, -1, -1}, {1, -1, -1, 1}, {-1, 1, 1, -1}};

public:
    void move(bool, bool, bool, bool, int16_t (&)[4]);
    void yume_belt(bool, bool, int16_t &);
    void taityo_arm(bool, bool, bool, bool, int16_t &, int16_t &);
    void taityo_rack(bool, bool, int16_t &);
    void nabe_link(bool, bool, int16_t &);
};

#endif // MECH_HPP_