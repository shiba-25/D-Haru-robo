#include "mbed.h"
#include <iostream>
#include <map>

int buf_index = 0;
int conai = 0;
bool stick = false;
char buf[64];
int counter = 0;

class controller {
public:
    static std::map<std::string, int> btton_value;
    static std::map<std::string, float> stick_value;
};

std::map<std::string, float> controller::stick_value = {
    {"lx", 0.0},
    {"ly", 0.0},
    {"rx", 0.0},
    {"ry", 0.0}};

std::map<std::string, int> controller::btton_value = {
    {"L1", false},
    {"L2", false},
    {"L3", false},
    {"R1", false},
    {"R2", false},
    {"R3", false},
    {"PS", false},
    {"SH", false},
    {"OP", false},
    {"u", false},
    {"d", false},
    {"l", false},
    {"r", false},
    {"ci", false},
    {"cr", false},
    {"tri", false},
    {"sq", false}};

BufferedSerial pc(USBTX, USBRX, 115200);
std::string last;

void btn_check()
{
    // 判定を行うラムダ（キー文字列を受け取り、on/off を判定して map を更新）
    auto set_if = [&](const std::string &key)
    {
        const std::string on = key + ":p";
        const std::string off = key + ":no_p";
        if (last.rfind(on, 0) == 0)
        { // 先頭一致 (on)
            controller::btton_value[key] = true;
        }
        else if (last.rfind(off, 0) == 0)
        { // 先頭一致 (off)
            controller::btton_value[key] = false;
        }
    };

    // 全キーに対してラムダを適用
    for (auto &kv : controller::btton_value)
    {
        set_if(kv.first);
    }
}
void stick_in()
{
    float read_value = 0;
    // printf("%f\n", std::stof(buf));
    if (std::stof(buf) > 0.1 || std::stof(buf) < -0.1)
    {
        read_value = std::stof(buf);
    }

    if (counter == 0)
    {
        controller::stick_value["lx"] = read_value;
    }
    else if (counter == 1)
    {
        controller::stick_value["ly"] = read_value;
    }
    else if (counter == 2)
    {
        controller::stick_value["rx"] = read_value;
    }
    else if (counter == 3)
    {
        controller::stick_value["ry"] = read_value;
    }
}

// コントローラー読み取り関数
void read_controller()
{
    if (pc.readable())
    {
        conai = 0;
        char c;
        int num = pc.read(&c, 1);
        if (num > 0)
        {
            if (c == '|' || c == ':')
            {
                last.assign(buf, buf_index);
                if (c == '|')
                {
                    buf_index = 0;
                    if (stick == true)
                    {
                        stick = false;
                        stick_in();
                        counter = 0;
                    }
                    btn_check();
                }
                else
                {
                    if (stick == true)
                    {
                        stick_in();
                        buf_index = 0;
                        counter++;
                    }
                    else if (last == "n")
                    {
                        stick = true;
                        buf_index = 0;
                    }
                    else
                    {
                        buf[buf_index++] = c;
                    }
                }
            }
            else if (buf_index < sizeof(buf) - 1)
            {
                buf[buf_index++] = c;
            }
        }
    }else{
        conai++;
        if(conai>1000){
            controller::stick_value["lx"] = 0;
            controller::stick_value["ly"] = 0;
            controller::stick_value["rx"] = 0;
            controller::stick_value["ry"] = 0;
            controller::btton_value["L1"] = 0;
            controller::btton_value["L2"] = 0;
            controller::btton_value["R1"] = 0;
            controller::btton_value["R2"] = 0;
            controller::btton_value["L3"] = 0;
            controller::btton_value["R3"] = 0;
            controller::btton_value["PS"] = 0;
            controller::btton_value["SH"] = 0;            
            controller::btton_value["OP"] = 0;
            controller::btton_value["u"] = 0;  
            controller::btton_value["d"] = 0;       
            controller::btton_value["l"] = 0;  
            controller::btton_value["r"] = 0;  
            controller::btton_value["ci"] = 0;  
            controller::btton_value["cr"] = 0;  
            controller::btton_value["tri"] = 0;  
            controller::btton_value["sq"] = 0;  
        }
    }
}