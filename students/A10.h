#include"A0.h"

class stud_A10:public stud{
	private:
		int sugar[100]={0};
		int sk_triTurn=-1,sk_mul=0,sk_cw=0;
		bool sk_ready=0;
		bool sk_used_this_class=0;
		int disabled_turns=0;
		stud* charged_target;
		
		void sk_pre(int teach,vector<stud*>team,vector<stud*>beside_team,int wcost){
			if(charged_target == NULL){
				if(debug_on) logPrint(10,"[A10] sk_pre aborted: charged_target is NULL!\n");
				sk_ready=0;
				sk_triTurn=-1;
				return;
			}
			
			if(charged_target->status==0 || !isalive[charged_target->id]){
				if(debug_on) logPrint(10,"[A10] sk_pre aborted: target is dead!\n");
				charged_target=NULL;
				sk_ready=0;
				sk_triTurn=-1;
				return;
			}
			
			int oldAtt=att;
			att=16;
			int final_att=(get_att()*sk_mul)*charged_target->get_be_att_mul();

			if(debug_on){
				logPrint(10,"[A10] Big Shoot AUTO attack! ATK=%d, multiplier=%d, final=%d (no cap)\n",att,sk_mul,final_att);
			}
			cwhite(-wcost);
			charged_target->cred(-final_att);
			att=oldAtt;
			
			charged_target=NULL;
		}

	public:
		bool ned=0;
		stud_A10(){
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
			sk_triTurn=-1;
			sk_ready=0;
			sk_cw=0;
			sk_used_this_class=0;
			disabled_turns=0;
			charged_target=NULL;
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
			if(disabled_turns>0){
				can_act=0;
				disabled_turns--;
				if(debug_on){
					logPrint(10,"[A10] Disabled! %d turns remaining.\n",disabled_turns);
				}
			}
		}
		
		void on_turn_end(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			
			// 蓄力完成，在回合结束时自动攻击
			if(sk_ready && disabled_turns==0){
				sk_pre(teach,team,beside_team,sk_cw);
				sk_ready=0;
				sk_triTurn=-1;
				if(debug_on){
					logPrint(10,"[A10] Big Shoot executed at turn end!\n");
				}
			}
		}

		void skhit(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(sk_used_this_class){
				if(debug_on){logPrint(10,"[A10] Big Shoot already used this class!\n");}
				return;
			}
			if(target==NULL){
				if(debug_on){logPrint(10,"[A10] Big Shoot aborted: target is NULL!\n");}
				return;
			}

			int r=tim%26;
			if(r<1||r>3){
				if(debug_on){logPrint(10,"[A10] Big Shoot can only be used in turn 1-3! (current turn: %d)\n",r);}
				return;
			}

			int skattmul=0;
			switch(r){
				case 1:sk_cw=30,skattmul=3;break;
				case 2:sk_cw=17,skattmul=2;break;
				case 3:sk_cw=5,skattmul=1;break;
			}
			if(white<sk_cw){
				if(debug_on){logPrint(10,"[A10] Not enough stamina for Big Shoot! Need %d, have %d\n",sk_cw,white);}
				return;
			}

			sk_used_this_class=1;
			sk_mul=skattmul;
			charged_target=target;
			
			cwhite(-sk_cw);
			int turns_until_3=3-r;
			disabled_turns=turns_until_3;
			
			if(turns_until_3>0){
				can_act=0;
				cant_act=disabled_turns;
			}
			
			int disabled_count=0;
			for(auto x:team){
				if(x!=this&&x->status==1&&isalive[x->id]){
					if(disabled_turns>0){
						x->can_act=0;
						x->cant_act=disabled_turns;
						disabled_count++;
						if(debug_on){logPrint(10,"[A10] Teammate %s \
is disabled for %d turns!\n",x->name.c_str(),disabled_turns);}
					}else{x->can_act=1;}
				}
			}
			
			sk_ready=1;
			
			if(debug_on){
				logPrint(10,"[A10] Big Shoot charged! Will attack on turn end. Disabled for %d turns.\n",turns_until_3);
			}
		}

		bool isCharging()const{return sk_ready&&disabled_turns>0;}
		
		void on_fight_end(){
			sk_used_this_class=0;
			disabled_turns=0;
			sk_ready=0;
			sk_triTurn=-1;
			charged_target=NULL;
			can_act=1;
			cant_act=-1;
		}
};
