#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <memory>
#include "include/abst_player.hpp"

class EventManager
{
public:
    EventManager(SDL_Event event, int input_type, std::vector<std::shared_ptr<AbstPlayer>> player_vec)  //, std::vector<std::shared_ptr<AbstRectObject>> rect_object_vec)
        : m_event(event),
          m_input_type(input_type),
          m_player_vec(player_vec)
    {
    }

    void execute(const std::string&, std::string&);

private:
    SDL_Event m_event;

    int m_input_type;

    bool top_key = 0;
    bool right_key = 0;
    bool bottom_key = 0;
    bool left_key = 0;
    int top_cnt = 0;

    std::vector<std::shared_ptr<AbstPlayer>> m_player_vec;
    //std::vector<std::shared_ptr<AbstRectObject>> m_rect_vec;

    bool top_key_flag = false;
};
