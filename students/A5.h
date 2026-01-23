#include"A0.h"

class stud_A5:public stud{
	public:
		stud_A5(){
			red_up+=80,blue_up+=20,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(13);
			py.push_back(15);
			ct1.push_back("MiddleYun");//中运
			ct2.push_back("MambaOut");//曼巴out
			ct1.push_back("QiangShi");//强势
			id=5;
			name="A05";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::before_att(target,teach,team,beside_team);
				if((rand()*rand())%10==9){
				    tmp_att_plus+=5;
					(*target).can_act=false;
					(*target).cant_act+=2;
				}
				return 2;
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
