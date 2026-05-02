#include"A0.h"

class stud_B12:public stud{
public:
	bool have_dead;
	int shake_turnsLeft=0;  // 从A0移入
	bool shake_active=0;  // 从A0移入

	stud_B12(){
		have_dead=0;
		red_up-=4,blue_up-=0,white_up+=40;
		red=red_up,blue=blue_up,white=white_up;
		att-=1;
		ct1.pb("HitPlane");
		ct1.pb("Letsrun");
		ct2.pb("ShakeXueBi");
		id=25;
		name="B12";
		shake_turnsLeft=0;
		shake_active=0;
	}

	int before_att(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		int return_num=stud::before_att(target,teach,team,beside_team);
		int diff=white-target->white;
		cwhite(5);
		cwhite(diff/3);
		if(debug_on){
			logPrint(10,"[B12] HitPlane: white diff=%d, adjusted STA by %d\n",diff,diff/3);
		}
		return return_num;
	}

	void after_att(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::after_att(target,teach,team,beside_team);
	}

	int on_before_be_atted(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		return stud::on_before_be_atted(target,teach,team,beside_team);
	}

	void on_minus_red(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_minus_red(target,teach,team,beside_team);
		int final_att=target->get_att()*get_be_att_mul();
		
		if(white>=max(30,2*final_att)){
			cred(final_att);
			cwhite(-2*final_att);
			if(debug_on){
				logPrint(10,"[B12] Counter: healed %d HP, lost %d STA\n",final_att,2*final_att);
			}
		}
		
		if(red<=0&&have_dead==0){
			have_dead=1;
			red_up=red_up-54;
			red=red_up;
			status=1;
			target->cred(-2*get_att());
			if(debug_on){
				logPrint(12,"[B12] Resurrected! Counterattack dealt %d damage\n",2*get_att());
			}
		}
	}

	void on_turn_start(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_turn_start(target,teach,team,beside_team);
		cred(-3);
		cwhite(6);
		
		if(shake_active){
			cwhite(10);
			if(debug_on){logPrint(10,"[B12] Shake effect: +10 STA this turn.\n");}
			
			shake_turnsLeft--;
			if(shake_turnsLeft<=0){
				shake_active=0;
				shake_turnsLeft=0;
				listen=1;
				if(debug_on){logPrint(10,"[B12] Shake effect ended.\n");}
			}
		}
	}

	void on_turn_end(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_turn_end(target,teach,team,beside_team);
	}

	void skhit(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		if(shake_active){
			if(debug_on){logPrint(10,"[B12] Shake skill already active.\n");}
			return;
		}
		
		if(white<20){
			if(debug_on){logPrint(10,"[B12] Not enough stamina for Shake skill.\n");}
			return;
		}
		
		if(white<30){
			cwhite(-white);
			if(debug_on){logPrint(10,"[B12] Shake skill used, becomes exhausted.\n");}
		}else{
			cwhite(-30);
			if(debug_on){logPrint(10,"[B12] Shake skill used, -30 STA.\n");}
		}
		
		cblue(10);
		cred(10);
		
		int teammateCount=0;
		for(auto x:team){
			if(x!=this&&isalive[x->id]){
				x->cblue(-12);
				x->cred(-5);
				teammateCount++;
				if(debug_on){logPrint(10,"[B12] Teammate %s: -12 SAN, -5 HP\n",x->name.c_str());}
				if(teammateCount>=2){break;}
			}
		}
		
		int opponentCount=0;
		for(auto x:beside_team){
			if(isalive[x->id]){
				x->cblue(-15);
				x->cred(-10);
				opponentCount++;
				if(debug_on){logPrint(10,"[B12] Opponent %s: -15 SAN, -10 HP\n",x->name.c_str());}
				if(opponentCount>=3){break;}
			}
		}
		
		target->cblue(-5);
		target->cred(-5);
		if(debug_on){logPrint(10,"[B12] Target %s extra: -5 SAN, -5 HP\n",target->name.c_str());}
		
		shake_active=1;
		shake_turnsLeft=3;
		listen=0;
		if(debug_on){logPrint(10,"[B12] Shake effect active for 3 turns.\n");}
	}
};