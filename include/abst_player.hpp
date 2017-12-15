#pragma once

#include <vector>
#include "include/abst_object.hpp"
#include "include/abst_fix_block.hpp"

class AbstPlayer : public AbstObject
{
public:
    AbstPlayer(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name) {}

    void updatePos() override
    {
        m_vel.y = 1;
        m_pos.y += m_vel.y;
    }

    /*
    virtual void updateCollisionWithBlock(std::vector<std::shared_ptr<AbstFixBlock>>& block_vec)
    {
        for (auto p : m_collision_point.at(2)) {
            const int block_size = AbstBlock::getBlockSize();
            int x = (p.x - p.x % block_size) / block_size;
            int y = (p.y - p.y % block_size) / block_size;
        }
		}*/

private:
    double hit_point = 0;
};
