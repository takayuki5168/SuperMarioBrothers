#pragma once

#include <fstream>
#include <vector>
#include "include/abst_manager.hpp"
#include "include/abst_fix_block.hpp"
#include "include/brick_block.hpp"
#include "include/params.hpp"

class FixBlockManager : public AbstManager
{
public:
    FixBlockManager() : AbstManager()
    {
        std::ifstream ifs("../data/back_fix_block.hpp");
        std::string str;
        int cnt = 0;
        const int block_size = AbstFixBlock::getBlockSize();

        // 固定ブロックの初期化
        m_block_map.resize(Params::WINDOW_HEIGHT / block_size);
        while (getline(ifs, str)) {
            m_block_map.at(cnt).resize(str.size());
            for (int i = 0; i < str.size(); i++) {
                int block = str[i];
                m_block_map.at(cnt).at(i) = block;

                switch (block) {
                case '1':
                    data.push_back(std::make_unique<BrickBlock>(i * block_size, cnt * block_size));
                    break;
                default:
                    break;
                }
            }
            cnt++;
        }
    }

private:
    std::vector<std::vector<int>> m_block_map;
};
