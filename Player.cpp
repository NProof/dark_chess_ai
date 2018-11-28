#include "Player.h"

Player::Player()
{
	
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
	auto safe = board->safePlace();
	if(safe.size() > 0)
	{
		std::string onePosition = safe[rand()%safe.size()];
		strcpy(move, (onePosition+"-"+onePosition).c_str());
		return;
	}
	{
		std::vector<std::pair<SetBoard, std::string> > options = multi_level(0);
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
	for(auto ptrMove : next(*board)){
		mapRank[score(ptrMove.second, level)].push_back(
			std::pair<SetBoard, std::string>(ptrMove.second, ptrMove.first->str)
		);
	}
	return mapRank.begin()->second;
}

std::map<Mov *, SetBoard> Player::next(Board board)
{
	return board.next();
}

Score Player::score(Board board, int level)
{
	if(level){
		Score bestScore = Score::minScore;
		for(auto options : next(board))
		{
			Score temp = -score(options.second, level-1);
			if(temp > bestScore)
				bestScore = temp;
		}
		return bestScore;
	}
	else{
		return *(board.getScore());
	}
}

Score Player::score(SetBoard option, int level)
{
	Score mean;
	std::map<Board, int> nextMov = option.GetpossibleBoards();
	for(std::map<Board, int>::iterator it = nextMov.begin(); it != nextMov.end(); it++)
	{
		Score addend = score(it->first, level);
		addend *= it->second;
		mean += addend;
	}
	return mean /= option.GetiDark();
}
