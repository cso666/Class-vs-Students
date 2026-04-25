#include"A0.h"
int classtablee[100+10][100+10]={{6,2,8,3,9,1,0},{2,13,4,1,7,8,5},{1,1,2,3,11,8,0},{1,8,12,7,10,4,2},{3,4,2,2,6,5,0}};
class stud_A12: public stud{
	public:
		double base_be_att_mul = 1.0;
		stud_A12(){
			red_up+=10;blue_up+=-20;white_up-=-10;
			red=red_up;blue=blue_up;white=white_up;
			att+=0;
			py.push_back(15);
			ct1.pb("EatWell");//我吃好了
			ct1.pb("YouXianglinSao");//并非蠢货 （何意味？？
			ct1.pb("YogHURT");//酸奶
			ct2.pb("EnchantedGoldenApple");//附魔金苹果
			id=12;
			name="A12";
			base_be_att_mul = be_att_mul;
		}
		int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		    int return_num=stud::before_att(target,teach,team,beside_team);
			if((*target).id==8){
				int final_att=(att*att_mul*(*target).be_att_mul+tmp_att_plus);
				for(auto x:beside_team){
					if((*x).id!=8)(*x).cred((rand() % 40) *0.01*final_att);
				}
			}	
			return return_num;
		}
		void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
				stud::after_att(target,teach,team,beside_team);		
		}
		int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int return_num=stud::on_before_be_atted(target,teach,team,beside_team);	
			be_att_mul *= max((150.0-blue)/150.0,1.0);
			return return_num;		
		}
		void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_minus_red(target,teach,team,beside_team);	
			be_att_mul *= max((150.0-blue)/150.0,1.0);
		}
		void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			stud::on_turn_end(target,teach,team,beside_team);
			be_att_mul = base_be_att_mul;
			int date=tim/26;
			if(tim%26!=0)return;
			int HTclas=0;
			for(int i=0;i<7;i++)HTclas+=classtablee[date][i]==2;
			cred(HTclas*5);
		}
		void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		
	}
};
