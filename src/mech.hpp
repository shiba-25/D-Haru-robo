#ifndef MECH_HPP_
#define MECH_HPP_

#include "mbed.h"
#include "FIRSTPENGUIN.hpp"

int32_t fp_can_id = 30;
CAN can(PB_12, PB_13, (int)1e6);
FirstPenguin penguin(fp_can_id, can);

class Mech{
    private:
        const int wheel_max = 7000;
        const int yume_belt_max = 5000;
        const int taityo_rack_max = 5000;
        const int nabe_link_max = 5000;
        const int wheel_motor[4][4] ={{-1,-1,1,1},{1,1,-1,-1},{1,-1,-1,1},{-1,1,1,-1}};
    public:
        void move(int, int16_t (&)[4]);
        void yume_belt(int, int16_t &);
        void taityo_rack(int, int16_t &);
        void nabe_link(int, int16_t &);
};

void Mech::move(int mode, int16_t (&pwm)[4]){
    switch (mode){
        case 0:
            for (int i = 0; i < 4; i++){
                pwm[i] = wheel_max * wheel_motor[0][i];
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++){
                pwm[i] = wheel_max * wheel_motor[1][i];
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++){
                pwm[i] = wheel_max * wheel_motor[2][i];
            }
            break;
        case 3:
            for (int i = 0; i < 4; i++){
                pwm[i] = wheel_max * wheel_motor[3][i];
            }
            break;
        default:
            for (int i = 0; i < 4; i++){
                pwm[i] = 0;
            }
            break;
    }
    penguin.send();
}

void Mech::yume_belt(int mode, int16_t &pwm){
    switch (mode){
        case 0:
            pwm = yume_belt_max;
            break;
        case 1:
            pwm = -yume_belt_max;
            break;
        default:
            pwm = 0;
            break;
    }
}

void Mech::taityo_rack(int mode, int16_t &pwm){
    switch (mode){
        case 0:
            pwm = taityo_rack_max;
            break;
        case 1:
            pwm = -taityo_rack_max;
            break;
        default:
            pwm = 0;
            break;
    }
}

void Mech::nabe_link(int mode, int16_t &pwm){
    switch (mode){
        case 0:
            pwm = nabe_link_max;
            break;
        case 1:
            pwm = -nabe_link_max;
            break;
        default:
            pwm = 0;
            break;
    }
}
#endif // MECH_HPP_