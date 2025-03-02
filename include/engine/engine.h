/*
 * Engine; a wrapper around a matrix
*/
#pragma once

#include <vector>
#include <stdexcept>

struct Coordinate {
    int x;
    int y;

    Coordinate(int x, int y) : x(x), y(y) {}
};

enum class PixelState {
    On,
    Off
};

class Engine {
    std::vector<std::vector<PixelState>> m_matrix;

public:
    Engine(int width, int height) {
        if (width == 0) {
            throw std::runtime_error("Width dimension cannot be 0");
        } else if (height == 0) {
            throw std::runtime_error("Height dimension cannot be 0");
        }
        m_matrix.resize(height, std::vector<PixelState>(width, PixelState::Off));
    }

    bool isOn(Coordinate coordinate) const {
        return m_matrix[coordinate.y][coordinate.x] == PixelState::On;
    }

    bool isOff(Coordinate coordinate) const {
        return m_matrix[coordinate.y][coordinate.x] == PixelState::Off;
    }

    void swap(Coordinate c1, Coordinate c2) {
        PixelState temp = m_matrix[c1.y][c1.x];
        m_matrix[c1.y][c1.x] = m_matrix[c2.y][c2.x];
        m_matrix[c2.y][c2.x] = temp;
    }

    void reset(Coordinate coordinate) {
        m_matrix[coordinate.y][coordinate.x] = PixelState::Off;
    }

    void clear() {
        for (int row = 0; row < m_matrix.size(); ++row) {
            for (int col = 0; col < m_matrix[0].size(); ++col) {
                m_matrix[row][col] = PixelState::Off;
            }
        }
    }
};
