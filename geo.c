#include <stdio.h>
#include <stdlib.h>

#include "geo.h"

// plot a point at a location (x, y) on screen
void plot(int x, int y, Color c)
{
    printf("Plot: (%d, %d) Color(%d, %d, %d)\n", x, y, c[0], c[1], c[2]);
}

//helper functions for plotLine
void switchToOctantZeroFrom(int octant, int* x, int* y)
{
    switch(octant)
    {
    case 0:
        return;
    case 1:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        return;
    case 2:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *x = -(*x);
        return;
    case 3:
        *x = -(*x);
        return;
    case 4:
        *x = -(*x);
        *y = -(*y);
        return;
    case 5:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *x = -(*x);
        *y = -(*y);
        return;
    case 6:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *y = -(*y);
        return;
    case 7:
        *y = -(*y);
        return;
    }
}

void switchFromOctantZeroTo(int octant, int* x, int* y)
{
    switch(octant)
    {
    case 0:
        return;
    case 1:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        return;
    case 2:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *y = -(*y);
        return;
    case 3:
        *x = -(*x);
        return;
    case 4:
        *x = -(*x);
        *y = -(*y);
        return;
    case 5:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *x = -(*x);
        *y = -(*y);
        return;
    case 6:
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
        *x = -(*x);
        return;
    case 7:
        *y = -(*y);
        return;
    }
}


// plots a line segment from (x0, y0) to (x1, y1) on screen
void plotLine(int x0, int y0, int x1, int y1, Color c)
{
    printf("Plot Line: (%d, %d) to (%d, %d)\n", x0, y0, x1, y1);
    int dx = x1 - x0;
    int dy = y1 - y0;

    int q = 3 * (dy < 0) + (dy >= 0 ? 1 : -1) * (dx < 0); //determine quadrant
    int o = 2 * q + (q % 2) * (abs(dx) >= abs(dy)) + ((q + 1) % 2) * (abs(dy) > abs(dx)); // determine octant

    switchToOctantZeroFrom(o, &x0, &y0);
    switchToOctantZeroFrom(o, &x1, &y1);
    dx = x1 - x0;
    dy = y1 - y0;

    int D = 2*dy - dx;
    int y = y0;

    for(int x = x0; abs(x) <= abs(x1); x += x1 / abs(x1))
    {
        int tx = x, ty = y;
        switchFromOctantZeroTo(o, &tx, &ty);
        plot(tx, ty, c);
        if(D * (dy < 0 ? -1 : 1) > 0)
        {
            y += y1 / abs(y1);
            D = D - 2*dx;
        }
        D = D + 2*dy;
    }
}

//helper functions for plotTri
void plotBotTri(P2 v1, P2 v2, P2 v3, Color c)
{
    double invslope1 = (v2[0] - v1[0]) / (v2[1] - v1[1]);
    double invslope2 = (v3[0] - v1[0]) / (v3[1] - v1[1]);

    double curx1 = v1[0];
    double curx2 = v1[0];

    for(int y = v1[1]; y <= v2[1]; ++y)
    {
        if(curx1 <= curx2)
            plotLine((int)curx1, y, (int)curx2, y, c);
        else
            plotLine((int)curx2, y, (int)curx1, y, c);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void plotTopTri(P2 v1, P2 v2, P2 v3, Color c)
{
    double invslope1 = (v3[0] - v1[0]) / (v3[1] - v1[1]);
    double invslope2 = (v3[0] - v2[0]) / (v3[1] - v2[1]);

    double curx1 = v3[0];
    double curx2 = v3[0];

    for(int y = v3[1]; y > v1[1]; --y)
    {
        if(curx1 <= curx2)
            plotLine((int)curx1, y, (int)curx2, y, c);
        else
            plotLine((int)curx2, y, (int)curx1, y, c);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void plotTri(P2 v1, P2 v2, P2 v3, Color c)
{
    // sort the vertices by y-coor ascending so v1 is topmost
    if(v1[1] > v2[1])
    {
        //swap(v1, v2);
        int* tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    if(v2[1] > v3[1])
    {
        //swap(v2, v3);
        int* tmp = v2;
        v2 = v3;
        v3 = tmp;
    }
    if(v1[1] > v2[1])
    {
        //swap(v1, v2);
        int* tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    // check for bottom-flat triangle
    if(v2[1] == v3[1])
    {
        plotBotTri(v1, v2, v3, c);
        return;
    }
    // check for top-flat triangle
    if(v1[1] == v2[1])
    {
        plotTopTri(v1, v2, v3, c);
        return;
    }

    P2 v4 = { (int)(v1[0] + ((double)(v2[1] - v1[0]) / (double)(v3[1] - v1[1])) * (v3[0] - v1[0])), v2[1]};
    plotBotTri(v1, v2, v4, c);
    plotTopTri(v2, v4, v3, c);
}
