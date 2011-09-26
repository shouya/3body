#include <cmath>

#include <sstream>
#include <iomanip>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "painter.h"
#include "interface.h"
#include "mathlib.h"
#include "object.h"
#include "cosmos.h"
#include "body.h"
#include "blackhole.h"
#include "config.h"
#include "graphics.h"

#include "font.h"

using namespace std;

struct Painter::color_list_t* Painter::s_clrlst = NULL;
const int Painter::s_num_clrlst = 255;

Painter::Painter(void) {
/*    float r, g, b;*/
    int i = 0;
    if (s_clrlst == NULL) {
        s_clrlst = new Painter::color_list_t[s_num_clrlst];
        srand(time(NULL));
        for (; i != s_num_clrlst; ++i) {
            s_clrlst[i].r = rand() % 255;
            s_clrlst[i].g = rand() % 255;
            s_clrlst[i].b = rand() % 255;
        }
/*
        for (r = 0.3f; r <= 1.0f; r += 0.1f) {
            for (g = 0.3f; g <= 1.0f; g += 0.1f) {
                for (b = 0.3f; b <= 1.0f; b += 0.1f) {
                    s_clrlst[i].r = r;
                    s_clrlst[i].g = g;
                    s_clrlst[i].b = b;
                    ++i;
                }
            }
            }*/
    }
    
}

void Painter::draw(Interface* interface) const {
    objs_t::const_iterator it = interface->cosmos_->objects().begin();

    /* comment next line to show trace */
    
    glClear(GL_COLOR_BUFFER_BIT/*|GL_DEPTH_BUFFER_BIT*/);

    interface->setNatureCoord();
    if (g_config.show_trace_) {
        restorepixels();
    }

    glPushMatrix();
    while (it != interface->cosmos_->objects().end()) {
        drawObject(interface, **it);
        ++it;
    }
    glPopMatrix();

    if (g_config.show_trace_) {
        storepixels();
    }

    interface->setScreenCoord();
    drawTips(interface);
    

    SDL_GL_SwapBuffers();
}

void Painter::drawObject(Interface* interface, const Object& obj) const {
    static int rngx = interface->cosmos_->rangeX(),
        rngy = interface->cosmos_->rangeY();
    static double x, y, radius;
    static int precision;
    static float r, g, b;

    x = obj.x() / rngx;
    y = obj.y() / rngy;

    if (g_config.display_mode_ == DISPLAY_MASS) {
        radius = sqrt(obj.mass()) / (rngx*rngy) + 0.003;
    } else if (g_config.display_mode_ == DISPLAY_RADIUS) {
        radius = obj.radius() / sqrt(rngx*rngy);
    } else {
        radius = 0.003;
    }
    precision = g_config.precision_;
    r = s_clrlst[obj.id()].r;
    g = s_clrlst[obj.id()].g;
    b = s_clrlst[obj.id()].b;

    drawCircle(x, y, radius, r, g, b, precision);

    if (g_config.show_mline_) {
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + obj.acceleration().x()/(rngx*0.03),
                   y + obj.acceleration().y()/(rngy*0.03));
        glEnd();
    }
}

void Painter::drawTips(Interface* interface) const {
    static unsigned long last_clock = SDL_GetTicks();
    static char strbuf[50] = {0};
    int x = 1;
    int y = 1;

    drawObjectList(interface);

    /* draw FPS */
    sprintf(strbuf, "\bwFPS: \br%4.1f", 1000.0/(SDL_GetTicks() - last_clock));
    drawtext(x, y, strbuf, 0,0,0,255);
    last_clock = SDL_GetTicks();

    /* draw display mode */
    sprintf(strbuf, "\bwMode: \br%s",
            g_config.display_mode_ == DISPLAY_MASS ? "M" : "R");
    drawtext(x += 60, y, strbuf, 0,0,0,255);

    /* draw trace/motion_line */
    sprintf(strbuf, "\bwTrace: %s",
            g_config.show_trace_ ? "\beY" : "\brN");
    drawtext(x += 50, y, strbuf, 0,0,0,255);
    sprintf(strbuf, "\bwMLine: %s",
            g_config.show_mline_ ? "\beY" : "\brN");
    drawtext(x += 50, y, strbuf, 0,0,0,255);


    /* draw MPS */
    sprintf(strbuf, "\bwMPS: \br%.1f", g_config.mps_);
    drawtext(x += 50, y, strbuf, 0,0,0,255);

    /* draw if pause */
    if (g_config.pause_) {
        drawtext(x += 50, y, "PAUSED", 0,255,255,255);
    }
}

void Painter::drawObjectList(Interface* interface) const {
    int x = 1, y = FONT_H+2, id;
    static objs_t::const_iterator it;
    static stringstream ss;
    
    it = interface->cosmos_->objects().begin();
    ss.str("");

    drawrect(x, y - 1, g_config.scrw_ - 1,
             (FONT_H+2)*interface->cosmos_->objects().size() - 2,
             127, 127, 127, 127);

    while (it != interface->cosmos_->objects().end()) {
        id = (*it)->id();
        x = drawtext(x, y, "# ",
                     s_clrlst[id].r, s_clrlst[id].g, s_clrlst[id].b, 255);
        ss << id << " ";
        ss << ((*it)->type() == T_BLACKHOLE ? "BLACKHOLE" :
               (*it)->type() == T_BODY ? "BODY" : "UNKOWN");
        ss << fixed << "(" << (*it)->x() << ", " << (*it)->y() << ")";
        ss << " - " << (*it)->mass() << " - ";
        ss << (*it)->acceleration().length();

        drawtext(x, y, ss.str().c_str(), 255, 255, 255, 127);

        ss.str("");
        x = 1;
        y += FONT_H + 2;
        ++it;
    }
}

