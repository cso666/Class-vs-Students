#ifndef __GUIDE_H__
#define __GUIDE_H__
#define __GUIDE_H_ver__ 5

struct stuDis{
    const char*name;
    const char*hp;
    const char*san;
    const char*sta;
    const char*atk;
    const char*passive;
    const char*active;
};
static stuDis stuDesc[]={
    // id=1  A01
    {"A01","125","100","100","15",
     "[Small Luck]: 5% chance for +5 ATK and stun target for 1 turn.\n[Tired]: 1.25x stamina cost.",
     "{Lemon So Sour}: -30 HP self; -15 MAX HP target (1 class)."},
    // id=2  A02
    {"A02","100","120","100","18",
     "[Unconnect]: Cannot act when SAN <= 40.\n[Subjective]: +5 ATK vs B10; -24 SAN self.",
     "{Parents Gone}: -30 STA; 2x ATK; 80% chance of -15 self damage; Damage  |\n| cap 45."},
    // id=3  A03
    {"A03","120","105","110","2",
     "[Become Red]: Attacker/defender takes 1.30x damage next turn.\nOn 3 triggers, target goes insane, A03 -20 SAN.\n[Things Disappeared]: 50% per turn: -5 STA, +5 HP, +30 SAN.",
     "{Your Mother}: , -25 SAN self; -5 HP target; marked target takes  |\n| -15 SAN extra and 1.05x SAN damage when attacked by A03 (1 day)."},
    // id=4  A04
    {"A04","60","100","100","5",
     "[Fast]: 20% chance to nullify incoming attacks.\n[Mice Shout]: -3 SAN to all enemies at start of each turn.\n[Weak]: Takes 1.25x damage.",
     "{Snack Theft}: -20 STA; ATK temporarily set to 7; Damage cap 12."},
    // id=5  A05
    {"A05","130","120","100","15",
     "[Middle Luck]: 10% chance for +5 ATK and stun target for the class.\n[Strong]: Immune to all healing except from A09.",
     "{Mamba Out}: -15 STA; +5 SAN self; -25 HP target."},
    // id=6  A06
    {"A06","90","100","100","10",
     "[LaoDa]: Takes 0.78x damage from LaoMen; deals 1.1x damage to them.\n[LoseJ]: Immune to SAN damage; nearby allies take 1.1x SAN effects.",
     "{EarlyWarning}: -5 STA; +5 SAN to two allies; -20 SAN target; target   |\n| takes 1.2x damage next turn."},
    // id=7  A07
    {"A07","280","200","200","1",
     "[GreatLuck]: Redirects 80% of ally damage to self.\n[Unbreakable]: First death: MAX HP->140, heal to 70 HP, STA->1.",
     "{RenShengA}: -5 STA; 20% chance to reflect original damage to attacker  |\n| (entire class)."},
    // id=8  A08
    {"A08","100","100","100","8",
     "[Turtle's Long Life]: Incoming damage capped at 18.\n[Brainstorm]: All allies gain 1.2x ATK each turn.\n[Six A+]: +4 ATK when all bars full.",
     "{Dimensional Strike}: vs LaoMen(once/day): -5 STA, 20% MAX HP damage;   |\n| else: -15 STA, 10% MAX HP damage, -1 SAN self."},
    // id=9  A09
    {"A09","85","110","180","12",
     "[Mr.Monitor]: 1.35x ATK for all allies; +10 damage cap on first turn of\neach class if A09 is sane.\n[Peacemaker]: 9% chance to nullify incoming damage to any ally.\n[Abundant Support]: A09's attacks with damage >=18 can also lead to\n-20 SAN, -10 STA target.",
     "{Find Out}: -5 STA; ATK=10 (temporary); damage cap 40; all allies heal  |\n| 1/3 of damage dealt."},
    // id=10 A10
    {"A10","80","100","120","10",
     "[Sugar But Smart]: Each attack gives the target +1 Sugar counter;\nwhen A10 dies, all enemies take Sugarx2 damage.\n[Stay]: SAN loss x0.8; SAN gain x1.2.",
     "{Big Shoot}: Used at turn 1/2/3: loses turns until turn 3, then have an |\n| auto-attack with ATK=16 and multiplier 3/2/1, no damage cap; costs\n| 30/17/5 STA."},
    // 木昆木
    {"GUNMU","GUNMU","GUNMU","GUNMU","GUNMU","GUNMU","GUNMU"},
    // id=12 A12
    {"A12","110","80","110","10",
     "[Eat Well]: End of day: restore (Math classes today x5) HP.\n[Not Stupid]: Damage taken = max(0, (150-SAN)/150 x damage).\n[YogHURT]: Attacked A08, other enemies take (rand%40)% of the damage.",
     "{Enchanted Golden Apple}: Once per game, no STA cost. Instantly restore |\n| 15 HP, +3 ATK; next 3 turns: +10 HP/SAN/STA, -1 ATK per turn."},
    // id=13 A13
    {"A13","90","90","130","9",
     "[We Are Legends]: ATK multiplier = max(1, team STA/500).\n[So Delicious]: Restore STA equal to hp taken.",
     "{Year Pig Weigh}: Requires STA >=70% max. No STA cost. First hit with   |\n| ATK=8 (cap 40), then ATK=18 for 3 turns or until STA <70%."},
    // id=14 B01
    {"B01","105","120","88","8",
     "[Catgirl]: Incoming damage reduced by 10-20% (B07 immune).\n[Nimble]: 0.85x stamina cost (except SwapSeat).\n[Madness]: SAN loss: 70% self, 15% each alive ally.",
     "{SwapSeat}: Fails vs B07. Success: +3 HP, -2 STA target. Fail: attack   |\n| with ATK+2, -5 STA. If target marked: remove mark, deal ATK+6 HP & -10  |\n| SAN, self ATK-1 permanently, heal +5, cost -7 STA."},
    // id=15 B02
    {"B02","100","93","100","12",
     "[TalkBack]: Takes 1.08x damage, 30% chance to reflect 60% damage.\n[Height Advantage]: When hit by >40%MAX HP damage, 30% chance to reduce\nby 70% but -12 STA.\n[Recitalist]: When killing an enemy, other enemies lose 8% current HP.",
     "{Barking}: -10 STA; ATK=10; -12 SAN target; target loses -5 SAN/turn    |\n| (rest of class)."},
    // id=16 B03
    {"B03","100","100","100","6",
     "[Tutor(TA)]: +2 ATK, +20% HP/SAN/STA caps when teacher is Math.\n[Calm&Composed]: +5 HP at end of each turn.\n[MathDUO]: +10% caps when A10 is on the same team.",
     "{HalfAngle}: ATK=5; +10 SAN, +10 STA self; -10 SAN, -10 STA target."},
    // id=17 B04
    {"B04","74","36","110","11",
     "[GeniusBEET]: Takes 0.8x damage.\n[ForeignFriend]: All allies -15% damage taken during English A/B.\n[LaoKing]: +20 STA, +20 SAN at end of class.\nUnaffected by subject effects.",
     "{BP}: ATK=4; heal HP equal to damage dealt."},
    // id=18 B05
    {"B05","102","100","106","9",
     "[pi2gu4]: 40% chance per turn to change HP/SAN/STA by +-10.\n[emo]: When SAN<=60%, take 0.6x damage but 40% chance to miss attacks.",
     "{GoHome}: -10 STA; skip the rest of this class, +10 HP at end of class."},
    // id=19 B06
    {"B06","96","92","105","random(0~14)",
     "[CADB]: Random ATK multiplier: 20% x0.6, 60% x1.0, 12% x1.28, 5% x1.8, \n2% x2.0, 1% x2.5.\n[Nazistent]: 1.2x stamina cost.",
     "{OldThousand}: ATK=9; hide opponent's HP/SAN/STA bars for this class."},
    // id=20 B07
    {"B07","104","86","106","11",
     "[CowStrength]: STAgain x1.3, SANgain x1.1; STAloss x0.9, SANloss x0.95.\n[Sigma]: Immune to CatGirl and Madness. Cannot be marked by SwapSeat.\n[BothHigh&Cold]: Immune to all ally buffs except A09.",
     "{ScythedDown}: -10 STA; attack target; if HP>=20% max, HP->20%, +6 ATK  |\n| this class; else if SAN>=20%max, SAN->20%, 1.8x damage this class; else |\n| SAN->20%. Once per class."},
    // id=21 B08
    {"B08","108","98","104","10",
     "[BreachOfFaith]: 10% damage reduction; 15% reduction and 90% be_att_mul\nduring English B.\n[KongyiJi]: During Math, lose 2xATK HP and ATK SAN, first attack ATKx2.",
     "{WantFight?}: -8 STA; both lose 15 SAN; ATK=14; +3 ATK for 3 turns, +2  |\n| HP/turn; after 3 turns -20 STA, -8 HP."},
    // id=22 B09
    {"B09","103","100","98","10",
     "[Adonis]: 1.5x ATK when A09 is on the same team.\n[Sad]: When HP<=65, 0.4x ATK and 0.2x be_att_mul; restore when HP>65.\n[Perfect...Miss...]: If any bar contains digit 2, +11 HP, +16 STA.",
     "{Fiddler}: -10 STA, +5 SAN; attack target; if actual damage>theoretical |\n| damage, self gain (diff) ATK permanently, target lose (diff/2) ATK      |\n| permanently. Once per target, once per 2 days."},
    // id=23 B10
    {"B10","96","80","98","7",
     "[Subjective]: ATK multiplier and be_att_mul x(1+0.2x alive) each turn.\n[Shouldn't...]: When insane, deal 5x(ATK x att_mul+tmp) damage (capped\n45) to all enemies, self HP x0.3.",
     "{UnforeseenDisaster}: -10 STA,-5 SAN per death; for each death, deal 6x |\n| damage and 4xSAN loss to enemies; attack target with ATK-2. Requires at |\n| least 1 death."},
    // id=24 B11
    {"B11","104","100","102","9",
     "[OneMoreFoot]: 99% chance to cancel lethal attack, target loses 5 SAN.\n[SongsTalent]: +10 SAN to all allies at start of each turn.",
     "{Guest}: -15 STA; target-5 SAN, -5 STA; all allies+5 SAN, +5 STA; all   |\n| enemies-5 SAN, -5 STA; 3 turns chance to mark enemies as not listening."},
    // id=25 B12
    {"B12","96","100","140","9",
     "[HitPlane]: After attack, +5 STA and +(white - target.white)/3 STA.\n[Letsrun]: -3 HP, +6 STA at start of each turn.\n[Undying]: First death: MAX HP-54, revive, counterattack for 2x damage.",
     "{ShakeXueBi}: Requires STA >=20 to use. -30 STA (if STA<30 becomes      |\n| exhausted). +10 SAN, +10 HP self; allies-12 SAN, -5 HP; enemies-15 SAN, |\n| -10 HP; target extra-5 SAN, -5 HP; 3 turns: +10 STA/turn, 1.2x damage   |\n| taken, marked not listening."},
    // id=26 B13
    {"B13","80","120","70","8",
     "[TakeItEasy...]: 15% chance per day to lose 10 SAN each turn.\n[SongsAreLife!]: During Art/Music/PE/Biology/Geography, 80% chance to\nleave battle, 20% chance +6 ATK.",
     "{KnowledgeIsPowDer}: Requires 20+ STA. Randomly costs 10/30 STA. Gains  |\n| +4/+8 ATK and 1.35x/2x damage. Extra -10 STA, target -15 SAN if STA     |\n| remains enough."},
    // id=27 B14
    {"B14","76","108","90","6",
     "[Baby]: count add 1 when hit.\n[Sorry]: When SAN<60, -3 tmp_att_plus, att_mul x(1+count x0.05).\n[Bambino]: Damage cap 10.",
     "{Self-healing}: Randomly heal 6 HP/SAN/STA to an ally."},
    // id=28 B15
    {"B15","102","100","100","8",
     "[PerfectRain]: Starts as SPR(with 3 Rain). Becomes GBR when hit. End of\nturn: SPR heals lowest HP ally; GBR damages highest HP enemy. \n[SkywardFireworks]: When an enemy dies, all allies gain 1.2x SAN/STA\n(crazy->SAN=1, exhausted->STA=1).",
     "{RainyDays}: Costs 15-20 STA. Self-8 SAN, -5 HP; target-14 SAN, -7 HP.  |\n| 50% chance to switch SPR/GBR. SPR heals +8 SAN, +5 HP; GBR deals extra  |\n| -8 SAN, -5 HP to both."}
};
const int stuDcnt=sizeof(stuDesc)/sizeof(stuDesc[0]);

