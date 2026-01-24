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
                pwm[i] = wheel_max * wheel_motor[0][i] * is_control_change;
            }
        }
        else if (move_button[1])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[1][i] * is_control_change;
            }
        }
        else if (move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[2][i] * is_control_change;
            }
        }
        else if (move_button[3])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * wheel_motor[3][i] * is_control_change;
            }
        }
        else if (move_button[4])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * is_control_change;
            }
        }
        else if (move_button[5])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = -wheel_max * is_control_change;
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
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[3][i]) / 2 * is_control_change;
            }
        }
        else if (move_button[0] && move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[0][i] + wheel_motor[2][i]) / 2 * is_control_change;
            }
        }
        else if (move_button[1] && move_button[2])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[2][i]) / 2 * is_control_change;
            }
        }
        else if (move_button[1] && move_button[3])
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * (wheel_motor[1][i] + wheel_motor[3][i]) / 2 * is_control_change;
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
    pwm = yume_belt_max * (belt_button[0] - belt_button[1]);
}

void Mech::taityo_arm(bool arm_button[4], int16_t &pwm1, int16_t &pwm2)
{
    pwm1 = taityo_single_arm_max * (arm_button[0] - arm_button[1]);

    pwm2 = taityo_double_arm_max * (arm_button[2] - arm_button[3]);
}

void Mech::taityo_rack(bool rack_button[2], int16_t &pwm)
{
    pwm = taityo_rack_max * (rack_button[0] - rack_button[1]);
}

void Mech::nabe_link(bool link_button[2], int16_t &pwm)
{
    pwm = nabe_link_max * (link_button[0] - link_button[1]);
}

void Mech::control_change(bool change_button)
{
    switch (is_control_change) {
        case 1:
            while (change_button)
            {
                is_control_change = -1;
            }
            break;
        case -1:
            while (change_button)
            {
                is_control_change = 1;
            }
            break;
    }
}