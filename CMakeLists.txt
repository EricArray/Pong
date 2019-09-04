cmake_minimum_required(VERSION 3.14)
project(pong)

set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.3)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.14)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx>=1.0.0)
PKG_SEARCH_MODULE(SDL2MIX REQUIRED SDL2_mixer>=2.0.2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR} ${SDL2MIX_INCLUDE_DIR})

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib)

set(
        SOURCES
        src/common.cpp
        src/common.hpp
        src/game/Game.cpp
        src/game/Game.hpp
        src/game/HighScoreListComponent.cpp
        src/game/HighScoreListComponent.hpp
        src/game/HighScores.cpp
        src/game/HighScores.hpp
        src/game/HighScoreScene.cpp
        src/game/HighScoreScene.hpp
        src/core/Lazy.hpp
        src/core/LazyStringTexture.hpp
        src/main.cpp
        src/game/MainMenuScene.cpp
        src/game/MainMenuScene.hpp
        src/game/MatchHeaderComponent.cpp
        src/game/MatchHeaderComponent.hpp
        src/game/MatchScene.cpp
        src/game/MatchScene.hpp
        src/game/MatchSceneAction.hpp
        src/game/MatchState.hpp
        src/game/MatchStateFinished.cpp
        src/game/MatchStateFinished.hpp
        src/game/MatchStatePaused.cpp
        src/game/MatchStatePaused.hpp
        src/game/MatchStatePlaying.cpp
        src/game/MatchStatePlaying.hpp
        src/core/Mixer.cpp
        src/core/Mixer.hpp
        src/game/NullScene.hpp
        src/core/PhysicsWorld.hpp
        src/core/PhysicsWorld.cpp
        src/game/Player.hpp
        src/game/PongWorld.cpp
        src/game/PongWorld.hpp
        src/core/OptionMenu.cpp
        src/core/OptionMenu.hpp
        src/core/Renderer.cpp
        src/core/Renderer.hpp
        src/game/SaveHighScoreScene.cpp
        src/game/SaveHighScoreScene.hpp
        src/game/Scene.cpp
        src/game/Scene.hpp
        src/core/Sdl.cpp
        src/core/Sdl.hpp
        src/core/Texture.hpp
)
add_executable(pong ${SOURCES})
target_link_libraries(pong SDL2 SDL2_image SDL2_ttf SDL2_gfx SDL2_mixer mpg123 Box2D)
target_compile_options(pong PRIVATE -Wall -Wextra -pedantic -Werror)

