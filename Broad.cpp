#include "Broad.h"

Broad::Broad()
{
//	std::cout << "Broad()." << std::endl;
	std::string name;
    for(int i=0; i<32; i++)
	{
		if(i/4>0)
			checks[i].pathsTo[Path::Up] = &checks[i-4];
		if(i/4<7)
			checks[i].pathsTo[Path::Down] = &checks[i+4];
		if(i%4>0)
			checks[i].pathsTo[Path::Left] = &checks[i-1];
		if(i%4<3)
			checks[i].pathsTo[Path::Right] = &checks[i+1];
        name = {char('a'+(i%4)),char('8'-(i/4))};
	    mapOfName[name] = &checks[i];
	    checks[i].name = name;

	    Chess * temp = new Chess('X');
        checks[i].chess = temp;
        temp->check = &checks[i];

        setDark.insert(temp);
	}
//    char chs[] = "kggmmrrnnccpppppKGGMMRRNNCCPPPPP";
//    chDark.insert(chs, chs+32);
    chDark['k'] = 1; chDark['K'] = 1;
    chDark['g'] = 2; chDark['G'] = 2;
    chDark['m'] = 2; chDark['M'] = 2;
    chDark['r'] = 2; chDark['R'] = 2;
    chDark['n'] = 2; chDark['N'] = 2;
    chDark['c'] = 2; chDark['C'] = 2;
    chDark['p'] = 5; chDark['P'] = 5;
}

/* void Broad::initBroad(int kinds[14], char current_position[32])
{
//    if(current_position == nullptr)
//        current_position = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    for(int i=0; i<32; i++)
    {
        char ch_po = current_position[i];
        if(ch_po != '-')
        {
            Chess * temp = new Chess(ch_po);
            checks[i].chess = temp;
            temp->check = &checks[i];
        }
    }
//    updateBoard();
} */

/*void Broad::updateBoard()
{
    /\* for(int i=0; i<32; i++)
    {
        char ch_po = current_position[i];
        if(ch_po != '-')
        {
            checks[i].chess->pickon();
//			std::cout << *this ;
    }*\/
}*/

std::ostream& operator<<(std::ostream& os, const Broad& broad)
{
    os << "operator<< " << &(broad);
    for(int i=0; i<32; i++)
    {
        if(i%4==0)
            os << '\n';
        os << " " ;
        if(broad.checks[i].chess)
        {
            os << *broad.checks[i].chess;
//            os << broad.checks[i].chess->mapOfMoves.size();
        }
        else
            os << "-";
    }
    os << '\n'<< "--- broad out." << std::endl;
    return os ;
}

Broad::~Broad()
{
    //dtor
}
