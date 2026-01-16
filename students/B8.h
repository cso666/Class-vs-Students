#include "A0.h"

class stud_B8:public stud{
	public:
		stud_B8(){
			red_up+=8,blue_up-=2,white_up+=4;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(14);
			ct1.pb("Defections");//叛变
			ct1.pb("BreachOfFaith");//
			ct2.pb("YouKongyiJi");//孔乙己
			ct1.pb("WantFight?");//打架吗
			id=21;
			name="B08";
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
