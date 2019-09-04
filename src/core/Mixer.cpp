#include "Mixer.hpp"
#include "../common.hpp"

#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>

using namespace std::string_literals;

Music load_music(const std::string& path) {
    auto music = Mix_LoadMUS(path.c_str());
    if (!music) {
        throw mix_exception();
    }
    return Music(music, &Mix_FreeMusic);
}

Chunk load_chunk(const std::string& path) {
    auto chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        throw mix_exception();
    }
    return Chunk(chunk, &Mix_FreeChunk);
}

Mixer::Mixer() :
    music(load_music("music.ogg")) {
    this->load_sound("bounce.ogg", "bounce");
}

void Mixer::pause() const {
    Mix_Pause(-1);
}

void Mixer::resume() const {
    Mix_Resume(-1);
}

void Mixer::load_sound(const std::string& path, std::string&& name) {
    if (this->sounds.count(name) > 0) {
        throw std::runtime_error("Sound "s + name + " was already loaded");
    }
    auto chunk = load_chunk(path);
    this->sounds.insert({std::move(name), std::move(chunk)});
}

void Mixer::play_sound(const std::string& name) const {
    auto sound = this->sounds.find(name);
    if (sound == this->sounds.end()) {
        throw std::runtime_error("Sound "s + name + " isn't loaded");
    }
    Mix_PlayChannel(-1, sound->second.get(), 0);
}

void Mixer::play_music() const {
    if (Mix_PlayMusic(this->music.get(), -1) < 0) {
        throw mix_exception();
    }
}
