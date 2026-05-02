#include "A0.h"

class stud_B7:public stud{
	public:
		stud_B7(){
			white_mul[0].first*=1.3;
			red_up+=4,blue_up-=14,white_up+=6;
			red=red_up,blue=blue_up,white=white_up;
			att+=1;
			py.push_back(14);
			ct1.push_back("CowStrength");//牛劲
			ct1.push_back("Digniu");//东格牛 ?
			//ct1.push_back("Defections");//叛变
			ct1.push_back("BothHigh&Cold");//又高又冷
			id=20;
			name="B07";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
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
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			blue_mul.clear();blue_mul.push_back({1.0,0x7f7f7f7f});
			red_mul.clear();red_mul.push_back({1.0,0x7f7f7f7f});
			white_mul.clear();white_mul.push_back({1.3,0x7f7f7f7f});
			att_mul.clear();att_mul.push_back({1.0,0x7f7f7f7f});
			be_att_mul.clear();be_att_mul.push_back({1.0,0x7f7f7f7f});
			tmp_att_plus.clear();tmp_att_plus.push_back({0,0x7f7f7f7f});
			can_act=true;
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
		}
};