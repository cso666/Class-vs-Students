#ifndef __EXPERI_H__
#define __EXPERI_H__

extern int nc_cnt,rc_cnt,wc_cnt,ec_cnt;
extern string normal_ct[100],rare_ct[100],with_ct[100],evolute_ct[100];
extern bool debug_on;
extern void logPrint(int colorCode,const char* format,...);

struct CtInfo{ 
    int type;// 1=普通, 2=个人, 3=稀有, 4=联动, 5=进化
    int targetIdx;// 个人词条: 学生索引, 普通/稀有: 词条池索引
    int skillSlot;// 个人词条专用: 0=主动, 1=第一被动, 2=第二被动; 其他类型为 -1
    string name;// 词条显示名称
};

// 词条类型名
string getCtTypeName(int type){
	switch(type){
		case 1:return"[Normal]";
		case 2:return"[Personal]";
		case 3:return"[Rare]";
		case 4:return"[Link]";
		case 5:return"[Evolve]";
		default:return"[Normal]";
	}
}

// 边框样式
void getCtBorder(int type,string& top,string& bottom){
	string line(40,'-');
	string doubleLine(40,'=');
	
	switch(type){
		case 1:
			top="+"+line+"+";
			bottom="+"+line+"+";
			break;
		case 2:
			top=":"+line+":";
			bottom=":"+line+":";
			break;
		case 3:
			top="+"+doubleLine+"+";
			bottom="+"+doubleLine+"+";
			break;
		case 4:
			top=":"+doubleLine+":";
			bottom=":"+doubleLine+":";
			break;
		case 5:
			top="["+doubleLine+"]";
			bottom="["+doubleLine+"]";
			break;
		default:
			top="+"+line+"+";
			bottom="+"+line+"+";
			break;
	}
}

// 抽词条界面（接收 CtInfo 数组）
int Choose_Ct(vector<void*> team, vector<CtInfo> ctInfos, bool isTeamA) {
    for(int i=3;i<=15;i++){
        gotoxy(0,i);
        for(int j=0;j<78;j++){printf(" ");}
    }
    
    // 框架
    gotoxy(0,0);
    printf(R"---(+------------------------------------------------+                
|             Choose an extra skill!             |                
+------------------------------------------------+                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
|                                                |                
+------------------------------------------------+                
|          W/S to move, Enter to select          |                
+------------------------------------------------+                )---");
    
    // 队伍名称
    gotoxy(19,3);
    if(isTeamA){
        color(10);
        printf("Team A's turn!");
    }else{
        color(9);
        printf("Team B's turn!");
    }
    color(7);
    
    // 绘制选项（最多4个）
    for(int i=0;i<4 && i<(int)ctInfos.size();i++){
        int type=ctInfos[i].type;
        string topBorder,bottomBorder;
        getCtBorder(type,topBorder,bottomBorder);
        
        // 设置颜色
        int borderColor=7;
        switch(type){
            case 1:borderColor=7;break;
            case 2:borderColor=11;break;
            case 3:borderColor=13;break;
            case 4:borderColor=6;break;
            case 5:borderColor=4;break;
        }
        color(borderColor);
        
        // 绘制边框
        gotoxy(4,5+i*3);
        printf("%s",topBorder.c_str());
        gotoxy(4,7+i*3);
        printf("%s",bottomBorder.c_str());
        
        // 绘制内容
        gotoxy(4,6+i*3);
        string typeName=getCtTypeName(type);
        string display=typeName+" "+to_string(i+1)+". "+ctInfos[i].name;
        if(display.length()>37){display=display.substr(0,34)+"...";}
        printf("| %-38s |",display.c_str());
    }
    
    // 光标初位
    int current=0;
    gotoxy(2,6+current*3);
    color(14);
    printf("->");
    color(7);
    
    // 交互
    while(1){
        char key=getch();
        if(key=='w'||key=='W'){
            gotoxy(2,6+current*3);
            printf("  ");
            current=(current-1+4)%4;
            gotoxy(2,6+current*3);
            color(14);
            printf("->");
            color(7);
        }else if(key=='s'||key=='S'){
            gotoxy(2,6+current*3);
            printf("  ");
            current=(current+1)%4;
            gotoxy(2,6+current*3);
            color(14);
            printf("->");
            color(7);
        }else if(key==13){
            if(debug_on){
                logPrint(10,"[DEBUG] Selected index: %d (type=%d, name=%s)\n", 
                         current, ctInfos[current].type, ctInfos[current].name.c_str());
            }
            return current;
        }
    }
}

