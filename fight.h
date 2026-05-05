#ifndef __FIGHT_H__
#define __FIGHT_H__

/*
 * fight.h - 战斗系统
 * 包含: hitt sk_hitt checkIN checkCL startTurn endTurn
 *       endBattle selAtt selTar selAct attExe canAct
 *       turn fight CVS_game CVS_main
 */

// ========== 普通攻击 ==========
void hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return;}
	stud*ta=(stud*)f1;
	stud*tb=(stud*)f2;

	if(debug_on){
		logPrint(10,"[ATTACK] %s",ta->name.c_str());
		logPrint(7," -> ");
		logPrint(9,"%s\n",tb->name.c_str());
	}

	vector<stud*>t1,t2;
	for(auto y:T1){
		if(y!=NULL){t1.push_back((stud*)y);}
	}
	for(auto y:T2){
		if(y!=NULL){t2.push_back((stud*)y);}
	}
	int sit1=(*ta).before_att(tb,sbj_teacher,t1,t2);
	int sit2=(*tb).on_before_be_atted(ta,sbj_teacher,t2,t1);

	if(sit1==1||sit2==1){
		if(debug_on){logPrint(12,"  -> Attack cancelled!\n");}
		return;
	}

	// 最终攻击 - 使用新版 getter
	int final_att=ta->get_att()*tb->get_be_att_mul();
	if(ta->id==5&&final_att>30){unlockChallenge(2);}

	if(debug_on){
		logPrint(7,"  Damage Calculation:\n");
		logPrint(7,"    Base Attack: %d\n",(*ta).att);
		logPrint(7,"    Attacker Multiplier: %.2f",(*ta).get_att_mul());
		if(ta->is_crazy){logPrint(12," (INSANE x1.5)");}
		logPrint(7,"\n");
		logPrint(7,"    Target Defense Multiplier: %.2f\n",(*tb).get_be_att_mul());
		logPrint(7,"    Temporary Attack Bonus: +%d\n",(*ta).get_tmp_att_plus());
		logPrint(7,"    Raw Damage: %d\n",final_att);
	}

	if(sit1==5||sit2==5){
		int old_final=final_att;
		final_att*=0.3;
		logPrint(12,"    Damage reduced 70%.\n");
	}else if(sit1!=2&&sit2!=2){
		int old_final=final_att,damCap=30;
		if(ta->id==9&&((stud_A9*)ta)->firstTurnA9){damCap=40;}
		if(sit1==4||sit2==4){damCap=18;}
		if(sit1==3||sit2==3){damCap=10;}
		final_att=min(final_att,damCap);
		if(debug_on&&old_final>damCap){logPrint(12,"    Damage capped to %d.\n",damCap);}
	}
	if(debug_on){logPrint(10,"    Final Damage: %d\n",final_att);}

	// 政治全局伤害倍率
	final_att=final_att*global_damage_mult;

	// 物理课标记攻击
	if(physics_marked!=NULL&&ta==physics_marked&&isalive[physics_marked->id]){
		vector<stud*>all;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){all.push_back(s);}
		}
		if(!all.empty()){
			int idx=rand()%all.size();
			stud* victim=all[idx];
			int shareDamage=final_att*0.2;
			victim->cred(-shareDamage);
			if(debug_on){logPrint(12,"[Physics Class] Marked %s attacks! %s takes 20%% (%d) damage.\n",
ta->name.c_str(),victim->name.c_str(),shareDamage);}
		}
	}
	// 物理课标记受击
	if(physics_marked!=NULL&&tb==physics_marked&&isalive[physics_marked->id]){
		vector<stud*>all;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){all.push_back(s);}
		}
		if(!all.empty()){
			int idx=rand()%all.size();
			stud* healer=all[idx];
			int healAmount=final_att*0.2;
			healer->cred(healAmount);
			if(debug_on){logPrint(10,"[Physics Class] Marked %s is attacked! %s heals 20%% (%d) HP.\n",
tb->name.c_str(),healer->name.c_str(),healAmount);}
		}
	}

	// 英语B替罪羊
	if(scapegoat!=NULL&&isalive[scapegoat->id]){
		if(debug_on){logPrint(12,"[English B] Scapegoat %s takes damage instead of %s\n",
scapegoat->name.c_str(),tb->name.c_str());}
		scapegoat->cred(-final_att);
		return;
	}

	// 语文课卡片
	if(ta->chinese_double!=0){final_att+=3;}
	if(tb->chinese_forgive!=0){
		int fr=rand()%100;
		if(fr<20){
			if(debug_on){logPrint(12,"[Chinese Class] Forgive Card: Attack nullified!\n");}
			return;
		}
		else if(fr<70){
			final_att=final_att*0.6;
			if(debug_on){logPrint(12,"[Chinese Class] Forgive Card: Damage reduced to 60%%\n");}
		}
	}
	if(ta->chinese_pass!=0){
		int passDamage=final_att*0.2;
		ta->cred(-passDamage);
		if(debug_on){logPrint(12,"[Chinese Class] Pass Card: Attacker takes 20%% (%d) self damage.\n",passDamage);}
	}

	int old_red=tb->red;
	(*tb).cred(final_att*-1);
	(*ta).cwhite(-5);
	if(tb->Bighuocar){
		int A7rand=rand()%5;
		if(A7rand==1){ta->cred(-final_att);}
	}
	if(debug_on){
		logPrint(7,"  Result:\n");
		logPrint(12,"    %s HP: %d -> %d ( -%d )\n",tb->name.c_str(),old_red,tb->red,final_att);
		logPrint(7,"  Stamina Cost:\n");
		logPrint(15,"    %s Stamina: %d -> %d ( -5 )\n",ta->name.c_str(),ta->white+5,ta->white);
	}

	(*ta).after_att(tb,sbj_teacher,t1,t2);
	(*tb).on_minus_red(ta,sbj_teacher,t2,t1);

	if((*tb).status==0){
		isalive[(*tb).id]=0;
		checkProgress(3);  // 首次击杀成就
		if(debug_on){logPrint(12,"  [DEATH] %s has been killed!\n",tb->name.c_str());}

		for(auto*s:t1){
			if(s&&s->id==28){((stud_B15*)s)->on_enemy_death(t1);}
		}
	}
	if(debug_on){logPrint(7,"\n");}
}

