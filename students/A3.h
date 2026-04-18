#include"A0.h"

class stud_A3:public stud{
	public:
		vector<pair<stud*,int> >hurtme; 
		stud_A3(){
			red_up+=20,blue_up+=5,white_up-=10;
			red=red_up,blue=blue_up,white=white_up;
			att-=8;
			hurtme.clear();
			py.push_back(2);
			py.push_back(10);
			py.push_back(15);
			ct1.push_back("BecomeRed");//红温
			ct1.push_back("ThingsDisappeared");//东西被偷了
			ct1.push_back("BecomeRed2nd");//红温2nd
			ct2.push_back("YouMother");//
			id=3;
			name="A03";
		}
	int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		int return_num=stud::before_att(target,teach,team,beside_team);
		
		(*target).be_att_mul*=1.25;
		hurtme.push_back({target,2});
		if(rand()%2==1)cblue(-3);
		return return_num;
	}
	void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::after_att(target,teach,team,beside_team);		
	}
	int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		int return_num = stud::on_before_be_atted(target,teach,team,beside_team);	
	    (*target).be_att_mul*=1.28;
	    hurtme.push_back({target,2});
		int tmp=0;
		int lry=0;
	    for(auto x : hurtme){
			if(hurtme[lry].first==target){
				tmp++;
			}
			lry++;
		}
		if(lry==3){
			target -> cblue(target -> blue);
		}
	    return return_num;
	}
	void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		    stud::on_minus_red(target,teach,team,beside_team);		
	}
	void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
		if(rand()%2==1)cblue(-3);
		for(int i=0;i<hurtme.size();i++){
			hurtme[i].second-=1;
			if(hurtme[i].second<0){
				(*hurtme[i].first).be_att_mul/=1.28;
				hurtme.erase(hurtme.begin()+i);
				i--;
			}
		}
	}
};