#ifndef __FIGHT_H__
#define __FIGHT_H__
#define __FIGHT_H_ver__ 18
extern void clear_action_area();

int hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return 0;}
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
	Return_Hit sit1=(*ta).before_att(tb,sbj_teacher,t1,t2);
	Return_BeHit sit2=(*tb).on_before_be_atted(ta,sbj_teacher,t2,t1);

	if(sit1.onf[2]==1){
		if((rand()%100)*1.0/100<=sit1.opp_cace){
		if(debug_on){logPrint(12,"  -> Attack cancelled!\n");}
		return 0;	
		}
	}
	if(sit2.onf[2]==1){
		if((rand()%100)*1.0/100<=sit2.opp_cace){
		if(debug_on){logPrint(12,"  -> Attack cancelled!\n");}
		return 0;	
		}
	}


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

	if(1){
		int old_final=final_att,damCap=30;
		if(ta->id==9&&((stud_A9*)ta)->firstTurnA9){damCap=40;}
		
		if(sit1.onf[1]&&sit2.onf[1])damCap=min(sit1.lim_hurt,sit2.lim_hurt);
		else if(sit1.onf[1]&&!sit2.onf[1])damCap=sit1.lim_hurt;
		else if(!sit1.onf[1]&&sit2.onf[1])damCap=sit2.lim_hurt;
		
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
		return 0;
	}

	// 语文课卡片
	if(ta->chinese_double!=0){final_att+=3;}
	if(tb->chinese_forgive!=0){
		int fr=rand()%100;
		if(fr<20){
			if(debug_on){logPrint(12,"[Chinese Class] Forgive Card: Attack nullified!\n");}
			return 0;
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

	if(tb->def > 0){
		int abhit=min(tb->def,final_att);
		tb->def-=abhit;
		final_att=0;
		if(debug_on){
			logPrint(7,"  Shield Absorption:\n");
			logPrint(7,"    Target DEF: %d\n",tb->def+abhit);
			logPrint(7,"    Absorbed: %d\n",abhit);
			logPrint(7,"    Remaining Damage: 0\n");
		}
	}

	int old_red=tb->red;
	if(sit1.onf[4]){
		double PC=sit1.pc_takplac;
		stud* Fp=(stud*)sit1.takplacer;
		(*tb).cred(final_att*-1*(1.0-PC));
		(*Fp).cred(final_att*-1*PC);
		if(PC>=0.5)(*Fp).cred(final_att*-1*PC);
	}else if(sit2.onf[4]){
		double PC=sit2.pc_takplac;
		stud* Fp=(stud*)sit2.takplacer;
		(*tb).cred(final_att*-1*(1.0-PC));
		(*Fp).cred(final_att*-1*PC);
		if(PC>=0.5)(*Fp).cred(final_att*-1*PC);
	}else{(*tb).cred(final_att*-1);}
	
	if(sit1.onf[3]){
		double spd=sit1.pc_spread;
		for(auto y:T2){
			stud* x=(stud*)y;
			(*x).cred(final_att*spd*(-1));
		}
	}
	if(sit2.onf[3]){
		double spd=sit2.pc_spread;
		for(auto y:T2){
			stud* x=(stud*)y;
			(*x).cred(final_att*spd*(-1));
		}
	}
	(*ta).cwhite(-5);
	if(sit1.onf[5]){
		double bac=sit1.opp_back;
		(*ta).cred(final_att*bac*(-1));
		
	}
	if(sit2.onf[5]){
		double bac=sit2.opp_back;
		(*ta).cred(final_att*bac*(-1));
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

	return final_att;
}

void sk_hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return;}
	vector<stud*>t1,t2;
	for(auto y:T1){
		if(y!=NULL){t1.push_back((stud*)y);}
	}
	for(auto y:T2){
		if(y!=NULL){t2.push_back((stud*)y);}
	}
	stud* fighter=(stud*)f1;
	stud* target=(stud*)f2;
	Return_Hit sit1=(*fighter).before_att(target,sbj_teacher,t1,t2);
	Return_BeHit sit2=(*target).on_before_be_atted(fighter,sbj_teacher,t2,t1);
	((stud*)f1)->skhit((stud*)f2,sbj_teacher,t1,t2);
	(*fighter).after_att(target,sbj_teacher,t1,t2);
	(*target).on_minus_red(fighter,sbj_teacher,t2,t1);
	return;
}

