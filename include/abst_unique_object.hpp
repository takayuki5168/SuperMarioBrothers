#pragma once

#include "include/abst_object.hpp"

class AbstUniqueObject : public AbstObject
{
public:
    explicit AbstUniqueObject(int x, int y, int color, std::string name, std::vector<Point> frame_points)
        : AbstObject(x, y, color, name, frame_points) {}

private:
};
