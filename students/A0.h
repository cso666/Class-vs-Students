#ifdef pb
	#undef pb
#endif
#define pb push_back
#ifndef __stud__
#define __stud__
#define __stud_ver__ 27

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
#include<queue>
using namespace std;

extern bool debug_on;
extern void logPrint(int colorCode,const char*format,...);
extern int day,clas;
extern int classtable[6][9];

string ppty_name[100]={"占位",
					   "语表"/*1*/,"数表"/*2*/,"英表A"/*3*/,"英表B"/*4*/,
					   "史表"/*5*/,"政表"/*6*/,"体委"/*7*/,"物表"/*8*/,"信表"/*9*/,"美表"/*10*/,
					   "音表"/*11*/,"生表"/*12*/,"地课"/*13*/,"词法组"/*14*/,"牢门"/*15*/};

struct Return_Hit{
	bool onf[100+10];
	int last[100+10];
	int front=4;
	
	int lim_hurt;//1
	double opp_cace;//2
	double pc_spread;//3
	double pc_takplac;void* takplacer;//4
	double opp_back;//5
	
	void update(pair<int,pair<int,int>> newrt){
		pair<int,int> sm=newrt.second;
		if(newrt.first==1){
			onf[1]=1;
			last[1]+=sm.second;
			lim_hurt=max(lim_hurt,sm.first);
		}
		
		return;
	}
	void update(pair<int,pair<double,int>> newrt){
		pair<double,int> sm=newrt.second;
		if(newrt.first==2){
			onf[2]=1;
			last[2]+=sm.second;
			opp_cace=min(opp_cace,sm.first);
		}
		else if(newrt.first==3){
			onf[3]=1;
			last[3]+=sm.second;
			pc_spread=max(pc_spread,sm.first);
		}
		else if(newrt.first==5){
			onf[5]=1;
			last[5]+=sm.second;
			opp_back=min(opp_back,sm.first);
		}
		
		return;
	}
	void update(pair<int,pair<pair<double,void*>,int>> newrt){
		pair<pair<double,void*>,int> sm=newrt.second;
		if(newrt.first==4){
			onf[4]=1;
			last[4]+=sm.second;
			pc_takplac=sm.first.first;
			takplacer=sm.first.second;
		}
		
		return;
	}
	
	void run(){
		for(int i=1;i<=front;i++){
			if(last[i]>0)last[i]-=1;
			else{
				last[i]=0;
				onf[i]=0;
			}
		}
		if(!onf[1]) lim_hurt=-1;
		if(!onf[2]) opp_cace=999.0;
		if(!onf[3]) pc_spread=-1.0;
		if(!onf[4]) pc_takplac=-1.0,takplacer=NULL;
		if(!onf[5]) opp_back=999.0;
	}
	Return_Hit(){
		front=5;
		for(int i=1;i<=front;i++)onf[i]=0;
		for(int i=1;i<=front;i++)last[i]=0;
		return;
	}
};
struct Return_BeHit{
	bool onf[100+10];
	int last[100+10];
	int front=4;
	
	int lim_hurt;//1
	double opp_cace;//2
	double pc_spread;//3
	double pc_takplac;void* takplacer;//4
	double opp_back;//5
	
	void update(pair<int,pair<int,int>> newrt){
		pair<int,int> sm=newrt.second;
		if(newrt.first==1){
			onf[1]=1;
			last[1]+=sm.second;
			lim_hurt=min(lim_hurt,sm.first);
		}
		
		return;
	}
	void update(pair<int,pair<double,int>> newrt){
		pair<double,int> sm=newrt.second;
		if(newrt.first==2){
			onf[2]=1;
			last[2]+=sm.second;
			opp_cace=max(opp_cace,sm.first);
		}
		else if(newrt.first==3){
			onf[3]=1;
			last[3]+=sm.second;
			pc_spread=min(pc_spread,sm.first);
		}
		else if(newrt.first==5){
			onf[5]=1;
			last[5]+=sm.second;
			opp_back=max(opp_back,sm.first);
		}
		
		return;
	}
	void update(pair<int,pair<pair<double,void*>,int>> newrt){
		pair<pair<double,void*>,int> sm=newrt.second;
		if(newrt.first==4){
			onf[4]=1;
			last[4]+=sm.second;
			pc_takplac=sm.first.first;
			takplacer=sm.first.second;
		}
		
		return;
	}
	
