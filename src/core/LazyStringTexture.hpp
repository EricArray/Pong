#pragma once

#include <string>
#include "Texture.hpp"
#include "Renderer.hpp"

class LazyStringTexture {
public:
    explicit LazyStringTexture(std::string text) :
        lazy_texture([text = std::move(text)](const Renderer& re) {
            return re.create_text_texture(text);
        }) {

    }

    LazyStringTexture(LazyStringTexture&& other) :
        lazy_texture(std::move(other.lazy_texture)) {

    }

    LazyStringTexture& operator=(LazyStringTexture&& other) noexcept {
        this->lazy_texture = std::move(other.lazy_texture);
        return *this;
    }

    Texture& get(const Renderer& re) { return lazy_texture.get(re); }

private:
    Lazy<Texture, const Renderer&> lazy_texture;
};