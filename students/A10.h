#include"A0.h"

class stud_A10:public stud{
	private:
		int sugar[100]={0};
		int sk_triTurn=-1,sk_rest;
		stud* charged_target;
		
	public:
		bool ned=0;
		stud_A10(){
			sk_rest=-999;
			ned=0;
			red_up-=30;
			blue_up=100;
			white_up+=40;
			red=red_up;
			blue=blue_up;
			white=white_up;
			att+=5;
			py.push_back(5);
			ct1.push_back("SugarButSmart");
			ct1.pb("Stay");
			ct2.pb("BigShoot");
			id=10;
			name="A10";
			memset(sugar,0,sizeof(sugar));
		}

		Return_Hit before_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(HavCt[1])sugar[(*target).id]+=1;
			return return_num;
		}
		
		void after_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);
		}
		
		Return_BeHit on_before_be_atted(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			return stud::on_before_be_atted(target,teach,team,beside_team);
		}
		
		void on_minus_red(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);
			if(HavCt[1]){
			if(status==0||status==-1){
				for(auto x:beside_team){x->cred(-2*sugar[(*x).id]);}
			}}
		}

		void on_turn_start(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			
			if(ned==0&&HavCt[2]){
				blue_mul[0].first*=0.8;
				blue_mul_p[0].first*=1.2;
				ned=1;
			}
		
			// 处理禁足状态
		}
		
		void on_turn_end(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			if(sk_rest==0){
				int hurt;
				switch(sk_triTurn){
					case 0:
						hurt=20;
						cwhite(-5);
						break;
					case 1:
						hurt=60;
						cwhite(-17);
						break;
					case 2:
						hurt=90;
						cwhite(-30);
						break;
				}
				int Fhurt=hurt*(*charged_target).get_be_att_mul();
				(*charged_target).cred(-1*Fhurt);
				sk_triTurn=-1; 
				charged_target=NULL;
				sk_rest=-999;
			}
			sk_rest-=1;
		}

		void skhit(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int last_turn=3-Dtee().second;
			last_turn=max(last_turn,0);
			for(auto y:team){
				(*y).cant_act+=last_turn;
				(*y).can_act=0;
			} 
			sk_triTurn=last_turn;
			sk_rest=last_turn;
			charged_target=target;
		}

		
		
};