	void run(){
		for(int i=1;i<=front;i++){
			if(last[i]>0)last[i]-=1;
			else{
				last[i]=0;
				onf[i]=0;
			}
		}
		if(!onf[1]) lim_hurt=999;
		if(!onf[2]) opp_cace=-1.0;
		if(!onf[3]) pc_spread=999.0;
		if(!onf[4]) pc_takplac=-1.0,takplacer=NULL;
		if(!onf[5]) opp_back=-1.0;
	}
	Return_BeHit(){
		front=5;
		for(int i=1;i<=front;i++)onf[i]=0;
		for(int i=1;i<=front;i++)last[i]=0;
		return;
	}
};
class stud{
	private:
	public:
		int tim;
		
		bool Bighuocar=0;  // A7用，暂留

		int red,red_up;
		int blue,blue_up;
		int white,white_up;
		int def,def_up;

		// first=倍率  second=剩余回合数
		vector<pair<double,int>>white_mul,blue_mul,red_mul;
		vector<pair<double,int>>white_mul_p,blue_mul_p,red_mul_p;
		
		int att;
		vector<pair<double,int>> att_mul,be_att_mul;
		vector<pair<int,int>> tmp_att_plus;  // 临时攻击力加成 (值, 剩余回合)
		Return_Hit att_rt;
		Return_BeHit be_att_rt;
		
		vector<int>py;
		vector<string>ct1,ct2;
		bool HavCt[10];
		int WithP=-1;
		
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
		bool affected=0;// get_att要用，写在A0.h
			// @delHYfish 或者你有更好的做法也可以移至A13.h
		// B06隐藏血条
		bool hide_bars=0;
		// A09全局（给我待在A0！！）
		bool firstTurnA9=0,fromA9=0;
		//Ct special change num
		int RJCS_6,ZJZL_7;
		
		// 计算当前是第几天第几节课第几回合
		pair<pair<int,int>,int>Dtee(){
			int d=tim/26+1;
			int c=tim%26>21?8:tim%26/3+1;
			int t=tim-(d-1)*26-(d-1)*26;
			return {{d,c},t};
		}
		
		// 获取当前红条倍率 (sc: 0=增加时, 1=减少时)
		double get_red_mul(int sc){
			double ans=1.0;
			if(sc==1){
				for(auto y:red_mul) ans*=y.first;				 
				return ans;
			}else{
				for(auto y:red_mul_p) ans*=y.first;			 
				return ans;
			}
		}
		double get_blue_mul(int sc){
			double ans=1.0;
			if(sc==1){
				for(auto y:blue_mul) ans*=y.first;				 
				return ans;
			}else{
				for(auto y:blue_mul_p) ans*=y.first;			 
				return ans;
			}
		}
		double get_white_mul(int sc){
			double ans=1.0;
			if(sc==1){
				for(auto y:white_mul) ans*=y.first;				 
				return ans;
			}else{
				for(auto y:white_mul_p) ans*=y.first;			 
				return ans;
			}
		}
		
