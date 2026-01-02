#include "A0.h"

class stud_B11:public stud{
	public:
		stud_B11(){
			red_up+=4,blue_up+=0,white_up+=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			py.push_back(8);
			py.push_back(14);
			ct1.pb("叛变");
			ct1.pb("嘉宾");
			ct1.pb("差一脚");
			ct1.pb("歌喉");
			id=24;
			name="B11";
		}
};
