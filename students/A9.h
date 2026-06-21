#include "A0.h"

class stud_A9:public stud{
	public:
		int res_red;
		stud_A9(){
			red_up-=25,blue_up+=10,white_up+=80;
			red=red_up,blue=blue_up,white=white_up;
			att+=1;
			py.push_back(15);
			ct1.push_back("MrMonitor");//班长大人
			//ct1.push_back("Peacemaker");//劝架使者
			ct1.push_back("AbundantSupport");//多助之至
			ct2.push_back("FindOut");//太守寻源
			id=9;
			name="A09";
		}
		
		Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			res_red=(*target).red;
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
		}
		
		Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num=stud::on_before_be_atted(target,teach,team,beside_team);
			if(HavCt[2]){if(res_red-(*target).red>=18){
					(*target).cblue(-20);
					(*target).cwhite(-20);
			}}	
			return return_num;
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(tim%26==1&&!is_crazy&&status!=-1){
				for(auto x:team){(*x).firstTurnA9=1;}
			}
			if(HavCt[1]){
				int where=-1;
				for(int i=0;i<team.size();i++){
					if((*team[i]).id==9)where=i;
				}
				for(int i=0;i<team.size();i++){
					if(i<where){
						(*team[i]).att_mul.push_back({1.35,0});
						(*team[i]).be_att_rt.update(pair<int,pair<double,int>>{2,{0.3,0}});	
						(*team[i]).att_rt.update(pair<int,pair<int,int>>{2,{40,0}});	
					}
					else{
						(*team[i]).att_mul.push_back({1.35,1});
						(*team[i]).be_att_rt.update(pair<int,pair<double,int>>{2,{0.3,1}});	
						(*team[i]).att_rt.update(pair<int,pair<int,int>>{2,{40,1}});	
					}
				}
			}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			if(debug_on){logPrint(10,"[A09] Find Out used on %s!\n",target->name.c_str());}

			cwhite(-5);
			int final_att=get_att(10)*(target->get_be_att_mul());
			if(final_att<=30){
				target->cred(-final_att);
				if(debug_on){logPrint(10,"[A09] Damage dealt: %d (capped by normal limit)\n",final_att);}
			}else if(final_att<40){
				target->cred(-30);
				target->cred(-(final_att-30));
				if(debug_on) logPrint(10,"[A09] Damage dealt: 30 + %d = %d (capped 40)\n",final_att-30,final_att);
			}else if(final_att>=40){
				target->cred(-30);
				target->cred(-10);
        		if(debug_on){logPrint(10,"[A09] Damage dealt: 40 (hard cap)\n");}
			}
			for(auto x:team){
				x->fromA9=1;
				x->cred(final_att/3);
				x->fromA9=0;
			}
			if(debug_on){logPrint(10,"[A09] All allies healed %d HP.\n",final_att/3);}
		}
};
