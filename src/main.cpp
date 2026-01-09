#include "mech.hpp"
#include "mbed.h"
#include <map>

constexpr int penguin_number = 0; //5個目のFPid指定
constexpr uint32_t fp_id_1 = 40; // fpのid指定
constexpr uint32_t fp_id_2 = 30; //5個目のFPid指定
constexpr int mech_can_id = 2;      // 丼モタのid指定
CAN can1(PB_12, PB_13, (int)1e6);
CAN can2(PA_11, PA_12, (int)1e6);
CANMessage msg1;
CANMessage msg2;
Mech mech;
FirstPenguin penguin(fp_id_1, can1); // PA_3,PA_2,PA_10,PB_3
FirstPenguin fp(fp_id_2, can2);
int16_t pwm[4] = {};

// char buf[16] = {};
// DigitalIn button(BUTTON1, PullUp); // Userbutton

// map<string, int> Status = {{"BELT", 0}, {"SINGLE_ARM", 1}, {"DOUBLE_ARM", 2}, {"RACK", 3}}; // すてーたすの作成

int main()
{
    while (true)
    {
        mech.move(penguin.pwm); //足回り
        mech.yume_belt(pwm[0]);
        mech.taityo_arm(pwm[1], pwm[2]);
        mech.taityo_rack(pwm[3]);
        mech.nabe_link(fp.pwm[penguin_number]);
        // for(int i = 0; i < 4; i++){
            // penguin.pwm[i] = -50;
        // }
        // fp.pwm[3] = 50;

        penguin.send(); // 足回り値の送信
        fp.send(); //本丸値の送信
        CANMessage msg(mech_can_id, (const uint8_t *)pwm, 8);
        can1.write(msg);
    }
}
