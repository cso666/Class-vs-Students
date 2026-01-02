#include "headers.h"
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
						"音表"/*11*/,"生表"/*12*/,"地课"/*13*/,"词法组"/*14*/,"OIer"/*15*/,"大运"/*16*/,
						"班长"/*17*/,"唐氏"/*18*/,"牢门"/*19*/};//属性（ppty）名字 


class stud{
	private:
	public:
		int red,red_up;//红条血量，上限 
		int blue,blue_up;//蓝条理智，上限 
		int white,white_up;//白条体力，上限 
		 
		int att;double att_mul;//伤害和伤害乘区 
		vector<int> py;//属性
		vector<string>ct1,ct2;//词条 1:被动 2:主动 
		
		int id=0;
		string name="A0";
		stud(){
			red=red_up=blue=blue_up=white=white_up=100;
			att=10;att_mul=1.0;
			py.clear();
			ct1.clear();
			ct2.clear();
			
			id=0;name="A0";
		}
};
#endif
