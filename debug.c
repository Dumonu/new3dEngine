#include "geo.h"

int main()
{
    Color white = {255, 255, 255};
    Color black = {0, 0, 0};

    plot(4, 2, white);
    plot(32, 1, black);

    plotLine(1,1,10,1,white);
    plotLine(0, 1, 6, 4, white);
    plotLine(0,0,10,10,white);
    plotLine(1, 0, 4, 6, white);
    plotLine(1,1,1,10, white);
    plotLine(-1, 0, -4, 6, white);
    plotLine(0,0,-10,10, white);
    plotLine(0, 1, -6, 4, white);
    plotLine(-1,1,-10,1, white);
    plotLine(0, -1, -6, -4, white);
    plotLine(0, 0, -10, -10, white);
    plotLine(-1, 0, -4, -6, white);
    plotLine(-1, -1, -1, -10, white);
    plotLine(1, 0, 4, -6, white);
    plotLine(0, 0, 10, -10, white);
    plotLine(0, -1, 6, -4, white);

    P2 v1 = {25, 25};
    P2 v2 = {50, 50};
    P2 v3 = {20, 75};
    plotTri(v1, v2, v3, white);
}
