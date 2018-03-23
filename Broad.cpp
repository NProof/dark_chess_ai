#include <iostream>

#include "Broad.h"

Broad::Broad()
{
	std::cout << "Broad()." << std::endl;
    for(int i=0; i<32; i++)
	{
		if(i/4>0)
			checks[i].pathsTo[Path::Up] = &checks[i-4];
		if(i/4<8)
			checks[i].pathsTo[Path::Down] = &checks[i+4];
		if(i%4>0)
			checks[i].pathsTo[Path::Left] = &checks[i-8];
		if(i%4<4)
			checks[i].pathsTo[Path::Right] = &checks[i+8];
	    checks[i].name = {'a'+(i%4),'8'-(i/4)};
	}
}

/* std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>> Broad::initBroad(int piece_count[14], char current_position[32])
{
    std::map<Type,std::set<Check *>> lChecks;
	std::map<Type,std::set<Check *>> hChecks;
	for(int i=0; i<32; i++)
	{
        char ch = current_position[i];
	    if(ch == 'X')
            unknownChecks.insert(&checks[i]);
		else if(ch != '-')
        {
            int index = intOfPosition(ch);
			piece_count[index]--;
            Type type = typeOfPosition(ch);
            std::set<Check *> tempset;
			if(index < 7)
			{
			    if(hChecks.count(type))
                    hChecks[type].insert(&checks[i]);
                else
                {
                    tempset.insert(&checks[i]);
                    hChecks[type] = tempset;
                }
			}
			else
            {
			    if(lChecks.count(type))
                    lChecks[type].insert(&checks[i]);
                else
                {
                    tempset.insert(&checks[i]);
                    lChecks[type] = tempset;
                }
            }
        }
	}
	for(int i=0; i<14; i++)
		for(int c=0; c<piece_count[i]; c++)
		    unknownSet.insert(pairOfInt(i));
    return std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>>(lChecks, hChecks);
} */

void Broad::initBroad(char current_position[32])
{
	for(int i=0; i<32; i++)
	{
        char ch_po = current_position[i];
	    if(ch_po != '-')
        {
			checks[i].chess = new Chess(ch_po);
        }
	}
}

/* // void Broad::initBroad(int piece_count[14], char current_position[32])
{
	for(int i=0; i<32; i++)
	{
        char ch_po = current_position[i];
	    if(ch_po != '-')
        {
//			piece_count[intOfPosition(ch_po)]--;
			checks[i].chess = new Chess(ch_po);
        }
	}
//	for(int i=0; i<14; i++)
//		for(int c=0; c<piece_count[i]; c++)
//		    unknownSet.insert(pairOfInt(i));
} */

int Broad::intOfPosition(char symbol)
{
	switch(symbol)
	{
		case 'K' :
			return 0;
		case 'G' :
			return 1;
		case 'M' :
			return 2;
		case 'R' :
			return 3;
		case 'N' :
			return 4;
		case 'C' :
			return 5;
		case 'P' :
			return 6;
		case 'k' :
			return 7;
		case 'g' :
			return 8;
		case 'm' :
			return 9;
		case 'r' :
			return 10;
		case 'n' :
			return 11;
		case 'c' :
			return 12;
		case 'p' :
			return 13;
        default :
            return -1;
	};
}

std::pair<bool, Type> Broad::pairOfInt(int index)
{
	return std::make_pair(index < 7, typeOfInt(index%7));
}

Type Broad::typeOfInt(int re)
{
	Type types[7] = {Type::General, Type::Advisor, Type::Elephant, Type::Chariot, Type::Horse, Type::Cannon, Type::Soldier};
	return types[re];
}

