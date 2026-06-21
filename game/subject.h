#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#define __SUBJECT_H_ver__ 3

// 不听讲检查
void checkListenStart(int subject){
	if(subject==3||subject==2||subject==8||subject==6||subject==5){
		stud* punished=NULL;
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(!s->listen){
				if(rand()%100<65){
					s->cred(-10);
					s->cblue(-10);
					s->cwhite(-10);
					s->listen=1;
					s->listen_punish++;
					punished=s;
					if(debug_on){logPrint(12,"[Class] Headteacher came! %s loses 10 HP/SAN/STA for not listening.\n",s->name.c_str());}
					if(s->listen_punish>=5){unlockChallenge(5);}
				}
			}
		}
		
		if(subject==5){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(rand()%100<50){
					s->cwhite(10);
					if(debug_on){logPrint(7,"[History Class] %s +10 STA\n",s->name.c_str());}
				}else{
					s->cblue(-10);
					if(debug_on){logPrint(7,"[History Class] %s -10 SAN\n",s->name.c_str());}
				}
			}
			
			bool aPunished=0,bPunished=0;
			for(auto x:listA){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!s->listen&&isalive[s->id]){
					aPunished=1;
					break;
				}
			}
			for(auto x:listB){
				if(x==NULL){continue;}
				stud* s=(stud*)x;
				if(!s->listen&&isalive[s->id]){
					bPunished=1;
					break;
				}
			}
			
			bool aDestroy=0,bDestroy=0;
			int cleanRounds=rand()%10;
			for(int i=0;i<cleanRounds;i++){rand();}
			
			if(aPunished&&rand()%100<1){
				aDestroy=1;
				if(debug_on){logPrint(12,"[History Class] Team A is annihilated!\n");}
				for(auto x:listA){
					if(x==NULL){continue;}
					stud* s=(stud*)x;
					if(isalive[s->id]){s->cred(-9999);}
				}
			}
			
			cleanRounds=rand()%10;
			for(int i=0;i<cleanRounds;i++){rand();}
			
			if(bPunished&&rand()%100<1){
				bDestroy=1;
				if(debug_on){logPrint(12,"[History Class] Team B is annihilated!\n");}
				for(auto x:listB){
					if(x==NULL){continue;}
					stud* s=(stud*)x;
					if(isalive[s->id]){s->cred(-9999);}
				}
			}
			
			if(aDestroy&&bDestroy){
				if(debug_on){logPrint(12,"[History Class] Total Destruction! Both teams annihilated!\n");}
				unlockChallenge(6);
			}
		}
	}
}

