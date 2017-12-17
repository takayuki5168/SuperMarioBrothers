#pragma once

#include <vector>
#include "include/abst_object.hpp"
#include "include/abst_fix_object.hpp"

class AbstDynamicObject : public AbstObject
{
public:
    explicit AbstDynamicObject(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name)
    {
        m_gravity = GRAVITY;
        {
            // 基本的に壁にあたったら止まる関数
            m_collision_true_fix_object_func.at(0)  // 天井
                = [this](int object_x, int object_y) {
                      setVelYPlus();
                      setPosY(object_y + AbstFixObject::getObjectSize());
                  };
            m_collision_true_fix_object_func.at(1)  // 右壁
                = [this](int object_x, int object_y) {
                      setVelXMinus();
                      setPosX(object_x - getWidth());
                  };
            m_collision_true_fix_object_func.at(2)  // 地面
                = [this](int object_x, int object_y) {
                      setGravity(0);
                      setVelYMinus();
                      setPosY(object_y - getHeight());

                      // 摩擦
                      auto vel_x = getVel().x;
                      if (vel_x != 0) {
                          auto tmp = vel_x;
                          vel_x = vel_x - 0.05 * vel_x / std::abs(vel_x);
                          if (tmp * vel_x < 0) {
                              vel_x = 0;
                          }
                          setVelX(vel_x);
                      }
                  };
            m_collision_true_fix_object_func.at(3)  // 左壁
                = [this](int object_x, int object_y) {
                      setVelXPlus();
                      setPosX(object_x + AbstFixObject::getObjectSize());
                  };

            // 基本的に重力で落ちる関数
            m_collision_false_fix_object_func.at(2)
                = [this](int object_x, int object_y) { setGravity(GRAVITY); };
        }

        {
            // 基本的に壁にあたったら止まる関数
            m_collision_true_unique_object_func.at(0)  // 天井
                = [this](int object_x, int object_y, int, int h) {
                      setVelYPlus();
                      setPosY(object_y + h);
                  };
            m_collision_true_unique_object_func.at(1)  // 右壁
                = [this](int object_x, int object_y, int, int) {
                      setVelXMinus();
                      setPosX(object_x - getWidth());
                  };
            m_collision_true_unique_object_func.at(2)  // 地面
                = [this](int object_x, int object_y, int, int) {
                      setGravity(0);
                      setVelYMinus();
                      setPosY(object_y - getHeight());

                      // 摩擦
                      auto vel_x = getVel().x;
                      if (vel_x != 0) {
                          auto tmp = vel_x;
                          vel_x = vel_x - 0.05 * vel_x / std::abs(vel_x);
                          if (tmp * vel_x < 0) {
                              vel_x = 0;
                          }
                          setVelX(vel_x);
                      }
                  };
            m_collision_true_unique_object_func.at(3)  // 左壁
                = [this](int object_x, int object_y, int w, int) {
                      setVelXPlus();
                      setPosX(object_x + w);
                  };
            // 基本的に重力で落ちる関数
            m_collision_false_unique_object_func.at(2)
                = [this](int object_x, int object_y, int, int) { setGravity(GRAVITY); };
        }
    }

protected:
    //constexpr static
    double GRAVITY = 0.15;
};
