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

private:
    struct color_list_t {
        float r, g, b;
    };
    static struct color_list_t* s_clrlst;
};

#endif /* __PAINTER_H__ */
