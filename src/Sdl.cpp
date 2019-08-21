#include "Sdl.hpp"
#include "common.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std::string_literals;

Sdl::Sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw sdl_exception();
    }

    if (TTF_Init() < 0) {
        throw ttf_exception();
    }
}

Sdl::~Sdl() {
    TTF_Quit();
    SDL_Quit();
}