/* 旧版，我怕我改完之后有bug就留下来了
pair<int,int> Choose_Ct_Old(vector<void*> team,vector<string> person_ct){
    pair<int,int> ans={-1,-1};
    int styyle[4]={1,-1,-1,-1};
    int num_id[4]={-1,-1,-1,-1};
    if(1){
        int iid=rand()%nc_cnt;
        color(2);
        cout << normal_ct[iid]<<endl;
        num_id[0]=iid;
        
        int chss=rand()%10;
        if(chss==9||chss==1||chss==8){
            iid=rand()%nc_cnt;
            color(2);
            cout << normal_ct[iid]<<endl;
            styyle[1]=1;
        }else if(chss==7){
            iid=rand()%rc_cnt;
            color(13);
            cout << rare_ct[iid]<<endl;
            styyle[1]=3;
        }else{
            color(9);
            iid=rand()%person_ct.size();
            cout << person_ct[iid]<<endl;
            styyle[1]=2;
        }num_id[1]=iid;
        
        chss=rand()%10;
        if(chss==7||chss==8||chss==1){
            iid=rand()%nc_cnt;
            color(2);
            cout << normal_ct[iid]<<endl;
            styyle[2]=1;
        }else if(chss==9){
            iid=rand()%rc_cnt;
            color(13);
            cout << rare_ct[iid]<<endl;
            styyle[2]=3;
        }else{
            iid=rand()%person_ct.size();
            color(9);
            cout << person_ct[iid]<<endl;
            styyle[2]=2;
        }num_id[2]=iid;
        
        chss=rand()%10;
        if(chss==9){
            iid=rand()%rc_cnt;
            color(13);
            cout << rare_ct[iid]<<endl;
            styyle[3]=3;
        }else if(chss==1){
            iid=rand()%wc_cnt;
            color(6);
            cout << with_ct[iid]<<endl;
            styyle[3]=4;
        }else if(chss==6){
            iid=rand()%ec_cnt;
            color(4);
            cout << evolute_ct[iid]<<endl;
            styyle[3]=5;
        }else{
            iid=rand()%person_ct.size();
            color(9);
            cout << person_ct[iid]<<endl;
            styyle[3]=2;
        }num_id[3]=iid;
    }
    color(7);
    cout << "Which you would like to choose? (0-3)\n";
    int cccs;cin >>cccs;
    while(cccs<0||cccs>3){
        color(7);
        cout << "Choose again!!!(your choose must<=3 ,and >=0)\n"; //不是这英语语法诗人啊
        cin >> cccs;
    }
    return {styyle[cccs],num_id[cccs]};
}
*/

// 抽词条主函数
CtInfo Choose_Ct_Main(vector<void*>team,vector<CtInfo>ctInfos,bool isTeamA){
    int idx=Choose_Ct(team,ctInfos,isTeamA);
    CtInfo result=ctInfos[idx];
    if(debug_on){logPrint(10,"[Choose Ct] %s selected: %s (type=%d)\n", 
 isTeamA?"Team A":"Team B",result.name.c_str(),result.type);}
    return result;
}

