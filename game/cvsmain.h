#ifndef __CVSMAIN_H__
#define __CVSMAIN_H__
#define __CVSMAIN_H_ver__ 7

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
	//当应用武器时初始化
	if(settings.attack_with_weapon){
		TAweapon.clear();
		TBweapon.clear();
		TAweapon.push_back(&EMPTY);
		TBweapon.push_back(&EMPTY);
		reset_every_weapon();
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
					(*tmp).cblue(20);
					(*tmp).cred(20);
				}
				color(10);
				printf("\n[MEAL] Meal time! +20 stamina restored!\n");
				color(7);
				if(settings.attack_with_weapon){
					weapon* new_weapon=get_rand_weapon();
					if(new_weapon->id!=0){
						if(rand()%2==0){
							TAweapon.push_back(new_weapon);
							printf("\n[WEAPON] Team A got weapon [%s]!\n",new_weapon->name.c_str());
						}
						else{
							TBweapon.push_back(new_weapon);
							printf("\n[WEAPON] Team B got weapon [%s]!\n",new_weapon -> name.c_str());
						}
					}
				}
				printf("\nPress any key to continue...\n");
				getch();
			}
			for(int i=0;i<stud_list.size();i++){
				if(stud_list[i]==NULL||!isalive[((stud*)stud_list[i])->id]){continue;}
				tmp=(stud*)(stud_list[i]);
				(*tmp).cblue(5);
				(*tmp).cred(5);
				(*tmp).cwhite(5);
				(*tmp).tim=(day-1)*26+(clas-1)*3;
			}
			fight(day,clas);
			if(settings.Ct_Need_Chose){
				if(clas==1||clas==2||clas==3||clas==4)Lets_Choose_Ct(listA,listB,1);
				else if(clas==8)Lets_Choose_Ct(listA,listB,2);
			}
			if(settings.attack_with_weapon){
				vector<stud*>tmpA,tmpB;
				for(auto x:listA){
					tmpA.push_back((stud*)x);
				}
				for(auto x:listB){
					tmpB.push_back((stud*)x);
				}
				change_weapon(tmpA,tmpB);
			}
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

int nowy=4;
bool timeOfStarting=0;

void clear_action_area(){
	for(int i=19+2*settings.attack_with_weapon;i<=26+2*settings.attack_with_weapon;i++){
		gotoxy(0,i);
		for(int j=0;j<80;j++){printf(" ");}
	}
}

void startASCIIart(){
	gotoxy(0,5);
	ppput("--------------->",0.1);
	for(int i=0;i<10;i++){
		gotoxy(7,i);
		if(i!=5&&i!=0)printf("|");
		else if(i==0) printf("^");
		else printf("+");
		sslp(0.1);
	}
	gotoxy(0,4);
	ppput("Floiyd",0.15);
	gotoxy(8,6);
	ppput("Studios",0.15);
	sslp(2);
	system("cls");
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

void CVS_main(){
	srand(time(nullptr)*rand());

	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole,&cursorInfo);
	cursorInfo.bVisible=0;
	SetConsoleCursorInfo(hConsole,&cursorInfo);
	setConsoleSize(80,37);

	_mkdir("saves");
    loadSettings();
    if(settings.debug_log) {
        debug_on=1;
        createLogWindow();
    }
	loadAch();

	startASCIIart();
	
start:
	reset();

	color(7);
	system("cls");
	color(11);
	printf("\
+------------------------+\n\
|   Class vs. Students   |\n\
|                  v1.2  |\n\
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

	if(!settings.hide_tips){showTip();}

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
	}else if(nowy==6){
		achievementMenu();
		goto start;
	}else if(nowy==7){
		system("start https://github.com/cso666/Class-vs-Students");
		goto start;
	}else if(nowy==8){
        settingsMenu();
        goto start;
    }else if(nowy==9){
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

#endif// __CVSMAIN_H__
