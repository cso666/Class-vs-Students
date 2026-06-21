#ifndef __CORE_H__
#define __CORE_H__
#define __CORE_H_ver__ 9

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
#include<string>
#include<map>
#include<time.h>
#include<stdarg.h>
#include<direct.h>
#define sslp(n) Sleep(n*1000)
using namespace std;

const int STUDENT_NAME_WIDTH=5;
const int STUDENT_SKILL_WIDTH=4;
const int STUDENT_NAME_SKILL_TOTAL=STUDENT_NAME_WIDTH+STUDENT_SKILL_WIDTH+1;
const int STUDENT_ATT_WIDTH=2;
const int STUDENT_ATTR_WIDTH=3;
const int STUDENT_ATTR_COUNT=4;
const int CARD_WIDTH=(STUDENT_ATTR_WIDTH+1)*STUDENT_ATTR_COUNT+1;
const int TEAM_TITLE_WIDTH=3*(CARD_WIDTH+1)+1;
const int TEAM_TITLE_WIDTH_LATE=5*(CARD_WIDTH+1)+1;

int sbj_teacher;//老师
map<string,int>subj;
string subj2[13+10];//学科

vector<void*>stud_list;
vector<void*>listA,listB;
int Anum=5,Bnum=5;
int day,clas;
bool isalive[135];

bool hav_full_cts[35]={0};
string normal_ct[100]={"Red Up","Blue Up","White Up","Red_Mul Up","Blue_Mul Up","White_Mul Up","Att Up","Powerer hit","Harmful hit","Comfort One","Destory One",
"More RedUp","More BlueUp","More WhiteUp","OldDoors'Growth","Song of Bravery","Wider hitt",};
string rare_ct[100]={"Double Red Mul","Double Blue Mul","Double White Mul","Lets Make Hero","The Scars of War","Silence Reigns Supreme",
"Life Blazing Spent","Never Giveup"};
string link_ct[100]={"Defections!!","Maths STAR!!"};//un deal
vector<int> link_check[100]={{13+7,13+8,13+11},{12,13}};
bool link_res[100]={1,1};
string evolve_ct[100]={"A03->A24","A04->A04-L"};
vector<int> evolve_check[100]={{3},{4}};
bool evolve_res[100]={1,1};
int nc_cnt=17,rc_cnt=8,lc_cnt=2,ec_cnt=2;

// 设置项结构体
struct GameSettings{
    bool auto_insane;// 全疯模式（所有学生开局疯人）
    bool debug_log;// 输出日志文件
    bool chinese_tips;// 中文tips
    bool full_tips;// 完整tips
    bool hide_tips;// 隐藏tips
    bool Ct_Need_Chose;
    bool full_rosters;
};
// 全局设置实例
static GameSettings settings={0,0,0,0,0,0};

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
#include"../students/A0.h"
#include"../students/A1.h"
#include"../students/A2.h"
#include"../students/A3.h"
#include"../students/A4.h"
#include"../students/A5.h"
#include"../students/A6.h"
#include"../students/A7.h"
#include"../students/A8.h"
#include"../students/A9.h"
#include"../students/A10.h"
#include"../students/A12.h"
#include"../students/A13.h"
#include"../students/B1.h"
#include"../students/B2.h"
#include"../students/B3.h"
#include"../students/B4.h"
#include"../students/B5.h"
#include"../students/B6.h"
#include"../students/B7.h"
#include"../students/B8.h"
#include"../students/B9.h"
#include"../students/B10.h"
#include"../students/B11.h"
#include"../students/B12.h"
#include"../students/B13.h"
#include"../students/B14.h"
#include"../students/B15.h"
#include"../students/DH1.h"

// ========== 类型定义 ==========
typedef vector<stud*>stuV;
typedef vector<void*>voiV;
struct actCho{
    int useSk;
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
stud_DH1 t29;
//=========
stud_A24 t103;
stud_A4_L t104;


// ========== 课表 ==========
int classtable[6][9]={
    {0,0,0,0,0,0,0,0,0},
    {0,7,3,9,4,10,2,1,14},
    {0,3,14,5,2,8,9,6,15},
    {0,2,2,3,4,12,9,1,16},
    {0,2,9,13,8,11,5,3,17},
    {0,4,5,3,3,7,6,1,0}
};

// ========== 前向声明 ==========
int hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2);
void sk_hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2);
extern void unlockProgress(int id);
extern void unlockChallenge(int id);

#endif// __CORE_H__
