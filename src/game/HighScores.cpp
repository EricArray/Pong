
#include <fstream>
#include <sstream>
#include <cassert>
#include <algorithm>
#include "HighScores.hpp"

std::string entry_to_string(const HighScoreEntry& entry) {
    std::stringstream ss;
    ss << entry.name << "," << entry.date << "," << entry.score_p1 << "," << entry.score_p2;
    return ss.str();
}

HighScoreEntry string_to_entry(const std::string& str) {
    HighScoreEntry entry;

    std::stringstream ss(str);
    std::getline(ss, entry.name, ',');
    std::getline(ss, entry.date, ',');

    std::string score_str;
    std::getline(ss, score_str, ',');
    entry.score_p1 = std::stoi(score_str);
    std::getline(ss, score_str);
    entry.score_p2 = std::stoi(score_str);

    return entry;
}

bool compare_entries(const HighScoreEntry& a, const HighScoreEntry& b) {
    auto diff_a = std::max(a.score_p1, a.score_p2) - std::min(a.score_p1, a.score_p2);
    auto diff_b = std::max(b.score_p1, b.score_p2) - std::min(b.score_p1, b.score_p2);
    if (diff_a > diff_b) {
        return true;
    } else if (diff_a < diff_b) {
        return false;
    } else {
        return a.date < b.date;
    }
}

std::vector<HighScoreEntry> load_high_score_entries() {
    std::vector<HighScoreEntry> high_score_entries;
    std::ifstream ifs("highscores.txt");
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            high_score_entries.push_back(string_to_entry(line));
        }
    }
    std::sort(high_score_entries.begin(), high_score_entries.end(), compare_entries);
    return high_score_entries;
}

void save_high_score(const HighScoreEntry& entry) {
    std::ofstream ofs("highscores.txt", std::ios_base::app);
    if (ofs.is_open()) {
        ofs << entry_to_string(entry) << "\n";
    } else {
        throw std::runtime_error("Couldn't save high score");
    }
}

namespace test {
    extern void high_score_test() {
        HighScoreEntry entry;
        entry.name = "Eric";
        entry.date = "20180821";
        entry.score_p1 = 7;
        entry.score_p2 = 6;

        auto entry_string = entry_to_string(entry);
        assert(entry_string == "Eric,20180821,7,6");

        auto loaded_entry = string_to_entry(entry_string);
        assert(loaded_entry.name == entry.name);
        assert(loaded_entry.date == entry.date);
        assert(loaded_entry.score_p1 == entry.score_p1);
        assert(loaded_entry.score_p2 == entry.score_p2);
    }
}