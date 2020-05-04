#include <hexmap/HexagonMap.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <thread>
#include <future>

void CliMenu(HexagonMap &hm);

using namespace cli;

void RenderTask(HexagonMap* hm) {
    hm->InitialiseGLFW();
    hm->StartRenderLoop();
}

void CliMenu(HexagonMap &hm) {
    auto rootMenu = std::make_unique<Menu>("cli");

    rootMenu->Insert("start",
                     [&hm](std::ostream& out)
                     {
                        std::cout << "Connecting to server" << std::endl;

                         if(hm.Connect() != HEXWORLD_CONNECTION_READY) {
                             std::cout << "Unable to connect to server" << std::endl;
                         }
                     },
    "Start visualisation");
    rootMenu->Insert("circle",{"r"},
                     [&hm](std::ostream& out, int radius)
                     {
                         hm.GetHexCircle(radius);
                     },
                     "Get hexagon circle");
    rootMenu->Insert("ring", {"r"},
                    [&hm](std::ostream& out, int radius)
                    {
                        hm.GetHexRing(radius);
                    },
                    "Get hexagon ring");
    rootMenu->Insert("clear",
                     [&hm](std::ostream& out)
                     {
                         hm.ClearMap();
                     },
                     "Clear map");

    Cli cli( move(rootMenu) );
    // global exit action
    cli.ExitAction( [](auto& out)
    {
        out << "Goodbye and thanks for all the fish.\n";
    });

    CliFileSession input(cli);
    input.Start();
}

int main(void)
{
    HexagonMap hm(AxialCoordinates(0,0), 30, true);
    std::thread t1(CliMenu, std::ref(hm));
    RenderTask(&hm);
    t1.join();

}

