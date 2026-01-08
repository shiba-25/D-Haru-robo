#include "mech.hpp"

void Mech::move(bool up, bool down, bool right, bool left, int16_t (&pwm)[4])
{
    int is_button_push = up + down + right + left;
    switch (is_button_push)
    {
    case 1:
        if (up)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[0][i];
            }
        }
        else if (down)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[1][i];
            }
        }
        else if (right)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[2][i];
            }
        }
        else if (left)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[3][i];
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
        if (up && left)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[3][i]) / 2;
            }
        }
        else if (up && right)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (down && right)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[2][i]) / 2;
            }
        }
        else if (down && left)
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

void Mech::yume_belt(bool tri, bool ci, int16_t &pwm)
{
    if (tri)
        pwm = yume_belt_max;
    else if (ci)
        pwm = -yume_belt_max;
    else
        pwm = 0;
}

void Mech::taityo_arm(bool R1, bool L1, bool R2, bool L2, int16_t &pwm1, int16_t &pwm2)
{
    if (R1)
        pwm1 = taityo_single_arm_max;
    else if (L1)
        pwm1 = -taityo_single_arm_max;
    else
        pwm1 = 0;

    if (R2)
        pwm2 = taityo_double_arm_max;
    else if (L2)
        pwm2 = -taityo_double_arm_max;
    else
        pwm2 = 0;
}

void Mech::taityo_rack(bool R3, bool L3, int16_t &pwm)
{
    if (R3)
        pwm = taityo_rack_max;
    else if (L3)
        pwm = -taityo_rack_max;
    else
        pwm = 0;
}

void Mech::nabe_link(bool sq, bool cr, int16_t &pwm)
{
    if (sq)
        pwm = nabe_link_max;
    else if (cr)
        pwm = -nabe_link_max;
    else
        pwm = 0;
}