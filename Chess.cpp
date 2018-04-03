#include <iostream>
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

bool Chess::atcCan(Type atc, Type be)
{
    switch(atc)
    {
    case Type::General :
        return be != Type::Soldier && be != Type::Unknown;
    case Type::Advisor :
        return be != Type::General && be != Type::Unknown;
    case Type::Elephant :
        return be != Type::General && be != Type::Advisor && be != Type::Unknown;
    case Type::Chariot :
        return be != Type::General && be != Type::Advisor && be != Type::Elephant && be != Type::Unknown;
    case Type::Horse :
        return be == Type::Soldier || be == Type::Cannon || be == Type::Horse;
    case Type::Cannon :
        return be != Type::Unknown;
    case Type::Soldier :
        return be == Type::Soldier || be == Type::General;
    case Type::Unknown :
        return false;
    default :
        return false;
    };
}

void Chess::pickon()
{
//    std::cout << "\npick on !" << std::endl;
    if(type == Type::Unknown)
    {
        mapOfMoves[Path::Pick] = new Move(this, Path::Pick, this->check);
		this->check->setOfMoves.insert(mapOfMoves[Path::Pick]);
    }
    for(std::map<Path, Check *>::iterator it=check->pathsTo.begin(); it !=check->pathsTo.end(); it++)
    {
        if(type==Type::Cannon)
        {
            if(it->second->chess == nullptr)
			{
				mapOfMoves[it->first] = new Move(this, it->first, it->second);
				it->second->setOfMoves.insert(mapOfMoves[it->first]);
			}
            Check * temp = check->jumpTo(it->first);
            if(temp)
            {
                Chess * a = temp->chess;
                if(a&&a->type!=Type::Unknown&&(color^a->color))
                {
                    mapOfMoves[it->first] = new Move(this, it->first, temp);
                    temp->setOfMoves.insert(mapOfMoves[it->first]);
                }
            }
        }
        else if(type!=Type::Unknown)
        {
            Chess * chess = it->second->chess;
            if(chess == nullptr || ( chess != nullptr && atcCan(type, chess->type) && ( color ^ chess->color )))
			{
//			    if((!color&&chess->color)||(color&&!(chess->color)))
                if((!color&&chess->color)||(color&&!(chess->color)));
                {
                    std::cout << *this << " eat " << chess << std::endl;
				mapOfMoves[it->first] = new Move(this, it->first, it->second);
				it->second->setOfMoves.insert(mapOfMoves[it->first]);
                }
			}
			// printf("(*) %x\n", check->jumpTo(it->first));
			Check * jump = check->jumpTo(it->first);
			if(jump)
			{
				Chess * temp = jump->chess;
				if(temp&&(temp->type==Type::Cannon&&(color^temp->color)))
				{
					// if(mapOfMoves.count(it->first))
						//
					mapOfMoves[it->first] = new Move(temp, it->first, this->check);
					this->check->setOfMoves.insert(mapOfMoves[it->first]);
				}
			}
		}
//      std::cout << " pick on %%" << std::endl;
    }
}

void Chess::pickoff(Move * movep)
{
	std::map<Path, Move *> ioo = this->mapOfMoves;
	for(std::map<Path, Move *>::iterator it = ioo.begin(); it != ioo.end(); it++)
		if(it->second != movep)
            delete it->second;
}
