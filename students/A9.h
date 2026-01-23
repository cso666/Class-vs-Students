#include "A0.h"

class stud_A9:public stud{
	public:
		stud_A9(){
			red_up-=15,blue_up+=80,white_up+=10;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(15);
			ct1.push_back("MrMonitor");//班长大人
			//(Ori: ClassLongBigHuman?????)
			ct1.push_back("Peacemaker");//劝架使者
			//(Ori: DaNiMaNe??????????????)
			ct1.push_back("AbundantSupport");//多助之至
			//(Ori: AllMyPeople???????????)
			ct2.push_back("FindOut");//太守寻源
			id=9;
			name="A09";
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
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			for(auto x:team){
				(*x).att_mul*=1.35;
			}
		}
		void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			for(auto x:team){
				(*x).att_mul/=1.35;
			}
		}
};
