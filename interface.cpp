#include <GL/gl.h>
#include <SDL/SDL.h>

#include "interface.h"

#include "painter.h"
#include "cosmos.h"



void Interface::init(void) {
    Uint32 flags;

    atexit(SDL_Quit);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_EnableUNICODE(SDL_TRUE);

    flags = SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER;
    /* full screen */
    /*flags |= SDL_FULLSCREEN;*/

    sfc_ = SDL_SetVideoMode(
        WIDTH, HEIGHT, 0, flags
        );

    /* OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-WIDTH, WIDTH, HEIGHT, -HEIGHT, 10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* data member intialization */
    fps_ = 30;
}

void Interface::mainLoop(void) {
    int can_exit;
    SDL_Event event;
    unsigned int tick;
    int tick_time;

    while (!can_exit) {
        if (SDL_PollEvent(&event)) {
            /* handle event */
            switch (event.type) {
            case SDL_KEYDOWN:
                (event.key.keysm.sym == SDLK_q) && (can_exit = 1);
                break;
            case SDL_Quit:
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
        tick_time = (clock() - tick) / 1000 / fps_;
        while (tick_time--) {
            cosmos_->doMove();
            tick = clock();
        }
    }
}

void Interface::setCosmos(Cosmos* cosmos) {
    cosmos_ = cosmos;
}

void Interface::setPainter(Painter* painter) {
    painter_ = painter;
}

