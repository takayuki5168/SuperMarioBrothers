#pragma once

#include <memory>
#include <vector>
#include "include/abst_object.hpp"
#include "include/abst_fix_block.hpp"

class AbstManager
{
public:
    explicit AbstManager() {}

    virtual void add(std::unique_ptr<AbstObject> object)
    {
        m_data.push_back(std::move(object));
    }

    virtual void updatePos()
    {
        for (int i = 0; i < m_data.size(); i++) {
            m_data.at(i)->updatePos();
        }
    }

    void setVel(int i, double vel_x, double vel_y) { m_data.at(i)->setVel(vel_x, vel_y); }
    void setVelX(int i, double vel_x) { m_data.at(i)->setVelX(vel_x); }
    void setVelY(int i, double vel_y) { m_data.at(i)->setVelY(vel_y); }

    void updateVel(int i, double vel_x, double vel_y) { m_data.at(i)->updateVel(vel_x, vel_y); }
    void updateVelX(int i, double vel_x) { m_data.at(i)->updateVelX(vel_x); }
    void updateVelY(int i, double vel_y) { m_data.at(i)->updateVelY(vel_y); }
    void updateVel(int i, double vel_x, double vel_y, double max_vel) { m_data.at(i)->updateVel(vel_x, vel_y, max_vel); }
    void updateVelX(int i, double vel_x, double max_vel) { m_data.at(i)->updateVelX(vel_x, max_vel); }
    void updateVelY(int i, double vel_y, double max_vel) { m_data.at(i)->updateVelY(vel_y, max_vel); }

    virtual void draw(SDL_Surface* m_window)
    {
        for (int i = 0; i < m_data.size(); i++) {
            m_data.at(i)->draw(m_window);
        }
    }

    const std::vector<std::unique_ptr<AbstObject>>& getData() { return m_data; }

protected:
    std::vector<std::unique_ptr<AbstObject>> m_data;

private:
};
