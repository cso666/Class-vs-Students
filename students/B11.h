#include "A0.h"

class stud_B11:public stud{
	public:
		stud_B11(){
			red_up+=4,blue_up+=0,white_up+=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			py.push_back(8);
			py.push_back(14);
			ct1.pb("Defections");//叛变
			ct1.pb("Guest");//嘉宾
			ct1.pb("OneMoreFoot");//差一脚 One不能接Feet!!
			ct1.pb("SongsTalent");//歌喉
			id=24;
			name="B11";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if((*target).red<=25)return 1;
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			if((*target).red<=25)tmp_att_plus+=4;		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			for(auto y:team)(*y).cblue(10);
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		
	}
};
