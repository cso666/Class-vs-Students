#include"../headers.h"
using namespace std;
#ifdef pb
    #undef pb
#endif
#define pb push_back
#ifndef __stud__
#define __stud__
string ppty_name[100]={"占位",
				  	   "语表"/*1*/,"数表"/*2*/,"英表A"/*3*/,"英表B"/*4*/,
						"史表"/*5*/,"政表"/*6*/,"体委"/*7*/,"物表"/*8*/,"信表"/*9*/,"美表"/*10*/,
						"音表"/*11*/,"生表"/*12*/,"地课"/*13*/,"词法组"/*14*/,"牢门"/*15*/};//属性（ppty）名字 


class stud{
	private:
	public:
		int red,red_up;//红条血量，上限 
		int blue,blue_up;//蓝条理智，上限 
		int white,white_up;//白条体力，上限 
		double white_mul;
		int att;double att_mul,be_att_mul;//伤害和伤害乘区 
		vector<int> py;//属性
		vector<string>ct1,ct2;//词条 1:被动 2:主动 
		
		int id=0;
		string name="A0";
		bool can_act=true;//能否行动，用于“沉默”。
		int cant_act=-1;//多少回合不能行动
		int tmp_att_plus=0;//临时攻击加成
		virtual int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){/*（虚函数，可以在子类里直接重定义*/
			//攻击之前
			return 0;
		}
		virtual void after_att(stud* target/*被攻击的学生*/,int teach,vector<stud*>team,vector<stud*>beside_team){
			//攻击之后
		}
		virtual int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			//被攻击时
			for(auto x:team)
				if((*x).id==9&&rand()%100<=9) return 1;
				
			return 0;
		}
		virtual void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			//受到伤害时
			int final_att=((*target).att*(*target).att_mul*be_att_mul+(*target).tmp_att_plus);
			for(auto x:team)
				if((*x).id==7) (*x).red-=final_att*0.8,red+=final_att*0.8;
			
			for(auto x:beside_team)
				if((*x).id==9&&final_att>=18)blue-=20,white-=20;
		}
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			tmp_att_plus=0;
			if(cant_act>=0){
				cant_act--;
				can_act=false;
			}
			else{
				can_act=true;
			}
		}//每回合开始前（多测要清空
		virtual void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			
		}//每个回合结束后（不知道有什么用但留着请别删
		stud(){
			red=red_up=blue=blue_up=white=white_up=100;
			white_mul=1.0;
			att=10;att_mul=1.0;be_att_mul=1.0;
			py.clear();
			ct1.clear();
			ct2.clear();
			
			id=0;name="A0";
		}
};
#endif
