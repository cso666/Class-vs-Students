#ifndef __CORE_H__
#define __CORE_H__

/*
 * core.h - 核心游戏逻辑
 * 包含: choose reset checkListenStart applySubjectStart
 *       applySubjectEnd init team_chs sett
 */

#include<iostream>
#include<limits.h>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<set>
#ifdef _WIN32
    #include<windows.h>
#endif
#include<conio.h>
#include<map>
#include<time.h>
#include<stdarg.h>
#define sslp(n) Sleep(n*1000)
using namespace std;

int sbj_teacher;//老师
map<string,int>subj;
string subj2[13+10];//学科

vector<void*>stud_list;
vector<void*>listA,listB;
int Anum=5,Bnum=5;
int day,clas;
bool isalive[35];

// ========== 控制台函数 ==========
void gotoxy(int x,int y){
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(hout,pos);
}

long long color(long long c){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
	return 0;
}

void ppput(const char*s,float k){
	unsigned leng=strlen(s);
	for(unsigned i=0;i<leng;i++){
		printf("%c",s[i]);
		sslp(k);
	}
}

void setConsoleSize(SHORT width,SHORT height){
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize={width,height};
    SetConsoleScreenBufferSize(hConsole,bufferSize);
    
    SMALL_RECT windowRect={0,0,(SHORT)(width-1),(SHORT)(height-1)};
    SetConsoleWindowInfo(hConsole,TRUE,&windowRect);
}

// ========== 学生头文件 ==========
#include"students/A0.h"
#include"students/A1.h"
#include"students/A2.h"
#include"students/A3.h"
#include"students/A4.h"
#include"students/A5.h"
#include"students/A6.h"
#include"students/A7.h"
#include"students/A8.h"
#include"students/A9.h"
#include"students/A10.h"
#include"students/A12.h"
#include"students/A13.h"
#include"students/B1.h"
#include"students/B2.h"
#include"students/B3.h"
#include"students/B4.h"
#include"students/B5.h"
#include"students/B6.h"
#include"students/B7.h"
#include"students/B8.h"
#include"students/B9.h"
#include"students/B10.h"
#include"students/B11.h"
#include"students/B12.h"
#include"students/B13.h"
#include"students/B14.h"
#include"students/B15.h"

// ========== 类型定义 ==========
typedef vector<stud*>stuV;
typedef vector<void*>voiV;
struct actCho{
    bool useSk;
    stud*user;
};

string stud_name[]={"A00",
"A01","A02","A03","A04","A05","A06","A07","A08","A09","A10","A12","A13",
"B01","B02","B03","B04","B05","B06","B07","B08","B09","B10","B11","B12","B13","B14","B15"
};

stud* tmp;

// ========== 学生实例 ==========
stud_A1 t1;
stud_A2 t2;
stud_A3 t3;
stud_A4 t4;
stud_A5 t5;
stud_A6 t6;
stud_A7 t7;
stud_A8 t8;
stud_A9 t9;
stud_A10 t10;
stud_A12 t12;
stud_A13 t13;
stud_B1 t14;
stud_B2 t15;
stud_B3 t16;
stud_B4 t17;
stud_B5 t18;
stud_B6 t19;
stud_B7 t20;
stud_B8 t21;
stud_B9 t22;
stud_B10 t23;
stud_B11 t24;
stud_B12 t25;
stud_B13 t26;
stud_B14 t27;
stud_B15 t28;

// ========== 课表 ==========
int classtable[5][8]={
	{6,2,8,3,9,1,0},
	{2,13,4,1,7,8,5},
	{1,1,2,3,11,8,0},
	{1,8,12,7,10,4,2},
	{3,4,2,2,6,5,0}
};

// ========== 前向声明 ==========
void hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2);
void sk_hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2);
extern void unlockProgress(int id);
extern void unlockChallenge(int id);

// ========== choose ==========
void*choose(int id){
	if(id<1||id>28){return NULL;}

	if(id==1){return&t1;}
	if(id==2){return&t2;}
	if(id==3){return&t3;}
	if(id==4){return&t4;}
	if(id==5){return&t5;}
	if(id==6){return&t6;}
	if(id==7){return&t7;}
	if(id==8){return&t8;}
	if(id==9){return&t9;}
	if(id==10){return&t10;}
	if(id==12){return&t12;}
	if(id==13){return&t13;}
	if(id==14){return&t14;}
	if(id==15){return&t15;}
	if(id==16){return&t16;}
	if(id==17){return&t17;}
	if(id==18){return&t18;}
	if(id==19){return&t19;}
	if(id==20){return&t20;}
	if(id==21){return&t21;}
	if(id==22){return&t22;}
	if(id==23){return&t23;}
	if(id==24){return&t24;}
	if(id==25){return&t25;}
	if(id==26){return&t26;}
	if(id==27){return&t27;}
	if(id==28){return&t28;}

	return NULL;
}

