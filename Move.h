#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
    virtual void makeMove() = 0;
private:
    std::string instruction;
};
#endif
