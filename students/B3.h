#include "A0.h"

class stud_B3:public stud{
	public:
		stud_B3(){
			red_up+=0,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			bool teacher_is_HT=false;
			bool has_A10=false;
			att-=4;
			py.push_back(1);
			ct1.pb("Tutor(TA)");//助教先生
			ct1.pb("Calm&Composed");//心平气和
			ct1.pb("MathDUO");//数学双星
			id=16;
			name="B03";
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
		void on_trun_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(teach==2&&! teacher_is_HT){
				teacher_is_HT=1;
				att+=4;
				red_up+=15;
				blue_up+=15;
				white_up+=15;
			}
			if(teach!=2&&teacher_is_HT){
				teacher_is_HT=0;
				att-=4;
				red_up-=15;
				blue_up-=15;
				white_up-=15;
			}
			cred(5);
			bool flag=false;
			for(auto x:team){
				if((x->id)==10){
					flag=true;
					break;
				}
			}
			if(flag&&! has_A10 &&isalive[10]){
				blue_up+=8;
				red_up+=8;
				white_up+=8;
				has_A10=1;
			}
			if(has_A10&&!isalive[10]){
				blue_up-=8;
				red_up-=8;
				white_up-=8;
				has_A10=0;
			}
		}
};
