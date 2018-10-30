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

        bool Getcolor() const;
        std::string getStringMove() const;
        int GetiDark() const;
		std::map<Board, int> GetpossibleBoards() const;
    protected:

    private:
        bool color;
        std::string strMove;
        int iDark;
        std::map<Board, int> possibleBoards;
};

#endif // MOVE_H
