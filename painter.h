#ifndef __PAINTER_H__
#define __PAINTER_H__

class Interface;
class Body;
class BlackHole;
class Object;

class Painter {
    void draw(Interface* interface) const;

    /* a clever way to recognition different objects, use overload functions */
    void drawObject(Interface* interface, const Body& obj) const;
    void drawObject(Interface* interface, const BlackHole& obj) const;
//    void drawObject(const Object& obj) const;
};

#endif /* __PAINTER_H__ */
