#pragma once

#include <string>
#include "Texture.hpp"
#include "RenderEngine.hpp"

class LazyStringTexture {
public:
    explicit LazyStringTexture(std::string&& text) :
        lazy_texture([text = std::move(text)](const RenderEngine& re) {
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

    Texture& get(const RenderEngine& re) { return lazy_texture.get(re); }

private:
    Lazy<Texture, const RenderEngine&> lazy_texture;
};