// ========== reset ==========
void reset(){
	stud_list.clear();
	listA.clear();
	listB.clear();
	Anum=5,Bnum=5;

	t1=stud_A1();
	t2=stud_A2();
	t3=stud_A3();
	t4=stud_A4();
	t5=stud_A5();
	t6=stud_A6();
	t7=stud_A7();
	t8=stud_A8();
	t9=stud_A9();
	t10=stud_A10();
	t12=stud_A12();
	t13=stud_A13();
	t14=stud_B1();
	t15=stud_B2();
	t16=stud_B3();
	t17=stud_B4();
	t18=stud_B5();
	t19=stud_B6();
	t20=stud_B7();
	t21=stud_B8();
	t22=stud_B9();
	t23=stud_B10();
	t24=stud_B11();
	t25=stud_B12();
	t26=stud_B13();
	t27=stud_B14();
	t28=stud_B15();
}

// ========== 学科效果系统 ==========

// 不听讲检查
void checkListenStart(int subject){
	if(subject==3||subject==2||subject==8||subject==6||subject==5){
		stud* punished=NULL;
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(!s->listen){
				if(rand()%100<65){
					s->cred(-10);
					s->cblue(-10);
					s->cwhite(-10);
					s->listen=1;
					s->listen_punish++;
					punished=s;
					if(debug_on){logPrint(12,"[Class] Headteacher came! %s loses 10 HP/SAN/STA for not listening.\n",s->name.c_str());}
					if(s->listen_punish>=5){unlockChallenge(5);}
				}
			}
		}
		
		if(subject==5){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(rand()%100<50){
					s->cwhite(10);
					if(debug_on){logPrint(7,"[History Class] %s +10 STA\n",s->name.c_str());}
				}else{
					s->cblue(-10);
					if(debug_on){logPrint(7,"[History Class] %s -10 SAN\n",s->name.c_str());}
				}
			}
			
			bool aPunished=0,bPunished=0;
			for(auto x:listA){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!s->listen&&isalive[s->id]){
					aPunished=1;
					break;
				}
			}
			for(auto x:listB){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!s->listen&&isalive[s->id]){
					bPunished=1;
					break;
				}
			}
			
			bool aDestroy=0,bDestroy=0;
			int cleanRounds=rand()%10;
			for(int i=0;i<cleanRounds;i++){rand();}
			
			if(aPunished&&rand()%100<1){
				aDestroy=1;
				if(debug_on){logPrint(12,"[History Class] Team A is annihilated!\n");}
				for(auto x:listA){
					if(x==NULL){continue;}
					stud* s=(stud*)x;
					if(isalive[s->id]){s->cred(-9999);}
				}
			}
			
			cleanRounds=rand()%10;
			for(int i=0;i<cleanRounds;i++){rand();}
			
			if(bPunished&&rand()%100<1){
				bDestroy=1;
				if(debug_on){logPrint(12,"[History Class] Team B is annihilated!\n");}
				for(auto x:listB){
					if(x==NULL){continue;}
					stud* s=(stud*)x;
					if(isalive[s->id]){s->cred(-9999);}
				}
			}
			
			if(aDestroy&&bDestroy){
				if(debug_on){logPrint(12,"[History Class] Total Destruction! Both teams annihilated!\n");}
				unlockChallenge(6);
			}
		}
	}
}

