#include <iostream>

#include "Game.hpp"
#include "NullScene.hpp"
#include "MainMenuScene.hpp"
#include "Scene.hpp"

const int Game::FPS = 32;
const int Game::WINNING_SCORE = 7;

Game::Game() :
    running(false), scene(new NullScene(*this)), next_scene(nullptr) {
}

void Game::start() {
    this->change_scene(std::unique_ptr<Scene>(new MainMenuScene(*this)));
    this->main_loop();
}

void Game::quit() {
    this->running = false;
}

void Game::change_scene(std::unique_ptr<Scene> new_next_scene) {
    this->next_scene.swap(new_next_scene);
}

void Game::main_loop() {
    this->running = true;
    while (this->running) {
        this->check_next_scene();
        this->poll_events();
        this->update_logic();
        this->render();
    }
}

void Game::check_next_scene() {
    if (this->next_scene) {
        this->scene = std::move(this->next_scene);
    }
}

void Game::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                this->running = false;
                break;
            }
            default: {
                this->scene->poll_event(event);
                break;
            }
        }
    }
}

void Game::update_logic() {
    this->scene->on_update();
}

void Game::render() {
    this->render_engine.clear();
    this->scene->on_render();
    this->render_engine.present();
}

static std::vector<HighScoreEntry> high_score_entries = {
    { "Eric", Player::P1, VsMode::VsComputer, 7, 1 },
    { "Ernok", Player::P2, VsMode::VsPlayer, 5, 7 },
};

const std::vector<HighScoreEntry>& Game::get_high_score_entries() const {
    return high_score_entries;
}

void Game::save_score(const std::string& name, Player winner, VsMode vs_mode, int score_p1, int score_p2) {
    high_score_entries.push_back({name, winner, vs_mode, score_p1, score_p2});
}
