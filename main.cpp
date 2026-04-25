#include"framew.h"
#include"extra.h"
#include"turn.h"
//注意！需要图标的话用project文件夹下的compile.bat编译，调试时可以使用Devc++.

int nowy=4;
bool timeOfStarting=0;

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

//普通攻击函数
void hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return;}
	stud*ta=(stud*)f1;
	stud*tb=(stud*)f2;

	if(debug_on){
		logPrint(10,"[ATTACK] %s",ta->name.c_str());
		logPrint(7," -> ");
		logPrint(9,"%s\n",tb->name.c_str());
	}//日志窗口输出

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
	}//日志窗口输出
	//最终攻击
	int final_att=((*ta).att*(*ta).att_mul*(*tb).be_att_mul+(*ta).tmp_att_plus);
	if(ta->id==5&&final_att>30){unlockChallenge(2);}

	if(debug_on){
		logPrint(7,"  Damage Calculation:\n");
		logPrint(7,"    Base Attack: %d\n",(*ta).att);
		logPrint(7,"    Attacker Multiplier: %.2f",(*ta).att_mul);
		if(ta->is_crazy){logPrint(12," (INSANE x1.5)");}
		logPrint(7,"\n");
		logPrint(7,"    Target Defense Multiplier: %.2f\n",(*tb).be_att_mul);
		logPrint(7,"    Temporary Attack Bonus: +%d\n",(*ta).tmp_att_plus);
		logPrint(7,"    Raw Damage: %d\n",final_att);
	}
	if(sit1!=2&&sit2!=2){
		int old_final=final_att;
		final_att=min(final_att,30);
		if(debug_on&&old_final>30){logPrint(12,"    Damage capped to 30 (max damage limit)\n");}
	}
	if(sit1==3||sit2==3){
		int old_final=final_att;
		final_att=min(final_att,10);
		if(debug_on&&old_final>10){logPrint(12,"    Damage capped to 10 (special damage limit)\n");}
	}
	if(sit1==4||sit2==4){
		int old_final=final_att;
		final_att=min(final_att,18);
		if(debug_on&&old_final>18){logPrint(12,"    Damage capped to 10 (special damage limit)\n");}
	}
	if(sit1==5||sit2==5){
		int old_final=final_att;
		final_att*=0.3;
		logPrint(12,"    Damage reduced 70% (special damage reduction)\n");
	}
	if(debug_on){logPrint(10,"    Final Damage: %d\n",final_att);}
	int old_red=tb->red;
	(*tb).cred(final_att*-1);
	(*ta).cwhite(-5);
	if(tb -> Bighuocar){
		int A7rand=rand()%5;
		if(A7rand==1){
			ta -> cred(-final_att);
		}
	}
	if(debug_on){
		logPrint(7,"  Result:\n");
		logPrint(12,"    %s HP: %d -> %d ( -%d )\n",tb->name.c_str(),old_red,tb->red,final_att);
		logPrint(7,"  Stamina Cost:\n");
		logPrint(15,"    %s Stamina: %d -> %d ( -5 )\n",ta->name.c_str(),ta->white+5,ta->white);
	}//日志窗口输出

	(*ta).after_att(tb,sbj_teacher,t1,t2);
	(*tb).on_minus_red(ta,sbj_teacher,t2,t1);

	if((*tb).status==0){
		isalive[(*tb).id]=0;
		checkProgress(2);  // 首次击杀成就
		if(debug_on){logPrint(12,"  [DEATH] %s has been killed!\n",tb->name.c_str());}

		for(auto*s:t1){
			if(s&&s->id==28){((stud_B15*)s)->on_enemy_death(t1);}
		}
	}
	if(debug_on){logPrint(7,"\n");}//日志窗口输出
}

//主动技能(under fixing)
void sk_hitt(void*f1,void*f2,vector<void*>T1,vector<void*>T2){
	if(f1==NULL||f2==NULL){return;}
	vector<stud*>t1,t2;
	for(auto y:T1){
		if(y!=NULL){t1.push_back((stud*)y);}
	}
	for(auto y:T2){
		if(y!=NULL){t2.push_back((stud*)y);}
	}
	((stud*)f1) -> skhit((stud*)f2,sbj_teacher,t1,t2);
	return;
}

void reset(){//哪个OIer没有点打表的毅力！！
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

	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL){continue;}
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py){
            if(j==sbj_teacher){(*tmp).att_mul+=0.2;}
        }
	}
}

