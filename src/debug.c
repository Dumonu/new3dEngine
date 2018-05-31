#include <SDL_events.h>
#include <unistd.h>
#include <math.h>

#include "global.h"
#include "geo.h"

SDL_Window* win;
SDL_Renderer* render;

const double pi = M_PI;

int main()
{
    /*****START SDL BOILERPLATE*****/
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("3D Graphics Engine", 100, 100, 300, 300, SDL_WINDOW_FULLSCREEN_DESKTOP);
    render = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(render, 100, 139, 237, 255);
    SDL_RenderFillRect(render, NULL);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderPresent(render);
    /*****END SDL BOILERPLATE*****/

    Color white = {255, 255, 255};
    Color black = {0, 0, 0};

    plot(4, 2, white);
    plot(32, 1, black);

    P2 t1v1 = {-100, 100};
    P2 t1v2 = {-100, -100};
    P2 t1v3 = {100, -100};
    plotTri(t1v1, t1v2, t1v3, black);

    SDL_RenderPresent(render);

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
 
    plotLine(0, 0, 100, 0, white);
    plotLine(0, 0, 100, 100, white);
    plotLine(0, 0, 0, 100, white);
    plotLine(0, 0, -100, 100, white);
    plotLine(0, 0, -100, 0, white);
    plotLine(0, 0, -100, -100, white);
    plotLine(0, 0, 0, -100, white);
    plotLine(0, 0, 100, -100, white);

    P2 v1 = {25, 25};
    P2 v2 = {50, 50};
    P2 v3 = {20, 75};
    plotTri(v1, v2, v3, white);

    SDL_RenderPresent(render);

 // for(double i = 0; i < 2 * pi; i += pi / 12)
 // {
 //     double x = cos(i);
 //     double y = sin(i);

 //     plotLine(0, 0, (int)(x * 100), (int)(y * 100), white);
 //     SDL_RenderPresent(render);
 // }

    while(1)
    {
        SDL_Event e;
        if(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                break;
            if(e.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = e.key.keysym.sym;

                switch(key)
                {
                case SDLK_ESCAPE:
                    {
                        SDL_Event exit;
                        exit.type = SDL_QUIT;
                        SDL_PushEvent(&exit);
                        break;
                    }
                }
            }
        }
    }
    SDL_Quit();
}
