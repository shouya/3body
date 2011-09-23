#include <cmath>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "painter.h"
#include "interface.h"
#include "mathlib.h"
#include "object.h"
#include "cosmos.h"
#include "body.h"
#include "config.h"

struct Painter::color_list_t* Painter::s_clrlst = NULL;

Painter::Painter(void) {
    float r, g, b;
    int i = 0;
    if (s_clrlst == NULL) {
        s_clrlst = new Painter::color_list_t[512];
        for (r = 0.3f; r <= 1.0f; r += 0.1f) {
            for (g = 0.3f; g <= 1.0f; g += 0.1f) {
                for (b = 0.3f; b <= 1.0f; b += 0.1f) {
                    s_clrlst[i].r = r;
                    s_clrlst[i].g = g;
                    s_clrlst[i].b = b;
                    ++i;
                }
            }
        }
    }
    
}

void Painter::draw(Interface* interface) const {
    objs_t::const_iterator it = interface->cosmos_->objects().begin();

    /* comment next line to show trace */
    
    if (!g_config.show_trace_) {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    glPushMatrix();
    while (it != interface->cosmos_->objects().end()) {
        drawObject(interface, **it);
        ++it;
    }
    glPopMatrix();

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
