#include "A0.h"
extern bool debug_on;
extern void logPrint(int colorCode,const char*format,...);

class stud_B13:public stud{
private:
	bool takeItEasy_active=0;
	bool is_away=0;
	int original_att;

public:
	stud_B13(){
		red_up-=20,blue_up+=20,white_up-=30;
		red=red_up,blue=blue_up,white=white_up;
		att-=2;
		original_att=att;
		takeItEasy_active=0,is_away=0;
		py.push_back(8);
		py.push_back(9);
		ct1.pb("TakeItEasy...");
		//ct1.pb("108 or lower");
		//ct1.pb("Maimai go home");
		ct1.pb("SongsAreLife!");
		ct2.pb("KnowledgeIsPowDer");
		id=26;
		name="B13";
	}

	void on_day_start(){// 每天开始时调用
		if(rand()%100<15){
			takeItEasy_active=1;
			if(debug_on){logPrint(12,"[B13] TakeItEasy... activated! Will lose 10 sanity per turn.\n");}
		}else{takeItEasy_active=0;}
	}// TakeItEasy... 判定
	
	void on_class_start(int subject_id){
		bool is_music_subject=(subject_id==10||subject_id==13||subject_id==12||subject_id==7||subject_id==11);
		
		if(is_music_subject){
			if(rand()%100<80){
				is_away=1;
				if(debug_on){logPrint(10,"[B13] %s goes to listen to music! Away from battle.\n",name.c_str());}
			}else{
				is_away=0;
				att=original_att+6;
				if(debug_on){logPrint(10,"[B13] %s feels inspired! Attack +6.\n",name.c_str());}
			}
		}else{
			is_away=0;
			att=original_att;
		}
	}// SongsAreLife! 判定（美/地/生/体/音 = 10/13/12/7/11）
	
	// 每回合开始时
	void on_turn_start(stud* target,int teach,vector<stud*> team,vector<stud*> beside_team) override {
		stud::on_turn_start(target,teach,team,beside_team);
		if(takeItEasy_active){
			cblue(-10);
			if(debug_on){logPrint(12,"[B13] TakeItEasy... active! -10 sanity. Current: %d\n",blue);}
		}
	}
	
	// 检查是否退场（用于战斗选择时排除）
	bool isAway()const{return is_away;}
	
	// 重置状态
	void resetDaily(){
		takeItEasy_active=0,is_away=0;
		att=original_att;
	}
	void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		stud::skhit(target,teach,team,beside_team);
		
	}
};