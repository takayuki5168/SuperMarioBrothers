/*#pragma once

#include <vector>
#include "include/abst_fix_object_manager.hpp"
#include "include/abst_fix_block.hpp"
#include "include/brick_block.hpp"
#include "include/params.hpp"

class FixBlockManager : public AbstFixObjectManager
{
public:
    FixBlockManager(std::string file_name) : AbstFixObjectManager(file_name)
    {
        const int block_size = AbstFixBlock::getBlockSize();

        for (int i = 0; i < m_object_map.size(); i++) {
            for (int j = 0; j < m_object_map.at(i).size(); j++) {
                switch (m_object_map.at(i).at(j)) {
                case '1':
                    m_data.push_back(std::make_unique<BrickBlock>(j * block_size, i * block_size));
                    break;
                default:
                    break;
                }
            }
        }
    }

    std::vector<std::vector<int>> getBlockMap() { return m_object_map; }

private:
};
*/
