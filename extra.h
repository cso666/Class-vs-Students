#ifndef __EXTRA_H__
#define __EXTRA_H__
#define sslp(n) Sleep(n*1000)
// be used for word-paint
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
     R"---(“这一片有人讲话就记 你 头上。”
“老师这不符合社会主义制度！”
“这符合人民代表大会制度。”)---",
     R"---("If someone in this area talks, I'm holding YOU accountable."
"Teacher, that's not how Socialism works!"
"This is how the People's Congress works.")---",15},

    {R"---(这色子合理吗？)---",
     R"---(Is this color-son in-river?)---",
     R"---(这色子合理吗？)---",
     R"---(Is this color-son in-river?)---",15},

    {R"---(我不具备任何优势，因此我也不准备发言稿。)---",
     R"---(No strengths. No speech.)---",
     R"---(“学校要征集参加介绍宪法活动的人，
请谈谈你参加此次活动有哪些优势并准备一个100字左右的发言稿。”
答：我不具备任何优势，因此我也不准备发言稿。)---",
     R"---("School needs people to introduce the Constitution.
Tell us your strengths and write a ~100-word speech."
Answer: No strengths. No speech.)---",15},

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

#endif// __EXTRA_H__