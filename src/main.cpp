#include "mech.hpp"
#include "mbed.h"
#include <map>
#include "controller.hpp"

constexpr int penguin_number = 0; //5個目のFPid指定
constexpr uint32_t fp_id_1 = 30; // fpのid指定
constexpr uint32_t fp_id_2 = 40; //5個目のFPid指定
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
        read_controller();
        // int a[6] = {1,0,0,0,0,0};
        bool is_move[6] = {controller["u"],controller["d"],controller["r"],controller["l"],controller["SH"],controller["OP"]};
        bool is_belt[2] = {controller["tri"],controller["ci"]};
        bool is_arm[4] = {controller["R1"], controller["L1"], controller["R2"], controller["L2"]};
        bool is_rack[2] = {controller["R3"], controller["L3"]};
        bool is_link[2] = {controller["sq"], controller["cr"]};
        mech.move(is_move, penguin.pwm, mech.is_control_change); //足回り
        mech.yume_belt(is_belt, pwm[0]);
        mech.taityo_arm(is_arm, pwm[1], pwm[2], mech.is_control_change);
        mech.taityo_rack(is_rack, pwm[3]);
        mech.nabe_link(is_link, fp.pwm[penguin_number]);
        // for(int i = 0; i < 4; i++){
            // penguin.pwm[i] = -50;
        // }
        // penguin.pwm[0] = 30;
        // fp.pwm[0] = 3000;
        // printf("lx: %f\nly: %f\nrx: %f\nry: %f\n", stick_value["lx"], stick_value["ly"], stick_value["rx"], stick_value["ry"]);

        penguin.send(); // 足回り値の送信
        fp.send(); //本丸値の送信
        CANMessage msg(mech_can_id, (const uint8_t *)pwm, 8);
        can1.write(msg);
    }
}