// 学科开始效果
void applySubjectStart(int subject){
	if(debug_on){logPrint(7,"[Subject Start] Subject ID: %d\n",subject);}
	
	if(subject==2){// 数学
		if(debug_on){logPrint(7,"[Math Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			
			// 伤害加成 (持续3回合)
			if(s->id==3||s->id==28||s->id==10){
				s->att_mul.push_back({1.1, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +10%% damage\n",s->name.c_str());}
			}
			if(s->id==9||s->id==26){
				s->att_mul.push_back({1.05, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +5%% damage\n",s->name.c_str());}
			}
			
			// 白条消耗 (持续3回合)
			if(s->id==10){
				s->white_mul.push_back({0.9, 3});
				if(debug_on){logPrint(7,"[Math Class] %s -10%% stamina cost\n",s->name.c_str());}
			}
			if(s->id==21||s->id==12||s->id==13){
				s->white_mul.push_back({1.1, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +10%% stamina cost\n",s->name.c_str());}
			}
			
			// B3 上限提升
			if(s->id==16){
				s->att+=2;
				s->red_up+=s->red_up*0.2;
				s->blue_up+=s->blue_up*0.2;
				s->white_up+=s->white_up*0.2;
				s->cred(s->red_up/6);
				s->cblue(s->blue_up/6);
				s->cwhite(s->white_up/6);
				if(debug_on){logPrint(7,"[Math Class] B3 +2 ATK, +20%% caps\n");}
			}
		}
		
		// 概率效果
		if(rand()%100<92){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==9&&isalive[s->id]){
					int dmg=-(rand()%14+3);
					s->cblue(dmg);
					if(debug_on){logPrint(7,"[Math Class] A9 loses %d SAN\n",-dmg);}
					break;
				}
			}
		}
		if(rand()%100<13){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if((s->id==12||s->id==13)&&isalive[s->id]){
					s->cwhite(11);
					if(debug_on){logPrint(7,"[Math Class] %s +11 STA\n",s->name.c_str());}
				}
			}
		}
		if(rand()%100<4){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==18&&isalive[s->id]){
					int dmg=-(rand()%21);
					s->cblue(dmg);
					if(debug_on){logPrint(7,"[Math Class] B5 loses %d SAN\n",-dmg);}
					break;
				}
			}
		}
	}
	
	if(subject==1){// 语文
		if(debug_on){logPrint(7,"[Chinese Class] Start effects\n");}
		
		int r=rand()%100;
		if(r<50){
			if(debug_on){logPrint(7,"[Chinese Class] Nothing happens.\n");}
		}
		else if(r<70){
			if(debug_on){logPrint(7,"[Chinese Class] All students lose 10 STA.\n");}
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(isalive[s->id]){s->cwhite(-10);}
			}
		}
		else if(r<90){
			if(debug_on){logPrint(7,"[Chinese Class] All students gain 10 SAN (B3 gains 15).\n");}
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(isalive[s->id]){
					if(s->id==16){s->cblue(15);}
					else{s->cblue(10);}
				}
			}
		}
		else{
			int card=rand()%4;
			int targetTeam=rand()%2;
			
			if(debug_on){logPrint(7,"[Chinese Class] Card effect! Card=%d, Target Team=%s\n",card,targetTeam==0?"A":"B");}
			
			switch(card){
				case 0: // Double Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_double=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_double=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Double Card: Team %s +3 ATK\n",targetTeam==0?"A":"B");}
					break;
				case 1: // Forgive Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_forgive=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_forgive=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Forgive Card: Team %s gets damage reduction\n",targetTeam==0?"A":"B");}
					break;
				case 2: // Pass Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_pass=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_pass=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Pass Card: Team %s takes self damage when attacking\n",targetTeam==0?"A":"B");}
					break;
				case 3: // Bread Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->cwhite(20);}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->cwhite(20);}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Bread Card: Team %s +20 STA\n",targetTeam==0?"A":"B");}
					break;
			}
		}
	}
	
	if(subject==3){// 英语A
		if(debug_on){logPrint(7,"[English A] Start effects\n");}
		
		bool hasAAlive=0;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if((s->id>=1&&s->id<=13)&&s->id!=11&&isalive[s->id]){
				hasAAlive=1;
				break;
			}
		}
		
		if(!hasAAlive){
			if(debug_on){logPrint(7,"[English A] No class A students here, effects disabled.\n");}
		}else{
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				s->cwhite(-10);
				s->cblue(-5);
				if(debug_on){logPrint(7,"[English A] %s -10 STA, -5 SAN\n",s->name.c_str());}
			}
		}
	}
	
	if(subject==4){// 英语B
		if(debug_on){logPrint(7,"[English B] Start effects\n");}
		
		bool hasBAlive=0;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id>=14&&s->id<=28&&isalive[s->id]){
				hasBAlive=1;
				break;
			}
		}
		
		if(!hasBAlive){
			if(debug_on){logPrint(7,"[English B] No class B students here, effects disabled.\n");}
			if(rand()%100<1){unlockChallenge(4);}
		}else{
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(s->id>=14&&s->id<=28){
					s->cwhite(-10);
					s->cblue(-5);
					if(debug_on){logPrint(7,"[English B] %s -10 STA, -5 SAN\n",s->name.c_str());}
				}else{
					s->cwhite(-5);
					s->cblue(-2);
					if(debug_on){logPrint(7,"[English B] %s -5 STA, -2 SAN\n",s->name.c_str());}
				}
			}
			
			if(rand()%100<1){
				vector<stud*> bStudents;
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(s->id>=14&&s->id<=28&&isalive[s->id]){bStudents.push_back(s);}
				}
				if(!bStudents.empty()){
					int idx=rand()%bStudents.size();
					scapegoat=bStudents[idx];
					if(debug_on){logPrint(7,"[English B] Scapegoat event! %s bears all incoming damage\n",scapegoat->name.c_str());}
				}
			}
		}
	}
	
	if(subject==6){// 政治
		if(debug_on){logPrint(7,"[Politics Class] Start effects\n");}
		
		// A3 睡觉
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==3&&isalive[s->id]){
				s->listen=0;
				if(debug_on){logPrint(7,"[Politics Class] A3 falls asleep\n");}
				break;
			}
		}
		
		// 全局伤害浮动
		float dmg_float=(910+rand()%10)/1000.0f;
		global_damage_mult=dmg_float;
		if(debug_on){logPrint(7,"[Politics Class] Global damage multiplier: %.3f\n",dmg_float);}
	}
	
	if(subject==7){// 体育
		if(debug_on){logPrint(7,"[PE Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			if(s->id==26||s->id==19){
				if(debug_on){logPrint(7,"[PE Class] %s doesn't love sports, skipped\n",s->name.c_str());}
				continue;
			}
			s->cwhite(-5);
			s->cblue(10);
			if(debug_on){logPrint(7,"[PE Class] %s -5 STA, +10 SAN\n",s->name.c_str());}
		}
	}
	
	if(subject==8){// 物理
		if(debug_on){logPrint(7,"[Physics Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){
				s->cwhite(5);
				if(debug_on){logPrint(7,"[Physics Class] %s +5 STA\n",s->name.c_str());}
			}
		}
		
		vector<stud*> alive;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){
				alive.push_back(s);
			}
		}
		if(!alive.empty()){
			int idx=rand()%alive.size();
			physics_marked=alive[idx];
			if(debug_on){
				logPrint(7,"[Physics Class] Marked: %s (effects not shown in game)\n",physics_marked->name.c_str());
			}
		}
	}
	
	if(subject==9){// 信息
		if(debug_on){logPrint(7,"[ICT Class] Start effects\n");}
		
		if(rand()%1000<1){
			if(debug_on){logPrint(7,"[ICT Class] OIer's game triggered! (0.1%%)\n");}
		}
	}
	
	if(subject==10&&debug_on){logPrint(7,"[Art Class] No special effects\n");}
	
	if(subject==11){// 音乐
		if(debug_on){logPrint(7,"[Music Class] Start effects\n");}
		
		if(rand()%100<10){
			if(debug_on){logPrint(7,"[Music Class] Note check! 30%% chance for everyone to lose HP\n");}
			
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(rand()%100<30){
					if(s->red>=5){
						s->cred(-5);
						if(debug_on){logPrint(7,"[Music Class] %s -5 HP (now %d)\n",s->name.c_str(),s->red);}
					}else if(s->red>0){
						int oldRed=s->red;
						s->cred(-s->red);
						if(debug_on){logPrint(7,"[Music Class] %s HP reduced from %d to 0\n",s->name.c_str(),oldRed);}
					}
				}
			}
		}
	}
	
	if(subject==12){// 生物
		if(debug_on){logPrint(7,"[Biology Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			int staGain=10;
			if(s->id==3){staGain=8;}
			s->cwhite(staGain);
			if(debug_on){logPrint(7,"[Biology Class] %s +%d STA\n",s->name.c_str(),staGain);}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==13&&isalive[s->id]){
				s->cblue(5);
				if(debug_on){logPrint(7,"[Biology Class] A13 +5 SAN\n");}
			}
		}
	}
	
	if(subject==13){// 地理
		if(debug_on){logPrint(7,"[Geography Class] Start effects\n");}
		
		bool hasB2=0;
		for(auto x:listA){
			if(x!=NULL&&((stud*)x)->id==15&&isalive[((stud*)x)->id]){
				hasB2=1;
				break;
			}
		}
		if(!hasB2){
			for(auto x:listB){
				if(x!=NULL&&((stud*)x)->id==15&&isalive[((stud*)x)->id]){
					hasB2=1;
					break;
				}
			}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			
			s->cwhite(5);
			
			if(hasB2){
				bool inTeam=0;
				for(auto x:listA){if(x==s){inTeam=1;}}
				for(auto x:listB){if(x==s){inTeam=1;}}
				if(inTeam){
					s->cwhite(5);
					if(debug_on){logPrint(7,"[Geography Class] %s +5 STA (team bonus)\n",s->name.c_str());}
				}
			}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==15&&isalive[s->id]){
				s->cwhite(5);
				if(debug_on){logPrint(7,"[Geography Class] B2 +5 STA (self bonus)\n");}
			}
		}
	}
}

