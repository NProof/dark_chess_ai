#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "Board.h"
#include "Protocol.h"

class Player
{
    public:
        Player(int [14], char [32], History&, int&);
        virtual ~Player();

        void setColor(PROTO_CLR);
        void generateMove(char *);
        void makeMove(char *);
    protected:

    private:
        bool color;
        Board *board;
        std::set<std::pair<std::string, std::string>> mValid;
};

#endif // PLAYER_H
