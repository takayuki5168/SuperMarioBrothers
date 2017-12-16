#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstPlayer : public AbstObject
{
public:
    AbstPlayer(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name)
    {
        m_gravity = GRAVITY;

        m_collision_true_fix_object_func = std::array<std::function<void(int, int)>, 4>{
            [this](int object_x, int object_y) {  // 天井
                setVelYPlus();
                setPosY(object_y + AbstFixObject::getObjectSize());
            },
            [this](int object_x, int object_y) {  // 右壁
                setVelXMinus();
                setPosX(object_x - getWidth());
            },
            [this](int object_x, int object_y) {  // 地面
                setGravity(0);
                setVelYMinus();
                setPosY(object_y - getHeight());

                // 摩擦
                auto vel_x = getVel().x;
                if (vel_x != 0) {
                    auto tmp = vel_x;
                    vel_x = vel_x - 0.13 * vel_x / std::abs(vel_x);
                    if (tmp * vel_x < 0) {
                        vel_x = 0;
                    }
                    setVelX(vel_x);
                }
            },
            [this](int object_x, int object_y) {  // 左壁
                setVelXPlus();
                setPosX(object_x + AbstFixObject::getObjectSize());
            }};

        m_collision_false_fix_object_func.at(2) =
            [this](int object_x, int object_y) { setGravity(GRAVITY); };
    }

private:
    constexpr static double GRAVITY = 0.15;
};
