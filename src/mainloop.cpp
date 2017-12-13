#include <iostream>
#include <chrono>
#include "include/mainloop.hpp"

MainLoop::MainLoop()
{
    m_window_rect = SDL_Rect{0, 0, static_cast<uint16_t>(WINDOW_WIDTH), static_cast<uint16_t>(WINDOW_HEIGHT)};
    mario = std::make_shared<Mario>();

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BPP, SDL_HWSURFACE);
}

void MainLoop::execute()
{
    while (not m_exit_flag) {
        auto start_time = std::chrono::system_clock::now();

        m_event_manager->execute();  //!< イベントの処理

        updatePos();       //!< 位置の更新
        judgeCollision();  //!< 当たり判定
        draw();            //!< 描画

        auto end_time = std::chrono::system_clock::now();
        auto diff_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        SDL_Delay(16 - diff_time);  // 16ms周期
    }
}

void MainLoop::updatePos()
{
    mario->updatePos();
}

void MainLoop::judgeCollision()
{
}

void MainLoop::draw()
{
    m_window = SDL_GetVideoSurface();
    SDL_FillRect(m_window, &m_window_rect, SDL_MapRGB(m_window->format, 0, 0, 0));

    // 描画
    mario->draw(m_window);

    // 更新
    SDL_UpdateRect(m_window, 0, 0, 0, 0);
    //SDL_Flip(m_window);
}
