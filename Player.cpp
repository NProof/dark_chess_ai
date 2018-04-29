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
    mapGreatMove.clear();
    Board *newBoard;
    std::string strMove;
    std::set<std::pair<std::string, std::string>> mValid = board->getMoveValid(color);
    std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
    for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
    {
        strMove = pairmoveIt->first+'-'+pairmoveIt->second;
        newBoard = new Board(*board);
        strcpy(move, strMove.c_str());
        newBoard->makeMove(move);
        mapGreatMove[std::map<Board *, double>{{newBoard, 1.0}}] = strMove;
    }
    std::set<std::string> setCheckDark = board->getSetCheckDark();
    std::set<std::string>::iterator setCheckDarkIt;
    std::map<char, int> mapChessesDark = board->getMapChessesDark();
    std::map<char, int>::iterator mapChessesDarkIt;
    int all = 0;
    for(mapChessesDarkIt=mapChessesDark.begin(); mapChessesDarkIt!=mapChessesDark.end(); mapChessesDarkIt++)
    {
        all += mapChessesDarkIt->second;
    }
    for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
    {
        std::map<Board *, double> newMap;
        for(mapChessesDarkIt=mapChessesDark.begin(); mapChessesDarkIt!=mapChessesDark.end(); mapChessesDarkIt++)
        {
            strMove = *setCheckDarkIt+'('+mapChessesDarkIt->first+')';
            newBoard = new Board(*board);
            strcpy(move, strMove.c_str());
            newBoard->makeMove(move);
            newMap.insert(std::pair<Board *, double>(newBoard, double(mapChessesDarkIt->second/all)));
        }
        mapGreatMove[newMap] = *setCheckDarkIt+'-'+*setCheckDarkIt;;
    }
    strcpy(move, mapGreatMove.begin()->second.c_str());
}

void Player::makeMove(char *move)
{
    this->board->makeMove(move);
}
