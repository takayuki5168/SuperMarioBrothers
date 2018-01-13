#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstItem : public AbstObject
{
public:
    AbstItem(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name)
    {
        m_gravity = GRAVITY;
        setVelX(1);

        m_collision_true_fix_object_func.at(0)  // 天井
            = [this](Point object, Point, Point) {
                  setVelYPlus();
                  setPosY(object.y + AbstFixObject::getObjectSize());
              };
        m_collision_true_fix_object_func.at(1)  // 右壁
            = [this](Point, Point, Point) {
                  setVelX(-1);
                  //setPosX(object_x - getWidth()); // TODO バグ
              };
        m_collision_true_fix_object_func.at(2)  // 地面
            = [this](Point object, Point, Point) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(object.y - getHeight());
              };
        m_collision_true_fix_object_func.at(3)  // 左壁
            = [this](Point object, Point, Point) {
                  setVelX(1);
                  setPosX(object.x + AbstFixObject::getObjectSize());
              };

        m_collision_false_fix_object_func.at(2)
            = [this](Point, Point, Point) { setGravity(GRAVITY); };
    }

private:
    constexpr static double GRAVITY = 0.15;
};
