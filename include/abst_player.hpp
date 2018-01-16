#pragma once

#include <vector>
#include "include/abst_character.hpp"

class AbstPlayer : public AbstCharacter
{
public:
    explicit AbstPlayer(int x, int y, int w, int h, int color, std::string name)
        : AbstCharacter(x, y, w, h, color, name) {}

private:
};
