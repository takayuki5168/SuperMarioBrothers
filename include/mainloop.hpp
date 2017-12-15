#pragma once

#include <iostream>
#include <memory>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "include/event_manager.hpp"
#include "include/mario.hpp"
#include "include/abst_fix_object.hpp"
#include "include/fix_object_manager.hpp"
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

    int m_which_x = 1;  // !< マリオが動くか画面が動くか
    double m_window_x = 0;

    bool m_exit_flag = false;
    int m_input_type = 0;
  
    SDL_Rect rect = SDL_Rect{-10, 0, 100, 100};

    std::unique_ptr<FixObjectManager> m_fix_object_manager = nullptr;
    //std::unique_ptr<UniqueBlockManager> m_unique_block_manager = nullptr;
    std::unique_ptr<PlayerManager> m_player_manager = nullptr;
    //std::unique_ptr<EnemyManager>m_enemy_manager= nullptr;
    std::unique_ptr<EventManager> m_event_manager = nullptr;  //std::make_unique<EventManager>(m_event);
};

inline MainLoop& mainLoop() { return MainLoop::instance(); }
