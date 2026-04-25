#include "A0.h"

class stud_B6:public stud{
	public:
		stud_B6(){
			red_up-=4,blue_up+=5,white_up-=8;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			B6CADB=1.0;
			ct1.pb("CADB");
			ct1.pb("Nazistent");//集中营
			ct2.pb("OldThousand");//老干
			id=19;
			name="B06";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			int B6_CADB=rand()%20;
			if(B6_CADB>=0&&B6_CADB<=3){
				att_mul*=1.28;
				B6CADB=1.28;
			}
			if(B6_CADB>=4&&B6_CADB<=5){
				att_mul*=1.8;
				B6CADB=1.8;
			}
			if(B6_CADB>=6&&B6_CADB<=9){
				att_mul*=0.6;
				B6CADB=0.6;
			}
			if(B6_CADB>=10&&B6_CADB<=11){
				att_mul*=2.0;
				B6CADB=2.0;
			}
			if(B6_CADB==12){
				att_mul*=0.25;
				B6CADB=0.25;
			}
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
			att_mul/=B6CADB;
			B6CADB=1.0;	
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
		
	}
};
