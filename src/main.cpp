#include "game/Game.hpp"
#include "game/HighScores.hpp"

void run_pre_tests();
void start_game();

int main() {
    run_pre_tests();
    start_game();
    return 0;
}

void run_pre_tests() {
    test::texture::should_not_create_null_texture();
    test::lazy::should_not_init_until_get_is_called();
    test::lazy::should_only_call_once();
    test::lazy::should_accept_arguments();
    test::high_score_test();
}

void start_game() {
    Game game;
    game.start();
}