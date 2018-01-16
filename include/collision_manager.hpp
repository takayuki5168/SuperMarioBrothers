#pragma once

#include <list>
#include "include/abst_character.hpp"
#include "include/abst_player.hpp"
#include "include/abst_enemy.hpp"
#include "include/abst_rect_object.hpp"
#include "include/abst_unique_object.hpp"
#include "include/abst_item.hpp"

class CollisionManager
{
public:
    explicit CollisionManager(
        std::vector<std::shared_ptr<AbstPlayer>> player_vec, std::vector<std::shared_ptr<AbstEnemy>> enemy_vec)
    {
        // TODO 書き方を簡単にする
        m_character_object.resize(1);
        for (auto player : player_vec) {
            m_character_object.at(0).push_back(player);
        }

        m_character_object.resize(2);
        for (auto enemy : enemy_vec) {
            m_character_object.at(1).push_back(enemy);
        }
    }

    void updateCollision(std::vector<std::vector<int>>& fix_object_map,
        std::vector<std::shared_ptr<AbstRectObject>> rect_object_vec, std::vector<std::shared_ptr<AbstUniqueObject>> unique_object_vec,
        std::vector<std::shared_ptr<AbstItem>> item_vec)
    {
        for (auto character_object_vec : m_character_object) {  // AbstPlayer, AbstEnemy
            for (auto character_object : character_object_vec) {
                character_object->setCollisionAll(false);
                for (int j = 0; j < 4; j++) {  // !< 四辺
                    const auto point = character_object->getCollisionPoint(j);

                    /*
                    // TODO uniqueと同じように書き換える
                    for (auto p : point) {// 一辺のうち三点
                        {                 // Collision With FixObject
                            int object_x = (p.m_x - static_cast<int>(p.m_x) % Params::BLOCK_SIZE);
                            int object_y = (p.m_y - static_cast<int>(p.m_y) % Params::BLOCK_SIZE);
                            int x = MathUtil::setInRange(object_x / Params::BLOCK_SIZE, 100);    //35, 0);  // TODO
                            int y = MathUtil::setInRange(object_y / Params::BLOCK_SIZE, 11, 0);  // TODO
                            if (fix_object_map.at(y).at(x) != '0') {                             // TODO
                                character_object->setCollisionTrue(j);
                            }

                            if (not character_object->getCollisionFixObject(j)) {  // 衝突していない
                                character_object->getCollisionFalseFixObjectFunc(j)(AbstObject::Point{object_x, object_y}, AbstObject::Point{}, AbstObject::Point{});
                            } else {  // 衝突している
                                character_object->getCollisionTrueFixObjectFunc(j)(AbstObject::Point{object_x, object_y}, AbstObject::Point{}, AbstObject::Point{});
                            }
                        }
						}*/
                    {                                                   // Collision With UniqueObject
                        for (auto unique_object : unique_object_vec) {  // 各unique_objectにおいて
                            auto pos = unique_object->getPos();
                            auto pos_diff = pos - unique_object->getPrePos();
                            int w = unique_object->getWidth();
                            int h = unique_object->getHeight();
                            bool collision_each_point = false;

                            const auto point = character_object->getCollisionPoint(j);
                            for (auto p : point) {  // 一辺のうち三点
                                if (j == 2) {       // 下辺だったら一フレーム前に衝突していたら位置の差分を引く
                                    if (p.m_x >= pos.m_x - pos_diff.m_x and p.m_x <= pos.m_x - pos_diff.m_x + w
                                        and p.m_y >= pos.m_y - pos_diff.m_y and p.m_y <= pos.m_y - pos_diff.m_y + h) {
                                        character_object->setCollisionTrue(j);
                                        collision_each_point = true;
                                    }
                                } else {  // 下辺以外だったら一フレーム前の位置の差分を引かない
                                    if (p.m_x >= pos.m_x and p.m_x <= pos.m_x + w and p.m_y >= pos.m_y and p.m_y <= pos.m_y + h) {
                                        character_object->setCollisionTrue(j);
                                        collision_each_point = true;
                                    }
                                }
                            }

                            if (collision_each_point) {
                                character_object->getMyFuncCollisionTrue(j)(pos, AbstObject::Point{w, h}, AbstObject::Point{pos_diff.m_x, 0});
                            }
                        }
                    }
                }
            }
        }
    }

private:
    std::vector<std::vector<std::shared_ptr<AbstCharacter>>> m_character_object;
};
