#include "A0.h"

class stud_A6 : public stud {
    public:
        void* James;  // 从A0移入
        
        stud_A6() {
            James=NULL;
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
            int return_num=stud::before_att(target, teach, team, beside_team);
            for(auto prop : target->py) {
                if(prop == 15) {
                    att_mul.push_back({1.1,1});
                    break;
                }
            }
            return return_num;
        }
        
        void after_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            stud::after_att(target, teach, team, beside_team);           
        }
        
        int on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            int return_num=stud::on_before_be_atted(target, teach, team, beside_team);
            for(auto prop : target->py) {
                if(prop == 15) {
                    be_att_mul.push_back({0.78,1});
                    break;
                }
            }
            return return_num;
        }
        
        void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            stud::on_minus_red(target, teach, team, beside_team);    
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
            target -> be_att_mul.push_back({1.2,1});
            James=target;
        }
        
        void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::on_turn_end(target,teach,team,beside_team);
            if(James!=NULL){
                James = NULL;
            }
        } 
};