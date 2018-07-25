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
	std::set<Move> moves = next(*board, color);
	std::set<Move>::iterator moveIt = (moves.begin());
	if(moves.empty())
	{
		strcpy(move, "NAN");
	}
	else
	{
		std::set<Move>::iterator movesIt = moves.begin();
		Move bestMove = *movesIt;
		while(++movesIt != moves.end())
		{
			if(score(bestMove, 1) < score(*movesIt, 1))
			{
				bestMove = *movesIt;
			}
		}
		strcpy(move, (bestMove.getSrcMove()+"-"+bestMove.getDstMove()).c_str());
	}
}

void Player::makeMove(char *move)
{
	makeMove(move, *this->board);
}

void Player::makeMove(const char *move, Board &board)
{
	board.makeMove(std::string(move));
}

//void Player::makeMove(const char *move, Board *&board)
//{
//	Board * temp = new Board(*board);
//	temp->makeMove(std::string(move));
//	if(theOne.find(*temp)==theOne.end())
//	{
//		theOne.insert(std::pair<Board, Board *>(*temp, temp));
//		board = temp;
//	}
//	else
//	{
//		board = theOne.at(*temp);
//		delete temp;
//	}
//}

bool Player::getColor()
{
	return color;
}

std::set<Move> Player::next(Board board, bool color)
{
	std::set<Move> ret;
	std::set<std::pair<std::string, std::string>> mValid = board.getMoveValid(color);
	std::set<std::pair<std::string, std::string>>::iterator pairmoveIt;
	for(pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end();pairmoveIt++)
	{
		ret.insert(Move(board, color, pairmoveIt->first, pairmoveIt->second));
	}
	std::set<std::string> setCheckDark = board.getSetCheckDark();
	std::set<std::string>::iterator setCheckDarkIt;
	for(setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
	{
		ret.insert(Move(board, color, *setCheckDarkIt, *setCheckDarkIt));
	}
	return ret;
}

std::pair<std::map<Board , int>, bool> Player::next(Move move)
{
	std::map<Board , int> ret;
	Board board = move.getSrcBoard();
	if(move.getSrcMove().compare(move.getDstMove()))
	{
		Board temp(board);
		makeMove((move.getSrcMove() + "-" + move.getDstMove()).c_str(), temp);
		ret.insert(std::pair<Board, int>(temp, 1));
	}
	else
	{
		for(std::pair<const char, int> it : move.getSrcBoard().getDarkPieces())
		{
			Board temp(board);
			makeMove((move.getSrcMove() + "(" + it.first + ")").c_str(), temp);
			ret.insert(std::pair<Board, int>(temp, it.second));
		}
	}
	return std::pair<std::map<Board, int>, bool>(ret, !move.getColor());
}

Score Player::score(Move move, int level)
{
	std::pair<std::map<Board , int>, bool> nextPair = next(move);
	Score meanScore;
	double meanRateWin = 0.0;
	int meanMyWays = 0;
	double meanRateDraw = 0.0;
	int meanOpWays = 0;
	double meanRateLose = 0.0;
	int allWeight;
	for(auto any : nextPair.first)
	{
		allWeight = allWeight + any.second;
		Score addScore = score(any.first, nextPair.second, level);
		meanRateWin = addScore.rateWin * any.second;
		meanMyWays = addScore.myWays * any.second;
		meanRateDraw = addScore.rateDraw * any.second;
		meanOpWays = addScore.opWays * any.second;
		meanRateLose = addScore.rateLose * any.second;
	}
	meanRateWin /= allWeight;
	meanMyWays /= allWeight;
	meanRateDraw /= allWeight;
	meanOpWays /= allWeight;
	meanRateLose /= allWeight;
	/* change the views for player	*/
	meanScore.rateWin = meanRateLose;
	meanScore.myWays = meanOpWays;
	meanScore.rateDraw = meanRateDraw;
	meanScore.opWays = meanMyWays;
	meanScore.rateLose = meanRateWin;
	return meanScore;
}

Score Player::score(Board board, bool color, int level)
{
	std::set<Move> nextSet = next(board, color);
	Score bestScore;
	if(nextSet.empty())
	{
		bestScore.rateLose = 1.0;
	}
	else
	{
		if( level > 0 )
		{
			std::set<Move>::iterator nextSetIt = nextSet.begin();
			bestScore = score(*nextSetIt, level - 1);
			if(bestScore.rateWin == 1.0)
			{
				return bestScore;
			}
			while(++nextSetIt != nextSet.end())
			{
				Score temp = score(*nextSetIt, level - 1);
				if(bestScore < temp)
				{
					if(temp.rateWin == 1.0)
					{
						return temp;
					}
					bestScore = temp;
				}
			}
		}
		else
		{
			bestScore.opWays = nextSet.size();
		}
	}
	return bestScore;
//	  return Score();
}
