#include"A0.h"

class stud_A3:public stud{
	public:
		bool mother[100];  // 从A0移入
		vector<pair<stud*,int> >hurtme; 
		
		stud_A3(){
			red_up+=20,blue_up+=35,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=6;
			hurtme.clear();
			memset(mother,0,sizeof(mother));
			py.push_back(2);
			py.push_back(10);
			py.push_back(15);
			ct1.push_back("BecomeRed");//红温
			ct1.push_back("ThingsDisappeared");//东西被偷了
			//ct1.push_back("BecomeRed2nd");红温2nd
			ct2.push_back("YouMother");//
			id=3;
			name="A03";
		}
		
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			
			target->be_att_mul.push_back({1.30,2});
			hurtme.push_back({target,2});
			if(HavCt[2])if(rand()%2){
				cblue(-5);
				cred(5);
				cwhite(5);
			}
			
			if(mother[(*target).id]==1){
				target->cblue(-15);
				cblue(5);
				target->blue_mul[0].first*=1.05;
			}
			
			return return_num;
		}
		
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
		}
		
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num = stud::on_before_be_atted(target,teach,team,beside_team);	
			if(HavCt[1]){
				target->be_att_mul.push_back({1.30,2});
				hurtme.push_back({target,2});
				int tmp=0;
				int lry=0;
				for(auto x : hurtme){
					if(hurtme[lry].first==target){
						tmp++;
					}
					lry++;
				}
				if(tmp==3){
					(*target).blue=0;
					cblue(-20);
				}
			}
			
			return return_num;
		}
		
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			if(rand()%2==1)cblue(-5);
			for(int i=0;i<hurtme.size();i++){
				hurtme[i].second-=1;
				if(hurtme[i].second<0){
					hurtme.erase(hurtme.begin()+i);
					i--;
				}
			}
		}
		
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-5);
			cred(-15);
			cblue(-25);
			target->cred(-5);
			mother[(*target).id]=1;
		}
		
		void on_day_start(int subject_id){
			for(int i=0;i<=29;i++)
				mother[i]=0;
		}
};
