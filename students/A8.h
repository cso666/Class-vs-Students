#include "A0.h"

class stud_A8:public stud{
	public:
		stud_A8(){
			red_up+=0,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			py.push_back(15);
			ct1.push_back("TurtleLivesLong");//神龟虽寿
			ct1.push_back("BrainStorm");//头脑风暴
			ct1.push_back("SixbleAp");//六重A+
			ct2.push_back("LowDHit");//降维打击(D -> demension)
			
			id=8;
			name="A08";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::before_att(target,teach,team,beside_team);
			if(red==red_up&&blue==blue_up&&white==white_up){
				tmp_att_plus+=2;
			}
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::after_att(target,teach,team,beside_team);	
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::on_before_be_atted(target,teach,team,beside_team);	
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
			  int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
			  red+=(final_att-8);  	
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			for(auto x:team){
				(*x).att_mul*=1.2;
			}
		}
		void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			for(auto x:team){
				(*x).att_mul/=1.2;
			}
		}
};
