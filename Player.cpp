#include "Player.h"

Player::Player()
{
    this->board = new Board();
}

Player::~Player()
{
    //dtor
}

void Player::setColor(PROTO_CLR color)
{
    this->color = color == PROTO_CLR::PCLR_BLACK; // =islower()
}

void Player::generateMove(char *move)
{
    std::set<std::string> stringMoves;
    std::set<std::pair<std::string, std::string>> mValid = board->getMoveValid(color);
    std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
    for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
    {
        stringMoves.insert(pairmoveIt->first+'-'+pairmoveIt->second);
    }
    std::set<std::string> setCheckDark = board->getSetCheckDark();
    std::set<std::string>::iterator setCheckDarkIt;
    for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
    {
        stringMoves.insert(*setCheckDarkIt+'-'+*setCheckDarkIt);
    }
    std::set<std::string>::iterator stringMovesIt = stringMoves.begin();
    int times = rand()%(stringMoves.size());
    for(int i=0; i<times; i++) stringMovesIt++;
    strcpy(move, stringMovesIt->c_str());
}

void Player::makeMove(char *move)
{
    this->board->makeMove(move);
}
