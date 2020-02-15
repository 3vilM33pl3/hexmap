#include <hexmap/HexagonMap.h>
#include <cli/cli.h>
#include <cli/clifilesession.h>
#include <thread>

using namespace std;
using namespace cli;

void RenderTask(HexagonMap* hm) {
    hm->InitialiseGLFW();
    hm->StartRenderLoop();
}

int main(void)
{
    HexagonMap hm(AxialCoordinates(0,0), 30, true);
    thread* t1;

    auto rootMenu = make_unique<Menu>("cli");

    rootMenu->Insert("start",
                     [&hm, &t1](ostream& out)
                     {
                        t1  = new thread(RenderTask, &hm);
                     },
    "Start visualisation");
    rootMenu->Insert("circle",{"r"},
                     [&hm](ostream& out, int radius)
                     {
                         hm.GetHexCircle(radius);
                     },
                     "Get hexagon circle");
    rootMenu->Insert("clear",
                     [&hm](ostream& out)
                     {
                         hm.ClearMap();
                     },
                     "Clear map");

    Cli cli( move(rootMenu) );
    // global exit action
    cli.ExitAction( [&t1](auto& out)
    {
        out << "Goodbye and thanks for all the fish.\n";
        t1->detach();
    });

    CliFileSession input(cli);
    input.Start();

}


