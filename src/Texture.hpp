#pragma once

#include <SDL2/SDL.h>
#include "common.hpp"
#include "Lazy.hpp"

using SdlTexturePtr = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>;

class Texture {
public:
    explicit Texture(SDL_Texture* sdl_texture) {
        if (!sdl_texture) {
            throw std::runtime_error("texture pointer can't be null");
        }
        this->sdl_texture = SdlTexturePtr(sdl_texture, &SDL_DestroyTexture);
        SDL_QueryTexture(sdl_texture, nullptr, nullptr, &this->w, &this->h);
    }

    Texture(const Texture& other) = delete;

    Texture(Texture&& other) noexcept {
        this->swap(other);
    }

    Texture& operator=(Texture& other) = delete;

    Texture& operator=(Texture&& other) noexcept {
        this->swap(other);
        return *this;
    }

    void swap(Texture& other) noexcept {
        std::swap(this->sdl_texture, other.sdl_texture);
        std::swap(this->w, other.w);
        std::swap(this->h, other.h);
    }

    [[nodiscard]] SDL_Texture* get() const { return this->sdl_texture.get(); }

    [[nodiscard]] int width() const { return this->w; }

    [[nodiscard]] int height() const { return this->h; }

    [[nodiscard]] SDL_Point size() const {
        return point(this->w, this->h);
    }

    [[nodiscard]] SDL_Rect bounding_box() const {
        return rect(0, 0, this->w, this->h);
    }

private:
    SdlTexturePtr sdl_texture;
    int w;
    int h;
};

namespace test::texture {
    inline void should_not_create_null_texture() {
        try {
            Texture texture(nullptr);
        } catch (std::runtime_error& e) {
            return;
        }
        fail("should had thrown");
    }
}
