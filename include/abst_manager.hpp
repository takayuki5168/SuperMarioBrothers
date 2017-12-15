#pragma once

#include <memory>
#include "include/abst_object.hpp"

class AbstManager
{
public:
    explicit AbstManager() {}

    virtual void add(std::unique_ptr<AbstObject> object)
    {
        data.push_back(std::move(object));
    }

    virtual void updatePos()
    {
        for (int i = 0; i < data.size(); i++) {
            data.at(i)->updatePos();
        }
    }

    virtual void updateCollision() {}

    virtual void draw(SDL_Surface* m_window)
    {
        for (int i = 0; i < data.size(); i++) {
            data.at(i)->draw(m_window);
        }
    }

protected:
    std::vector<std::unique_ptr<AbstObject>> data;

private:
};