// 学科结束效果
void applySubjectEnd(int subject){
	if(debug_on){logPrint(7,"[Subject End] Subject ID: %d\n",subject);}
	
	if(subject==2){// 数学
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			
			// 注意：att_mul 和 white_mul 的临时乘区会在 on_turn_start 中自动过期
			// 只需要重置 B3 这种永久改属性的
			if(s->id==16){
				s->att-=2;
				s->red_up=100;
				s->blue_up=100;
				s->white_up=100;
				s->red=min(s->red,s->red_up);
				s->blue=min(s->blue,s->blue_up);
				s->white=min(s->white,s->white_up);
				if(debug_on){logPrint(7,"[Math Class] B3 caps restored\n");}
			}
		}
	}
	
	if(subject==1){// 语文
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			s->chinese_double=0;
			s->chinese_forgive=0;
			s->chinese_pass=0;
		}
		if(debug_on){logPrint(7,"[Chinese Class] Card effects cleared\n");}
	}
	
	if(subject==6){// 政治
		global_damage_mult=1.0f;
		if(debug_on){logPrint(7,"[Politics Class] Effects cleared\n");}
	}
	if(subject==8){// 物理
		physics_marked=NULL;
		if(debug_on){logPrint(7,"[Physics Class] Mark cleared\n");}
	}
	if(subject==4){// 英语B
		scapegoat=NULL;
		if(debug_on){logPrint(7,"[English B] Scapegoat cleared\n");}
	}
}

