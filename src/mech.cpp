#include "mech.hpp"

void Mech::move(bool move_button[6], float stick_position[4], int16_t (&pwm)[4])
{
    is_button_push = 0;
    int wheel_dir[4] = {0};
    for (int i = 0; i < 6; i++)
    {
        is_button_push += move_button[i];
    }

    for (int i = 0; i < 6; i++)
    {
        if (move_button[i])
        {
            for (int j = 0; j < 4; j++)
            {
                wheel_dir[j] += wheel_motor[j][i];
            }
        }
    }

    switch (is_button_push)
    {
    case 0:
        if (stick_position[0] != 0 || stick_position[1] != 0)
        {
            r_dir = atan2((-1 * stick_position[1]), stick_position[0]);
            // float power = hypot(stick_position[0], stick_position[1]);
            for (int i = 0; i < 4; i++)
            {
                int mekanamu = -1 * (int)(sin((M_PI / 180 * (90 * i + 45)) + r_dir) * slow_wheel_max);
                if (mekanamu > 0)
                {
                    pwm[i] = min(mekanamu, wheel_max);
                }
                else if (mekanamu < 0)
                {
                    pwm[i] = max(mekanamu, -wheel_max);
                }
                else
                {
                    pwm[i] = 0;
                }
            }
        }
        else if (stick_position[2] != 0 || stick_position[3] != 0)
        {
            if (stick_position[2] > 100)
            {
                for (int i = 0; i < 4; i++)
                {
                    pwm[i] = slow_wheel_max * wheel_motor[2][i] * is_control_change;
                }
            }
            else if (stick_position[2] < -100)
            {
                for (int i = 0; i < 4; i++)
                {
                    pwm[i] = slow_wheel_max * wheel_motor[3][i] * is_control_change;
                }
            }
            else if (stick_position[3] > 100)
            {
                for (int i = 0; i < 4; i++)
                {
                    pwm[i] = slow_wheel_max * wheel_motor[0][i] * is_control_change;
                }
            }
            else if (stick_position[3] < -100)
            {
                for (int i = 0; i < 4; i++)
                {
                    pwm[i] = slow_wheel_max * wheel_motor[1][i] * is_control_change;
                }
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    pwm[i] = 0;
                }
            }
        }
        else
        {
            for(int i = 0;i < 4; i++)
            {
                pwm[i] = 0;
            }
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++)
        {
            pwm[i] = wheel_max  * is_control_change * wheel_dir[i];
        }
        break;
    case 2:
        for (int i = 0; i < 4; i++)
        {
            pwm[i] = wheel_max * is_control_change * (wheel_dir[i] / 2);
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

void Mech::nabe_honmaru(bool link_button[2], int16_t &pwm)
{
    pwm = nabe_link_max * (link_button[0] - link_button[1]);
}
