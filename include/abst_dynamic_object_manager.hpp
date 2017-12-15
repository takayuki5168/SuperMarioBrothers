#pragma once

#include "include/abst_manager.hpp"
//#include "include/abst_fix_object_manager.hpp"
#include "include/fix_object_manager.hpp"

class AbstDynamicObjectManager : public AbstManager
{
public:
    explicit AbstDynamicObjectManager()
        : AbstManager()
    {
        m_collision_true_fix_object_func = std::array<std::function<void(int, int, int)>, 4>{
            [this](int i, int object_x, int object_y) {  // 天井
                m_data.at(i)->setVelYPlus();
                m_data.at(i)->setPosY(object_y + AbstFixObject::getObjectSize());
            },
            [this](int i, int object_x, int object_y) {  // 右壁
                m_data.at(i)->setVelXMinus();
                m_data.at(i)->setPosX(object_x - m_data.at(i)->getWidth());
            },
            [this](int i, int object_x, int object_y) {  // 地面
                m_data.at(i)->setGravity(0);
                m_data.at(i)->setVelYMinus();
                m_data.at(i)->setPosY(object_y - m_data.at(i)->getHeight());

                {
                    auto vel_x = m_data.at(i)->getVel().x;
                    if (vel_x != 0) {
                        auto tmp = vel_x;
                        vel_x = vel_x - 0.13 * vel_x / std::abs(vel_x);
                        if (tmp * vel_x < 0) {
                            vel_x = 0;
                        }
                        m_data.at(i)->setVelX(vel_x);
                    }
                }
            },
            [this](int i, int object_x, int object_y) {  // 左壁
                m_data.at(i)->setVelXPlus();
                m_data.at(i)->setPosX(object_x + AbstFixObject::getObjectSize());
            }};

        m_collision_false_fix_object_func = std::array<std::function<void(int)>, 4>{
            [this](int i) {},
            [this](int i) {},
            [this](int i) { m_data.at(i)->setGravity(0.15); },
            [this](int i) {}};
    }

    void updateCollisionWithFixObject(std::unique_ptr<FixObjectManager>& fix_object_manager)
    {
        for (int i = 0; i < m_data.size(); i++) {
            for (int j = 0; j < 4; j++) {
                const auto point = m_data.at(i)->getCollisionPoint(j);
                m_collision_fix_object_flag.at(j) = false;
                int object_x, object_y;
                for (auto p : point) {
                    object_x = (p.x - static_cast<int>(p.x) % AbstFixObject::getObjectSize());
                    object_y = (p.y - static_cast<int>(p.y) % AbstFixObject::getObjectSize());
                    int x = MathUtil::setInRange(object_x / AbstFixObject::getObjectSize(), 16, 0);
                    int y = MathUtil::setInRange(object_y / AbstFixObject::getObjectSize(), 12, 0);

                    if (fix_object_manager->getObjectMap().at(y).at(x) != '0') {
                        m_collision_fix_object_flag.at(j) = true;
                    }
                }

                if (not m_collision_fix_object_flag.at(j)) {
                    m_collision_false_fix_object_func.at(j)(i);
                } else {  // 衝突している
                    m_collision_true_fix_object_func.at(j)(i, object_x, object_y);
                }
            }
        }
    }

    std::array<bool, 4> getCollisionFixObjectFlag() { return m_collision_fix_object_flag; }

protected:
    std::array<bool, 4> m_collision_fix_object_flag = std::array<bool, 4>{false, false, false, false};  // !< 衝突しているかどうかの判定フラグ
    std::array<std::function<void(int, int, int)>, 4> m_collision_true_fix_object_func;                 // !< 衝突した時の処理関数
    std::array<std::function<void(int)>, 4> m_collision_false_fix_object_func;                          // !< 衝突していない時の処理関数
};
