#ifndef __EXTRA_H__
#define __EXTRA_H__
#define sslp(n) Sleep(n*1000)
// be used for word-paint
#include "framew.h"
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

// ===ACHIEVEMENT===

// 进度成就
struct ProgressAchv{
	int id;
	string name;
	string method;
	bool completed;
};
// 挑战成就
struct ChallengeAchv{
	int id;
	string name;
	string hint;
	string solution;
	bool completed;
};
// 进度成就数组
static ProgressAchv progressAchv[]={
	{1,"First Launch","Open the game once",0},
	{2,"First Blood","Kill an enemy",0},
	{3,"First Battle","Start a battle",0},
	{4,"Explorer","Open Achievement page",0},
	{5,"Seeker","Open Guidance page",0},
	{6,"Settings Master","Open Settings page",0},
	{7,"Last Stand","Clear a battle with HP ≤ 20%",0},
	{8,"Flawless","Clear a battle with full HP",0},
};
static int progressCount=sizeof(progressAchv)/sizeof(progressAchv[0]);

// 挑战成就数组
static ChallengeAchv challengeAchv[]={
	{1,"Total Insanity","\"How are all students losing their minds?\"","Complete the game in Auto Insane Mode",0},
	{2,"One Shot","\"A5 has no damage cap of 30!\"","Deal more than 30 damage with A5",0},
	{3,"ESP User","\"I remember every interface should respond to Enter, right?\"","Press Enter on A4 in Guidance page",0},
};
static int challengeCount=sizeof(challengeAchv)/sizeof(challengeAchv[0]);

static int currentPage=0;
static int currentIndex=0;

// 成就解锁输出（在控制台最后一行）
void printAchievementMsg(const char* prefix,const char* name){
	gotoxy(0,30);
	color(10);
	printf("[%s] %s",prefix,name);
	color(7);
}

