#include "mech.hpp"
#include "mbed.h"
#include <iostream>
#include <map>
#include "controller.hpp"
// #include "pid.hpp"
// #include "sensor.hpp"
// #include "pid/pid.hpp"
// #define limit_1 PB_8
// constexpr float p_gain = 0;
// constexpr float i_gain = 0;
// constexpr float d_gain = 0;
constexpr int penguin_number = 0; //5個目のFPid指定
constexpr uint32_t fp_id_1 = 30; // fpのid指定
constexpr uint32_t fp_id_2 = 35; //5個目のFPid指定
constexpr int mech_can_id = 2;      // 丼モタのid指定
bool fast_check = 1;
int dt = 100;
// int o = 1;
int16_t encoder_initial[4] = {0};
int16_t encoder_value[4] = {0, 0, 0, 0};
CAN plus_can(PB_12, PB_13, (int)1e6);
CAN minus_can(PA_11, PA_12, (int)1e6);
CANMessage msg;
Mech mech(1);
FirstPenguin penguin(fp_id_1, plus_can, minus_can); // PA_3,PA_2,PA_10,PB_3
FirstPenguin fp(fp_id_2, plus_can, minus_can);
controller ctl;

// struct PidGain
// {
//     float kp = 1.0;
//     float ki = 0.0;
//     float kd = 0.0;
// };
// Pid pid;
int16_t pwm[4] = {};
bool is_limit[5] = {1,1,1,1,1};

// char buf[16] = {};
DigitalIn button(BUTTON1, PullUp); // Userbutton
bool hobo_ticker(int ms, int timer_num)
{
    static Timer timer[2];
    static bool started[2] = {false};
    if (!started[timer_num])
    {
        timer[timer_num].start();
        started[timer_num] = true;
    }
    if (timer[timer_num].read_ms() >= ms)
    {
        timer[timer_num].reset();
        return true;
    }
    else
    {
        return false;
    }
}

void read_encoder(int16_t (&encoder)[4])
{
    plus_can.read(msg);
    penguin.read(msg);
    if (fast_check)
    {
        encoder_initial[0] = penguin.receive[0].enc;
        encoder_initial[1] = penguin.receive[1].enc;
        encoder_initial[2] = penguin.receive[2].enc;
        encoder_initial[3] = penguin.receive[3].enc;
    }
    else
    {
        encoder[0] = penguin.receive[0].enc - encoder_initial[0];
        encoder[1] = penguin.receive[1].enc - encoder_initial[1];
        encoder[2] = penguin.receive[2].enc - encoder_initial[2];
        encoder[3] = penguin.receive[3].enc - encoder_initial[3];
    }
}

// void encoder_reset(int16_t (&encoder)[4])
// {
    // ThisThread::sleep_for(1s);
    // encoder[0] = 0;
    // encoder[1] = 0;
    // encoder[2] = 0;
    // encoder[3] = 0;
// }

// void read_limit(bool (&is_sw_push)[5])
// {
//     if(plus_can.read(msg); msg.id == 11){
//         uint8_t sw = msg.data[5]; //スイッチの値の内容
//         for(int i = 0; i < 5; i++){
//             //シフトで判別する位を最下位ビットへ移動し、1と論理積を行うことで各位の値を判別する。
//                 is_sw_push[i] = (sw >> i) & 0x01;
//         }
//     }
// }

// map<string, int> Status = {{"BELT", 0}, {"SINGLE_ARM", 1}, {"DOUBLE_ARM", 2}, {"RACK", 3}}; // すてーたすの作成


