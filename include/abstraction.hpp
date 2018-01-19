#pragma once

#include <array>
#include "include/math_util.hpp"
#include "include/params.hpp"

class Abstraction
{
public:
    struct Point {
        Point() = default;
        Point(int x, int y)
            : m_x(x), m_y(y) {}
        Point(double x, double y)
            : m_x(x), m_y(y) {}
        Point(int x, double y)
            : m_x(x), m_y(y) {}
        Point(double x, int y)
            : m_x(x), m_y(y) {}
        Point operator+(Point other) { return Point{m_x + other.m_x, m_y + other.m_y}; }
        Point operator-(Point other) { return Point{m_x - other.m_x, m_y - other.m_y}; }

        void setInRange(double max)
        {
            m_x = MathUtil::setInRange(m_x, max);
            m_y = MathUtil::setInRange(m_y, max);
        }

        double m_x = 0;
        double m_y = 0;
    };

    enum State {
        Nothing = 0,
        Running = 1,
        Jumping = 2,
    };

    explicit Abstraction(int x, int y, int color, std::string name,
        std::vector<Point> frame_points)
        : m_pos(Point{x, y}), m_name(name), m_color(color), m_frame_points(frame_points)
    {
        m_collision_flag.resize(frame_points.size());

        // frame_pointsで枠を与えられた場合には矩形の最大値を求める
        int max_w = 0, max_h = 0, min_w = Params::WINDOW_WIDTH, min_h = Params::WINDOW_HEIGHT;
        for (int i = 0; i < frame_points.size(); i++) {
            if (max_w < frame_points.at(i).m_x) {
                max_w = frame_points.at(i).m_x;
            } else if (min_w > frame_points.at(i).m_x) {
                min_w = frame_points.at(i).m_x;
            }
            if (max_h < frame_points.at(i).m_y) {
                max_h = frame_points.at(i).m_y;
            } else if (min_h > frame_points.at(i).m_y) {
                min_h = frame_points.at(i).m_y;
            }
        }
        m_width = max_w - min_w;
        m_height = max_h - min_h;
        std::cout << m_width << " " << m_height << std::endl;
        m_rect = std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(m_width), static_cast<uint16_t>(m_height)});

        // collision_pointを求める
        for (int i = 0; i < frame_points.size(); i++) {
            if (i == frame_points.size() - 1) {
                Point p1 = frame_points.at(i);
                Point p2 = frame_points.at(0);
                std::array<Point, 3> tmp_points = std::array<Point, 3>{
                    // TODO Pointにmoveをつけるか
                    Point{p1.m_x * 1.0 / 4.0 + p2.m_x * 3.0 / 4.0, p1.m_y * 1.0 / 4.0 + p2.m_y * 3.0 / 4.0},
                    Point{p1.m_x / 2.0 + p2.m_x / 2.0, p1.m_y / 2.0 + p2.m_y / 2.0},
                    Point{p1.m_x * 3.0 / 4.0 + p2.m_x * 1.0 / 4.0, p1.m_y * 3.0 / 4.0 + p2.m_y * 1.0 / 4.0}};
                m_collision_points.push_back(std::move(tmp_points));

            } else {
                Point p1 = frame_points.at(i);
                Point p2 = frame_points.at(i + 1);
                std::array<Point, 3> tmp_points = std::array<Point, 3>{
                    Point{p1.m_x * 1.0 / 4.0 + p2.m_x * 3.0 / 4.0, p1.m_y * 1.0 / 4.0 + p2.m_y * 3.0 / 4.0},
                    Point{p1.m_x / 2.0 + p2.m_x / 2.0, p1.m_y / 2.0 + p2.m_y / 2.0},
                    Point{p1.m_x * 3.0 / 4.0 + p2.m_x * 1.0 / 4.0, p1.m_y * 3.0 / 4.0 + p2.m_y * 1.0 / 4.0}};
                m_collision_points.push_back(std::move(tmp_points));
            }
        }
    }

    explicit Abstraction(int x, int y, int w, int h, int color, std::string name)
        : m_rect(std::move(SDL_Rect{static_cast<int16_t>(x), static_cast<int16_t>(y), static_cast<uint16_t>(w), static_cast<uint16_t>(h)})), m_pos(Point{x, y}),
          m_name(name), m_color(color), m_width(w), m_height(h)
    {
        m_frame_points = {Point{0, 0}, Point{w, 0}, Point{w, h}, Point{0, h}};
        /*
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
	  */
        m_collision_flag.resize(4);
        std::array<Point, 3> top_point = std::array<Point, 3>{
            Point{w * 1.0 / 4.0, 0 - 1},
            Point{w / 2.0, 0 - 1},
            Point{w * 3.0 / 4.0, 0 - 1}};
        std::array<Point, 3> right_point = std::array<Point, 3>{
            Point{w + 1, h * 3.0 / 4.0},
            Point{w + 1, h / 2.0},
            Point{w + 1, h / 4.0}};
        std::array<Point, 3> bottom_point = std::array<Point, 3>{
            Point{w * 3.0 / 4.0, h + 1},
            Point{w / 2.0, h + 1},
            Point{w / 4.0, h + 1}};
        std::array<Point, 3> left_point = std::array<Point, 3>{
            Point{0 - 1, h * 3.0 / 4.0},
            Point{0 - 1, h / 2.0},
            Point{0 - 1, h / 4.0}};

        m_collision_points = std::move(std::vector<std::array<Point, 3>>{
            std::move(top_point),
            std::move(right_point),
            std::move(bottom_point),
            std::move(left_point)});
    }

    std::string getName() { return m_name; }
    double getWidth() { return m_width; }
    double getHeight() { return m_height; }
    Point getCenter() { return m_pos + Point{m_width / 2.0, m_height / 2.0}; }

    /*!
     * @brief   updatePos(位置の更新関数)内で呼ぶ装飾関数
     */
    virtual void updatePosDecorator(double time) {}

    /*!
     * @brief   位置の更新関数
     */
    virtual void updatePos(double time)
    {
        m_pre_pos = m_pos;
        updatePosDecorator(time);  //!< 主に敵の自由な動作に使う
        m_vel.m_y += m_gravity;
        m_vel.setInRange(m_max_vel);
        m_pos = m_pos + m_vel;
    }
    virtual void updatePos(Point pos) { m_pos = m_pos + pos; }
    Point getPos() { return m_pos; }
    Point getPrePos() { return m_pre_pos; }
    void setPos(Point pos) { m_pos = pos; }
    void setPosX(double x) { m_pos.m_x = x; }
    void setPosY(double y) { m_pos.m_y = y; }

    void updateVel(double vel_x, double vel_y, double max_vel = m_max_vel)
    {
        m_vel = m_vel + Point{vel_x, vel_y};
        m_vel.setInRange(max_vel);
    }
    void updateVelX(double vel_x, double max_vel = m_max_vel) { m_vel.m_x = MathUtil::setInRange(m_vel.m_x + vel_x, max_vel); }
    void updateVelY(double vel_y, double max_vel = m_max_vel) { m_vel.m_y = MathUtil::setInRange(m_vel.m_y + vel_y, max_vel); }
    Point getVel() { return m_vel; }
    void setVel(double vel_x, double vel_y) { m_vel = Point{vel_x, vel_y}; }
    void setVelX(double vel_x) { m_vel.m_x = vel_x; }
    void setVelXPlus() { m_vel.m_x = MathUtil::setPlus(m_vel.m_x); }
    void setVelXMinus() { m_vel.m_x = MathUtil::setMinus(m_vel.m_x); }
    void setVelY(double vel_y) { m_vel.m_y = vel_y; }
    void setVelYPlus() { m_vel.m_y = MathUtil::setPlus(m_vel.m_y); }
    void setVelYMinus() { m_vel.m_y = MathUtil::setMinus(m_vel.m_y); }

    std::array<Point, 3> getCollisionPoint(int i)
    {
        return std::array<Point, 3>{
            m_collision_points.at(i).at(0) + m_pos,
            m_collision_points.at(i).at(1) + m_pos,
            m_collision_points.at(i).at(2) + m_pos};
    }
    std::vector<std::array<Point, 3>> getCollisionPoint()
    {
        std::vector<std::array<Point, 3>> tmp_collision_point = m_collision_points;

        for (int i = 0; i < tmp_collision_point.size(); i++) {
            for (int j = 0; j < tmp_collision_point.at(i).size(); j++) {
                tmp_collision_point.at(i).at(j) = tmp_collision_point.at(i).at(j) + m_pos;
            }
        }
        return tmp_collision_point;
    }

    std::vector<Point> getFramePoints() const
    {
        std::vector<Point> tmp_frame_points = m_frame_points;

        for (int i = 0; i < tmp_frame_points.size(); i++) {
            tmp_frame_points.at(i) = tmp_frame_points.at(i) + m_pos;
        }
        return tmp_frame_points;
    }


    virtual void draw(SDL_Surface* m_window, double m_window_x)
    {
        m_rect.x = static_cast<int>(m_pos.m_x + m_window_x);
        m_rect.y = static_cast<int>(m_pos.m_y);
        m_rect.w = m_width;   // TODO バグ m_w, m_hを消す
        m_rect.h = m_height;  // TODO バグ
        SDL_FillRect(m_window, &m_rect, m_color);
    }

    void setGravity(double g) { m_gravity = g; }
    double getGravity() { return m_gravity; }

    // !< 4辺が衝突しているかどうか
    bool getCollisionFlag(int i) { return m_collision_flag.at(i); }
    void setCollisionTrue(int i) { m_collision_flag.at(i) = true; }
    void setCollisionAll(bool collision)
    {
        for (int i = 0; i < m_collision_flag.size(); i++) {
            m_collision_flag.at(i) = collision;
        }
    }

    std::function<void(std::shared_ptr<Abstraction>)> callMyFuncCollisionTrueWithObject(int i) { return m_my_func_collision_true_with_object.at(i); }
    std::function<void(std::shared_ptr<Abstraction>)> callOtherFuncCollisionTrueWithObject(int i) { return m_other_func_collision_true_with_object.at(i); }
    std::function<void(std::shared_ptr<Abstraction>)> callMyFuncCollisionFalseWithObject(int i) { return m_my_func_collision_false_with_object.at(i); }

    std::function<void(std::shared_ptr<Abstraction>)> callOtherFuncCollisionTrueWithCharacter() { return m_other_func_collision_true_with_character; }

    double getLifePoint() const { return m_life_point; }
    void updateLifePoint(double diff_life_point) { m_life_point += diff_life_point; }
    bool isAlive() { return m_is_alive; }
    void setAlive(bool is_alive) { m_is_alive = is_alive; }

    int setIdx(int idx) { m_idx = idx; }
    int getIdx() const { return m_idx; }

    State getState() const { return m_state; }
    void setState(State state) { m_state = state; }

    virtual int getJumpCount() const { return m_jump_cnt; }
    virtual void updateJumpCount(int cnt) { m_jump_cnt += cnt; }
    virtual void setJumpCount(int cnt) { m_jump_cnt = cnt; }

    void setFriction(double friction) { m_friction = friction; }
    double getFriction() const { return m_friction; }


