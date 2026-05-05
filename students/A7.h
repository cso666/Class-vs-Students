#include "A0.h"

class stud_A7:public stud{
	public:
		bool have_dead;
		
		stud_A7(){
			have_dead=0;
			red_up+=180,blue_up-=0,white_up+=100;
			red=red_up,blue=blue_up,white=white_up;
			Bighuocar=0;
			att-=8;
			py.push_back(15);
			ct1.push_back("BigYun");//大运之力
			ct1.push_back("RefusedToDie");//自强不屈
			ct2.push_back("RenShengA");//大运来力
			id=7;
			name="A07";
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
			int final_att=(*target).get_att()*get_be_att_mul();
			 if(HavCt[2])if(red<=0&&white>1&&have_dead==0){
			 	have_dead=1;
			 	red_up=0.5*red_up;
			 	red=0.5*red_up;
			 	white=1;
			 	status=1;
			 }  
			//(*target).cred(-int(0.3*final_att)); 	
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-5);
			for(auto y:team)
				(*y).Bighuocar=1;
		}
		
		void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			for(auto y:team)
				(*y).Bighuocar=1;
		}
};
