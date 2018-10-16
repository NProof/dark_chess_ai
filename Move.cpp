#include "Move.h"

Move::Move(Board * srcBoard, std::string srcMove, std::string dstMove)
{
    this->srcBoard = srcBoard;
    this->srcMove = srcMove;
    this->dstMove = dstMove;
}

Move::~Move()
{
    //dtor
}

Board * Move::getSrcBoard()
{
    return srcBoard;
}

std::string Move::getStrMove()
{
    if(srcMove == dstMove && kind != 'X')
        return srcMove + "(" + kind + ")";
    return srcMove + "-" + dstMove;
}

bool Move::srcSamedst()
{
    return srcMove == dstMove;
}
