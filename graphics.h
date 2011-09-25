#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#define PIXPACK(x) ((((x)>>8)&0x0000FF00)|(((x)<<8)&0x00FF0000)|(((x)<<24)&0xFF000000))
#define PIXRGB(r,g,b) (((r)<<24)|((g)<<16)|((b)<<8))
#define PIXR(x) (((x)>>24)&0xFF)
#define PIXG(x) (((x)>>16)&0xFF)
#define PIXB(x) (((x)>>8))

typedef unsigned int pixel;


void drawpixel(int x, int y, int r, int g, int b, int a);
int drawchar(int x, int y, int c, int r, int g, int b, int a);
int drawtext(int x, int y, const char* s, int r, int g, int b, int a);
int drawtext_outline(int x, int y, const char* s, int r, \
                     int g, int b, int a, int _or, int og, int ob, int oa);
void drawrect(int x, int y, int w, int h, int r, int g, int b, int a);

#endif /* __GRAPHICS_H__ */
