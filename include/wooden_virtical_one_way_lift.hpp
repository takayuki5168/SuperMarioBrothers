#pragma once

#include "include/abst_rect_object.hpp"

class WoodenVirticalOneWayLift : public AbstRectObject
{
public:
    WoodenVirticalOneWayLift(int x, int y, bool restore = false)
        : AbstRectObject(x, y, LIFT_WIDTH, LIFT_HEIGHT, 0x8d3800, "WoodenVirticalLift"), m_restore(restore) {}

    virtual void updatePosDecorator(double time)
    {
        setVelY(-1.3);
        if (m_pos.m_y > Params::WINDOW_HEIGHT or m_pos.m_y + m_height < 0) {
            if (m_restore) {
                m_pos.m_y = Params::WINDOW_HEIGHT;
            } else {
                m_is_alive = false;
            }
        }
    }

private:
    static constexpr int LIFT_WIDTH = Params::BLOCK_SIZE * 4;
    static constexpr int LIFT_HEIGHT = Params::BLOCK_SIZE * 1;

    bool m_restore = false;

    static constexpr int TIME_STEP = 2000;
};
