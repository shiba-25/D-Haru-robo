#include "mech.hpp"
#include "mbed.h"
#include <map>
#include "controller.hpp"

// constexpr float p_gain = 0;
// constexpr float i_gain = 0;
// constexpr float d_gain = 0;
constexpr int penguin_number = 0; //5個目のFPid指定
constexpr uint32_t fp_id_1 = 30; // fpのid指定
constexpr uint32_t fp_id_2 = 35; //5個目のFPid指定
constexpr int mech_can_id = 2;      // 丼モタのid指定
CAN plus_can(PB_12, PB_13, (int)1e6);
CAN minus_can(PA_11, PA_12, (int)1e6);
CANMessage msg1;
CANMessage msg2;
Mech mech(1);
FirstPenguin penguin(fp_id_1, plus_can, minus_can); // PA_3,PA_2,PA_10,PB_3
FirstPenguin fp(fp_id_2, plus_can, minus_can);
// Pid pid({p_gain, i_gain, d_gain});
int16_t pwm[4] = {};

// char buf[16] = {};
// DigitalIn button(BUTTON1, PullUp); // Userbutton

// map<string, int> Status = {{"BELT", 0}, {"SINGLE_ARM", 1}, {"DOUBLE_ARM", 2}, {"RACK", 3}}; // すてーたすの作成


int main()
{
    // pid.reset();
    while (true)
    {
        // penguin.encoder_read(mech.encoder);
        // penguin.pwm_read(mech.pwm);
        read_controller();
        // int a[6] = {1,0,0,0,0,0};
        bool is_move[6] = {controller["u"],controller["d"],controller["r"],controller["l"],controller["SH"],controller["OP"]};
        bool is_belt[4] = {controller["tri"],controller["ci"], controller["sq"], controller["cr"]};
        bool is_arm[4] = {controller["R1"], controller["L1"], controller["R2"], controller["L2"]};
        bool is_rack[2] = {controller["R3"], controller["L3"]};
        bool is_vgoal = controller["PS"];
        float stick_position[4] = {stick_value["lx"], stick_value["ly"], stick_value["ry"], stick_value["rx"]};
        mech.move(is_move, stick_position, penguin.pwm); //足回り
        // mech.slow_move(stick_position, penguin.pwm);
        mech.yume_belt(is_belt, pwm[0]);
        mech.taityo_arm(is_arm, pwm[1], pwm[2]);
        mech.taityo_rack(is_rack, pwm[3]);
        mech.v_goal(is_vgoal);
        // for(int i = 0; i < 4; i++){
            // penguin.pwm[i] = -50;
        // }
        // penguin.pwm[0] = 30;
        // fp.pwm[0] = 3000;
        // printf("lx: %f\nly: %f\nrx: %f\nry: %f\n", stick_value["lx"], stick_value["ly"], stick_value["rx"], stick_value["ry"]);

        penguin.plus_send(); // 足回り値の送信
        penguin.minus_send();
        fp.plus_send();
        fp.minus_send(); //本丸値の送信
        CANMessage msg(mech_can_id, (const uint8_t *)pwm, 8);
        plus_can.write(msg);
        minus_can.write(msg);
    }
}
