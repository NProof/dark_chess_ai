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
    std::set<Move *> moves = next(board, color);
    Move * onemove = (*moves.begin());
    strcpy(move, (moves.empty()) ? "NAN" : (onemove->getSrcMove()+"-"+onemove->getDstMove()).c_str());
}

void Player::makeMove(char *move)
{
    makeMove(move, this->board);
}

void Player::makeMove(const char *move, Board *&board)
{
    Board * temp = new Board(*board);
    temp->makeMove(std::string(move));
    if(theOne.find(*temp)==theOne.end())
    {
        theOne.insert(std::pair<Board, Board *>(*temp, temp));
        board = temp;
    }
    else
    {
        board = theOne.at(*temp);
        delete temp;
    }
}

bool Player::getColor()
{
    return color;
}

std::set<Move *> Player::next(Board * board, bool color)
{
    std::set<Move *> ret;
    std::set<std::pair<std::string, std::string>> mValid = board->getMoveValid(color);
    std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
    for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
    {
        ret.insert(new Move(board, pairmoveIt->first, pairmoveIt->second));
    }
    std::set<std::string> setCheckDark = board->getSetCheckDark();
    std::set<std::string>::iterator setCheckDarkIt;
    for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
    {
        ret.insert(new Move(board, *setCheckDarkIt, *setCheckDarkIt));
    }
    return ret;
}

std::map<Board *, int> Player::next(Move * move)
{
    std::map<Board *, int> ret;
    Board * board = move->getSrcBoard();
    if(move->getSrcMove().compare(move->getDstMove()))
    {
        Board * temp = new Board(*board);
        makeMove((move->getSrcMove() + "-" + move->getDstMove()).c_str(), temp);
        ret.at(temp) = 1;
    }
    else
    {
        for(std::pair<const char, int> it : move->getSrcBoard()->getDarkPieces())
        {
            Board * temp = new Board(*board);
            makeMove((move->getSrcMove() + "(" + it.first + ")").c_str(), temp);
            ret.at(temp) = it.second;
        }
    }
    return ret;
}
