#pragma once

#include <string>
#include <vector>
#include "Player.hpp"

struct HighScoreEntry {
    std::string name;
    std::string date;
    int score_p1;
    int score_p2;
};

[[nodiscard]] extern std::vector<HighScoreEntry> load_high_score_entries();

extern void save_high_score(const HighScoreEntry& entry);

namespace test {
    extern void high_score_test();
}