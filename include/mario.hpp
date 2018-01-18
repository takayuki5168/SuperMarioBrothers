#pragma once

#include "include/abst_player.hpp"


class Mario : public AbstPlayer
{
public:
    explicit Mario(int x = 300 + 1000, int y = 30)
        : AbstPlayer(x, y, 40, 70, 0xff0000, "Mario") { m_idx = 150; }


private:
};
