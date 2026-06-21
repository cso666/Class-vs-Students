#ifndef __ACHIEVE_H__
#define __ACHIEVE_H__
#define __ACHIEVE_H_ver__ 8

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
	{2,"First Battle","Start a battle.",0},
	{3,"First Blood","Kill an enemy.",0},
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
	FILE* fp=fopen("saves/achievement.dat","wb");
	if(fp){
		for(int i=0;i<pcnt;i++){fwrite(&pahv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<ccnt;i++){fwrite(&cahv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}// 保存成就

void loadAch(){
	FILE* fp=fopen("saves/achievement.dat","rb");
	if(fp){
		for(int i=0;i<pcnt;i++){fread(&pahv[i].completed,sizeof(bool),1,fp);}
		for(int i=0;i<ccnt;i++){fread(&cahv[i].completed,sizeof(bool),1,fp);}
		fclose(fp);
	}
}// 加载成就

void checkProgress(int id){
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

// 显示成就页面
void achievementMenu(){
	system("cls");
    checkProgress(4);
    color(11);
    printf(R"---(+-------------------------------------------------------------------------+
|              Progress              |             Challenges             |
+-------------------------------------------------------------------------+)---");
    color(7);
    printf(R"---(
|    1. First Launch                 |    1. Total Insanity               |
|    2. First Battle                 |    2. Heavenly Strike              |
|    3. First Blood                  |    3. ESP User                     |
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

#endif// _ACHIEVE_H__