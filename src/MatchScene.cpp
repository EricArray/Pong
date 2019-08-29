#include "Game.hpp"
#include "MatchScene.hpp"
#include "MatchStatePaused.hpp"
#include "MatchStatePlaying.hpp"
#include "MatchStateFinished.hpp"
#include "MainMenuScene.hpp"
#include "SaveHighScoreScene.hpp"

MatchScene::MatchScene(Game& game, VsMode vs_mode) :
    Scene(game),
    vs_mode(vs_mode),
    p1_score(0),
    p2_score(0),
    header_component(game, vs_mode),
    state(new MatchStatePlaying()), controller_p1(new PaddleControllerPlayer(SDL_SCANCODE_W, SDL_SCANCODE_S)),
    controller_p2(
        vs_mode == VsMode::VsPlayer
        ? static_cast<PaddleController*>(new PaddleControllerPlayer(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN))
        : static_cast<PaddleController*>(new PaddleControllerComputer())
    ) {

}

void MatchScene::on_keydown(SDL_Scancode key) {
    this->react(this->state->on_keydown(key));
}

void MatchScene::on_update() {
    this->pong_world.set_paddle_movement_p1(this->controller_p1->get_movement());
    this->pong_world.set_paddle_movement_p2(this->controller_p2->get_movement());

    this->react(this->state->on_update());

    if (this->next_state) {
        this->state.swap(this->next_state);
        this->next_state.reset();
    }
}

void MatchScene::on_render() {
    this->header_component.render(game.renderer(), point(0, 0));
    this->pong_world.render(game.renderer(),
                            center_rect(point(900, 450),
                                        rect(50, 50, Renderer::WINDOW_W - 100, Renderer::WINDOW_H - 100)));
    this->state->on_render(game.renderer());
}

void MatchScene::goal(Player player) {
    int& score =
        player == Player::P1
        ? this->p1_score
        : this->p2_score;

    score += 1;

    this->header_component.set_scores(this->p1_score, this->p2_score);

    if (score >= Game::WINNING_SCORE) {
        this->change_state(std::unique_ptr<MatchState>(new MatchStateFinished(player, this->vs_mode)));
    } else {
        this->pong_world.reset_ball();
    }
}

void MatchScene::change_state(std::unique_ptr<MatchState> new_state) {
    this->next_state.swap(new_state);
}

void MatchScene::react(MatchSceneAction action) {
    switch (action) {
        case MatchSceneAction::NoAction:
            break;
        case MatchSceneAction::Pause: {
            this->change_state(std::unique_ptr<MatchState>(new MatchStatePaused()));
            this->game.mixer().pause();
            break;
        }
        case MatchSceneAction::Resume: {
            this->change_state(std::unique_ptr<MatchState>(new MatchStatePlaying()));
            this->game.mixer().resume();
            break;
        }
        case MatchSceneAction::UpdateWorld: {
            auto world_actions = this->pong_world.update();
            for (auto world_action : world_actions) {
                this->react(world_action);
            }
            break;
        }
        case MatchSceneAction::GoalForP1: {
            this->goal(Player::P1);
            break;
        }
        case MatchSceneAction::GoalForP2: {
            this->goal(Player::P2);
            break;
        }
        case MatchSceneAction::CompleteMatch: {
            this->game.change_scene(std::unique_ptr<Scene>(new SaveHighScoreScene(
                this->game,
                (this->p1_score > this->p2_score ? Player::P1 : Player::P2),
                this->vs_mode, this->p1_score, this->p2_score
            )));
            break;
        }
        case MatchSceneAction::Quit: {
            this->game.change_scene(std::unique_ptr<Scene>(new MainMenuScene(this->game)));
            break;
        }
        case MatchSceneAction::BallOutsideOfTable: {
            this->pong_world.reset_ball();
            break;
        }
        case MatchSceneAction::PlayBounceSound: {
            this->game.mixer().play_sound("bounce");
            break;
        }
    }
}
