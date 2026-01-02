#include "A0.h"

class stud_B2:public stud{
	public:
		stud_B2(){
			red_up-=7,blue_up-=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			py.push_back(13);
			ct1.pb("顶嘴");
			ct2.pb("犬吠");
			ct1.pb("身高优势");
			ct1.pb("朗诵家");
			id=15;
			name="B02";
		}
};
