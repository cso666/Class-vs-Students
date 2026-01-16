#include "A0.h"
#include <cstdlib>

#undef cnl
#define cnl 2147483647

class stud_A4 : public stud {
public:
    stud_A4() {
        red_up -= 40, blue_up += 0, white_up += 0;
        red = red_up, blue = blue_up, white = white_up;
        att -= 5;
        be_att_mul = 1.25;
        py.push_back(15);
        ct1.push_back("Fast");        // 敏捷
        ct1.push_back("MiceShout");   // 鼠叫
        ct1.push_back("Weak");        // 弱小
        
        // 修复随机数语法
        if((rand() % 200) == 78) {  // 原: rand()*rand()%200==78
            ct1.push_back("GodPower");  // 超能力者
            red_up = cnl;
            red = cnl;
            blue_up = cnl;
            blue = cnl;
            white_up = cnl;
            white = cnl;
        }
        id = 4;
        name = "A04";
    }
    
    // 修复1: 返回int（匹配基类）
    int before_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::before_att(target, teach, team, beside_team);
        
        // 修复2: 正确的循环语法
        for(size_t i = 0; i < beside_team.size(); i++) {
            beside_team[i]->blue -= 3;
        }
        
        return 0;  // 必须返回int
    }
    
    void after_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::after_att(target, teach, team, beside_team);        
    }
    
    // 修复3: 返回int（匹配基类）
    int on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::on_before_be_atted(target, teach, team, beside_team);
        
        // 修复4: 正确的循环语法
        for(size_t i = 0; i < beside_team.size(); i++) {
            beside_team[i]->blue -= 3;
        }
        
        // 修复5: 确保所有路径都有返回值
        if(rand() % 3 == 1) {
            return 1;        
        }
        
        return 0;  // 必须确保所有路径都返回int
    }
    
    void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::on_minus_red(target, teach, team, beside_team);    
    }
};
