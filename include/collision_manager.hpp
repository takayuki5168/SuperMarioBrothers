#pragma once

#include <list>
#include "include/params.hpp"
#include "include/abst_character.hpp"
#include "include/abst_player.hpp"
#include "include/abst_enemy.hpp"
#include "include/abst_rect_object.hpp"
#include "include/abst_unique_object.hpp"
#include "include/abst_item.hpp"
#include "include/pipe.hpp"

class CollisionManager
{
public:
    explicit CollisionManager(
        std::vector<std::shared_ptr<AbstPlayer>> player_vec, std::vector<std::shared_ptr<AbstEnemy>> enemy_vec)
    {
        // TODO 書き方を簡単にする
        m_character_vec.resize(player_vec.size() + enemy_vec.size());
        for (int i = 0; i < player_vec.size(); i++) {
            m_character_vec.at(i) = player_vec.at(i);
        }
        for (int i = 0; i < enemy_vec.size(); i++) {
            m_character_vec.at(player_vec.size() + i) = enemy_vec.at(i);
        }
    }

    void updateCollision(std::vector<std::vector<int>>& fix_object_map,
        std::vector<std::shared_ptr<AbstRectObject>> rect_object_vec, std::vector<std::shared_ptr<AbstUniqueObject>> unique_object_vec,
        std::vector<std::shared_ptr<AbstItem>> item_vec)
    {
        updateCollisionWithObject(fix_object_map, rect_object_vec, unique_object_vec, item_vec);
        updateCollisionWithCharacter();


        for (int i = 0; i < m_character_vec.size(); i++) {
            if (not m_character_vec.at(i)->isAlive()) {
                m_character_vec.erase(m_character_vec.begin() + i);
            }
        }
    }

