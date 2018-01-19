#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "include/event_manager.hpp"
#include "include/collision_manager.hpp"
#include "include/abst_player.hpp"
#include "include/abst_enemy.hpp"
#include "include/abst_item.hpp"
#include "include/abst_rect_object.hpp"
#include "include/abst_unique_object.hpp"
#include "include/pipe.hpp"

class MainLoop
{
public:
    static MainLoop& instance()
    {
        static MainLoop inst;
        return inst;
    }

    void execute();
    void updateOther();
    void updatePos();
    void updateCollision();
    void updateStatus();
    void draw();

    void initTestWorld();
    void initIceWorld();

private:
    MainLoop();
    ~MainLoop() { delete m_window; }

    SDL_Surface* m_window;
    SDL_Rect m_window_rect;
    SDL_Event m_event;

    int m_which_x = 1;  // !< マリオが動くか画面が動くか
    double m_window_x = 0;

    bool m_exit_flag = false;
    int m_input_type = 0;

    //!< マネージャークラスのポインタ
    std::unique_ptr<EventManager> m_event_manager = nullptr;
    std::unique_ptr<CollisionManager> m_collision_manager = nullptr;

    //!< Abstractionの継承クラスのポインタ
    std::vector<std::shared_ptr<AbstPlayer>> m_player_vec;
    std::vector<std::shared_ptr<AbstEnemy>> m_enemy_vec;

    std::vector<std::shared_ptr<AbstItem>> m_item_vec;

    std::vector<std::shared_ptr<AbstRectObject>> m_rect_object_vec;
    std::vector<std::shared_ptr<AbstUniqueObject>> m_unique_object_vec;

    //!< マップ
    std::vector<std::vector<int>> m_fix_object_map;

    std::string m_back_file_name;

    std::chrono::system_clock::time_point m_start_chrono_time;
    double m_time;

    std::unordered_map<std::string, std::function<void(void)>> m_file_to_init_func;
    std::string m_next_world = "";
};

inline MainLoop& mainLoop() { return MainLoop::instance(); }
