#include <cmath>

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "painter.h"
#include "interface.h"
#include "mathlib.h"
#include "object.h"
#include "cosmos.h"
#include "body.h"

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    drawCircle(obj.x() / rngx, obj.y() / rngy, (obj.mass() / 1e10) + 0.003,
              s_clrlst[obj.id()].r, s_clrlst[obj.id()].g, s_clrlst[obj.id()].b,
               20);
    glBegin(GL_LINES);
    glVertex2f(obj.x()/rngx, obj.y()/rngy);
    glVertex2f(obj.x()/rngx+obj.acceleration().x()/(rngx*0.03),
               obj.y()/rngy+obj.acceleration().y()/(rngy*0.03));
    glEnd();
}
