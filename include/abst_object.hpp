#pragma once

#include <vector>

class AbstObject
{
public:
    struct Point {
        Point() = default;
        Point(int x, int y)
            : x(x), y(y) {}
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
        std::vector<Point> collision_point, std::vector<Line> collision_frame)
        : m_rect(std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(w), static_cast<uint16_t>(h)})), m_pos(Point{x, y}),
          m_name(name), m_color(color),
          m_collision_point(std::move(collision_point)), m_collision_frame(std::move(collision_frame)) {}

    void draw(SDL_Surface* m_window)
    {
        m_rect.x = m_pos.x;
        m_rect.y = m_pos.y;
        SDL_FillRect(m_window, &m_rect, m_color);
    }

    virtual void updatePos() = 0;

protected:
    std::vector<Point> m_collision_point;
    std::vector<Line> m_collision_frame;

    Point m_pos;
    Point m_acc;
    Point m_vel;

private:
    SDL_Rect m_rect;
    int m_color;
    std::string m_name;
};
