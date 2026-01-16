#include "A0.h"

class stud_B13:public stud{
	public:
		stud_B13(){
			red_up-=20,blue_up+=20,white_up-=30;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			py.push_back(8);
			py.push_back(9);
			ct1.pb("TakeItEasy...");
			//ct1.pb("108 or lower");
			//ct1.pb("Maimai go home");
			ct1.pb("SongsAreLife!");
			ct2.pb("KnowledgeIsPowDer");
			id=26;
			name="B13";
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
