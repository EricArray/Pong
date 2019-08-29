#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <functional>
#include <map>
#include "Texture.hpp"

using Music = std::unique_ptr<Mix_Music, std::function<void(Mix_Music*)>>;
using Chunk = std::unique_ptr<Mix_Chunk, std::function<void(Mix_Chunk*)>>;

class Mixer {
public:
    Mixer();

    void pause() const;
    void resume() const;

    void play_music() const;

    void load_sound(const std::string& path, std::string&& name);
    void play_sound(const std::string& name) const;

private:
    Music music;
    std::map<std::string, Chunk> sounds;
};
