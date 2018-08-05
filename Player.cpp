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
	if(moves.empty())
	{
		strcpy(move, "NAN");
	}
	else
	{
		int level = 2;
		std::set<Move>::iterator movesIt = moves.begin();
		std::vector<Move> vectorBesterMove = std::vector<Move>();
		Score bestScore = score(*movesIt, level - 1);
		vectorBesterMove.push_back(*movesIt);
		while(++movesIt != moves.end())
		{
			Score tryScore = score(*movesIt, level - 1);
			if(bestScore < tryScore)
			{
				bestScore = tryScore;
				vectorBesterMove.clear();
				vectorBesterMove.push_back(*movesIt);
			}
			else if(!(tryScore < bestScore))
			{
				vectorBesterMove.push_back(*movesIt);
			}
		}
		int random_t = rand()%vectorBesterMove.size();
		Move bestMove = vectorBesterMove[random_t];
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

std::pair<std::map<Board, int>, bool> Player::next(Move move)
{
	std::map<Board, int> ret;
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
	std::pair<std::map<Board, int>, bool> nextPair = next(move);
	Score meanScore;
	double meanRateWin = 0.0;
	float meanMyWays = 0;
	double meanRateDraw = 0.0;
	float meanOpWays = 0;
	double meanRateLose = 0.0;
	int allWeight;
	auto any = nextPair.first.begin();
	for(; any!=nextPair.first.end(); any++)
	{
		allWeight = allWeight + any->second;
		Score addScore = score(any->first, nextPair.second, level);
		meanRateWin = meanRateWin + addScore.rateWin * any->second;
		meanMyWays = meanMyWays + addScore.myWays * any->second;
		meanRateDraw = meanRateDraw + addScore.rateDraw * any->second;
		meanOpWays = meanOpWays + addScore.opWays * any->second;
		meanRateLose = meanRateLose + addScore.rateLose * any->second;
	}
	meanRateWin = meanRateWin / allWeight;
	meanMyWays = meanMyWays / allWeight;
	meanRateDraw = meanRateDraw / allWeight;
	meanOpWays = meanOpWays / allWeight;
	meanRateLose = meanRateLose / allWeight;
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
		if( level > 1 )
		{
			std::set<Move>::iterator nextSetIt = nextSet.begin();
			bestScore = score(*nextSetIt, level - 1);
			if(bestScore.maxScore())
			{
				return bestScore;
			}
			while(++nextSetIt != nextSet.end())
			{
				Score temp = score(*nextSetIt, level - 1);
				if(bestScore < temp)
				{
					if(temp.maxScore())
					{
						return temp;
					}
					bestScore = temp;
				}
			}
		}
		else if(level)
		{
			bestScore.myWays = nextSet.size();
		}
		else
		{
			bestScore.opWays = nextSet.size();
		}
	}
	return bestScore;
//	  return Score();
}
