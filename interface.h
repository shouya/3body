#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/* #include <SDL/SDL.h> */

struct SDL_Surface;

class Cosmos;
class Painter;

class Interface {
    friend class Painter;

public:
    void init();
    void mainLoop();
    void setCosmos(Cosmos* cosmos);
    void setPainter(Painter* painter);

private:
    SDL_Surface* sfc_;
    Cosmos* cosmos_;
    Painter* painter_;
    float fps_;

private:
    enum {
        WIDTH = 600,
        HEIGHT = 600
    };

};


#endif /* __INTERFACE_H__ */
