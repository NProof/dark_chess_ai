#include "Chess.h"

Chess::Chess(char x)
{
    init(x);
}

void Chess::init(char x)
{
    switch(x)
	{
	    case 'X' :
            this->type = Type::Unknown;
            break;
		case 'K' :
            this->color = false;
            this->type = Type::General;
            break;
		case 'G' :
            this->color = false;
            this->type = Type::Advisor;
            break;
		case 'M' :
            this->color = false;
            this->type = Type::Elephant;
            break;
		case 'R' :
            this->color = false;
            this->type = Type::Chariot;
            break;
		case 'N' :
            this->color = false;
            this->type = Type::Horse;
            break;
		case 'C' :
            this->color = false;
            this->type = Type::Cannon;
            break;
		case 'P' :
            this->color = true;
            this->type = Type::Soldier;
            break;
		case 'k' :
            this->color = true;
            this->type = Type::General;
            break;
		case 'g' :
            this->color = true;
            this->type = Type::Advisor;
            break;
		case 'm' :
            this->color = true;
            this->type = Type::Elephant;
            break;
		case 'r' :
            this->color = true;
            this->type = Type::Chariot;
            break;
		case 'n' :
            this->color = true;
            this->type = Type::Horse;
            break;
		case 'c' :
            this->color = true;
            this->type = Type::Cannon;
            break;
		case 'p' :
            this->color = true;
            this->type = Type::Soldier;
            break;
//        default :
//            exit(1);
	};
}

Chess::~Chess()
{
    //dtor
}

std::ostream& operator<<(std::ostream& os, const Chess& chess)
{
    if(chess.type == Type::Unknown)
        return os << 'X' ;
    else
    {
        switch(chess.type)
        {
        case Type::General:
            return os << (chess.color ? 'k' : 'K');
        case Type::Advisor:
            return os << (chess.color ? 'g' : 'G');
        case Type::Elephant:
            return os << (chess.color ? 'm' : 'M');
        case Type::Chariot:
            return os << (chess.color ? 'r' : 'R');
        case Type::Horse:
            return os << (chess.color ? 'n' : 'N');
        case Type::Cannon:
            return os << (chess.color ? 'c' : 'C');
        case Type::Soldier:
            return os << (chess.color ? 'p' : 'P');
        default:
            exit(1);
        };
    }
}

void Chess::update()
{

}
