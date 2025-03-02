
#pragma once

struct BoundingBox {
    int far_top;
    int far_left;
    int far_right;
    int far_bottom;

    void increase_y(int amount) {
        far_top += amount;
        far_bottom += amount;
    }

    void increase_x(int amount) {
        far_left += amount;
        far_right += amount;
    }

    void decrease_y(int amount) {
        far_top -= amount;
        far_bottom -= amount;
    }

    void decrease_x(int amount) {
        far_left -= amount;
        far_right -= amount;
    }
};
