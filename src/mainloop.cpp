#include <iostream>
#include <fstream>
#include "include/mainloop.hpp"
#include "include/params.hpp"
#include "include/mario.hpp"
#include "include/kuribo.hpp"
#include "include/gabon.hpp"
#include "include/wooden_virtical_lift.hpp"
#include "include/wooden_circle_lift.hpp"
#include "include/wooden_rotate_rect.hpp"
#include "include/pipe.hpp"

/*!
 * @brief   コンストラクタ
 */
MainLoop::MainLoop()
{
    m_window_rect = SDL_Rect{0, 0, static_cast<uint16_t>(Params::WINDOW_WIDTH), static_cast<uint16_t>(Params::WINDOW_HEIGHT)};

    m_file_to_init_func = {{"../data/back_test_map.txt", [this]() { initTestWorld(); }}, {"../data/back_ice_map.txt", [this]() { initIceWorld(); }}};


    {  // Playerの初期化
        std::shared_ptr<AbstPlayer> mario = std::make_shared<Mario>();
        m_player_vec.push_back(std::move(mario));
    }
    m_back_file_name = "../data/back_test_map.txt";
    std::function<void(void)> func = m_file_to_init_func[m_back_file_name];  //"../data/back_test_map.txt"];
    func();

    //m_file_to_init_func[m_back_file_name];  // テスト環境の初期化


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(Params::WINDOW_WIDTH, Params::WINDOW_HEIGHT, Params::BPP, SDL_HWSURFACE);

    m_start_chrono_time = std::chrono::system_clock::now();
}

/*!
 * @brief   メインの実行関数
 */
void MainLoop::execute()
{
    while (not m_exit_flag) {
        double start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start_chrono_time).count();

        m_event_manager->execute(m_back_file_name, m_next_world);  //!< イベントの処理

        updateOther();  //!< 諸々の更新

        updatePos();        //!< 位置の更新
        updateCollision();  //!< 当たり判定
        updateStatus();     //!< 生存確認
        draw();             //!< 描画

        m_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_start_chrono_time).count();
        double diff_time = m_time - start_time;
        SDL_Delay(16 - diff_time);  // 16ms周期
    }
}

/*!
 * @brief   諸々の更新関数
 */
void MainLoop::updateOther()
{
    // Worldの変更フラグが立っていたら
    if (m_next_world != "") {
        m_back_file_name = m_next_world;
        std::function<void(void)> func = m_file_to_init_func[m_next_world];
        func();
        m_next_world = "";
    }
}

/*!
 * @brief   位置の更新関数
 */
void MainLoop::updatePos()
{
    for (auto player : m_player_vec) {
        player->updatePos(m_time);
    }
    for (auto enemy : m_enemy_vec) {
        enemy->updatePos(m_time);
    }
    for (auto item : m_item_vec) {
        item->updatePos(m_time);
    }
    for (auto rect_object : m_rect_object_vec) {
        rect_object->updatePos(m_time);
    }
    for (auto unique_object : m_unique_object_vec) {
        unique_object->updatePos(m_time);
    }
}

/*!
 * @brief   衝突の更新関数
 */
void MainLoop::updateCollision()
{
    m_collision_manager->updateCollision(m_fix_object_map, m_rect_object_vec, m_unique_object_vec, m_item_vec);
}

/*!
 * @brief   生存確認関数
 */
void MainLoop::updateStatus()
{
    for (int i = 0; i < m_player_vec.size(); i++) {
        if (not m_player_vec.at(i)->isAlive()) {
            m_player_vec.erase(m_player_vec.begin() + i);
        }
    }
    for (int i = 0; i < m_enemy_vec.size(); i++) {
        if (not m_enemy_vec.at(i)->isAlive()) {
            m_enemy_vec.erase(m_enemy_vec.begin() + i);
        }
    }

    /*
    for (auto item : m_item_vec) {
        item->updatePos(m_time);
    }
    for (auto rect_object : m_rect_object_vec) {
        rect_object->updatePos(m_time);
    }
    for (auto unique_object : m_unique_object_vec) {
        unique_object->updatePos(m_time);
		}*/
}

/*!
 * @brief   描画関数
 */
void MainLoop::draw()
{
    m_window = SDL_GetVideoSurface();
    SDL_FillRect(m_window, &m_window_rect, SDL_MapRGB(m_window->format, 0, 0, 0));

    // 基準点の変更
    m_window_x = 300 - m_player_vec.at(0)->getPos().m_x;

    // FixObjectMapの描画
    for (unsigned int i = 0; i < m_fix_object_map.size(); i++) {
        for (unsigned int j = 0; j < m_fix_object_map.at(i).size(); j++) {
            SDL_Rect rect;
            rect.x = j * Params::BLOCK_SIZE + m_window_x;
            rect.y = i * Params::BLOCK_SIZE;
            rect.w = Params::BLOCK_SIZE;
            rect.h = Params::BLOCK_SIZE;

            if (m_fix_object_map.at(i).at(j) == 1) {
                SDL_FillRect(m_window, &rect, 0x8d3800);
            } else if (m_fix_object_map.at(i).at(j) == 3) {
                SDL_FillRect(m_window, &rect, 0x9dcce0);
            }
        }
    }

    // Abstractionの継承クラスのインスタンスの描画
    for (auto player : m_player_vec) {
        player->draw(m_window, m_window_x);
    }
    for (auto enemy : m_enemy_vec) {
        enemy->draw(m_window, m_window_x);
    }
    for (auto item : m_item_vec) {
        item->draw(m_window, m_window_x);
    }
    for (auto rect_object : m_rect_object_vec) {
        rect_object->draw(m_window, m_window_x);
    }
    for (auto unique_object : m_unique_object_vec) {
        unique_object->draw(m_window, m_window_x);
    }

    // 更新
    SDL_UpdateRect(m_window, 0, 0, 0, 0);
    SDL_Flip(m_window);
}

