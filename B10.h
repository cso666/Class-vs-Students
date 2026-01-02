#include "A0.h"

class stud_B10:public stud{
	public:
		stud_B10(){
			red_up-=4,blue_up-=20,white_up-=2;
			red=red_up,blue=blue_up,white=white_up;
			att-=3;
			ct1.pb("主观");
			ct1.pb("你不应该……");
			id=23;
			name="B10";
		}
};
