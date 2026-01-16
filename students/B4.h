#include "A0.h"

class stud_B4:public stud{
	public:
		stud_B4(){
			red_up-=26,blue_up+=0,white_up+=64;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			ct1.pb("GeniusBEET");//甜菜
			ct1.pb("BP");//扒皮
			ct1.pb("ForeignFriend");//国际友人
			ct1.pb("LaoKing");//牢王
			id=17;
			name="B04";
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
