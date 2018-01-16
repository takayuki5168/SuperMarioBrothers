#pragma once

#include <vector>
#include "include/abst_character.hpp"

class AbstEnemy : public AbstCharacter
{
public:
    AbstEnemy(int x, int y, int w, int h, int color, std::string name)
        : AbstCharacter(x, y, w, h, color, name)
    {
        setVelX(-1);

        m_my_func_collision_true.at(1)  // 右壁
            = [this](Point, Point, Point) {
                  setVelX(-1);
                  //setPosX(object_x - getWidth()); // TODO バグ
              };
        m_my_func_collision_true.at(2)  // 地面
            = [this](Point object, Point, Point) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(object.m_y - getHeight());
              };

        m_my_func_collision_true.at(3)  // 左壁
            = [this](Point object, Point wh, Point) {
                  setVelX(1);
                  setPosX(object.m_x + wh.m_x);
              };
    }

private:
    constexpr static double GRAVITY = 0.15;
};
