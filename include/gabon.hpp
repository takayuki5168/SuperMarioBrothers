#pragma once

#include "include/abst_enemy.hpp"

class Gabon : public AbstEnemy
{
public:
    Gabon(int x = 500, int y = 30)
        : AbstEnemy(x, y, 40, 40, 0x003d00, "Gabon")
    {
        setVelX(0);

        m_my_func_collision_true.at(1)  // 右壁
            = [this](Point, Point, Point) {};
        m_my_func_collision_true.at(2)  // 地面
            = [this](Point object, Point, Point) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(object.m_y - getHeight());
              };

        m_my_func_collision_true.at(3)  // 左壁
            = [this](Point, Point, Point) {};
    }

private:
};
