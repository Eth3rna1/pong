#pragma once

#include <memory>
#include <vector>
#include "engine.h"
#include "bounding_box.h"
#include "../result.h"
#include "../utils.h"


class Sprite {
    std::shared_ptr<Engine> m_engine;
    std::vector<Coordinate> m_coordinates;
    BoundingBox m_bbox;
    int m_velocity;
    bool m_collisions;
    
    Sprite(std::shared_ptr<Engine> engine, std::vector<Coordinate> position, int velocity): m_engine(engine), m_velocity(velocity), m_collisions(false) {
        sortCoordinates(position);
        m_coordinates = position;
        int far_top = position[0].y;
        int far_left = position[0].x;
        int far_right = position[position.size()].y;
        int far_bottom = position[position.size()].y;
        m_bbox = BoundingBox { far_top, far_left, far_right, far_bottom };
    }

    void setCollisions(bool v) {
        m_collisions = v;
    }

    void moveUp() {}

    void moveDown() {}

    void moveLeft() {}

    void moveRight() {}

};
