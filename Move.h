#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"

class Move
{
    public:
        Move(Board *, std::string, std::string);
        virtual ~Move();

        Board * getSrcBoard();
        bool srcSamedst();
        std::string getStrMove();
    protected:

    private:
        Board * srcBoard;
        std::string srcMove;
        std::string dstMove;
        char kind = 'X';
};

#endif // MOVE_H
