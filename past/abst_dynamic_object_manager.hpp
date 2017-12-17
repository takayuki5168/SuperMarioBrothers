#pragma once

#include "include/abst_manager.hpp"
//#include "include/abst_fix_object_manager.hpp"
#include "include/fix_object_manager.hpp"

class AbstDynamicObjectManager : public AbstManager
{
public:
    explicit AbstDynamicObjectManager() : AbstManager() {}

    virtual void addDecorator()
    {
        // 衝突している時、していない時の処理関数の登録
        m_collision_true_fix_object_func.push_back(std::move(m_data.back()->getCollisionTrueFixObjectFunc()));
        m_collision_false_fix_object_func.push_back(std::move(m_data.back()->getCollisionFalseFixObjectFunc()));
    }

    /*!
     * @brief   FixObjectと衝突している時、していない時の処理をする
     */
    void updateCollisionWithFixObject(std::unique_ptr<FixObjectManager>& fix_object_manager)
    {
        for (int i = 0; i < m_data.size(); i++) {  // キャラクターごと
            m_data.at(i)->setLeftCollision(false);
            m_data.at(i)->setRightCollision(false);
            for (int j = 0; j < 4; j++) {  // どの辺か
                const auto point = m_data.at(i)->getCollisionPoint(j);
                m_collision_fix_object_flag.at(j) = false;
                int object_x, object_y;
                for (auto p : point) {  // 辺のうちのどの点か
                    object_x = (p.x - static_cast<int>(p.x) % AbstFixObject::getObjectSize());
                    object_y = (p.y - static_cast<int>(p.y) % AbstFixObject::getObjectSize());
                    int x = MathUtil::setInRange(object_x / AbstFixObject::getObjectSize(), 35, 0);  // TODO
                    int y = MathUtil::setInRange(object_y / AbstFixObject::getObjectSize(), 11, 0);  // TODO

                    if (fix_object_manager->getObjectMap().at(y).at(x) != '0') {
                        m_collision_fix_object_flag.at(j) = true;
                        if (j == 1) {
                            m_data.at(i)->setRightCollision(true);
                        } else if (j == 3) {
                            m_data.at(i)->setLeftCollision(true);
                        }
                    }
                }

                if (not m_collision_fix_object_flag.at(j)) {  // 衝突していない
                    m_collision_false_fix_object_func.at(i).at(j)(object_x, object_y);
                } else {  // 衝突している
                    m_collision_true_fix_object_func.at(i).at(j)(object_x, object_y);
                }
            }
        }
    }

    void updateCollisionWithDynamicObject(std::unique_ptr<AbstDynamicObjectManager>& dynamic_object_manager) {}

protected:
    std::array<bool, 4> m_collision_fix_object_flag = std::array<bool, 4>{false, false, false, false};  // !< 衝突しているかどうかの判定フラグ
    std::vector<std::array<std::function<void(int, int)>, 4>> m_collision_true_fix_object_func;         // !< 衝突した時の処理関数
    std::vector<std::array<std::function<void(int, int)>, 4>> m_collision_false_fix_object_func;        // !< 衝突していない時の処理関数
};
