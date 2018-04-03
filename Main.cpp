#include <iostream>

#include "Broad.h"
#include "Ai.h"

using namespace std;

int main()
{
    Broad b;
	Ai ai1, ai2;

	ai1.broadOfAi = &b;
	ai2.broadOfAi = &b;

	char move[6] ;

//    char c[64] = "XnXXC-XXXXXXcXpXM-XXRkXMXXXpXXXG";
    char c[64] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    b.initBroad(c);

//    while(ai1.generateMove(move)&&ai1.MakeMove(move)&&ai2.generateMove(move)&&ai2.MakeMove(move));
    while(true)
    {
        cout << b << endl;
        if(ai1.generateMove(move))
        {
            if(b.mapOfName[std::string{move[0], move[1]}]==b.mapOfName[std::string{move[0], move[1]}])
            {
                scanf("%s", &move[3]);
                move[2] = '('; move[4] = ')';
            }
            printf("%s\n", move);
        }
        else
            break;

        if(ai1.MakeMove(move))
            printf("%s\n", move);
        else
            break;

        cout << b << endl;
        if(ai2.generateMove(move))
        {
            if(b.mapOfName[std::string{move[0], move[1]}]==b.mapOfName[std::string{move[0], move[1]}])
            {
                scanf("%s", &move[3]);
                move[2] = '('; move[4] = ')';
            }
            printf("%s\n", move);
        }
        else
            break;

        if(ai2.MakeMove(move))
            printf("%s\n", move);
        else
            break;
    }

	return 0;
}
