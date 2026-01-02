#include "A0.h"

class stud_B15:public stud{
	public:
		stud_B15(){
			red_up+=2,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=2; 
			py.push_back(2);
			ct1.pb("好雨");
			id=28;
			name="B15";
		}
};
