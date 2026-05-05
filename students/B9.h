#include "A0.h"

class stud_B9:public stud{
	public:
		bool is_upset=0;
		int last_use_day=-1;
		map<stud*,bool>target_marked;
		int original_att;
		
		stud_B9(){
			is_upset=0;
			last_use_day=-1;
			original_att=att;
			red_up+=3,blue_up+=0,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(4);
			ct1.pb("Adonis");
			ct1.pb("Sad");
			ct2.pb("Fiddler");
			id=22;
			name="B09";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			if(HavCt[1])for(auto y:team){
				if((*y).id==9){
					att_mul.push_back({1.5,0x7f7f7f7f});
				}
			}
			return return_num;
		}
		
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(HavCt[2]){
				if(red<=65){
					att_mul[0].first=0.4;
					be_att_mul[0].first=0.2;
					is_upset=1;
				}
				if(is_upset==1&&red>65){
					att_mul[0].first=1.0;
					be_att_mul[0].first=1.0;
					is_upset=0;
				}
				
				bool isin2=0;
				int tr=red,tb=blue,tw=white;
				while(tr){
					if(tr%10==2){isin2=1;}
					tr/=10;
				}
				while(tb){
					if(tb%10==2){isin2=1;}
					tb/=10;
				}
				while(tw){
					if(tw%10==2){isin2=1;}
					tw/=10;
				}
				if(isin2){cred(11),cwhite(16);}	
			}
			
		}

		void on_day_start(int subject_id){;}
		bool can_use_this_day(int current_day){
			if(last_use_day==-1){return 1;}
			return(current_day-last_use_day)>=2;
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(!can_use_this_day(day)){
				if(debug_on){logPrint(10,"[B09] Fiddler already used in these two days!\n");}
				return;
			}
			if(target_marked[target]){
				if(debug_on){logPrint(10,"[B09] %s already targeted by Fiddler!\n",target->name.c_str());}
				return;
			}
			if(white<10){
				if(debug_on){logPrint(10,"[B09] Not enough stamina for Fiddler!\n");}
				return;
			}
			
			cwhite(-10);
			cblue(5);
			
			last_use_day=day;
			target_marked[target]=1;
			
			if(debug_on){
				logPrint(10,"[B09] Fiddler used on %s! -10 STA, +5 SAN\n",target->name.c_str());
			}
			
			int y=get_att();
			int old_tmp=get_tmp_att_plus();
			int x=get_att()*target->get_be_att_mul();
			
			int damCap=30;
			if(this->id==9&&((stud_A9*)this)->firstTurnA9){damCap=40;}
			if(x>damCap){x=damCap;}
			
			x=x*global_damage_mult;
			
			if(debug_on){logPrint(10,"[B09] y (raw damage): %d, x (actual damage): %d\n",y,x);}
			
			int delta=max(x-y,0);
			
			if(delta>0){
				tmp_att_plus.push_back({delta,0x7f7f7f7f});
				target->att-=delta/2;
				if(target->att<0){target->att=0;}
				
				if(debug_on){
					logPrint(10,"[B09] delta=%d, B09 +%d ATK permanently, %s -%d ATK permanently.\n",
						delta,delta,target->name.c_str(),delta/2);
				}
			}
			
			target->cred(-x);
			if(debug_on){logPrint(10,"[B09] Attack dealt %d damage to %s!\n",x,target->name.c_str());}
		}
};
