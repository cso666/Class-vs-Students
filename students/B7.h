#include "A0.h"

class stud_B7:public stud{
	public:
		bool skill_active=0;// 技能效果
		bool dmg_mul_active=0;// 1.8倍伤害
		
		bool ned=0;
		stud_B7(){
			ned=0;
			red_up+=4,blue_up-=14,white_up+=6;
			red=red_up,blue=blue_up,white=white_up;
			att+=1;
			skill_active=0;
			dmg_mul_active=0;
			py.push_back(14);
			ct1.push_back("CowStrength");
			ct1.push_back("Digniu");
			ct1.push_back("BothHigh&Cold");
			ct2.push_back("ScythedDown");
			id=20;
			name="B07";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
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
		
		void on_turn_start(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(ned==0&&HavCt[1]){
				white_mul_p[0].first*=1.3;
				blue_mul_p[0].first*=1.1;
				white_mul[0].first*=0.9;
				blue_mul[0].first*=0.95;
				ned=1;
			}
		}
		void on_class_end(){skill_active=dmg_mul_active=0;}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(white<10){
				if(debug_on){logPrint(10,"[B07] Not enough stamina for ScythedDown!\n");}
				return;
			}
			
			if(skill_active){
				if(debug_on){logPrint(10,"[B07] ScythedDown already active this class!\n");}
				return;
			}
			
			cwhite(-10);
			skill_active=1;
			
			if(debug_on){logPrint(10,"[B07] ScythedDown used on %s!\n",target->name.c_str());}
			
			int turns_left=0;
			if(clas!=8){turns_left=3-Dtee().second;}
			else{turns_left=8-Dtee().second;}
			if(turns_left<0){turns_left=0;}
			
			if((double)red/red_up>=0.2){
				int target_hp=red_up*0.2;
				cred(target_hp-red);
				if(turns_left>0){tmp_att_plus.push_back({6, turns_left});}
				else{tmp_att_plus.push_back({6,1});}
				if(debug_on){logPrint(10,"[B07] HP >= 20%%, reduced to 20%%. +6 ATK for %d turns.\n",turns_left);}
			}else{
				if((double)blue/blue_up>=0.2){
					int target_san=blue_up*0.2;
					cblue(target_san-blue);
					if(turns_left>0){att_mul.push_back({1.8,turns_left});}
					else{att_mul.push_back({1.8,1});}
					if(debug_on){logPrint(10,"[B07] SAN >= 20%%, reduced to 20%%. +80%% damage for %d turns.\n",turns_left);}
				}else{
					int target_san=blue_up*0.2;
					cblue(target_san-blue);
					if(debug_on){logPrint(10,"[B07] SAN < 20%%, restored to 20%%. No bonus.\n");}
				}
			}
			
			int final_att=get_att()*target->get_be_att_mul();
			target->cred(-final_att);
			if(debug_on){logPrint(10,"[B07] Immediate attack! Damage: %d\n",final_att);}
		}
};
