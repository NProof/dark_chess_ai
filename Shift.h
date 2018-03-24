#ifndef SHIFT_H_INCLUDED
#define SHIFT_H_INCLUDED

#include "Check.h"
#include "Chess.h"

class Shift : public Move
{
public :
    void makeMove()
    {

    }
private:
    Chess * chess;
    Check * check;
};

#endif // SHIFT_H_INCLUDED
