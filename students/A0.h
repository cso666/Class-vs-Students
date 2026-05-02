#ifdef pb
	#undef pb
#endif
#define pb push_back
#ifndef __stud__
#define __stud__

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<time.h>
#include<stdarg.h>
#include<string>
using namespace std;

extern bool debug_on;
extern void logPrint(int colorCode,const char*format,...);
extern int day,clas;
extern int classtable[5][8];

string ppty_name[100]={"占位",
					   "语表"/*1*/,"数表"/*2*/,"英表A"/*3*/,"英表B"/*4*/,
					   "史表"/*5*/,"政表"/*6*/,"体委"/*7*/,"物表"/*8*/,"信表"/*9*/,"美表"/*10*/,
					   "音表"/*11*/,"生表"/*12*/,"地课"/*13*/,"词法组"/*14*/,"牢门"/*15*/};

class stud{
	private:
	public:
		int tim;
		
		bool Bighuocar=0;  // A7用，暂留

		int red,red_up;
		int blue,blue_up;
		int white,white_up;
		// 新版乘区系统：vector存储，pair.first=倍率，pair.second=剩余回合数
		vector<pair<double,int>> white_mul,blue_mul,red_mul;
		int att;
		vector<pair<double,int>> att_mul,be_att_mul;
		vector<pair<int,int>> tmp_att_plus;  // 临时攻击力加成 (值, 剩余回合)
		vector<int>py;
		vector<string>ct1,ct2;
		
		int id=0;
		string name="A0";
		//能不能动
		bool can_act=1;
		//几个回合不能动
		int cant_act=-1;
		bool is_crazy=0;
		int status=1;
		
		// 听讲
		bool listen=1;
		int listen_punish=0;
		// 语文卡
		char chinese_double=0,chinese_forgive=0,chinese_pass=0;
		// A04超能力者标记
		bool espp=0;
		// B06隐藏血条
		bool hide_bars=0;
		// A09全局（给我待在A0！！）
		bool firstTurnA9=0,fromA9=0;
		
		// 计算当前是第几天第几节课第几回合
		pair<pair<int,int>,int> Dtee(){
			int d=tim/26+1;
			int c=tim%26>21?8:tim%26/3+1;
			int t=tim-(d-1)*26-(d-1)*26;
			return {{d,c},t};
		}
		
		// 获取当前红条倍率 (sc: 0=增加时, 1=减少时)
		double get_red_mul(){
			double ans=1.0;
			for(auto y:red_mul) ans*=y.first;
			return ans;
		}
		double get_blue_mul(){
			double ans=1.0;
			for(auto y:blue_mul) ans*=y.first;
			return ans;
		}
		double get_white_mul(){
			double ans=1.0;
			for(auto y:white_mul) ans*=y.first;
			return ans;
		}
		
		// 获取最终攻击力
		int get_att(){
			double ans=att;
			for(auto y:att_mul) ans*=y.first;
			for(auto y:tmp_att_plus) ans+=y.first;
			return (int)ans;
		}
		// 重载：传入临时攻击力
		int get_att(int t_att){
			double ans=t_att;
			for(auto y:att_mul) ans*=y.first;
			for(auto y:tmp_att_plus) ans+=y.first;
			return (int)ans;
		}
		int get_tmp_att_plus(){
			int ans=0;
			for(auto y:tmp_att_plus) ans+=y.first;
			return ans;
		}
		double get_att_mul(){
			double ans=1.0;
			for(auto y:att_mul) ans*=y.first;
			return ans;
		}
		double get_be_att_mul(){
			double ans=1.0;
			for(auto y:be_att_mul) ans*=y.first;
			return ans;
		}
		
		// 扣血
		virtual int cred(int chg){
			if(chg<0){red+=chg*get_red_mul();}
			else{red+=chg;}
			red=min(red,red_up);
			if(red<0){red=0,status=0;}
			return status;
		}
		// 扣体力
		virtual int cwhite(int chg){
			if(chg<0){white+=chg*get_white_mul();}
			else{white+=chg;}
			white=min(white,white_up);
			if(white<0){
				status=-1;
				// A10技能重置逻辑移至子类
			}
			else if(white>=0&&status==-1){status=1;}
			return status;
		}
		// 扣理智
		virtual int cblue(int chg){
			if(chg<0){blue+=chg*get_blue_mul();}
			else{blue+=chg;}
			blue=min(blue,blue_up);
			if(blue<0){is_crazy=1;}
			return status;
		}

