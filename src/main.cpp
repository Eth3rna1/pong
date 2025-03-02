#include <iostream>
#include <memory>
#include <expected>
#include "../include/engine/engine.h"
#include "../include/errors.h"
#include "../include/engine/sprite.h"
#include "../include/utils.h"

constexpr int DELTA_TIME = 50; // in milliseconds
constexpr int HEIGHT = 20;
constexpr int WIDTH = 50;
constexpr char PIXEL_CHAR = '#';
constexpr char BACKGROUND_CHAR = '.';

constexpr int DOT_STEP_PER_DELTA = 2;

int main() {
    clear();
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(Engine(WIDTH, HEIGHT));
    std::vector<Coordinate> dot_position({Coordinate(0, engine->height / 2)});
    Sprite dot = Sprite(engine, dot_position, DOT_STEP_PER_DELTA);
    dot.spawn();
    for (int i = 0; i < engine->width; ++i) {
        std::expected<void, Error> result = dot.moveRight();
        if (!result.has_value()) {
            std::cout << result.error().diagnosis << std::endl;
            engine->display(PIXEL_CHAR, BACKGROUND_CHAR);
            break;
        }
        engine->display(PIXEL_CHAR, BACKGROUND_CHAR);
        sleep(DELTA_TIME);
        refresh();
    }
    return 0;
}
