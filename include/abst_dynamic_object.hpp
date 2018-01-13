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
            // fix objectにあたった時の関数
            // 基本的に壁にあたったら止まる関数
            m_collision_true_fix_object_func.at(0)  // 天井
                = [this](Point object, Point, Point) {
                      setVelYPlus();
                      setPosY(object.y + AbstFixObject::getObjectSize());
                  };
            m_collision_true_fix_object_func.at(1)  // 右壁
                = [this](Point object, Point, Point) {
                      setVelXMinus();
                      setPosX(object.x - m_rect.w);
                  };
            m_collision_true_fix_object_func.at(2)  // 地面
                = [this](Point object, Point, Point) {
                      setGravity(0);
                      setVelYMinus();
                      setPosY(object.y - m_rect.h);

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
                = [this](Point object, Point, Point) {
                      setVelXPlus();
                      setPosX(object.x + AbstFixObject::getObjectSize());
                  };

            // 基本的に重力で落ちる関数
            m_collision_false_fix_object_func.at(2)
                = [this](Point, Point, Point) { setGravity(GRAVITY); };
        }

        {
            // 基本的に壁にあたったら止まる関数
            m_collision_true_unique_object_func.at(0)  // 天井
                = [this](Point object, Point wh, Point) {
                      setVelYPlus();
                      setPosY(object.y + wh.y);
                  };
            m_collision_true_unique_object_func.at(1)  // 右壁
                = [this](Point object, Point, Point) {
                      setVelXMinus();
                      setPosX(object.x - getWidth());
                  };
            m_collision_true_unique_object_func.at(2)  // 地面
                = [this](Point object, Point, Point pos_diff) {
                      setGravity(0);
                      setVelYMinus();

                      setPosY(object.y - m_rect.h);
                      updatePos(pos_diff);

                      // 摩擦
                      auto vel_x = getVel().x;
                      if (vel_x != 0) {
                          auto tmp = vel_x;
                          vel_x = vel_x - 0.15 * vel_x / std::abs(vel_x);
                          if (tmp * vel_x < 0) {
                              vel_x = 0;
                          }
                          setVelX(vel_x);
                      }
                  };
            m_collision_true_unique_object_func.at(3)  // 左壁
                = [this](Point object, Point wh, Point) {
                      setVelXPlus();
                      setPosX(object.x + wh.x);
                  };
            // 基本的に重力で落ちる関数
            m_collision_false_unique_object_func.at(2)
                = [this](Point, Point, Point) { setGravity(GRAVITY); };
        }
    }

    //void setUniqueObjectBottom(bool flag) { m_unique_object_bottom_flag = flag; }
    //bool getUniqueObjectBottom() { return m_unique_object_bottom_flag; }

protected:
    //constexpr static
    double GRAVITY = 0.15;
    bool m_unique_object_bottom_flag = false;
};
