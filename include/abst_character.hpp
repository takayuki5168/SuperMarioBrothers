#pragma once

#include <vector>
#include "include/abstraction.hpp"
//#include "include/abst_fix_object.hpp"

class AbstCharacter : public Abstraction
{
public:
    explicit AbstCharacter(int x, int y, int w, int h, int color, std::string name)
        : Abstraction(x, y, w, h, color, name)
    {
        m_gravity = GRAVITY;
        {
            // 基本的に壁にあたったら止まる関数
            m_my_func_collision_true.at(0) = [this](Point object, Point wh, Point) {  // 天井
                setVelYPlus();
                setPosY(object.m_y + wh.m_y);
            };
            m_my_func_collision_true.at(0) = [this](Point object, Point, Point) {  // 右壁
                setVelXMinus();
                setPosX(object.m_x - m_rect.w);
            };
            m_my_func_collision_true.at(0) = [this](Point object, Point, Point) {  // 地面
                setGravity(0);
                setVelYMinus();
                setPosY(object.m_y - m_rect.h);

                // 摩擦
                auto vel_x = getVel().m_x;
                if (vel_x != 0) {
                    auto tmp = vel_x;
                    vel_x = vel_x - 0.05 * vel_x / std::abs(vel_x);
                    if (tmp * vel_x < 0) {
                        vel_x = 0;
                    }
                    setVelX(vel_x);
                }
            };
            m_my_func_collision_true.at(0) = [this](Point object, Point wh, Point) {  // 左壁
                setVelXPlus();
                setPosX(object.m_x + wh.m_x);
            };
        };

        // 基本的に重力で落ちる関数
        m_my_func_collision_false.at(2)
            = [this](Point, Point, Point) { setGravity(GRAVITY); };
    }

    /*
        {
            // 基本的に壁にあたったら止まる関数
            m_collision_true_unique_obj
                = [this](Point object, Point wh, Point) {  // 天井
                      setVelYPlus();
                      setPosY(object.y + wh.y);
                  };
            m_collision_true_unique_object_func.at(1)
                = [this](Point object, Point, Point) {  // 右壁
                      setVelXMinus();
                      setPosX(object.x - getWidth());
                  };
            m_collision_true_unique_object_func.at(2)
                = [this](Point object, Point, Point pos_diff) {  // 地面
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
            m_collision_true_unique_object_func.at(3)
                = [this](Point object, Point wh, Point) {  // 左壁
                      setVelXPlus();
                      setPosX(object.x + wh.x);
                  };
            // 基本的に重力で落ちる関数
            m_collision_false_unique_object_func.at(2)
                = [this](Point, Point, Point) { setGravity(GRAVITY); };
				}
}
*/
protected:
    double GRAVITY = 0.15;
    //bool m_unique_object_bottom_flag = false;
};
