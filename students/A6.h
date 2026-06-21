#include "A0.h"

class stud_A6 : public stud {
    public:
        void* James;  // 从A0移入
        int cntL;
        stud_A6() {
        	cntL=0;
            James=NULL;
            red_up -= 10, blue_up += 30, white_up += 0;
            red = red_up, blue = blue_up, white = white_up;
            att -= 0;
            py.push_back(15);
            ct1.push_back("PrisonGuard"); // 狱警
            ct1.push_back("LoseJ");       // YJ
            ct2.push_back("EarlyWarning");
            id = 6;
            name = "A06";
        }
        
        Return_Hit before_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            Return_Hit return_num=stud::before_att(target, teach, team, beside_team);
            if(HavCt[1]){
			for(auto prop : target->py) {
                if(prop == 15) {
                    att_mul.push_back({1.1,0});
                    (*target).cred(-5);
                    if(James==target)(*target).cred(-5);
                    break;
                }
            }
            if(James==target)(*target).cred(-5);
            for(auto y:team)
            	for(auto z:(*y).py){
            		if(z==15)cntL++;
				}
			}
            return return_num;
        }
        
        void after_att(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            stud::after_att(target, teach, team, beside_team);           
        }
        
        Return_BeHit on_before_be_atted(stud* target, int teach, vector<stud*> team, vector<stud*> beside_team) override {
            Return_BeHit return_num=stud::on_before_be_atted(target, teach, team, beside_team);
            if(HavCt[1]){
			for(auto prop : target->py) {
                if(prop == 15) {
                    be_att_mul.push_back({0.78,0});
                    break;
                }
            }}
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
            int cnttL=0;
            for(auto x:beside_team){
                for(auto y:(*x).py){
                	if(y==15)cnttL++;
				}
            }
            target -> cblue(-20);
            target -> be_att_mul.push_back({1.2,1});
            target -> cred(-5*cnttL);
            James=target;
        }
        void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::on_turn_start(target,teach,team,beside_team);
            if(HavCt[1]){
            for(auto y:beside_team){
            	(*y).cred(-1*cntL);
			}cntL=0;
			}
        } 
        void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
            stud::on_turn_end(target,teach,team,beside_team);
            if(James!=NULL){
                James = NULL;
            }
        } 
};
