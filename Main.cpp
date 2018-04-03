#include <iostream>

#include <vector>
#include <set>

#include "Broad.h"
#include "Chess.h"
#include "Check.h"
#include "Move.h"
#include "Ai.h"

#include <cstdlib>

class Check;

using namespace std;

int main()
{
    Broad b;
	Ai ai1, ai2;

	ai1.broadOfAi = &b;
	ai2.broadOfAi = &b;

	char move[6] ;

    char c[35] = "XnXXC-XXXXXXcXpXM-XXRkXMXXXpXXXG";
    b.initBroad(nullptr);

//    while(ai1.generateMove(move)&&ai1.MakeMove(move)&&ai2.generateMove(move)&&ai2.MakeMove(move));
    while(true)
    {
        cout << b << endl;
        if(ai1.generateMove(move)&&ai1.MakeMove(move)&&ai2.generateMove(move)&&ai2.MakeMove(move))
            printf("dd\n");
        else
            printf("fail\n");
    }

	return 0;
}
