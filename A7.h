#include "A0.h"

class stud_A7:public stud{
	public:
		stud_A7(){
			red_up+=180,blue_up-=0,white_up+=100;
			red=red_up,blue=blue_up,white=white_up;
			att-=8;
			py.push_back(16);
			py.push_back(19);
			ct1.push_back("大运之力");
			ct1.push_back("自强不屈");
			ct2.push_back("大运来力");
			id=7;
			name="A07";
		}
};
