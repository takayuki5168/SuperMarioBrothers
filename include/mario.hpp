#pragma once

#include "include/abst_charactor.hpp"

class Mario : public AbstCharactor
{
public:
    Mario(int x = 300, int y = 300)
        : AbstCharactor(x, y, 50, 100, 0xff0000, "Mario", std::vector<AbstObject::Point>(), std::vector<AbstObject::Line>()) {}

private:
};
