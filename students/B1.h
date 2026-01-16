#include "A0.h"

class stud_B1:public stud{
	public:
		stud_B1(){
			red_up-=0,blue_up-=4,white_up-=12;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			ct1.pb("CatGirl");//猫娘
			ct1.pb("Nimble");//轻巧
			ct1.pb("BecomeRed");//红温
			ct1.pb("2085");//魔怔
			id=14;
			name="B01";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::before_att(target,teach,team,beside_team);
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);			
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_before_be_atted(target,teach,team,beside_team);			
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
		}
};
