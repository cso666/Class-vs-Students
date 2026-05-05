#include"A0.h"

class stud_B3:public stud{
	public:
		bool teacher_is_HT=0;  // 从A0移入
		bool has_A10=0;  // 从A0移入

		stud_B3(){
			red_up+=0,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			py.push_back(1);
			ct1.pb("Tutor(TA)");
			ct1.pb("Calm&Composed");
			ct1.pb("MathDUO");
			ct2.pb("HalfAngle");// 夹半角
			id=16;
			name="B03";
		}

		void on_turn_start(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
			stud::on_turn_start(target,teach,team,beside_team);
		}
		
		void on_turn_end(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
			stud::on_turn_end(target,teach,team,beside_team);
			if(HavCt[2])cred(5);
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cblue(10);
			cwhite(10);
			target->cblue(-10);
			target->cwhite(-10);
			int final_skhit=get_att(5)*(*target).get_be_att_mul();
			target->cred(-final_skhit);
		}
};
