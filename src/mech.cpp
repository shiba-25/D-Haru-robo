#include "mech.hpp"

void Mech::move(bool up, bool down, bool right, bool left, int16_t (&pwm)[4]){
    int is_button_push = up + down + right + left;
    switch (is_button_push){
        case 1:
            if (up) {
                for(int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * wheel_motor[0][i];
                }
            } else if (down) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * wheel_motor[1][i];
                }
            } else if (right) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * wheel_motor[2][i];
                }
            } else if (left) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * wheel_motor[3][i];
                }
            } else {
                for (int i = 0; i < 4; i++){
                    pwm[i] = 0;
                }
            }
            break;
        case 2:
            if (up && left) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[3][i]) / 2;
                }
            } else if (up && right) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[2][i]) / 2;
                }
            } else if (down && right) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[2][i]) / 2;
                }
            } else if (down && left) {
                for (int i = 0; i < 4; i++){
                    pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[3][i]) / 2;
                }
            } else {
                for (int i = 0; i < 4; i++){
                    pwm[i] = 0;
                }
            }
            break;
        default:
            for (int i = 0; i < 4; i++){
                pwm[i] = 0;
            }
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