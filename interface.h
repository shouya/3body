#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/* #include <SDL/SDL.h> */

struct SDL_Surface;

class Cosmos;
class Painter;

struct SDL_keysym;

class Interface {
    friend class Painter;

public:
    void init();
    void mainLoop();
    void setCosmos(Cosmos* cosmos);
    void setPainter(Painter* painter);

    int dealHotkeys(SDL_keysym* key);

private:
    SDL_Surface* sfc_;
    Cosmos* cosmos_;
    Painter* painter_;
};


#endif /* __INTERFACE_H__ */
