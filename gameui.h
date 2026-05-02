#ifndef __GAMEUI_H__
#define __GAMEUI_H__
#define sslp(n) Sleep(n*1000)

/*
 * gameui.h is including:
 *   ACHIVEVMENT
 *   SETTINGS
 *   TIPS
 *   GUIDE
 *   GAME
 */

// ===ACHIEVEMENT===
struct p_ahv{
	int id;
	string name;
	string method;
	bool completed;
};// 进度成就
struct c_ahv{
	int id;
	string name;
	string hint;
	string solution;
	bool completed;
};// 挑战成就
static p_ahv pahv[]={
	{1,"First Launch","Open the game once.",0},
	{2,"First Blood","Kill an enemy.",0},
	{3,"First Battle","Start a battle.",0},
	{4,"Explorer","Open Achievement page.",0},
	{5,"Seeker","Open Guidance page.",0},
	{6,"Settings Master","Open Settings page.",0},
	{7,"Last Stand","Clear a battle with HP <= 20%.",0},
	{8,"Flawless","Clear a battle with full HP.",0},
};// 进度成就数组
static c_ahv cahv[]={
	{1,"Total Insanity","\"How are all students losing their minds?\"",
    "Complete the game in Auto Insane Mode.",0},
	{2,"Heavenly Strike","\"A5 has no damage cap of 30!\"",
    "Deal more than 30 damage with A5.",0},
	{3,"ESP User","\"Every interface should respond to Enter, no?\"",
    "Press Enter on A4 in Guidance page.",0},
    {4,"Scape... Escape?","\"I want to find a student to be the scapegoat at first...\"",
    "Trigger the 1% scapegoat event when no class B students are present.",0},
    {5,"Ineffective Warning?","\"Why all the teachers are speechless?\"",
    "Trigger the listening punishment 5 times in one day.",0},
    {6,"Total Destruction","\"Headteacher+History=PPPPPunishment!!!\"",
    "Both teams get punished in History class 0.01%ly drawed.",0},
    {7,"OIer's game!","\"Actually, we wanted to develop CVS at ICT classes.\"",
    "Trigger the 0.1% OIer count event in ICT class and achieve a draw.",0},
};// 挑战成就数组
static int pcnt=sizeof(pahv)/sizeof(pahv[0]);
static int ccnt=sizeof(cahv)/sizeof(cahv[0]);

void printAch(const char* prefix,const char* name){
	color(10);
	gotoxy(0,32);
	printf("[%s] %s",prefix,name);
    gotoxy(0,0);
	color(7);
}// 成就解锁输出（在控制台最后一行）

