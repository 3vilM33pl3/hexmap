#pragma once

#include <cstdint>
#include <vector>
#include <cmath>

using namespace std;

struct PixelPoint {
    int64_t X;
    int64_t Y;

    PixelPoint(int64_t X_, int64_t Y_)
    {
        X = X_;
        Y = Y_;
    }
};

struct AxialCoordinates {
    int32_t Q;
    int32_t R;

    AxialCoordinates(int32_t Q_, int32_t R_) {
        Q = Q_;
        R = R_;
    }
};

class HexagonMap {

public:
    AxialCoordinates AxialCoords = AxialCoordinates(0,0);
    PixelPoint Center = PixelPoint(0, 0);
    vector<PixelPoint> Corners;
    int PixelSize;

    HexagonMap(const struct AxialCoordinates ac, int Size, bool bFlatTop = true);

private:

//    function flat_hex_to_pixel(hex):
//        var x = size * (     3./2 * hex.q                    )
//        var y = size * (sqrt(3)/2 * hex.q  +  sqrt(3) * hex.r)
//        return Point(x, y)
    PixelPoint ConvertAxialToPixelCoords(const struct AxialCoordinates &ac, const int size);

    vector<PixelPoint> CalculatePixelCoordsCorners(const PixelPoint Center, const int Size);

};



