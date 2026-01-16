#include "A0.h"

class stud_A6 : public stud {
public:
    stud_A6() {
        red_up -= 10, blue_up += 0, white_up += 0;
        red = red_up, blue = blue_up, white = white_up;
        att -= 0;
        py.push_back(15);
        ct1.push_back("PrisonGuard"); // 狱警
        ct1.push_back("LoseJ");       // YJ
        id = 6;
        name = "A06";
    }
    
    int before_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::before_att(target, teach, team, beside_team);
        return 0;  // 必须返回int
    }
    
    void after_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::after_att(target, teach, team, beside_team);            
    }
    
    int on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::on_before_be_atted(target, teach, team, beside_team);
        
        // 修复：检查目标是否有"牢门"属性(15)
        for(auto prop : target->py) {  // 遍历目标的属性列表
            if(prop == 15) {  // 如果目标是"牢门"属性
                be_att_mul = 0.5;  // 对该目标的伤害减半
                break;
            }
        }
        
        return 0;  // 必须返回int
    }
    
    void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::on_minus_red(target, teach, team, beside_team);    
        be_att_mul = 1.0;  // 恢复默认伤害倍率    
    }
};
