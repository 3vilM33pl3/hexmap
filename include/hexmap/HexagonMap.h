#pragma once

#include <cstdint>
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <hexworld/hex_client.h>
#include <hexworld/hex_lib.h>
#include <hexworld/hex_com_state.h>

#define HEX_SIZE 15
#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 400

struct PixelPoint {
    int64_t X;
    int64_t Y;

    PixelPoint(int64_t X_, int64_t Y_)
    {
        X = X_;
        Y = Y_;
    }
};

class HexagonMap {

public:
    AxialCoordinates AxialCoords = AxialCoordinates(0,0);
    PixelPoint Center = PixelPoint(0, 0);
    std::vector<PixelPoint> Corners;
    int PixelSize;

    HexagonMap(const struct AxialCoordinates ac, int Size, bool bFlatTop = true);

    int InitialiseGLFW();
    void StartRenderLoop();
    hw_conn_state Connect();

    void GetHexCircle(int radius);
    void GetHexRing(int radius);
    void ClearMap();

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

private:
    HexagonClient* hexagonClient;
//    function flat_hex_to_pixel(hex):
//        var x = size * (     3./2 * hex.q                    )
//        var y = size * (sqrt(3)/2 * hex.q  +  sqrt(3) * hex.r)
//        return Point(x, y)
    PixelPoint ConvertAxialToPixelCoords(const struct AxialCoordinates &ac, const int size);
    std::vector<PixelPoint> CalculatePixelCoordsCorners(const PixelPoint Center, const int Size);
    void RenderFlatTopHexagon(const HexagonMap &hex);

    void RenderFlatTopFilledHexagon(const HexagonMap &hex);

    void Renderloop(const std::vector<HexagonMap> vhex);

    GLFWwindow* window;
    std::vector<HexagonMap> hav;

};



