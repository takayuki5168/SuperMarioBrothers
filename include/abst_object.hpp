#pragma once

#include <vector>
#include "include/abstraction.hpp"

class AbstObject : public Abstraction
{
public:
    AbstObject(int x, int y, int w, int h, int color, std::string name)
        : Abstraction(x, y, w, h, color, name) {}
    AbstObject(int x, int y, int color, std::string name, std::vector<Point> frame_points)
        : Abstraction(x, y, color, name, frame_points) {}
};
