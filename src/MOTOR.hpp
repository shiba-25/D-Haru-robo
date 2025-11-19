#ifndef MOTOR
#define MOTOR

#include "mbed.h"

class Wheel
{
    const int wheel_power = 5000;
    const int wheel_stop = 0;

public:
    int automatic = 0;
    void front_move();
    void back_move();
    void right_move();
    void left_move();
    void stop_move();
};

class Mech
{
    const int motor_power = 5000;
    const int motor_stop = 0;

public:
    int motor_pwm[3] = {0};
    void chiikawa_mech_turn_plus() { motor_pwm[0] = motor_power; };
    void chiikawa_mech_turn_minus() { motor_pwm[0] = -motor_power; };
    void chiikawa_mech_turn_stop() { motor_pwm[0] = motor_stop; };
    void chiikawa_mech_up() { motor_pwm[1] = motor_power; };
    void chiikawa_mech_down() { motor_pwm[1] = -motor_power; };
    void chiikawa_mech_updn_stop() { motor_pwm[1] = motor_stop; };
    void kandai_mech_plus() { motor_pwm[2] = motor_power; };
    void kandai_mech_minus() { motor_pwm[2] = -motor_power; };
    void kandai_mech_stop() { motor_pwm[2] = motor_stop; };
};

#endif // MOTOR