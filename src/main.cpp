#include "mech.hpp"
#include "read_controller.hpp"
#include "mbed.h"
#include <map>

int penguin_number = 0;
constexpr uint32_t fp_id_1 = 30; // fpのid指定
constexpr uint32_t fp_id_2 = 35;
constexpr int fp_send_id = 0;
constexpr int mech_can_id = 2;      // 丼モタのid指定
CAN can(PB_12, PB_13, (int)1e6);
CANMessage msg;
Mech mech;
FirstPenguin penguin(fp_id_1, can); // PA_3,PA_2,PA_10,PB_3
FirstPenguin fp(fp_id_2, can);
int16_t pwm[4] = {};

// char buf[16] = {};
// DigitalIn button(BUTTON1, PullUp); // Userbutton

// map<string, int> Status = {{"BELT", 0}, {"SINGLE_ARM", 1}, {"DOUBLE_ARM", 2}, {"RACK", 3}}; // すてーたすの作成

int main()
{
    while (true)
    {
        mech.move(controller["u"], controller["d"], controller["r"], controller["l"], penguin.pwm);
        mech.yume_belt(controller["tri"], controller["ci"], pwm[0]);
        mech.taityo_arm(controller["R1"], controller["L1"], controller["R2"], controller["L2"], pwm[1], pwm[2]);
        mech.taityo_rack(controller["R3"], controller["L3"], pwm[3]);
        mech.nabe_link(controller["sq"], controller["cr"], fp.pwm[fp_send_id]);

        penguin.send(); // 値の送信
        fp.send();
        CANMessage msg(mech_can_id, (const uint8_t *)pwm, 8);
        can.write(msg);
    }
}
