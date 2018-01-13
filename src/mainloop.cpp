#include <iostream>
#include <fstream>
#include "include/mainloop.hpp"
#include "include/params.hpp"
#include "include/mario.hpp"
#include "include/kuribo.hpp"
#include "include/gabon.hpp"
#include "include/brick_block.hpp"
#include "include/wooden_horizontal_lift.hpp"
#include "include/wooden_circle_lift.hpp"

MainLoop::MainLoop()
{
    m_window_rect = SDL_Rect{0, 0, static_cast<uint16_t>(Params::WINDOW_WIDTH), static_cast<uint16_t>(Params::WINDOW_HEIGHT)};

    {  // Player
        auto mario = std::make_unique<Mario>();
        m_player_vec.push_back(std::move(mario));
    }

    {  // Enemy
        auto kuribo1 = std::make_unique<Kuribo>();
        m_enemy_vec.push_back(std::move(kuribo1));

        auto kuribo2 = std::make_unique<Kuribo>(1000);
        m_enemy_vec.push_back(std::move(kuribo2));

        auto gabon1 = std::make_unique<Gabon>(100);
        m_enemy_vec.push_back(std::move(gabon1));
    }

    {// Item
        //auto kuribo = std::make_unique<Kuribo>();
        //m_item_vec.push_back(std::move(kuribo));
    }

    {  // FixObject
        std::ifstream ifs("../data/back_fix_object.txt");
        std::string str;
        int cnt = 0;
        const int object_size = AbstFixObject::getObjectSize();

        // 固定ブロックの初期化
        m_fix_object_map.resize(Params::WINDOW_HEIGHT / object_size);
        while (getline(ifs, str)) {
            m_fix_object_map.at(cnt).resize(str.size());
            for (int i = 0; i < str.size(); i++) {
                int object = str[i];
                m_fix_object_map.at(cnt).at(i) = object;
                switch (object) {
                case '1':
                    m_fix_object_vec.push_back(std::make_shared<BrickBlock>(i * object_size, cnt * object_size));
                    break;
                case '2':
                    break;
                default:
                    break;
                }
            }
            cnt++;
        }
    }

    {  // UniqueObject
        auto wooden_circle_lift1 = std::make_unique<WoodenCircleLift>(400, 200);
        m_unique_object_vec.push_back(std::move(wooden_circle_lift1));

        auto wooden_horizontal_lift1 = std::make_unique<WoodenHorizontalLift>(80, 240);
        m_unique_object_vec.push_back(std::move(wooden_horizontal_lift1));
    }

    {  // EventManager
        m_event_manager = std::make_unique<EventManager>(m_event, m_input_type, m_player_vec);
    }

    {  // CollisionManager
        m_collision_manager = std::make_unique<CollisionManager>(m_player_vec, m_enemy_vec, m_fix_object_vec);
    }

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(Params::WINDOW_WIDTH, Params::WINDOW_HEIGHT, Params::BPP, SDL_HWSURFACE);

    m_start_chrono_time = std::chrono::system_clock::now();
}

void MainLoop::execute()
{
    while (not m_exit_flag) {
        double start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start_chrono_time).count();

        m_event_manager->execute();  //!< イベントの処理

        updatePos();        //!< 位置の更新
        updateCollision();  //!< 当たり判定
        draw();             //!< 描画

        m_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start_chrono_time).count();
        double diff_time = m_time - start_time;
        SDL_Delay(16 - diff_time);  // 16ms周期
    }
}

void MainLoop::updatePos()
{
    for (auto player : m_player_vec) {
        player->updatePos(m_time);
    }
    for (auto enemy : m_enemy_vec) {
        enemy->updatePos(m_time);
    }
    for (auto item : m_item_vec) {
        item->updatePos(m_time);
    }
    for (auto fix_object : m_fix_object_vec) {
        fix_object->updatePos(m_time);
    }
    for (auto unique_object : m_unique_object_vec) {
        unique_object->updatePos(m_time);
    }
}

void MainLoop::updateCollision()
{
    m_collision_manager->updateCollision(m_fix_object_map, m_unique_object_vec);
    /*
    m_player_vec->updateCollision(m_fix_object_manager);
    m_enemy_manager->updateCollision(m_fix_object_manager);
    m_item_manager->updateCollision(m_fix_object_manager);
  */
}

void MainLoop::draw()
{
    m_window = SDL_GetVideoSurface();
    SDL_FillRect(m_window, &m_window_rect, SDL_MapRGB(m_window->format, 0, 0, 0));

    // 基準点の変更
    m_window_x = 300 - m_player_vec.at(0)->getPos().x;

    // 描画
    for (auto player : m_player_vec) {
        player->draw(m_window, m_window_x);
    }
    for (auto enemy : m_enemy_vec) {
        enemy->draw(m_window, m_window_x);
    }
    for (auto item : m_item_vec) {
        item->draw(m_window, m_window_x);
    }
    for (auto fix_object : m_fix_object_vec) {
        fix_object->draw(m_window, m_window_x);
    }
    for (auto unique_object : m_unique_object_vec) {
        unique_object->draw(m_window, m_window_x);
    }


    // 更新
    SDL_UpdateRect(m_window, 0, 0, 0, 0);
    SDL_Flip(m_window);
}
