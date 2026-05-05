#include "A0.h"

class stud_B4:public stud{
	public:
		bool weidadebp=0;  // 从A0移入
		
		stud_B4(){
			red_up-=26,blue_up+=0,white_up+=64;
			red=red_up,blue=blue_up,white=white_up;
			be_att_mul[0].first=0.25;
			att+=0;
			weidadebp=0;
			
			ct2.pb("BP");//扒皮
			ct1.pb("ForeignFriend");//国际友人
			ct1.pb("LaoKing");//牢王
			ct1.pb("GeniusBEET");//甜菜
			id=17;
			name="B04";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}

		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			// 国际友人
			if(HavCt[1])if((teach==3||teach==4)&&!weidadebp){
				weidadebp=1;
				for(auto x:team){
					x->be_att_mul.push_back({0.85,0x7f7f7f7f});
				}
			}
			if(HavCt[1])if((teach!=3&&teach!=4)&&weidadebp){weidadebp=0;}
		}

		void on_fight_end(){
			if(HavCt[2]){
				cwhite(20);
				cblue(20);	
			}
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);			
		}
		
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			int final_skhit=get_att(4)*(*target).get_be_att_mul();
			target->cred(-final_skhit);
			cred(final_skhit);
		}
};
