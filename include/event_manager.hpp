#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <memory>
#include "include/player_manager.hpp"

class EventManager
{
public:
    EventManager(SDL_Event event, int input_type)
        : m_event(event), m_input_type(input_type) {}

    void execute(std::unique_ptr<PlayerManager>& player_manager, double& window_vel_x, int which_x)
    {
        int player = 0;


        if (m_input_type == 0) {
            if (SDL_PollEvent(&m_event)) {
                if (m_event.type == SDL_KEYDOWN) {
                    if (m_event.key.keysym.sym == SDLK_UP and player_manager->getData().at(player)->getGravity() == 0) {
                        top_key = true;
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
                player_manager->updateVelY(player, -0.5);
                top_cnt--;
            } else {
                top_key = false;
                top_cnt = 12;
            }
            if (right_key) {
                if (player_manager->getData().at(player)->getGravity() == 0) {
                    if (which_x == 0) {
                        player_manager->updateVelX(player, 0.2, 3);
                    } else if (which_x == 1) {
                        updateVelX(window_vel_x, -0.2, 3);
                    }
                } else {
                    if (which_x == 0) {
                        player_manager->updateVelX(player, 0.05, 2);
                    } else if (which_x == 1) {
                        updateVelX(window_vel_x, -0.05, 3);
                    }
                }
            }
            if (bottom_key) {
            }
            if (left_key) {
                if (player_manager->getData().at(player)->getGravity() == 0) {
                    if (which_x == 0) {
                        player_manager->updateVelX(player, -0.2, 3);
                    } else if (which_x == 1) {
                        updateVelX(window_vel_x, 0.2, 3);
                    }
                } else {
                    if (which_x == 0) {
                        player_manager->updateVelX(player, -0.05, 2);
                    } else if (which_x == 1) {
                        updateVelX(window_vel_x, 0.05, 3);
                    }
                }
            }
        }
    }

    void updateVelX(double& vel_x, double diff_vel_x, double max_vel = m_max_vel) { vel_x = MathUtil::setInRange(vel_x + diff_vel_x, max_vel); }

private:
    SDL_Event m_event;
    int m_input_type;
    bool top_key = 0;
    bool right_key = 0;
    bool bottom_key = 0;
    bool left_key = 0;
    int top_cnt = 0;

    static constexpr double m_max_vel = 5;
};
