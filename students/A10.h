#include"A0.h"

class stud_A10:public stud{
	public:
		int sugar=0;
		stud_A10(){
			sugar=0;
			blue_mul*=1.2;
			red_up-=20,blue_up-=40,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(5);
			ct1.push_back("SugarButSmart");//大智若唐
			ct1.pb("Stay");//定力
			ct2.pb("BigShoot");//大力抽射
			id=10;
			name="A10";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			
			sugar+=3;
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
			   if(status==0||status==-1){
			   	for(auto x:beside_team)
			   		(*x).cred(-1*sugar);
			   }
		}
};