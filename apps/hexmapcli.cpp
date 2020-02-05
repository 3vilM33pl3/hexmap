#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <hexmap/HexagonMap.h>
#include <hexlib/HexagonClient.hpp>

#define HEX_SIZE 15
#define WINDOW_HEIGHT 400
#define WINDOW_WIDTH 400

using namespace std;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void render_flat_top_hexagon(const HexagonMap &hex)
{
    glBegin(GL_LINE_LOOP);

    for(const PixelPoint& p: hex.Corners) {
        glVertex3f(p.X + WINDOW_WIDTH/2, p.Y + WINDOW_HEIGHT/2, 0.0);
    }

    glEnd();
}

void render_loop(const vector<HexagonMap> vhex)
{

    glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1);
    glLineWidth(1);
    glColor3f(130.0/255.0, 130.0/255.0, 130.0/255.0);
    for(auto hex: vhex) {
        render_flat_top_hexagon(hex);
    }

}

int main(void)
{
    HexagonClient hexagonClient;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    // Generated with https://glad.dav1d.de
    gladLoadGL();
    glfwSwapInterval(1);
    glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POLYGON_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    vector<HexagonMap> hav {
            HexagonMap(AxialCoordinates(0, 0), HEX_SIZE),
            HexagonMap(AxialCoordinates(1, 0), HEX_SIZE),
            HexagonMap(AxialCoordinates(0, 1), HEX_SIZE),
            HexagonMap(AxialCoordinates(1, -1), HEX_SIZE),
            HexagonMap(AxialCoordinates(-1, 0), HEX_SIZE),
            HexagonMap(AxialCoordinates(0, -1), HEX_SIZE),
            HexagonMap(AxialCoordinates(-1, 1), HEX_SIZE),
    };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        render_loop(hav);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}