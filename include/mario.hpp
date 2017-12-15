#pragma once

#include "include/abst_player.hpp"
#include "include/abst_fix_block.hpp"

class Mario : public AbstPlayer
{
public:
    Mario(int x = 300, int y = 30)
        : AbstPlayer(x, y, 40, 70, 0xff0000, "Mario") {}

    void updatePos() override
    {
        m_vel.y = 2;
        m_pos.y += m_vel.y;
    }
    /*
    virtual void updateCollisioinWithBlock(std::vector<std::shared_ptr<AbstBlock>>& block_vec)
    {
    }*/

private:
};
