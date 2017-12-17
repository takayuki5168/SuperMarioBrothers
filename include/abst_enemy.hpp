#pragma once

#include <vector>
#include "include/abst_dynamic_object.hpp"

class AbstEnemy : public AbstDynamicObject
{
public:
    AbstEnemy(int x, int y, int w, int h, int color, std::string name)
        : AbstDynamicObject(x, y, w, h, color, name)
    {
        setVelX(-1);

        m_collision_true_fix_object_func.at(1)  // 右壁
            = [this](int object_x, int object_y) {
                  setVelX(-1);
                  //setPosX(object_x - getWidth()); // TODO バグ
              };
        m_collision_true_fix_object_func.at(2)  // 地面
            = [this](int object_x, int object_y) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(object_y - getHeight());
              };

        m_collision_true_fix_object_func.at(3)  // 左壁
            = [this](int object_x, int object_y) {
                  setVelX(1);
                  setPosX(object_x + AbstFixObject::getObjectSize());
              };
    }

private:
    constexpr static double GRAVITY = 0.15;
};
