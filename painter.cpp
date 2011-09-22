#include <SDL/SDL.h>

#include "painter.h"
#include "interface.h"


static void drawCircle(float x, float y, double radius,
                       float r, float g, float b, int div_parts) {
    int i = 0;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(r, g, b, 1.0f);
    glVertex2f(x, y);
    for (; i != div_parts; ++i) {
        glVertex2f(x + r*cos(2*PI/div_parts * i),
                   y + r*sin(2*PI/div_parts * i));
    }
    glEnd();
}

void Painter::draw(Interface* interface) const {
    objs_t it = interface->cosmos_->objects().begin();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    while (it != interface->cosmos_->objects().end()) {
        drawObject(interface, *it);
        ++it;
    }
    SDL_GL_SwapBuffers();
}

void Painter::drawObject(Interface* interface, const Body& obj) const {
    SDL_Surface* sfc = interface->sfc_;
    drawCircle(obj.x(), obj.y(), obj.mass(), 1, 1, 1, 20);
}
void Painter::drawObject(Interface* interface, const BlackHole& obj) const {
    SDL_Surface* sfc = interface->sfc_;
    drawCircle(obj.x(), obj.y(), obj.mass(), 1, 1, 1, 20);
}
