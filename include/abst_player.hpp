#pragma once

#include <vector>
#include "include/abst_character.hpp"

class AbstPlayer : public AbstCharacter
{
public:
    explicit AbstPlayer(int x, int y, int w, int h, int color, std::string name)
        : AbstCharacter(x, y, w, h, color, name)
    {
        {  // AbstCharacterと衝突した時
            m_other_func_collision_true_with_character
                = [this](std::shared_ptr<Abstraction> abstraction) {
                      if (abstraction->getIdx() < 0) {
                          return;
                      }

                      double abstraction_y = abstraction->getCenter().m_y;
                      if (abstraction_y > getCenter().m_y) {
                      } else {
                      }
                  };
        }
    }

private:
};