		// 获取最终攻击力
		int get_att(){
			double ans=att;
			for(auto y:att_mul){ans*=y.first;}
			for(auto y:tmp_att_plus){ans+=y.first;}
			
			// 当数值异常时输出
			if((ans>999||ans<-999)&&debug_on){
				if(espp){
					logPrint(12,"[DEBUG] %s: unfathomable power\n",name.c_str());
				}else if(affected){
					logPrint(12,"[DEBUG] %s: granted divine inspiration from A04L (value: %.0f)\n",name.c_str(),ans);
				}else{
					logPrint(12,"[DEBUG] %s get_att() = %.0f (abnormal!)\n",name.c_str(),ans);
					logPrint(12,"  att=%d, att_mul size=%d, tmp_att_plus size=%d\n",
						att,(int)att_mul.size(),(int)tmp_att_plus.size());
					for(auto y:att_mul){logPrint(12,"    att_mul: %.2f x %d turns\n",y.first,y.second);}
					for(auto y:tmp_att_plus){logPrint(12,"    tmp_att_plus: %d x %d turns\n",y.first,y.second);}
				}
			}
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
		
		virtual int cred(int chg){
			if(chg<0){
				if(def>0){
					def-=chg;
					def=max(def,0);
				}
				else red+=chg*get_red_mul(1);
			}
			else{red+=chg*get_red_mul(0);}
			red=min(red,red_up);
			if(red<0){red=0,status=0;}
			return status;
		}
		virtual int cwhite(int chg){
			if(chg<0){
				if(def>0){
					def-=chg;
					def=max(def,0);
				}
				else white+=chg*get_white_mul(1);
			}
			else{white+=chg*get_white_mul(0);}
			white=min(white,white_up);
			if(white<0){
				status=-1;
			}
			else if(white>=0&&status==-1){status=1;}
			return status;
		}
		virtual int cblue(int chg){
    		/*if(chg<0)*/if(chg<0){
        		if(id==6&&HavCt[2]){chg=0;}
				if(def>0){
					def-=chg;
					def=max(def,0);
				}
				else blue+=chg*get_blue_mul(1);
			}
    		else{blue+=chg*get_blue_mul(0);}
    		blue=min(blue,blue_up);
    		if(blue<0){is_crazy=1;}
    		return status;
		}
		
		virtual Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(ZJZL_7)att_rt.update(pair<int,pair<int,int>>{1,{att_rt.lim_hurt+ZJZL_7,0x3f3f3f3f}});
			return att_rt;
		}
		virtual void after_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){;}
		virtual Return_BeHit on_before_be_atted(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){return be_att_rt;}
		virtual void on_minus_red(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			if(status==0&&RJCS_6){
				for(auto y:beside_team){(*y).cred(-1*min(white,30));}
			}
		}

		// 回合开始：自动减少所有临时乘区的回合数
		virtual void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
			tim++;
			for(int i=0;i<red_mul.size();i++){
				if(red_mul[i].second<=0) red_mul.erase(red_mul.begin()+i),i--;
				else red_mul[i].second--;
			}for(int i=0;i<blue_mul.size();i++){
				if(blue_mul[i].second<=0) blue_mul.erase(blue_mul.begin()+i),i--;
				else blue_mul[i].second--;
			}for(int i=0;i<white_mul.size();i++){
				if(white_mul[i].second<=0) white_mul.erase(white_mul.begin()+i),i--;
				else white_mul[i].second--;
			}
			for(int i=0;i<att_mul.size();i++){
				if(att_mul[i].second<=0) att_mul.erase(att_mul.begin()+i),i--;
				else att_mul[i].second--;
			}for(int i=0;i<be_att_mul.size();i++){
				if(be_att_mul[i].second<=0) be_att_mul.erase(be_att_mul.begin()+i),i--;
				else be_att_mul[i].second--;
			}for(int i=0;i<tmp_att_plus.size();i++){
				if(tmp_att_plus[i].second<=0) tmp_att_plus.erase(tmp_att_plus.begin()+i),i--;
				else tmp_att_plus[i].second--;
			}
			att_rt.run();
			be_att_rt.run();
			
			
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
		virtual int get_dead_count(bool is_late_night){return 0;}
		virtual void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){;}
		
		stud(){
			tim=0;
			red=red_up=blue=blue_up=white=white_up=def_up=100;
			// 永久乘区用很大的剩余回合数表示
			white_mul.push_back({1.0,0x7f7f7f7f});
			blue_mul.push_back({1.0,0x7f7f7f7f});
			red_mul.push_back({1.0,0x7f7f7f7f});
			white_mul_p.push_back({1.0,0x7f7f7f7f});
			blue_mul_p.push_back({1.0,0x7f7f7f7f});
			red_mul_p.push_back({1.0,0x7f7f7f7f});
			att=10;
			att_mul.push_back({1.0,0x7f7f7f7f});
			be_att_mul.push_back({1.0,0x7f7f7f7f});
			tmp_att_plus.push_back({0,0x7f7f7f7f});
			HavCt[1]=0;
			HavCt[2]=0;
			HavCt[0]=0;
			WithP=-1;//
			py.clear();
			ct1.clear();
			ct2.clear();
			status=1;
			id=0;name="A0";
			Bighuocar=0;
			espp=affected=0;
			hide_bars=0;
			RJCS_6=0;
			ZJZL_7=0;
		}
		~stud()=default;
};



// 政治全局伤害倍率
float global_damage_mult=1.0f;
// 物理标记 & 英语B替罪羊
stud*physics_marked=NULL;
stud*scapegoat=NULL;

#endif
