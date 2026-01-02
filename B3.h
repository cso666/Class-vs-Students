#include "A0.h"

class stud_B3:public stud{
	public:
		stud_B3(){
			red_up+=0,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			py.push_back(1);
			ct1.pb("助教先生");
			ct1.pb("心平气和");
			ct1.pb("数学双星");
			id=16;
			name="B03";
		}
};
