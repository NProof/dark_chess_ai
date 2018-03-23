#include <iostream>

#include "Ai.h"
#include "Check.h"
//#include "Chess.h"

using namespace std;

int main()
{
	int a[14] = {1, 2, 2, 2, 2, 2, 4, 1, 2, 2, 2, 2, 1, 5};
	char c[35] = "XnXXX-XXXXXXXXXXXM-XXXkXMXXXXXXX";
//	Broad broad;
//	broad.initBroad(c);
//	cout << broad.checks[1].name << endl;

    Ai ai;
    ai.initBoardState(a, c);

	return 0;
}
