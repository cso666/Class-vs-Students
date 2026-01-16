#include "A0.h"

class stud_B9:public stud{
	public:
		stud_B9(){
			red_up+=3,blue_up+=0,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(4);
			ct1.pb("Adonis");//男神
			ct1.pb("Sad");//伤感
			ct2.pb("Perfect…Miss…");//成也…败也…
			id=22;
			name="B09";
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
