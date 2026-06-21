#include"A0.h"

class stud_A3:public stud{
	public:
		bool mother[205];  // 从A0移入
		vector<pair<stud*,int> >hurtme; 
		bool isb[205];
		
		stud_A3(){
			red_up+=20,blue_up+=35,white_up+=20;
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
		
		virtual Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
			
			if(HavCt[1]){
				target->be_att_mul.push_back({1.30,2});
				hurtme.push_back({target,2});
				int tmp=0;
				int lry=0;
				for(auto x : hurtme){
					if(x.first==target){
						tmp++;
					}
				}
				if(tmp==3){
					(*target).blue=0;
					cblue(-20);
				}
			}
			if(HavCt[2]){if(rand()%2){
				cwhite(-5);
				cred(5);
				cwhite(30);
			}}
			
			if(mother[(*target).id]==1){
				target->cblue(-15);
				cblue(5);
				target->blue_mul[0].first*=1.05;
			}
			
			return return_num;
		}
		
		virtual void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);		
		}
		
		virtual Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			Return_BeHit return_num = stud::on_before_be_atted(target,teach,team,beside_team);	
			if(HavCt[1]){
				isb[(*target).id]=1;
				target->be_att_mul.push_back({1.30,2});
				hurtme.push_back({target,2});
				int tmp=0;
				int lry=0;
				for(auto x : hurtme){
					if(x.first==target){
						tmp++;
					}
				}
				if(tmp==3&&isb[(*target).id]){
					(*target).blue=1;
					(*target).cblue(-1);
					cblue(-20);
				}
			}
			
			return return_num;
		}
		
		virtual void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);		
		}
		
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
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
		
		virtual void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::skhit(target,teach,team,beside_team);
			cwhite(-5);
			cblue(-25);
			target->cred(-5);
			mother[(*target).id]=1;
		}
		
		virtual void on_day_start(int subject_id){
			for(int i=0;i<=29;i++)
				mother[i]=0;
		}
};
class stud_A24:public stud_A3{
	public:
		
		stud_A24(){
			red_up+=0,blue_up+=100,white_up+=50;
			red=red_up,blue=blue_up,white=white_up;
			blue_mul[0].first*=0.8;
			att+=1;
			hurtme.clear();
			memset(mother,0,sizeof(mother));
			py.push_back(2);
			py.push_back(10);
			py.push_back(15);
			HavCt[1]=1;
			HavCt[2]=1;
			HavCt[0]=1;
			ct1.push_back("BecomeRed");//红温
			ct1.push_back("ThingsDisappeared");//东西被偷了
			//ct1.push_back("BecomeRed2nd");红温2nd
			ct2.push_back("YouMother");//
			id=3+100;
			name="A24";
		}
		void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			for(int i=0;i<hurtme.size();i++){
				hurtme[i].second-=1;
				if(hurtme[i].second<0){
					hurtme.erase(hurtme.begin()+i);
					i--;
				}else{
					(*hurtme[i].first).blue-=5;
				}
			}
			cblue(10);
			if(red<=red_up*0.3){
				int gred=red_up*0.5;
				if(blue-1*(gred-red)>=50){
					cred(gred-red);
					cblue(-1*(gred-red));	
				}	
			}
			if(white<=white_up*0.3){
				int gwhite=white_up*0.5;
				if(blue-1*(gwhite-white)>=50){
					cwhite(gwhite-white);
					cblue(-1*(gwhite-white));	
				}	
			}
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud_A3::skhit(target,teach,team,beside_team);
			cwhite(-30);
			(*target).cwhite(-30);
			(*target).cred(-20);
		}
		void on_day_start(int subject_id){
			for(int i=0;i<=29;i++)
				mother[i]=0;
			
		}
};
