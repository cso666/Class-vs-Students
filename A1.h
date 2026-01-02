#include "A0.h"

class stud_A1:public stud{
	public:
		stud_A1(){
			red_up+=25,blue_up+=0,white_up+=0;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(3);
			py.push_back(9);
			py.push_back(10); 
			py.push_back(16);
			py.push_back(19);
			ct1.push_back("小运");
			ct1.push_back("柠檬强酸");
			ct1.push_back("劳累");
			ct1.push_back("唐人爆率高");
			id=1;
			name="A01";
		}
};
