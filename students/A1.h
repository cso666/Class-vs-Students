#include "A0.h"
#include<cstdlib>
class stud_A1:public stud{
	public:
		stud_A1(){
			red_up+=25,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(15);
			py.push_back(3);
			py.push_back(10); 
			py.push_back(9);
			ct1.push_back("SmallYun");//小运
			ct2.push_back("LemonSoSour");//柠檬强酸
			ct1.push_back("Tired");//劳累

			id=1;
			name="A01";
		}
	int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::before_att(target,teach,team,beside_team);//一个好习惯，勿删！
				white_mul=1.25;
				if((rand()*rand())%20==16){
				    tmp_att_plus+=5;
					(*target).can_act=false;
					(*target).cant_act++;
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
