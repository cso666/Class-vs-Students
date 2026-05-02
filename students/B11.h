#include"A0.h"

class stud_B11:public stud{
public:
	int guest_turnsLeft=0,guest_marked=0;  // 从A0移入

	stud_B11(){
		red_up+=4,blue_up+=0,white_up+=2;
		red=red_up,blue=blue_up,white=white_up;
		att-=1;
		py.push_back(8);
		py.push_back(14);
		ct1.pb("Defections");
		ct1.pb("OneMoreFoot");
		ct1.pb("SongsTalent");
		ct2.pb("Guest");
		id=24;
		name="B11";
		guest_turnsLeft=0;
		guest_marked=0;
	}

	int before_att(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		int return_num=stud::before_att(target,teach,team,beside_team);
		
		// OneMoreFoot
		int final_att=get_att()*target->get_be_att_mul();
		if(target->red<=final_att){
			if(rand()%100<99){
				target->cblue(-5);
				if(debug_on){
					logPrint(12,"[B11] OneMoreFoot: Attack cancelled, %s loses 5 SAN instead.\n",target->name.c_str());
				}
				return 1;
			}
		}
		
		return return_num;
	}

	void after_att(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::after_att(target,teach,team,beside_team);
		if(target->red<=25){
			tmp_att_plus.push_back({4,0x7f7f7f7f});
		}
	}

	int on_before_be_atted(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		return stud::on_before_be_atted(target,teach,team,beside_team);
	}

	void on_minus_red(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_minus_red(target,teach,team,beside_team);
	}

	void on_turn_start(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_turn_start(target,teach,team,beside_team);
		// SongsTalent
		for(auto y:team){y->cblue(10);}
		
		// 嘉宾
		if(guest_turnsLeft>0){
			guest_turnsLeft--;
			
			if(guest_turnsLeft>=0){
				for(auto y:beside_team){
					if(isalive[y->id]&&!y->listen){
						int prob=70;
						if(guest_marked==1){prob=40;}
						else if(guest_marked==2){prob=10;}
						else if(guest_marked>=3){prob=0;}
						
						if(rand()%100<prob){
							y->listen=0;
							guest_marked++;
							if(debug_on){
								logPrint(12,"[B11] Guest effect: %s marked as not listening. (Marked count: %d)\n",y->name.c_str(),guest_marked);
							}
						}
					}
				}
			}
			
			if(guest_turnsLeft<=0){
				guest_turnsLeft=0;
				guest_marked=0;
				if(debug_on){logPrint(10,"[B11] Guest effect ended.\n");}
			}
		}
	}

	void on_turn_end(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		stud::on_turn_end(target,teach,team,beside_team);
	}

	void skhit(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team){
		if(guest_turnsLeft>0){
			if(debug_on){logPrint(10,"[B11] Guest skill already active.\n");}
			return;
		}
		
		if(white<15){
			if(debug_on){logPrint(10,"[B11] Not enough stamina for Guest skill.\n");}
			return;
		}
		cwhite(-15);
		
		target->cblue(-5);
		target->cwhite(-5);
		
		if(debug_on){
			logPrint(10,"[B11] Guest skill used on %s! -5 SAN, -5 STA to target.\n",target->name.c_str());
		}
		
		for(auto y:team){
			if(y!=this&&isalive[y->id]){
				y->cblue(5);
				y->cwhite(5);
				if(debug_on){logPrint(10,"[B11] Teammate %s: +5 SAN, +5 STA\n",y->name.c_str());}
			}
		}
		
		for(auto y:beside_team){
			if(isalive[y->id]){
				y->cblue(-5);
				y->cwhite(-5);
				if(debug_on){logPrint(10,"[B11] Opponent %s: -5 SAN, -5 STA\n",y->name.c_str());}
			}
		}
		
		guest_turnsLeft=3;
		guest_marked=0;
		
		if(debug_on){
			logPrint(10,"[B11] Guest effect active for 3 turns.\n");
		}
	}
};