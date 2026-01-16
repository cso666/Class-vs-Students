#include "A0.h"

class stud_B10:public stud{
	public:
		stud_B10(){
			red_up-=4,blue_up-=20,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=3;
			ct1.pb("Subjective");
			ct1.pb("Shouldn't...");
			id=23;
			name="B10";
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