void guide(){
	system("cls");
    checkProgress(5);  // 打开图鉴成就

	color(11);
	printf(R"---(+-------------------------------------------------------------------------+
|                              Guidance Book                              |
+-------------------------------------------------------------------------+)---");
	color(7);
	printf(R"---(
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | A01 | | A02 | | A03 | | A04 | | A05 | | A06 | | A07 | | A08 | | A09 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | A10 | | A12 | | A13 | | B01 | | B02 | | B03 | | B04 | | B05 | | B06 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
| | B07 | | B08 | | B09 | | B10 | | B11 | | B12 | | B13 | | B14 | | B15 | |
| +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ +-----+ |
)---");
	color(11);
	printf("+-------------------------------------------------------------------------+");
	color(14);
	printf(R"---(
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |
|                                                                         |)---");
	color(11);
	printf(R"---(
+-------------------------------------------------------------------------+
|            W/A/S/D to move the pointer, R to view game rules            |
|                       Esc to return the main page                       |
+-------------------------------------------------------------------------+)---");
	
	// 初始化光标位置 (0-8/0-2)
	int _cx=0,_cy=0;
	int studentId[3][9]={
		{1,2,3,4,5,6,7,8,9},
		{10,12,13,14,15,16,17,18,19},
		{20,21,22,23,24,25,26,27,28}
	};
	
	// 绘制高亮光标
	gotoxy(2+_cx*8,3+_cy*3);
	color(14);
	printf("+-----+");
	gotoxy(2+_cx*8,3+_cy*3+1);
	printf("|     |");
	gotoxy(2+_cx*8,3+_cy*3+2);
	printf("+-----+");
    gotoxy(4+_cx*8,3+_cy*3+1);
    if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
    else{printf("B%02d",studentId[_cy][_cx]-13);}
	color(7);

    stuDis& s0=stuDesc[0];
    
    gotoxy(2,14);
    color(14);
    printf("%s",s0.name);
    color(7);
    printf("  ");
    color(4);
    printf("%s",s0.hp);
    color(7);
    printf("/");
    color(3);
    printf("%s",s0.san);
    color(7);
    printf("/");
    color(15);
    printf("%s",s0.sta);
    color(7);
    printf("  ");
    color(6);
    printf("att:%s",s0.atk);
    color(7);

    // 被动技能
    gotoxy(2,16);
    color(7);
    const char*p=s0.passive;
    int line=16;
    while(*p&&line<=22){
        gotoxy(2,line);
        while(*p&&*p!='\n'){
            printf("%c",*p);
            p++;
        }
        if(*p=='\n'){p++;}
        line++;
    }
    
    // 主动技能
    gotoxy(2,++line);
    color(14);
    printf("%s",s0.active);
	
	char ch;
	do{
		ch=getch();
		if(ch==27){break;}
        bool a4_esp=0;
		
		// 清除当前高亮
        color(7);
		gotoxy(2+_cx*8,3+_cy*3);
		printf("+-----+");
		gotoxy(2+_cx*8,3+_cy*3+1);
		printf("|     |");
		gotoxy(2+_cx*8,3+_cy*3+2);
		printf("+-----+");
        gotoxy(4+_cx*8,3+_cy*3+1);
        if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
        else{printf("B%02d",studentId[_cy][_cx]-13);}
		
		// 移动光标
		if(ch=='w'||ch=='W'){_cy=(_cy==0)?2:_cy-1;a4_esp=0;}
        else if(ch=='s'||ch=='S'){_cy=(_cy==2)?0:_cy+1;a4_esp=0;}
        else if(ch=='a'||ch=='A'){_cx=(_cx==0)?8:_cx-1;a4_esp=0;}
        else if(ch=='d'||ch=='D'){_cx=(_cx==8)?0:_cx+1;a4_esp=0;}
        else if(ch=='r'||ch=='R'){system("start README.md");}
        else if(ch==13){
            int id=studentId[_cy][_cx];
            if(id==4){
                unlockChallenge(3);
                static bool espMode=0;
                espMode=!espMode;
                if(espMode){
                    a4_esp=1;
                    color(4);
                    gotoxy(2+_cx*8,3+_cy*3);
                    printf("+-----+");
                    gotoxy(2+_cx*8,3+_cy*3+1);
                    printf("|     |");
                    gotoxy(2+_cx*8,3+_cy*3+2);
                    printf("+-----+");
                    gotoxy(4+_cx*8,3+_cy*3+1);
                    color(228);
                    printf("A04");
                    color(7);
                    for(int i=13;i<23;i++){
                        gotoxy(2,i);
                        for(int j=0;j<72;j++){printf(" ");}
                    }
                    // 显示超能力者信息
                    gotoxy(2,14);
                    color(228);
                    printf("A04 [ESP]");
                    color(7);
                    gotoxy(2,16);
                    color(180);
                    printf("10`n^095|7");
                    color(7);
                    printf("/");
                    color(179);
                    printf("10e1[$h567");
                    color(7);
                    printf("/");
                    color(191);
                    printf("!061v0?/67");
                    color(7);
                    gotoxy(2,17);
                    color(182);
                    printf("att: 1~6f}0p56b");
                    color(7);
                    gotoxy(2,19);
                    color(4);
                    printf("Writ deep into CVS's heart is a name you do not know.");
                    gotoxy(2,20);
                    color(78);
                    printf("O@M`a*f5\\");
                    color(4);
                    printf("'s power overflows. You cannot yet command it.");
                    gotoxy(2,22);
                    printf("It's an unfathomable power that should be ");
                    color(78);
                    printf("i0^o@-e?&[s\\");
                    color(7);
                }else{
                    color(14);
                    gotoxy(2+_cx*8,3+_cy*3);
                    printf("+-----+");
                    gotoxy(2+_cx*8,3+_cy*3+1);
                    printf("|     |");
                    gotoxy(2+_cx*8,3+_cy*3+2);
                    printf("+-----+");
                    gotoxy(4+_cx*8,3+_cy*3+1);
                    printf("A04");
                    color(7);
                    for(int i=13;i<=24;i++){
                        gotoxy(2,i);
                        for(int j=0;j<72;j++){printf(" ");}
                    }
                    gotoxy(2,14);
                    color(7);
                    printf("A04 (Details coming soon)");
                }
            }
        }
        
        if(!a4_esp){
            for(int i=13;i<=24;i++){
                gotoxy(2,i);
                for(int j=0;j<72;j++){printf(" ");}
            }

            int id=studentId[_cy][_cx];
            if(id>=1&&id<=28&&stuDesc[id-1].name[0]!='\0'){
                for(int i=13;i<=24;i++){
                    gotoxy(2,i);
                    for(int j=0;j<72;j++){printf(" ");}
                }

                int id=studentId[_cy][_cx];
                if(id>=1&&id<=28&&stuDesc[id-1].name[0]!='\0'){
                    stuDis& s=stuDesc[id-1];
                    
                    gotoxy(2,14);
                    color(14);
                    printf("%s",s.name);
                    color(7);
                    printf("  ");
                    color(4);
                    printf("%s",s.hp);
                    color(7);
                    printf("/");
                    color(3);
                    printf("%s",s.san);
                    color(7);
                    printf("/");
                    color(15);
                    printf("%s",s.sta);
                    color(7);
                    printf("  ");
                    color(6);
                    printf("att:%s",s.atk);
                    color(7);

                    // 被动技能
                    gotoxy(2,16);
                    color(7);
                    const char*p=s.passive;
                    int line=16;
                    while(*p&&line<=22){
                        gotoxy(2,line);
                        while(*p&&*p!='\n'){
                            printf("%c",*p);
                            p++;
                        }
                        if(*p=='\n'){p++;}
                        line++;
                    }
                    
                    // 主动技能
                    gotoxy(2,++line);
                    color(14);
                    printf("%s",s.active);
                }
            }

            gotoxy(2+_cx*8,3+_cy*3);
            color(14);
            printf("+-----+");
            gotoxy(2+_cx*8,3+_cy*3+1);
            printf("|     |");
            gotoxy(2+_cx*8,3+_cy*3+2);
            printf("+-----+");
            gotoxy(4+_cx*8,3+_cy*3+1);
            if(studentId[_cy][_cx]<=13){printf("A%02d",studentId[_cy][_cx]);}
            else{printf("B%02d",studentId[_cy][_cx]-13);}
        }
		color(7);
	}while(1);
	
	system("cls");
	color(7);
}

#endif// __GUIDE_H__
