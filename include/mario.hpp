#pragma once

#include "include/abst_player.hpp"
#include "include/abst_fix_block.hpp"

class Mario : public AbstPlayer
{
public:
    Mario(int x = 300, int y = 30)
        : AbstPlayer(x, y, 40, 70, 0xff0000, "Mario") {}

    /*
    void updatePos() override
    {
        m_vel.y += m_gravity;
        m_pos = m_pos + m_vel;
    }
  */

private:
};
