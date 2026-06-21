#include "A0.h"

class stud_A8:public stud{
	public:
		bool hasuse;
		
		stud_A8(){
			red_up+=0,blue_up+=10,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			hasuse=0;
			py.push_back(15);
			ct1.push_back("TurtleLivesLong");//神龟虽寿
			ct1.push_back("BrainStorm");//头脑风暴
			ct1.push_back("SixbleAp");//六重A+
			ct2.push_back("LowDHit");//降维打击(D -> demension)
			
			id=8;
			name="A08";
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(red==red_up&&blue==blue_up&&white==white_up&&att==8){att+=4;}
			else if(att==12){att-=4;}
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
		}
		
		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);
			if(HavCt[1]){return_num.update(pair<int,pair<int,int>>{1,{18,0}});}
			return return_num;
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(HavCt[2]){
				int where=-1;
				for(int i=0;i<team.size();i++){
					if((*team[i]).id==8)where=i;
				}
				for(int i=0;i<team.size();i++){
					if(i<where)(*team[i]).att_mul.push_back({1.2,0});
					else(*team[i]).att_mul.push_back({1.2,1});
				}
			}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			bool flag=0;
			for(auto x:(target -> py)){
				if(x==15){
					flag=1;
					break;
				}
			}
			if(flag&&!hasuse){
				hasuse=1;
				cwhite(-5);
				target->cred(-(target->red_up)*0.2);
			}else{
				cwhite(-15);
				cblue(-1);
				target->cred(-(target->red_up)*0.1);
			}
		}
		
		void on_day_start(int subject_id){
			hasuse=0;
		}
};
