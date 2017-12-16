#pragma once

#include "include/abst_enemy.hpp"

class Kuribo : public AbstEnemy
{
public:
    Kuribo(int x = 500, int y = 30)
        : AbstEnemy(x, y, 40, 40, 0x3d0000, "Kuribo") {}

private:
};
