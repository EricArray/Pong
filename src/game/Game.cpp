#include <iostream>

#include "Game.hpp"
#include "NullScene.hpp"
#include "MainMenuScene.hpp"
#include "Scene.hpp"

const int Game::FPS = 32;
const int Game::WINNING_SCORE = 7;

Game::Game() :
    running(false), scene(new NullScene()), next_scene(nullptr) {
    this->mixer().play_music();
}

void Game::start() {
    this->change_scene(std::unique_ptr<Scene>(new MainMenuScene()));
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
        this->scene->on_event(*this, event);

        if (event.type == SDL_QUIT) {
            this->running = false;
        }
    }
}

void Game::update_logic() {
    this->scene->on_update(*this);
}

void Game::render() {
    this->_renderer.clear();
    this->scene->on_render(this->renderer());
    this->_renderer.present();
}
