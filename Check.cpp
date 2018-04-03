#include "Check.h"

Check::Check()
{
    chess = nullptr;
}

Check::~Check()
{
    //dtor
}

Check * Check::jumpTo(Path path)
{
	Check * temp = leavTo(path);
	return temp ? temp->leavTo(path) : NULL ;
}

Check * Check::leavTo(Path path)
{
	if(pathsTo.count(path))
    {
		if(pathsTo[path]->chess)
			return pathsTo[path];
		else
			return pathsTo[path]->leavTo(path);
    }
	return NULL;
}

void Check::pickon()
{

}

void Check::pickoff(Move * movep)
{
	std::set<Move *> df = this->setOfMoves;
	for(std::set<Move *>::iterator it = df.begin(); it != df.end(); it++)
		if(*it != movep)
            delete *it;
}
