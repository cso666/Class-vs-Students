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
		//(B6)
		double B6CADB;
		//伟大的扒皮！(B4)
		bool weidadebp;
		//(B5)
		bool B5emo;
		//(B3)
		bool teacher_is_HT;
		bool has_A10;

		int red,red_up;//红条血量，上限 
		int blue,blue_up;//蓝条理智，上限 
		int white,white_up;//白条体力，上限 
		double white_mul=1.0,blue_mul=1.0,red_mul=1.0;
		int att;double att_mul,be_att_mul;//伤害和伤害乘区 
		vector<int> py;//属性
		vector<string>ct1,ct2;//词条 1:被动 2:主动 
		
		int id=0;
		string name="A0";
		bool can_act=true;//能否行动，用于“沉默”。
		int cant_act=-1;//多少回合不能行动
		int tmp_att_plus=0;//临时攻击加成
		bool is_crazy=false;//疯人状态标记
		int status=1;
		
		int cred(int chg){
			red+=chg*red_mul;
			red=min(red,red_up);
			if(red<0)red=0,status=0;
			return status;
		}
		int cwhite(int chg){
			if(id==19){
				chg*=1.2;
			}
			white+=chg*white_mul;
			white=min(white,white_up);
			if(white<0)status=-1;
			else if(white>=0&&status==-1){status=1;}
			return status;
		}
		int cblue(int chg){
			if(id==14){
				chg*=1.35;
				cred(8);
			}
			blue+=chg*blue_mul;
			blue=min(blue,blue_up);
			if(blue<0) is_crazy = true;
			return status;
		}
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
				if((*x).id==7&&id!=7){
					(*x).cred(-final_att*0.8);
					cred(final_att*0.8);
				}
			
			for(auto x:beside_team)
				if((*x).id==9&&final_att>=18){
					cblue(-2);
					cwhite(-2);
				}
		}
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			tmp_att_plus=0;
			if(cant_act>=0){
				cant_act--;
				can_act=false;
			}
			else{can_act=true;}
			// 疯人状态处理（扣血）
			if(is_crazy){
				cred(-10);
				// 检查是否解除疯人状态
				if(blue >= 0){
					is_crazy=false;
					att_mul/=1.5;
				}
			}
			// 力竭状态处理（白条归零 status=-1）
			if(status == -1){
				can_act=false;// 无法行动
				be_att_mul *= 1.3;// 防御力下降
				cred(-5);// 每回合扣5血
			}
		}//每回合开始前（多测要清空
		virtual void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int fwry=0;
			fwry=1;
		}//每个回合结束后（不知道有什么用但留着请别删
		stud(){
			red=red_up=blue=blue_up=white=white_up=100;
			white_mul=1.0;
			blue_mul=1.0;
			red_mul=1.0;
			att=10;att_mul=1.0;be_att_mul=1.0;
			py.clear();
			ct1.clear();
			ct2.clear();
			
			id=0;name="A0";
		}
};

int toge_fight(vector<stud*> team){//連擕技
	set<int> st;
	for(auto y:team)st.insert((*y).id);
	if(st.count(20)&&st.count(21)&&st.count(24)){
		return 1;
	}
	else return -1;
}
#endif