int toge_fight(pair<int,int> WandC,pair<stud*,stud*>FandT,vector<stud*> team,vector<stud*>beside_team){
	int classs=WandC.second,withid=WandC.first;
	stud *fighter=FandT.first,*target=FandT.second;
	vector<int> links=link_check[withid];
	int mans=0;
	for(auto y:team)
		for(auto z:links)
			if((*y).id==z)mans++;
	if(mans<=1)return -1;	
	
	switch(withid){
		case 0://B7B8B11
			if(mans==2){
				int tot=0;
				for(auto y:beside_team){
					if((*y).id>13)(*y).att_mul.push_back({0,1}),(*y).blue_mul.push_back({1.25,3}),(*y).cwhite(-10);
					(*y).blue_mul.push_back({1.25,3});
					tot+=(*y).blue;
				}
				for(auto y:team){
					for(auto z:links){
						if((*y).id==z){
							(*y).blue+=tot/2*mans;
						}
					}
				}
				(*fighter).att-=1;
			}
			else if(mans==3){
				int tot=0;
				for(auto y:beside_team){
					if((*y).id>13)(*y).att_mul.push_back({-1,1}),(*y).blue_mul.push_back({1.5,3}),(*y).cwhite(-30);
					else (*y).att_mul.push_back({0.5,1});
					(*y).blue_mul.push_back({1.5,3});
					tot+=(*y).blue;
				}
				for(auto y:team){
					for(auto z:links){
						if((*y).id==z){
							(*y).blue+=tot*mans;
						}
					}
				}
				(*fighter).att-=1;
			}
			if(classs==4){
				for(auto y:team){
					if((*y).id>13)(*y).cwhite(-20);
				}
			}
			break;
		case 1://A12A13
			for(auto y:team)
				for(auto z:links)
					if((*y).id==z&&(*y).id!=(*fighter).id)(*fighter).tmp_att_plus.push_back({(*y).att,1});
			if(classs==2){
				for(auto y:team)
					for(auto z:links)
						if((*y).id==z){
							(*y).cred(10);
							(*y).cwhite(10);
							(*y).cblue(10);
						}
				(*fighter).cred(10);
				(*fighter).cwhite(10);
				(*fighter).cblue(10);
			}else{
				for(auto y:team)
					for(auto z:links)
						if((*y).id==z){
							(*y).cred(5);
							(*y).cwhite(5);
							(*y).cblue(5);
						}
				(*fighter).cred(5);
				(*fighter).cwhite(5);
				(*fighter).cblue(5);
			}
			break;
			
	}
	Return_Hit sit1=(*fighter).before_att(target,classs,team,beside_team);
	Return_BeHit sit2=(*target).on_before_be_atted(fighter,classs,beside_team,team);
	int final_att=fighter->get_att()*target->get_be_att_mul();
	if(withid==1)final_att=max(final_att,11);
	(*target).cred(final_att*-1);
	(*fighter).cwhite(-5);
	(*fighter).after_att(target,classs,team,beside_team);
	(*target).on_minus_red(fighter,classs,beside_team,team);
	
	return withid;
}

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

static void startTurn(stuV&teamA,stuV&teamB,int tchID){
	for(auto*s:teamA){
		if(s){s->on_turn_start(0,tchID,teamA,teamB);}
	}
	for(auto*s:teamB){
		if(s){s->on_turn_start(0,tchID,teamB,teamA);}
	}
	for(auto x:teamA){
		if((*x).id>100)continue;
		if((*x).HavCt[0]&&(*x).HavCt[1]&&(*x).HavCt[2])
			hav_full_cts[(*x).id]=1;
	}
	for(auto x:teamB){
		if((*x).id>100)continue;
		if((*x).HavCt[0]&&(*x).HavCt[1]&&(*x).HavCt[2])
			hav_full_cts[(*x).id]=1;
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
			printf("   %s (DEAD)                      \n",s->name.c_str());
			color(7);
			continue;
		}
        if(!s->can_act){
            color(8);
            printf("   %s (DISABLED)                  \n",s->name.c_str());
            color(7);
            continue;
        }
		if(i==attIdx){
			color(14);
			printf("-> ");
		}else{printf("   ");}
		if(s->status==-1){
			color(8);
			printf("%s (EXHAUSTED)                   \n",s->name.c_str());
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
            team[newIdx]->status==-1||team[newIdx]->red<0||!team[newIdx]->can_act));
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
            team[newIdx]->status==-1||team[newIdx]->red<0||!team[newIdx]->can_act));
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

static stud*selTar(stud* atter,stuV& defer,const string& teamN,int startL){
	int size=defer.size(),tarIdx=0;
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
		printf("%s - Select your target (W/S keys, Enter to confirm):\n",teamN.c_str());
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
		gotoxy(0,24);
		color(12);
		printf("[INSANE] %s is insane! tar selected randomly!",atter->name.c_str());
		color(7);
		sslp(1);
		clear_action_area();
		return allTar[randIdx];
	}
	// 正常选择
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

