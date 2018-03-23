#include <iostream>

#include "Chess.h"

/* Chess::Chess()
{
    std::cout << "Chess()." << std::endl;
    type = Type::Unknown;
} */

Chess::Chess(char symbol)
{
    std::cout << "Chess(char)." << std::endl;
    switch(symbol)
	{
	    case 'X' :
            this->type = Type::Unknown;
            break;
		case 'K' :
//			return std::make_pair(false, Type::General);
            this->color = false;
            this->type = Type::General;
            break;
		case 'G' :
//			return std::make_pair(false, Type::Advisor);
            this->color = false;
            this->type = Type::Advisor;
            break;
		case 'M' :
//			return std::make_pair(false, Type::Elephant);
            this->color = false;
            this->type = Type::Elephant;
            break;
		case 'R' :
//			return std::make_pair(false, Type::Chariot);
            this->color = false;
            this->type = Type::Chariot;
            break;
		case 'N' :
//			return std::make_pair(false, Type::Horse);
            this->color = false;
            this->type = Type::Horse;
            break;
		case 'C' :
//			return std::make_pair(false, Type::Cannon);
            this->color = false;
            this->type = Type::Cannon;
            break;
		case 'P' :
//			return std::make_pair(false, Type::Soldier);
            this->color = true;
            this->type = Type::Soldier;
            break;
		case 'k' :
//			return std::make_pair(true, Type::General);
            this->color = true;
            this->type = Type::General;
            break;
		case 'g' :
//			return std::make_pair(true, Type::Advisor);
            this->color = true;
            this->type = Type::Advisor;
            break;
		case 'm' :
//			return std::make_pair(true, Type::Elephant);
            this->color = true;
            this->type = Type::Elephant;
            break;
		case 'r' :
//			return std::make_pair(true, Type::Chariot);
            this->color = true;
            this->type = Type::Chariot;
            break;
		case 'n' :
//			return std::make_pair(true, Type::Horse);
            this->color = true;
            this->type = Type::Horse;
            break;
		case 'c' :
//			return std::make_pair(true, Type::Cannon);
            this->color = true;
            this->type = Type::Cannon;
            break;
		case 'p' :
//			return std::make_pair(true, Type::Soldier);
            this->color = true;
            this->type = Type::Soldier;
            break;
        default :
            exit(1);
	};
}


std::ostream& operator<<(std::ostream& os, const Chess& chess)
{
    if(chess.type == Type::Unknown)
        os << 'X' ;
    else
    {
        switch(chess.type)
        {
        case Type::General:
            os << (chess.color ? 'k' : 'K');
            break;
        case Type::Advisor:
            os << (chess.color ? 'g' : 'G');
            break;
        case Type::Elephant:
            os << (chess.color ? 'm' : 'M');
            break;
        case Type::Chariot:
            os << (chess.color ? 'r' : 'R');
            break;
        case Type::Horse:
            os << (chess.color ? 'n' : 'N');
            break;
        case Type::Cannon:
            os << (chess.color ? 'c' : 'C');
            break;
        case Type::Soldier:
            os << (chess.color ? 'p' : 'P');
            break;
        }
    }
    return os ;
}
