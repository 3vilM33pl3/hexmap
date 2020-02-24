#include <hexmap/HexagonMap.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <thread>
#include <future>

void CliMenu(HexagonMap &hm);

using namespace std;
using namespace cli;

void RenderTask(HexagonMap* hm) {
    hm->InitialiseGLFW();
    hm->StartRenderLoop();
}

void CliMenu(HexagonMap &hm) {
    auto rootMenu = make_unique<Menu>("cli");

    rootMenu->Insert("start",
                     [&hm](ostream& out)
                     {
                        cout << "Connecting to server" << endl;

                         if(hm.Connect() != 0) {
                             cout << "Unable to connect to server" << endl;
                         }
                     },
    "Start visualisation");
    rootMenu->Insert("circle",{"r"},
                     [&hm](ostream& out, int radius)
                     {
                         hm.GetHexCircle(radius);
                     },
                     "Get hexagon circle");
    rootMenu->Insert("ring", {"r"},
                    [&hm](ostream& out, int radius)
                    {
                        hm.GetHexRing(radius);
                    },
                    "Get hexagon ring");
    rootMenu->Insert("clear",
                     [&hm](ostream& out)
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
    thread t1(CliMenu, std::ref(hm));
    RenderTask(&hm);
    t1.join();

}

