#ifndef BROAD_H
#define BROAD_H

#include <iostream>
#include "Check.h"
#include <map>

class Check;

class Broad
{
    public:
        Broad(); // 空的盤面
        virtual ~Broad();

//        void initBroad(int [14], char [32]); //初始盤面
        friend std::ostream& operator<<(std::ostream&, const Broad&);

        Check checks[36];
        std::map<std::string, Check *> mapOfName;

        std::set<Chess *> setDark;
        std::map<char, int> chDark;

    protected:

    private:
};

#endif // BROAD_H
