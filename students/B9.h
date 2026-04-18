#include "A0.h"

class stud_B9:public stud{
	public:
		bool is_upset=0;
		stud_B9(){
			is_upset=0;
			red_up+=3,blue_up+=0,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(4);
			ct1.pb("Adonis");//男神
			ct1.pb("Sad");//伤感
			ct2.pb("Perfect … Miss … ");//成也…败也…
			id=22;
			name="B09";
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::before_att(target,teach,team,beside_team);
			for(auto y:team){
				if((*y).id==9)att_mul*=1.5;
			}
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::after_att(target,teach,team,beside_team);	
			att_mul/=1.5;		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			    stud::on_minus_red(target,teach,team,beside_team);
						
		}
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_start(target,teach,team,beside_team);
			for(auto y:team){
				(*y).cred((*y).red_up*0.05);
			}
			if(red<=65) att_mul*=0.4,be_att_mul*=0.2,is_upset=1;
			if(is_upset==1&&red>65) att_mul/=0.4,be_att_mul/=0.2,is_upset=0;
			
			//fuck yuyuanjiang!why your ct so hard to write?
			bool isin2=0;
			int tr=red,tb=blue,tw=white;
			while(tr){
				if(tr%10==2)isin2=1;
				tr/=10;
			}
			while(tb){
				if(tb%10==2)isin2=1;
				tb/=10;
			}
			while(tw){
				if(tw%10==2)isin2=1;
				tw/=10;
			}if(isin2)cred(11),cwhite(16);
		}
};
