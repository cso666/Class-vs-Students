#include "A0.h"

class stud_B5:public stud{
	public:
		stud_B5(){
			red_up+=2,blue_up+=6,white_up-=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=1;
			ct1.pb("回家");
			ct1.pb("pi gu");
			ct1.pb("emo");
			id=18;
			name="B05";
		}
};
