#include"headers.h"
#include"student.h"
//注意！需要图标的话用project文件夹下的compile.bat编译，调试时可以使用Devc++. 
#include"teacher.h"


using namespace std;

int sbj_teacher;//老师 
map<string,int> subj;string subj2[13+10];//学科

int day,clas;

bool isalive[28+1];
vector<void*> stud_list;
vector<void*> listA,listB;
int Anum=5,Bnum=5;

void* choose(int id){
	if(id==1) return &t1;
	if(id==2) return &t2;
	if(id==3) return &t3;
	if(id==4) return &t4;
	if(id==5) return &t5;
	if(id==6) return &t6;
	if(id==7) return &t7;
	if(id==8) return &t8;
	if(id==9) return &t9;
	if(id==10) return &t10;
	if(id==12) return &t12;
	if(id==13) return &t13;
	if(id==14) return &t14;
	if(id==15) return &t15;
	if(id==16) return &t16;
	if(id==17) return &t17;
	if(id==18) return &t18;
	if(id==19) return &t19;
	if(id==20) return &t20;
	if(id==21) return &t21;
	if(id==22) return &t22;
	if(id==23) return &t23;
	if(id==24) return &t24;
	if(id==25) return &t25;
	if(id==26) return &t26;
	if(id==27) return &t27;
	if(id==28) return &t28; 
}
void hitt(void* f1,void* f2){
	stud* ta=(stud*)f1;
	stud* tb=(stud*)f2;
	(*tb).red-=int((*ta).att*(*ta).att_mul);
	(*ta).white-=5;
} 

void init(){//初始化 
	
	subj["chinese"]=1,subj2[1]="chinese";
	subj["math"]=2,subj2[2]="math";
	subj["EnglishA"]=3,subj2[3]="EnglishA";
	subj["EnglishB"]=4,subj2[4]="EnglishB";
	subj["history"]=5,subj2[5]="history";
	subj["politics"]=6,subj2[6]="politics";
	subj["pe"]=7,subj2[7]="pe";
	subj["physics"]=8,subj2[8]="physics";
	subj["ict"]=9,subj2[9]="ict";
	subj["art"]=10,subj2[10]="art";
	subj["music"]=11,subj2[11]="music";
	subj["biology"]=12,subj2[12]="biology";
	subj["geography"]=13,subj2[13]="geography";
	
	sbj_teacher=rand()*rand()%13+1;cout << "your teacher is--"<<subj2[sbj_teacher]<<endl;
	
	isalive[11]=1;
	while(stud_list.size()<16){
		int tr=rand()*rand()%28+1;
		while(isalive[tr]) tr%=28,tr++;
		isalive[tr]=1;
		stud_list.push_back(choose(tr));
	}
	
	cout << "choose your student:\n";
	int xi=0;
	for(auto x:stud_list){
		stud y=(*(stud*)x);
		cout << "\tNumber"<<xi<<' '<<y.name<<' '<<y.red_up<<' '<<y.blue_up<<' '<<y.white_up<<' '<<y.att<<endl; 
		xi++;
	}
	
	for(int i=0;i<stud_list.size();i++){
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py) if(j==sbj_teacher){
			(*tmp).att_mul+=0.2;
		} 
	}
}
void team_chs(){//分队
	int s;
	bool isc[16+10]={0};
	while(listB.size()<5){
		cout << "teamA turn,type your choose:";
		cin >> s;
		while(isc[s]) cout <<"NO!choose again!:",cin >> s;
		listA.push_back(stud_list[s]);
		isc[s]=1;
		
		cout << "teamB turn,type your choose:";
		cin >> s;
		while(isc[s]) cout <<"NO!choose again!:",cin >> s;
		listB.push_back(stud_list[s]);
		isc[s]=1; 
	}
	cout << "this is the choose:\n";
	cout << "\tteamA: ";
	for(auto x:listA){
		stud y=(*(stud*)x);
		cout <<y.name<<' ';
	}cout << endl;
	cout << "\tteamB: ";
	for(auto x:listB){
		stud y=(*(stud*)x);
		cout <<y.name<<' ';
	}cout << endl;
	cout << "if you are ready to play,type \'1\':";
	int ready_question;cin >> ready_question;
	if(ready_question!=1) cout << "NO!you must be ready!\n";
	else {
		cout << "OK!Lets go!\n";
		Sleep(2000);
		system("cls");
	}
}
void sett(vector<void*> lA,vector<void*> lB){//战斗输出字符画
	printf("Day %d , Class %d:",day,clas);cout << subj2[classtable[day-1][clas-1]]<<endl;
	cout << "----------------------------------------------------------------------------------------------------\n"; 
	for(auto x:lA){
		stud y=(*(stud*)x);
		cout <<y.name;
		printf(" att:%02d     ||",int(y.att*y.att_mul));
	}cout << endl;
	for(auto x:lA){
		stud y=(*(stud*)x);
		printf("hp: %03d/%03d/%03d||",y.red,y.blue,y.white);
	}cout << endl;
	cout << "\nVS\n\n";
	for(auto x:lB){
		stud y=(*(stud*)x);
		cout <<y.name;
		printf(" att:%02d     ||",int(y.att*y.att_mul));
	}cout << endl;
	for(auto x:lB){
		stud y=(*(stud*)x);
		printf("hp: %03d/%03d/%03d||",y.red,y.blue,y.white);
	}cout << endl;
	cout << "----------------------------------------------------------------------------------------------------\n";
}
void turn(int timE,vector<void*> lA,vector<void*>lB){//战斗回合
	int lena=lA.size(),lenb=lB.size();
	while(timE--){
		system("cls");
		sett(lA,lB);
		//战斗！ 
		cout << "teamA choose your fighter and the goal:";
		int a,b;
		F1:
		cin >>a>>b;
		if(0<=a&&a<lena&&0<=b&&b<lenb && isalive[(*((stud*)listA[a])).id] && isalive[(*((stud*)listB[b])).id]){
			void* ta=listA[a];
			void* tb=listB[b];
			hitt(ta,tb);
		}
		else {cout<<"incorrct!choose again!\n";goto F1;}
		cout << "teamB choose your fighter and the goal:";
		int c,d;
		F2:
		cin >>c>>d;
		if(0<=c&&c<lenb&&0<=d&&d<lena && isalive[(*((stud*)listB[c])).id] && isalive[(*((stud*)listA[d])).id]){
			void* tc=listB[c];
			void* td=listA[d];
			hitt(tc,td);
		}
		else {cout << "incorrct!choose again!\n";goto F2;}
		//死亡判定 
		for(int i=0;i<listA.size();i++){
			tmp=(stud*)listA[i];
			if((*tmp).red<=0||(*tmp).white<=0){
				if(isalive[(*tmp).id]==1)Anum-=1;
				isalive[(*tmp).id]=0;
				(*tmp).red=-1;
				(*tmp).blue=-1;
				(*tmp).white=-1;
				(*tmp).att=-1;
				(*tmp).att_mul=1.0;
			}
		}
		for(int i=0;i<listB.size();i++){
			tmp=(stud*)listB[i];
			if((*tmp).red<=0||(*tmp).white<=0){
				if(isalive[(*tmp).id]==1) Bnum-=1;
				isalive[(*tmp).id]=0;
				(*tmp).red=-1;
				(*tmp).blue=-1;
				(*tmp).white=-1;
				(*tmp).att=-1;
				(*tmp).att_mul=1.0;
			}
		}
		if(Anum<=0||Bnum<=0) break;
	}
	sett(lA,lB);
}