// ========== 主动技能 ==========
void sk_hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return;}
	vector<stud*>t1,t2;
	for(auto y:T1){
		if(y!=NULL){t1.push_back((stud*)y);}
	}
	for(auto y:T2){
		if(y!=NULL){t2.push_back((stud*)y);}
	}
	((stud*)f1)->skhit((stud*)f2,sbj_teacher,t1,t2);
	return;
}

// ========== 状态检查 ==========
static void checkIN(stuV&team){
	for(auto*s:team){
		if(s&&s->blue<0&&!s->is_crazy){
			s->is_crazy=1;
			// 使用 vector push_back 添加疯人乘区
			s->att_mul.push_back({1.5, 0x7f7f7f7f});
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

static void checkCL(stuV&team){
	for(auto*s:team){
		if(s&&s->blue>=0&&s->is_crazy){
			s->is_crazy=0;
			// 移除疯人乘区
			for(int i=0;i<s->att_mul.size();i++){
				if(s->att_mul[i].first==1.5){
					s->att_mul.erase(s->att_mul.begin()+i);
					break;
				}
			}
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

// ========== 回合开始/结束 ==========
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

static void endTurn(stuV&teamA,stuV&teamB,int tchID){
	for(auto*s:teamA){
		if(s){s->on_turn_end(0,tchID,teamA,teamB);}
	}
	for(auto*s:teamB){
		if(s){s->on_turn_end(0,tchID,teamB,teamA);}
	}
}

// ========== 战斗结束检查 ==========
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
		for(auto*x:listA){
			stud* s=(stud*)x;
			if(s&&isalive[s->id]&&s->red>=0){Anum++;}
		}
		for(auto*x:listB){
			stud* s=(stud*)x;
			if(s&&isalive[s->id]&&s->red>=0){Bnum++;}
		}
		return 1;
	}
	return 0;
}

// ========== 选择攻击方 ==========
static stud*selAtt(stuV&team,const string&teamN,int startL){
	int size=team.size();
	int attIdx=0;
	// 增加 can_act 检查
	while(attIdx<size&&(!team[attIdx]||!isalive[team[attIdx]->id]||
		team[attIdx]->status==-1||team[attIdx]->red<0||!team[attIdx]->can_act)){attIdx++;}
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
			printf("   %s (DEAD)                    \n",s->name.c_str());
			color(7);
			continue;
		}
		if(i==attIdx){
			color(14);
			printf("-> ");
		}else{printf("   ");}
		if(s->status==-1){
			color(8);
			printf("%s (EXHAUSTED)                    \n",s->name.c_str());
		}else if(s->is_crazy){
			color(12);
			printf("%s (ATT:%02d)                    \n",s->name.c_str(),s->get_att());
		}else{
			color(teamN=="Team A"?10:9);
			if(s->espp){color(95);}
			printf("%s (ATT:%02d)",s->name.c_str(),s->get_att());
			color(7);
			printf("                    \n");
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

// ========== 选择受击方 ==========
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
	printf("%s - Select your target (W/S keys, Enter to confirm):\n",teamN.c_str());
	for(int i=0;i<size;i++){
		if(!defer[i]){continue;}
		stud*s=defer[i];
		gotoxy(0,startL+i);
		if(!isalive[s->id]||s->red<0){
			color(8);
			printf("   %s (DEAD)                    \n",s->name.c_str());
			color(7);
			continue;
		}
		if(i==tarIdx){
			color(14);
			printf("-> ");
		}else{printf("   ");}
		if(s->status==-1){
			color(8);
			printf("%s (EXHAUSTED)                    \n",s->name.c_str());
		}else if(s->is_crazy){
			color(12);
			printf("%s (ATT:%02d)                    \n",s->name.c_str(),s->get_att());
		}else{
			color(teamN=="Team A"?9:10);
			if(s->espp){color(95);}
			printf("%s (ATT:%02d)",s->name.c_str(),s->get_att());
			color(7);
			printf("                    \n");
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

// ========== 选择行动类型 ==========
static actCho selAct(stud* atter,const string& teamN){
	bool canSk=(atter->white>0&&!atter->ct2.empty()),staeno=1,notused=1,skilled=1;
	if(atter->id==12&&((stud_A12*)atter)->ega_used){canSk=notused=0;}
	if(atter->id==13){canSk=staeno=(atter->white>=atter->white_up*0.7);}
	if(atter->id==21&&((stud_B8*)atter)->fight_active){canSk=notused=0;}
	if(atter->id==22){
		stud_B9*b9=(stud_B9*)atter;
		if(!atter->white<10){canSk=staeno=0;}
		if(!b9->can_use_this_day(day)){canSk=notused=0;}
	}
	if(atter->id==24&&((stud_B11*)atter)->guest_turnsLeft>0){canSk=staeno=0;}
	if(atter->id==25&&((stud_B12*)atter)->shake_active){canSk=staeno=0;}
	if(atter->id==26){canSk=staeno=(atter->white>=20);}
	canSk&=(*atter).HavCt[0];
	skilled&=(*atter).HavCt[0];
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
			if(!canSk){
				color(8);
				if(!skilled){printf("SKILL: %s [Unskilled]",atter->ct2[0].c_str());}
				else if(!notused){printf("SKILL: %s [Used]",atter->ct2[0].c_str());}
				else{printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"NO SKILL":atter->ct2[0].c_str());}
			}else{
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}
		}else{
			printf("   ");
			if(!canSk){
				color(8);
				if(!skilled){printf("SKILL: %s [Unskilled]",atter->ct2[0].c_str());}
				else if(!notused){printf("SKILL: %s [Used]",atter->ct2[0].c_str());}
				else{printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"NO SKILL":atter->ct2[0].c_str());}
			}else{
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}
		}
		color(7);
		char key=getch();
		if(key=='w'||key=='W'){choice=0;}
		else if(key=='s'||key=='S'){choice=1;}
		else if(key==13){
			if(choice==0){return{0,atter};}
			if(choice==1&&canSk){return{1,atter};}
		}
	}
}

// ========== 执行攻击 ==========
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

// ========== 队伍是否有可行动人员 ==========
static bool canAct(stuV&team){
	for(auto*s:team){
		if(s&&isalive[s->id]&&s->status!=-1&&s->red>=0&&s->can_act){return 1;}
	}
	return 0;
}

// ========== 主战斗循环 ==========
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
		checkIN(teamA);
		checkIN(teamB);
		startTurn(teamA,teamB,tchID);
		checkCL(teamA);
		checkCL(teamB);
		if(endBattle(teamA,teamB)){break;}
		
		system("cls");
		color(14);
		printf("+========================================================+\n");
		printf("|                      ROUND %-2d                          |\n",r+1);
		printf("+========================================================+\n");
		color(7);
		sett(lA,lB,isL?5:3);
		
		// Team A 回合
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
		if(endBattle(teamA,teamB)){break;}
		
		system("cls");
		color(14);
		printf("+========================================================+\n");
		printf("|                      ROUND %-2d                          |\n",r+1);
		printf("+========================================================+\n");
		color(7);
		sett(lA,lB,isL?5:3);
		
		// Team B 回合
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
		endTurn(teamA,teamB,tchID);
	}
	system("cls");
	sett(lA,lB,3);
	color(7);
}

// ========== fight 函数 ==========
void fight(int day,int cla){
	if(day==5&&cla>=7)return;
	if(cla==8){
		system("cls");
		color(11);
		printf("+-----------------------------------------------------------+\n");
		printf("|                  LATE SELF-STUDY HOUR                     |\n");
		printf("|               8 ROUNDS OF INTENSE BATTLE!                 |\n");
		printf("|              EVERY STUDENT NEEDS TO FIGHT!                |\n");
		printf("+-----------------------------------------------------------+\n");
		color(7);
		sett(listA,listB,5);
		printf("Press any key to continue...");
		getch();
		turn(8,listA,listB,1);
		return;
	}

	system("cls");
	color(11);
	printf("\n+-----------------------------------------------------------+\n");
	printf("|  Class: %s%*s|\n", subj2[classtable[day][cla]].c_str(), 50 - (int)subj2[classtable[day][cla]].length(), " ");
	printf("|  Subject bonus active! Students with matching attributes  |\n");
	printf("|  gain +50%% attack power!                                  |\n");
	printf("+-----------------------------------------------------------+\n");
	color(7);
	sett(listA, listB, 5);
	checkProgress(2);

	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL){continue;}
		tmp=(stud*)stud_list[i];
		if(tmp->id==26){((stud_B13*)tmp)->on_class_start(classtable[day][cla]);}
	}

	for (int i = 0; i < stud_list.size(); i++){
		if (stud_list[i] == NULL) continue;
		tmp = (stud * )(stud_list[i]);
		for (int j : (*tmp).py) if (j == classtable[day][cla]){
			(*tmp).att_mul.push_back({1.5, 3});
		}
	}

	vector<void*> lA, lB;
	bool isc1[6] = {0}, isc2[6] = {0};
	int current_pos_A = 0, current_pos_B = 0;

	while (current_pos_A < 5 && listA[current_pos_A] == NULL) current_pos_A++;
	while (current_pos_B < 5 && listB[current_pos_B] == NULL) current_pos_B++;

	int a_start_line = 23;
	int b_start_line = a_start_line;

	// Team A 选择
	bool a_selection_valid=false,a_chosen=false;
	while(!a_selection_valid){
		lA.clear();
		memset(isc1, 0, sizeof(isc1));
		current_pos_A = 0;
		while(current_pos_A < 5 && listA[current_pos_A] == NULL) current_pos_A++;
		
		gotoxy(0, 21);
		color(14);
		if(!a_chosen){
			printf("\nTeam A - Select 3 students for battle (W/S to move, Enter to select):\n");
			a_chosen=1;
		}else{printf("\nTeam A - Invalid choice, please select again:                         \n");}
		color(7);
		
		for (int i = 0; i < 5; i++){
			if (listA[i] == NULL){
				printf("\n");
				continue;
			}
			stud y = (*(stud * )listA[i]);
			
			if (i == current_pos_A){
				color(14);
				printf("-> ");
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)                 \n",i+1,y.name.c_str());
				}else{
					color(10);
					if(y.espp){color(95);}
					printf("%s (ATT:%02d)",y.name.c_str(),y.get_att());
					color(7);
					printf("                    \n");
				}
				color(7);
			}
			else {
				printf("   ");
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)                 \n",i+1,y.name.c_str());
				}else{
					color(10);
					if(y.espp){color(95);}
					printf("%s (ATT:%02d)",y.name.c_str(),y.get_att());
					color(7);
					printf("                    \n");
				}
				color(7);
			}
		}
		
		while(lA.size() < 3){
			char key = getch();
			if(key == 'w' || key == 'W'){
				gotoxy(0, a_start_line + current_pos_A);
				printf("   ");
				current_pos_A--;
				if(current_pos_A < 0) current_pos_A = 4;
				while(listA[current_pos_A] == NULL){
					current_pos_A--;
					if(current_pos_A < 0) current_pos_A = 4;
				}
				gotoxy(0, a_start_line + current_pos_A);
				color(14);
				printf("->");
				color(7);
			}
			else if(key == 's' || key == 'S'){
				gotoxy(0, a_start_line + current_pos_A);
				printf("   ");
				current_pos_A++;
				if(current_pos_A >= 5) current_pos_A = 0;
				while(listA[current_pos_A] == NULL){
					current_pos_A++;
					if(current_pos_A >= 5) current_pos_A = 0;
				}
				gotoxy(0, a_start_line + current_pos_A);
				color(14);
				printf("->");
				color(7);
			}
			else if(key == 13){
				if(!isc1[current_pos_A] && listA[current_pos_A] != NULL){
					lA.push_back(listA[current_pos_A]);
					isc1[current_pos_A] = true;
					
					gotoxy(3, a_start_line + current_pos_A);
					color(8);
					stud y = (*(stud * )listA[current_pos_A]);
					printf("%s (ATT:%02d) [SELECTED]\n",y.name.c_str(),y.get_att());
					color(7);
					gotoxy(0, a_start_line + current_pos_A);
					printf("   ");
					
					int next = current_pos_A + 1;
					while(next < 5 && (isc1[next] || listA[next] == NULL)) next++;
					if(next >= 5){
						next = 0;
						while(next < 5 && (isc1[next] || listA[next] == NULL)) next++;
					}
					if(next < 5 && !isc1[next]){
						current_pos_A = next;
						gotoxy(0, a_start_line + current_pos_A);
						color(14);
						printf("->");
						color(7);
					}
				}
			}
		}
		
		bool all_dead = true;
		for(auto x : lA){
			stud* s = (stud*)x;
			if(s->id==26&&((stud_B13*)s)->isAway()){continue;}
			if(isalive[s->id] && s->red >= 0){
				all_dead = false;
				break;
			}
		}
		
		if(all_dead){
			a_selection_valid = false;
			for(int i = 0; i < 10; i++){
				gotoxy(0, a_start_line + i);
				for(int j = 0; j < 80; j++) printf(" ");
			}
		} else {
			a_selection_valid = true;
		}
	}

	// Team B 选择
	bool b_selection_valid=false,b_chosen=false;
	while(!b_selection_valid){
		lB.clear();
		memset(isc2, 0, sizeof(isc2));
		current_pos_B = 0;
		while(current_pos_B < 5 && listB[current_pos_B] == NULL) current_pos_B++;
		
		gotoxy(0, 21);
		color(14);
		if(!b_chosen){
			printf("\nTeam B - Select 3 students for battle (W/S to move, Enter to select):\n");
			b_chosen=1;
		}else{printf("\nTeam B - Invalid choice, please select again:                         \n");}
		color(7);
		
		for (int i = 0; i < 5; i++){
			if (listB[i] == NULL){
				printf("\n");
				continue;
			}
			stud y = (*(stud * )listB[i]);
			
			if (i == current_pos_B){
				color(14);
				printf("-> ");
				color(9);
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)                 \n",i+1,y.name.c_str());
				}else{
					color(9);
					if(y.espp){color(95);}
					printf("%s (ATT:%02d)",y.name.c_str(),y.get_att());
					color(7);
					printf("                    \n");
				}
				color(7);
			}
			else {
				printf("   ");
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)                 \n",i+1,y.name.c_str());
				}else{
					color(9);
					if(y.espp){color(95);}
					printf("%s (ATT:%02d)",y.name.c_str(),y.get_att());
					color(7);
					printf("                    \n");
				}
				color(7);
			}
		}
		
		while(lB.size() < 3){
			char key = getch();
			if(key == 'w' || key == 'W'){
				gotoxy(0, b_start_line + current_pos_B);
				printf("   ");
				current_pos_B--;
				if(current_pos_B < 0) current_pos_B = 4;
				while(listB[current_pos_B] == NULL){
					current_pos_B--;
					if(current_pos_B < 0) current_pos_B = 4;
				}
				gotoxy(0, b_start_line + current_pos_B);
				color(14);
				printf("->");
				color(7);
			}
			else if(key == 's' || key == 'S'){
				gotoxy(0, b_start_line + current_pos_B);
				printf("   ");
				current_pos_B++;
				if(current_pos_B >= 5) current_pos_B = 0;
				while(listB[current_pos_B] == NULL){
					current_pos_B++;
					if(current_pos_B >= 5) current_pos_B = 0;
				}
				gotoxy(0, b_start_line + current_pos_B);
				color(14);
				printf("->");
				color(7);
			}
			else if(key == 13){
				if(!isc2[current_pos_B] && listB[current_pos_B] != NULL){
					lB.push_back(listB[current_pos_B]);
					isc2[current_pos_B] = true;
					
					gotoxy(3, b_start_line + current_pos_B);
					color(8);
					stud y = (*(stud * )listB[current_pos_B]);
					printf("%s (ATT:%02d) [SELECTED]\n",y.name.c_str(),y.get_att());
					color(7);
					gotoxy(0, b_start_line + current_pos_B);
					printf("   ");
					
					int next = current_pos_B + 1;
					while(next < 5 && (isc2[next] || listB[next] == NULL)) next++;
					if(next >= 5){
						next = 0;
						while(next < 5 && (isc2[next] || listB[next] == NULL)) next++;
					}
					if(next < 5 && !isc2[next]){
						current_pos_B = next;
						gotoxy(0, b_start_line + current_pos_B);
						color(14);
						printf("->");
						color(7);
					}
				}
			}
		}
		
		bool all_dead = true;
		for(auto x : lB){
			stud* s = (stud*)x;
			if(s->id==26&&((stud_B13*)s)->isAway()){continue;}
			if(isalive[s->id] && s->red >= 0){
				all_dead = false;
				break;
			}
		}
		
		if(all_dead){
			b_selection_valid = false;
			for(int i = 0; i < 10; i++){
				gotoxy(0, b_start_line + i);
				for(int j = 0; j < 80; j++) printf(" ");
			}
		} else {
			b_selection_valid = true;
		}
	}

	color(7);

	gotoxy(0, 22);
	color(10);
	printf("Team A selected: ");
	for (auto x : lA){
		stud y = (*(stud * )x);
		printf("%s ", y.name.c_str());
	}
	color(7);
	printf("                                              \n");

	color(9);
	printf("Team B selected: ");
	for (auto x : lB){
		stud y = (*(stud * )x);
		printf("%s ", y.name.c_str());
	}
	color(7);
	printf("                             \n                             \n");

	printf("Press any key to start the battle...                ");
	printf("\n                                                  ");
	printf("\n                                                  ");
	getch();

	// 学科开始效果
	applySubjectStart(classtable[day][cla]);
	checkListenStart(classtable[day][cla]);
	
	// ICT 特殊事件
	if(classtable[day][cla]==9){
		if(rand()%1000<1){
			if(debug_on){logPrint(7,"[ICT Class] OIer's game triggered! (0.1%%)\n");}
			
			int specialIds[]={1,26,3,9,12};
			int teamACount=0,teamBCount=0;
			
			for(auto x:lA){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				for(int id:specialIds){
					if(s->id==id){
						teamACount++;
						if(debug_on){logPrint(7,"[ICT Class] Team A OIer: %s\n",s->name.c_str());}
						break;
					}
				}
			}
			for(auto x:lB){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				for(int id:specialIds){
					if(s->id==id){
						teamBCount++;
						if(debug_on){logPrint(7,"[ICT Class] Team B OIer: %s\n",s->name.c_str());}
						break;
					}
				}
			}
			
			if(debug_on){logPrint(7,"[ICT Class] OIer counts: Team A = %d, Team B = %d\n",teamACount,teamBCount);}
			
			if(teamACount>teamBCount){
				if(debug_on){logPrint(12,"[ICT Class] Team A wins! Team B destroyed.\n");}
				for(auto x:lB){if(x!=NULL){((stud*)x)->cred(-9999);}}
			}else if(teamBCount>teamACount){
				if(debug_on){logPrint(12,"[ICT Class] Team B wins! Team A destroyed.\n");}
				for(auto x:lA){if(x!=NULL){((stud*)x)->cred(-9999);}}
			}else if(teamACount>0&&teamBCount>0&&teamACount==teamBCount){
				if(debug_on){logPrint(12,"[ICT Class] Draw! Both teams destroyed.\n");}
				for(auto x:lA){if(x!=NULL){((stud*)x)->cred(-9999);}}
				for(auto x:lB){if(x!=NULL){((stud*)x)->cred(-9999);}}
				unlockChallenge(7);
			}
		}
	}

	turn(3,lA,lB,0);

	// 检查残血/满血通关成就
	bool allLow=1,allFull=1;

	for(auto x:lA){
		stud* s=(stud*)x;
		if(isalive[s->id]&&s->red>=0){
			double ratio=(double)s->red/s->red_up;
			if(ratio>0.2){allLow=0;}
			if(s->red<s->red_up){allFull=0;}
		}
	}
	for(auto x:lB){
		stud* s=(stud*)x;
		if(isalive[s->id]&&s->red>=0){
			double ratio=(double)s->red/s->red_up;
			if(ratio>0.2){allLow=0;}
			if(s->red<s->red_up){allFull=0;}
		}
	}

	if(allLow){checkProgress(7);}
	if(allFull){checkProgress(8);}

	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL) continue;
		tmp=(stud*)stud_list[i];
		if(tmp->id==28){((stud_B15*)tmp)->on_class_end();}
	}

	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i] == NULL){continue;}
		tmp=(stud*)stud_list[i];
		tmp->on_fight_end();
	}
}


