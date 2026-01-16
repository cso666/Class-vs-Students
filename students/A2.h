#include"A0.h"
#include<cstdlib>
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
		stud::before_att(target,teach,team,beside_team);
				if(blue<=40){
					can_act=false;
					cant_act++;
				}
				if((*target).name=="B10"){
					tmp_att_plus+=5;
					blue-=24;
				}
				if((rand()*rand())%3==1){
					tmp_att_plus+=5;
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
	}
};
