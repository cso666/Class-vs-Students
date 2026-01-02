#include "A0.h"

class stud_B1:public stud{
	public:
		stud_B1(){
			red_up-=0,blue_up-=4,white_up-=12;
			red=red_up,blue=blue_up,white=white_up;
			att-=2;
			ct1.pb("猫娘");
			ct1.pb("轻巧");
			ct1.pb("不耐烦");
			ct2.pb("红温");
			ct2.pb("魔怔");
			id=14;
			name="B01";
		}
};
