#ifndef __TURN_H__
#define __TURN_H__

typedef vector<stud*> stuV;
typedef vector<void*> voiV;

struct actCho{
    bool useSk;
    stud*user;
};

extern bool debug_on;
extern void logPrint(int colorCode,const char*format,...);
extern bool isalive[35];
extern int Anum,Bnum;
extern int sbj_teacher;
extern void hitt(void*f1,void*f2,voiV T1,voiV T2);
extern void sk_hitt(void*f1,void*f2,voiV T1,voiV T2);
extern void sett(voiV lA,voiV lB,const int k);
extern void clear_action_area();

// 状态检查函数
static void checkIN(stuV&team){
	for(auto*s:team){
		if(s&&s->blue<0&&!s->is_crazy){
			s->is_crazy=1;
			s->att_mul*=1.5;
			if(debug_on){logPrint(12,
			"[STATUS] %s has gone INSANE! Attack power x1.5!\n",s->name.c_str());}
			clear_action_area();
			gotoxy(0,21);
			color(12);
			printf("[INSANE] %s has gone insane! Attack power increased by 1.5x!",s->name.c_str());
			color(7);
			printf("\nPress any key to continue...");
			getch();
			clear_action_area();
		}
	}
}

// 状态检查函数
static void checkCL(stuV&team){
	for(auto*s:team){
		if(s&&s->blue>=0&&s->is_crazy){
			s->is_crazy=0;
			s->att_mul/=1.5;
			if(debug_on){logPrint(10,"[STATUS] %s has calmed down.\n",s->name.c_str());}
			clear_action_area();
			gotoxy(0,21);
			color(10);
			printf("[CALM] %s has calmed down. Attack power restored.",s->name.c_str());
			color(7);
			printf("\nPress any key to continue...");
			getch();
			clear_action_area();
		}
	}
}

// 回合开始
static void startTurn(stuV&teamA,stuV&teamB,int tchID){
	for(auto*s:teamA){
		if(s){s->on_turn_start(0,tchID,teamA,teamB);}
	}
	for(auto*s:teamB){
		if(s){s->on_turn_start(0,tchID,teamB,teamA);}
	}
	if(debug_on){
		for(auto*s:teamA){
			if(s&&s->status==-1&&s->white<=0){logPrint(8,
			"[STATUS] %s is EXHAUSTED! Cannot act.\n",s->name.c_str());}
		}
		for(auto*s:teamB){
			if(s&&s->status==-1&&s->white<=0){logPrint(8,
			"[STATUS] %s is EXHAUSTED! Cannot act.\n",s->name.c_str());}
		}
	}
}

// 回合结束
static void endTurn(stuV&teamA,stuV&teamB,int tchID){
	for(auto*s:teamA){
		if(s){s->on_turn_end(0,tchID,teamA,teamB);}
	}
	for(auto*s:teamB){
		if(s){s->on_turn_end(0,tchID,teamB,teamA);}
	}
}

// 战斗结束检查
static bool endBattle(stuV&teamA,stuV&teamB){
	bool aHasAlive=0,bHasAlive=0;
	for(auto*s:teamA){
		if(s&&isalive[s->id]&&s->red>=0){aHasAlive=1;break;}
	}
	for(auto*s:teamB){
		if(s&&isalive[s->id]&&s->red>=0){bHasAlive=1;break;}
	}
	if(!aHasAlive||!bHasAlive){
		Anum=0,Bnum=0;
		for(auto*s:teamA){
			if(s&&isalive[s->id]&&s->red>=0){Anum++;}
		}
		for(auto*s:teamB){
			if(s&&isalive[s->id]&&s->red>=0){Bnum++;}
		}
		return 1;
	}
	return 0;
}

