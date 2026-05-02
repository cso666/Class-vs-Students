#include"A0.h"

class stud_A5:public stud{
	public:
		bool firstTurnA9=0,fromA9=0;  // 从A0移入
		
		stud_A5(){
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
		
		int cred(int chg)override{
			if(chg>0&&!fromA9){return status;}  // 非 A9 回血无效
			fromA9=0;
			red+=chg;
			red=min(red,red_up);
			if(red<0){red=0,status=0;}
			return status;
		}

		void healFromA9(int chg) {
			fromA9 = true;
			cred(chg);
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if((rand()*rand())%10==9){
				tmp_att_plus.push_back({5,1});
				(*target).can_act=false;
				int ctttt=tim%26%3; 
				(*target).cant_act+=3-ctttt;
			}
			return 2;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);				
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