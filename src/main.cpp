#include "FIRSTPENGUIN.hpp"
#include "mbed.h"

constexpr uint32_t fp_can_id = 30;
// constexpr int mech_can_id = 2;
char buf[16] = {};
DigitalIn button(BUTTON1,PullUp);
// // int num = -1;

BufferedSerial pc(USBTX, USBRX, 115200);
CAN can(PB_12, PB_13, (int)1e6);
CANMessage msg;
int penguin_number = 0;

FirstPenguin penguin(fp_can_id, can); // PA_3,PA_2,PA_10,PB_3

int main()
{
    while (true)
    {
        // printf("a\n");
        // if (pc.readable())
        // {
            // printf("pc read");
            // int n = pc.read(buf, sizeof(buf) - 1);
            // if (n > 0)
            // {
                // buf[n] = '\0';
                // if (buf[n - 1] == '\n' || buf[n - 1] == '\r')
                // {
                    // buf[n - 1] = '\0';
                // }
            // }
        // }
        // for(int i = 0; i < 4; i++){
            // penguin.wheel_pwm[i] = penguin.wheel_power * penguin.wheel_motor[0][i];
        // }
        if(button == 1){
            penguin.wheel_pwm[2] = 1000;
            penguin.send();
        } else if (button == 0){
            penguin.wheel_pwm[2] = -1000;
            penguin.send();
        } else {
            penguin.wheel_pwm[2] = 0;
            penguin.send();
        }
        // penguin.wheel_pwm[0] = 1000;
        // penguin.send();
        // move('f');
        // penguin.send();
    }
}