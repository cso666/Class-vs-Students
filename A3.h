#include"A0.h"

class stud_A3:public stud{
	public:
		stud_A3(){
			red_up+=5,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att-=5;
			py.push_back(2);
			py.push_back(10);
			py.push_back(15);
			py.push_back(19);
			ct1.push_back("红温");
			ct1.push_back("东西被偷了");
			ct1.push_back("You mother");
			ct1.push_back("如烟");
			id=3;
			name="A03";
		}
};
