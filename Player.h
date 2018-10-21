#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <set>
#include "Protocol.h"
#include "Board.h"
#include "Move.h"

class Move;
class Player
{
    public:
        Player();
        virtual ~Player();

        void setColor(PROTO_CLR);
        void generateMove(char *);
        void makeMove(char *);

        bool getColor();
    protected:

    private:
        std::vector<Move> betterMoves(Board);

        bool color;
        Board *board;
        std::map<Board, std::set<Move *>> B2MS;
        std::map<Move, std::map<Board *, int>> M2BM;
};

#endif // PLAYER_H
