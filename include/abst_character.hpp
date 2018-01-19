#pragma once

#include <vector>
#include "include/abstraction.hpp"
#include "include/pipe.hpp"
#include "include/abst_rect_object.hpp"

class AbstCharacter : public Abstraction
{
public:
    explicit AbstCharacter(int x, int y, int w, int h, int color, std::string name)
        : Abstraction(x, y, w, h, color, name)
    {
        m_gravity = GRAVITY;

        {  // オブジェクトに衝突した時
            // 基本的に壁にあたったら止まる関数
            m_my_func_collision_true_with_object.at(0) = [this](std::shared_ptr<Abstraction> abstraction) {  // 天井
                setVelYPlus();
                setPosY(abstraction->getPos().m_y + abstraction->getHeight());
            };
            m_my_func_collision_true_with_object.at(1) = [this](std::shared_ptr<Abstraction> abstraction) {  // 右壁
                setVelXMinus();
                setPosX(abstraction->getPos().m_x - getWidth());
            };
            m_my_func_collision_true_with_object.at(2) = [this](std::shared_ptr<Abstraction> abstraction) {  // 地面
                setGravity(0);
                setVelYMinus();
                setPosY(abstraction->getPos().m_y - getHeight());

                int idx = abstraction->getIdx();
                // 摩擦
                if (idx == 3) {                            // 氷
                    m_friction = DEFAULT_FRICTION * 0.15;  //0.06;
                } else {
                    m_friction = DEFAULT_FRICTION;
                }
                auto vel_x = getVel().m_x;
                if (vel_x != 0) {
                    auto tmp = vel_x;
                    vel_x = vel_x - m_friction * 0.3 * vel_x / std::abs(vel_x);
                    if (tmp * vel_x < 0) {
                        vel_x = 0;
                    }
                    setVelX(vel_x);
                }
            };

            m_my_func_collision_true_with_object.at(3) = [this](std::shared_ptr<Abstraction> abstraction) {  // 左壁
                setVelXPlus();
                setPosX(abstraction->getPos().m_x + abstraction->getWidth());
            };
        }

        {  // オブジェクトに衝突していない時
            // 基本的に重力で落ちる関数
            m_my_func_collision_false_with_object.at(2)
                = [this](std::shared_ptr<Abstraction>) {
                      setGravity(GRAVITY);
                      m_friction = DEFAULT_FRICTION;
                      auto vel_x = getVel().m_x;
                      if (vel_x != 0) {
                          auto tmp = vel_x;
                          vel_x = vel_x - m_friction * 0.06 * vel_x / std::abs(vel_x);
                          if (tmp * vel_x < 0) {
                              vel_x = 0;
                          }
                          setVelX(vel_x);
                      }
                  };
        }
    }

    virtual void updatePosDecorator(double /*time*/) override {}

    void contactPipeNone() { m_contact_pipe = nullptr; }
    void contactPipe(std::shared_ptr<AbstRectObject> pipe) { m_contact_pipe = pipe; }
    std::shared_ptr<AbstRectObject> getContactPipe() { return m_contact_pipe; }

protected:
    static constexpr double GRAVITY = 0.15;
    bool m_pipe_flag = false;
    std::shared_ptr<AbstRectObject> m_contact_pipe = nullptr;
};
