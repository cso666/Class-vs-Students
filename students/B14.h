   #include "A0.h"

class stud_B14:public stud{
	public:
		int cnt_hitme;
		stud_B14(){
			cnt_hitme=2;
			red_up-=24,blue_up+=8,white_up-=10;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			ct1.pb("Baby");//宝宝
			ct2.pb("Self-healing");//自愈
			ct2.pb("Sorry");//抱歉
			id=27;
			name="B14";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
			int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
			int sbhc=rand()*rand()%3,rzhc=rand()*rand()%team.size();
			if(sbhc==1)(*team[rzhc]).cred(6);
			else if(sbhc==2)(*team[rzhc]).cwhite(6);
			else (*team[rzhc]).cblue(6);
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return 3;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);		
			cnt_hitme+1;
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			int sbhc=rand()*rand()%3;
			if(sbhc==1)cred(6);
			else if(sbhc==2)cwhite(6);
			else cblue(6);
			if(blue<60){
				if(att+tmp_att_plus-3>=0)tmp_att_plus-=3,att_mul*=1+cnt_hitme*0.05;
			}
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		
	}
};
