#include "mech.hpp"

void Mech::move(bool move_button[4], float stick_position[3], int16_t (&pwm)[4])
{
    is_button_push = 0;
    int wheel_dir[4] = {0};
    for (int i = 0; i < 4; i++)
    {
        is_button_push += move_button[i];
    }


    for (int i = 0; i < 6; i++)
    {
        if (move_button[i])
        {
            for (int j = 0; j < 4; j++)
            {
                wheel_dir[j] += wheel_motor[i][j];
            }
        }
        else
        {
            continue;
        }
    }

    switch (is_button_push)
    {
    case 0:
        if (stick_position[2] != 0)
        {
            for (int i = 0; i < 4; i++)
            {
                pwm[i] = wheel_max * stick_position[2] * is_control_change;
            }
        }
        else
        {
            power = hypot(stick_position[0], stick_position[1]);
            angle = atan2(stick_position[1], -stick_position[0]);
            for (int i = 0; i < 4; i++)
            {
                mecanum[i] = (sin((M_PI / 180 * (90 * i + 45)) + angle) * power * 4 );
                pwm[i] = wheel_max * mecanum[i] * is_control_change;
            }
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++)
        {
            pwm[i] = wheel_max * is_control_change * wheel_dir[i];
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


void Mech::yume_belt(bool belt_button[4], int16_t &pwm)
{
    if(belt_button[0] || belt_button[1])
    {
        pwm = yume_belt_max * (belt_button[0] - belt_button[1]);
    }
    else if(belt_button[2] || belt_button[3])
    {
        pwm = slow_yume_belt_max * (belt_button[2] - belt_button[3]);
    }
    else
    {
        pwm = 0;
    }
}

void Mech::taityo_arm(bool arm_button[4], int16_t &pwm1, int16_t &pwm2)
{
    pwm1 = taityo_single_arm_max * arm_button[0] - arm_button[1];

    pwm2 = taityo_double_arm_max * arm_button[2] - arm_button[3];
}

void Mech::taityo_rack(bool rack_button[2], int16_t &pwm)
{
    pwm = taityo_rack_max * (rack_button[0] - rack_button[1]);
}

void Mech::nebaarukun(bool nebaru_button[2], int16_t &pwm)
{
    pwm = nebaarukun_max * (nebaru_button[0] - nebaru_button[1]);
}

// void Mech::v_goal(bool sengen)
// {
//     DigitalOut NeoPixel(PA_0);
//     if (sengen)
//     {
//         NeoPixel = 0;
//     }
//     else
//     {
//         NeoPixel = 1;
//     }
// }
// void Mech::pid_calc(int16_t (&pwm_control), int16_t encoder_value, int16_t want_value)
// {
//     float error;
//     error = want_value - (encoder_value * decomposition);
//     p_control = error;
//     i_control += error * dt;
//     d_control = (error - before_error) / dt;

//     pwm_control = p_gain * p_control + i_gain * i_control + d_gain * d_control;
//     if (pwm_control > 10000)
//     {
//         pwm_control = 10000;
//     }
//     else if (pwm_control < -10000)
//     {
//         pwm_control = -10000;
//     }
//     before_encoder = encoder_value;
//     before_error = error;
// }

// void Mech::pid_start()
// {
//     for (int i = 0; i < 4; i++)
//     {
//         pid_calc(pwm[i], encoder[i], revolutions);
//     }
// }

// void Mech::pid_starter()
// {
//     Ticker pid_starter;
//     pid_starter.attach(&Mech::pid_start, 0.02f);
// }