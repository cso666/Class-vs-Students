#include"A0.h"

class stud_A2:public stud{
	public:
		stud_A2(){
			red_up+=0,blue_up+=20,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=10;
			py.push_back(7);
			py.push_back(15);
			ct1.push_back("Unconnect");//断网
			ct1.push_back("Subjective");//主观的人
			ct2.push_back("ParentsGone");//我的浮木似了
			ct1.push_back("Headshot");//

			id=2;
			name="A02";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if(blue<=40){
				can_act=false;
				cant_act++;
			}
			if((*target).name=="B10"){
				tmp_att_plus.push_back({5,1});
				cblue(-24);
			}
			if((rand()*rand())%3==1){
				tmp_att_plus.push_back({5,1});
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
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-30);
			int final_att=(2*get_att())*(target->get_be_att_mul());
			if(final_att<=30){
				target->cred(-final_att);
			}
			else if(final_att<45){
				target->cred(-30);
				target->cred(-(final_att-30));
			}
			else if(final_att>=45){
				target->cred(-30);
				target->cred(-15);
			}
			int A2sktrand=rand()%5;
			if(A2sktrand>=1&&A2sktrand<=4){cred(-15);}
		}
};