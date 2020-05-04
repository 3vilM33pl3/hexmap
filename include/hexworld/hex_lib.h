#pragma once

struct Hexagon {
    int64_t X;
    int64_t Y;
    int64_t Z;

    Hexagon(int x_, int y_, int z_):X(x_), Y(y_), Z(z_) {};
};

struct AxialCoordinates {
    int32_t Q;
    int32_t R;

    AxialCoordinates(int32_t Q_, int32_t R_) {
        Q = Q_;
        R = R_;
    }
};