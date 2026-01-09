#include "mech.hpp"

void Mech::move(int16_t (&pwm)[4])
{
    int is_button_push = controller["up"] + controller["down"] + controller["right"] + controller["left"] + controller["OP"] + controller["SH"];
    switch (is_button_push)
    {
    case 1:
        if (controller["up"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[0][i];
            }
        }
        else if (controller["down"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[1][i];
            }
        }
        else if (controller["right"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[2][i];
            }
        }
        else if (controller["left"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[3][i];
            }
        }
        else if (controller["SH"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max;
            }
        }
        else if (controller["OP"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = -wheel_max;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = 0;
            }
        }
        break;
    case 2:
        if (controller["up"] && controller["left"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[3][i]) / 2;
            }
        }
        else if (controller["up"] && controller["right"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (controller["down"] && controller["right"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (controller["down"] && controller["left"])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[3][i]) / 2;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = 0;
            }
        }
        break;
    default:
        for (int i = 0; i < 4; i++)
        {
            pwm[i] = 0;
        }
    }
}

void Mech::yume_belt(int16_t &pwm)
{
    if (controller["tri"]) pwm = yume_belt_max;
    else if (controller["ci"]) pwm = -yume_belt_max;
    else pwm = 0;
}

void Mech::taityo_arm(int16_t &pwm1, int16_t &pwm2)
{
    if (controller["R1"]) pwm1 = taityo_single_arm_max;
    else if (controller["L1"]) pwm1 = -taityo_single_arm_max;
    else pwm1 = 0;

    if (controller["R2"]) pwm2 = taityo_double_arm_max;
    else if (controller["L2"]) pwm2 = -taityo_double_arm_max;
    else pwm2 = 0;
}

void Mech::taityo_rack(int16_t &pwm)
{
    if (controller["R3"]) pwm = taityo_rack_max;
    else if (controller["L3"]) pwm = -taityo_rack_max;
    else pwm = 0;
}

void Mech::nabe_link(int16_t &pwm)
{
    if (controller["sq"]) pwm = nabe_link_max;
    else if (controller["cr"]) pwm = -nabe_link_max;
    else pwm = 0;
}