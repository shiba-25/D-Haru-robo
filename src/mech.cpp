#include "mech.hpp"


void Mech::move(bool move_button[6], int16_t (&pwm)[4])
{
    is_button_push = 0;
    for (int i = 0; i < 6; i++)
    {
        is_button_push += move_button[i];
    }
        switch (is_button_push)
    {
    case 1:
        if (move_button[0])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[0][i];
            }
        }
        else if (move_button[1])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[1][i];
            }
        }
        else if (move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[2][i];
            }
        }
        else if (move_button[3])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[3][i];
            }
        }
        else if (move_button[4])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max;
            }
        }
        else if (move_button[5])
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
        if (move_button[0] && move_button[3])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[3][i]) / 2;
            }
        }
        else if (move_button[0] && move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (move_button[1] && move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (move_button[1] && move_button[3])
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

void Mech::yume_belt(bool belt_button[2], int16_t &pwm)
{
    if (belt_button[0]) pwm = yume_belt_max;
    else if (belt_button[1]) pwm = -yume_belt_max;
    else pwm = 0;
}

void Mech::taityo_arm(bool arm_button[4], int16_t &pwm1, int16_t &pwm2)
{
    if (arm_button[0]) pwm1 = taityo_single_arm_max;
    else if (arm_button[1]) pwm1 = -taityo_single_arm_max;
    else pwm1 = 0;

    if (arm_button[2]) pwm2 = taityo_double_arm_max;
    else if (arm_button[3]) pwm2 = -taityo_double_arm_max;
    else pwm2 = 0;
}

void Mech::taityo_rack(bool rack_button[2], int16_t &pwm)
{
    if (rack_button[0]) pwm = taityo_rack_max;
    else if (rack_button[1]) pwm = -taityo_rack_max;
    else pwm = 0;
}

void Mech::nabe_link(bool link_button[2], int16_t &pwm)
{
    if (link_button[0]) pwm = nabe_link_max;
    else if (link_button[1]) pwm = -nabe_link_max;
    else pwm = 0;
}