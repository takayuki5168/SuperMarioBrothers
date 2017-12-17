#pragma once

#include <array>
#include "include/math_util.hpp"

class AbstObject
{
public:
    struct Point {
        Point() = default;
        Point(int x, int y)
            : x(x), y(y) {}
        Point(double x, double y)
            : x(x), y(y) {}
        Point(int x, double y)
            : x(x), y(y) {}
        Point(double x, int y)
            : x(x), y(y) {}
        Point operator+(Point other) { return Point{x + other.x, y + other.y}; }
        void setInRange(double max)
        {
            x = MathUtil::setInRange(x, max);
            y = MathUtil::setInRange(y, max);
        }

        double x = 0;
        double y = 0;
    };
    /*
    struct Line {
        Line() = default;
        Line(double x1, double y1, double x2, double y2)
            : start_point(Point{x1, y1}), end_point(Point{x2, y2}) {}
        Point start_point = Point{0, 0};
        Point end_point = Point{0, 0};
    };
  */

    explicit AbstObject(int x, int y, int w, int h, int color, std::string name)
        : m_rect(std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(w), static_cast<uint16_t>(h)})), m_pos(Point{x, y}),
          m_name(name), m_color(color), m_w(w), m_h(h)
    {
        std::array<Point, 3> top_point = std::array<Point, 3>{
            Point{w / 6.0, 0},
            Point{w / 2.0, 0},
            Point{w * 5.0 / 6, 0}};
        std::array<Point, 3> right_point = std::array<Point, 3>{
            Point{w, h / 6.0},
            Point{w, h / 2.0},
            Point{w, h * 5.0 / 6}};
        std::array<Point, 3> bottom_point = std::array<Point, 3>{
            Point{w / 6.0, h},
            Point{w / 2.0, h},
            Point{w * 5.0 / 6, h}};
        std::array<Point, 3> left_point = std::array<Point, 3>{
            Point{0, h / 6.0},
            Point{0, h / 2.0},
            Point{0, h * 5.0 / 6}};

        m_collision_point = std::move(std::array<std::array<Point, 3>, 4>{
            std::move(top_point),
            std::move(right_point),
            std::move(bottom_point),
            std::move(left_point)});
    }

    virtual void updatePosDecorator(double time) {}
    virtual void updatePos(double time)
    {
        updatePosDecorator(time);
        m_vel.y += m_gravity;
        m_vel.setInRange(m_max_vel);
        m_pos = m_pos + m_vel;
    }

    Point getPos() { return m_pos; }
    SDL_Rect getRect() { return m_rect; }

    void setPos(Point pos) { m_pos = pos; }
    void setPosX(double x) { m_pos.x = x; }
    void setPosY(double y) { m_pos.y = y; }

    Point getVel() { return m_vel; }

    void setVel(double vel_x, double vel_y) { m_vel = Point{vel_x, vel_y}; }
    void setVelX(double vel_x) { m_vel.x = vel_x; }
    void setVelXPlus() { m_vel.x = MathUtil::setPlus(m_vel.x); }
    void setVelXMinus() { m_vel.x = MathUtil::setMinus(m_vel.x); }
    void setVelY(double vel_y) { m_vel.y = vel_y; }
    void setVelYPlus() { m_vel.y = MathUtil::setPlus(m_vel.y); }
    void setVelYMinus() { m_vel.y = MathUtil::setMinus(m_vel.y); }

    void updateVel(double vel_x, double vel_y, double max_vel = m_max_vel)
    {
        m_vel = m_vel + Point{vel_x, vel_y};
        m_vel.setInRange(max_vel);
    }
    void updateVelX(double vel_x, double max_vel = m_max_vel) { m_vel.x = MathUtil::setInRange(m_vel.x + vel_x, max_vel); }
    void updateVelY(double vel_y, double max_vel = m_max_vel) { m_vel.y = MathUtil::setInRange(m_vel.y + vel_y, max_vel); }


    virtual void draw(SDL_Surface* m_window, double m_window_x)
    {
        m_rect.x = static_cast<int>(m_pos.x + m_window_x);
        m_rect.y = static_cast<int>(m_pos.y);
        m_rect.w = m_w;  // TODO バグ
        m_rect.h = m_h;  // TODO バグ
        SDL_FillRect(m_window, &m_rect, m_color);
    }

    std::array<Point, 3> getCollisionPoint(int i)
    {
        return std::array<Point, 3>{
            m_collision_point.at(i).at(0) + Point{m_pos.x, m_pos.y},
            m_collision_point.at(i).at(1) + Point{m_pos.x, m_pos.y},
            m_collision_point.at(i).at(2) + Point{m_pos.x, m_pos.y}};
    }

    double getWidth() { return m_rect.w; }
    double getHeight() { return m_rect.h; }

    void setGravity(double g) { m_gravity = g; }
    double getGravity() { return m_gravity; }

    // !< 4辺が衝突しているかどうか
    void setCollisionFixObjectTrue(int i) { m_collision_fix_object_flag.at(i) = true; }
    void setCollisionFixObjectFalseAll()
    {
        for (int i = 0; i < 4; i++) {
            m_collision_fix_object_flag.at(i) = false;
        }
    }
    bool getCollisionFixObject(int i) { return m_collision_fix_object_flag.at(i); }

    void setCollisionUniqueObjectTrue(int i) { m_collision_unique_object_flag.at(i) = true; }
    void setCollisionUniqueObjectFalseAll()
    {
        for (int i = 0; i < 4; i++) {
            m_collision_unique_object_flag.at(i) = false;
        }
    }
    bool getCollisionUniqueObject(int i) { return m_collision_unique_object_flag.at(i); }

    bool getCollision(int i) { return m_collision_fix_object_flag.at(i) or m_collision_unique_object_flag.at(i); }


    std::string getName() { return m_name; }

    std::function<void(int, int)> getCollisionTrueFixObjectFunc(int i) { return m_collision_true_fix_object_func.at(i); }
    std::function<void(int, int)> getCollisionFalseFixObjectFunc(int i) { return m_collision_false_fix_object_func.at(i); }
    std::function<void(int, int, int, int)> getCollisionTrueUniqueObjectFunc(int i) { return m_collision_true_unique_object_func.at(i); }
    std::function<void(int, int, int, int)> getCollisionFalseUniqueObjectFunc(int i) { return m_collision_false_unique_object_func.at(i); }

