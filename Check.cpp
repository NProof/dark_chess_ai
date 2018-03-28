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
