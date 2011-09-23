#include "config.h"

using namespace std;

Config g_config;


Config::Config(void) {
}

Config::Config(const string& config_file) {
    
}

void Config::loadConfig(const string& config_file) {
    ifstream fs(config_file.c_str());
    string line;

    loadDefault();

    if (!fs.is_open()) {
        return;
    }

    for (;;) {
        try {
            getline(fs, line);
        } except (...) {
            break;
        }
        line
    }
}
