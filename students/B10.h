#include "A0.h"

class stud_B10:public stud{
	public:
		int cnt_x=0;
		
		stud_B10(){
			red_up-=4,blue_up-=20,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=3;
			ct1.pb("Subjective!!");
			ct1.pb("Shouldn't...");
			ct2.pb("UnforeseenDisaster");
			id=23;
			name="B10";
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
		
		// 计算已死亡学生数量
		int get_dead_count(bool is_late_night){
			int total=is_late_night?10:6;
			int dead=0;
			for(auto x:listA){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!isalive[s->id]||s->red<0){dead++;}
			}
			for(auto x:listB){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!isalive[s->id]||s->red<0){dead++;}
			}
			if(dead>total){dead=total;}
			return dead;
		}
		
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(HavCt[1]){
				cnt_x=0;
				for(auto y:team){cnt_x+=(*y).status==1;}
				for(auto y:beside_team){cnt_x+=(*y).status==1;}
				att_mul[0].first=1+0.2*cnt_x;
				be_att_mul[0].first=1+0.2*cnt_x;
				
				if(HavCt[2])if(is_crazy){
					for(auto y:beside_team){(*y).cred(5*get_att());}
					cwhite(0.9*white);
				}	
			}
			
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			bool is_late_night=(clas==8);
			int total_players=is_late_night?10:6;
			int x=get_dead_count(is_late_night);
			
			if(x<=0){
				if(debug_on){logPrint(10,"[B10] No one dead! Unforeseen Disaster ineffective.\n");}
				return;
			}
			
			int white_cost=10+x;
			if(white<white_cost){
				if(debug_on){logPrint(10,"[B10] Not enough stamina! Need %d, have %d\n",white_cost,white);}
				return;
			}
			
			cwhite(-white_cost);
			cblue(-(5+2*x));
			
			if(debug_on){logPrint(10,"[B10] Unforeseen Disaster! Dead count: %d, Cost: %d STA, %d SAN\n",x,white_cost,5+2*x);}
			
			vector<stud*> all_enemies;
			for(auto s:beside_team){
				if(s!=NULL&&isalive[s->id]&&s->red>0){
					s->cred(-6*x);
					s->cblue(-4*x);
					if(debug_on){
						logPrint(10,"[B10] Enemy %s: -%d HP, -%d SAN\n",s->name.c_str(),6*x,4*x);
					}
				}
			}
			
			int oldAtt=att;
			att=att-2;
			if(att<0){att=0;}
			int final_att=get_att()*target->get_be_att_mul();
			target->cred(-final_att);
			att=oldAtt;
			
			if(debug_on){logPrint(10,"[B10] Attack on %s! Damage: %d\n",target->name.c_str(),final_att);}
		}
};
