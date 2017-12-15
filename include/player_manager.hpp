#pragma once

#include "include/abst_dynamic_object_manager.hpp"
#include "include/abst_player.hpp"
#include "fix_block_manager.hpp"

class PlayerManager : public AbstDynamicObjectManager
{
public:
    PlayerManager() : AbstDynamicObjectManager() {}
    void updateCollision(std::unique_ptr<FixBlockManager>& fix_block_manager)
    //void updateCollision(std::unique_ptr<AbstFixObjectManager>& fix_block_manager)
    {
        updateCollisionWithFixObject(fix_block_manager);
    }

private:
};
