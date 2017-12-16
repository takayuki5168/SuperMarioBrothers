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

        m_collision_true_fix_object_func = std::array<std::function<void(int, int)>, 4>{
            [this](int object_x, int object_y) {  // 天井
                setVelYPlus();
                setPosY(object_y + AbstFixObject::getObjectSize());
            },
            [this](int object_x, int object_y) {  // 右壁
                setVelX(-1);
                //setPosX(object_x - getWidth()); // TODO バグ
            },
            [this](int object_x, int object_y) {  // 地面
                setGravity(0);
                setVelYMinus();
                setPosY(object_y - getHeight());
            },
            [this](int object_x, int object_y) {  // 左壁
                setVelX(1);
                setPosX(object_x + AbstFixObject::getObjectSize());
            }};

        m_collision_false_fix_object_func.at(2) =
            [this](int object_x, int object_y) { setGravity(GRAVITY); };
    }

private:
    constexpr static double GRAVITY = 0.15;
};
