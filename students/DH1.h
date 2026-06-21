#include"A0.h"

class stud_DH1:public stud{
    private:
    bool have_leaf;
    public:
    stud_DH1(){
        red_up+=15,blue_up-=20,white_up-=10;
        red=red_up,blue=blue_up,white=white_up;
        att-=2;
        have_leaf=0;
        ct1.pb("Play?withleaf");
        have_leaf=0;
        ct1.pb("NBestOIer");
        ct2.pb("Deletecode");
        id=29;
        name="DH1";
    }
    virtual Return_Hit before_att(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
		Return_Hit return_num=stud::before_att(target,teach,team,beside_team);
		
		if(HavCt[2]){
			int wh=(*target).id;
			if(wh==1||wh==3||wh==103||wh==12||wh==9||wh==26){
				(*target).cred(-5);
				(*target).cblue(-5);
				(*target).cwhite(-5);
				cred(5);
				cblue(5);
				cwhite(5);
			}
		}
		
		return return_num;
	}
    void on_turn_start(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
        stud::on_turn_start(target,teach,team,beside_team);
        if(HavCt[1]){
		for(auto x:team){
            if(x -> id == 26){
                cwhite(-10);
                cblue(10);
                (*x).cred(30);
                (*x).cant_act+=1;
                (*x).can_act=0;
                for(auto y:beside_team)
                	(*y).att_rt.update(pair<int,pair<pair<double,void*>,int>>{4,{{0.4,x},1}});
                break;
            }
        }}
		if(HavCt[2]){if(Dtee().second==1){
                if(teach==9){
                    tmp_att_plus.push_back({3,3});
                    att_rt.update(pair<int,pair<int,int>>{1,{40,2}});
                    cred(10);
                }
            }}
    }
    void skhit(stud* target,int teach,vector<stud*>team,vector<stud*>beside_team){
        stud::skhit(target,teach,team,beside_team);
        int a=rand();
        if(a%1000==78){
            exit(1);
        }
        else{
        	(*target).cred(50);
        	for(auto y:beside_team){
        		if((*y).id!=(*target).id)(*y).cred(-20);
			}
            cblue(-25);
            cwhite(-25);
        }
    }
};
