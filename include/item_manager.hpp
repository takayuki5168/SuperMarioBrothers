#pragma once

#include "include/abst_dynamic_object_manager.hpp"
#include "include/abst_item.hpp"
#include "fix_object_manager.hpp"

class ItemManager : public AbstDynamicObjectManager
{
public:
    ItemManager() : AbstDynamicObjectManager() {}

    void updateCollision(std::unique_ptr<FixObjectManager>& fix_object_manager)
    {
        updateCollisionWithFixObject(fix_object_manager);
        //updateCollisionWithUniqueObject();
    }

private:
};