static actCho selAct(stud* atter, voiV& currentTeam){
	bool canSk=(atter->white>0&&!atter->ct2.empty()),staeno=1,notused=1,skilled=1;
	
	int myLinkId=-1;
	bool hasLinkPotential=0;
	
	for(int i=0;i<lc_cnt;i++){
		for(int id:link_check[i]){
			if(atter->id==id){
				myLinkId=i;
				break;
			}
		}
		if(myLinkId!=-1){break;}
	}
	hasLinkPotential=(myLinkId!=-1);
	
	bool allFull=0,allPresent=0,hasLink=0;
	
	if(hasLinkPotential){
		allFull=link_res[myLinkId];
		for(int id:link_check[myLinkId]){
			if(hav_full_cts[id]==0){
				allFull=0;
				break;
			}
		}
		
		allPresent=1;
		for(int id:link_check[myLinkId]){
			bool found=0;
			for(auto p:currentTeam){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==id){
					found=1;
					break;
				}
			}
			if(!found){
				allPresent=0;
				break;
			}
		}
		
		hasLink=(atter->WithP>=0);
	}
	
	if(atter->id==12&&((stud_A12*)atter)->ega_used){canSk=notused=0;}
	if(atter->id==13){canSk=staeno=(atter->white>=atter->white_up*0.7);}
	if(atter->id==21&&((stud_B8*)atter)->fight_active){canSk=notused=0;}
	if(atter->id==22){
		stud_B9*b9=(stud_B9*)atter;
		if(!(atter->white<10)){canSk=staeno=0;}
		if(!b9->can_use_this_day(day)){canSk=notused=0;}
	}
	if(atter->id==24&&((stud_B11*)atter)->guest_turnsLeft>0){canSk=staeno=0;}
	if(atter->id==25&&((stud_B12*)atter)->shake_active){canSk=staeno=0;}
	if(atter->id==26){canSk=staeno=(atter->white>=20);}
	canSk&=(*atter).HavCt[0];
	skilled&=(*atter).HavCt[0];
	
	int choice=0,max_choice=1;
	if(hasLinkPotential){max_choice=2;}
	
	clear_action_area();
	gotoxy(0,19);
	color(14);
	printf("Choose action (W/S to move, Enter to confirm):");
	
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
				if(!skilled){printf("SKILL: %s [Unskilled]",atter->ct2.empty()?"???":atter->ct2[0].c_str());}
				else if(!notused){printf("SKILL: %s [Used]",atter->ct2[0].c_str());}
				else{printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"???":atter->ct2[0].c_str());}
			}else{
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}
		}else{
			printf("   ");
			if(!canSk){
				color(8);
				if(!skilled){printf("SKILL: %s [Unskilled]",atter->ct2.empty()?"???":atter->ct2[0].c_str());}
				else if(!notused){printf("SKILL: %s [Used]",atter->ct2[0].c_str());}
				else{printf("SKILL: %s (Not enough stamina)",atter->ct2.empty()?"???":atter->ct2[0].c_str());}
			}else{
				color(11);
				printf("SKILL: %s",atter->ct2[0].c_str());
			}
		}
		color(7);
		
		if(hasLinkPotential){
			gotoxy(0,22);
			
			auto getRandomStr=[](int len)->string{
				string s;
				for(int i=0;i<len;i++){s+=33+rand()%94;}
				return s;
			};
			
			string displayText;
			int textColor=8;
			bool canLink=0;
			
			if(!allFull){
				string rand1=getRandomStr(4);
				string rand2=getRandomStr(atter->name.length());
				string rand3=getRandomStr(9);
				displayText=rand1+": "+rand2+" ["+rand3+"]";
				textColor=8;
				canLink=0;
			}else if(!hasLink){
				string rand2=getRandomStr(atter->name.length());
				displayText="LINK: "+rand2+" [Unskilled]";
				textColor=8;
				canLink=0;
			}else if(!allPresent){
				displayText="LINK: "+link_ct[myLinkId]+" [Incomplete]";
				textColor=8;
				canLink=0;
			}else{
				displayText="LINK: "+link_ct[myLinkId];
				textColor=6;
				canLink=1;
			}
			
			if(choice==2){
				color(14);
				printf("-> ");
				color(textColor);
				printf("%s",displayText.c_str());
			}else{
				printf("   ");
				color(textColor);
				printf("%s",displayText.c_str());
			}
			color(7);
		}
		
		char key=getch();
		if(key=='w'||key=='W'){
			if(choice>0){choice--;}
			else{choice=max_choice;}
		}else if(key=='s'||key=='S'){
			if(choice<max_choice){choice++;}
			else{choice=0;}
		}else if(key==13){
			if(choice==0){return{0,atter};}
			if(choice==1&&canSk){return{1,atter};}
			if(choice==2&&hasLinkPotential&&allFull&&hasLink&&allPresent){return{2,atter};}
		}
	}
}

