#include <ctime>

#include <GL/gl.h>
#include <SDL/SDL.h>

#include "interface.h"

#include "painter.h"
#include "cosmos.h"
#include "config.h"
#include "graphics.h"

#include <cstdio>



void Interface::init(void) {
    Uint32 flags;

    atexit(&SDL_Quit);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_EnableUNICODE(SDL_TRUE);

    flags = SDL_HWSURFACE | SDL_OPENGL | SDL_GL_DOUBLEBUFFER;

    if (g_config.fulscr_) {
        flags |= SDL_FULLSCREEN;
    }

    sfc_ = SDL_SetVideoMode(
        g_config.scrw_, g_config.scrh_, 32, flags
        );

    SDL_WM_SetCaption("Three Body 1.3", NULL);

    /* OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glViewport(0, 0, g_config.scrw_, g_config.scrh_);
    glDisable(GL_DEPTH_TEST);

    setNatureCoord();

    glEnable(GL_BLEND);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
}

void Interface::mainLoop(void) {
    int can_exit = 0;
    SDL_Event event;
    unsigned long pv_tick, nx_tick, tick;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pv_tick = SDL_GetTicks();
    nx_tick = pv_tick + (1000 / g_config.mps_);

    while (!can_exit) {
        if (SDL_PollEvent(&event)) {
            /* handle event */
            switch (event.type) {
            case SDL_KEYDOWN:
                if (dealHotkeys(&event.key.keysym)) can_exit = 1;
                /*
                */
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
        tick = SDL_GetTicks();
        if (tick >= nx_tick) {
            if (!g_config.pause_) {
                cosmos_->doMove((float)(tick - pv_tick) / 1000.0);
            }
            pv_tick = tick;
            nx_tick = SDL_GetTicks() + (1000 / g_config.mps_);
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

void Interface::setNatureCoord(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-g_config.scrw_, g_config.scrw_,
            g_config.scrh_, -g_config.scrh_, 1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Interface::setScreenCoord(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, g_config.scrw_+1,
            g_config.scrh_ , -1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int Interface::dealHotkeys(SDL_keysym* key) {
    switch (key->sym) {
    case SDLK_q:
        return 1; /* return non-zero means exit */
    case SDLK_t:
        g_config.show_trace_ = !g_config.show_trace_;
        resetpixels();
        break;
    case SDLK_m:
        g_config.show_mline_ = !g_config.show_mline_;
        break;
    case SDLK_LEFTBRACKET:
        --g_config.mps_;
        if (g_config.mps_ < 1) g_config.mps_ = 1;
        break;
    case SDLK_RIGHTBRACKET:
        ++g_config.mps_;
        if (g_config.mps_ > 150) g_config.mps_ = 150;
        break;
    case SDLK_c:
        if (g_config.display_mode_ == DISPLAY_MASS) {
            g_config.display_mode_ = DISPLAY_RADIUS;
        } else {
            g_config.display_mode_ = DISPLAY_MASS;
        }
        break;
    case SDLK_SPACE:
        g_config.pause_ = !g_config.pause_;
    default:;
    }
    return 0;
}
