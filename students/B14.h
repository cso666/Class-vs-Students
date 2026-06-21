#include "A0.h"

class stud_B14:public stud{
	public:
		int cnt_hitme;
		
		stud_B14(){
			cnt_hitme=2;
			red_up-=24,blue_up+=8,white_up-=10;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			ct1.pb("Baby");//宝宝
			ct2.pb("Self-healing");//自愈
			ct1.pb("Sorry");//抱歉
			id=27;
			name="B14";
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
			
		}
		
		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			if(HavCt[1]){return_num.update(pair<int,pair<int,int>>{1,{10,0}});}
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
			cnt_hitme++;
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(HavCt[2]){
				
				int tmp_tmp_att_plus=get_tmp_att_plus();
				if(blue<60){
					if(att+tmp_tmp_att_plus-3>=0){
						tmp_att_plus[0].first-=3;
						att_mul.push_back({1+cnt_hitme*0.05,0x7f7f7f7f});
					}
				}	
			}
			
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			int sbhc=rand()*rand()%3;
				if(sbhc==1)cred(6);
				else if(sbhc==2)cwhite(6);
				else cblue(6);
			int rzhc=rand()*rand()%team.size();
				if(sbhc==1)(*team[rzhc]).cred(6);
				else if(sbhc==2)(*team[rzhc]).cwhite(6);
				else (*team[rzhc]).cblue(6);
		}
};
