#pragma once

#include <fstream>
#include "include/params.hpp"
#include "include/abst_manager.hpp"

class AbstFixObjectManager : public AbstManager
{
public:
    explicit AbstFixObjectManager(std::string file_name)
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
            }
            cnt++;
        }
    }

    std::vector<std::vector<int>> getObjectMap() { return m_object_map; }

protected:
    std::vector<std::vector<int>> m_object_map;
};
