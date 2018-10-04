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

std::ostream & operator<<(std::ostream & os, const Score & score)
{
	std::cout << std::setprecision(4);
	return os << " [ " 
	<< score.rateWin<< " "
	<< score.myWays<< " "
	<< score.rateDraw<< " "
	<< score.opWays << " "
	<< score.rateLose << " ] " ;
}

void Player::generateMove(char *move, int level)
{
	std::set<Move> moves = next(*board, color);
	if(moves.empty())
	{
		strcpy(move, "NAN");
	}
	else
	{
		Score alpha, beta;
//		alpha.rateWin = 1.0; beta.rateLose = 1.0;
		alpha.rateLose = 1.0; beta.rateWin = 1.0;

		std::set<Move>::iterator movesIt = moves.begin();
		std::vector<Move> vectorBesterMove = std::vector<Move>();
		Score bestScore = score(*movesIt, level - 1, alpha, beta, moves.size());
//		alpha = -score(*movesIt, level - 1, alpha, beta, moves.size());

		vectorBesterMove.push_back(*movesIt);
		while(++movesIt != moves.end())
		{
			Score tryScore = score(*movesIt, level - 1, alpha, beta, moves.size());
			if(bestScore < tryScore)
//			if(alpha < tryScore)
			{
				std::cout << bestScore << " < " << tryScore << std::endl;
				bestScore = tryScore;
//				alpha = tryScore;
				vectorBesterMove.clear();
				vectorBesterMove.push_back(*movesIt);
			}
			else if(!(tryScore < bestScore))
//			else if(!(tryScore < alpha))
			{
				std::cout << tryScore << " !< " << bestScore << std::endl;
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

Score Player::score(Move move, int level, Score alpha, Score beta, const int lastMyWays)
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
		Score addScore = score(any->first, nextPair.second, level, alpha, beta, lastMyWays);
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
	meanScore.rateWin = meanRateWin;
	meanScore.myWays = meanMyWays;
	meanScore.rateDraw = meanRateDraw;
	meanScore.opWays = meanOpWays;
	meanScore.rateLose = meanRateLose;
	return meanScore;
}

Score Player::score(Board board, bool color, int level, Score alpha, Score beta, const int lastMyWays)
{
	std::set<Move> nextSet = next(board, color);
	if(nextSet.empty())
	{
		alpha.rateWin = 0.0;
		alpha.myWays = 0.0;
		alpha.rateDraw = 0.0;
		alpha.opWays = 0.0;
		alpha.rateLose = 1.0;
	}
	else
	{
		if( level )
		{
			std::set<Move>::iterator nextSetIt = nextSet.begin();
			for(;nextSetIt != nextSet.end(); nextSetIt++)
			{
				Score temp = -score(*nextSetIt, level - 1, -beta, -alpha, nextSet.size());
				if(!(temp < beta))
				{
					return alpha;
				}
				if(alpha < temp)
				{
					if(temp.maxScore())
					{
						return temp;
					}
					alpha = temp;
				}
			}
		}
		else
		{
			alpha.rateWin = 0.0;
			alpha.myWays = nextSet.size();
			alpha.rateDraw = 0.0;
			alpha.opWays = lastMyWays;
			alpha.rateLose = 0.0;
		}
	}
	return alpha;
}
