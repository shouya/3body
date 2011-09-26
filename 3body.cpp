#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "3body.h"

#include "interface.h"
#include "cosmos.h"
#include "painter.h"
#include "body.h"
#include "blackhole.h"
#include "config.h"

int main(int argc, char** argv) {
    Interface* ui;
    Cosmos* cosmos;

    g_config.loadConfig(argv[1] ? argv[1] : "3body.conf");
    g_config.parseConfig();

    printf("config arguments:\n");
    printf("fps: %f\n", g_config.mps_);
    printf("show trace: %s\n", g_config.show_trace_ ? "yes" : "no");
    printf("show motion line: %s\n", g_config.show_mline_ ? "yes" : "no");
    printf("full screen: %s\n", g_config.fulscr_ ? "yes" : "no");
    printf("cosmos x-range: %ld\n", g_config.xrng_);
    printf("cosmos y-range: %ld\n", g_config.yrng_);
    printf("screen width: %d\n", g_config.scrw_);
    printf("screen height: %d\n", g_config.scrh_);
    printf("gravitational contant: %e\n", g_config.gconst_);


    ui = new Interface;
    ui->init();


    cosmos = new Cosmos();
    cosmos->loadFromConfig();
    
    ui->setCosmos(cosmos);
    ui->setPainter(new Painter());

    printf("Initialize complete.\n\n");

    ui->mainLoop();

    exit(0);
}