void MainLoop::initTestWorld()
{
    {  // Enemyの初期化
        m_enemy_vec.clear();
        std::shared_ptr<AbstEnemy> kuribo1 = std::make_shared<Kuribo>();
        m_enemy_vec.push_back(std::move(kuribo1));

        std::shared_ptr<AbstEnemy> kuribo2 = std::make_shared<Kuribo>(1000);
        m_enemy_vec.push_back(std::move(kuribo2));

        std::shared_ptr<AbstEnemy> gabon1 = std::make_shared<Gabon>(100);
        m_enemy_vec.push_back(std::move(gabon1));
    }

    {  // Itemの初期化
        m_item_vec.clear();

        //auto kuribo = std::make_unique<Kuribo>();
        //m_item_vec.push_back(std::move(kuribo));
    }

    {  // FixObjectMapの初期化
        std::ifstream ifs(m_back_file_name);
        std::string str;
        int cnt = 0;
        const int object_size = Params::BLOCK_SIZE;

        // 固定ブロックの初期化
        m_fix_object_map.resize(Params::WINDOW_HEIGHT / object_size);
        while (getline(ifs, str)) {
            m_fix_object_map.at(cnt).resize(str.size());
            for (unsigned int i = 0; i < str.size(); i++) {
                int object = str[i] - '0';
                m_fix_object_map.at(cnt).at(i) = object;
            }
            cnt++;
        }
    }

    {  // RectObjectの初期化
        m_rect_object_vec.clear();

        std::shared_ptr<AbstRectObject> wooden_circle_lift1 = std::make_shared<WoodenCircleLift>(400, 200);
        m_rect_object_vec.push_back(std::move(wooden_circle_lift1));

        std::shared_ptr<AbstRectObject> wooden_virtical_lift1 = std::make_shared<WoodenVirticalLift>(80, 240);
        m_rect_object_vec.push_back(std::move(wooden_virtical_lift1));

        std::shared_ptr<AbstRectObject> pipe1 = std::make_shared<Pipe>(160, 360, 280, 360, "../data/back_test_map.txt", "../data/back_ice_map.txt");
        m_rect_object_vec.push_back(std::move(pipe1));
    }

    {  // UniqueObjectの初期化
        m_unique_object_vec.clear();

        std::shared_ptr<AbstUniqueObject> wooden_rotate_rect1 = std::make_shared<WoodenRotateRect>(800, 100, 50);
        //m_unique_object_vec.push_back(std::move(wooden_rotate_rect1));
    }

    {  // EventManagerの初期化
        m_event_manager = std::make_unique<EventManager>(m_event, m_input_type, m_player_vec);
    }

    {  // CollisionManagerの初期化
        m_collision_manager = std::make_unique<CollisionManager>(m_player_vec, m_enemy_vec);
    }
}

void MainLoop::initIceWorld()
{
    {  // Enemyの初期化
        m_enemy_vec.clear();

        std::shared_ptr<AbstEnemy> kuribo1 = std::make_shared<Kuribo>();
        m_enemy_vec.push_back(std::move(kuribo1));

        std::shared_ptr<AbstEnemy> kuribo2 = std::make_shared<Kuribo>(1000);
        m_enemy_vec.push_back(std::move(kuribo2));

        std::shared_ptr<AbstEnemy> gabon1 = std::make_shared<Gabon>(100);
        m_enemy_vec.push_back(std::move(gabon1));
    }

    {  // Itemの初期化
        m_item_vec.clear();

        //auto kuribo = std::make_unique<Kuribo>();
        //m_item_vec.push_back(std::move(kuribo));
    }

    {  // FixObjectMapの初期化
        std::ifstream ifs(m_back_file_name);

        std::string str;
        int cnt = 0;
        const int object_size = Params::BLOCK_SIZE;

        // 固定ブロックの初期化
        m_fix_object_map.resize(Params::WINDOW_HEIGHT / object_size);
        while (getline(ifs, str)) {
            m_fix_object_map.at(cnt).resize(str.size());
            for (unsigned int i = 0; i < str.size(); i++) {
                int object = str[i] - '0';
                m_fix_object_map.at(cnt).at(i) = object;
            }
            cnt++;
        }
    }

    {  // RectObjectの初期化
        m_rect_object_vec.clear();

        std::shared_ptr<AbstRectObject> wooden_circle_lift1 = std::make_shared<WoodenCircleLift>(400, 200);
        m_rect_object_vec.push_back(std::move(wooden_circle_lift1));

        std::shared_ptr<AbstRectObject> wooden_virtical_lift1 = std::make_shared<WoodenVirticalLift>(80, 240);
        m_rect_object_vec.push_back(std::move(wooden_virtical_lift1));

        std::shared_ptr<AbstRectObject> pipe1 = std::make_shared<Pipe>(160, 360, 280, 360, "../data/back_test_map.txt", "../data/back_ice_map.txt");
        pipe1->setPosByFile(m_back_file_name);
        m_rect_object_vec.push_back(std::move(pipe1));
    }


    {  // UniqueObjectの初期化
        m_unique_object_vec.clear();

        std::shared_ptr<AbstUniqueObject> wooden_rotate_rect1 = std::make_shared<WoodenRotateRect>(800, 100, 50);
        //m_unique_object_vec.push_back(std::move(wooden_rotate_rect1));
    }

    {  // EventManagerの初期化
        m_event_manager = std::make_unique<EventManager>(m_event, m_input_type, m_player_vec);
    }

    {  // CollisionManagerの初期化
        m_collision_manager = std::make_unique<CollisionManager>(m_player_vec, m_enemy_vec);
    }
}
