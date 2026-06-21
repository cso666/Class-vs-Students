#include "A0.h"

class stud_A4:public stud{
    public:
        stud_A4() {
            red_up -= 40, blue_up += 0, white_up += 80;
            red = red_up, blue = blue_up, white = white_up;
            att -= 5;
            be_att_mul[0].first*=1.25;
            py.push_back(15);
            ct1.push_back("Fast");        // 敏捷
            ct1.push_back("MiceShout");   // 鼠叫
            //ct1.push_back("Weak");         弱小
            ct2.push_back("SnackTheft");
            id = 4;
            name = "A04";
        }

        virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::on_turn_start(target,teach,team,beside_team);
            if(HavCt[2]){	
			for(size_t i = 0; i<beside_team.size(); i++){
                beside_team[i]->cblue(-3);
            }}
        }
        
        virtual Return_BeHit on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            Return_BeHit return_num=stud::on_before_be_atted(target, teach, team, beside_team);
            if(HavCt[1]){	
				return_num.update(pair<int,pair<double,int>>{2,make_pair(0.33,0)});
			}
            return return_num;
        }
        
        virtual void on_minus_red(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            stud::on_minus_red(target, teach, team, beside_team);    
        }
        
        virtual void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
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
class stud_A4_L:public stud{
	public:
		stud_A4_L() {
            red_up += 40, blue_up += 0, white_up += 0;
            red = red_up, blue = blue_up, white = white_up;
            att += 30;
            be_att_mul[0].first/=1.25;
            att_mul[0].first*=1.25;
            blue_mul[0].first*=0;
            white_mul[0].first*=0;
            py.push_back(15);
            HavCt[1]=1;
			HavCt[2]=1;
			HavCt[0]=1;
            ct1.push_back("Fast");        // 敏捷
            ct1.push_back("MiceShout");   // 鼠叫
            //ct1.push_back("Weak");         弱小
            ct2.push_back("SnackTheft");
            id = 4+100;
            name = "A04-L";
        }
        Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(red<red_up*0.5){
				tmp_att_plus.push_back({red_up-red,0});
				return return_num;
			}
			return return_num;
		}
		Return_BeHit on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            Return_BeHit return_num=stud::on_before_be_atted(target, teach, team, beside_team);
            if(HavCt[1])if(rand() % 3 == 1) {
                tmp_att_plus.push_back({10,3});     
            }
            return return_num;
        }
};
