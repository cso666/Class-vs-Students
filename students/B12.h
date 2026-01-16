#include "A0.h"

class stud_B12:public stud{
	public:
		stud_B12(){
			red_up-=4,blue_up-=0,white_up+=8;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct1.pb("HitPlane");//？王
			ct1.pb("Letsrun");//约跑
			id=25;
			name="B12";
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
