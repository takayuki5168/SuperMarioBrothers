#pragma once

#include <list>
#include "include/abst_dynamic_object.hpp"
#include "include/abst_player.hpp"
#include "include/abst_enemy.hpp"
#include "include/abst_static_object.hpp"
#include "include/abst_fix_object.hpp"
#include "include/abst_unique_object.hpp"

class CollisionManager
{
public:
    explicit CollisionManager(
        std::vector<std::shared_ptr<AbstPlayer>> player_vec, std::vector<std::shared_ptr<AbstEnemy>> enemy_vec,
        std::vector<std::shared_ptr<AbstFixObject>> /* TODO fix_object_vec */)
    {
        // TODO 書き方を簡単にする
        m_dynamic_object.resize(1);
        for (auto player : player_vec) {
            m_dynamic_object.at(0).push_back(player);
        }
        //m_dynamic_object.push_back(player_vec);

        m_dynamic_object.resize(2);
        for (auto enemy : enemy_vec) {
            m_dynamic_object.at(1).push_back(enemy);
        }

        /*
        m_static_object.resize(1);
        for (auto fix_object : fix_object_vec) {
            m_static_object.at(0).push_back(fix_object);
        }
		*/
    }

    void updateCollision(std::vector<std::vector<int>>& fix_object_map, std::vector<std::shared_ptr<AbstUniqueObject>> unique_object_vec)
    {
        for (auto dynamic_object_vec : m_dynamic_object) {
            for (auto dynamic_object : dynamic_object_vec) {
                dynamic_object->setCollisionFixObjectFalseAll();
                dynamic_object->setCollisionUniqueObjectFalseAll();
                for (int j = 0; j < 4; j++) {  // !< 四辺
                    const auto point = dynamic_object->getCollisionPoint(j);

                    // TODO uniqueと同じように書き換える
                    for (auto p : point) {// 一辺のうち三点
                        {                 // Collision With FixObject
                            int object_x = (p.x - static_cast<int>(p.x) % AbstFixObject::getObjectSize());
                            int object_y = (p.y - static_cast<int>(p.y) % AbstFixObject::getObjectSize());
                            int x = MathUtil::setInRange(object_x / AbstFixObject::getObjectSize(), 100);    //35, 0);  // TODO
                            int y = MathUtil::setInRange(object_y / AbstFixObject::getObjectSize(), 11, 0);  // TODO
                            if (fix_object_map.at(y).at(x) != '0') {                                         // TODO
                                dynamic_object->setCollisionFixObjectTrue(j);
                            }

                            if (not dynamic_object->getCollisionFixObject(j)) {  // 衝突していない
                                dynamic_object->getCollisionFalseFixObjectFunc(j)(AbstObject::Point{object_x, object_y}, AbstObject::Point{}, AbstObject::Point{});
                            } else {  // 衝突している
                                dynamic_object->getCollisionTrueFixObjectFunc(j)(AbstObject::Point{object_x, object_y}, AbstObject::Point{}, AbstObject::Point{});
                            }
                        }
                    }
                    {                                                   // Collision With UniqueObject
                        for (auto unique_object : unique_object_vec) {  // 各unique_objectにおいて
                            auto pos = unique_object->getPos();
                            auto pos_diff = pos - unique_object->getPrePos();
                            int w = unique_object->getWidth();
                            int h = unique_object->getHeight();
                            bool collision_each_point = false;

                            const auto point = dynamic_object->getCollisionPoint(j);
                            for (auto p : point) {  // 一辺のうち三点
                                if (j == 2) {       // 下辺だったら一フレーム前に衝突していたら位置の差分を引く
                                    if (p.x >= pos.x - pos_diff.x and p.x <= pos.x - pos_diff.x + w
                                        and p.y >= pos.y - pos_diff.y and p.y <= pos.y - pos_diff.y + h) {
                                        dynamic_object->setCollisionUniqueObjectTrue(j);
                                        collision_each_point = true;
                                    }
                                } else {  // 下辺以外だったら一フレーム前の位置の差分を引かない
                                    if (p.x >= pos.x and p.x <= pos.x + w and p.y >= pos.y and p.y <= pos.y + h) {
                                        dynamic_object->setCollisionUniqueObjectTrue(j);
                                        collision_each_point = true;
                                    }
                                }
                            }

                            if (collision_each_point) {
                                dynamic_object->getCollisionTrueUniqueObjectFunc(j)(pos, AbstObject::Point{w, h}, AbstObject::Point{pos_diff.x, 0});
                            }
                        }
                    }
                }
            }
        }
    }

private:
    std::vector<std::vector<std::shared_ptr<AbstDynamicObject>>> m_dynamic_object;
};