// ========== init ==========
void init(){
	subj["chinese"]=1,subj2[1]="Chinese";
	subj["math"]=2,subj2[2]="Math";
	subj["EnglishA"]=3,subj2[3]="English A";
	subj["EnglishB"]=4,subj2[4]="English B";
	subj["history"]=5,subj2[5]="History";
	subj["politics"]=6,subj2[6]="Politics";
	subj["pe"]=7,subj2[7]="P.E.";
	subj["physics"]=8,subj2[8]="Physics";
	subj["ict"]=9,subj2[9]="I.C.T.";
	subj["art"]=10,subj2[10]="Art";
	subj["music"]=11,subj2[11]="Music";
	subj["biology"]=12,subj2[12]="Biology";
	subj["geography"]=13,subj2[13]="Geography";

	sbj_teacher=rand()*rand()%13+1;

	for(int i=0;i<=30;i++){isalive[i]=0;}

	while(stud_list.size()<16){
		int tr=rand()*rand()%28+1;
		int loop_count=0;
		while(isalive[tr]&&loop_count<100){
			tr=tr%28+1;
			loop_count++;
		}
		if(loop_count>=100){
			for(int i=1;i<=28;i++){
				if(!isalive[i]){tr=i;break;}
			}
		}
		isalive[tr]=1;
		void*student=choose(tr);
		if(student!=NULL){
			stud_list.push_back(student);
		}
	}

	// 属性匹配加成 (持续3回合)
	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL){continue;}
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py){
            if(j==sbj_teacher){(*tmp).att_mul.push_back({1.2, 3});}
        }
	}
}

