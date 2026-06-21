#ifndef __PREGAME_H__
#define __PREGAME_H__
#define __PREGAME_H_ver__ 12

bool hasLinkSkill(vector<void*> team){
	for(int i=0;i<lc_cnt;i++){
		bool all_condition_met=link_res[i];
		for(auto id:link_check[i]){
			if(hav_full_cts[id]==0){
				all_condition_met=0;
				break;
			}
			bool student_exists=0;
			for(auto p:team){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==id){
					student_exists=1;
					break;
				}
			}
			if(!student_exists){
				all_condition_met=0;
				break;
			}
		}
		if(all_condition_met){return 1;}
	}
	return 0;
}

string getCtSymbols(stud& y,vector<void*> team){
	string symbols="";
	if(y.id>100){return"{}";}
	
	if(y.HavCt[0]){symbols+="+";}
	else if(!y.ct2.empty()){symbols+="+";}
	
	if(y.HavCt[1]){symbols+="-";}
	else if(!y.ct1.empty()){symbols+="-";}
	
	if(y.ct1.size()>=2){
		if(y.HavCt[2]){symbols+="-";}
		else{symbols+="-";}
	}
	
	for(int i=0;i<lc_cnt;i++){
		bool all_condition_met=link_res[i];
		for(auto id:link_check[i]){
			if(hav_full_cts[id]==0){
				all_condition_met=0;
				break;
			}
			bool student_exists=0;
			for(auto p:team){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==id){
					student_exists=1;
					break;
				}
			}
			if(!student_exists){
				all_condition_met=0;
				break;
			}
		}
		if(all_condition_met){
			for(int id:link_check[i]){
				if(y.id==id){
					symbols+="*";
					break;
				}
			}
		}
	}
	return symbols;
}

void*choose(int id){
	if(id<1||id>29){return NULL;}

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
	if(id==29){return&t29;}
	return NULL;
}

void reset(){
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

	if(settings.full_rosters){
		for(int tr=1;tr<=29;tr++){
			if(tr==11){continue;}
			isalive[tr]=1;
			void*student=choose(tr);
			if(student!=NULL){stud_list.push_back(student);}
		}
	}else{
		while(stud_list.size()<16){
			int tr=rand()*rand()%28+1;
			int loop_count=0;
			while(isalive[tr]&&loop_count<100){
				tr=tr%29+1;
				loop_count++;
			}
			if(loop_count>=100){
				for(int i=1;i<=28;i++){
					if(!isalive[i]){tr=i;break;}
				}
			}
			isalive[tr]=1;
			void*student=choose(tr);
			if(student!=NULL){stud_list.push_back(student);}
		}
	}

	// 属性匹配加成 (持续3回合)
	for(int i=0;i<stud_list.size();i++){
		if(stud_list[i]==NULL){continue;}
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py){
            if(j==sbj_teacher){(*tmp).att_mul.push_back({1.2,3});}
        }
	}
}

int __cal_rpos(int current_line,int current_pos){
	if(settings.full_rosters){
		if(current_line){return current_pos+12;}
		else if(current_pos>=13){return current_pos+14;}
		else{return current_pos;}
	}
	if(current_line==0&&current_pos==12){return -1;}
	return current_pos;
}
#define rpos __cal_rpos(current_line,current_pos)