void Fix_Ct(vector<void*> team,vector<void*> beside_team,CtInfo ct){
	if(ct.type==1){  // 普通词条
		int iiid=ct.targetIdx;
		if(iiid==0){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Red Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).cred(20);
			}
		}else if(iiid==1){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Blue Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).cblue(20);
			}
		}else if(iiid==2){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: White Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).cwhite(20);
			}
		}else if(iiid==3){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Red_Mul Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).red_mul_p.push_back({1.25,3});
				(*x).red_mul.push_back({0.8,3});
			}
		}else if(iiid==4){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Blue_Mul Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).blue_mul_p.push_back({1.25,3});
				(*x).blue_mul.push_back({0.8,3});
			}
		}else if(iiid==5){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: White_Mul Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).white_mul_p.push_back({1.25,3});
				(*x).white_mul.push_back({0.8,3});
			}
		}else if(iiid==6){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Att Up\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).tmp_att_plus.push_back({3,3});
			}
		}else if(iiid==7){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Powerer hit\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).att_mul.push_back({1.25,3});
			}
		}else if(iiid==8){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Harmful hit\n");}
			for(auto y:beside_team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).be_att_mul.push_back({1.25,3});
			}
		}else if(iiid==9){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Comfort One\n");}
			int who=rand()%5;
			int tries=0;
			while(tries<10&&(who>=5||team[who]==NULL||((*(stud*)team[who]).status==0))){
				who=rand()%5;
				tries++;
			}
			if(who<5&&team[who]!=NULL){
				(*(stud*)team[who]).status=1;
				(*(stud*)team[who]).cblue(5);
				(*(stud*)team[who]).cred(5);
				(*(stud*)team[who]).cwhite(5);
				if(debug_on){logPrint(10,"[Apply Skill] Comfort One revived %s\n",((stud*)team[who])->name.c_str());}
			}
		}else if(iiid==10){
			if(debug_on){logPrint(10,"[Apply Skill] Applied Normal: Destory One\n");}
			int who=rand()%5;
			int tries=0;
			while(tries<10&&(who>=5||beside_team[who]==NULL||((*(stud*)beside_team[who]).status==0))){
				who=rand()%5;
				tries++;
			}
			if(who<5&&beside_team[who]!=NULL){
				(*(stud*)beside_team[who]).cblue(-5);
				(*(stud*)beside_team[who]).cred(-5);
				(*(stud*)beside_team[who]).cwhite(-5);
				if(debug_on){logPrint(10,"[Apply Skill] Destory One damaged %s\n",((stud*)beside_team[who])->name.c_str());}
			}
		}
	}else if(ct.type==2){  // 个人词条
		if(ct.targetIdx>=0&&ct.targetIdx<(int)team.size()){
			stud* x=(stud*)team[ct.targetIdx];
			if(x!=NULL){
				(*x).HavCt[ct.skillSlot]=1;
				if(debug_on){
					logPrint(10,"[Apply Skill] %s learned: %s (slot %d)\n",x->name.c_str(),ct.name.c_str(),ct.skillSlot);
				}
			}
		}
	}else if(ct.type==3){  // 稀有词条
		int iiid=ct.targetIdx;
		if(iiid==0){
			if(debug_on){logPrint(13,"[Apply Skill] Applied Rare: Double Red Mul\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).red_mul_p.push_back({2,3});
				(*x).red_mul.push_back({0.5,3});
			}
		}else if(iiid==1){
			if(debug_on){logPrint(13,"[Apply Skill] Applied Rare: Double Blue Mul\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).blue_mul_p.push_back({2,3});
				(*x).blue_mul.push_back({0.5,3});
			}
		}else if(iiid==2){
			if(debug_on){logPrint(13,"[Apply Skill] Applied Rare: Double White Mul\n");}
			for(auto y:team){
				stud* x=(stud*)y;
				if((*x).status==0){continue;}
				(*x).white_mul_p.push_back({2,3});
				(*x).white_mul.push_back({0.5,3});
			}
		}else if(iiid==3){
			if(debug_on){logPrint(13,"[Apply Skill] Applied Rare: Lets Make Hero\n");}
			int who=rand()%5;
			int tries=0;
			while(tries<10&&(who>=5||team[who]==NULL||((*(stud*)team[who]).status==0))){
				who=rand()%5;
				tries++;
			}
			if(who<5&&team[who]!=NULL){
				(*(stud*)team[who]).status=1;
				(*(stud*)team[who]).tmp_att_plus.push_back({10,3});
				(*(stud*)team[who]).be_att_mul.push_back({0.5,3});
				if(debug_on){logPrint(10,"[Apply Skill] Lets Make Hero buffed %s\n",((stud*)team[who])->name.c_str());}
			}
		}
	}else if(ct.type==4){
		// 联动词条 (with_ct)
		if(debug_on){logPrint(6,"[Apply Skill] Link Ct (not implemented yet)\n");}
	}else if(ct.type==5){
		// 进化词条 (evolute_ct)
		if(debug_on){logPrint(4,"[Apply Skill] Evolve Ct (not implemented yet)\n");}
	}
}

// 主函数
void Lets_Choose_Ct(vector<void*> tA,vector<void*> tB,int num){
	color(7);
	while(num--){
		// Team A 抽词条
		vector<CtInfo> ctInfos;
		
		// 添加个人词条
		for(int i=0;i<(int)tA.size();i++){
			if(tA[i]==NULL){continue;}
			stud* x=(stud*)tA[i];
			if((*x).status==0){continue;}
			if(!(*x).HavCt[0]&&!(*x).ct2.empty()){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=0;
				info.name=(*x).ct2[0];
				ctInfos.push_back(info);
			}
			if(!(*x).HavCt[1]&&!(*x).ct1.empty()){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=1;
				info.name=(*x).ct1[0];
				ctInfos.push_back(info);
			}
			if((*x).ct1.size()>=2&&!(*x).HavCt[2]){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=2;
				info.name=(*x).ct1[1];
				ctInfos.push_back(info);
			}
		}
		
		// 添加普通词条作为填充
		while((int)ctInfos.size()<4){
			int iid=rand()%nc_cnt;
			CtInfo info;
			info.type=1;
			info.targetIdx=iid;
			info.skillSlot=-1;
			info.name=normal_ct[iid];
			ctInfos.push_back(info);
		}
		
		CtInfo ctA=Choose_Ct_Main(tA,ctInfos,true);
		
		// 显示选择结果
		gotoxy(0,21);
		color(10);
		Fix_Ct(tA,tB,ctA);
		if(ctA.type==2){printf("[Team A] %s learned: %s",
((stud*)tA[ctA.targetIdx])->name.c_str(),ctA.name.c_str());}
		else{printf("[Team A] Applied: %s",ctA.name.c_str());}
		color(7);
		
		gotoxy(0,22);
		printf("Press any key to continue...");
		getch();

		// 清空提示行
		gotoxy(0,21);
		for(int i=0;i<70;i++){printf(" ");}
		gotoxy(0,22);
		for(int i=0;i<70;i++){printf(" ");}
		
		// Team B 抽词条
		ctInfos.clear();
		
		for(int i=0;i<(int)tB.size();i++){
			if(tB[i]==NULL){continue;}
			stud* x=(stud*)tB[i];
			if((*x).status==0){continue;}
			if(!(*x).HavCt[0]&&!(*x).ct2.empty()){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=0;
				info.name=(*x).ct2[0];
				ctInfos.push_back(info);
			}
			if(!(*x).HavCt[1]&&!(*x).ct1.empty()){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=1;
				info.name=(*x).ct1[0];
				ctInfos.push_back(info);
			}
			if((*x).ct1.size()>=2&&!(*x).HavCt[2]){
				CtInfo info;
				info.type=2;
				info.targetIdx=i;
				info.skillSlot=2;
				info.name=(*x).ct1[1];
				ctInfos.push_back(info);
			}
		}
		
		while((int)ctInfos.size()<4){
			int iid=rand()%nc_cnt;
			CtInfo info;
			info.type=1;
			info.targetIdx=iid;
			info.skillSlot=-1;
			info.name=normal_ct[iid];
			ctInfos.push_back(info);
		}
		
		CtInfo ctB=Choose_Ct_Main(tB,ctInfos,false);
		
		// 显示选择结果
		gotoxy(0,21);
		color(9);
		Fix_Ct(tB,tA,ctB);
		if(ctB.type==2){printf("[Team B] %s learned: %s",
((stud*)tB[ctB.targetIdx])->name.c_str(),ctB.name.c_str());}
		else{printf("[Team B] Applied: %s",ctB.name.c_str());}
		color(7);
		
		gotoxy(0,22);
		printf("Press any key to continue...");
		getch();
		
		// 清空提示行
		gotoxy(0,21);
		for(int i=0;i<70;i++){printf(" ");}
		gotoxy(0,22);
		for(int i=0;i<70;i++){printf(" ");}
	}
}

#endif //__EXPERI_H__