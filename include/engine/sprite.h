#pragma once

#include <memory>
#include <vector>
#include <expected>
#include "engine.h"
#include "bounding_box.h"
/*#include "../result.h"*/
#include "../errors.h"
#include "../utils.h"

void moveSpriteUp(std::shared_ptr<Engine> engine, std::vector<Coordinate>& coordinates) {
    // reversing the array
    for (int i = coordinates.size(); i > 0; --i) {
        Coordinate expected = Coordinate(coordinates[i].x, coordinates[i].y - 1);
        engine->swap(coordinates[i], expected);
        coordinates[i] = expected;
    }
}

void moveSpriteLeft(std::shared_ptr<Engine> engine, std::vector<Coordinate>& coordinates) {
    // reversing the array
    for (int i = coordinates.size(); i > 0; --i) {
        Coordinate expected = Coordinate(coordinates[i].x - 1, coordinates[i].y);
        engine->swap(coordinates[i], expected);
        coordinates[i] = expected;
    }
}

void moveSpriteRight(Engine& engine, std::vector<Coordinate>& coordinates) {
    for (Coordinate& coordinate : coordinates) {
        Coordinate expected = Coordinate(coordinate.x + 1, coordinate.y);
        engine.swap(coordinate, expected);
        coordinate = expected;
    }
}

void moveSpriteDown(Engine& engine, std::vector<Coordinate>& coordinates) {
    for (Coordinate& coordinate: coordinates) {
        Coordinate expected = Coordinate(coordinate.x, coordinate.y + 1);
        engine.swap(coordinate, expected);
        coordinate = expected;
    }
}


class Sprite {
    std::shared_ptr<Engine> m_engine;
    std::vector<Coordinate> m_coordinates;
    BoundingBox m_bbox;
    int m_velocity;
    bool m_collisions;
    
public:
    Sprite(std::shared_ptr<Engine> engine, std::vector<Coordinate> position, int velocity): m_engine(engine), m_velocity(velocity), m_collisions(false) {
        /*sortCoordinates(position);*/
        m_coordinates = position;
        int far_top = position[0].y;
        int far_left = position[0].x;
        int far_right = position[0].x;
        int far_bottom = position[0].y;
        for (Coordinate& coordinate: position) {
            if (coordinate.x > far_right) {
                far_right = coordinate.x;
            }
            if (coordinate.y > far_bottom) {
                far_bottom = coordinate.y;
            }
            if (coordinate.x < far_left) {
                far_left = coordinate.x;
            }
            if (coordinate.y < far_top) {
                far_top = coordinate.y;
            }
        }
        m_bbox = BoundingBox { far_top, far_left, far_right, far_bottom };
    }

    void setCollisions(bool v) {
        m_collisions = v;
    }

    void spawn() {
        for (const Coordinate& coordinate : m_coordinates) {
            m_engine->spawn(coordinate);
        }
    }

    void moveUp() {
        for (int i = 0; i < m_velocity; ++i) {
            moveSpriteUp(m_engine, m_coordinates);
        }
    }

    std::expected<void, Error> moveDown() {
        if (m_bbox.far_bottom >= m_engine->height - 1) {
            return std::unexpected(Error(ErrorKind::OutOfBounds, "Hit far bottom boundry"));
        }
        if (m_bbox.far_bottom + m_velocity >= m_engine->height) {
            for (int i = 0; i < m_engine->height - m_velocity; ++i) {
                moveSpriteDown(*m_engine, m_coordinates);
            }
            return std::unexpected(Error(ErrorKind::OutOfBounds, "Hit far bottom boundry"));
        }
        for (int i = 0; i < m_velocity; ++i) {
            moveSpriteDown(*m_engine, m_coordinates);
        }
        return {};
    }

    void moveLeft() {
        for (int i = 0; i < m_velocity; ++i) {
            moveSpriteDown(*m_engine, m_coordinates);
        }
    }

    std::expected<void, Error> moveRight() {
        int width = m_engine->width;
        if (m_bbox.far_right >= width - 1) {
            return std::unexpected(Error(ErrorKind::OutOfBounds,
                "Hit far right boundry 1"));
            }
            if (m_bbox.far_right + m_velocity >= width) {
                int steps = width - (width - m_velocity) - 1;
                // int steps = width - 1 - m_bbox.far_right;
                for (int i = 0; i < steps; ++i) {
                    moveSpriteRight(*m_engine, m_coordinates);
                }
                m_bbox.increase_x(steps);
                std::cout << "Bounding Box: " << m_bbox.far_right << std::endl;
                return std::unexpected(Error(ErrorKind::OutOfBounds, "Hit far right boundry 2"));
            }
            for (int i = 0; i < m_velocity; ++i) {
                moveSpriteRight(*m_engine, m_coordinates);
            }
            m_bbox.increase_x(m_velocity);
            std::cout << "Bounding Box: " << m_bbox.far_right << std::endl;
        return {};
    }
};

