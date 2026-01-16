#include"A0.h"
#include<cstdlib>
class stud_A3:public stud{
	public:
		vector<int>hurtme; 
		stud_A3(){
			red_up+=5,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=8;
			hurtme.clear();
			hurtme.push_back(0);
			py.push_back(2);
			py.push_back(10);
			py.push_back(15);
			ct1.push_back("BecomeRed");//红温
			ct1.push_back("ThingsDisappeared");//东西被偷了
			ct1.push_back("YouMother");//
			ct1.push_back("RuYan");//如烟
			id=3;
			name="A03";
		}
	int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::before_att(target,teach,team,beside_team);
		
		(*target).be_att_mul*=1.28;
		if(rand()%2==1)blue-=3;
	}
	void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::after_att(target,teach,team,beside_team);		
	}
	int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::on_before_be_atted(target,teach,team,beside_team);	
	    (*target).be_att_mul*=1.28;
	    if(rand()%2==1)blue-=3;
	}
	void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		    stud::on_minus_red(target,teach,team,beside_team);		
	}
};
