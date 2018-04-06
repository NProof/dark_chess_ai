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
    board->updateMoves();
    std::set<std::pair<std::string, std::string>> mValid = board->getMoveValid(color);
    std::set<std::pair<std::string, std::string>>::iterator pairmove;
    pairmove = mValid.begin();
    int times = rand()%(mValid.size());
    for(int i=0; i<times; i++) pairmove++;
    strcpy(move, pairmove->first.c_str());
    move[2] = '-';
    strcpy(move+3, pairmove->second.c_str());
}

void Player::makeMove(char *move)
{
    this->board->makeMove(move);
}
