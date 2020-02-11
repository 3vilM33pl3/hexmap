#include <iostream>
#include <hexmap/HexagonMap.h>
#include <hexlib/HexagonClient.hpp>

using namespace std;

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

void HexagonMap::StartRenderLoop() {
    vector<HexagonMap> hav = GetHexRing();

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

    for(const PixelPoint& p: hex.Corners) {
        glVertex3f(p.X + WINDOW_WIDTH/2, p.Y + WINDOW_HEIGHT/2, 0.0);
    }

    glEnd();
}

void HexagonMap::Renderloop(const vector<HexagonMap> vhex)
{
    glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1);
    glLineWidth(1);
    glColor3f(130.0/255.0, 130.0/255.0, 130.0/255.0);
    for(auto hex: vhex) {
        RenderFlatTopHexagon(hex);
    }
}

vector<HexagonMap> HexagonMap::GetHexRing() {
    shared_ptr<Channel> channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    auto ChannelStatus = channel->GetState(true);

    vector<HexagonMap> hav;

    if(channel->WaitForConnected(gpr_time_add(gpr_now(GPR_CLOCK_REALTIME), gpr_time_from_seconds(10, GPR_TIMESPAN)))) {
        if(ChannelStatus == GRPC_CHANNEL_READY || ChannelStatus == GRPC_CHANNEL_IDLE) {
            HexagonClient hexagonClient(channel);

            for(int i = 1; i < 8; i++) {
                auto result = hexagonClient.GetHexagonRing(new Hexagon(0, 0, 0), i);
                for(auto hex: result) {
                    hav.push_back(HexagonMap(AxialCoordinates(hex.q, hex.s), HEX_SIZE));
                }
            }
        } else {
            cout << "Channel not ready" << endl;
        }
    } else {
        cout << "Channel connection timeout" << endl;
    }

    return hav;
}