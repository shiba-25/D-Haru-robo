#include "MOTOR.hpp"
#include "FIRSTPENGUIN.hpp"
#include "mbed.h"

constexpr uint32_t can_id = 35;

BufferedSerial pc(USBTX, USBRX, 115200);
CAN can(PA_11, PA_12, (int)1e6);
CANMessage msg;

FirstPenguin penguin(can_id, can);

DigitalIn front_limit(PA_3, PullUp); // PA_3,PA_2,PA_10,PB_3
DigitalIn back_limit(PA_2, PullUp);
DigitalIn right_limit(PA_10, PullUp);
DigitalIn left_limit(PB_3, PullUp);

void Wheel::front_move()
{
    if (front_limit)
    {
        int wheel_motor[4] = {-1, -1, 1, 1};
        for (int i; i < 4; i++)
        {
            penguin.pwm[i] = wheel_power * wheel_motor[i];
        }
        penguin.send();
    }
    else
    {
        automatic += 1;
    }
}

void Wheel::back_move()
{
    if (back_limit)
    {
        int wheel_motor[4] = {1, 1, -1, -1};
        for (int i; i < 4; i++)
        {
            penguin.pwm[i] = wheel_power * wheel_motor[i];
        }
        penguin.send();
    }
    else
    {
        automatic += 1;
    }
}

void Wheel::right_move()
{
    if (right_limit)
    {
        int wheel_motor[4] = {-1, 1, 1, -1};
        for (int i; i < 4; i++)
        {
            penguin.pwm[i] = wheel_power * wheel_motor[i];
        }
        penguin.send();
    }
    else
    {
        automatic += 1;
    }
}

void Wheel::left_move()
{
    if (left_limit)
    {
        int wheel_motor[4] = {1, -1, -1, 1};
        for (int i; i < 4; i++)
        {
            penguin.pwm[i] = wheel_power * wheel_motor[i];
        }
        penguin.send();
    }
    else
    {
        automatic += 1;
    }
}

void Wheel::stop_move()
{
    for (int i; i < 4; i++)
    {
        penguin.pwm[i] = wheel_stop;
    }
    penguin.send();
}