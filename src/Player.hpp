#pragma once

#include "common.hpp"

enum class Player {
    P1,
    P2,
};

enum class VsMode {
    VsComputer,
    VsPlayer,
};

inline std::string get_p1_name() {
    return "P1";
}

inline std::string get_p2_name(VsMode players_mode) {
    switch (players_mode) {
        case VsMode::VsComputer:
            return "CPU";
        case VsMode::VsPlayer:
            return "P2";
        default:
            throw unexpected();
    }
}

inline std::string get_player_name(Player player, VsMode vs_mode) {
    switch (player) {
        case Player::P1:
            return get_p1_name();
        case Player::P2:
            return get_p2_name(vs_mode);
        default:
            throw unexpected();
    }
}

inline VsMode invert_vs_mode(VsMode vs_mode) {
    switch (vs_mode) {
        case VsMode::VsComputer:
            return VsMode::VsPlayer;
        case VsMode::VsPlayer:
            return VsMode::VsComputer;
        default:
            throw unexpected();
    }
}

inline std::string get_vs_mode_name(VsMode vs_mode) {
    switch (vs_mode) {
        case VsMode::VsComputer:
            return "Vs CPU";
        case VsMode::VsPlayer:
            return "Vs P2";
        default:
            throw unexpected();
    }
}