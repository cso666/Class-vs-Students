#include "A0.h"

class stud_B1:public stud{
	public:
		map<const stud*,int> swaP;
		double catG=1.0;
		bool ned=0;
		stud_B1(){
			ned=0;
			red_up+=5,blue_up+=20,white_up-=12;
			red=red_up,blue=blue_up,white=white_up;
			
			be_att_mul[0].first=1.0;
			att-=2;
			ct1.pb("CatGirl");//猫娘
			ct1.pb("Nimble");//轻巧
			ct1.pb("2085");//魔怔
            ct2.push_back("SwapSeat");
			id=14;
			name="B01";
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
			}
			if(HavCt[1])be_att_mul.push_back({catG,1});
			catG=1.0;
			return return_num;		
		}
		void on_turn_start(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(ned==0&&HavCt[2]){
				white_mul[0].first=0.85;
				ned=1;
			}
		
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if((*target).id==20||(*target).name=="B7"&&(*target).HavCt[2]){
				int final_att=get_att(att+2)*(*target).get_be_att_mul();
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
				int final_att=get_att(att+6)*(*target).get_be_att_mul();
				(*target).cred(final_att);
				(*target).cwhite(-10);
				att-=1;
				cred(5);
				cwhite(-7);
			}
		}
};
