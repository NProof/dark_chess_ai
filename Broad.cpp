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
	}
}

void Broad::initBroad(char current_position[32])
{
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
	for(int i=0; i<32; i++)
	{
        char ch_po = current_position[i];
	    if(ch_po != '-')
        {
			checks[i].chess->pickon();
//			std::cout << *this ;
        }
	}
}

std::ostream& operator<<(std::ostream& os, const Broad& broad)
{
    os << '\n';
    for(int i=0; i<32; i++)
    {
        if(i%4==0)
            os << '\n';
        os << " " ;
        if(broad.checks[i].chess)
        {
            os << *broad.checks[i].chess;
            os << broad.checks[i].chess->mapOfMoves.size();
        }
        else
            os << "--";
    }
    os << '\n'<< " broad out." ;
//    for(int i=0; i<32; i++)
//    {
//        if(i%4==0)
//            os << '\n';
//        os << " ." ;
//        if(broad.checks[i].chess)
//            os << broad.checks[i].chess->mapOfMoves.size();
//        else
//            os << '$';
//    }
//    for(int i=0; i<32; i++)
//    {
//        if(i%4==0)
//            os << '\n';
//        os << " ." ;
//        os << broad.checks[i].pathsTo.size();
//    }
    return os ;
}

Broad::~Broad()
{
    //dtor
}
