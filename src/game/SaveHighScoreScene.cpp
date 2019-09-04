
#include <iomanip>
#include "SaveHighScoreScene.hpp"
#include "HighScoreScene.hpp"
#include "HighScores.hpp"

SaveHighScoreScene::SaveHighScoreScene(
    Player winner,
    VsMode vs_mode,
    int score_p1, int score_p2
) :
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

void SaveHighScoreScene::on_event(Game& game, const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                HighScoreEntry entry;
                entry.name = this->name;
                entry.date = get_date_string();
                entry.score_p1 = this->score_p1;
                entry.score_p2 = this->score_p2;
                save_high_score(entry);

                game.change_scene(std::unique_ptr<Scene>(new HighScoreScene()));
            }
            break;
        }

        case SDL_TEXTINPUT: {
            if (this->name.size() < 20) {
                this->name += event.text.text;
                this->name_texture = LazyStringTexture(std::string(this->name));
            }
            break;
        }

        default:;
    }
}

void SaveHighScoreScene::on_update(Game&) {

}

void SaveHighScoreScene::on_render(const Renderer& re) {
    re.render_texture(this->title_texture.get(re), this->title_texture.get(re).bounding_box() + point(0, 0));
    re.render_rect(rect(40, 40, Renderer::WINDOW_W - 80, FONT_SIZE), FORE_COLOR, std::nullopt);
    re.render_texture(this->name_texture.get(re), this->name_texture.get(re).bounding_box() + point(40, 40));
}