// 学科开始效果
void applySubjectStart(int subject){
	if(debug_on){logPrint(7,"[Subject Start] Subject ID: %d\n",subject);}
	
	if(subject==2){// 数学
		if(debug_on){logPrint(7,"[Math Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			
			// 伤害加成 (持续3回合)
			if(s->id==3||s->id==28||s->id==10){
				s->att_mul.push_back({1.1, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +10%% damage\n",s->name.c_str());}
			}
			if(s->id==9||s->id==26){
				s->att_mul.push_back({1.05, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +5%% damage\n",s->name.c_str());}
			}
			
			// 白条消耗 (持续3回合)
			if(s->id==10){
				s->white_mul.push_back({0.9, 3});
				if(debug_on){logPrint(7,"[Math Class] %s -10%% stamina cost\n",s->name.c_str());}
			}
			if(s->id==21||s->id==12||s->id==13){
				s->white_mul.push_back({1.1, 3});
				if(debug_on){logPrint(7,"[Math Class] %s +10%% stamina cost\n",s->name.c_str());}
			}
			
			// B3 上限提升
			if(s->id==16){
				s->att+=2;
				s->red_up+=s->red_up*0.2;
				s->blue_up+=s->blue_up*0.2;
				s->white_up+=s->white_up*0.2;
				s->cred(s->red_up/6);
				s->cblue(s->blue_up/6);
				s->cwhite(s->white_up/6);
				if(debug_on){logPrint(7,"[Math Class] B3 +2 ATK, +20%% caps\n");}
			}
		}
		
		// 概率效果
		if(rand()%100<92){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==9&&isalive[s->id]){
					int dmg=-(rand()%14+3);
					s->cblue(dmg);
					if(debug_on){logPrint(7,"[Math Class] A9 loses %d SAN\n",-dmg);}
					break;
				}
			}
		}
		if(rand()%100<13){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if((s->id==12||s->id==13)&&isalive[s->id]){
					s->cwhite(11);
					if(debug_on){logPrint(7,"[Math Class] %s +11 STA\n",s->name.c_str());}
				}
			}
		}
		if(rand()%100<4){
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(s->id==18&&isalive[s->id]){
					int dmg=-(rand()%21);
					s->cblue(dmg);
					if(debug_on){logPrint(7,"[Math Class] B5 loses %d SAN\n",-dmg);}
					break;
				}
			}
		}
	}
	
	if(subject==1){// 语文
		if(debug_on){logPrint(7,"[Chinese Class] Start effects\n");}
		
		int r=rand()%100;
		if(r<50){
			if(debug_on){logPrint(7,"[Chinese Class] Nothing happens.\n");}
		}
		else if(r<70){
			if(debug_on){logPrint(7,"[Chinese Class] All students lose 10 STA.\n");}
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(isalive[s->id]){s->cwhite(-10);}
			}
		}
		else if(r<90){
			if(debug_on){logPrint(7,"[Chinese Class] All students gain 10 SAN (B3 gains 15).\n");}
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(isalive[s->id]){
					if(s->id==16){s->cblue(15);}
					else{s->cblue(10);}
				}
			}
		}
		else{
			int card=rand()%4;
			int targetTeam=rand()%2;
			
			if(debug_on){logPrint(7,"[Chinese Class] Card effect! Card=%d, Target Team=%s\n",card,targetTeam==0?"A":"B");}
			
			switch(card){
				case 0: // Double Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_double=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_double=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Double Card: Team %s +3 ATK\n",targetTeam==0?"A":"B");}
					break;
				case 1: // Forgive Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_forgive=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_forgive=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Forgive Card: Team %s gets damage reduction\n",targetTeam==0?"A":"B");}
					break;
				case 2: // Pass Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_pass=1;}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->chinese_pass=-1;}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Pass Card: Team %s takes self damage when attacking\n",targetTeam==0?"A":"B");}
					break;
				case 3: // Bread Card
					if(targetTeam==0){
						for(auto x:listA){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->cwhite(20);}
						}
					}else{
						for(auto x:listB){
							if(x!=NULL&&isalive[((stud*)x)->id]){((stud*)x)->cwhite(20);}
						}
					}
					if(debug_on){logPrint(7,"[Chinese Class] Bread Card: Team %s +20 STA\n",targetTeam==0?"A":"B");}
					break;
			}
		}
	}
	
	if(subject==3){// 英语A
		if(debug_on){logPrint(7,"[English A] Start effects\n");}
		
		bool hasAAlive=0;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if((s->id>=1&&s->id<=13)&&s->id!=11&&isalive[s->id]){
				hasAAlive=1;
				break;
			}
		}
		
		if(!hasAAlive){
			if(debug_on){logPrint(7,"[English A] No class A students here, effects disabled.\n");}
		}else{
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				s->cwhite(-10);
				s->cblue(-5);
				if(debug_on){logPrint(7,"[English A] %s -10 STA, -5 SAN\n",s->name.c_str());}
			}
		}
	}
	
	if(subject==4){// 英语B
		if(debug_on){logPrint(7,"[English B] Start effects\n");}
		
		bool hasBAlive=0;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id>=14&&s->id<=28&&isalive[s->id]){
				hasBAlive=1;
				break;
			}
		}
		
		if(!hasBAlive){
			if(debug_on){logPrint(7,"[English B] No class B students here, effects disabled.\n");}
			if(rand()%100<1){unlockChallenge(4);}
		}else{
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(s->id>=14&&s->id<=28){
					s->cwhite(-10);
					s->cblue(-5);
					if(debug_on){logPrint(7,"[English B] %s -10 STA, -5 SAN\n",s->name.c_str());}
				}else{
					s->cwhite(-5);
					s->cblue(-2);
					if(debug_on){logPrint(7,"[English B] %s -5 STA, -2 SAN\n",s->name.c_str());}
				}
			}
			
			if(rand()%100<1){
				vector<stud*> bStudents;
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(s->id>=14&&s->id<=28&&isalive[s->id]){bStudents.push_back(s);}
				}
				if(!bStudents.empty()){
					int idx=rand()%bStudents.size();
					scapegoat=bStudents[idx];
					if(debug_on){logPrint(7,"[English B] Scapegoat event! %s bears all incoming damage\n",scapegoat->name.c_str());}
				}
			}
		}
	}
	
	if(subject==6){// 政治
		if(debug_on){logPrint(7,"[Politics Class] Start effects\n");}
		
		// A3 睡觉
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==3&&isalive[s->id]){
				s->listen=0;
				if(debug_on){logPrint(7,"[Politics Class] A3 falls asleep\n");}
				break;
			}
		}
		
		// 全局伤害浮动
		float dmg_float=(910+rand()%10)/1000.0f;
		global_damage_mult=dmg_float;
		if(debug_on){logPrint(7,"[Politics Class] Global damage multiplier: %.3f\n",dmg_float);}
	}
	
	if(subject==7){// 体育
		if(debug_on){logPrint(7,"[PE Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			if(s->id==26||s->id==19){
				if(debug_on){logPrint(7,"[PE Class] %s doesn't love sports, skipped\n",s->name.c_str());}
				continue;
			}
			s->cwhite(-5);
			s->cblue(10);
			if(debug_on){logPrint(7,"[PE Class] %s -5 STA, +10 SAN\n",s->name.c_str());}
		}
	}
	
	if(subject==8){// 物理
		if(debug_on){logPrint(7,"[Physics Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){
				s->cwhite(5);
				if(debug_on){logPrint(7,"[Physics Class] %s +5 STA\n",s->name.c_str());}
			}
		}
		
		vector<stud*> alive;
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(isalive[s->id]){
				alive.push_back(s);
			}
		}
		if(!alive.empty()){
			int idx=rand()%alive.size();
			physics_marked=alive[idx];
			if(debug_on){
				logPrint(7,"[Physics Class] Marked: %s (effects not shown in game)\n",physics_marked->name.c_str());
			}
		}
	}
	
	if(subject==9){// 信息
		if(debug_on){logPrint(7,"[ICT Class] Start effects\n");}
		
		if(rand()%1000<1){
			if(debug_on){logPrint(7,"[ICT Class] OIer's game triggered! (0.1%%)\n");}
		}
	}
	
	if(subject==10&&debug_on){logPrint(7,"[Art Class] No special effects\n");}
	
	if(subject==11){// 音乐
		if(debug_on){logPrint(7,"[Music Class] Start effects\n");}
		
		if(rand()%100<10){
			if(debug_on){logPrint(7,"[Music Class] Note check! 30%% chance for everyone to lose HP\n");}
			
			for(auto p:stud_list){
				if(p==NULL){continue;}
				stud* s=(stud*)p;
				if(!isalive[s->id]){continue;}
				
				if(rand()%100<30){
					if(s->red>=5){
						s->cred(-5);
						if(debug_on){logPrint(7,"[Music Class] %s -5 HP (now %d)\n",s->name.c_str(),s->red);}
					}else if(s->red>0){
						int oldRed=s->red;
						s->cred(-s->red);
						if(debug_on){logPrint(7,"[Music Class] %s HP reduced from %d to 0\n",s->name.c_str(),oldRed);}
					}
				}
			}
		}
	}
	
	if(subject==12){// 生物
		if(debug_on){logPrint(7,"[Biology Class] Start effects\n");}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			int staGain=10;
			if(s->id==3){staGain=8;}
			s->cwhite(staGain);
			if(debug_on){logPrint(7,"[Biology Class] %s +%d STA\n",s->name.c_str(),staGain);}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==13&&isalive[s->id]){
				s->cblue(5);
				if(debug_on){logPrint(7,"[Biology Class] A13 +5 SAN\n");}
			}
		}
	}
	
	if(subject==13){// 地理
		if(debug_on){logPrint(7,"[Geography Class] Start effects\n");}
		
		bool hasB2=0;
		for(auto x:listA){
			if(x!=NULL&&((stud*)x)->id==15&&isalive[((stud*)x)->id]){
				hasB2=1;
				break;
			}
		}
		if(!hasB2){
			for(auto x:listB){
				if(x!=NULL&&((stud*)x)->id==15&&isalive[((stud*)x)->id]){
					hasB2=1;
					break;
				}
			}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			
			s->cwhite(5);
			
			if(hasB2){
				bool inTeam=0;
				for(auto x:listA){if(x==s){inTeam=1;}}
				for(auto x:listB){if(x==s){inTeam=1;}}
				if(inTeam){
					s->cwhite(5);
					if(debug_on){logPrint(7,"[Geography Class] %s +5 STA (team bonus)\n",s->name.c_str());}
				}
			}
		}
		
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(s->id==15&&isalive[s->id]){
				s->cwhite(5);
				if(debug_on){logPrint(7,"[Geography Class] B2 +5 STA (self bonus)\n");}
			}
		}
	}
	if(subject>=14&&subject<=17){// 晚，什么科目自己看输出
		if(debug_on){logPrint(7,"[Late Self-Study] Subject ID: %d\n",subject);}
		
		if(subject==14){
			if(rand()%100<70){
				if(debug_on){logPrint(12,"[Late Self-Study] Physics exam! -10 STA, -7 SAN\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cwhite(-10);
					s->cblue(-7);
				}
			}else{
				if(debug_on){logPrint(10,"[Late Self-Study] No physics exam! +10 HP/SAN/STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cred(10);
					s->cblue(10);
					s->cwhite(10);
				}
			}
		}
		else if(subject==15){
			if(rand()%100<95){
				if(debug_on){logPrint(12,"[Late Self-Study] Math exam! -15 STA, -15 SAN (B3/B4 exempt)\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==16||s->id==17){continue;}
					s->cwhite(-15);
					s->cblue(-15);
				}
			}else{
				if(debug_on){logPrint(10,"[Late Self-Study] No math exam! +10 HP/SAN/STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cred(10);
					s->cblue(10);
					s->cwhite(10);
				}
			}
		}
		else if(subject==16){
			int r1=rand()%100;
			if(r1<90){
				if(debug_on){logPrint(12,"[Late Self-Study] Class combining! B class -5 STA, -5 SAN\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id>=14&&s->id<=28){
						if(s->id==17){continue;}
						s->cwhite(-5);
						s->cblue(-5);
					}
				}
				int r2=rand()%100;
				if(r2<25){
					if(debug_on){logPrint(10,"[Late Self-Study] English films! +10 HP/SAN/STA\n");}
					for(auto p:stud_list){
						if(p==NULL){continue;}
						stud* s=(stud*)p;
						if(!isalive[s->id]){continue;}
						if(s->id==17){continue;}
						s->cred(10);
						s->cblue(10);
						s->cwhite(10);
					}
				}else{
					if(debug_on){logPrint(12,"[Late Self-Study] English exam penalty! -10 HP/SAN/STA\n");}
					for(auto p:stud_list){
						if(p==NULL){continue;}
						stud* s=(stud*)p;
						if(!isalive[s->id]){continue;}
						if(s->id==17){continue;}
						s->cred(-10);
						s->cblue(-10);
						s->cwhite(-10);
					}
				}
			}else{
				if(debug_on){logPrint(10,"[Late Self-Study] Watch films together! +25 HP/SAN/STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cred(25);
					s->cblue(25);
					s->cwhite(25);
				}
			}
		}
		else if(subject==17){
			int r=rand()%100;
			if(r<20){
				if(debug_on){logPrint(12,"[Late Self-Study] Chinese exam - Modern Reading II! -5 SAN, -5 STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cblue(-5);
					s->cwhite(-5);
				}
			}else if(r<40){
				if(debug_on){logPrint(12,"[Late Self-Study] Chinese exam - Basics! -5 STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cwhite(-5);
				}
			}else if(r<80){
				if(debug_on){logPrint(10,"[Late Self-Study] Chinese - Documentary! +5 HP/SAN/STA\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cred(5);
					s->cblue(5);
					s->cwhite(5);
				}
			}else{
				if(debug_on){logPrint(12,"[Late Self-Study]\
 Chinese exam - Composition Practice! -10 SAN, -10 STA, -5 HP\n");}
				for(auto p:stud_list){
					if(p==NULL){continue;}
					stud* s=(stud*)p;
					if(!isalive[s->id]){continue;}
					if(s->id==17){continue;}
					s->cred(-5);
					s->cblue(-10);
					s->cwhite(-10);
				}
			}
		}
	}
}

// 学科结束效果
void applySubjectEnd(int subject){
	if(debug_on){logPrint(7,"[Subject End] Subject ID: %d\n",subject);}
	
	if(subject==2){// 数学
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			if(!isalive[s->id]){continue;}
			if(s->id==17){continue;}
			
			// 注意：att_mul 和 white_mul 的临时乘区会在 on_turn_start 中自动过期
			// 只需要重置 B3 这种永久改属性的
			if(s->id==16){
				s->att-=2;
				s->red_up=100;
				s->blue_up=100;
				s->white_up=100;
				s->red=min(s->red,s->red_up);
				s->blue=min(s->blue,s->blue_up);
				s->white=min(s->white,s->white_up);
				if(debug_on){logPrint(7,"[Math Class] B3 caps restored\n");}
			}
		}
	}
	
	if(subject==1){// 语文
		for(auto p:stud_list){
			if(p==NULL){continue;}
			stud* s=(stud*)p;
			s->chinese_double=0;
			s->chinese_forgive=0;
			s->chinese_pass=0;
		}
		if(debug_on){logPrint(7,"[Chinese Class] Card effects cleared\n");}
	}
	
	if(subject==6){// 政治
		global_damage_mult=1.0f;
		if(debug_on){logPrint(7,"[Politics Class] Effects cleared\n");}
	}
	if(subject==8){// 物理
		physics_marked=NULL;
		if(debug_on){logPrint(7,"[Physics Class] Mark cleared\n");}
	}
	if(subject==4){// 英语B
		scapegoat=NULL;
		if(debug_on){logPrint(7,"[English B] Scapegoat cleared\n");}
	}
}

#endif// __SUBJECT_H__