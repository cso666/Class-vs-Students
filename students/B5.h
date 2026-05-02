#include "A0.h"

class stud_B5:public stud{
	public:
		bool B5emo=0,B5GoHome=0;  // 从A0移入
		
		stud_B5(){
			red_up+=2,blue_up+=6,white_up-=0;
			red=red_up,blue=blue_up,white=white_up;
			B5emo=0;B5GoHome=0;
			att-=1;
			ct2.pb("GoHome");//回家
			ct1.pb("pi2gu4");//
			ct1.pb("emo");//
			id=18;
			name="B05";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if(B5emo&&rand()%100<40){return 1;}
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			if(B5emo&&rand()%5==1){
				int qx=get_att()*(*target).get_be_att_mul();
				target -> cred(qx);
			}		
		}
		
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(rand()%5<2){
				cred(rand()%21-10);
				cblue(rand()%21-10);
				cwhite(rand()%21-10);
			}
			if(blue_up*0.6>blue&&!B5emo){
				B5emo=1;
				be_att_mul.push_back({0.6,0x7f7f7f7f});
			}
			if(blue_up*0.6<=blue&&B5emo){
				B5emo=0;
				// 移除0.6倍率
				for(int i=0;i<be_att_mul.size();i++){
					if(be_att_mul[i].first==0.6){
						be_att_mul.erase(be_att_mul.begin()+i);
						break;
					}
				}
			}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-10);
			B5GoHome=1;
			can_act=0;
		}
		
		void on_fight_end(){
			if(B5GoHome){
				can_act=1;
				cant_act=-1;
				B5GoHome=0;
			}
		}
};