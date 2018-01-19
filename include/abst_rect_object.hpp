#pragma once

#include <vector>
#include "include/abst_object.hpp"

class AbstRectObject : public AbstObject
{
public:
    AbstRectObject(int x, int y, int w, int h, int color, std::string name)
        : AbstObject(x, y, w, h, color, name) {}

    // 土管用
    virtual std::array<std::string, 2> getFileNameVec() const {}
    virtual std::array<Point, 2> getPosVec() const {}
    virtual void setPosByFile(std::string) {}

private:
};
