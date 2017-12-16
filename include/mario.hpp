#pragma once

#include "include/abst_player.hpp"


class Mario : public AbstPlayer
{
public:
    Mario(int x = 300, int y = 30)
        : AbstPlayer(x, y, 40, 70, 0xff0000, "Mario") {}

private:
};
