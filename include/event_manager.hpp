#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <memory>
#include "include/abst_player.hpp"

class EventManager
{
public:
    EventManager(SDL_Event event, int input_type, std::vector<std::shared_ptr<AbstPlayer>> player_vec)
        : m_event(event), m_input_type(input_type), m_player_vec(player_vec) {}

    void execute()
    {
        int player = 0;

        if (m_input_type == 0) {
            if (SDL_PollEvent(&m_event)) {
                if (m_event.type == SDL_KEYDOWN) {
                    if (m_event.key.keysym.sym == SDLK_UP) {
                        if (m_player_vec.at(player)->getGravity() == 0) {
                            top_key = true;
                        } else if (m_player_vec.at(player)->getCollision(3) == true) {  // 壁キック
                            m_player_vec.at(player)->setVelY(-5.0);
                            m_player_vec.at(player)->updateVelX(2.0, 2.0);
                        } else if (m_player_vec.at(player)->getCollision(1) == true) {  // 壁キック
                            m_player_vec.at(player)->setVelY(-5.0);
                            m_player_vec.at(player)->updateVelX(-2.0, 2.0);
                        }
                    } else if (m_event.key.keysym.sym == SDLK_DOWN) {
                        bottom_key = true;
                    } else if (m_event.key.keysym.sym == SDLK_RIGHT) {
                        right_key = true;
                    } else if (m_event.key.keysym.sym == SDLK_LEFT) {
                        left_key = true;
                    }
                } else if (m_event.type == SDL_KEYUP) {
                    if (m_event.key.keysym.sym == SDLK_UP and top_key) {
                        top_key = false;
                    } else if (m_event.key.keysym.sym == SDLK_DOWN and bottom_key) {
                        bottom_key = false;
                    } else if (m_event.key.keysym.sym == SDLK_RIGHT and right_key) {
                        right_key = false;
                    } else if (m_event.key.keysym.sym == SDLK_LEFT and left_key) {
                        left_key = false;
                    }
                }
            }

            if (top_key and top_cnt > 0) {
                m_player_vec.at(player)->updateVelY(-0.6);
                top_cnt--;
            } else {
                top_key = false;
                top_cnt = 15;
            }
            if (right_key) {
                if (m_player_vec.at(player)->getGravity() == 0) {
                    m_player_vec.at(player)->updateVelX(0.2, 3);
                } else {
                    m_player_vec.at(player)->updateVelX(0.05, 2.5);
                }
            }
            if (bottom_key) {
            }
            if (left_key) {
                if (m_player_vec.at(player)->getGravity() == 0) {
                    m_player_vec.at(player)->updateVelX(-0.2, 3);
                } else {
                    m_player_vec.at(player)->updateVelX(-0.05, 2.5);
                }
            }
        }
    }

private:
    SDL_Event m_event;

    int m_input_type;

    bool top_key = 0;
    bool right_key = 0;
    bool bottom_key = 0;
    bool left_key = 0;
    int top_cnt = 0;

    std::vector<std::shared_ptr<AbstPlayer>> m_player_vec;
};
