#pragma once

enum class MatchSceneAction {
    NoAction,
    Pause,
    Resume,
    UpdateWorld,
    GoalForP1,
    GoalForP2,
    CompleteMatch,
    Quit,
    BallOutsideOfTable,
    PlayBounceSound,
};
