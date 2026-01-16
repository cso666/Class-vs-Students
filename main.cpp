#include"headers.h"
#include"student.h"
//注意！需要图标的话用project文件夹下的compile.bat编译，调试时可以使用Devc++. 
#include"teacher.h"
#define sslp(n) Sleep(n*1000)

using namespace std;

int sbj_teacher;//老师 
map<string,int> subj;string subj2[13+10];//学科

int day,clas;

bool isalive[28+1];
vector<void*> stud_list;
vector<void*> listA,listB;
int Anum=5,Bnum=5;

void gotoxy(int x,int y){
	HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(hout,pos);
}
long long color(long long c){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}
void ppput(const char*s,float k){
	unsigned leng=strlen(s);
	for(unsigned i=0;i<leng;i++){
		cout<<s[i];
		sslp(k);
	}
}

int nowy=2;
bool timeOfStarting=0;

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
void hitt(void* f1,void* f2,vector<void*> T1,vector<void*> T2){
	stud* ta=(stud*)f1;
	stud* tb=(stud*)f2;
	vector<stud*>t1,t2;
	for(auto y:T1)t1.push_back((stud*)y);
	for(auto y:T2)t2.push_back((stud*)y);
	
	int sit1=(*ta).before_att(tb,sbj_teacher,t1,t2);
	int sit2=(*tb).on_before_be_atted(ta,sbj_teacher,t2,t1);
	if(sit1==1||sit2==1)return;
	
	int final_att=((*ta).att*(*ta).att_mul*(*tb).be_att_mul+(*ta).tmp_att_plus);
	(*tb).red-=final_att;
	(*ta).white-=5*((*ta).white_mul);
	(*ta).after_att(tb,sbj_teacher,t1,t2);
	(*tb).on_minus_red(ta,sbj_teacher,t2,t1);
	//(*tb).red-=int((*ta).att*(*ta).att_mul);
	//(*ta).white-=5;
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
	vector<stud*> teamA_stud, teamB_stud;
	for(auto ptr : lA) teamA_stud.push_back((stud*)ptr);
	for(auto ptr : lB) teamB_stud.push_back((stud*)ptr);
	
	for(auto player : lA) {
	    ((stud*)player)->on_turn_start(nullptr, sbj_teacher, teamA_stud, teamB_stud);
	}
	for(auto player : lB) {
  	  ((stud*)player)->on_turn_start(nullptr, sbj_teacher, teamB_stud, teamA_stud);
	}
		void* ta;void* tb;void* tc;void *td;
		system("cls");
		sett(lA,lB);
		//战斗！
		
		cout << "teamA choose your fighter and the goal:";	
		int a,b;
		F1:
		cin >>a>>b;
		if(0<=a&&a<lena&&0<=b&&b<lenb && isalive[(*((stud*)lA[a])).id] && isalive[(*((stud*)lB[b])).id])
			ta=lA[a],tb=lB[b];
		else {cout<<"incorrct!choose again!\n";goto F1;}

		cout << "teamB choose your fighter and the goal:";
		int c,d;
		F2:
		cin >>c>>d;
		if(0<=c&&c<lenb&&0<=d&&d<lena && isalive[(*((stud*)lB[c])).id] && isalive[(*((stud*)lA[d])).id])
			tc=lB[c],td=lA[d];
		else {cout << "incorrct!choose again!\n";goto F2;}
		
		hitt(ta,tb,lA,lB);
		hitt(tc,td,lB,lA);
		//死亡判定
		for(int i=0;i<lA.size();i++){
			tmp=(stud*)lA[i];
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
		for(int i=0;i<lB.size();i++){
			tmp=(stud*)lB[i];
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
	cout << "teamA turn,you can choose 3students:";
	while(lA.size()<3){
		cin >> s;
		while(s<0||s>4||isc1[s]==1) cout <<"NO!choose again!:",cin >> s;
		lA.push_back(listA[s]);
		isc1[s]=1;
	}
	cout << "teamB turn,you can choose 3students:";
	while(lB.size()<3){
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

void startASCIIart(){
	cout<<"\
       _\n\
      / \n\
     |    \n\
      \\_";
    sslp(0.2);
    ppput("lass",0.15);
    sslp(0.4);
    system("cls");
    cout<<"\
             _\n\
            /\n\
            \\  \n\
          __/";
    sslp(0.2);
    ppput("tudents",0.15);
    sslp(0.4);
    system("cls");
	cout<<"\
       _    /_ \n\
      /    //\n\
     | \\  / \\  \n\
      \\_\\/__/  ";
    gotoxy(2,5);
    sslp(0.2);
    ppput("Class vs. Students",0.06);
	sslp(1);
	color(4);
	gotoxy(7,2);
	cout<<"\\  /";
	gotoxy(8,3);
	cout<<"\\/";
	gotoxy(11,1);
	cout<<"/";
	gotoxy(12,0);
	cout<<"/";
	gotoxy(2,5);
	cout<<"Class vs. Students";
	gotoxy(0,7);
	color(7);
	cout<<"Press any key to start...";
	getch();
}

int main(){
	srand(time(nullptr)*rand());
	/*startASCIIart();

start:
	system("cls");
	cout<<"\
  Class vs. Students v0.25\n\
    ----------------------\n\
    |     Start Game     |\n\
    ----------------------\n\
    ----------------------\n\
    |        Rule        |\n\
    ----------------------\n\
    ----------------------\n\
    |     Our Github     |\n\
    ----------------------\n\
    ----------------------\n\
    |        Exit        |\n\
    ----------------------\n\
";
	if(!timeOfStarting){sslp(0.8);}
	timeOfStarting=1;
	gotoxy(1,nowy);
	cout<<"->";
	char cstart=getch();
	while(cstart!='\r'&&cstart!='\n'){
		if(cstart==0||cstart==224||cstart==-32){
			cstart=getch();
			gotoxy(1,nowy);
			cout<<"  ";
			if(nowy<11&&cstart==80){nowy+=3;}
			else if(nowy>2&&cstart==72){nowy-=3;}
			gotoxy(1,nowy);
			cout<<"->";
		}
		cstart=getch();
	}
	if(nowy==5){
		//You guys write the code here, I can't do it.
		//Actually here's the game rule.
		goto start;
	}else if(nowy==8){
		system("start https://github.com/cso666/Class-vs-Students");
		goto start;
	}else if(nowy==11){
		gotoxy(13,11);
		cout<<"    \b\b\b\b";
		ppput("BYE!",0.2);
		gotoxy(0,13);
		return 0;
	}
	
	system("cls");
	cout<<"\
        Are you ready?\n\
    ----------------------\n\
    |  YES, Let's go!!!  |\n\
    ----------------------\n\
\n\
    ----------------------\n\
    |         NO         |\n\
    ----------------------\n\
";
	sslp(0.8);
	gotoxy(1,2);
	cout<<"->";
	char cnextt=getch();bool starttttt=0;
	while(cnextt!='\r'&&cnextt!='\n'){
		if(cnextt==0||cnextt==224||cnextt==-32){
			cnextt=getch();
			if(starttttt==0&&cnextt==80){
				gotoxy(1,2);
				cout<<"  ";
				gotoxy(1,6);
				cout<<"->";
				starttttt=1;
			}else if(starttttt==1&&cnextt==72){
				gotoxy(1,6);
				cout<<"  ";
				gotoxy(1,2);
				cout<<"->";
				starttttt=0;
			}
		}
		cnextt=getch();
	}
	if(starttttt){
		gotoxy(4,1);
		ppput("                      ",0.02);
		gotoxy(4,2);
		ppput("                      ",0.02);
		gotoxy(4,3);
		ppput("                      ",0.02);
		gotoxy(2,3);
		ppput("Seems' you're not ready yet.",0.05);
		sslp(0.4);
		system("cls");
		goto start;
		return 0;
	}
	gotoxy(4,5);
	ppput("                      ",0.02);
	gotoxy(4,6);
	ppput("                      ",0.02);
	gotoxy(4,7);
	ppput("                      ",0.02);
	gotoxy(12,6);
	ppput("READY?",0.2);
	sslp(1);
	system("cls");
	gotoxy(13,6);
	cout<<"GO!!";
	sslp(1.5);*/
	
	system("cls");
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
