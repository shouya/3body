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
    int i, j, w, bn = 0, ba = 0;
    char* rp = font_data + font_ptrs[c];
    w = *(rp++);
    for (j = 0; j < FONT_H; ++j) {
        for (i = 0; i < w; i++) {
            if (!bn) {
                ba = *(rp++);
                bn = 8;
            }
            drawpixel(x+i, y+j, r, g, b, ((ba&3)*a)/3);
            ba >>= 2;
            bn -= 2;
        }
    }
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
