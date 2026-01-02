   #include "A0.h"

class stud_B14:public stud{
	public:
		stud_B14(){
			red_up-=8,blue_up-=12,white_up-=4;
			red=red_up,blue=blue_up,white=white_up;
			att-=4;
			ct1.pb("宝宝");
			ct1.pb("自愈");
			ct1.pb("抱歉");
			id=27;
			name="B14";
		}
};
