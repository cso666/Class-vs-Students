#include "A0.h"

class stud_B8:public stud{
	public:
		bool ifai=0;
		double base_att_mul = 1.0;
		double base_be_att_mul = 0.7;
		stud_B8(){
			be_att_mul*=0.7;
			red_up+=8,blue_up-=2,white_up+=4;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(14);
			ct1.pb("Defections");//叛变
			ct1.pb("BreachOfFaith");//
			ct2.pb("YouKongyiJi");//孔乙己
			ct1.pb("WantFight?");//打架吗
			id=21;
			name="B08";
			base_att_mul = att_mul;
			base_be_att_mul = be_att_mul;
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);			
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			// 先重置乘区
			att_mul = base_att_mul;
			be_att_mul = base_be_att_mul;
			
			stud::on_turn_start(target,teach,team,beside_team);
			
			if(teach==4 && ifai==0){
				att_mul *= 0.7;
				be_att_mul += 0.4;
				ifai=1;
			}
			if(teach!=4){
				att_mul /= 0.7;
				be_att_mul -= 0.4;
				ifai=0;
			}
			for(auto y:beside_team){
				if((*y).id==19){
					cblue(-3);
					(*y).cblue(-3);
					tmp_att_plus+=2;
					(*y).tmp_att_plus+=2;
				}
			}
		}
};