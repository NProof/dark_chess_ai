#include <iostream>
#include <set>

#include "Check.h"

Check::Check()
{
	std::cout << "Check()." << std::endl;
//	type = Type::Space;
    chess = nullptr;
}

/* inline std::ostream& operator<<(std::ostream& os, const Type& type)
{
   switch(type)
   {
   case Type::Space :
    os << '-' ;
    break;
   case Type::Soldier :
    os << 'P' ;
    break;
   case Type::Cannon :
    os << 'C' ;
    break;
   case Type::Horse :
    os << 'N' ;
    break;
   case Type::Chariot :
    os << 'R' ;
    break;
   case Type::Elephant :
    os << 'M' ;
    break;
   case Type::Advisor :
    os << 'G' ;
    break;
   case Type::General :
    os << 'K' ;
    break;
   case Type::Unknown :
    os << 'X' ;
    break;
   }
   return os << ". " ;
} */

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
