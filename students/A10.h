#include"A0.h"

class stud_A10:public stud{
	private:
		int sugar[100]={0};  // 从A0移入
		int sk_triTurn=-1,sk_mul=0,sk_cw=0;  // 从A0移入
		bool sk_ready=0;  // 从A0移入
		
		void sk_pre(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team,int wcost){
			int oldAtt=att;
			att=16;
			int old_tmp=get_tmp_att_plus();
			int final_att=(get_att()*sk_mul)*target->get_be_att_mul();

			if(debug_on){
				logPrint(10,"[A10] Big Shoot AUTO attack! ATK=%d, multiplier=%d, final=%d (no cap)\n",att,sk_mul,final_att);
			}
			cwhite(-wcost);
			target->cred(-final_att);
			att=oldAtt;

			can_act=1;
			cant_act=-1;
		}

	public:
		stud_A10(){
			blue_mul[0].first*=0.8;
			red_up-=20;
			blue_up=100;
			white_up+=20;
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
			sk_triTurn=-1;
			sk_ready=0;
			sk_cw=0;
			memset(sugar,0,sizeof(sugar));
		}

		int before_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			sugar[(*target).id]+=1;
			return return_num;
		}
		
		void after_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);
		}
		
		int on_before_be_atted(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			return stud::on_before_be_atted(target,teach,team,beside_team);
		}
		
		void on_minus_red(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);
			if(status==0||status==-1){
				for(auto x:beside_team){x->cred(-2*sugar[(*x).id]);}
			}
		}

		void on_turn_start(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);

			if(sk_ready&&tim%26==3){
				sk_pre(target,teach,team,beside_team,sk_cw);
				sk_ready=0;
				sk_triTurn=-1;
			}
		}

		void skhit(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(sk_triTurn!=-1){return;}

			int r=tim%26;
			if(r<1||r>3){return;}

			int skattmul=0;
			switch(r){
				case 1:sk_cw=30,skattmul=3;break;
				case 2:sk_cw=17,skattmul=2;break;
				case 3:sk_cw=5,skattmul=1;break;
			}
			if(white<sk_cw){return;}

			if(r==3){
				sk_pre(target,teach,team,beside_team,sk_cw);
				return;
			}

			sk_triTurn=r;
			sk_mul=skattmul;
			sk_ready=1;
			can_act=0;
			cant_act=(3-r)+1;

			if(debug_on){logPrint(10,"[A10] Charged! Will attack on turn 3 with %dx multiplier. Cost %d STA.\n",skattmul,sk_cw);}
		}
};