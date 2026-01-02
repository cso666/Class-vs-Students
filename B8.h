#include "A0.h"

class stud_B8:public stud{
	public:
		stud_B8(){
			red_up+=8,blue_up-=2,white_up+=4;
			red=red_up,blue=blue_up,white=white_up;
			att+=0;
			py.push_back(14);
			ct2.pb("叛变");
			ct1.pb("faith");
			ct1.pb("孔乙己");
			ct2.pb("打架吗");
			id=21;
			name="B08";
		}
};
