#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <memory>


class EventManager
{
public:
    EventManager(SDL_Event event) : m_event(event) {}
    void execute();

private:
    SDL_Event m_event;
};
