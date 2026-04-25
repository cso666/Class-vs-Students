#include "A0.h"

class stud_A6 : public stud {
public:
    stud_A6() {
        red_up -= 10, blue_up += 0, white_up += 0;
        red = red_up, blue = blue_up, white = white_up;
        att -= 0;
        James=NULL;
        py.push_back(15);
        ct1.push_back("PrisonGuard"); // 狱警
        ct1.push_back("LoseJ");       // YJ
        id = 6;
        name = "A06";
    }
    int cblue(int chg){
		if(chg<0)blue+=0;
		else blue+=chg*blue_mul_p;
		red=min(blue,blue_up);
		if(blue<0)blue=0,status=0;
		return status;
	}
    int before_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        int return_num=stud::before_att(target, teach, team, beside_team);
        for(auto prop : target->py) {  // 遍历目标的属性列表
            if(prop == 15) {  // 如果目标是"牢门"属性
                att_mul *= 1.1;  // 对该目标的伤害减半
                break;
            }
        }
        return return_num;
    }
    
    void after_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::after_att(target, teach, team, beside_team);           
		for(auto prop : target->py) {  // 遍历目标的属性列表
            if(prop == 15) {  // 如果目标是"牢门"属性
                att_mul /= 1.1;  // 对该目标的伤害减半
                break;
            }
        } 
    }
    
    int on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        int return_num=stud::on_before_be_atted(target, teach, team, beside_team);
        
        // 修复：检查目标是否有"牢门"属性(15)
        for(auto prop : target->py) {  // 遍历目标的属性列表
            if(prop == 15) {  // 如果目标是"牢门"属性
                be_att_mul *= 0.78;  // 对该目标的伤害减半
                break;
            }
        }
        
        return return_num;  // 必须返回int
    }
    
    void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
        stud::on_minus_red(target, teach, team, beside_team);    
         for(auto prop : target->py) {  // 遍历目标的属性列表
            if(prop == 15) {  // 如果目标是"牢门"属性
                be_att_mul /= 0.78;  // 对该目标的伤害减半
                break;
            }
        }  
    }
    void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		cwhite(-5);
        for(auto x:team){
            if(x -> id!=6){
                x -> cblue(5);
            }
        }
        target -> cblue(-20);
        target -> be_att_mul*=1.2;
        James=target;
	}
    void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::on_turn_end(target,teach,team,beside_team);
        if(James!=NULL){
            ((stud*)James) -> be_att_mul /= 1.2;
            James = NULL;
        }
    } 
};
