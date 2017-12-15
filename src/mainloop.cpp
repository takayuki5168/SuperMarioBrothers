#include <iostream>
#include <chrono>
#include "include/mainloop.hpp"
#include "include/params.hpp"

MainLoop::MainLoop()
{
    m_window_rect = SDL_Rect{0, 0, static_cast<uint16_t>(Params::WINDOW_WIDTH), static_cast<uint16_t>(Params::WINDOW_HEIGHT)};

    {
        m_player_manager = std::make_unique<PlayerManager>();

        auto mario = std::make_unique<Mario>();
        m_player_manager->add(std::move(mario));
    }

    {
        m_fix_object_manager = std::make_unique<FixObjectManager>("../data/back_fix_object.txt");
    }

    m_event_manager = std::make_unique<EventManager>(m_event, m_input_type);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(Params::WINDOW_WIDTH, Params::WINDOW_HEIGHT, Params::BPP, SDL_HWSURFACE);
}

void MainLoop::execute()
{
    while (not m_exit_flag) {
        auto start_time = std::chrono::system_clock::now();

        m_event_manager->execute(m_player_manager);  //!< イベントの処理

        updatePos();        //!< 位置の更新
        updateCollision();  //!< 当たり判定
        draw();             //!< 描画

        auto end_time = std::chrono::system_clock::now();
        auto diff_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        SDL_Delay(16 - diff_time);  // 16ms周期
    }
}

void MainLoop::updatePos()
{
    m_player_manager->updatePos();
    m_fix_object_manager->updatePos();
    //m_fix_object_manager->showVelXAll();
}

void MainLoop::updateCollision()
{
    m_player_manager->updateCollision(m_fix_object_manager);
}

void MainLoop::draw()
{
    m_window = SDL_GetVideoSurface();
    SDL_FillRect(m_window, &m_window_rect, SDL_MapRGB(m_window->format, 0, 0, 0));

    // 基準点の変更
    m_window_x = 300 - m_player_manager->getData().at(0)->getPos().x;

    // 描画
    m_player_manager->draw(m_window, m_window_x);
    m_fix_object_manager->draw(m_window, m_window_x);

    // 更新
    SDL_UpdateRect(m_window, 0, 0, 0, 0);
    SDL_Flip(m_window);
}
