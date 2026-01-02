#include "A0.h"

class stud_B12:public stud{
	public:
		stud_B12(){
			red_up-=4,blue_up-=0,white_up+=8;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct1.pb("？王");
			id=25;
			name="B12";
		}
};
