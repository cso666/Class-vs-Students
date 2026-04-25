#include "A0.h"

class stud_B2:public stud{
	public:
		stud_B2(){
			red_up-=7,blue_up-=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			be_att_mul=1.08;
			att+=2;
			py.push_back(13);
			ct1.pb("TalkBack");//顶嘴
			ct2.pb("Barking");//犬吠
			//ct1.pb("Height(DIS)Adv.");//身高优势
			ct1.pb("Recitalist");//朗诵家
			id=15;
			name="B02";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			if(!isalive[target -> id]){
				for(auto x:beside_team){
					x -> cred((x -> red)*0.08);
				}
			}		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			int fs=(target -> att)*(target -> att_mul)*(be_att_mul)+(target -> tmp_att_plus);
			if(fs>=0.4*red&&rand()%20<=6){
				cwhite(-12);
			    return 5;
			}
			return return_num;		
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int final_att=(10*att_mul*(*target).be_att_mul+tmp_att_plus);
			(*target).cred(final_att*-1);
			(*target).cblue(-12);
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);	
			    int fs=(target -> att)*(target -> att_mul)*(be_att_mul)+(target -> tmp_att_plus);
			    if(fs>=0.4*red&&rand()%20<=6){
			    	
				}
				if(rand()%20<=6){
					
					fs*=0.60;
					target -> cred(-fs);
				}	
		}
};
