#include "A0.h"

class stud_A7:public stud{
	public:
		bool have_dead;
		stud_A7(){
			have_dead=0;
			red_up+=180,blue_up-=0,white_up+=100;
			red=red_up,blue=blue_up,white=white_up;
			att-=8;
			py.push_back(15);
			ct1.push_back("BigYun");//大运之力
			ct1.push_back("RefusedToDie");//自强不屈
			ct2.push_back("RenShengA");//大运来力
			//人生啊能不能放过我这一次
			id=7;
			name="A07";
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
			int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
			 if(red<=0&&white>1&&have_dead==0){
			 	have_dead=1;
			 	red=0.5*red_up;
			 }  
			(*target).red-=0.3*final_att; 	
		}
};
