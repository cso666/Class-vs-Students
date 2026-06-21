#include"A0.h"

class stud_A1:public stud{
	public:
		void*sour_lemon;
		bool is_plusatt=0;
		
		stud_A1(){
			sour_lemon=NULL;
			red_up+=25,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			white_mul[0].first*=1.25;
			att+=3;
			py.push_back(15);
			py.push_back(3);
			py.push_back(10); 
			py.push_back(9);
			ct1.push_back("SmallYun");//小运
			ct2.push_back("LemonSoSour");//柠檬强酸
			ct1.push_back("Tired");//劳累
			id=1;
			name="A01";
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(HavCt[1]){
			if((rand()*rand())%100<7){
				tmp_att_plus.push_back({5,0});
				if(HavCt[2]){
					(*target).can_act=false;
					(*target).cant_act++;	
				}
				is_plusatt=1;
			}	
			}
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);			
		}
		
		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);		
			return return_num;
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-5);
			cred(-30);
			sour_lemon=target;
			target->red_up-=15;
			target->red=min(target->red,target->red_up);
		}
		
		void on_fight_end(){
			if(sour_lemon!=NULL){
				((stud*)sour_lemon)->red_up+=15;
				sour_lemon=NULL;
			}
		}
};