// ========== team_chs 选人 ==========
void team_chs(){
	bool isc[16+10]={0};
	int current_pos=0;
	int round=0;
	bool team_a_turn=1;

	while(current_pos<stud_list.size()&&stud_list[current_pos]==NULL){current_pos++;}
	
	// ===== 选人界面 =====
	color(11);
	printf("+---------------------------------+\n");
	printf("|       Team Selection Phase      |\n");
	printf("+---------------------------------+\n");
	color(7);
	printf("|     ");
	color(10);
	printf("Team A's turn to select");
	color(7);
	printf("     |\n");
	printf("+---------------------------------+\n");
	printf("|           Student List          |\n");
	printf("+---------------------------------+\n");
	color(14);
	printf("| ->");
	color(7);
	
	for(int i=0;i<stud_list.size();i++){
		stud y=(*(stud*)stud_list[i]);
		if(i){printf("|   ");}
		printf(" %02d. %-8s ",i,y.name.c_str());
		color(12);
		printf("%03d ",y.red_up);
		color(3);
		printf("%03d ",y.blue_up);
		color(15);
		printf("%03d ",y.white_up);
		color(6);
		printf("%02d",y.att);
		color(7);
		printf("  |\n");
	}

	color(11);
	printf("+---------------------------------+\n\n");
	color(14);
	printf("Controls: W/S to move, Enter to select\n");
	color(10);
	printf("Team A selected: \n");
	color(9);
	printf("Team B selected: ");

	while(round<5){
		char key=getch();
		if(key=='w'||key=='W'){
			gotoxy(0,current_pos+7);
			color(7);
			printf("|    ");
			current_pos--;
			if(current_pos<0){current_pos=stud_list.size()-1;}
			while(stud_list[current_pos]==NULL){
				current_pos--;
				if(current_pos<0){current_pos=stud_list.size()-1;}
			}
			gotoxy(0,current_pos+7);
			color(14);
			printf("| ->");
		}
		else if(key=='s'||key=='S'){
			gotoxy(0,current_pos+7);
			color(7);
			printf("|    ");
			current_pos++;
			if(current_pos>=stud_list.size()){current_pos=0;}
			while(stud_list[current_pos]==NULL){
				current_pos++;
				if(current_pos>=stud_list.size()){current_pos=0;}
			}
			gotoxy(0,current_pos+7);
			color(14);
			printf("| ->");
		}
		else if(key==13){
			if(!isc[current_pos]&&stud_list[current_pos]!=NULL){
				stud y=(*(stud*)stud_list[current_pos]);
				gotoxy(0,current_pos+7);
				color(7);
				printf("|    ");
				if(team_a_turn){color(160);}
				else{color(144);}
				printf("%02d. %s",current_pos,y.name.c_str());

				if(team_a_turn){
					gotoxy(round*4+17,26);
					color(10);
					printf("%s",y.name.c_str());
					listA.push_back(stud_list[current_pos]);
					isc[current_pos]=1;
					team_a_turn=0;
				}
				else{
					gotoxy(round*4+17,27);
					color(9);
					printf("%s",y.name.c_str());
					listB.push_back(stud_list[current_pos]);
					isc[current_pos]=1;
					team_a_turn=1;
					round++;
				}

				if(team_a_turn){
					gotoxy(6,3);
					color(10);
					printf("Team A's turn to select");
				}
				else{
					gotoxy(6,3);
					color(9);
					printf("Team B's turn to select");
				}

				int next_pos=current_pos+1;
				while(next_pos<stud_list.size()&&(isc[next_pos]||stud_list[next_pos]==NULL)){next_pos++;}
				if(next_pos>=stud_list.size()){
					next_pos=0;
					while(next_pos<stud_list.size()&&(isc[next_pos]||stud_list[next_pos]==NULL)){next_pos++;}
				}
				current_pos=next_pos;

				gotoxy(0,current_pos+7);
				color(14);
				printf("| ->");
			}
		}
	}

	system("cls");

	// ===== 最终队伍显示 =====
	color(11);
	printf("+-------------------------------+\n");
	printf("|       Final Team Rosters      |\n");
	printf("+-------------------------------+\n");
	color(14);
	printf("|  Team A: ");
	for(auto x:listA){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		printf("%s ",y.name.c_str());
	}
	printf(" |");
	color(14);
	printf("\n|  Team B: ");
	for(auto x:listB){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		printf("%s ",y.name.c_str());
	}
	printf(" |");
	color(11);
	printf("\n+-------------------------------+\n");
	color(7);

	// ===== A4 超能力者触发 =====
	bool nesssp=0;
	for(auto x:stud_list){
        if(x==NULL){continue;}
        stud* s=(stud*)x;
        if(s->id==4){
            if(rand()%1000==0){  // 0.1%概率
				nesssp=1;
                s->red_up=s->red=0x3f3f3f3f;
                s->blue_up=s->blue=0x3f3f3f3f;
                s->white_up=s->white=0x3f3f3f3f;
                s->att=0x3f3f3f3f;
                s->ct1.push_back("GodPower");
                s->espp=1;
            }
            break;
        }
    }

	gotoxy(0,7);
	printf("Press any key to continue...");
	getch();
	gotoxy(0,9);
	if(nesssp){
		color(95);
        printf("An unfathomable power has irrupted.");
	}else{
		color(10);
		printf("OK! Let's go!\n");
	}
	color(7);
	sslp(1.5);
	system("cls");
}