// 选择攻击方
static stud* selAtt(stuV&team,const string&teamN,int startL){
	int size=team.size();
	int attIdx=0;
	while(attIdx<size&&(!team[attIdx]||!isalive[team[attIdx]->id]||
		team[attIdx]->status==-1||team[attIdx]->red<0)){attIdx++;}
	if(attIdx>=size){return 0;}
	clear_action_area();
	gotoxy(0,19);
	color(14);
	printf("%s - Select your fighter (W/S keys, Enter to confirm):\n",teamN.c_str());
	for(int i=0;i<size;i++){
		if(!team[i]){continue;}
		stud*s=team[i];
		gotoxy(0,startL+i);
		if(!isalive[s->id]||s->red<0){
			color(8);
			printf("   %s (DEAD)          \n",s->name.c_str());
			color(7);
			continue;
		}
		if(i==attIdx){
			color(14);
			printf("-> ");
		}else{printf("   ");}
		if(s->status==-1){
			color(8);
			printf("%s (EXHAUSTED)\n",s->name.c_str());
		}else if(s->is_crazy){
			color(12);
			printf("%s (ATT:%02d)\n",s->name.c_str(),int(s->att*s->att_mul+s->tmp_att_plus));
		}else{
			color(teamN=="Team A"?10:9);
			printf("%s (ATT:%02d)\n",s->name.c_str(),int(s->att*s->att_mul+s->tmp_att_plus));
		}
		color(7);
	}
	while(1){
		char key=getch();
		if(key=='w'||key=='W'){
			int newIdx=attIdx;
			do{
				newIdx--;
				if(newIdx<0){newIdx=size-1;}
			}while(newIdx!=attIdx&&(!team[newIdx]||!isalive[team[newIdx]->id]||
				team[newIdx]->status==-1||team[newIdx]->red<0));
			if(newIdx!=attIdx){
				gotoxy(0,startL+attIdx);
				printf("   ");
				attIdx=newIdx;
				gotoxy(0,startL+attIdx);
				color(14);
				printf("->");
				color(7);
			}
		}else if(key=='s'||key=='S'){
			int newIdx=attIdx;
			do{
				newIdx++;
				if(newIdx>=size){newIdx=0;}
			}while(newIdx!=attIdx&&(!team[newIdx]||!isalive[team[newIdx]->id]||
				team[newIdx]->status==-1||team[newIdx]->red<0));
			if(newIdx!=attIdx){
				gotoxy(0,startL+attIdx);
				printf("   ");
				attIdx=newIdx;
				gotoxy(0,startL+attIdx);
				color(14);
				printf("->");
				color(7);
			}
		}else if(key==13){
			if(team[attIdx]&&isalive[team[attIdx]->id]&&team[attIdx]->status!=-1){return team[attIdx];}
		}
	}
}