    void updateCollisionWithObject(std::vector<std::vector<int>>& fix_object_map,
        std::vector<std::shared_ptr<AbstRectObject>> rect_object_vec, std::vector<std::shared_ptr<AbstUniqueObject>> unique_object_vec,
        std::vector<std::shared_ptr<AbstItem>> item_vec)
    {
        for (auto character : m_character_vec) {  // AbstPlayer, AbstEnemy
            character->setCollisionAll(false);
            for (int j = 0; j < 4; j++) {  // !< 四辺
                const auto point = character->getCollisionPoint(j);

                bool collision_flag = false;
                std::shared_ptr<Abstraction> dummy_abst_object = nullptr;

                // Collision With FixMap
                for (auto p : point) {  // 一辺のうち三点
                    int object_x = (p.m_x - static_cast<int>(p.m_x) % Params::BLOCK_SIZE);
                    int object_y = (p.m_y - static_cast<int>(p.m_y) % Params::BLOCK_SIZE);
                    int x = MathUtil::setInRange(object_x / Params::BLOCK_SIZE, 100);    //35, 0);  // TODO
                    int y = MathUtil::setInRange(object_y / Params::BLOCK_SIZE, 11, 0);  // TODO

                    if (fix_object_map.at(y).at(x) != 0) {  // TODO
                        collision_flag = true;
                        character->setCollisionTrue(j);
                    }
                    dummy_abst_object = std::make_shared<Abstraction>(
                        Params::BLOCK_SIZE * x, Params::BLOCK_SIZE * y, Params::BLOCK_SIZE, Params::BLOCK_SIZE, 0, "Dummy");
                    dummy_abst_object->setIdx(fix_object_map.at(y).at(x));
                }
                if (not collision_flag) {
                    character->callMyFuncCollisionFalseWithObject(j)(dummy_abst_object);
                } else {  // 衝突している
                    character->callMyFuncCollisionTrueWithObject(j)(dummy_abst_object);
                }

                // Collision With RectObject
                for (auto abst_object : rect_object_vec) {
                    auto pos = abst_object->getPos();
                    auto pos_diff = pos - abst_object->getPrePos();
                    int w = abst_object->getWidth();
                    int h = abst_object->getHeight();
                    bool collision_each_flag = false;

                    const auto point = character->getCollisionPoint(j);
                    for (auto p : point) {  // 一辺のうち三点
                        if (j == 2) {       // 下辺だったら一フレーム前に衝突していたら位置の差分を引く
                            if (p.m_x >= pos.m_x - pos_diff.m_x and p.m_x <= pos.m_x - pos_diff.m_x + w
                                and p.m_y >= pos.m_y - pos_diff.m_y and p.m_y <= pos.m_y - pos_diff.m_y + h) {
                                character->setCollisionTrue(j);
                                collision_each_flag = true;
                            }
                        } else {  // 下辺以外だったら一フレーム前の位置の差分を引かない
                            if (p.m_x >= pos.m_x and p.m_x <= pos.m_x + w and p.m_y >= pos.m_y and p.m_y <= pos.m_y + h) {
                                character->setCollisionTrue(j);
                                collision_each_flag = true;
                            }
                        }

                        // 土管用に別で当たり判定

                        if (p.m_x >= pos.m_x and p.m_x <= pos.m_x + w and p.m_y >= pos.m_y and p.m_y <= pos.m_y + h) {
                            if (abst_object->getIdx() == 'z' and j == 2) {
                                character->contactPipe(abst_object);
                            } else {
                                character->contactPipeNone();
                            }
                        }
                    }


                    if (collision_each_flag) {
                        abst_object->callOtherFuncCollisionTrueWithObject(j)(character);
                        character->callMyFuncCollisionTrueWithObject(j)(abst_object);
                    }
                }

                // Collision With UniqueObject
                for (auto abst_object : unique_object_vec) {
                    auto pos = abst_object->getPos();
                    auto pos_diff = pos - abst_object->getPrePos();
                    int w = abst_object->getWidth();
                    int h = abst_object->getHeight();
                    bool collision_each_flag = false;

                    const auto point = character->getCollisionPoint(j);
                    // TODO unique仕様に変える
                    for (auto p : point) {  // 一辺のうち三点
                        std::vector<Abstraction::Point> frame_points = abst_object->getFramePoints();
                        int cnt = 0;
                        for (int i = 0; i < frame_points.size(); i++) {
                            Abstraction::Point point1 = frame_points.at(i), point2;
                            if (i == abst_object->getFramePoints().size() - 1) {
                                point2 = frame_points.at(0);
                            } else {
                                point2 = frame_points.at(i + 1);
                            }

                            Abstraction::Point center = abst_object->getCenter();
                            if (point1.m_x == point2.m_x) {
                                if ((point1.m_x - p.m_x) * (point1.m_x - center.m_x) > 0) {
                                    cnt++;
                                }
                            } else if (point1.m_y == point2.m_y) {
                                if ((point1.m_y - p.m_y) * (point1.m_y - center.m_y) > 0) {
                                    cnt++;
                                }
                            } else {
                                if (((point1.m_y - point2.m_y) / (point1.m_x - point2.m_x) * (p.m_x - point1.m_x) + point2.m_y - p.m_y)
                                        * ((point1.m_y - point2.m_y) / (point1.m_x - point2.m_x) * (center.m_x - point1.m_x) + point2.m_y - center.m_y)
                                    > 0) {
                                    cnt++;
                                }
                            }
                        }
                        if (cnt == frame_points.size()) {
                            character->setCollisionTrue(j);
                            collision_each_flag = true;
                        }
                    }

                    if (collision_each_flag) {
                        abst_object->callOtherFuncCollisionTrueWithObject(j)(character);
                        character->callMyFuncCollisionTrueWithObject(j)(abst_object);
                    }
                }
            }
        }
    }

    void updateCollisionWithCharacter()
    {
        for (int i = 0; i < m_character_vec.size(); i++) {
            for (int j = 0; j < m_character_vec.size(); j++) {
                if (i > j) {
                    continue;
                }

                Abstraction::Point pos = m_character_vec.at(j)->getPos();
                double width = m_character_vec.at(j)->getWidth();
                double height = m_character_vec.at(j)->getHeight();
                // TODO とりあえず矩形で当たり判定
                for (auto points : m_character_vec.at(i)->getCollisionPoint()) {  // 四辺のうち一辺
                    for (auto point : points) {                                   // 三点のうち一点
                        if (point.m_x >= pos.m_x and point.m_x <= pos.m_x + width
                            and point.m_y >= pos.m_y and point.m_y <= pos.m_y + height) {
                            m_character_vec.at(i)->callOtherFuncCollisionTrueWithCharacter()(m_character_vec.at(j));
                            m_character_vec.at(j)->callOtherFuncCollisionTrueWithCharacter()(m_character_vec.at(i));
                            break;
                        }
                    }
                }
            }
        }
    }


private:
    std::vector<std::shared_ptr<AbstCharacter>> m_character_vec;
};
