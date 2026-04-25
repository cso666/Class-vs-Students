#include"A0.h"

class stud_A5:public stud{
	public:
		bool is_plusatt=0;
		stud_A5(){
			is_plusatt=0;
			red_up+=30,blue_up+=20,white_up+=0;
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
				int return_num=stud::before_att(target,teach,team,beside_team);
				if((rand()*rand())%10==9){
				    tmp_att_plus+=5;
					(*target).can_act=false;
					int ctttt=tim%26%3; 
					(*target).cant_act+=3-ctttt;
					is_plusatt=1;
				}
				return 2;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
				if(is_plusatt==1){
				is_plusatt=0;
				tmp_att_plus-=5;
			}			
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
		cwhite(-15);
		cblue(5);
		target -> cred(-25);
	}
};
