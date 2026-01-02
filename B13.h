#include "A0.h"

class stud_B13:public stud{
	public:
		stud_B13(){
			red_up-=20,blue_up+=20,white_up-=30;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			py.push_back(8);
			py.push_back(9);
			py.push_back(14);
			py.push_back(15);
			ct1.pb("Take it easy…");
			ct1.pb("108 or lower");
			ct1.pb("Maimai go home");
			ct1.pb("Songs are life!");
			ct1.pb("Knowledge is power");
			id=26;
			name="B13";
		}
};