// 选择受击方
static stud*selTar(stud* atter,stuV& defer,const string& teamN,int startL){
	// 疯人状态：随机选择
	if(atter->is_crazy){
		stuV allTar;
		for(auto*s:defer){
			if(s&&isalive[s->id]&&s->red>=0){allTar.push_back(s);}
		}
		if(allTar.empty()){return 0;}
		int randIdx=rand()%allTar.size();
		clear_action_area();
		gotoxy(0,19);
		color(14);
		printf("%s - tar selected randomly (INSANE mode):",teamN.c_str());
		// 乱码选项
		vector<string> INstr;
		for(int i=0;i<3;i++){
			string s;
			for(int j=0;j<15;j++){s+=33+rand()%94;}
			INstr.push_back(s);
		}
		for(int i=0;i<3;i++){
			gotoxy(0,20+i);
			color(12);
			printf("   %s",INstr[i].c_str());
		}
		// 模拟用户选择（自动选第一个）
		int INcho=0;
		for(int i=0;i<3;i++){
			gotoxy(0,20+i);
			if(i==INcho){
				color(78);
				printf("-> %s",INstr[i].c_str());
			}else{
				color(12);
				printf("   %s",INstr[i].c_str());
			}
		}
		sslp(0.5);
		gotoxy(0,24);
		color(12);
		printf("[INSANE] %s is insane! tar selected randomly!",atter->name.c_str());
		color(7);
		sslp(1);
		clear_action_area();
		return allTar[randIdx];
	}
	// 正常选择
	int size=defer.size();
	int tarIdx=0;
	while(tarIdx<size&&(!defer[tarIdx]||!isalive[defer[tarIdx]->id]||defer[tarIdx]->red<0)){tarIdx++;}
	if(tarIdx>=size){return 0;}
	clear_action_area();
	gotoxy(0,19);
	color(14);
	printf("%s - Select your tar (W/S keys, Enter to confirm):\n",teamN.c_str());
	for(int i=0;i<size;i++){
		if(!defer[i]){continue;}
		stud*s=defer[i];
		gotoxy(0,startL+i);
		if(!isalive[s->id]||s->red<0){
			color(8);
			printf("   %s (DEAD)          \n",s->name.c_str());
			color(7);
			continue;
		}
		if(i==tarIdx){
			color(14);
			printf("-> ");
		}else{printf("   ");}
		if(s->status==-1){
			color(8);
			printf("%s (EXHAUSTED)\n",s->name.c_str());
		}else if(s->is_crazy){
			color(12);
			printf("%s (ATT:%02d)\n",s->name.c_str(),int(s->att*s->att_mul+s->tmp_att_plus));
		}else{
			color(teamN=="Team A"?9:10);
			printf("%s (ATT:%02d)\n",s->name.c_str(),int(s->att*s->att_mul+s->tmp_att_plus));
		}
		color(7);
	}
	while(1){
		char key=getch();
		if(key=='w'||key=='W'){
			int newIdx=tarIdx;
			do{
				newIdx--;
				if(newIdx<0){newIdx=size-1;}
			}while(newIdx!=tarIdx&&(!defer[newIdx]||!isalive[defer[newIdx]->id]||defer[newIdx]->red<0));
			if(newIdx!=tarIdx){
				gotoxy(0,startL+tarIdx);
				printf("   ");
				tarIdx=newIdx;
				gotoxy(0,startL+tarIdx);
				color(14);
				printf("->");
				color(7);
			}
		}else if(key=='s'||key=='S'){
			int newIdx=tarIdx;
			do{
				newIdx++;
				if(newIdx>=size){newIdx=0;}
			}while(newIdx!=tarIdx&&(!defer[newIdx]||!isalive[defer[newIdx]->id]||defer[newIdx]->red<0));
			if(newIdx!=tarIdx){
				gotoxy(0,startL+tarIdx);
				printf("   ");
				tarIdx=newIdx;
				gotoxy(0,startL+tarIdx);
				color(14);
				printf("->");
				color(7);
			}
		}else if(key==13){
			if(defer[tarIdx]&&isalive[defer[tarIdx]->id]){return defer[tarIdx];}
		}
	}
}

// 选择行动类型
static actCho selAct(stud* atter,const string& teamN){
	bool canSk=(atter->white>0&&!atter->ct2.empty());
	int choice=0;
	clear_action_area();
	gotoxy(0,19);
	color(14);
	printf("Choose action (W/S keys, Enter to confirm):");
	while(1){
		gotoxy(0,20);
		if(choice==0){
			color(14);
			printf("-> ");
			color(10);
			printf("NORMAL ATTACK");
		}else{
			printf("   ");
			color(10);
			printf("NORMAL ATTACK");
		}
		color(7);
		gotoxy(0,21);
		if(choice==1){
			color(14);
			printf("-> ");
			if(canSk){
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}else{
				color(8);
				printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"NO SKILL":atter->ct2[0].c_str());
			}
		}else{
			printf("   ");
			if(canSk){
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}else{
				color(8);
				printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"NO SKILL":atter->ct2[0].c_str());
			}
		}
		color(7);
		char key=getch();
		if(key=='w'||key=='W'){choice=0;}
		else if(key=='s'||key=='S'){choice=1;}
		else if(key==13){
			if(choice==0){return {0,atter};}
			if(choice==1&&canSk){return {1,atter};}
		}
	}
}