void fight(int day,int cla){
	if(day==5&&cla>=7) return;
	if(cla==8){
		cout << "\n this time is late-self-learning,we all need fight!\n";
		turn(8,listA,listB);
		return;
	}
	cout << "\nthis class is:"<<subj2[classtable[day][cla]]<<",lets choose your team!\n";
	sett(listA,listB);
	for(int i=0;i<stud_list.size();i++){
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py) if(j==classtable[day][cla]){
			(*tmp).att_mul+=0.5;
		} 
	}
	
	vector<void*> lA,lB;
	int s;
	bool isc1[16+10]={0},isc2[16+10]={0};
	while(lB.size()<3){
		cout << "teamA turn,type your choose:";
		cin >> s;
		while(s<0||s>4||isc1[s]==1) cout <<"NO!choose again!:",cin >> s;
		lA.push_back(listA[s]);
		isc1[s]=1;
		
		cout << "teamB turn,type your choose:";
		cin >> s;
		while(s<0||s>4||isc2[s]==1) cout <<"NO!choose again!:",cin >> s;
		lB.push_back(listB[s]);
		isc2[s]=1; 
	}
	cout << "this is the choose:\n";
	cout << "\tteamA: ";
	for(auto x:lA){
		stud y=(*(stud*)x);
		cout <<y.name<<' ';
	}cout << endl;
	cout << "\tteamB: ";
	for(auto x:lB){
		stud y=(*(stud*)x);
		cout <<y.name<<' ';
	}cout << endl;
	turn(3,lA,lB);
	for(int i=0;i<stud_list.size();i++){
		tmp=(stud*)(stud_list[i]);
		for(int j:(*tmp).py) if(j==classtable[day][cla]){
			(*tmp).att_mul-=0.5;
		} 
	}
	
	return;
} 

int main(){
	srand(time(nullptr)*rand());
	cout << "Are you ready?\nyes:type 1\tno:type0 ";
	int start_question;cin >> start_question;
	if(start_question!=1) return 0;  
	cout << "ready?";Sleep(1000);cout << "Go!\n";
	init();
	team_chs();
	while(Anum>0&&Bnum>0){
		for(day=1;day<=5;day++){
			for(clas=1;clas<=8;clas++){
				if(Anum<=0||Bnum<=0) continue;
				if(clas==5||clas==8)
					for(int i=0;i<stud_list.size();i++){//中饭和晚饭回复体力 +20
						tmp=(stud*)(stud_list[i]);
						(*tmp).white+=20;
						(*tmp).white=min((*tmp).white,(*tmp).white_up);
					}
				for(int i=0;i<stud_list.size();i++){//下课回复理智 +5
					tmp=(stud*)(stud_list[i]);
					(*tmp).blue+=5;
					(*tmp).blue=min((*tmp).blue,(*tmp).blue_up);
				}
				fight(day-1,clas-1);
			}
			for(int i=0;i<stud_list.size();i++){//周末回复RBW 
				tmp=(stud*)(stud_list[i]);
				//体力回满 
				(*tmp).white=(*tmp).white_up;
				//理智 +20 
				(*tmp).blue+=20;
				(*tmp).blue=min((*tmp).blue,(*tmp).blue_up);
				//如果血量小于上限的20%则改为上限20%，否则 +20 
				if((*tmp).red<0.2*(*tmp).red_up) (*tmp).red=0.2*(*tmp).red_up;
				else (*tmp).red+=20;
				(*tmp).red=min((*tmp).red,(*tmp).red_up);
			}
		}	
	}
	if(Anum<=0&&Bnum<=0) cout << "PingJu.";
	else if(Anum<=0)cout << "Bwin!";
	else if(Bnum<=0)cout << "Awin!";
	Sleep(20000);
	system("cls");
	return 0;
}
