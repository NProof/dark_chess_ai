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
        std::string getSrcMove();
        std::string getDstMove();
    protected:

    private:
        Board * srcBoard;
        std::string srcMove;
        std::string dstMove;
};

#endif // MOVE_H