// 执行攻击
static void attExe(stud* atter,stud* tar,stuV& team,stuV&enemy,const actCho& action,int& cntAlive){
	gotoxy(0,23);
	if(action.useSk){
		color(11);
		printf("[SKILL] %s uses %s!",atter->name.c_str(),atter->ct2[0].c_str());
	}else{
		color(10);
		printf("[ATTACK] %s attacks %s!",atter->name.c_str(),tar->name.c_str());
	}
	color(7);
	// 转换为 void* 调用原函数
	voiV vTeam,vEnemy;
	for(auto*p:team){vTeam.push_back(p);}
	for(auto*p:enemy){vEnemy.push_back(p);}
	if(action.useSk){
		sk_hitt(atter,tar,vTeam,vEnemy);
	}else{
		hitt(atter,tar,vTeam,vEnemy);
	}
	if(tar->status==0){
		gotoxy(0,24);
		color(12);
		printf("[DEATH] %s has fallen!",tar->name.c_str());
		color(7);
		cntAlive--;
		gotoxy(0,25);
		printf("Press any key to continue...");
		getch();
	}else{
		gotoxy(0,25);
		color(14);
		printf("Press any key to continue...");
		getch();
	}
	clear_action_area();
}

// 队伍是否有可行动人员
static bool canAct(stuV&team){
	for(auto*s:team){
		if(s&&isalive[s->id]&&s->status!=-1&&s->red>=0){return 1;}
	}
	return 0;
}

// 主战斗函数
static void turn(int rounds,voiV lA,voiV lB,bool isL){
	stuV teamA,teamB;
	for(auto*p:lA){
		if(p){teamA.push_back((stud*)p);}
	}
	for(auto*p:lB){
		if(p){teamB.push_back((stud*)p);}
	}
	int tchID=sbj_teacher;
	for(int r=0;r<rounds;r++){
		// 疯人状态检查
		checkIN(teamA);
		checkIN(teamB);
		// 回合开始
		startTurn(teamA,teamB,tchID);
		// 检查疯人解除
		checkCL(teamA);
		checkCL(teamB);
		// 检查战斗是否结束
		if(endBattle(teamA,teamB)){break;}
		// 刷新界面
		system("cls");
		color(14);
		printf("+========================================================+\n");
		printf("|                      ROUND %-2d                          |\n",r+1);
		printf("+========================================================+\n");
		color(7);
		sett(lA,lB,isL?5:3);
		// ===== Team A 回合 =====
		if(canAct(teamA)){
			int startL=20;
			stud* atter=selAtt(teamA,"Team A",startL);
			if(atter){
				int tarLine=isL?startL+teamA.size()-5:startL+teamA.size()-3;
				stud* tar=selTar(atter,teamB,"Team A",tarLine);
				if(tar){
					actCho action=selAct(atter,"Team A");
					attExe(atter,tar,teamA,teamB,action,Bnum);
				}
			}
		}
		// 检查战斗是否结束
		if(endBattle(teamA,teamB)){break;}
		// 刷新界面（Team B回合）
		system("cls");
		color(14);
		printf("+========================================================+\n");
		printf("|                      ROUND %-2d                          |\n",r+1);
		printf("+========================================================+\n");
		color(7);
		sett(lA,lB,isL?5:3);
		// ===== Team B 回合 =====
		if(canAct(teamB)){
			int startL=20;
			stud* atter=selAtt(teamB,"Team B",startL);
			if(atter){
				int tarLine=isL?startL+teamB.size()-5:startL+teamB.size()-3;
				stud* tar=selTar(atter,teamA,"Team B",tarLine);
				if(tar){
					actCho action=selAct(atter,"Team B");
					attExe(atter,tar,teamB,teamA,action,Anum);
				}
			}
		}
		// 回合结束
		endTurn(teamA,teamB,tchID);
	}
	// 战斗结束，显示结果
	system("cls");
	sett(lA,lB,3);
	color(7);
}

#endif// __TURN_H__