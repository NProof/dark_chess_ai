#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include "Board.h"

class Board::Move
{
    public:
        Move(Board, std::string);
        Move(Board, std::string, int, std::map<char, int>);
        virtual ~Move();

        bool operator<(const Move& other) const;

        Board GetOringinB();
        PROTO_CLR Getcolor() const;
        std::string getStringMove() const;
        int GetiDark() const;
		std::map<char, int> GetpossibleKinds();
		std::map<Board, int> GetpossibleBoards() const;
    protected:

    private:
        Board originB;
        PROTO_CLR color;
        std::string strMove;
        int iDark;
        std::map<char, int> possibleKinds;
        std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
