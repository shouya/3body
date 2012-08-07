#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <GL/gl.h>

#include "graphics.h"

#include "config.h"

#define INCLUDE_FONTDATA
#include "font.h"
#undef INCLUDE_FONTDATA





void drawpixel(int x, int y, int r, int g, int b, int a) {
    if (x < 0 || y < 0 || x >= g_config.scrw_ || y >= g_config.scrh_) {
        return;
    }

    glBegin(GL_POINTS);
    glColor4ub(r, g, b, a);
    glVertex2i(x, y);
    glEnd();
}

int drawchar(int x, int y, int c, int r, int g, int b, int a) {
    static GLint* vertex_ptr = new GLint[FONT_H*FONT_H*2];
    static GLubyte* color_ptr = new GLubyte[FONT_H*FONT_H*4];
    int i, j, w, bn = 0, ba = 0, ii = 0, bc = 0;
    char* rp = font_data + font_ptrs[c];

    w = *(rp++);
    if (x < 0 || y < 0 || x >= g_config.scrw_ || y >= g_config.scrh_) {
        return (x + w);
    }

    bc = w * FONT_H;

    for (j = 0; j != FONT_H; ++j)
        for (i = 0; i != w; ++i) {
            if (!bn) {
                ba = *(rp++);
                bn = 8;
            }
            vertex_ptr[2*ii] = x+i;
            vertex_ptr[2*ii+1] = y+j;
            color_ptr[4*ii] = r;
            color_ptr[4*ii+1] = g;
            color_ptr[4*ii+2] = b;
            color_ptr[4*ii+3] = ((ba&3)*a)/3;
            ba >>= 2;
            bn -= 2;
            ++ii;
        }
    glVertexPointer(2, GL_INT, 0, vertex_ptr);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, color_ptr);
    glDrawArrays(GL_POINTS, 0, bc);
/*    for (j = 0; j < FONT_H; ++j) {
        for (i = 0; i < w; ++i) {
            if (!bn) {
                ba = *(rp++);
                bn = 8;
            }
            drawpixel(x+i, y+j, r, g, b, ((ba&3)*a)/3);
            ba >>= 2;
            bn -= 2;
        }
        }*/

    return (x + w);
}

int drawtext(int x, int y, const char* s, int r, int g, int b, int a) {
    int sx = x;
    for (; *s; s++) {
        if (*s == '\n') {
            x = sx;
            y += FONT_H+2;
        } else if (*s == '\b') {
            switch (s[1]) {
            case 'w':
                r = g = b = 255;
                break;
            case 'g':
                r = g = b = 192;
                break;
            case 'o':
                r = 255;
                g = 216;
                b = 32;
                break;
            case 'r':
                r = 255;
                g = b = 0;
                break;
            case 'e':
                g = 255;
                r = b = 0;
                break;
            case 'b':
                r = g = 0;
                b = 255;
                break;
            case 't':
                b = 255;
                g = 170;
                r = 32;
                break;
            } /* switch */
            s++;
        } else {
            x = drawchar(x, y, *s, r, g, b, a);
        } /* switch (*s) [\n,\b,*] */
    } /* for each char */
    return x;
}

int drawtext_outline(int x, int y, const char* s, int r, \
                     int g, int b, int a, int _or, int og, int ob, int oa) {
	drawtext(x-1, y-1, s, _or, og, ob, oa);
	drawtext(x+1, y+1, s, _or, og, ob, oa);

	drawtext(x-1, y+1, s, _or, og, ob, oa);
	drawtext(x+1, y-1, s, _or, og, ob, oa);

	return drawtext(x, y, s, r, g, b, a);
}

void drawrect(int x, int y, int w, int h, int r, int g, int b, int a) {
    glBegin(GL_LINE_LOOP);
    glColor4ub(r, g, b, a);
    glVertex2i(x, y);
    glVertex2i(x+w, y);
    glVertex2i(x+w, y+h);
    glVertex2i(x, y+h);
    glEnd();
}

static unsigned char* pixels = NULL;

void resetpixels(void) {
    if (pixels) {
        memset(pixels, 0, g_config.scrw_ * g_config.scrh_ * 4 * sizeof(char));
    }
}

void storepixels(void) {
    if (!pixels) {
        pixels = (unsigned char*)malloc(g_config.scrw_ * g_config.scrh_ * 4
                                        * sizeof(unsigned char));
    }
    glReadPixels(0, 0, g_config.scrw_, g_config.scrh_,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}

void restorepixels(void) {
    if (!pixels) {
        return;
    }
    glDrawPixels(g_config.scrw_, g_config.scrh_,
                 GL_RGBA, GL_UNSIGNED_BYTE, pixels);
}
