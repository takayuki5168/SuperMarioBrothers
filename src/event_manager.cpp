#include <iostream>
#include "include/event_manager.hpp"

void EventManager::execute()
{
    if (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_KEYDOWN:
            switch (m_event.key.keysym.sym) {
            case SDLK_UP:
                std::cout << "up" << std::endl;
                break;
            case SDLK_DOWN:
                break;
            case SDLK_RIGHT:
                break;
            case SDLK_LEFT:
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
    return;
}
