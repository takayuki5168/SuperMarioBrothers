#pragma once

#include "include/abst_enemy.hpp"

class Gabon : public AbstEnemy
{
public:
    Gabon(int x = 500, int y = 30)
        : AbstEnemy(x, y, 40, 40, 0x003d00, "Gabon")
    {
        setVelX(0);

        m_collision_true_fix_object_func.at(1)  // 右壁
            = [this](Point, Point, Point) {};
        m_collision_true_fix_object_func.at(2)  // 地面
            = [this](Point object, Point, Point) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(object.y - getHeight());
              };

        m_collision_true_fix_object_func.at(3)  // 左壁
            = [this](Point, Point, Point) {};
    }

private:
};
