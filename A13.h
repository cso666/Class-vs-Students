#include "A0.h"

class stud_A13:public stud{
	public:
		stud_A13(){
			red_up-=10,blue_up+=30,white_up-=10;
			red=red_up,blue=blue_up,white=white_up;
			att+=2;
			py.push_back(12);
			py.push_back(19);
			ct1.pb("我是传奇");
			ct1.pb("食之有味");
			ct2.pb("年猪千钧");
			id=13;
			name="A13";
		}
};