		virtual int before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){return 0;}
		virtual void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){;}
		virtual int on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			for(auto x:team){
				if((*x).id==9&&rand()%100<=9){return 1;}
			}
			return 0;
		}
		virtual void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			int final_att=target->get_att()*get_be_att_mul();
			for(auto x:team){
				if((*x).id==7&&id!=7){
					(*x).cred(-final_att*0.8);
					cred(final_att*0.8);
				}
			}
			for(auto x:beside_team){
				if((*x).id==9&&final_att>=18){
					cblue(-20);
					cwhite(-10);
				}
			}
		}

		// 回合开始：自动减少所有临时乘区的回合数
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			tim++;
			// 红条倍率过期
			for(int i=0;i<red_mul.size();i++){
				if(red_mul[i].second<=0) red_mul.erase(red_mul.begin()+i),i--;
				else red_mul[i].second--;
			}
			// 蓝条倍率过期
			for(int i=0;i<blue_mul.size();i++){
				if(blue_mul[i].second<=0) blue_mul.erase(blue_mul.begin()+i),i--;
				else blue_mul[i].second--;
			}
			// 白条倍率过期
			for(int i=0;i<white_mul.size();i++){
				if(white_mul[i].second<=0) white_mul.erase(white_mul.begin()+i),i--;
				else white_mul[i].second--;
			}
			// 攻击倍率过期
			for(int i=0;i<att_mul.size();i++){
				if(att_mul[i].second<=0) att_mul.erase(att_mul.begin()+i),i--;
				else att_mul[i].second--;
			}
			// 受击倍率过期
			for(int i=0;i<be_att_mul.size();i++){
				if(be_att_mul[i].second<=0) be_att_mul.erase(be_att_mul.begin()+i),i--;
				else be_att_mul[i].second--;
			}
			// 临时攻击力加成过期
			for(int i=0;i<tmp_att_plus.size();i++){
				if(tmp_att_plus[i].second<=0) tmp_att_plus.erase(tmp_att_plus.begin()+i),i--;
				else tmp_att_plus[i].second--;
			}
			
			if(cant_act>=0){
				cant_act--;
				can_act=0;
			}
			else{can_act=1;}
			
			if(is_crazy){
				cred(-10);
				if(blue>=0){
					is_crazy=0;
					// 移除疯人1.5倍乘区
					for(int i=0;i<att_mul.size();i++){
						if(att_mul[i].first==1.5){
							att_mul.erase(att_mul.begin()+i);
							break;
						}
					}
				}
			}
			if(status==-1){
				can_act=0;
				be_att_mul.push_back({1.3, 1});
				cred(-5);
			}
		}
		
		virtual void on_turn_end(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){;}
		virtual void on_day_start(int subject_id){;}
		virtual void on_fight_end(){;}
		virtual void on_enemy_death(vector<stud*>&team){;}
		virtual bool isAway()const{return 0;}
		virtual void resetDaily(){;}
		virtual void resetRain(){;}
		virtual void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){;}
		
		stud(){
			tim=0;
			red=red_up=blue=blue_up=white=white_up=100;
			// 永久乘区用很大的剩余回合数表示
			white_mul.push_back({1.0,0x7f7f7f7f});
			blue_mul.push_back({1.0,0x7f7f7f7f});
			red_mul.push_back({1.0,0x7f7f7f7f});
			att=10;
			att_mul.push_back({1.0,0x7f7f7f7f});
			be_att_mul.push_back({1.0,0x7f7f7f7f});
			tmp_att_plus.push_back({0,0x7f7f7f7f});
			py.clear();
			ct1.clear();
			ct2.clear();
			
			id=0;name="A0";
			Bighuocar=0;
			espp=0;
			hide_bars=0;
		}
};

int toge_fight(vector<stud*> team){
	set<int> st;
	for(auto y:team){st.insert((*y).id);}
	if(st.count(20)&&st.count(21)&&st.count(24)){return 1;}
	else{return -1;}
}

// 政治全局伤害倍率
float global_damage_mult=1.0f;
// 物理标记 & 英语B替罪羊
stud*physics_marked=NULL;
stud*scapegoat=NULL;

#endif