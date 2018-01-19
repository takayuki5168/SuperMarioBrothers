#include <iostream>
#include <fstream>
#include "include/event_manager.hpp"
#include "include/pipe.hpp"

void EventManager::execute(const std::string& back_file_name, std::string& next_world)  //std::vector<std::vector<int>>& fix_object_map)
{
    int player_idx = 0;

    if (m_input_type == 0) {
        if (SDL_PollEvent(&m_event)) {
            if (m_event.type == SDL_KEYDOWN) {
                if (m_event.key.keysym.sym == SDLK_UP) {
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

        if (m_player_vec.at(player_idx)->getGravity() == 0 and top_key == false) {
            m_player_vec.at(player_idx)->setState(Abstraction::State::Nothing);
        }
        if (top_key) {
            if (m_player_vec.at(player_idx)->getGravity() == 0 and m_player_vec.at(player_idx)->getState() != Abstraction::State::Jumping) {  // ジャンプし始め
                m_player_vec.at(player_idx)->updateVelY(-3.5);
                m_player_vec.at(player_idx)->setState(Abstraction::State::Jumping);
                m_player_vec.at(player_idx)->setJumpCount(20);
            } else if (m_player_vec.at(player_idx)->getVel().m_y < 0
                       and m_player_vec.at(player_idx)->getState() == Abstraction::State::Jumping
                       and m_player_vec.at(player_idx)->getJumpCount() > 0) {  // ジャンプ中
                m_player_vec.at(player_idx)->updateVelY(m_player_vec.at(player_idx)->getVel().m_y * 0.09);
                m_player_vec.at(player_idx)->updateJumpCount(-1);
            } else if (m_player_vec.at(player_idx)->getCollisionFlag(3) == true and top_key_flag == false) {  // 壁キック
                m_player_vec.at(player_idx)->setVelY(-5.0);
                m_player_vec.at(player_idx)->updateVelX(2.0, 2.0);
            } else if (m_player_vec.at(player_idx)->getCollisionFlag(1) == true and top_key_flag == false) {  // 壁キック
                m_player_vec.at(player_idx)->setVelY(-5.0);
                m_player_vec.at(player_idx)->updateVelX(-2.0, 2.0);
            }
            top_key_flag = true;
        } else {
            top_key_flag = false;
            if (m_player_vec.at(player_idx)->getJumpCount() < 20) {
                m_player_vec.at(player_idx)->setJumpCount(0);
            }
        }
        /*else {
            if (m_player_vec.at(player_idx)->getJumpCount() > 0) {
                if (m_player_vec.at(player_idx)->getVel().m_y < 0) {
                    m_player_vec.at(player_idx)->setVelY(m_player_vec.at(player_idx)->getVel().m_y * 0.5);
                }
            }
			}*/
        if (right_key) {
            if (m_player_vec.at(player_idx)->getGravity() == 0) {
                m_player_vec.at(player_idx)->updateVelX(m_player_vec.at(player_idx)->getFriction(), 3);
            } else {
                m_player_vec.at(player_idx)->updateVelX(0.1, 2.5);
            }
        }
        if (bottom_key) {
            std::shared_ptr<AbstRectObject> pipe = m_player_vec.at(player_idx)->getContactPipe();
            if (pipe != nullptr) {
                std::array<std::string, 2> file_name_vec = pipe->getFileNameVec();

                for (int i = 0; i < file_name_vec.size(); i++) {
                    if (file_name_vec.at(i) == back_file_name) {
                        next_world = file_name_vec.at(1 - i);
                        break;
                    }
                }
            }
        }
        if (left_key) {
            if (m_player_vec.at(player_idx)->getGravity() == 0) {
                //m_player_vec.at(player_idx)->updateVelX(-0.3, 3);
                m_player_vec.at(player_idx)->updateVelX(-m_player_vec.at(player_idx)->getFriction(), 3);
            } else {
                m_player_vec.at(player_idx)->updateVelX(-0.1, 2.5);
            }
        }
    }
}
