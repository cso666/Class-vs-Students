#include"A0.h"

class stud_B13:public stud{
	private:
		bool takeItEasy_active=0;
		bool is_away=0;
		int original_att;

	public:
		stud_B13(){
			red_up-=20,blue_up+=20,white_up-=30;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			original_att=att;
			takeItEasy_active=0,is_away=0;
			py.push_back(8);
			py.push_back(9);
			ct1.pb("TakeItEasy...");
			ct1.pb("SongsAreLife!");
			ct2.pb("KnowledgeIsPowDer");
			id=26;
			name="B13";
		}

		void on_day_start(){
			if(rand()%100<15){
				takeItEasy_active=1;
				if(debug_on){logPrint(12,"[B13] TakeItEasy... activated! Will lose 10 sanity per turn.\n");}
			}else{takeItEasy_active=0;}
		}
		
		void on_class_start(int subject_id){
			bool is_music_subject=(subject_id==10||subject_id==13||subject_id==12||subject_id==7||subject_id==11);
			
			if(is_music_subject){
				if(rand()%100<80){
					is_away=1;
					if(debug_on){logPrint(10,"[B13] %s goes to listen to music! Away from battle.\n",name.c_str());}
				}else{
					is_away=0;
					att=original_att+6;
					if(debug_on){logPrint(10,"[B13] %s feels inspired! Attack +6.\n",name.c_str());}
				}
			}else{
				is_away=0;
				att=original_att;
			}
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
			stud::on_turn_start(target,teach,team,beside_team);
			if(takeItEasy_active){
				cblue(-10);
				if(debug_on){logPrint(12,"[B13] TakeItEasy... active! -10 sanity. Current: %d\n",blue);}
			}
		}
		
		bool isAway()const{return is_away;}
		
		void resetDaily(){
			takeItEasy_active=0,is_away=0;
			att=original_att;
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(white<20){return;}
			int cost1=0,cost2=0;
			float atk_p=0,atk_m=1.0;

			if(white>=40&&rand()%100<30){cost1=30;atk_p=8;}
			else{cost1=10;atk_p=4;}
			cwhite(-cost1);
			if(white>=40&&rand()%100<30){cost2=30;atk_m=2.0;}
			else{cost2=10;atk_m=1.35;}
			cwhite(-cost2);
			if(white>=10){cwhite(-10);target->cblue(-15);}

			int old_atk_p=get_tmp_att_plus();
			tmp_att_plus.push_back({(int)atk_p,1});
			int final_att=get_att()*atk_m*target->get_be_att_mul();
			target->cred(-final_att);
			// 临时攻击力会在on_turn_start中自动移除
		}
};