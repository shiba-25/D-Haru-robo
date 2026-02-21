#include "FIRSTPENGUIN.hpp"

bool FirstPenguin::plus_send()
{
    return plus_can.write(CANMessage{send_id, reinterpret_cast<const uint8_t *>(pwm), 8});
}

bool FirstPenguin::minus_send()
{
    for(int i = 0; i < 4; i++)
    {
        pwm[i] *= -1;
    }
    return minus_can.write(CANMessage{send_id, reinterpret_cast<const uint8_t *>(pwm), 8});
}

void FirstPenguin::read(const CANMessage &msg)
{
    if (msg.format == CANStandard && msg.type == CANData && msg.len == sizeof(receive[0]) && send_id < msg.id && msg.id <= send_id + 5)
    {
        receive[msg.id - send_id - 1].set(msg.data);
    }
}
