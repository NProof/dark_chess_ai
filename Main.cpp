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
	char move[10] ;
	
    char c[35] = "XnXXC-XXXXXXcXpXM-XXRkXMXXXpXXXG";
    b.initBroad(c);
    cout << b << endl;
    
	// ai1.turn = true;
	// ai2.turn = false;
	// ai1.colorOfAi = PROTO_CLR::PCLR_UNKNOW;
	// ai2.colorOfAi = PROTO_CLR::PCLR_UNKNOW;
	
	/* for(int i=0; i<32; i++)
	{
		if(
		b.checks[i].chess 
		&& ( ai1.colorOfAi == PROTO_CLR::PCLR_UNKNOW 
		? true : ( ai1.colorOfAi == PROTO_CLR::PCLR_RED ) == b.checks[i].chess.color )
		)
			
	} */
	cout << *b.checks[2].chess << endl;
	
	// std::vector<Move *> mainOfMoves;
	// for(int i=0; i<32; i++)
	// {
		// mainOfMoves.insert(b.checks[i].setOfMoves.begin(), b.checks[i].setOfMoves.end());
		// if(b.checks[i].setOfMoves.begin()!=)
			
	// }
	// cout << mainOfMoves.size() << endl;
	
	

	return 0;
}
