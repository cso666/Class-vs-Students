#include "A0.h"

class stud_A10:public stud{
	public:
		stud_A10(){
			red_up-=20,blue_up-=40,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(5);
			py.push_back(18);
			ct1.push_back("大智若唐");
			ct1.pb("定力");
			ct2.pb("大力抽射");
			id=10;
			name="A10";
		}
};