// ========== sett 显示战斗界面 ==========
void sett(vector<void*>lA,vector<void*>lB,const int k){
	if(day<1||day>5||clas<1||clas>8){
		color(12);
		printf("Error: Invalid day or class!\n");
		color(7);
		return;
	}

	color(14);
	printf("+========================================================+\n");
	printf("|  Day %d  |  Class %d  |  %-20s            |\n",day,clas,subj2[classtable[day-1][clas-1]].c_str());
	printf("+========================================================+\n\n");
	color(7);

	color(14);
	if(k==3){printf("+--- Team A ------------------------------+\n");}
	if(k==5){printf("+--- Team A ----------------------------------------------------------+\n");}
	color(7);
	printf("| ");
	for(auto x:lA){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		if(is_dead){
			color(8);
			printf("%-6s",y.name.c_str());
		}else{
			if(y.espp){color(95);}
			else{color(10);}
			printf("%-6s",y.name.c_str());
		}
		color(7);
		if(y.att<=0||is_dead){printf("  --  | ");}
		else if(y.espp){
			color(86);
			printf("  ");
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else{
			color(6);
			printf("  %02d  ",y.get_att());
			color(7);
			printf("| ");
		}
	}
	printf("\n| ");
	for(auto x:lA){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		bool is_white_dead=(y.status==-1||y.white<=0);
		
		if(is_dead){
			color(8);
			printf("XXX XXX XXX ");
		}else if(y.hide_bars){
			color(128);
			printf("??? ??? ???");
			color(7);
			printf(" ");
		}else if(y.espp){
			color(84);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(83);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(95);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
		}else{
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int white_display=max(0,y.white);
				color(15);
				printf("%03d ",white_display);
			}
		}
		color(7);
		printf("| ");
	}
	color(14);
	if(k==3){printf("\n+-----------------------------------------+\n");}
	if(k==5){printf("\n+---------------------------------------------------------------------+\n");}
	color(7);

	if(k==3){printf("\n                    VS.\n\n");}
	if(k==5){printf("\n                                  VS.\n\n");}

	color(14);
	if(k==3){printf("+--- Team B ------------------------------+\n");}
	if(k==5){printf("+--- Team B ----------------------------------------------------------+\n");}
	color(7);
	printf("| ");
	for(auto x:lB){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		if(is_dead){
			color(8);
			printf("%-6s",y.name.c_str());
		}else{
			if(y.espp){color(95);}
			else{color(9);}
			printf("%-6s",y.name.c_str());
		}
		color(7);
		if(y.att<=0||is_dead){printf("  --  | ");}
		else if(y.espp){
			color(86);
			printf("  ");
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else{
			color(6);
			printf("  %02d  ",y.get_att());
			color(7);
			printf("| ");
		}
	}
	printf("\n| ");
	for(auto x:lB){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		bool is_white_dead=(y.status==-1||y.white<=0);
		
		if(is_dead){
			color(8);
			printf("XXX XXX XXX ");
		}else if(y.hide_bars){
			color(128);
			printf("??? ??? ???");
			color(7);
			printf(" ");
		}else if(y.espp){
			color(84);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(83);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(95);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
		}else{
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int white_display=max(0,y.white);
				color(15);
				printf("%03d ",white_display);
			}
		}
		color(7);
		printf("| ");
	}
	color(14);
	if(k==3){printf("\n+-----------------------------------------+\n");}
	if(k==5){printf("\n+---------------------------------------------------------------------+\n");}
	color(7);
	printf("\n");
}

#endif// __CORE_H__