#include <iostream>
#include "include/mainloop.hpp"

MainLoop::MainLoop()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_HWSURFACE);
}

void MainLoop::execute()
{
    while (not m_exit_flag) {
        m_event_manager->execute();
        /*
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
                break;
            default:
                break;
            }
        }
		*/
    }
}

void MainLoop::draw()
{
    //m_window = SDL_GetVideoSurface();
    SDL_FillRect(m_window, &m_window_rect, SDL_MapRGB(m_window->format, 0, 0, 0));

    // 描画

    SDL_Flip(m_window);
}
