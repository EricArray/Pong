cmake_minimum_required(VERSION 3.14)
project(pong)

set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.3)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.14)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx>=1.0.0)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})

set(
        SOURCES
        src/common.hpp
        src/Game.cpp
        src/Game.hpp
        src/HighScoreListComponent.cpp
        src/HighScoreListComponent.hpp
        src/HighScoreScene.cpp
        src/HighScoreScene.hpp
        src/Lazy.hpp
        src/LazyStringTexture.hpp
        src/main.cpp
        src/MainMenuScene.cpp
        src/MainMenuScene.hpp
        src/MatchHeaderComponent.cpp
        src/MatchHeaderComponent.hpp
        src/MatchScene.cpp
        src/MatchScene.hpp
        src/MatchSceneAction.hpp
        src/MatchState.hpp
        src/MatchStateFinished.cpp
        src/MatchStateFinished.hpp
        src/MatchStatePaused.cpp
        src/MatchStatePaused.hpp
        src/MatchStatePlaying.cpp
        src/MatchStatePlaying.hpp
        src/NullScene.hpp
        src/PhysicsWorld.hpp
        src/PhysicsWorld.cpp
        src/Player.hpp
        src/PongWorld.cpp
        src/PongWorld.hpp
        src/OptionMenu.cpp
        src/OptionMenu.hpp
        src/RenderEngine.cpp
        src/RenderEngine.hpp
        src/SaveHighScoreScene.cpp
        src/SaveHighScoreScene.hpp
        src/Scene.cpp
        src/Scene.hpp
        src/Sdl.cpp
        src/Sdl.hpp
        src/Texture.hpp
)
add_executable(pong ${SOURCES})
target_link_libraries(pong SDL2 SDL2_image SDL2_ttf SDL2_gfx Box2D)
target_compile_options(pong PRIVATE -Wall -Wextra -pedantic -Werror)