// ========== CVS_game 主游戏循环 ==========
void CVS_game(){
	system("cls");
	init();
	team_chs();

	// 应用全疯设置
	if(settings.auto_insane){
		for(auto x:stud_list){
			if(x!=NULL){
				((stud*)x)->blue=-1;
				if(!((stud*)x)->is_crazy){
					((stud*)x)->is_crazy=true;
					((stud*)x)->att_mul.push_back({1.5, 0x7f7f7f7f});
				}
			}
		}
		color(12);
		printf("\n[SETTINGS] Auto Insane Mode enabled!\n");
		color(7);
		printf("Press any key to continue...");
		getch();
	}
	if(!settings.Ct_Need_Chose){
		for(auto x:stud_list){
			if(x!=NULL){
				for(int i=0;i<3;i++)
				((stud*)x)->HavCt[i]=1;
			}
		}
	}

	for(day=1;day<=5;day++){
		for(int i=0;i<stud_list.size();i++){
			if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
			tmp=(stud*)stud_list[i];
			if(tmp->id==26){
				((stud_B13*)tmp)->resetDaily();
				((stud_B13*)tmp)->on_day_start();
			}
		}

		for(clas=1;clas<=8;clas++){
			if(Anum<=0||Bnum<=0){continue;}
			if(clas==5||clas==8){
				for(int i=0;i<stud_list.size();i++){
					if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
					tmp=(stud*)(stud_list[i]);
					(*tmp).cwhite(20);
				}
				color(10);
				printf("\n[MEAL] Meal time! +20 stamina restored!\n");
				color(7);
			}
			for(int i=0;i<stud_list.size();i++){
				if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
				tmp=(stud*)(stud_list[i]);
				(*tmp).cblue(5);
			}
			fight(day,clas);
			if(clas==2||clas==5||clas==7)Lets_Choose_Ct(listA,listB,1);
			else if(clas==8)Lets_Choose_Ct(listA,listB,2);
		}
		for(int i=0;i<stud_list.size();i++){
			if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
			tmp=(stud*)(stud_list[i]);
			(*tmp).white=(*tmp).white_up;
			(*tmp).cblue(20);

			if((*tmp).red<0.2*(*tmp).red_up){(*tmp).red=0.2*(*tmp).red_up;}
			else{(*tmp).cred(20);}
		}
		color(7);
	}

	if(settings.auto_insane&&(Anum<=0||Bnum<=0)){unlockChallenge(1);}

	system("cls");
	color(14);
	printf("\n+========================================================+\n");
	if((Anum<=0&&Bnum<=0)||(Anum>0&&Bnum>0)){printf("|                        DRAW GAME!                      |\n");}
	else if(Anum<=0){printf("|                     TEAM B VICTORY!                    |\n");}
	else if(Bnum<=0){printf("|                     TEAM A VICTORY!                    |\n");}
	printf("+========================================================+\n\nPress any key to continue...");
	color(7);
	getch();
}

