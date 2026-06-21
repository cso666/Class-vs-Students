#include"A0.h"

int classtablee[100+10][100+10]={{6,2,8,3,9,1,0},{2,13,4,1,7,8,5},{1,1,2,3,11,8,0},{1,8,12,7,10,4,2},{3,4,2,2,6,5,0}};

class stud_A12: public stud{
	public:
		bool ega_used=0;  // 从A0移入
		int ega_turnsLeft=0;  // 从A0移入
		double base_be_att_mul=1.0;  // 从A0移入
		
		stud_A12(){
			red_up+=10;blue_up+=-20;white_up-=-10;
			red=red_up;blue=blue_up;white=white_up;
			att+=0;
			py.push_back(15);
			ct1.pb("EatWell");//我吃好了
			ct1.pb("YogHURT");//酸奶
			ct1.pb("YouXianglinSao");//并非蠢货
			ct2.pb("EnchantedGoldenApple");//附魔金苹果
			id=12;
			name="A12";
			base_be_att_mul=be_att_mul[0].first;
			ega_used=0;
			ega_turnsLeft=0;
		}
		
		Return_Hit before_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			if(target->id==8){
				return_num.update(pair<int,pair<double,int>>{2,{1.10,0}});
			}
			return return_num;
		}

		Return_BeHit on_before_be_atted(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);
			if(HavCt[1])be_att_mul.push_back({1+max((150.0-blue)/150.0,1.0),0});
			return return_num;
		}

		void on_turn_end(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			
			int date=tim/26;
			if(tim%26!=0){return;}
			int HTclas=0;
			for(int i=0;i<7;i++){HTclas+=classtablee[date][i]==2;}
			if(HavCt[2])cred(HTclas*5);// 我吃好了
			
			if(ega_turnsLeft>0){
				cred(10);
				cblue(10);
				cwhite(10);
				att--;
				ega_turnsLeft--;
			}// 附魔金苹果
		}

		void skhit(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(ega_used){
				if(debug_on){logPrint(10,"[A12] Enchanted Golden Apple already used, skipping.\n");}
				return;
			}
			ega_used=1;
			if(debug_on){logPrint(10,"[A12] Enchanted Golden Apple used! Attacked on %s!\n",target->name.c_str());}
			
			att+=3;
			int final_att=get_att()*(*target).get_be_att_mul();
			target->cred(-final_att);
			if(debug_on){logPrint(10,"[A12] Attack damage: %d\n",final_att);}
			
			cred(15);
			ega_turnsLeft=3;
			
			if(debug_on){
				logPrint(10,"[A12] Enchanted Golden Apple used! Attack with +3 ATK, +15 HP, next 3 turns: +10 HP/SAN/STA, -1 ATK per turn.\n");
			}
		}
};