int main()
{
    // pid::PidParameter param = {
    // .gain = {.kp = 1.0f, .ki = 0.1f, .kd = 0.01f},
    // .min = -100.0f,
    // .max = 100.0f,
    // };
    // pid::Pid pid(param);
    // pid.reset();
    DigitalOut NeoPixel(PA_0);
    while (true)
    {

        // penguin.encoder_read(mech.encoder);
        // penguin.pwm_read(mech.pwm);
        read_controller();
        read_encoder(encoder_value);
        // read_limit(is_limit);
        // fast_check = 0;
        // int a[6] = {1,0,0,0,0,0};
        bool is_move[4] = {ctl.btton_value["u"],ctl.btton_value["d"],ctl.btton_value["r"],ctl.btton_value["l"]};
        bool is_belt[4] = {ctl.btton_value["ci"],ctl.btton_value["cr"], ctl.btton_value["tri"], ctl.btton_value["sq"]};
        bool is_arm[2] = {ctl.btton_value["L1"], ctl.btton_value["R1"]};
        bool is_rack[2] = {ctl.btton_value["R2"], ctl.btton_value["L2"]};
        bool is_nebaru[2] = {ctl.btton_value["SH"], ctl.btton_value["OP"]};
        float stick_position[4] = {ctl.stick_value["ly"], ctl.stick_value["lx"], ctl.stick_value["rx"]};
        mech.move(is_move, stick_position, penguin.pwm, encoder_value); //足回り
        mech.nebaarukun(is_nebaru, fp.pwm[penguin_number]);
        mech.yume_belt(is_belt, pwm[0]);
        mech.taityo_arm(is_arm, pwm[1], pwm[2]);
        mech.taityo_rack(is_rack, pwm[3]);
        // bool is_vgoal = controller["PS"];
        // mech.v_goal(is_vgoal);
        // for(int i = 0; i < 4; i++){
            // penguin.pwm[i] = -50;
            // }
            // fp.pwm[0] = 3
            if (hobo_ticker(dt, 0))
            {
                // penguin.pwm[0] = 30;
                // encoder_reset(encoder_value);
                if(ctl.btton_value["PS"] == 1)
                {
                    NeoPixel = 1;
                    fast_check = 0;
                }
                else
                {
                    NeoPixel = 0;
                }
            }
            static int dbg_cnt = 0;
            if (++dbg_cnt % 50 == 0)
            {
                // printf("pwm: %d", penguin.pwm[0]);
                // printf("enc: %d, %d, %d, %d enc_init: %d, %d, %d, %d\n", encoder_value[0], encoder_value[1], encoder_value[2], encoder_value[3], encoder_initial[0], encoder_initial[1], encoder_initial[2], encoder_initial[3]);
                // printf("pwm: %d, %d, %d, %d\n", penguin.pwm[0], pwm[1], pwm[2], pwm[3]);
                // printf("limit: %d\n", limit);
                // printf("stick: %f, %f, %f", stick_value["lx"], stick_value["ly"], stick_value["rx"]);
            }
        // if(plus_can.read(msg); msg.id == 12){ //ID10のCANメッセージを抽出
        
        //     int16_t enc = msg.data[1] << 8 | msg.data[0]; //受け取った2byteのデータを結合
        //     const float k = 360.0 / (256.0 * 2.0); //Revolution / (PPR * 2)
        //     int deg = enc * k; //角度に変2

        //     printf("Message received: %d, %d\n", enc, deg);
        // }
        // bool is_sw_push[5];  //スイッチが押されているか

        // if(plus_can.read(msg); msg.id == 13)
        // {
        //     uint8_t sw = msg.data[5]; //スイッチの値の内容
        //     for(int i = 0; i < 5; i++)
        //     {
        //         is_sw_push[i] = (sw >> i) & 0x01;
        //         //シフトで判別する位を最下位ビットへ移動し、1と論理積を行うことで各位の値を判別する。
        //     }
        //     printf("swbit: %d, %d, %d, %d, %d\n", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4]);
        //     printf("Switch: %d, %d, %d, %d, %d\n", is_sw_push[4], is_sw_push[3], is_sw_push[2], is_sw_push[1], is_sw_push[0]);
        // }
        
        // if (is_sw_push[0])
        // {
        //     penguin.pwm[0] = 100;
        // }
        // else if (is_sw_push[4])
        // {
        //     penguin.pwm[1] = 100;
        // }

        // if (penguin.pwm[0] > 8000)
        // {
        //     penguin.pwm[0] = 8000;
        // }
        // else if (penguin.pwm[0] < -8000)
        // {
        //     penguin.pwm[0] = -8000;
        // }

        penguin.plus_send(); // 足回り値の送信
        penguin.minus_send();
        fp.plus_send();
        fp.minus_send(); //本丸値の送信
        CANMessage msg(mech_can_id, (const uint8_t *)pwm, 8);
        plus_can.write(msg);
        minus_can.write(msg);

    }
}