protected:
    std::array<std::array<Point, 3>, 4> m_collision_point;

    Point m_pos;
    Point m_vel;
    constexpr static double m_max_vel = 5;

    double m_gravity = 0;

    // !< 左辺・右辺が衝突しているかどうか
    //bool m_left_collision_flag = false;
    //bool m_right_collision_flag = false;
    // !< 4辺が衝突しているかどうか
    std::array<bool, 4> m_collision_fix_object_flag;
    std::array<bool, 4> m_collision_unique_object_flag;

    double m_hit_point;

    std::array<std::function<void(int object_x, int object_y)>, 4> m_collision_true_fix_object_func
        = std::array<std::function<void(int, int)>, 4>{[](int, int) {}, [](int, int) {}, [](int, int) {}, [](int, int) {}};  // !< 衝突した時の処理関数
    std::array<std::function<void(int object_x, int object_y)>, 4> m_collision_false_fix_object_func
        = std::array<std::function<void(int, int)>, 4>{[](int, int) {}, [](int, int) {}, [](int, int) {}, [](int, int) {}};  // !< 衝突していない時の処理関数
    std::array<std::function<void(int object_x, int object_y, int, int)>, 4> m_collision_true_unique_object_func
        = std::array<std::function<void(int, int, int, int)>, 4>{[](int, int, int, int) {}, [](int, int, int, int) {}, [](int, int, int, int) {}, [](int, int, int, int) {}};  // !< 衝突した時の処理関数
    std::array<std::function<void(int object_x, int object_y, int, int)>, 4> m_collision_false_unique_object_func
        = std::array<std::function<void(int, int, int, int)>, 4>{[](int, int, int, int) {}, [](int, int, int, int) {}, [](int, int, int, int) {}, [](int, int, int, int) {}};  // !< 衝突していない時の処理関数

    //private:
    SDL_Rect m_rect;
    int m_color;
    std::string m_name;

    double m_w;
    double m_h;
};
