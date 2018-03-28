#include <iostream>
//
#include <Broad.h>
//#include <Chess.h>
#include <Move.h>

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

	return 0;
}
