#include <time.h>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "interface.h"

#include "painter.h"
#include "cosmos.h"

#include <cstdio>

void Interface::init(void) {
    Uint32 flags;

    atexit(&SDL_Quit);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_EnableUNICODE(SDL_TRUE);

    flags = SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
    /* full screen */
    /*flags |= SDL_FULLSCREEN;*/

    sfc_ = SDL_SetVideoMode(
        WIDTH, HEIGHT, 32, flags
        );

    /* OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-WIDTH, WIDTH, HEIGHT, -HEIGHT, 10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* data member intialization */
    fps_ = 30.0;
}

void Interface::mainLoop(void) {
    int can_exit = 0;
    SDL_Event event;
    unsigned long nx_tick;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    nx_tick = SDL_GetTicks() + (1000 / fps_);

    while (!can_exit) {
        if (SDL_PollEvent(&event)) {
            /* handle event */
            switch (event.type) {
            case SDL_KEYDOWN:
                (event.key.keysym.sym == SDLK_q) && (can_exit = 1);
                break;
            case SDL_QUIT:
                can_exit = 1;
                break;
            default:;
            }
        }

        /* paint */
        if (painter_ && cosmos_) {
            painter_->draw(this);
        }

        /* move event */
        if (SDL_GetTicks() >= nx_tick) {
            cosmos_->doMove();
            nx_tick = SDL_GetTicks() + (1000 / fps_);
        }

        SDL_Delay(1);
    }
}

void Interface::setCosmos(Cosmos* cosmos) {
    cosmos_ = cosmos;
}

void Interface::setPainter(Painter* painter) {
    painter_ = painter;
}

