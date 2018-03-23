#include <iostream>

#include "Ai.h"

Ai::Ai()
{

}

void Ai::initBoardState(int piece_count[14], char current_position[32])
{
//    std::pair<std::map<Type,std::set<Check *>>, std::map<Type,std::set<Check *>>> repair = broad.initBroad(piece_count, current_position);
    broadOfAi = new Broad();
    broadOfAi->initBroad(current_position);
}
