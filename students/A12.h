#include "A0.h"

class stud_A12: public stud{
	public:
		stud_A12(){
			red_up+=10;blue_up+=10;white_up-=20;
			red=red_up;blue=blue_up;white=white_up;
			att+=0;
			py.push_back(15);
			ct1.pb("EatWell");//我吃好了
			ct1.pb("YouXianglinSao");//并非蠢货 （何意味？？
			ct1.pb("YogHURT");//酸奶
			ct2.pb("EnchantedGoldenApple");//附魔金苹果
			id=12;
			name="A12";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::before_att(target,teach,team,beside_team);
			if((*target).id==8){
				int final_att=(att*att_mul*(*target).be_att_mul+tmp_att_plus);
				for(auto x:beside_team){
					(*x).red-=final_att*0.10;
				}
			}	
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
				stud::after_att(target,teach,team,beside_team);		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_before_be_atted(target,teach,team,beside_team);	
			be_att_mul*=max((150.0-blue)/150.0,1.0);		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
			be_att_mul*=max((150.0-blue)/150.0,1.0);
		}
};
