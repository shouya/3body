#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <fstream>

#include "config.h"
#include "object.h"
#include "body.h"
#include "blackhole.h"
#include "vector.h"
#include "cosmos.h"

using namespace std;

Config Config::s_config;
Config& g_config = Config::s_config;


Config::Config(void) : fps_(30), gconst_(6.67e-7),
                       xrng_(1e3), yrng_(1e3), scrw_(600), scrh_(600),
                       show_trace_(0), show_mline_(1), fulscr_(0),
                       merge_mode_(1),
                       display_mode_(DISPLAY_MASS),
                       precision_(20)
{
}

Config::Config(const string& config_file) :
    fps_(30), gconst_(6.67e-7),
    xrng_(1e3), yrng_(1e3), scrw_(600), scrh_(600),
    show_trace_(0), show_mline_(1), fulscr_(0),
    merge_mode_(1),
    display_mode_(DISPLAY_MASS),
    precision_(20)
{
    loadConfig(config_file);
    parseConfig();
}

void Config::loadConfig(const string& config_file) {
    ifstream fs(config_file.c_str());
    string line, grp_name, tok_name;
    map<string, string> tokens;
    size_t eqs_pos;

    if (!fs.is_open()) {
        return;
    }
    while (getline(fs, line)) {
        if (line[0] == '#') { /* comment line */
            continue;
        }
        if (line[0] == '[' && line[line.length()-1] == ']') {
            if (grp_name != "") {
                token_[grp_name] = tokens;
            }
            grp_name = line.substr(1, line.length() - 2);
            tokens.clear();
            continue;
        }
        
        eqs_pos = line.find('=');
        if (eqs_pos == string::npos) {
            continue;
        }
        tokens[line.substr(0, eqs_pos)] = line.substr(eqs_pos+1);
    }

    token_[grp_name] = tokens;
    fs.close();
}


void Config::parseConfig(void) {
    map<string, map<string, string> >::iterator grp_it = token_.begin();
    map<string, string>::iterator tok_it;
    
    srand(time(NULL));
    for (; grp_it != token_.end(); ++grp_it) {
        tok_it = grp_it->second.begin();
        if (grp_it->first == "CONFIG") {
            for (; tok_it != grp_it->second.end(); ++tok_it) {
                const string& key = tok_it->first;
                const string& val = tok_it->second;
                if (key == "FPS") {
                    fps_ = atof(val.c_str());
                } else if (key == "SHOW_TRACE") {
                    show_trace_ = atol(val.c_str());
                } else if (key == "SHOW_MOTION_LINE") {
                    show_mline_ = atol(val.c_str());
                } else if (key == "RANGE_X") {
                    xrng_ = atol(val.c_str());
                } else if (key == "RANGE_Y") {
                    yrng_ = atol(val.c_str());
                } else if (key == "SCREEN_WIDTH") {
                    scrw_ = atol(val.c_str());
                } else if (key == "SCREEN_HEIGHT") {
                    scrh_ = atol(val.c_str());  
                } else if (key == "G_CONSTANT") {
                    gconst_ = atof(val.c_str()); 
                } else if (key == "FULLSCREEN") {
                    fulscr_ = atol(val.c_str());  
                } else if (key == "MERGE_MODE") {
                    merge_mode_ = atol(val.c_str());
                } else if (key == "DISPLAY_MODE") {
                    (val == "MASS")   && (display_mode_ = DISPLAY_MASS);
                    (val == "RADIUS") && (display_mode_ = DISPLAY_RADIUS);
                } else if (key == "PRECISION") {
                    precision_ = atol(val.c_str());
                } else {
                    printf("unkown config [%s] -> [%s]\n",
                           key.c_str(), val.c_str());
                } /* if (key == ***) */
            } /* for (tokit++) */
        } /* if (group name == "CONFIG") */
        
        if (grp_it->first.substr(0,3) == "OBJ") {
            const string& type = grp_it->second["TYPE"];
            int n = parseInteger(grp_it->second["N"]);
            int type_id;

            (n <= 0) && (n = 1);

            if (type == "BODY") {
                type_id = T_BODY;
            } else if (type == "BLACKHOLE") {
                type_id = T_BLACKHOLE;
            } else {
                type_id = 0; /* what is the type? */
                fprintf(stderr, "error: plz special type of group %s\n",
                        type.c_str());
                return;
            }

            printf("load object: [%s](%s)\n",
                   grp_it->first.c_str(), type.c_str());

            while (n--) {
                objs_.push_back(
                    Cosmos::createObject(
                        type_id,
                        parseFloat(grp_it->second["X"]),
                        parseFloat(grp_it->second["Y"]), 
                        parseFloat(grp_it->second["MASS"]),
                        parseFloat(grp_it->second["RADIUS"]),
                        parseFloat(grp_it->second["AX"]),
                        parseFloat(grp_it->second["AX"]))
                    );
            } /* while n-- */
        } /* if (group name == "OBJ*") */
    } /* for each group */
}


long Config::parseInteger(const string& str) {
    double lbound, ubound;
    int ldel, rdel;

    if (str.empty()) {
        return 0;
    }
    if (str[0] != 'R') {
        return atol(str.c_str());
    }
    ldel = str.find('(') + 1;
    rdel = str.find(',');
    lbound = atof(str.substr(ldel, rdel-ldel).c_str());
    ldel = rdel+1;
    rdel = str.find(')');
    ubound = atof(str.substr(ldel, rdel-ldel).c_str());
    
    return rand()%((int)(ubound-lbound)) + lbound;
}

double Config::parseFloat(const string& str) {
    double lbound, ubound;
    int ldel, rdel;

    if (str.empty()) {
        return 0;
    }
    if (str[0] != 'R') {
        return atof(str.c_str());
    }
    ldel = str.find('(') + 1;
    rdel = str.find(',');
    lbound = atof(str.substr(ldel, rdel-ldel).c_str());
    ldel = rdel+1;
    rdel = str.find(')');
    ubound = atof(str.substr(ldel, rdel-ldel).c_str());
    
    return (rand()%1000000/1000000.0) * (ubound-lbound) +lbound;
}
