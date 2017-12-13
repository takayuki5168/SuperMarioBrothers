#pragma once

#include <iostream>
#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "include/event_manager.hpp"
#include "include/mario.hpp"

class MainLoop
{
public:
    static MainLoop& instance()
    {
        static MainLoop inst;
        return inst;
    }

    void execute();
    void updatePos();
    void judgeCollision();
    void draw();

private:
    MainLoop();
    ~MainLoop()
    {
        delete m_window;
    }

    SDL_Surface* m_window;
    SDL_Rect m_window_rect;
    SDL_Event m_event;
    std::shared_ptr<EventManager> m_event_manager = std::make_unique<EventManager>(m_event);

    bool m_exit_flag = false;

    const int BPP = 32;
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;

    std::shared_ptr<Mario> mario = nullptr;
};

inline MainLoop& mainLoop() { return MainLoop::instance(); }
