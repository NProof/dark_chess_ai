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
        std::string getStringMove();
        int GetiDark();
		std::map<char, int> GetpossibleKinds();
		std::map<Board, int> GetpossibleBoards();
    protected:

    private:
        Board originB;
        std::string strMove;
        int iDark;
        std::map<char, int> possibleKinds;
		std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
