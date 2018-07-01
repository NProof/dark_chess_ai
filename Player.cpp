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
    std::set<Move> greaterMove;
    std::set<std::pair<std::string, std::string>> mValid = board->getMoveValid(color);
    std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
    for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
    {
        greaterMove.insert(Move(this, *board, pairmoveIt->first+'-'+pairmoveIt->second));
    }
    std::map<char, int> mapChessesDark = board->getMapChessesDark(color);
    std::map<char, int>::iterator mapChessesDarkIt;
    int all = 0;
    for(mapChessesDarkIt=mapChessesDark.begin(); mapChessesDarkIt!=mapChessesDark.end(); mapChessesDarkIt++)
    {
        all += mapChessesDarkIt->second;
    }
    std::set<std::string> setCheckDark = board->getSetCheckDark();
    std::set<std::string>::iterator setCheckDarkIt;
    for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
    {
        greaterMove.insert(Move(this, *board, all, mapChessesDark, *setCheckDarkIt));
    }
    strcpy(move, (greaterMove.size() > 0) ? greaterMove.begin()->getStringMove().c_str() : "NAN");
}

void Player::makeMove(char *move)
{
    this->board->makeMove(std::string(move));
}

bool Player::getColor()
{
    return color;
}
