#include "Move.h"

Move::Move(Chess * chess, Check * check)
{
    this->chess = chess;
    this->check = check;
}

Move::~Move()
{
    //dtor
}

void Move::generateMove(char move[6])
{
    strcpy(move, chess->check->name.c_str());
    move[2] = '-';
    strcpy(move+3, check ? check->name.c_str() : chess->check->name.c_str());
}

void Move::makeMove(char move[6])
{
    if(check)
    {
        this->check->chess = this->chess;
        this->chess->check->chess = nullptr;
        this->chess->check = this->check;
    }
    else
    {
        this->chess->init(move[3]);
    }
}
