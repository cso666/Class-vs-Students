//zi4 fu2 hua4 ce4 shi4
//DONNOT DELETE

/*
            /
       /ˉ //ˉ
      | \ //_
       \_v__/

       /ˉ
      |
       \_lass
    
            /ˉ
           /_
          __/tudents

            /
       /ˉ //ˉ
      | \ //_
       \_v__/
  Class vs. Students

*/

/*main:

        Are you ready?
    ----------------------
 -> |  YES, Let's go!!!  |
    ----------------------

    ----------------------
    |         NO         |
    ----------------------

*/

#include"headers.h"
using namespace std;
#define sslp(xx) Sleep(xx*1000)

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
int main(){
//	while(1){
//		char cc=getch();
//		cout<<(int)cc<<'\n';
//	} 
/*
	cout<<"\n\
      /ˉ \n\
     |    \n\
      \\_";
    sslp(0.2);
    ppput("lass",0.15);
    sslp(0.4);
    system("cls");
    cout<<"\n\
            /ˉ\n\
            \\  \n\
          __/";
    sslp(0.2);
    ppput("tudents",0.15);
    sslp(0.4);
    system("cls");
	cout<<"\
            /  \n\
      /ˉ  //ˉ\n\
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
	getch();*/
start:
	system("cls");
	cout<<"\
  Class vs. Students v0.14.1\n\
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
	return 0;
}