protected:
    std::vector<std::array<Point, 3>> m_collision_points;
    std::vector<Point> m_frame_points;

    Point m_pos;
    Point m_pre_pos;
    Point m_vel;
    constexpr static double m_max_vel = 5;

    double m_gravity = 0;

    int m_idx = -1;

    //!< 4辺が衝突しているかどうか
    std::array<bool, 4> m_collision_fix_object_flag;
    std::array<bool, 4> m_collision_unique_object_flag;

    //!< ライフポイント
    double m_life_point = 10;
    //!< 生存しているかどうか
    bool m_is_alive = true;

    //!< 状態
    State m_state;

    int m_jump_cnt = 0;

    // TODO 引数考える
    std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4> m_my_func_collision_true_with_object
        = std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4>{[](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}};  // !< 衝突した時の自分が受ける処理関数
    std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4> m_other_func_collision_true_with_object
        = std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4>{[](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}};  // !< 衝突した時の相手が受ける処理関数
    std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4> m_my_func_collision_false_with_object
        = std::array<std::function<void(std::shared_ptr<Abstraction>)>, 4>{[](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}, [](std::shared_ptr<Abstraction>) {}};  // !< 衝突していない時の自分が受ける処理関数

    std::function<void(std::shared_ptr<Abstraction>)> m_other_func_collision_true_with_character
        = [](std::shared_ptr<Abstraction>) {};

    std::vector<bool> m_collision_flag;

    SDL_Rect m_rect;

    //!< Note なぜかm_width, m_heightを付けないとオブジェクトが画面から見きれる
    double m_width, m_height;

    double m_friction;
    double DEFAULT_FRICTION = 0.4;

private:
    int m_color;
    std::string m_name;
};
