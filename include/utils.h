#pragma once

#include <vector>
#include <algorithm>
#include "engine/engine.h" // for Coordinate struct

void sortCoordinates(std::vector<Coordinate> coordinates) {
    std::sort(coordinates.begin(), coordinates.end(), [](const Coordinate& a, const Coordinate& b) {
        if (a.x == b.x) {
            return a.y < b.y;
        } else {
            return a.x < b.x;
        }
    });
}
