#pragma once

#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
/*#include <algorithm>*/
/*#include "engine/coordinate.h" // for Coordinate struct*/


// No need to sort coordinates, since I'm already using a for loop
// and comparing the values within the Sprite.
/*void sortCoordinates(std::vector<Coordinate>& coordinates) {*/
/*    std::sort(coordinates.begin(), coordinates.end(),*/
/*        [](const Coordinate& a, const Coordinate& b) {*/
/*            if (a.x == b.x) {*/
/*                return a.y < b.y;*/
/*            } else {*/
/*                return a.x < b.x;*/
/*            }*/
/*        });*/
/*}*/

void clear() {
    std::cout << "\x1B[2J\x1B[1;1H";
}

void refresh() {
    std::cout << "\x1B[H";
}

void sleep(const int& milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
