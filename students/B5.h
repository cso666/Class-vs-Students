#include "A0.h"

class stud_B5:public stud{
	public:
		stud_B5(){
			red_up+=2,blue_up+=6,white_up-=0;
			red=red_up,blue=blue_up,white=white_up;
			B5emo=0;
			att-=1;
			ct2.pb("GoHome");//回家
			ct2.pb("pi2gu4");//
			ct1.pb("emo");//
			id=18;
			name="B05";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			if(B5emo&&rand()%5==1){
				int qx=(target -> att)*(target -> att_mul)*(be_att_mul)+(target -> tmp_att_plus);
				target -> cred(qx);
			}		
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
			if(rand()%5==1){
					int randa=rand()%3;
					int randb=rand()%3;
					if(randa==0){
						if(randb==0){
							cred(-3);
							cred(2);
						}
						if(randb==1){
							cred(-3);
							cblue(2);
						}
						if(randb==2){
							cred(-3);
							cwhite(2);
						}
					}
					if(randa==1){
						if(randb==0){
							cblue(-3);
							cred(2);
						}
						if(randb==1){
							cblue(-3);
							cblue(2);
						}
						if(randb==2){
							cblue(-3);
							cwhite(2);
						}
					}
					if(randa==3){
						if(randb==0){
							cwhite(-3);
							cred(2);
						}
						if(randb==1){
							cwhite(-3);
							cblue(2);
						}
						if(randb==2){
							cwhite(-3);
							cwhite(2);
						}
					}
				}
			if(blue_up*0.6>blue&&!B5emo){
				B5emo=1;
				be_att_mul-=0.4;
			}
			if(blue_up*0.6<=blue&&B5emo){
				B5emo=0;
				be_att_mul+=0.4;
			}
		}

};
