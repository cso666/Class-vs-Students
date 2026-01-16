#include "A0.h"

class stud_B3:public stud{
	public:
		stud_B3(){
			red_up+=0,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			py.push_back(1);
			ct1.pb("Tutor(TA)");//助教先生
			ct1.pb("Calm&Composed");//心平气和
			ct1.pb("MathDUO");//数学双星
			id=16;
			name="B03";
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
