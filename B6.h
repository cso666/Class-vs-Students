#include "A0.h"

class stud_B6:public stud{
	public:
		stud_B6(){
			red_up-=4,blue_up+=5,white_up-=8;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct1.pb("CADB");
			ct1.pb("自行车");
			ct1.pb("老干");
			id=19;
			name="B06";
		}
};
