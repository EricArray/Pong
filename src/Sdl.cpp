#include "Sdl.hpp"
#include "common.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std::string_literals;

Sdl::Sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw sdl_exception();
    }

    if (TTF_Init() < 0) {
        throw ttf_exception();
    }

    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) {
        throw mix_exception();
    } else {
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
            throw mix_exception();
        }
    }
}

Sdl::~Sdl() {
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
