#include "A0.h"

class stud_B4:public stud{
	public:
		stud_B4(){
			red_up-=26,blue_up+=0,white_up+=64;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			ct1.pb("甜菜");
			ct2.pb("扒皮");
			ct1.pb("国际友人");
			ct1.pb("牢王");
			id=17;
			name="B04";
		}
};
