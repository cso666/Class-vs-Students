#include "A0.h"

class stud_B12:public stud{
	public:
		bool have_dead;
		stud_B12(){
			have_dead=0;
			red_up-=4,blue_up-=0,white_up+=40;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct1.pb("HitPlane");//？王
			ct1.pb("Letsrun");//约跑
			id=25;
			name="B12";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if((*target).white<white){
				cwhite(5);
				cwhite((white-(*target).white)/3);
			}
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
			int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
				
			if(white>=max(30,2*final_att)){
				cred(final_att);
				cwhite(-2*final_att);
			}
			if(red<=0&&have_dead==0){
			 	have_dead=1;
			 	red_up=red_up-54;
			 	red=red_up;
			 	status=1;
				(*target).cred(-2*(att*att_mul+tmp_att_plus)); 
			 }  
			
					
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			cred(-3);
			cwhite(6);
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		
	}
};
