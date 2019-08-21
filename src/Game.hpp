#pragma once

#include <memory>
#include "Scene.hpp"
#include "RenderEngine.hpp"
#include "Sdl.hpp"
#include "PhysicsWorld.hpp"

struct HighScoreEntry {
    std::string name;
    Player winner;
    VsMode vs_mode;
    int score_p1;
    int score_p2;
};

class Game {
public:
    static const int FPS;
    static const int WINNING_SCORE;

    Game();

    void start();
    void quit();

    void change_scene(std::unique_ptr<Scene> new_next_scene);
    void save_score(const std::string& name, Player winner, VsMode vs_mode, int score_p1, int score_p2);

    [[nodiscard]] const RenderEngine& renderer() const {
        return this->render_engine;
    }

    [[nodiscard]] const std::vector<HighScoreEntry>& get_high_score_entries() const;

private:
    void main_loop();

    void check_next_scene();
    void poll_events();
    void update_logic();
    void render();

    Sdl sdl;
    RenderEngine render_engine;
    bool running;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Scene> next_scene;
};
