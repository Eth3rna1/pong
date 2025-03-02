/*
 * Engine; a wrapper around a matrix
*/
#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include "../utils.h"
#include "../engine/coordinate.h"

enum class PixelState {
    On,
    Off
};

class Engine {
    std::vector<std::vector<PixelState>> m_matrix;
public:
    int width;
    int height;

public:
    Engine(int width, int height): width(width), height(height) {
        if (width == 0) {
            throw std::runtime_error("Width dimension cannot be 0");
        } else if (height == 0) {
            throw std::runtime_error("Height dimension cannot be 0");
        }
        /*m_matrix.resize(height, std::vector<PixelState>(width, PixelState::Off));*/
        for (int row = 0; row < height; ++row) {
            std::vector<PixelState> buffer;
            for (int col = 0; col < width; ++col) {
                buffer.push_back(PixelState::Off);
            }
            m_matrix.push_back(buffer);
        }
    }

    void spawn(Coordinate coordinate) {
        m_matrix[coordinate.y][coordinate.x] = PixelState::On;
    }

    bool isOn(Coordinate coordinate) const {
        return m_matrix[coordinate.y][coordinate.x] == PixelState::On;
    }

    bool isOff(Coordinate coordinate) const {
        return m_matrix[coordinate.y][coordinate.x] == PixelState::Off;
    }

    void swap(Coordinate& c1, Coordinate& c2) {
        PixelState temp = m_matrix[c1.y][c1.x];
        m_matrix[c1.y][c1.x] = m_matrix[c2.y][c2.x];
        m_matrix[c2.y][c2.x] = temp;
    }

    void reset(Coordinate coordinate) {
        m_matrix[coordinate.y][coordinate.x] = PixelState::Off;
    }

    void clear() {
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                m_matrix[row][col] = PixelState::Off;
            }
        }
    }

    void display(char pixel_char, char background_char) {
        std::vector<std::string> lines;
        for (int row = 0; row < height; ++row) {
            std::string buffer;
            for (int col = 0; col < width; ++col) {
                if (m_matrix[row][col] == PixelState::On) {
                    buffer += pixel_char;
                } else {
                    buffer += background_char;
                }
            }
            std::string buffer_clone = buffer;
            lines.push_back(buffer_clone);
            buffer.clear();
        }
        std::string buffer;
        int line_total = lines.size();
        for (int i = 0; i < line_total; ++i) {
            buffer += lines[i];
            if (i != line_total - 1) {
                buffer += "\n";
            }
        }
        std::cout << buffer << std::endl;
    }
};
