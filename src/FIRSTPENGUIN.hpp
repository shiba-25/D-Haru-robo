#ifndef FIRSTPENGUIN_H
#define FIRSTPENGUIN_H

#include <mbed.h>

class FirstPenguin
{
public:
    static constexpr int max = INT16_MAX;
    uint32_t send_id;
    int16_t pwm[4] = {};
    const int motor_power = 5000;
    int wheel_motor[4][4] = {{-1, -1, 1, 1}, {1, 1, -1, -1}, {-1, 1, 1, -1}, {1, -1, -1, 1}};

    struct ReceiveData
    {
        int32_t enc;
        uint32_t adc;
        void set(const uint8_t data[8])
        {
            memcpy(this, data, sizeof(*this));
        }
    } receive[4] = {};

    // コンストラクタ
    FirstPenguin(uint32_t id, CAN &can1, CAN &can2) : send_id(id), plus_can(can1), minus_can(can2)  {}

    // メンバーへのアクセスを可能にする関数
    const ReceiveData *getReceiveData() const { return receive; }
    int16_t *getPwmData() { return pwm; }
    bool plus_send();
    bool minus_send();
    void read(const CANMessage &msg);

private:
    CAN &plus_can;
    CAN &minus_can;
};

#endif
