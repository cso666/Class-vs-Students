#include "A0.h"

class stud_B1:public stud{
	public:
		stud_B1(){
			red_up+=5,blue_up+=20,white_up-=12;
			red=red_up,blue=blue_up,white=white_up;
			be_att_mul=0.75;
			att-=2;
			ct1.pb("CatGirl");//猫娘
			ct1.pb("Nimble");//轻巧
			ct1.pb("2085");//魔怔
			id=14;
			name="B01";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			cwhite(1);		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			if((target -> id)==20)be_att_mul=1.0;
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			be_att_mul=0.75;
		}
};
