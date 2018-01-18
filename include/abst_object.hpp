#pragma once

#include <vector>
#include "include/abstraction.hpp"

class AbstObject : public Abstraction
{
public:
    AbstObject(int x, int y, int w, int h, int color, std::string name)
        : Abstraction(x, y, w, h, color, name) { init(); }
    AbstObject(int x, int y, int color, std::string name, std::vector<Point> frame_points)
        : Abstraction(x, y, color, name, frame_points) { init(); }

private:
    void init()
    {
        m_other_func_collision_true_with_object.at(2)
            = [this](std::shared_ptr<Abstraction> abstraction) {  // 地面
                  auto pos_diff = m_pos - m_pre_pos;              //getPos() - getPrePos();
                  abstraction->updatePos(pos_diff);

              };
    }
};
