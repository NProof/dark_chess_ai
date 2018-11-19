#include "Player.h"

Player::Player()
{
	this->board = Board();
}

Player::~Player()
{
	//dtor
}

void Player::setColor(PROTO_CLR color)
{
	this->color = color ; // =islower()
}

void Player::generateMove(char *move)
{
	std::cout << board.nD_red << " and Black : " << board.nD_black << std::endl;
	if(board.nD_red+board.nD_black>0)
	{
		std::vector<Board::SetBoard> moves;
		for(Board::SetBoard ptrMove : next(board)){
			moves.push_back(ptrMove);
		}
		strcpy(move, (moves.empty()) ? "NAN" : moves[rand()%moves.size()].getStringMove().c_str());
	}
	else
	{
		std::vector<Board::SetBoard> moves = multi_level(1);
		strcpy(move, (moves.empty()) ? "NAN" : moves[rand()%moves.size()].getStringMove().c_str());
	}
}

void Player::makeMove(char *move)
{
	this->board.makeMove(std::string(move));
}

bool Player::getColor()
{
	return color;
}

std::vector<Board::SetBoard> Player::multi_level(int level)
{
	std::map<Score, std::vector<Board::SetBoard> > mapRank;
	for(Board::SetBoard ptrMove : next(board)){
		mapRank[score(ptrMove, level)].push_back(ptrMove);
	}
	return mapRank.begin()->second;
}

std::set<Board::SetBoard> Player::next(Board board)
{
		std::set<Board::SetBoard> temp;
		std::set<std::pair<std::string, std::string>> mValid = board.getMoveValid();
		for(auto pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end(); pairmoveIt++)
		{
			temp.insert(Board::SetBoard(board, pairmoveIt->first+'-'+pairmoveIt->second));
		}
		std::map<char, int> mapChessesDark = board.getDarkPieces();
		std::set<std::string> setCheckDark = board.getSetCheckDark();
		for(auto setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
		{
			temp.insert(Board::SetBoard(board, *setCheckDarkIt, setCheckDark.size(), mapChessesDark));
		}
		return temp;
}

std::map<Board, int> Player::next(Board::SetBoard mov)
{
	return mov.GetpossibleBoards();
}

Score Player::score(Board board, int level)
{
	if(level){
		Score bestScore = Score::minScore;
		for(auto mov : next(board))
		{
			Score temp = -score(mov, level-1);
			if(temp > bestScore)
				bestScore = temp;
		}
		return bestScore;
	}
	else{
		return *board.getScore();
	}
}

Score Player::score(Board::SetBoard mov, int level)
{
	std::map<Board, int> nextMov = next(mov);
	std::map<Board, int>::iterator it = nextMov.begin();
	Score mean = (score(it->first, level) *= it->second);
	for(; it != nextMov.end(); it++)
	{
		mean += (score(it->first, level) *= it->second);
	}
	return mean /= mov.GetiDark();
}