// ========== CVS_main 主菜单 ==========
void CVS_main(){
	srand(time(nullptr)*rand());

	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole,&cursorInfo);
	cursorInfo.bVisible=0;
	SetConsoleCursorInfo(hConsole,&cursorInfo);
	setConsoleSize(80,33);

    loadSettings();
    if(settings.debug_log) {
        debug_on=1;
        createLogWindow();
    }
	loadAch();
	
start:
	reset();

	color(7);
	system("cls");
	color(11);
	printf("\
+------------------------+\n\
|   Class vs. Students   |\n\
|           v0.3 rc-4.3  |\n\
+------------------------+\n");
	color(7);
	printf("\
|       Start Game       |\n\
|        Guidance        |\n\
|      Achievements      |\n\
|       Our Github       |\n\
|        Settings        |\n\
|          Exit          |\n");
	color(11);
	printf("+------------------------+\n\n\n");
	if(!timeOfStarting){sslp(0.3);}
	timeOfStarting=1;

	if(!settings.hide_tips){
		randomTip();
		showTip();
	}

	color(14);
	gotoxy(0,nowy);
	printf("| ->");
	char cstart=getch();
	while(cstart!='\r'&&cstart!='\n'){
		gotoxy(0,nowy);
		color(7);
		printf("|   ");
		if(nowy>4&&(cstart=='w'||cstart=='W')){nowy--;}
		else if(nowy<9&&(cstart=='s'||cstart=='S')){nowy++;}
		color(14);
		gotoxy(0,nowy);
		printf("| ->");
		cstart=getch();
	}
	if(nowy==5){
		guide();
		goto start;
	}
	else if(nowy==6){
		achievementMenu();
		goto start;
	}
	else if(nowy==7){
		system("start https://github.com/cso666/Class-vs-Students");
		goto start;
	}
    else if(nowy==8){
        settingsMenu();
        goto start;
    }
	else if(nowy==9){
		gotoxy(11,9);
		ppput("BYE!",0.2);
		gotoxy(0,14);

		color(7);
		cursorInfo.bVisible=1;
		SetConsoleCursorInfo(hConsole,&cursorInfo);
		closeLogWindow();
		return;
	}

	system("cls");

	color(11);
	printf("\
+------------------------+\n\
|     Are you ready?     |\n\
+------------------------+\n");
	color(7);
	printf("\
|    YES, Let's go!!!    |\n\
|           NO           |\n");
	color(11);
	printf("+------------------------+");
	sslp(0.3);
	gotoxy(0,3);
	color(14);
	printf("| ->");
	color(7);
	char cnextt=getch();bool starttttt=0;
	while(cnextt!='\r'&&cnextt!='\n'){
		if(starttttt==1&&(cnextt=='w'||cnextt=='W')){
			gotoxy(0,4);
			color(7);
			printf("|   ");
			gotoxy(0,3);
			color(14);
			printf("| ->");
			starttttt=0;
			color(7);
		}
		else if(starttttt==0&&(cnextt=='s'||cnextt=='S')){
			gotoxy(0,3);
			color(7);
			printf("|   ");
			gotoxy(0,4);
			color(14);
			printf("| ->");
			starttttt=1;
			color(7);
		}
		cnextt=getch();
	}
	if(starttttt){
		color(7);
		gotoxy(0,3);
		printf("|                        |\n|                        |");
		gotoxy(5,3);
		ppput("It seems you're ",0.05);
		gotoxy(6,4);
		ppput("not ready yet.",0.05);
		sslp(0.4);
		system("cls");
		goto start;
		return;
	}
	color(7);
	gotoxy(0,3);
	printf("|                        |\n|                        |");
	gotoxy(10,3);
	ppput("READY?",0.2);
	sslp(1);
	system("cls");
	gotoxy(11,3);
	printf("GO!!");
	sslp(1.5);
    
	CVS_game();
    goto start;
}

#endif// __FIGHT_H__
