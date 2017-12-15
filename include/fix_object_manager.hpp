#pragma once

#include <fstream>
#include "include/params.hpp"
#include "include/abst_manager.hpp"
#include "include/brick_block.hpp"

class FixObjectManager : public AbstManager
{
public:
    explicit FixObjectManager(std::string file_name)
        : AbstManager()
    {
        std::ifstream ifs(file_name);
        std::string str;
        int cnt = 0;
        const int object_size = AbstFixObject::getObjectSize();

        // 固定ブロックの初期化
        m_object_map.resize(Params::WINDOW_HEIGHT / object_size);
        while (getline(ifs, str)) {
            m_object_map.at(cnt).resize(str.size());
            for (int i = 0; i < str.size(); i++) {
                int object = str[i];
                m_object_map.at(cnt).at(i) = object;
                switch (object) {
                case '1':
                    m_data.push_back(std::make_unique<BrickBlock>(i * object_size, cnt * object_size));
                    break;
                default:
                    break;
                }
            }
            cnt++;
        }
    }

    std::vector<std::vector<int>> getObjectMap() { return m_object_map; }

protected:
    std::vector<std::vector<int>> m_object_map;
};
