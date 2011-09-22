#include <cstdlib>

#include "3body.h"

#include "interface.h"
#include "cosmos.h"
#include "painter.h"
#include "body.h"

int main(int argc, char** argv) {
    Interface* ui;
    Cosmos* cosmos;

    ui = new Interface;
    ui->init();

    cosmos = new Cosmos;
    cosmos->addObject(Body(0, 0, 50));
    cosmos->addObject(Body(0, 100, 50));

    ui->setCosmos(cosmos);
    ui->setPainter(new Painter);

    ui->mainLoop();

    exit(0);
}
