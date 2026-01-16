#include "A0.h"

class stud_B5:public stud{
	public:
		stud_B5(){
			red_up+=2,blue_up+=6,white_up-=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct2.pb("GoHome");//回家
			ct2.pb("pi2gu4");//
			ct1.pb("emo");//
			id=18;
			name="B05";
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
