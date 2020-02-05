#include <hexmap/HexagonMap.h>

HexagonMap::HexagonMap(const AxialCoordinates AxialCoords, int Size, bool bFlatTop) {
    PixelSize = Size;
    Center = ConvertAxialToPixelCoords(AxialCoords, Size);
    Corners = CalculatePixelCoordsCorners(Center, Size);
}

PixelPoint HexagonMap::ConvertAxialToPixelCoords(const struct AxialCoordinates &ac, const int size) {
    double x = size * (3.0 / 2.0 * ac.Q);
    double y = size * (sqrt(3.0)/2.0 * ac.Q + sqrt(3.0) * ac.R);
    return PixelPoint(x, y);
}

vector<PixelPoint> HexagonMap::CalculatePixelCoordsCorners(const PixelPoint Center, const int Size) {
    auto vpp = vector<PixelPoint>();
    for(int i = 0; i < 6; i++) {
        double angle_deg = 60 * i;
        double angle_rad = M_PI / 180.0f * angle_deg;
        vpp.push_back(PixelPoint(Center.X + Size * cos(angle_rad), Center.Y + Size * sin(angle_rad)));
    }
    return vpp;
}
