#pragma once

#include <iostream>
#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "include/event_manager.hpp"
#include "include/mario.hpp"
#include "include/abst_fix_block.hpp"
#include "include/fix_block_manager.hpp"
#include "include/player_manager.hpp"

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
    void updateCollision();
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

    bool m_exit_flag = false;

    std::unique_ptr<FixBlockManager> m_fix_block_manager = nullptr;
    //std::unique_ptr<UniqueBlockManager> m_unique_block_manager = nullptr;
    std::unique_ptr<PlayerManager> m_player_manager = nullptr;
    //std::unique_ptr<EnemyManager>m_enemy_manager= nullptr;
    std::unique_ptr<EventManager> m_event_manager = std::make_unique<EventManager>(m_event);
};

inline MainLoop& mainLoop() { return MainLoop::instance(); }
