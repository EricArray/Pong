
#include "SaveHighScoreScene.hpp"
#include "HighScoreScene.hpp"

SaveHighScoreScene::SaveHighScoreScene(Game& game,
                                       Player winner,
                                       VsMode vs_mode,
                                       int score_p1, int score_p2) :
    Scene(game),
    winner(winner),
    vs_mode(vs_mode),
    score_p1(score_p1),
    score_p2(score_p2),
    title_texture("Save High Score"),
    name_texture("") {

}

void SaveHighScoreScene::on_keydown(SDL_Scancode key) {
    if (key == SDL_SCANCODE_RETURN) {
        this->game.save_score(this->name, this->winner, this->vs_mode, this->score_p1, this->score_p2);
        this->game.change_scene(std::unique_ptr<Scene>(new HighScoreScene(this->game)));
    } else {
        this->name += SDL_GetScancodeName(key);
        this->name_texture = LazyStringTexture(std::string(this->name));
    }
}

void SaveHighScoreScene::on_update() {

}

void SaveHighScoreScene::on_render() {
    auto& re = this->game.renderer();
    re.render_texture(this->title_texture.get(re), 0, 0);
    re.render_texture(this->name_texture.get(re), 40, 40);
}
