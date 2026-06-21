#include "A0.h"

class stud_B8:public stud{
	public:
		bool ifai=0;
		bool fight_active=0;  // WantFight? 是否激活
		int fight_turnsLeft=0;  // 剩余回合数
		double base_att_mul = 1.0;
		double base_be_att_mul = 0.7;
		
		stud_B8(){
			be_att_mul[0].first*=0.7;
			red_up+=28,blue_up-=22,white_up+=24;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			fight_active=0;
			fight_turnsLeft=0;
			py.push_back(14);
			ct1.pb("BreachOfFaith");
			ct2.pb("KongyiJi");
			ct1.pb("WantFight?");
			id=21;
			name="B08";
			base_att_mul = att_mul[0].first;
			base_be_att_mul = be_att_mul[0].first;
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num= stud::before_att(target,teach,team,beside_team);
			if(HavCt[1]){if(teach==2){att_mul.push_back({2.0,0});}
			}
			return return_num;
		}

		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			
			if(HavCt[1]){
			if(teach==4){
				att_mul.push_back({0.7,0});
				be_att_mul.push_back({1.4,0});
				ifai=1;
			}}
			if(HavCt[2]){
			for(auto y:beside_team){
				if((*y).id==19){
					cblue(-3);
					(*y).cblue(-3);
					tmp_att_plus.push_back({2,0});
					(*y).tmp_att_plus.push_back({2,0});
				}
			}}
			
			// WantFight? 持续效果
			if(HavCt[2]){
			if(fight_active){
				// 每回合 +2 HP
				cred(2);
				
				fight_turnsLeft--;
				if(debug_on){logPrint(10,"[B08] WantFight? active: +2 HP, turns left: %d\n",fight_turnsLeft);}
				
				if(fight_turnsLeft<=0){
					fight_active=0;
					// 结束效果：-20 STA, -8 HP
					cwhite(-20);
					cred(-8);
					if(debug_on){logPrint(10,"[B08] WantFight? ended! -20 STA, -8 HP\n");}
				}
			}}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			// -8 STA
			cwhite(-8);
			// -15 SAN
			cblue(-15);
			target->cblue(-15);
			// 不听讲
			listen=0;
			target->listen=0;
			
			if(debug_on){logPrint(10,"[B08] \
WantFight? used on %s! -15 SAN, target not listening.\n",target->name.c_str());}
			
			// 临ATK=14
			int oldAtt=att;
			att=14;
			int final_att=get_att()*target->get_be_att_mul();
			target->cred(-final_att);
			att=oldAtt;
			
			if(debug_on){
				logPrint(10,"[B08] Immediate attack! Damage: %d\n",final_att);
			}
			
			// 持续3回合
			fight_active=1;
			fight_turnsLeft=3;
			// 3回合 att +3
			tmp_att_plus.push_back({3,3});
			
			if(debug_on){logPrint(10,"[B08] WantFight? active for 3 turns! +3 ATK, +2 HP/turn.\n");}
		}
};