static bool attDis(stud*atter,stud*tar,stuV&team,stuV&enemy,const actCho&action,int&cntAlive){
	if(atter==NULL||tar==NULL){return 0;}
    gotoxy(0,24);
    if(action.useSk==2){
        color(6);
        printf("[LINK_SKILL] %s will use %s!",atter->name.c_str(),link_ct[atter->WithP].c_str());
    }else if(action.useSk==1){
        color(11);
        printf("[SKILL] %s will use %s!",atter->name.c_str(),atter->ct2[0].c_str());
    }else{
        color(10);
        printf("[ATTACK] %s will attack %s!",atter->name.c_str(),tar->name.c_str());
    }
    color(7);
    gotoxy(0,25);
    color(14);
    printf("Press any key to continue...");
    getch();
    clear_action_area();
	return 1;
}

static void attExe(stud* atter,stud* tar,stuV& team,stuV& enemy,const actCho& action,int& cntAlive,int loc){
	color(7);
	voiV vTeam,vEnemy;
	for(auto* p:team){vTeam.push_back(p);}
	for(auto* p:enemy){vEnemy.push_back(p);}
	
	gotoxy(0,loc);
	int finat=0;
	if(action.useSk==1){
		sk_hitt(atter,tar,vTeam,vEnemy);
		color(11);
		printf("[SKILL] %s uses %s to %s!",atter->name.c_str(),atter->ct2[0].c_str(),tar->name.c_str());
	}else if(action.useSk==2){
		int classId=classtable[atter->Dtee().first.first][atter->Dtee().first.second];
		toge_fight({atter->WithP,classId},{atter,tar},team,enemy);
		color(6);
		printf("[LINK_SKILL] %s uses %s to %s!",atter->name.c_str(),link_ct[atter->WithP].c_str(),tar->name.c_str());
	}else{
		int original_damage=hitt(atter,tar,vTeam,vEnemy);
		
		bool hasSilenceBonus=0;
		int silenceBonus=0;
		for(auto& bonus:atter->tmp_att_plus){
			if(bonus.first==10000&&bonus.second>0){
				hasSilenceBonus=1;
				silenceBonus=bonus.first;
				break;
			}
		}
		
		if(hasSilenceBonus){
			color(10);
			printf("[ATTACK] %s attacks %s and deals %d damage!",atter->name.c_str(),tar->name.c_str(),original_damage);
			gotoxy(0,loc+1);
			color(13);
			printf("[Silence Reigns Supreme] +%d damage!!!",silenceBonus);
			gotoxy(0,loc+2);
		}else{
			color(10);
			printf("[ATTACK] %s attacks %s and deals %d damage!",atter->name.c_str(),tar->name.c_str(),original_damage);
			gotoxy(0,loc+1);
		}
	}
	
	if(tar->status==0){
		color(12);
		printf("[DEATH] %s has fallen!",tar->name.c_str());
		color(7);
		cntAlive--;
	}
}

static bool canAct(stuV&team){
	for(auto*s:team){
		if(s&&isalive[s->id]&&s->status!=-1&&s->red>=0&&s->can_act){return 1;}
	}
	return 0;
}

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
		
		stud*atter1=NULL;
		stud*atter2=NULL;
		stud*tar1=NULL;
		stud*tar2=NULL;
		actCho action1={0,NULL};
		actCho action2={0,NULL};
		bool ifact1=0,ifact2=0;
		
		// Team A 回合
		if(canAct(teamA)){
			int startL=20;
			atter1=selAtt(teamA,"Team A",startL);
			if(atter1){
				int tarLine=isL?startL+teamA.size()-5:startL+teamA.size()-3;
				tar1=selTar(atter1,teamB,"Team A",tarLine);
				if(tar1){
					action1=selAct(atter1,lA);
					ifact1=attDis(atter1,tar1,teamA,teamB,action1,Bnum);
				}
			}
		}
		
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
			atter2=selAtt(teamB,"Team B",startL);
			if(atter2){
				int tarLine=isL?startL+teamB.size()-5:startL+teamB.size()-3;
				tar2=selTar(atter2,teamA,"Team B",tarLine);
				if(tar2){
					action2=selAct(atter2,lB);
					ifact2=attDis(atter2,tar2,teamB,teamA,action2,Anum);
				}
			}
		}
		clear_action_area();
		if(ifact1){attExe(atter1,tar1,teamA,teamB,action1,Bnum,19);}
		if(ifact2){attExe(atter2,tar2,teamB,teamA,action2,Anum,22);}
		gotoxy(0,25);
		color(14);
		printf("Press any key to continue...");
		getch();
		endTurn(teamA,teamB,tchID);
	}
	system("cls");
	sett(lA,lB,3);
	color(7);
}

void fight(int day,int cla){
	if(day==5&&cla>=7)return;
	if(cla==8){
		system("cls");
		color(14);
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
	color(14);
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
	applySubjectEnd(classtable[day][cla]);

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

#endif// __FIGHT_H__
