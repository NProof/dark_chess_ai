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
    std::set<Move *>::iterator moveIt = (moves.begin());
    if(moves.empty())
    {
        strcpy(move, "NAN");
    }
    else
    {
        int times = rand()%(moves.size());
        for(int i=0; i<times; i++) moveIt++;
        strcpy(move, ((*moveIt)->getSrcMove()+"-"+(*moveIt)->getDstMove()).c_str());
    }
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

        ret.insert(new Move(board, color, pairmoveIt->first, pairmoveIt->second));
    }
    std::set<std::string> setCheckDark = board->getSetCheckDark();
    std::set<std::string>::iterator setCheckDarkIt;
    for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
    {
        ret.insert(new Move(board, color, *setCheckDarkIt, *setCheckDarkIt));
    }
    return ret;
}

std::pair<std::map<Board *, int>, bool> Player::next(Move * move)
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
    return std::pair<std::map<Board *, int>, bool>(ret, !move->getColor());
}

Score Player::score(Move * move)
{
    std::pair<std::map<Board *, int>, bool> nextPair = next(move);
//    std::map<Board *, int> nextMap = next(move);
	Score meanScore;
	double meanRateWin = 0.0;
	double meanRateDraw = 0.0;
	double meanRateLose = 0.0;
	int allWeight;
	for(auto any : nextPair.first)
    {
		allWeight = allWeight + any.second;
		Score addScore = score(any.first, nextPair.second);
		meanRateWin = addScore.rateWin * any.second;
		meanRateDraw = addScore.rateDraw * any.second;
		meanRateLose = addScore.rateLose * any.second;
    }
    meanRateWin /= allWeight;
    meanRateDraw /= allWeight;
    meanRateLose /= allWeight;
	/* change the views for player  */
    meanScore.rateWin = meanRateLose;
    meanScore.rateDraw = meanRateDraw;
    meanScore.rateLose = meanRateWin;
	return meanScore;
}

Score Player::score(Board * board, bool color)
{
    std::set<Move *> nextSet = next(board, color);
    Score bestScore;
    if(nextSet.empty())
    {
        bestScore.rateLose = 1.0;
    }
    else
    {
        std::set<Move *>::iterator nextSetIt = nextSet.begin();
        bestScore = score(*nextSetIt);
        while(++nextSetIt != nextSet.end())
        {
            Score temp = score(*nextSetIt);
            if(bestScore < temp)
            {
                bestScore = temp;
            }
        }
    }
    return bestScore;
//    return Score();
}
