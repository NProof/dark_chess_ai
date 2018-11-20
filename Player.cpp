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
	if(board.d_red + board.d_black > 0)
	{
		std::vector<std::pair<SetBoard, std::string> > options;
		for(auto ptrMove : next(board)){
			options.push_back(std::pair<SetBoard, std::string>( ptrMove.second, ptrMove.first ));
		}
		strcpy(move, (options.empty()) ? "NAN" : options[rand()%options.size()].second.c_str());
	}
	else
	{
		std::vector<std::pair<SetBoard, std::string> > options = multi_level(1);
		strcpy(move, (options.empty()) ? "NAN" : options[rand()%options.size()].second.c_str());
	}
}

bool Player::getColor()
{
	return color;
}

std::vector<std::pair<SetBoard, std::string> > Player::multi_level(int level)
{
	std::map<Score, std::vector<std::pair<SetBoard, std::string> > > mapRank;
	for(auto ptrMove : next(board)){
		mapRank[score(ptrMove.second, level)].push_back(
			std::pair<SetBoard, std::string>(ptrMove.second, ptrMove.first)
		);
	}
	return mapRank.begin()->second;
}

std::map<std::string, SetBoard> Player::next(Board board)
{
		std::map<std::string, SetBoard> temp;
		std::set<std::pair<std::string, std::string>> mValid = board.getMoveValid();
		for(auto pairmoveIt=mValid.begin(); pairmoveIt!=mValid.end(); pairmoveIt++)
		{
			temp.insert(std::pair<std::string, SetBoard>(
				pairmoveIt->first+'-'+pairmoveIt->second, SetBoard(board, pairmoveIt->first+'-'+pairmoveIt->second))
		   );
		}
		std::map<char, int> mapChessesDark = board.getDarkPieces();
		std::set<std::string> setCheckDark = board.getSetCheckDark();
		for(auto setCheckDarkIt=setCheckDark.begin(); setCheckDarkIt!=setCheckDark.end(); setCheckDarkIt++)
		{
			temp.insert(std::pair<std::string, SetBoard>(
				*setCheckDarkIt+'-'+*setCheckDarkIt, SetBoard(board, *setCheckDarkIt, setCheckDark.size(), mapChessesDark))
			);
		}
		return temp;
}

Score Player::score(Board board, int level)
{
	if(level){
		Score bestScore = Score::minScore;
		for(auto mov : next(board))
		{
			Score temp = -score(mov.second, level-1);
			if(temp > bestScore)
				bestScore = temp;
		}
		return bestScore;
	}
	else{
		return *board.getScore();
	}
}

Score Player::score(SetBoard mov, int level)
{
	std::map<Board, int> nextMov = mov.GetpossibleBoards();
	std::map<Board, int>::iterator it = nextMov.begin();
	Score mean = (score(it->first, level) *= it->second);
	for(; it != nextMov.end(); it++)
	{
		mean += (score(it->first, level) *= it->second);
	}
	return mean /= mov.GetiDark();
}
