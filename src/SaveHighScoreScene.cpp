
#include <iomanip>
#include "SaveHighScoreScene.hpp"
#include "HighScoreScene.hpp"
#include "HighScores.hpp"

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

std::string get_date_string() {
    auto time = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d");
    return ss.str();
}

void SaveHighScoreScene::on_keydown(SDL_Scancode key) {
    if (key == SDL_SCANCODE_RETURN) {
        HighScoreEntry entry;
        entry.name = this->name;
        entry.date = get_date_string();
        entry.score_p1 = this->score_p1;
        entry.score_p2 = this->score_p2;
        save_high_score(entry);

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
    re.render_texture(this->title_texture.get(re), this->title_texture.get(re).bounding_box() + point(0, 0));
    re.render_rect(rect(40, 40, Renderer::WINDOW_W - 80, FONT_SIZE), FORE_COLOR, std::nullopt);
    re.render_texture(this->name_texture.get(re), this->name_texture.get(re).bounding_box() + point(40, 40));
}
