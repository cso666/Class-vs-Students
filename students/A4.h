#include "A0.h"

class stud_A4:public stud{
    public:
        stud_A4() {
            red_up -= 40, blue_up += 0, white_up += 0;
            red = red_up, blue = blue_up, white = white_up;
            att -= 5;
            be_att_mul[0].first*=1.25;
            py.push_back(15);
            ct1.push_back("Fast");        // 敏捷
            ct1.push_back("MiceShout");   // 鼠叫
            ct1.push_back("Weak");        // 弱小
            id = 4;
            name = "A04";
        }

        void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::on_turn_start(target,teach,team,beside_team);
            for(size_t i = 0; i<beside_team.size(); i++){
                beside_team[i]->cblue(-3);
            }
        }
        
        int on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            int return_num=stud::on_before_be_atted(target, teach, team, beside_team);
            if(rand() % 3 == 1) {
                return 1;        
            }
            return return_num;
        }
        
        void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            stud::on_minus_red(target, teach, team, beside_team);    
        }
        
        void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::skhit(target,teach,team,beside_team);
            cwhite(-20);
            int final_att=(7*get_att())*(target -> get_be_att_mul());
            if(final_att<=12){
                target->cred(final_att);
            }
            else if(final_att>12){
                target->cred(-12);
            }
        }
};