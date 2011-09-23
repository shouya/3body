#include <cstdlib>
#include <ctime>

#include "3body.h"

#include "interface.h"
#include "cosmos.h"
#include "painter.h"
#include "body.h"
#include "blackhole.h"

int main(int argc, char** argv) {
    Interface* ui;
    Cosmos* cosmos;

    ui = new Interface;
    ui->init();

    cosmos = new Cosmos();

    srand(time(NULL));
    cosmos->addObject(new BlackHole(rand()%100-50, rand()%100-50,
                                    3e8));
    for (int i = 0; i != atol(argv[1]); ++i) {
        cosmos->addObject(new Body(rand()%1000-500, rand()%1000-500,
                                   rand()%100 * 1e6+1,
                                   Vector(rand()%2-1,rand()%2-1)
                              ));
    }

    ui->setCosmos(cosmos);
    ui->setPainter(new Painter());

    ui->mainLoop();

    exit(0);
}
