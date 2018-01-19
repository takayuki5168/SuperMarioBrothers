#pragma once

#include <string>
#include "include/abst_rect_object.hpp"


class Pipe : public AbstRectObject
{
public:
    explicit Pipe(int x1, int y1, int x2, int y2, std::string file_name1, std::string file_name2)
        : AbstRectObject(x1, y1, Params::BLOCK_SIZE, Params::BLOCK_SIZE, 0x00ff00, "Pipe"),
          m_pos_vec({Point{x1, y1}, Point{x2, y2}}), m_file_name_vec({file_name1, file_name2})
    {
        m_idx = 'z';
        std::cout << m_file_name_vec.at(0) << std::endl;
    }

    virtual std::array<std::string, 2> getFileNameVec() const override { return m_file_name_vec; }
    virtual std::array<Point, 2> getPosVec() const override { return m_pos_vec; }
    virtual void setPosByFile(std::string file_name) override
    {
        if (file_name == m_file_name_vec.at(0)) {
            m_pos = m_pos_vec.at(0);
        } else {
            m_pos = m_pos_vec.at(1);
        }
    }

private:
    std::array<std::string, 2> m_file_name_vec = std::array<std::string, 2>{"a", "a"};
    std::array<Point, 2> m_pos_vec;
};
