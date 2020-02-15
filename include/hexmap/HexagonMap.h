#pragma once


#include <cstdint>
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <hexlib/HexagonClient.hpp>

#define HEX_SIZE 15
#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 400

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

    int InitialiseGLFW();
    void StartRenderLoop();

    vector<HexagonMap> GetHexCircle(int radius);
    void ClearMap();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

private:

//    function flat_hex_to_pixel(hex):
//        var x = size * (     3./2 * hex.q                    )
//        var y = size * (sqrt(3)/2 * hex.q  +  sqrt(3) * hex.r)
//        return Point(x, y)
    PixelPoint ConvertAxialToPixelCoords(const struct AxialCoordinates &ac, const int size);
    vector<PixelPoint> CalculatePixelCoordsCorners(const PixelPoint Center, const int Size);
    void RenderFlatTopHexagon(const HexagonMap &hex);
    void Renderloop(const vector<HexagonMap> vhex);


    GLFWwindow* window;
    vector<HexagonMap> hav;

};



