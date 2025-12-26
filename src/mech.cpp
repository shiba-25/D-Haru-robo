#include "mech.hpp"

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