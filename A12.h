#include "A0.h"

class stud_A12: public stud{
	public:
		stud_A12(){
			red_up+=10;blue_up+=10;white_up-=20;
			red=red_up;blue=blue_up;white=white_up;
			att+=0;
			py.push_back(15);
			py.push_back(19);
			ct1.pb("我吃好了");
			ct1.pb("并非蠢货");
			ct1.pb("酸奶");
			ct2.pb("附魔金苹果");
			id=12;
			name="A12";
		}
};
