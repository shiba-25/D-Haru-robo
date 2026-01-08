#include "mech.hpp"
#include "read_controller.hpp"
#include "mbed.h"
#include <map>


int penguin_number = 0;
constexpr uint32_t fp_send_id = 30; // fpのid指定
constexpr int mech_can_id = 2; // 丼モタのid指定
CAN can(PB_12, PB_13, (int)1e6);
CANMessage msg;
Mech mech;
FirstPenguin penguin(fp_send_id, can); // PA_3,PA_2,PA_10,PB_3


// char buf[16] = {};
DigitalIn button(BUTTON1, PullUp); // Userbutton

map<string, int> Status = {{"FRONT", 0}, {"BACK", 1}, {"RIGHT", 2}, {"LEFT", 3}}; //すてーたすの作成



int main()
{
    while (true)
    {
        mech.move(1, 0, 0, 1, penguin.wheel_pwm);

        penguin.send(); // 値の送信
        CANMessage msg(mech_can_id, (const uint8_t *)penguin.wheel_pwm, 8);
        can.write(msg);
    }
}
