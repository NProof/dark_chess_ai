#include "Move.h"

Move::Move(Chess * chess, Path path, Check * check)
{
    this->chess = chess;
	this->path = path;
    this->check = check;
}

Move::~Move()
{
    this->check->setOfMoves.erase(this);
    this->chess->mapOfMoves.erase(this->path);
}

void Move::generateMove(char move[6])
{
    strcpy(move, chess->check->name.c_str());
    if(path!=Path::Pick)
    {
		move[2] = '-';
		strcpy(move+3, check ? check->name.c_str() : chess->check->name.c_str());
	}
	else
	{
		scanf("%c", &move[3]);
	}
}

void Move::makeMove(char move[6])
{
	this->chess->pickoff();
    if(path!=Path::Pick)
    {
        this->check->chess = this->chess;
        this->chess->check->chess = nullptr;
        this->chess->check = this->check;
    }
    else
    {
        this->chess->init(move[3]);
    }
	this->chess->pickon();
}
