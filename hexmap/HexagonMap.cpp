#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <hexmap/HexagonMap.h>
#include <mutex>

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

std::vector<PixelPoint> HexagonMap::CalculatePixelCoordsCorners(const PixelPoint Center, const int Size) {
    auto vpp = std::vector<PixelPoint>();
    for(int i = 0; i < 6; i++) {
        double angle_deg = 60 * i;
        double angle_rad = M_PI / 180.0f * angle_deg;
        double dsize = Size;
        vpp.push_back(PixelPoint(Center.X + round(dsize * cos(angle_rad)), Center.Y + round(dsize * sin(angle_rad))));
    }
    return vpp;
}

void HexagonMap::StartRenderLoop() {


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        Renderloop(hav);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

}

int HexagonMap::InitialiseGLFW() {
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

    return 0;
}

void HexagonMap::RenderFlatTopHexagon(const HexagonMap &hex)
{
    glBegin(GL_LINE_LOOP);
    glColor3f(0.1, 0.1, 0.1);
    for(const PixelPoint& p: hex.Corners) {
        glVertex3f(p.X + WINDOW_WIDTH/2, p.Y + WINDOW_HEIGHT/2, 0.0);
    }

    glEnd();
}

void HexagonMap::RenderFlatTopFilledHexagon(const HexagonMap &hex) {

    for(int i = 0; i < 6; i++) {
        glBegin(GL_TRIANGLES);
            glColor3f(0.7, 0.1, 0.1);
            glVertex3f(hex.Corners.at(i).X + WINDOW_WIDTH/2, hex.Corners.at(i).Y + WINDOW_HEIGHT/2, 0);
            int j = i + 1;
            if(j == 6) {
                j = 0;
            }
            glVertex3f(hex.Corners.at(j).X + WINDOW_WIDTH/2, hex.Corners.at(j).Y + WINDOW_HEIGHT/2, 0);
            glVertex3f(hex.Center.X + WINDOW_WIDTH/2, hex.Center.Y + WINDOW_HEIGHT/2, 0);
        glEnd();
    }

}



void HexagonMap::Renderloop(const std::vector<HexagonMap> vhex)
{
    glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1);
    glLineWidth(1);
    glColor3f(130.0/255.0, 130.0/255.0, 130.0/255.0);
    for(auto hex: vhex) {
        RenderFlatTopHexagon(hex);
        RenderFlatTopFilledHexagon(hex);
    }
}

hw_conn_state HexagonMap::Connect() {
    hexagonClient = new HexagonClient("hexcloud-j6feiuh7aa-ue.a.run.app:443");
    return hexagonClient->ConnectToServer();
}

void HexagonMap::ClearMap() {
    hav.clear();
}

std::mutex g_display_mutex;

void HexagonMap::GetHexCircle(int radius) {
    std::lock_guard<std::mutex> guard(g_display_mutex);
    for(int i = 1; i < radius; i++) {
        auto result = hexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), i);
        for(auto hex: result) {
            hav.push_back(HexagonMap(AxialCoordinates(hex.X, hex.Z), HEX_SIZE));
        }
    }
}

void HexagonMap::GetHexRing(int radius) {
    auto result = hexagonClient->GetHexagonRing(new Hexagon(0, 0, 0), radius);
    for(auto hex: result) {
        hav.push_back(HexagonMap(AxialCoordinates(hex.X, hex.Z), HEX_SIZE));
    }
}
