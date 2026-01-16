#include "A0.h"

class stud_B2:public stud{
	public:
		stud_B2(){
			red_up-=7,blue_up-=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			py.push_back(13);
			ct1.pb("TalkBack");//顶嘴
			ct1.pb("Barking");//犬吠
			ct1.pb("Height(DIS)Adv.");//身高优势
			ct1.pb("Recitalist");//朗诵家
			id=15;
			name="B02";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::before_att(target,teach,team,beside_team);
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
