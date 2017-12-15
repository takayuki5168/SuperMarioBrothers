#pragma once

#include <array>

class AbstObject
{
public:
    struct Point {
        Point() = default;
        Point(int x, int y)
            : x(x), y(y) {}
        Point(double x, double y)
            : x(static_cast<int>(x)), y(static_cast<int>(y)) {}
        Point(int x, double y)
            : x(x), y(static_cast<int>(y)) {}
        Point(double x, int y)
            : x(static_cast<int>(x)), y(y) {}

        int x = 0;
        int y = 0;
    };
    struct Line {
        Line() = default;
        Line(int x1, int y1, int x2, int y2)
            : start_point(Point{x1, y1}), end_point(Point{x2, y2}) {}
        Point start_point = Point{0, 0};
        Point end_point = Point{0, 0};
    };

    AbstObject(int x, int y, int w, int h, int color, std::string name,
        std::array<std::array<Point, 3>, 4> collision_point)
        : m_rect(std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(w), static_cast<uint16_t>(h)})), m_pos(Point{x, y}),
          m_name(name), m_color(color),
          m_collision_point(std::move(collision_point)) {}

    AbstObject(int x, int y, int w, int h, int color, std::string name)
        : m_rect(std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(w), static_cast<uint16_t>(h)})), m_pos(Point{x, y}),
          m_name(name), m_color(color)
    {
        std::array<Point, 3> top_point = std::array<Point, 3>{
            Point{x + w / 6.0, y},
            Point{x + w / 2.0, y},
            Point{x + w * 5.0 / 6, y}};
        std::array<Point, 3> right_point = std::array<Point, 3>{
            Point{x + w, y + h / 6.0},
            Point{x + w, y + h / 2.0},
            Point{x + w, y + h * 5.0 / 6}};
        std::array<Point, 3> bottom_point = std::array<Point, 3>{
            Point{x + w / 6.0, y + h},
            Point{x + w / 2.0, y + h},
            Point{x + w * 5.0 / 6, y + h}};
        std::array<Point, 3> left_point = std::array<Point, 3>{
            Point{x, y + h / 6.0},
            Point{x, y + h / 2.0},
            Point{x, y + h * 5.0 / 6}};

        m_collision_point = std::move(std::array<std::array<Point, 3>, 4>{
            std::move(top_point),
            std::move(right_point),
            std::move(bottom_point),
            std::move(left_point)});
    }

    void draw(SDL_Surface* m_window)
    {
        m_rect.x = m_pos.x;
        m_rect.y = m_pos.y;
        SDL_FillRect(m_window, &m_rect, m_color);
    }

    virtual void updatePos() = 0;

protected:
    std::array<std::array<Point, 3>, 4> m_collision_point;

    Point m_pos;
    Point m_acc;
    Point m_vel;

private:
    SDL_Rect m_rect;
    int m_color;
    std::string m_name;
};
