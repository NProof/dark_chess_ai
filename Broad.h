#ifndef BROAD_H
#define BROAD_H

#include <iostream>
#include "Check.h"
#include <map>

class Check;

class Broad
{
    public:
        Broad();
        virtual ~Broad();

        void initBroad(char [32]);
        friend std::ostream& operator<<(std::ostream&, const Broad&);

        Check checks[36];
        std::map<std::string, Check *> mapOfName;

    protected:

    private:
};

#endif // BROAD_H
