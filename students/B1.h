#include "A0.h"

class stud_B1:public stud{
	public:
		map<const stud*,int> swaP;
		double catG=1.0;
		stud_B1(){
			red_up+=5,blue_up+=20,white_up-=12;
			red=red_up,blue=blue_up,white=white_up;
			white_mul=0.85;
			be_att_mul=1.0;
			att-=2;
			ct1.pb("CatGirl");//猫娘
			ct1.pb("Nimble");//轻巧
			ct1.pb("2085");//魔怔
			id=14;
			name="B01";
		}
		int cblue(int chg,vector<stud*>team){
			stud::cblue(chg);
			int cnt_M=0;
			for(auto x:team){
				if((*x).status==1)cnt_M+1,(*x).cblue(0.15*chg);
			}
			stud::cblue(cnt_M*(-0.15)*chg);
			return status;
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			cwhite(1);		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			if((target -> id)!=20){
				catG-=(rand()*rand()%10+10)*0.01;
			}be_att_mul*=catG;
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);	
				be_att_mul	/=catG;
				catG=1.0;
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if((*target).id==20||(*target).name=="B7"){
				int final_att=(att*att_mul*(*target).be_att_mul+tmp_att_plus+2);
				cwhite(-5);
				(*target).cred(-1*final_att);
				return;
			}
			if(swaP[target]==0){
				(*target).cred(3);
				(*target).cwhite(-2);
				swaP[target]=1;
			}
			else{
				swaP[target]=0;
				int final_att=(att*att_mul*(*target).be_att_mul+tmp_att_plus+6);
				(*target).cred(final_att);
				(*target).cwhite(-10);
				att-=1;
				cred(5);
				cwhite(-7);
			}
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			be_att_mul=0.75;
		}
};
