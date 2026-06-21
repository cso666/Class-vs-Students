#include "A0.h"

class stud_B5:public stud{
	public:
		bool B5emo=0,B5GoHome=0;  // 从A0移入
		
		stud_B5(){
			red_up+=21,blue_up+=6,white_up-=0;
			red=red_up,blue=blue_up,white=white_up;
			B5emo=0;B5GoHome=0;
			att-=1;
			ct2.pb("GoHome");//回家
			ct1.pb("pi2gu4");//
			ct1.pb("emo");//
			id=18;
			name="B05";
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(HavCt[2]){if(B5emo&&rand()%100<40){return_num.update(pair<int,pair<double,int>>{2,{1.0,0}});}
			}
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			if(HavCt[2]){
			if(B5emo&&rand()%5==1){
				be_att_mul[0].first*=0.8;
			}}		
		}
		
		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
			if(HavCt[1]){
				if(red<=0)
				for(auto y:team){
					(*y).tmp_att_plus.push_back({get_att()/10,30});
				}
				else
				tmp_att_plus.push_back({2,5});
			}
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(HavCt[2]){
			if(blue_up*0.6>blue&&!B5emo){
				B5emo=1;
				be_att_mul.push_back({0.6,0x7f7f7f7f});
			}}
			if(HavCt[2]){
			if(blue_up*0.6<=blue&&B5emo){
				B5emo=0;
				// 移除0.6倍率
				for(int i=0;i<be_att_mul.size();i++){
					if(be_att_mul[i].first==0.6){
						be_att_mul.erase(be_att_mul.begin()+i);
						break;
					}
				}
			}}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-10);
			cred(-60);
			B5GoHome=1;
			be_att_rt.update(pair<int,pair<double,int>>{2,{1.0,(Dtee().first.second==8?5:3)-Dtee().second}});
			cant_act+=21;
			can_act=0;
		}
		
		void on_fight_end(){
			if(B5GoHome){
				can_act=1;
				cant_act=-1;
				B5GoHome=0;
				cred(60);
			}
		}
};
