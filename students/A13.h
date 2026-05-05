#include"A0.h"

class stud_A13:public stud{
	public:
		int ypw_left=0,ypw_oria=0;  // 从A0移入
		
		stud_A13(){
			red_up-=10,blue_up+=-10,white_up-=-30;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			py.push_back(12);
			py.push_back(15);
			ct1.pb("WeAreLegends");
			ct1.pb("SoDelicious");
			ct2.pb("YearPigWeigh");
			id=13;
			name="A13";
			ypw_left=0;
			ypw_oria=att;
		}

		int before_att(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			int wum=0;
			for(auto x:team){
				if(x->espp){affected=1;}// 这叫获得神谕！！
				wum+=x->white;
			}
			if(HavCt[1])att_mul.push_back({max(wum/500.0,1.0),1});
			return return_num;
		}

		int on_before_be_atted(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			return stud::on_before_be_atted(target,teach,team,beside_team);
		}
		
		void on_minus_red(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);
			int final_att=(*target).get_att()*get_be_att_mul();
			if(HavCt[2])cwhite(final_att);
		}

		void on_turn_start(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			affected=0;
			if(ypw_left>0){
				if(white<white_up*0.7){
					ypw_left=0;
					att=ypw_oria;
					if(debug_on){logPrint(10,"[A13] Year Pig Weigh ended early (STA < 70%%), ATK restored to %d.\n",att);}
				}
			}
		}

		void on_turn_end(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			if(ypw_left>0){
				ypw_left--;
				if(ypw_left==0){
					att=ypw_oria;
					if(debug_on){logPrint(10,"[A13] Year Pig Weigh ended, ATK restored to %d.\n",att);}
				}else if(debug_on){logPrint(10,"[A13] Year Pig Weigh turns left: %d, current ATK=%d\n",ypw_left,att);}
			}
		}

		void skhit(stud*target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(white<white_up*0.7){
				if(debug_on){logPrint(10,"[A13] Year Pig Weigh failed: STA = %d (<70%%)\n",white);}
				return;
			}
			if(ypw_left==0){ypw_oria=att;}
			if(debug_on){logPrint(10,"[A13] Year Pig Weigh used on %s! STA = %d\n",target->name.c_str(),white);}
			
			int oldAtt=att;
			att=8;
			int final_att=get_att()*(*target).get_be_att_mul();
			if(final_att>30){final_att=30;}
			target->cred(-final_att);
			att=oldAtt;
			if(debug_on){logPrint(10,"[A13] Year Pig Weigh first hit! ATK=8, damage=%d (capped 30).\n",final_att);}
			
			ypw_left=3;
			att=18;
			if(debug_on){logPrint(10,"[A13] Year Pig Weigh active! Next 3 turns: ATK=18, damage cap 40.\n");}
		}
};
