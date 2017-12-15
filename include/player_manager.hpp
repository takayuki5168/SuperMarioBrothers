#pragma once

#include "include/abst_dynamic_object_manager.hpp"
#include "include/abst_player.hpp"
#include "fix_block_manager.hpp"

class PlayerManager : public AbstDynamicObjectManager
{
public:
    PlayerManager() : AbstDynamicObjectManager() {}
    void updateCollision(std::unique_ptr<FixBlockManager>& fix_block_manager)
    {
        updateCollisionWithFixBlock(fix_block_manager);
    }

private:
};
