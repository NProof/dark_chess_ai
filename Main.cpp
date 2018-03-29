#include <iostream>

#include <set>

#include "Broad.h"
//#include "Chess.h"
#include "Move.h"

//class Move;

using namespace std;

int main()
{
    Broad b;
    char c[35] = "XnXXX-XXXXXXXXXXXM-XXXkXMXXXXXXX";
    b.initBroad(c);

//    cout << b << endl;
//    cout << &b.checks[3] << endl;
//    cout << b.checks[3].chess << endl;
//    cout << b.checks[3].chess->check << endl;

//**//
//    char op[6];
    /* Flip * flip = new Flip(b.checks[4].chess) ;
    cout << *flip->fliped << endl;
    flip->generateMove(op);
    cout << op << endl;

    Shift * shift = new Shift(b.checks[15].chess, &b.checks[14]);
    shift->generateMove(op);
    cout << op << endl; */

    char op[6];
    Move move(b.checks[10].chess, nullptr);
    move.generateMove(op);
    cout << op << " and Move ... " << endl;
	cout << b << endl;
	cout << *b.checks[1].chess << endl;
	b.checks[1].chess->pickon();
	// b.checks[1].chess->showSet();
	// std::set<Move *> ioo = b.checks[1].chess->setOfMoves;
	// cout << ioo.size() << endl;
	// std::set<Move *>::iterator it;
	// for(it = ioo.begin(); it != ioo.end(); it++)
		// std::cout << " " << (*it)->chess->check->name << " , " << (*it)->check->name << std::endl;

	return 0;
}
