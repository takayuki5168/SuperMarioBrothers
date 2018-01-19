#pragma once

#include "include/abst_unique_object.hpp"

class WoodenRotateRect : public AbstUniqueObject
{
public:
    WoodenRotateRect(int x, int y, int length)
        : AbstUniqueObject(x, y, 0x8d3800, "WoodenRotateRect",
              {Point{0, 0}, Point{2 * length, 0}, Point{2 * length, 2 * length}, Point{0, 2 * length}}),
          m_length(length), m_center_pos(Point{x + length, y + length}) {}


    virtual void updatePosDecorator(double time)
    {
        int t = static_cast<int>(time);
        double theta = 0.1;  //t * 0.0005;
        double x = getPos().m_x;
        double y = getPos().m_y;

        m_frame_points = {m_center_pos + Point{m_length * std::cos(theta), m_length * std::sin(theta)} - m_pos,
            m_center_pos + Point{m_length * std::sin(theta), -m_length * std::cos(theta)} - m_pos,
            m_center_pos + Point{-m_length * std::cos(theta), -m_length * std::sin(theta)} - m_pos,
            m_center_pos + Point{-m_length * std::sin(theta), m_length * std::cos(theta)} - m_pos};


        /*
        int max_w = 0, max_h = 0, min_w = Params::WINDOW_WIDTH, min_h = Params::WINDOW_HEIGHT;
        for (int i = 0; i < m_frame_points.size(); i++) {
            if (max_w < m_frame_points.at(i).m_x) {
                max_w = m_frame_points.at(i).m_x;
            } else if (min_w > m_frame_points.at(i).m_x) {
                min_w = m_frame_points.at(i).m_x;
            }
            if (max_h < m_frame_points.at(i).m_y) {
                max_h = m_frame_points.at(i).m_y;
            } else if (min_h > m_frame_points.at(i).m_y) {
                min_h = m_frame_points.at(i).m_y;
            }
        }
        m_width = max_w - min_w;
        m_height = max_h - min_h;*/
    }

private:
    static constexpr int TIME_STEP = 2000;

    int m_length;
    Point m_center_pos;
};