// 保存成就
void saveAchievements(){
	FILE* fp=fopen("achievement.dat","wb");
	if(fp){
		for(int i=0;i<progressCount;i++){fwrite(&progressAchv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<challengeCount;i++){fwrite(&challengeAchv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}

// 加载成就
void loadAchievements(){
	FILE* fp=fopen("achievement.dat","rb");
	if(fp){
		for(int i=0;i<progressCount;i++){fread(&progressAchv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<challengeCount;i++){fread(&challengeAchv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}

// 解锁进度成就
void unlockProgress(int id){
	if(id<1||id>progressCount){return;}
	if(!progressAchv[id-1].completed){
		progressAchv[id-1].completed=1;
		saveAchievements();
		printAchievementMsg("ACHIEVEMENT UNLOCKED",progressAchv[id-1].name.c_str());
	}
}

// 解锁挑战成就
void unlockChallenge(int id){
	if(id<1||id>challengeCount){return;}
	if(!challengeAchv[id-1].completed){
		challengeAchv[id-1].completed=1;
		saveAchievements();
		printAchievementMsg("CHALLENGE COMPLETED",challengeAchv[id-1].name.c_str());
	}
}

// 检查进度成就
void checkProgress(int type){
	switch(type){
		case 1:unlockProgress(1);break;
		case 2:unlockProgress(2);break;
		case 3:unlockProgress(3);break;
		case 4:unlockProgress(4);break;
		case 5:unlockProgress(5);break;
		case 6:unlockProgress(6);break;
		case 7:unlockProgress(7);break;
		case 8:unlockProgress(8);break;
	}
}

// 显示成就页面 (UNDER FIXING)
void achievementMenu(){
	system("cls");
	while(1){
		color(11);
		printf("+----------+--------------------------------------------------+\n");
		if(currentPage==0){
			printf("| Progress |                                                  |\n");
		}else{
			printf("| Challenges |                                                |\n");
		}
		printf("+----------+--------------------------------------------------+\n");
		color(7);
		int displayCount=(currentPage==0)?progressCount:challengeCount;
		for(int i=0;i<displayCount;i++){
			gotoxy(0,4+i);
			if(i==currentIndex){
				color(14);
				printf("| -> ");
			}else{
				color(7);
				printf("|    ");
			}
			if(currentPage==0){
				printf("%d. %s",i+1,progressAchv[i].name.c_str());
				int len=12+strlen(progressAchv[i].name.c_str());
				for(int j=len;j<28;j++){printf(" ");}
			}else{
				printf("%d. %s",i+1,challengeAchv[i].name.c_str());
				int len=12+strlen(challengeAchv[i].name.c_str());
				for(int j=len;j<28;j++){printf(" ");}
			}
			color(7);
		}
		// 右侧详情
		gotoxy(30,4);
		if(currentPage==0){
			ProgressAchv& a=progressAchv[currentIndex];
			color(14);
			printf("%s",a.name.c_str());
			color(7);
			gotoxy(30,6);
			if(a.completed){
				color(10);
				printf("[DONE]");
				gotoxy(30,8);
				color(7);
				printf("Method: %s",a.method.c_str());
			}else{
				color(8);
				printf("Method: %s",a.method.c_str());
			}
		}else{
			ChallengeAchv& a=challengeAchv[currentIndex];
			color(14);
			printf("%s",a.name.c_str());
			color(7);
			gotoxy(30,6);
			if(a.completed){
				color(10);
				printf("[DONE]");
				gotoxy(30,8);
				color(7);
				printf("Solution: %s",a.solution.c_str());
				gotoxy(30,10);
				color(8);
				printf("%s",a.hint.c_str());
			}else{
				gotoxy(30,8);
				color(8);
				printf("%s",a.hint.c_str());
			}
		}
		color(7);
		color(11);
		printf("\n+----------+--------------------------------------------------+\n");
		color(14);
		printf("|  +/-/_/= : Switch page  |  Enter : View solution (Challenges) |\n");
		printf("|  W/S     : Move cursor  |  Esc   : Return to main page        |\n");
		color(11);
		printf("+--------------------------------------------------------------+\n");
		color(7);
		char ch=getch();
		if(ch==27){break;}
		if(ch=='w'||ch=='W'){
			currentIndex--;
			if(currentIndex<0){currentIndex=displayCount-1;}
		}else if(ch=='s'||ch=='S'){
			currentIndex++;
			if(currentIndex>=displayCount){currentIndex=0;}
		}else if(ch=='+'||ch=='='||ch=='-'||ch=='_'){
			currentPage=1-currentPage;
			currentIndex=0;
		}else if(ch==13&&currentPage==1){
			ChallengeAchv& a=challengeAchv[currentIndex];
			if(!a.completed){
				gotoxy(30,10);
				color(14);
				printf("Solution: %s",a.solution.c_str());
				color(7);
				getch();
				gotoxy(30,10);
				for(int i=0;i<50;i++){printf(" ");}
				gotoxy(30,10);
				color(8);
				printf("%s",a.hint.c_str());
				color(7);
			}
		}
		// 清空右侧区域
		for(int i=6;i<=12;i++){
			gotoxy(28,i);
			for(int j=0;j<52;j++){printf(" ");}
		}
	}
	system("cls");
	color(7);
}

// ===SETTINGS===

// 调试模式
bool debug_on=0;// 标志
// 日志窗口句柄
FILE*logStream=NULL;

void createLogWindow(){
    if(!debug_on){return;}
    logStream=fopen("combat.log","w");
    if(logStream){
        fprintf(logStream,"========== Combat Log (Debug Mode) ==========\n");
        fprintf(logStream,"战斗详情将在此文件中记录\n\n");
        fflush(logStream);
    }
}// 创建日志文件

void closeLogWindow(){
    if(!debug_on){return;}
    if(logStream){
        fclose(logStream);
        logStream=NULL;
    }
}// 关闭日志文件

void logPrint(int colorCode,const char*format,...){
    if(!debug_on){return;}
    if(!logStream){return;}
    
    va_list args;
    va_start(args,format);
    vfprintf(logStream,format,args);
    fflush(logStream);
    va_end(args);
}// 日志输出函数

// 设置项结构体
struct GameSettings{
    bool auto_insane;// 全疯模式（所有学生开局疯人）
    bool debug_log;// 输出日志文件
    bool chinese_tips;// 中文tips
    bool full_tips;// 完整tips
    bool hide_tips;// 隐藏tips
};

// 全局设置实例
static GameSettings settings={0,0,0,0,0};

// 保存设置到文件
void saveSettings(){
    FILE*fp=fopen("settings.dat","wb");
    if(fp){
        fwrite(&settings,sizeof(GameSettings),1,fp);
        fclose(fp);
    }
}

// 加载设置
void loadSettings(){
    FILE*fp=fopen("settings.dat","rb");
    if(fp) {
        fread(&settings,sizeof(GameSettings),1,fp);
        fclose(fp);
    }
}

// 显示设置菜单
void settingsMenu(){
    system("cls");
    checkProgress(6);  // 打开设置成就
    int nowy=3;

    color(11);
    printf("+------------------------------------------+\n");
    printf("|                 Settings                 |\n");
    printf("+------------------------------------------+\n");
    color(7);
    printf("|    1. Auto Insane Mode                   |\n");
    printf("|    2. Debug Log                          |\n");
    printf("|    3. Chinese Tips                       |\n");
    printf("|    4. Full Tips                          |\n");
    printf("|    5. Hide Tips                          |\n");
    color(11);
    printf("+------------------------------------------+\n");
    color(4);
    printf("|  Caution: Please think carefully before  |\n");
    printf("|  modifying settings, particularly those  |\n");
    printf("| marked \"Chinese\"/\"Non-ASCII Characters,\" |\n");
    printf("|   as they may cause text corruption or   |\n");
    printf("|            display anomalies.            |\n");
    color(11);
    printf("+------------------------------------------+\n");
    color(14);
    printf("|       W/S to move, Enter to toggle       |\n");
    printf("|      ESC to return to the Main Page      |\n");
    color(11);
    printf("+------------------------------------------+\n");
    color(7);

    gotoxy(0,3);
    color(14);
    printf("| ->");

    gotoxy(37,3);
    if(settings.auto_insane){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(37,4);
    if(settings.debug_log){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(37,5);
    if(settings.chinese_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(37,6);
    if(settings.full_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    gotoxy(37,7);
    if(settings.hide_tips){color(10);printf("[ON] ");}
    else{color(8);printf("[OFF]");}
    color(7);

    while(1){
        char key=getch();
        if((key=='w'||key=='W')&&nowy>3){
            color(7);
            gotoxy(0,nowy);
            printf("|   ");
            nowy--;
            color(14);
            gotoxy(0,nowy);
            printf("| ->");
        }
        else if((key=='s'||key=='S')&&nowy<7){
            color(7);
            gotoxy(0,nowy);
            printf("|   ");
            nowy++;
            color(14);
            gotoxy(0,nowy);
            printf("| ->");
        }
        else if(key==13){
            if(nowy==3){
                settings.auto_insane=!settings.auto_insane;
                saveSettings();
                gotoxy(37,nowy);
                if(settings.auto_insane){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==4){
                settings.debug_log=!settings.debug_log;
                saveSettings();
                // 根据设置开关日志
                if(settings.debug_log&&!debug_on){
                    debug_on=1;
                    createLogWindow();
                }else if(!settings.debug_log&&debug_on) {
                    debug_on=0;
                    closeLogWindow();
                }
                gotoxy(37,nowy);
                if(settings.debug_log){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==5){
                settings.chinese_tips=!settings.chinese_tips;
                saveSettings();
                gotoxy(37,nowy);
                if(settings.chinese_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==6){
                settings.full_tips=!settings.full_tips;
                saveSettings();
                gotoxy(37,nowy);
                if(settings.full_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }else if(nowy==7){
                settings.hide_tips=!settings.hide_tips;
                saveSettings();
                gotoxy(37,nowy);
                if(settings.hide_tips){
                    color(10);
                    printf("[ON] ");
                }else{
                    color(8);
                    printf("[OFF]");
                }
            }
        }
        else if(key==27){break;}
    }
}

// ===TIPS===

// Tip 数据
struct Tip{
    const char*cn;
    const char*en;
    const char*cnfu;
    const char*enfu;
    int color;
};

static Tip tips[] = {
    {R"---(Class vs. Students!!1)---",
     R"---(Class vs. Students!!1)---",
     R"---(Class vs. Students!!1)---",
     R"---(Class vs. Students!!1)---",14},

    {R"---(过路涵洞装什么？)---", 
     R"---(What does a passage culvert hold?)---",
     R"---(过路涵洞不装水装 什 么 ？（一本正经）)---", 
     R"---(A passage culvert doesn't hold water -- then WHAT DOES IT HOLD? (In all seriousness))---",15},

    {R"---(人民代表大会制度就是这么做的！)---", 
     R"---(The People's Congress system is exactly how this is done!)---",
     R"---(“这一片有人讲话就记 你 头上。”\n“老师这不符合社会主义制度！”\n“这符合人民代表大会制度。”)---",
     R"---(\"If someone in this area talks, I'm holding YOU accountable.\"\n\"Teacher, that's not how Socialism works!\"\n\"This is how the People's Congress works.\")---",15},

    {R"---(这色子合理吗？)---",
     R"---(Is this color-son in-river?)---",
     R"---(这色子合理吗？)---",
     R"---(Is this color-son in-river?)---",15},

    {R"---(我不具备任何优势，因此我也不准备发言稿。)---",
     R"---(No strengths. No speech.)---",
     R"---(学校要征集参加介绍宪法活动的人，\n请谈谈你参加此次活动有哪些优势并准备一个100字左右的发言稿。\n答：我不具备任何优势，因此我也不准备发言稿。)---",
     R"---(School needs people to introduce the Constitution.Tell us your strengths and write a ~100-word speech.\nAnswer: No strengths. No speech.)---",15},

    {R"---(得分能力不等于成绩！)---",
     R"---(The ability of getting scores isn't equals to those scores!)---",
     R"---(“我也不是很关心你们的成绩，但是你们的得分能力呢？”)---",
     R"---("I don't really care about your scores -- but where's your ability to GET scores?")---",15},

    {R"---(这也是配料的一部分吗？)---",
     R"---(Is this also a part of the ingredients?)---",
     R"---(这也是配料的一部分吗？)---",
     R"---(Is this also a part of the ingredients?)---",15},
};

static int tip_count=sizeof(tips)/sizeof(tips[0]);
static int current_tip=0;

// 随机获取一条 Tip
void randomTip(){current_tip=rand()%tip_count;}

// 显示 Tip
void showTip(){
    const char*curtip="";
    if(settings.chinese_tips&&settings.full_tips){curtip=tips[current_tip].cnfu;}
    else if(settings.chinese_tips){curtip=tips[current_tip].cn;}
    else if(settings.full_tips){curtip=tips[current_tip].enfu;}
    else{curtip=tips[current_tip].en;}
    color(tips[current_tip].color);
    printf("Tip: %s\n",curtip);
    color(7);
}

// ===GUIDE===

void guide(){
/* after added teacher(subject)
+-----------------------------------------------------------------------+
|                             Guidance Book                             |
+-----------------------------------------------------------------------+
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| | A01 | | A02 | | A03 | | A04 | | A05 | | |  Chinese  | |    Math   | |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| | A06 | | A07 | | A08 | | A09 | | A10 | | | English-A | | English-B | |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
|         +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
|         | A12 | | A13 | | B01 | | B02 | | |  Physics  | |   Music   | |
|         +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| | B03 | | B04 | | B05 | | B06 | | B07 | | |  History  | |  Politics | |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +-----------+ +-----------+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +------+ +-----+ +--------+ |
| | B08 | | B09 | | B10 | | B11 | | B12 | | | P.E. | | Art | | I.C.T. | |
| +-----+ +-----+ +-----+ +-----+ +-----+ | +------+ +-----+ +--------+ |
| +-----+ +-----+ +-----+                 | +-----------+ +-----------+ |
| | B13 | | B14 | | B15 |                 | |  Biology  | | Geography | |
| +-----+ +-----+ +-----+                 | +-----------+ +-----------+ |
+-----------------------------------------------------------------------+
|           W/A/S/D to move the pointer, R to view game rules           |
|           Enter to view details, Esc to return the mainpage           |
+-----------------------------------------------------------------------+
*/
	system("cls");
    checkProgress(5);  // 打开图鉴成就

	color(11);
	printf(R"---(+-------------------------------------------------------------------------+
|                              Guidance Book                              |
+-------------------------------------------------------------------------+)---");
	color(7);
	printf(R"---(
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | A01 | | A02 | | A03 | | A04 | | A05 | | A06 | | A07 | | A08 | | A09 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | A10 | | A12 | | A13 | | B01 | | B02 | | B03 | | B04 | | B05 | | B06 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | B07 | | B08 | | B09 | | B10 | | B11 | | B12 | | B13 | | B14 | | B15 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
)---");
	color(11);
	printf("+-------------------------------------------------------------------------+");
	color(14);
	printf(R"---(
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |)---");
	color(11);
	printf(R"---(
+-------------------------------------------------------------------------+
|            W/A/S/D to move the pointer, R to view game rules            |
|                       Esc to return the main page                       |
+-------------------------------------------------------------------------+)---");
	
	// 初始化光标位置 (0-8/0-2)
	int _cx=0,_cy=0;
	int studentId[3][9]={
		{1,2,3,4,5,6,7,8,9},
		{10,12,13,14,15,16,17,18,19},
		{20,21,22,23,24,25,26,27,28}
	};
	
	// 绘制高亮光标
	gotoxy(2+_cx*8,3+_cy*3);
	color(14);
	printf("+-----+");
	gotoxy(2+_cx*8,3+_cy*3+1);
	printf("|     |");
	gotoxy(2+_cx*8,3+_cy*3+2);
	printf("+-----+");
    gotoxy(4+_cx*8,3+_cy*3+1);
    if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
    else{printf("B%02d",studentId[_cy][_cx]-13);}
	color(7);
	
	char ch;
	do{
		ch=getch();
		if(ch==27){break;}
		
		// 清除当前高亮
        color(7);
		gotoxy(2+_cx*8,3+_cy*3);
		printf("+-----+");
		gotoxy(2+_cx*8,3+_cy*3+1);
		printf("|     |");
		gotoxy(2+_cx*8,3+_cy*3+2);
		printf("+-----+");
        gotoxy(4+_cx*8,3+_cy*3+1);
        if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
        else{printf("B%02d",studentId[_cy][_cx]-13);}
		
		// 移动光标
		if(ch=='w'||ch=='W'){_cy=(_cy==0)?2:_cy-1;}
        else if(ch=='s'||ch=='S'){_cy=(_cy==2)?0:_cy+1;}
        else if(ch=='a'||ch=='A'){_cx=(_cx==0)?8:_cx-1;}
        else if(ch=='d'||ch=='D'){_cx=(_cx==8)?0:_cx+1;}
        else if(ch=='r'||ch=='R'){system("start README.md");}
        else if(ch==13){
            int id=studentId[_cy][_cx];
            if(id==4){
                unlockChallenge(3);
                static bool espMode=0;
                espMode=!espMode;
                if(espMode){
                    // 超能力者模式 - 红色高亮光标
                    color(4);
                    gotoxy(2+_cx*8,3+_cy*3);
                    printf("+-----+");
                    gotoxy(2+_cx*8,3+_cy*3+1);
                    printf("|     |");
                    gotoxy(2+_cx*8,3+_cy*3+2);
                    printf("+-----+");
                    gotoxy(4+_cx*8,3+_cy*3+1);
                    color(228);
                    printf("A04");
                    color(7);
                    for(int i=13;i<=22;i++){
                        gotoxy(2,i);
                        for(int j=0;j<40;j++){printf(" ");}
                    }
                    // 显示超能力者信息
                    gotoxy(2,14);
                    color(228);
                    printf("A4 [ESP]");
                    color(7);
                    gotoxy(2,16);
                    color(180);
                    printf("2147483647");
                    color(7);
                    printf("/");
                    color(179);
                    printf("2147483647");
                    color(7);
                    printf("/");
                    color(191);
                    printf("2147483647");
                    color(7);
                    gotoxy(2,17);
                    color(182);
                    printf("att: 2147483647");
                    color(7);
                    gotoxy(2,19);
                    color(4);
                    printf("This name is etched into the very core of CVS's memory.");
                    gotoxy(2,20);
                    printf("His power is beyond mortal comprehension.");
                    gotoxy(2,21);
                    printf("You cannot wield it without ");
                    color(78);
                    printf("i0^o@-e?&[s\\");
                    color(7);
                    printf(" ");
                }else{
                    // 普通模式 - 恢复黄色高亮
                    color(14);
                    gotoxy(2+_cx*8,3+_cy*3);
                    printf("+-----+");
                    gotoxy(2+_cx*8,3+_cy*3+1);
                    printf("|     |");
                    gotoxy(2+_cx*8,3+_cy*3+2);
                    printf("+-----+");
                    gotoxy(4+_cx*8,3+_cy*3+1);
                    printf("A04");
                    color(7);
                    for(int i=13;i<=22;i++){
                        gotoxy(2,i);
                        for(int j=0;j<40;j++){printf(" ");}
                    }
                    gotoxy(2,14);
                    color(7);
                    printf("A04 (Details coming soon)");
                }
            }
        }
        
        int id=studentId[_cy][_cx];
        // TODO: 显示对应学生的详细信息
        // showStudentInfo(id);
		
		// 绘制新高亮
		gotoxy(2+_cx*8,3+_cy*3);
		color(14);
		printf("+-----+");
		gotoxy(2+_cx*8,3+_cy*3+1);
		printf("|     |");
		gotoxy(2+_cx*8,3+_cy*3+2);
		printf("+-----+");
        gotoxy(4+_cx*8,3+_cy*3+1);
        if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
        else{printf("B%02d",studentId[_cy][_cx]-13);}
		color(7);
	}while(1);
	
	system("cls");
	color(7);
}

#endif// __EXTRA_H__
