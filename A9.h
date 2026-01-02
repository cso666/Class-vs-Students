#include "A0.h"

class stud_A9:public stud{
	public:
		stud_A9(){
			red_up-=15,blue_up+=80,white_up+=10;
			red=red_up,blue=blue_up,white=white_up;
			att+=5;
			py.push_back(17);
			py.push_back(19);
			ct1.push_back("班长大人");
			ct1.push_back("劝架使者");
			ct1.push_back("多助之至");
			ct2.push_back("太守寻源");
			id=9;
			name="A09";
		}
};