void team_chs(){
	bool isc[16+10]={0};
	int current_pos=0;
	bool current_line=0;
	int round=0;
	bool team_a_turn=1;

	// ===== 选人界面 =====
	if(settings.full_rosters){
		gotoxy(0,21);
		color(7);
		printf("|");
		gotoxy(0,0);
		color(11);
		printf("+-------------------------------------------------------------------+\n");
		printf("|                        Team Selection Phase                       |\n");
		printf("+-------------------------------------------------------------------+\n");
		color(7);
		printf("|                      ");
		color(10);
		printf("Team A's turn to select");
		color(7);
		printf("                      |\n");
		printf("+-------------------------------------------------------------------+\n");
		printf("|                            Student List                           |\n");
		printf("+---------------------------------+---------------------------------+\n");
		color(14);
		printf("| ->");
		color(7);
	}else{
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
	}
	
	if(settings.full_rosters){
		for(int i=0;i<12;i++){
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
		printf("|---------------------------------|\n");
		for(int i=27;i<28;i++){
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
			printf("  |");
		}
		for(int i=12;i<27;i++){
			gotoxy(34,i-5);
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
	}else{
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
	}

	int line1_=13,line2_=15;
	if(!settings.full_rosters){line1_=16;}
	color(11);
	if(settings.full_rosters){printf("+---------------------------------+---------------------------------+\n\n");}
	else{printf("+---------------------------------+\n\n");}
	gotoxy(0,25);
	color(14);
	if(settings.full_rosters){printf("Controls: W/A/S/D to move, Enter to select\n");}
	else{printf("Controls: W/S to move, Enter to select\n");}
	color(10);
	printf("Team A selected: \n");
	color(9);
	printf("Team B selected: ");
	char key=getch();

	while(round<5){
		if(key=='w'||key=='W'){
			gotoxy(current_line*34,current_pos+7);
			color(7);
			printf("|    ");
			current_pos--;
			int boun_;

			if(current_line){boun_=line2_-1;}
			else{boun_=line1_;}
			while(current_pos>=0&&(isc[rpos]||stud_list[rpos]==NULL)){current_pos--;}
			if(current_pos<0){
				current_pos=boun_;
				while(current_pos>=0&&(isc[rpos]||stud_list[rpos]==NULL)){current_pos--;}
			}

			if(current_line==0&&current_pos==12&&settings.full_rosters){current_pos--;}
			gotoxy(current_line*34,current_pos+7);
			color(14);
			printf("| ->");
		}else if(key=='s'||key=='S'){
			gotoxy(current_line*34,current_pos+7);
			color(7);
			printf("|    ");
			current_pos++;
			int boun_;

			if(current_line){boun_=line2_;}
			else{boun_=line1_;}
			while(current_pos<=boun_&&(isc[rpos]||stud_list[rpos]==NULL)){current_pos++;}
			if(current_pos>boun_){
				current_pos=0;
				while(current_pos<=boun_&&(isc[rpos]||stud_list[rpos]==NULL)){current_pos++;}
			}

			if(current_line==0&&current_pos==12&&settings.full_rosters){current_pos++;}
			gotoxy(current_line*34,current_pos+7);
			color(14);
			printf("| ->");
		}if((key=='a'||key=='A'||key=='d'||key=='D')&&settings.full_rosters&&rpos!=24){
			gotoxy(current_line*34,current_pos+7);
			color(7);
			printf("|    ");
			current_line=!current_line;
			int __ori_pos=current_pos;
			if(current_pos>(current_line?line2_:line1_)){current_pos=(current_line?line2_:line1_);}
			if(isc[rpos]){
				current_line=!current_line;
				current_pos=__ori_pos;
			}
			gotoxy(current_line*34,current_pos+7);
			color(14);
			printf("| ->");
		}else if(key==13){
			if(!isc[rpos]&&stud_list[rpos]!=NULL){
				stud y=(*(stud*)stud_list[rpos]);

				gotoxy(current_line*34,current_pos+7);
				color(7);
				printf("|    ");
				if(team_a_turn){color(160);}
				else{color(144);}
				printf("%02d. %s",rpos,y.name.c_str());

				if(team_a_turn){
					gotoxy(round*4+17,26);
					color(10);
					printf("%s",y.name.c_str());
					listA.push_back(stud_list[rpos]);
					isc[rpos]=1;
					team_a_turn=0;
					
					if(settings.full_rosters){gotoxy(23,3);}
					else{gotoxy(6,3);}
					color(10);
					printf("Team A's turn to select");
				}else{
					gotoxy(round*4+17,27);
					color(9);
					printf("%s",y.name.c_str());
					listB.push_back(stud_list[rpos]);
					isc[rpos]=1;
					team_a_turn=1;
					round++;
					
					if(settings.full_rosters){gotoxy(23,3);}
					else{gotoxy(6,3);}
					color(9);
					printf("Team B's turn to select");
				}
				key='s';continue;
			}
		}
		key=getch();
	}

	system("cls");

	// ===== 最终队伍显示 =====
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

	// ===== A4 超能力者触发 =====
	bool nesssp=0;
	if(settings.Ct_Need_Chose){
		for(auto x:stud_list){
			if(x==NULL){continue;}
			stud* s=(stud*)x;
			if(s->id==4){
				if(rand()%1000==115+80+75){  // 0.1%概率
					nesssp=1;
					s->red_up=s->red=0x3f3f3f3f;
					s->blue_up=s->blue=0x3f3f3f3f;
					s->white_up=s->white=0x3f3f3f3f;
					s->att=0x3f3f3f3f;
					s->ct1.push_back("GodPower");
					s->espp=1;
				}
				break;
			}
		}
	}

	gotoxy(0,7);
	printf("Press any key to continue...");
	getch();
	gotoxy(0,9);
	if(nesssp){
		color(95);
        printf("An unfathomable power has irrupted.");
	}else{
		color(10);
		printf("OK! Let's go!\n");
	}
	color(7);
	sslp(1.5);
	system("cls");

#ifdef __CVS_TEMPORARY_DEBUG__
	// A12 A13 满词条
	t12.HavCt[0]=t12.HavCt[1]=t12.HavCt[2]=
	t13.HavCt[0]=t13.HavCt[1]=t13.HavCt[2]=1;
	hav_full_cts[12]=hav_full_cts[13]=1;

	// B7 B8 B11 满词条
	t20.HavCt[0]=t20.HavCt[1]=t20.HavCt[2]=
	t21.HavCt[0]=t21.HavCt[1]=t21.HavCt[2]=
	t24.HavCt[0]=t24.HavCt[1]=t24.HavCt[2]=1;
	hav_full_cts[20]=hav_full_cts[21]=hav_full_cts[24]=1;

	if(debug_on){logPrint(10,"[DEBUG] A12/A13/B7/B8/B11 set to full skills for testing.\n");}
#endif
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
	printf("|  Day %d  |  Class %d  |  %-20s            |\n",day,clas,subj2[classtable[day][clas]].c_str());
	printf("+========================================================+\n");
	color(7);
	color(14);
	if(k==3){printf("\n+--- Team A %s+\n",string(TEAM_TITLE_WIDTH-13,'-').c_str());}
	if(k==5){printf("\n+--- Team A %s+\n",string(TEAM_TITLE_WIDTH_LATE-13,'-').c_str());}
	color(7);
	printf("| ");

	for(auto x:lA){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		if(is_dead){
			color(8);
			printf("%-*s",STUDENT_NAME_WIDTH,y.name.c_str());
			color(7);
		}else{
			if(y.espp){color(95);}
			else{color(10);}
			printf("%-*s",STUDENT_NAME_WIDTH,y.name.c_str());
			color(7);
			string symbols=getCtSymbols(y,lA);
			if(!symbols.empty()){
				int passives_shown=0;
				for(char c:symbols){
					if(c=='+'){
						if(y.HavCt[0]){color(14);}
						else{color(8);}
					}else if(c=='-'){
						passives_shown++;
						if(passives_shown==1){
							if(y.HavCt[1]){color(7);}
							else{color(8);}
						}else if(passives_shown==2){
							if(y.HavCt[2]){color(7);}
							else{color(8);}
						}
					}else if(c=='*'){
						if(y.WithP!=-1){color(6);}
						else{color(8);}
					}else if(c=='{'||c=='}'){color(4);}
					printf("%c",c);
				}
				color(7);
				int total_len=y.name.size()+symbols.size();
				for(int i=total_len;i<STUDENT_NAME_WIDTH+STUDENT_SKILL_WIDTH+1;i++){printf(" ");}
			}else{
				for(int ________i=0;________i<STUDENT_SKILL_WIDTH+1;________i++){printf(" ");}
			}
		}
		if(y.att<=0||is_dead){printf(" --  | ");}
		else if(y.espp){
			color(86);
			printf(" ");
			for(int i=1;i<=2;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else if(y.affected){
			color(118);
			printf(" ");
			for(int i=1;i<=2;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else{
			color(6);
			printf(" %02d ",y.get_att());
			color(7);
			printf("| ");
		}
	}
	printf("\n|");
	for(int i=1;i<=k;i++){printf("%s|",string(CARD_WIDTH,' ').c_str());}
	printf("\n| ");
	for(auto x:lA){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		bool is_white_dead=(y.status==-1||y.white<0);
		if(is_dead){
			color(8);
			printf("XXX XXX XXX XXX ");
		}else if(y.hide_bars){
			color(128);
			printf("??? ??? ??? ??? ");
			color(7);
			printf(" ");
		}else if(y.espp){
			color(84);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(83);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(95);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(91);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
		}else{
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int white_display=max(0,y.white);
				color(15);
				printf("%03d ",white_display);
			}
			int def_display=y.def;
			color(11);
			printf("%03d ",def_display);
		}
		color(7);
		printf("| ");
	}

	color(14);
	if(k==3){printf("\n+%s+\n",string(TEAM_TITLE_WIDTH-2,'-').c_str());}
	if(k==5){printf("\n+%s+\n",string(TEAM_TITLE_WIDTH_LATE-2,'-').c_str());}
	color(7);
	if(k==3){printf("\n%sVS.\n",string(TEAM_TITLE_WIDTH/2-2,' ').c_str());}
	if(k==5){printf("\n%sVS.\n",string(TEAM_TITLE_WIDTH_LATE/2-2,' ').c_str());}
	color(14);
	if(k==3){printf("+--- Team B %s+\n",string(TEAM_TITLE_WIDTH-13,'-').c_str());}
	if(k==5){printf("+--- Team B %s+\n",string(TEAM_TITLE_WIDTH_LATE-13,'-').c_str());}
	color(7);
	printf("| ");

	for(auto x:lB){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		if(is_dead){
			color(8);
			printf("%-*s",STUDENT_NAME_WIDTH,y.name.c_str());
			color(7);
		}else{
			if(y.espp){color(95);}
			else{color(10);}
			printf("%-*s",STUDENT_NAME_WIDTH,y.name.c_str());
			color(7);
			string symbols=getCtSymbols(y,lB);
			if(!symbols.empty()){
				int passives_shown=0;
				for(char c:symbols){
					if(c=='+'){
						if(y.HavCt[0]){color(14);}
						else{color(8);}
					}else if(c=='-'){
						passives_shown++;
						if(passives_shown==1){
							if(y.HavCt[1]){color(7);}
							else{color(8);}
						}else if(passives_shown==2){
							if(y.HavCt[2]){color(7);}
							else{color(8);}
						}
					}else if(c=='*'){
						if(y.WithP!=-1){color(6);}
						else{color(8);}
					}else if(c=='{'||c=='}'){color(4);}
					printf("%c",c);
				}
				color(7);
				int total_len=y.name.size()+symbols.size();
				for(int i=total_len;i<STUDENT_NAME_WIDTH+STUDENT_SKILL_WIDTH+1;i++){printf(" ");}
			}else{
				for(int ________i=0;________i<STUDENT_SKILL_WIDTH+1;________i++){printf(" ");}
			}
		}
		if(y.att<=0||is_dead){printf(" --  | ");}
		else if(y.espp){
			color(86);
			printf(" ");
			for(int i=1;i<=2;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else if(y.affected){
			color(118);
			printf(" ");
			for(int i=1;i<=2;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" | ");
		}else{
			color(6);
			printf(" %02d ",y.get_att());
			color(7);
			printf("| ");
		}
	}
	printf("\n|");
	for(int i=1;i<=k;i++){printf("%s|",string(CARD_WIDTH,' ').c_str());}
	printf("\n| ");
	for(auto x:lB){
		if(x==NULL){continue;}
		stud y=(*(stud*)x);
		bool is_dead=!isalive[y.id];
		bool is_white_dead=(y.status==-1||y.white<0);
		if(is_dead){
			color(8);
			printf("XXX XXX XXX XXX ");
		}else if(y.hide_bars){
			color(128);
			printf("??? ??? ??? ??? ");
			color(7);
			printf(" ");
		}else if(y.espp){
			color(84);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(83);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(95);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
			color(91);
			for(int i=1;i<=3;i++){
				char c=33+rand()%94;
				printf("%c",c);
			}
			color(7);
			printf(" ");
		}else{
			int red_display=(y.red<0)?0:y.red;
			color(12);
			printf("%03d ",red_display);
			if(y.is_crazy){
				color(67);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int blue_display=max(0,y.blue);
				color(3);
				printf("%03d ",blue_display);
			}
			if(is_white_dead){
				color(79);
				printf("XXX");
				color(7);
				printf(" ");
			}else{
				int white_display=max(0,y.white);
				color(15);
				printf("%03d ",white_display);
			}
			int def_display=y.def;
			color(11);
			printf("%03d ",def_display);
		}
		color(7);
		printf("| ");
	}

	color(14);
	if(k==3){printf("\n+%s+\n",string(TEAM_TITLE_WIDTH-2,'-').c_str());}
	if(k==5){printf("\n+%s+\n",string(TEAM_TITLE_WIDTH_LATE-2,'-').c_str());}
	color(7);
	printf("\n");
}

#endif// __PREGAME_H__