#ifndef __PAINTER_H__
#define __PAINTER_H__

class Interface;
class Body;
class BlackHole;
class Object;

class Painter {
public:
    Painter(void);
    void draw(Interface* interface) const;

private:

    void drawObject(Interface* interface, const Object& obj) const;
    void drawTips(Interface* interface) const;

    void drawObjectList(Interface* interface) const;
    void drawFPS(void) const;

private:
    struct color_list_t {
        unsigned char r, g, b;
    };
    static struct color_list_t* s_clrlst;
    static const int s_num_clrlst;
};

#endif /* __PAINTER_H__ */
