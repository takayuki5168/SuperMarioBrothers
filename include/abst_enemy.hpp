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
        DEFAULT_FRICTION = 0;

        {
            m_my_func_collision_true_with_object.at(1)  // 右壁
                = [this](std::shared_ptr<Abstraction>) {
                      setVelX(-1);
                      //setPosX(object_x - getWidth()); // TODO バグ
                  };
            m_my_func_collision_true_with_object.at(2)  // 地面
                = [this](std::shared_ptr<Abstraction> abst_object) {
                      setGravity(0);
                      setVelYMinus();
                      setPosY(abst_object->getPos().m_y - getHeight());
                  };

            m_my_func_collision_true_with_object.at(3)  // 左壁
                = [this](std::shared_ptr<Abstraction> abst_object) {
                      setVelX(1);
                      setPosX(abst_object->getPos().m_x + abst_object->getWidth());
                  };
        }

        {  // AbstPlayerと衝突した時
            m_other_func_collision_true_with_character
                = [this](std::shared_ptr<Abstraction> abstraction) {
                      int other_idx = abstraction->getIdx();
                      if (other_idx < 0) {
                          return;
                      } else if (other_idx > 150 - 1 and other_idx < 200) {  // when AbstPlayer
                          double other_bottom_y = abstraction->getPos().m_y + abstraction->getHeight();
                          if (other_bottom_y < getCenter().m_y) {  // 真横以外で相手の方が高かったら
                              m_is_alive = false;
                              abstraction->updateVelY(-8.0);
                              abstraction->setState(State::Jumping);
                              abstraction->setJumpCount(20);
                          } else {  // 真横or自分の方が高かったら
                                    //abstraction->setAlive(false);
                          }
                      }
                  };
        }
    }

private:
    constexpr static double GRAVITY = 0.15;
};
