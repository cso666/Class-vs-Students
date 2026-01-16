   #include "A0.h"

class stud_B14:public stud{
	public:
		stud_B14(){
			red_up-=8,blue_up-=12,white_up-=4;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			ct1.pb("Baby");//宝宝
			ct2.pb("Self-healing");//自愈
			ct2.pb("Sorry");//抱歉
			id=27;
			name="B14";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
					stud::before_att(target,teach,team,beside_team);
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);			
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_before_be_atted(target,teach,team,beside_team);			
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
		}
};
