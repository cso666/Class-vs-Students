#include "A0.h"

class stud_B15:public stud{
	public:
		stud_B15(){
			red_up+=2,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=2; 
			py.push_back(2);
			ct2.pb("PerfectRain");//好雨
			ct1.pb("HitUpFlowerFire");//打上花火
			id=28;
			name="B15";
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
