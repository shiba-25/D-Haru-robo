#include "mech.hpp"

void Mech::move(bool move_button[6], float stick_position[4], int16_t (&pwm)[4])
{
    is_button_push = 0;
    int wheel_dir[4] = {0};
    for (int i = 0; i < 6; i++)
    {
        is_button_push += move_button[i];
    }

    for (int i = 1; i < 4; i++)
    {
        stick_position[i] /= 127;
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
        pwm[0] = (- stick_position[0] + stick_position[1] - stick_position[3]);
        pwm[1] = (+ stick_position[0] + stick_position[1] - stick_position[3]);
        pwm[2] = (- stick_position[0] - stick_position[1] - stick_position[3]);
        pwm[3] = (+ stick_position[0] - stick_position[1] - stick_position[3]);
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

void Mech::v_goal(bool sengen)
{
    DigitalOut NeoPixel(PA_0);
    NeoPixel = sengen;
}
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