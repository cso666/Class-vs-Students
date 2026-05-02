#include "A0.h"

class stud_B15:public stud{
	private:
		int rain;
		bool is_spr;
		int original_att;

	public:
		stud_B15(){
			red_up+=2,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			original_att=att;
			rain=3;
			is_spr=1;
			py.push_back(2);
			ct2.pb("PerfectRain");
			ct1.pb("SkywardFireworks");
			id=28;
			name="B15";
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
			stud::on_minus_red(target,teach,team,beside_team);
			if(is_spr){
				is_spr=0;
				if(debug_on){logPrint(12,"[B15] %s was hit! Transformed into Ghost of the Bad Rain!\n",name.c_str());}
			}
		}
		
		void on_turn_end(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
			stud::on_turn_end(target,teach,team,beside_team);
			if(is_spr){
				stud* target_student=0;
				double min_ratio=1.0;
				for(auto*s:team){
					if(s&&isalive[s->id]&&s->red>=0){
						double ratio=(double)s->red/s->red_up;
						if(ratio<min_ratio){min_ratio=ratio,target_student=s;}
					}
				}
				if(target_student){
					if(min_ratio<=0.15&&rain>0){
						int target_hp=target_student->red_up*0.2;
						target_student->cred(target_hp-target_student->red);
						rain--;
						if(debug_on){logPrint(10,"[B15-PefectRain] %s restored to 20%% HP! Rain left: %d\n",target_student->name.c_str(),rain);}
					}else{
						target_student->cred(target_student->red_up*0.02);
						if(debug_on){logPrint(10,"[B15-PefectRain] %s restored 2%% HP.\n",target_student->name.c_str());}
					}
				}
			}else{
				stud* target_enemy=0;
				double max_ratio=0.0;
				for(auto*s:beside_team){
					if(s&&isalive[s->id]&&s->red>=0){
						double ratio=(double)s->red/s->red_up;
						if(ratio>max_ratio){max_ratio=ratio,target_enemy=s;}
					}
				}
				if(target_enemy){
					if(max_ratio<=0.15&&rain>0){
						target_enemy->cred(-target_enemy->red);
						rain--;
						if(debug_on){logPrint(12,"[B15-PefectRain] %s was executed! Rain left: %d\n",target_enemy->name.c_str(),rain);}
					}else{
						target_enemy->cred(-target_enemy->red_up*0.02);
						if(debug_on){logPrint(12,"[B15-PefectRain] %s took 2%% HP damage.\n",target_enemy->name.c_str());}
					}
				}
			}
		}
		
		void on_class_end(){
			is_spr=1;
			if(debug_on){logPrint(10,"[B15] %s returned to Son of the Perfect Rain.\n",name.c_str());}
		}
		
		void on_enemy_death(vector<stud*>& team){
			for(auto*s:team){
				if(s&&isalive[s->id]&&s->red>=0){
					if(s->is_crazy){
						s->blue=1;
						if(debug_on){logPrint(10,"[B15-SkywardFireworks] %s is insane! Blue set to 1.\n",s->name.c_str());}
					}else if(s->status==-1){
						s->white=1;
						if(debug_on){logPrint(10,"[B15-SkywardFireworks] %s is exhausted! White set to 1.\n",s->name.c_str());}
					}else{
						s->blue=s->blue*1.2;
						s->white=s->white*1.2;
						if(debug_on){logPrint(10,"[B15-SkywardFireworks] %s blue and white increased by 1.2x!\n",s->name.c_str());}
					}
				}
			}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
		}
};