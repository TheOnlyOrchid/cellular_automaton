#pragma once

constexpr int INFECTED_TIME = 2;

inline constexpr int directions[4][2] = {
    {-1, 0}, // left/up depending on your coordinate convention
    { 1, 0},
    { 0,-1},
    { 0, 1}
};