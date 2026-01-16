#include "A0.h"

class stud_A13:public stud{
	public:
		stud_A13(){
			red_up-=10,blue_up+=30,white_up-=10;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			py.push_back(12);
			py.push_back(15);
			ct1.pb("WeAreLegends");//我是传奇
			ct1.pb("SoDelicious");//食之有味
			ct2.pb("YearPigWeigh");//年猪千钧
			id=13;
			name="A13";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::before_att(target,teach,team,beside_team);
				int wum=0;
				for(auto x:team)wum+=(*x).white;
				att_mul*=max(wum/500.0,1.0);	
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
				int wum=0;
				for(auto x:team)wum+=(*x).white;
				att_mul/=max(wum/500.0,1.0);
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
				stud::on_before_be_atted(target,teach,team,beside_team);		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
			    int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
				white+=final_att;	
		}
};