void team_chs(){
	bool isc[16+10]={0};
	int current_pos=0;
	int round=0;
	bool team_a_turn=1;

	while(current_pos<stud_list.size()&&stud_list[current_pos]==NULL){current_pos++;}
	

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
					/*NUSFWP*/listA.push_back(stud_list[current_pos]);
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

	printf("\nPress any key to continue...");
	getch();
	printf("\n\n");
	color(10);
	printf("OK! Let's go!\n");
	color(7);
	sslp(1.5);
	system("cls");
}

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

	int lll=lA.size();
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
		}
		else{
			color(10);
			printf("%-6s",y.name.c_str());
		}
		color(7);
		if(y.att<=0||is_dead){printf("  --  | ");}
		else{
			color(6);
			printf("  %02d  ",int(y.att*y.att_mul+y.tmp_att_plus));
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
		}
		else{
			//血量显示
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			
			//蓝量显示（疯人显示XXX，输出后加空格）
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}
			else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			
			//体力显示（累倒显示XXX，输出后加空格）
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}
			else{
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
		}
		else{
			color(9);
			printf("%-6s",y.name.c_str());
		}
		color(7);
		if(y.att<=0||is_dead){printf("  --  | ");}
		else{
			color(6);
			printf("  %02d  ",int(y.att*y.att_mul+y.tmp_att_plus));
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
		}
		else{
			//血量显示
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			
			//蓝量显示（疯人显示XXX，输出后加空格）
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}
			else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			
			//体力显示（累倒显示XXX，输出后加空格）
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}
			else{
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

void clear_action_area(){
	for(int i=19;i<=26;i++){
		gotoxy(0,i);
		for(int j=0;j<80;j++){printf(" ");}
	}
}

void fight(int day, int cla){
		if(day==5&&cla>=7)return;
	if(cla==8){
		system("cls");
		color(11);
		printf("+=======================================================+\n");
		printf("|                LATE SELF-STUDY HOUR                   |\n");
		printf("|             8 ROUNDS OF INTENSE BATTLE!               |\n");
		printf("+=======================================================+\n\n");
		color(7);
		sslp(2);
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
	checkProgress(3);  // 首次战斗成就

	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL){continue;}
		tmp=(stud*)stud_list[i];
		if(tmp->id==26){((stud_B13*)tmp)->on_class_start(classtable[day][cla]);}
	}

	for (int i = 0; i < stud_list.size(); i++){
		if (stud_list[i] == NULL) continue;
		tmp = (stud * )(stud_list[i]);
		for (int j : (*tmp).py) if (j == classtable[day][cla]){
			(*tmp).att_mul += 0.5;
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
		}else{printf("\nTeam A - Invalid choice, please select again:\n");}
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
					printf("%d. %s(AWAY)     \n",i+1,y.name.c_str());
				}else{
					color(10);
					printf("%d. %s(ATT:%02d)          \n",i+1,y.name.c_str(),int(y.att*y.att_mul));
				}
				color(7);
			}
			else {
				printf("   ");
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)     \n",i+1,y.name.c_str());
				}else{
					color(10);
					printf("%d. %s(ATT:%02d)          \n",i+1,y.name.c_str(),int(y.att*y.att_mul));
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
					printf("%d. %s(ATT:%02d) [SELECTED]       ", current_pos_A + 1, y.name.c_str(), int(y.att * y.att_mul));
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
		
		// 检查选中的3人是否全部死亡（排除力竭，力竭算活着）
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
			// 全部死亡，清空重新选
			a_selection_valid = false;
			// 清屏显示错误提示区域
			for(int i = 0; i < 10; i++){
				gotoxy(0, a_start_line + i);
				for(int j = 0; j < 80; j++) printf(" ");
			}
		} else {
			a_selection_valid = true;
		}
	}

	// Team B 选择（同样逻辑）
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
		}else{printf("\nTeam B - Invalid choice, please select again:\n");}
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
					printf("%d. %s(AWAY)     \n",i+1,y.name.c_str());
				}else{
					color(10);
					printf("%d. %s(ATT:%02d)          \n",i+1,y.name.c_str(),int(y.att*y.att_mul));
				}
				color(7);
			}
			else {
				printf("   ");
				if(y.id==26&&((stud_B13*)&y)->isAway()){
					color(8);
					printf("%d. %s(AWAY)     \n",i+1,y.name.c_str());
				}else{
					color(9);
					printf("%d. %s(ATT:%02d)          \n",i+1,y.name.c_str(),int(y.att*y.att_mul));
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
					printf("%d. %s(ATT:%02d) [SELECTED]       ", current_pos_B + 1, y.name.c_str(), int(y.att * y.att_mul));
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
		
		// 检查选中的3人是否全部死亡（排除力竭，力竭算活着）
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
	printf("     \n                             \n");

	printf("Press any key to start the battle...                ");
	printf("\n                                                  ");
	printf("\n                                                  ");
	getch();

	turn(3,lA,lB,0);

	// 检查残血/满血通关成就
	bool allAlive=1,allFull=1,anyLow=0;

	for(auto x:lA){
		stud* s=(stud*)x;
		if(isalive[s->id]&&s->red>=0){
			double ratio=(double)s->red/s->red_up;
			if(ratio<=0.2){anyLow=1;}
			if(s->red<s->red_up){allFull=0;}
		}
	}
	for(auto x:lB){
		stud* s=(stud*)x;
		if(isalive[s->id]&&s->red>=0){
			double ratio=(double)s->red/s->red_up;
			if(ratio<=0.2){anyLow=1;}
			if(s->red<s->red_up){allFull=0;}
		}
	}

	if(anyLow){checkProgress(7);}
	if(allFull){checkProgress(8);}

	for(int i = 0; i < stud_list.size(); i++){
		if(stud_list[i] == NULL) continue;
		tmp = (stud*)stud_list[i];
		if(tmp->id == 28){
			((stud_B15*)tmp)->on_class_end();
		}
	}

	for (int i = 0; i < stud_list.size(); i++){
		if (stud_list[i] == NULL) continue;
		tmp = (stud * )(stud_list[i]);
		for (int j : (*tmp).py) if (j == classtable[day][cla]){
			(*tmp).att_mul -= 0.5;
		}
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
	getch();
}



int main(){
	srand(time(nullptr)*rand());

    // 加载设置
    loadSettings();
    // 根据设置开启调试日志
    if(settings.debug_log) {
        debug_on = true;
        createLogWindow();
    }
	// 加载成就
	loadAchievements();
	checkProgress(1);  // 首次启动成就

	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole,&cursorInfo);
	cursorInfo.bVisible=0;

	SetConsoleCursorInfo(hConsole,&cursorInfo);//隐藏光标

	//startASCIIart();

start:
	reset();

	color(7);
	system("cls");
	color(11);
	printf("\
+------------------------+\n\
|   Class vs. Students   |\n\
|           v0.3 rc-2.9  |\n\
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
    else if(nowy==8){// Settings
        settingsMenu();
        goto start;
    }
	else if(nowy==9){
		gotoxy(11,8);
		ppput("BYE!",0.2);
		gotoxy(0,14);

		color(7);
		cursorInfo.bVisible=1;
		SetConsoleCursorInfo(hConsole,&cursorInfo);//恢复光标
		closeLogWindow();//关闭日志窗口
		return 0;
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
		return 0;
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
					((stud*)x)->att_mul*=1.5;
				}
			}
		}
		color(12);
		printf("\n[SETTINGS] Auto Insane Mode enabled!\n");
		color(7);
		printf("Press any key to continue...");
		getch();
	}

	while(Anum>0&&Bnum>0){
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
			}
			for(int i=0;i<stud_list.size();i++){
				if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
				tmp=(stud*)(stud_list[i]);
				(*tmp).white=(*tmp).white_up;
				(*tmp).cblue(20);

				if((*tmp).red<0.2*(*tmp).red_up){(*tmp).red=0.2*(*tmp).red_up;}
				else{(*tmp).cred(20);}
			}
			color(10);
			printf("\n[WEEKEND] Weekend! Full stamina restored!\n");
			color(7);
		}
	}

	if(settings.auto_insane&&(Anum<=0||Bnum<=0)){unlockChallenge(1);}

	system("cls");
	color(14);
	printf("\n+========================================================+\n");
	if(Anum<=0&&Bnum<=0){
		printf("|                        DRAW GAME!                      |\n");
	}
	else if(Anum<=0){
		printf("|                     TEAM B VICTORY!                    |\n");
	}
	else if(Bnum<=0){
		printf("|                     TEAM A VICTORY!                    |\n");
	}
	printf("+========================================================+\n\nPress any key to continue...");
	color(7);

	getch();
	goto start;
	system("cls");
	return 0;
}
