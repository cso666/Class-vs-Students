#include "A0.h"

class stud_B7:public stud{
	public:
		stud_B7(){
			red_up+=4,blue_up-=14,white_up+=6;
			red=red_up,blue=blue_up,white=white_up;
			att+=1;
			py.push_back(14);
			ct1.push_back("CowStrength");//牛劲
			ct1.push_back("Digniu");//东格牛 ?
			ct1.push_back("Defections");//叛变
			ct1.push_back("BothHigh&Cold");//又高又冷
			id=20;//竟然有彩蛋！！！
			name="B07";
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
