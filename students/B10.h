#include "A0.h"

class stud_B10:public stud{
	public:
		int cnt_x=0;
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
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			cnt_x=0;
			for(auto y:team)
				cnt_x+=(*y).status==1;
			for(auto y:beside_team)
				cnt_x+=(*y).status==1;
			att_mul*=1+0.2*cnt_x;
			be_att_mul*=1+0.2*cnt_x;
			
			if(is_crazy){
				for(auto y:beside_team)
					(*y).cred(5*(att*att_mul+tmp_att_plus));
				cwhite(0.9*white);
			}
		}
		virtual void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			att_mul/=0.2*cnt_x;
			be_att_mul/=0.2*cnt_x;
		}
};
