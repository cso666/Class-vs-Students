#include "A0.h"

class stud_B11:public stud{
	public:
		stud_B11(){
			red_up+=4,blue_up+=0,white_up+=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			py.push_back(8);
			py.push_back(14);
			ct1.pb("Defections");//叛变
			ct1.pb("Guest");//嘉宾
			ct1.pb("OneMoreFoot");//差一脚 One不能接Feet!!
			ct1.pb("SongsTalent");//歌喉
			id=24;
			name="B11";
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
