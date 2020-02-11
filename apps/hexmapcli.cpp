#include <vector>
#include <math.h>
#include <hexmap/HexagonMap.h>

using namespace std;

int main(void)
{
    HexagonMap hm(AxialCoordinates(0,0), 30, true);
    hm.InitialiseGLFW();
    hm.StartRenderLoop();

}