void saveAch(){
	FILE* fp=fopen("achievement.dat","wb");
	if(fp){
		for(int i=0;i<pcnt;i++){fwrite(&pahv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<ccnt;i++){fwrite(&cahv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}// 保存成就

void loadAch(){
	FILE* fp=fopen("achievement.dat","rb");
	if(fp){
		for(int i=0;i<pcnt;i++){fread(&pahv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<ccnt;i++){fread(&cahv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}// 加载成就

void unlockProgress(int id){
	if(id<1||id>pcnt){return;}
	if(!pahv[id-1].completed){
		pahv[id-1].completed=1;
		saveAch();
		printAch("ACHIEVEMENT UNLOCKED",pahv[id-1].name.c_str());
	}
}// 解锁进度成就

void unlockChallenge(int id){
	if(id<1||id>ccnt){return;}
	if(!cahv[id-1].completed){
		cahv[id-1].completed=1;
		saveAch();
		printAch("CHALLENGE COMPLETED",cahv[id-1].name.c_str());
	}
}// 解锁挑战成就

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
}// 检查进度成就

// 显示成就页面
void achievementMenu(){
	system("cls");
    color(11);
    printf(R"---(+-------------------------------------------------------------------------+
|              Progress              |             Challenges             |
+-------------------------------------------------------------------------+)---");
    color(7);
    printf(R"---(
|    1. First Launch                 |    1. Total Insanity               |
|    2. First Blood                  |    2. Heavenly Strike              |
|    3. First Battle                 |    3. ESP User                     |
|    4. Explorer                     |    4. Scape... Escape?             |
|    5. Seeker                       |    5. Ineffective Warning?         |
|    6. Settings Master              |    6. Total Destruction            |
|    7. Last Stand                   |    7. OIer's game!                 |
|    8. Flowless                     |                                    |
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
|                                                                         |)---");
    color(11);
    printf(R"---(
+-------------------------------------------------------------------------+
|                 Enter to view solutions (of challenges)                 |
|          W/A/S/D to move the cursor, Esc to return to mainpage          |
+-------------------------------------------------------------------------+)---");
    color(14);
    gotoxy(15,1);
    printf("Progress");
    gotoxy(51,1);
    printf("Challenges");
    gotoxy(0,3);
    printf("| ->");
	
    p_ahv& a=pahv[0];
    gotoxy(4,max(ccnt,pcnt)+4);
    color(14);
    printf("%s",a.name.c_str());
    color(7);
    if(a.completed){
        color(10);
        printf("  [UNLOCKED]");
    }else{
        color(8);
        printf("  [LOCKED]");
    }
    gotoxy(4,max(ccnt,pcnt)+6);
    color(7);
    printf("%s",a.method.c_str());

	char ch=' ';
    bool cPa=0;
    int cIn=0,upin=max(ccnt,pcnt)+4,dwin=upin+5;
	while(1){
		ch=getch();
		if(ch==27){break;}
        if(ch==13&&cPa==1){
			c_ahv& tmp=cahv[cIn];
			if(!tmp.completed){
				gotoxy(4,upin+2);
				color(15);
				printf("%s",tmp.solution.c_str());
				color(7);
                ch=getch();
			}
            gotoxy(4,dwin);
            for(int i=0;i<50;i++){printf(" ");}
		}

		if(ch=='a'||ch=='A'||ch=='d'||ch=='D'){
            gotoxy(cPa*37,cIn+3);
            color(7);
            printf("|   ");

			cPa=!cPa;
            int maxIdx=(cPa==0)?pcnt:ccnt;
			cIn=min(cIn,maxIdx-1);
            
            gotoxy(cPa*37,cIn+3);
            color(14);
            printf("| ->");
		}else if(ch=='w'||ch=='W'){
            gotoxy(cPa*37,cIn+3);
            color(7);
            printf("|   ");

			int maxIdx=(cPa==0)?pcnt:ccnt;
			cIn--;
			if(cIn<0){cIn=maxIdx-1;}

            gotoxy(cPa*37,cIn+3);
            color(14);
            printf("| ->");
		}else if(ch=='s'||ch=='S'){
            gotoxy(cPa*37,cIn+3);
            color(7);
            printf("|   ");

			int maxIdx=(cPa==0)?pcnt:ccnt;
			cIn++;
			if(cIn>=maxIdx){cIn=0;}

            gotoxy(cPa*37,cIn+3);
            color(14);
            printf("| ->");
		}

        for(int i=upin;i<=dwin;i++){
			gotoxy(2,i);
			for(int j=0;j<70;j++){printf(" ");}
		}

        if(cPa==0){
			p_ahv& a=pahv[cIn];
			gotoxy(4,upin);
			color(14);
			printf("%s",a.name.c_str());
			color(7);
			
			if(a.completed){
				color(10);
				printf("  [UNLOCKED]");
			}else{
				color(8);
				printf("  [LOCKED]");
			}
			
			gotoxy(4,upin+2);
			color(7);
			printf("%s",a.method.c_str());
		}else{
			c_ahv& a=cahv[cIn];
			gotoxy(4,upin);
			color(14);
			printf("%s",a.name.c_str());
			color(7);
			
			if(a.completed){
				color(10);
				printf("  [COMPLETED]");
			}else{
				color(8);
				printf("  [NOT COMPLETED]");
			}
			
			gotoxy(4,dwin);
			color(8);
			printf("%s",a.hint.c_str());
			
			if(a.completed){
				gotoxy(4,upin+2);
				color(7);
				printf("%s",a.solution.c_str());
			}
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

// ===GUIDE===
struct stuDis{
    const char*name;
    const char*hp;
    const char*san;
    const char*sta;
    const char*atk;
    const char*passive;
    const char*active;
};
static stuDis stuDesc[]={
    // id=1  A01
    {"A01","125","100","100","15",
     "[Small Luck]: 5% chance for +5 ATK and stun target for 1 turn.\n[Tired]: 1.25x stamina cost.",
     "{Lemon So Sour}: -30 HP self; -15 MAX HP target (1 class)."},
    // id=2  A02
    {"A02","100","120","100","18",
     "[Unconnect]: Cannot act when SAN <= 40.\n[Subjective]: +5 ATK vs B10; -24 SAN self.",
     "{Parents Gone}: -30 STA; 2x ATK; 80% chance of -15 self damage; Damage  |\n| cap 45."},
    // id=3  A03
    {"A03","120","105","110","2",
     "[Become Red]: Attacker/defender takes 1.28x damage next turn.\nOn 3 triggers, target goes insane, A03 -20 SAN.\n[Things Disappeared]: 50% per turn: -5 SAN, +5 HP, +5 STA.",
     "{Your Mother}: -15 HP, -25 SAN self; -5 HP target; marked target takes  |\n| -15 SAN extra and 1.05x SAN damage when attacked by A03 (1 day)."},
    // id=4  A04
    {"A04","60","100","100","5",
     "[Fast]: 20% chance to nullify incoming attacks.\n[Mice Shout]: -3 SAN to all enemies at start of each turn.\n[Weak]: Takes 1.25x damage.",
     "{Snack Theft}: -20 STA; ATK temporarily set to 7; Damage cap 12."},
    // id=5  A05
    {"A05","130","120","100","15",
     "[Middle Luck]: 10% chance for +5 ATK and stun target for the class.\n[Strong]: Immune to all healing except from A09.",
     "{Mamba Out}: -15 STA; +5 SAN self; -25 HP target."},
    // id=6  A06
    {"A06","90","100","100","10",
     "[LaoDa]: Takes 0.78x damage from LaoMen; deals 1.1x damage to them.\n[LoseJ]: Immune to SAN damage; nearby allies take 1.1x SAN effects.",
     "{Early Warning}: -5 STA; +5 SAN to two allies; -20 SAN target; target   |\n| takes 1.2x damage next turn."},
    // id=7  A07
    {"A07","280","200","200","1",
     "[Great Luck]: Redirects 80% of ally damage to self.\n[Unbreakable]: First death: MAX HP->140, heal to 70 HP, STA->1.",
     "{RenShengA}: -5 STA; 20% chance to reflect original damage to attacker  |\n| (entire class)."},
    // id=8  A08
    {"A08","100","100","100","8",
     "[Turtle's Long Life]: Incoming damage capped at 18.\n[Brainstorm]: All allies gain 1.2x ATK each turn.\n[Six A+]: +4 ATK when all bars full.",
     "{Dimensional Strike}: vs LaoMen(once/day): -5 STA, 20% MAX HP damage;   |\n| else: -15 STA, 10% MAX HP damage, -1 SAN self."},
    // id=9  A09
    {"A09","85","110","180","12",
     "[Mr.Monitor]: 1.35x ATK for all allies; +10 damage cap on first turn of\neach class if A09 is sane.\n[Peacemaker]: 9% chance to nullify incoming damage to any ally.\n[Abundant Support]: A09's attacks with damage >=18 can also lead to\n-20 SAN, -10 STA target.",
     "{Find Out}: -5 STA; ATK=10 (temporary); damage cap 40; all allies heal  |\n| 1/3 of damage dealt."},
    // id=10 A10
    {"A10","80","100","120","10",
     "[Sugar But Smart]: Each attack gives the target +1 Sugar counter;\nwhen A10 dies, all enemies take Sugarx2 damage.\n[Stay]: SAN loss x0.8; SAN gain x1.2.",
     "{Big Shoot}: Used at turn 1/2/3: loses turns until turn 3, then have an |\n| auto-attack with ATK=16 and multiplier 3/2/1, no damage cap; costs\n| 30/17/5 STA."},
    // 木昆木
    {"GUNMU","GUNMU","GUNMU","GUNMU","GUNMU","GUNMU","GUNMU"},
    // id=12 A12
    {"A12","110","80","110","10",
     "[Eat Well]: End of day: restore (Math classes today x5) HP.\n[Not Stupid]: Damage taken = max(0, (150-SAN)/150 x damage).\n[YogHURT]: Attacked A08, other enemies take (rand%40)% of the damage.",
     "{Enchanted Golden Apple}: Once per game, no STA cost. Instantly restore |\n| 15 HP, +3 ATK; next 3 turns: +10 HP/SAN/STA, -1 ATK per turn."},
    // id=13 A13
    {"A13","90","90","130","9",
     "[We Are Legends]: ATK multiplier = max(1, team STA/500).\n[So Delicious]: Restore STA equal to hp taken.",
     "{Year Pig Weigh}: Requires STA >=70% max. No STA cost. First hit with   |\n| ATK=8 (cap 40), then ATK=18 for 3 turns or until STA <70%."},
    // id=14 B01
    {"B01","105","120","88","8",
     "[Catgirl]: Incoming damage reduced by 10-20% (B07 immune).\n[Nimble]: 0.85x stamina cost (except SwapSeat).\n[Madness]: SAN loss: 70% self, 15% each alive ally.",
     "{SwapSeat}: Fails vs B07. Success: +3 HP, -2 STA target. Fail: attack   |\n| with ATK+2, -5 STA. If target marked: remove mark, deal ATK+6 HP & -10  |\n| SAN, self ATK-1 permanently, heal +5, cost -7 STA."},
    // id=15 B02
    {"B02","100","93","100","12",
     "[TalkBack]: Takes 1.08x damage, 30% chance to reflect 60% damage.\n[Height Advantage]: When hit by >40%MAX HP damage, 30% chance to reduce\nby 70% but -12 STA.\n[Recitalist]: When killing an enemy, other enemies lose 8% current HP.",
     "{Barking}: -10 STA; ATK=10; -12 SAN target; target loses -5 SAN/turn    |\n| (rest of class)."},
    // id=16 B03
    {"B03","100","100","100","6",
     "[Tutor(TA)]: +2 ATK, +20% HP/SAN/STA caps when teacher is Math.\n[Calm&Composed]: +5 HP at end of each turn.\n[MathDUO]: +10% caps when A10 is on the same team.",
     "{???}: ATK=5; +10 SAN, +10 STA self; -10 SAN, -10 STA target."},
    // id=17 B04
    {"B04","74","36","110","11",
     "[GeniusBEET]: Takes 0.8x damage.\n[ForeignFriend]: All allies -15% damage taken during English A/B.\n[LaoKing]: +20 STA, +20 SAN at end of class.\nUnaffected by subject effects.",
     "{BP}: ATK=4; heal HP equal to damage dealt."},
    // id=18 B05
    {"B05","102","100","106","9",
     "[pi2gu4]: 40% chance per turn to change HP/SAN/STA by +-10.\n[emo]: When SAN<=60%, take 0.6x damage but 40% chance to miss attacks.",
     "{GoHome}: -10 STA; skip the rest of this class, +10 HP at end of class."},
    // id=19 B06
    {"B06","96","92","105","random(0~14)",
     "[CADB]: Random ATK multiplier: 20% x0.6, 60% x1.0, 12% x1.28, 5% x1.8, \n2% x2.0, 1% x2.5.\n[Nazistent]: 1.2x stamina cost.",
     "{OldThousand}: ATK=9; hide opponent's HP/SAN/STA bars for this class."},
    // id=20 B07
    {"B07","104","86","106","11",
     "[CowStrength]: STAgain x1.3, SANgain x1.1; STAloss x0.9, SANloss x0.95.\n[Sigma]: Immune to CatGirl and Madness. Cannot be marked by SwapSeat.\n[BothHigh&Cold]: Immune to all ally buffs except A09.",
     "{???}: (Active skill coming soon)"},
    // id=21 B08
    {"B08","108","98","104","10",
     "[BreachOfFaith]: 10% damage reduction; 15% reduction and 90% be_att_mul\nduring English B.\n[KongyiJi]: During Math, lose 2xATK HP and ATK SAN, first attack ATKx2.",
     "{WantFight?}: -8 STA; both lose 15 SAN; ATK=14; +3 ATK for 3 turns, +2  |\n| HP/turn; after 3 turns -20 STA, -8 HP."},
    // id=22 B09
    {"B09","103","100","98","10",
     "[Adonis]: 1.5x ATK when A09 is on the same team.\n[Sad]: When HP<=65, 0.4x ATK and 0.2x be_att_mul; restore when HP>65.\n[Perfect...Miss...]: If any bar contains digit 2, +11 HP, +16 STA.",
     "{???}: (Active skill coming soon)"},
    // id=23 B10
    {"B10","96","80","98","7",
     "[Subjective]: ATK multiplier and be_att_mul x(1+0.2x alive) each turn.\n[Shouldn't...]: When insane, deal 5x(ATK x att_mul+tmp) damage (capped\n45) to all enemies, self HP x0.3.",
     "{???}: (Active skill coming soon)"},
    // id=24 B11
    {"B11","104","100","102","9",
     "[OneMoreFoot]: 99% chance to cancel lethal attack, target loses 5 SAN.\n[SongsTalent]: +10 SAN to all allies at start of each turn.",
     "{Guest}: -15 STA; target-5 SAN, -5 STA; all allies+5 SAN, +5 STA; all   |\n| enemies-5 SAN, -5 STA; 3 turns chance to mark enemies as not listening."},
    // id=25 B12
    {"B12","96","100","140","9",
     "[HitPlane]: After attack, +5 STA and +(white - target.white)/3 STA.\n[Letsrun]: -3 HP, +6 STA at start of each turn.\n[Undying]: First death: MAX HP-54, revive, counterattack for 2x damage.",
     "{ShakeXueBi}: Requires STA >=20 to use. -30 STA (if STA<30 becomes      |\n| exhausted). +10 SAN, +10 HP self; allies-12 SAN, -5 HP; enemies-15 SAN, |\n| -10 HP; target extra-5 SAN, -5 HP; 3 turns: +10 STA/turn, 1.2x damage   |\n| taken, marked not listening."},
    // id=26 B13
    {"B13","80","120","70","8",
     "[TakeItEasy...]: 15% chance per day to lose 10 SAN each turn.\n[SongsAreLife!]: During Art/Music/PE/Biology/Geography, 80% chance to\nleave battle, 20% chance +6 ATK.",
     "{KnowledgeIsPowDer}: Requires 20+ STA. Randomly costs 10/30 STA. Gains  |\n| +4/+8 ATK and 1.35x/2x damage. Extra -10 STA, target -15 SAN if STA     |\n| remains enough."},
    // id=27 B14
    {"B14","76","108","90","6",
     "[Baby]: count add 1 when hit.\n[Sorry]: When SAN<60, -3 tmp_att_plus, att_mul x(1+count x0.05).\n[Bambino]: Damage cap 10.",
     "{Self-healing}: Randomly heal 6 HP/SAN/STA to an ally."},
    // id=28 B15
    {"B15","102","100","100","8",
     "[PerfectRain]: Starts as SPR(with 3 Rain). Becomes GBR when hit. End of\nturn: SPR heals lowest HP ally; GBR damages highest HP enemy. \n[SkywardFireworks]: When an enemy dies, all allies gain 1.2x SAN/STA\n(crazy->SAN=1, exhausted->STA=1).",
     "{RainyDays}: Costs 15-20 STA. Self-8 SAN, -5 HP; target-14 SAN, -7 HP.  |\n| 50% chance to switch SPR/GBR. SPR heals +8 SAN, +5 HP; GBR deals extra  |\n| -8 SAN, -5 HP to both."}
};
const int stuDcnt=sizeof(stuDesc)/sizeof(stuDesc[0]);

void guide(){
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

    stuDis& s0=stuDesc[0];
    
    gotoxy(2,14);
    color(14);
    printf("%s",s0.name);
    color(7);
    printf("  ");
    color(4);
    printf("%s",s0.hp);
    color(7);
    printf("/");
    color(3);
    printf("%s",s0.san);
    color(7);
    printf("/");
    color(15);
    printf("%s",s0.sta);
    color(7);
    printf("  ");
    color(6);
    printf("att:%s",s0.atk);
    color(7);

    // 被动技能
    gotoxy(2,16);
    color(7);
    const char*p=s0.passive;
    int line=16;
    while(*p&&line<=22){
        gotoxy(2,line);
        while(*p&&*p!='\n'){
            printf("%c",*p);
            p++;
        }
        if(*p=='\n'){p++;}
        line++;
    }
    
    // 主动技能
    gotoxy(2,++line);
    color(14);
    printf("%s",s0.active);
	
	char ch;
	do{
		ch=getch();
		if(ch==27){break;}
        bool a4_esp=0;
		
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
		if(ch=='w'||ch=='W'){_cy=(_cy==0)?2:_cy-1;a4_esp=0;}
        else if(ch=='s'||ch=='S'){_cy=(_cy==2)?0:_cy+1;a4_esp=0;}
        else if(ch=='a'||ch=='A'){_cx=(_cx==0)?8:_cx-1;a4_esp=0;}
        else if(ch=='d'||ch=='D'){_cx=(_cx==8)?0:_cx+1;a4_esp=0;}
        else if(ch=='r'||ch=='R'){system("start README.md");}
        else if(ch==13){
            int id=studentId[_cy][_cx];
            if(id==4){
                unlockChallenge(3);
                static bool espMode=0;
                espMode=!espMode;
                if(espMode){
                    a4_esp=1;
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
                    for(int i=13;i<23;i++){
                        gotoxy(2,i);
                        for(int j=0;j<72;j++){printf(" ");}
                    }
                    // 显示超能力者信息
                    gotoxy(2,14);
                    color(228);
                    printf("A04 [ESP]");
                    color(7);
                    gotoxy(2,16);
                    color(180);
                    printf("10`n^095|7");
                    color(7);
                    printf("/");
                    color(179);
                    printf("10e1[$h567");
                    color(7);
                    printf("/");
                    color(191);
                    printf("!061v0?/67");
                    color(7);
                    gotoxy(2,17);
                    color(182);
                    printf("att: 1~6f}0p56b");
                    color(7);
                    gotoxy(2,19);
                    color(4);
                    printf("Writ deep into CVS's heart is a name you do not know.");
                    gotoxy(2,20);
                    color(78);
                    printf("O@M`a*f5\\");
                    color(4);
                    printf("'s power overflows. You cannot yet command it.");
                    gotoxy(2,22);
                    printf("It's an unfathomable power that should be ");
                    color(78);
                    printf("i0^o@-e?&[s\\");
                    color(7);
                }else{
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
                    for(int i=13;i<=24;i++){
                        gotoxy(2,i);
                        for(int j=0;j<72;j++){printf(" ");}
                    }
                    gotoxy(2,14);
                    color(7);
                    printf("A04 (Details coming soon)");
                }
            }
        }
        
        if(!a4_esp){
            for(int i=13;i<=24;i++){
                gotoxy(2,i);
                for(int j=0;j<72;j++){printf(" ");}
            }

            int id=studentId[_cy][_cx];
            if(id>=1&&id<=28&&stuDesc[id-1].name[0]!='\0'){
                for(int i=13;i<=24;i++){
                    gotoxy(2,i);
                    for(int j=0;j<72;j++){printf(" ");}
                }

                int id=studentId[_cy][_cx];
                if(id>=1&&id<=28&&stuDesc[id-1].name[0]!='\0'){
                    stuDis& s=stuDesc[id-1];
                    
                    gotoxy(2,14);
                    color(14);
                    printf("%s",s.name);
                    color(7);
                    printf("  ");
                    color(4);
                    printf("%s",s.hp);
                    color(7);
                    printf("/");
                    color(3);
                    printf("%s",s.san);
                    color(7);
                    printf("/");
                    color(15);
                    printf("%s",s.sta);
                    color(7);
                    printf("  ");
                    color(6);
                    printf("att:%s",s.atk);
                    color(7);

                    // 被动技能
                    gotoxy(2,16);
                    color(7);
                    const char*p=s.passive;
                    int line=16;
                    while(*p&&line<=22){
                        gotoxy(2,line);
                        while(*p&&*p!='\n'){
                            printf("%c",*p);
                            p++;
                        }
                        if(*p=='\n'){p++;}
                        line++;
                    }
                    
                    // 主动技能
                    gotoxy(2,++line);
                    color(14);
                    printf("%s",s.active);
                }
            }

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
        }
		color(7);
	}while(1);
	
	system("cls");
	color(7);
}

// ===GAME===
extern void CVS_game();
int nowy=4;
bool timeOfStarting=0;

void clear_action_area(){
	for(int i=19;i<=26;i++){
		gotoxy(0,i);
		for(int j=0;j<80;j++){printf(" ");}
	}
}

void startASCIIart(){
	printf("\
       _\n\
      / \n\
     |    \n\
      \\_");
	sslp(0.2);
	ppput("lass",0.15);
	sslp(0.4);
	system("cls");
	printf("\
             _\n\
            /\n\
            \\  \n\
          __/");
	sslp(0.2);
	ppput("tudents",0.15);
	sslp(0.4);
	system("cls");
	printf("\
       _    /_ \n\
      /    //\n\
     | \\  / \\  \n\
      \\_\\/__/  ");
	gotoxy(2,5);
	sslp(0.2);
	ppput("Class vs. Students",0.06);
	sslp(1);
	color(4);
	gotoxy(7,2);
	printf("\\  /");
	gotoxy(8,3);
	printf("\\/");
	gotoxy(11,1);
	printf("/");
	gotoxy(12,0);
	printf("/");
	gotoxy(2,5);
	printf("Class vs. Students");
	gotoxy(0,7);
	color(7);
	printf("Press any key to start...");
	checkProgress(1);  // 首次启动成就
	getch();
}

#endif// __GAMEUI_H__