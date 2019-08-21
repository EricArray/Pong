#include "Game.hpp"
#include "Scene.hpp"

Scene::Scene(Game& game) :
    game(game) {

}

Scene::~Scene() {

}

void Scene::poll_event(const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN: this->on_keydown(event.key.keysym.scancode);
    }
}