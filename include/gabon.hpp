#pragma once

#include "include/abst_enemy.hpp"

class Gabon : public AbstEnemy
{
public:
    Gabon(int x = 500, int y = 30)
        : AbstEnemy(x, y, 40, 40, 0x003d00, "Gabon")
    {
        setVelX(0);

        m_my_func_collision_true_with_object.at(1)  // 右壁
            = [this](std::shared_ptr<Abstraction>) {};
        m_my_func_collision_true_with_object.at(2)  // 地面
            = [this](std::shared_ptr<Abstraction> abstraction) {
                  setGravity(0);
                  setVelYMinus();
                  setPosY(abstraction->getPos().m_y - getHeight());
              };

        m_my_func_collision_true_with_object.at(3)  // 左壁
            = [this](std::shared_ptr<Abstraction>) {};
    }

private:
};
