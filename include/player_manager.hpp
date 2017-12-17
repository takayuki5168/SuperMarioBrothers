#pragma once

#include "include/abst_dynamic_object_manager.hpp"
#include "include/abst_player.hpp"
#include "include/fix_object_manager.hpp"

class PlayerManager : public AbstDynamicObjectManager
{
public:
    PlayerManager() : AbstDynamicObjectManager() {}

    void updateCollision(std::unique_ptr<FixObjectManager>& fix_object_manager)
    {
        updateCollisionWithFixObject(fix_object_manager);
        //updateCollisionWithDynamicObject(enemy_manager);
        //updateCollisionWithUniqueObject();
    }

private:
};
