#include <cstdlib>
#include <cstring>


#include <fstream>

#include "config.h"
#include "object.h"
#include "body.h"
#include "blackhole.h"
#include "vector.h"

using namespace std;

Config g_config;

/*
    float fps_;
    double gconst_;
    long xrng_, yrng_;
    int scrw_, scrh_;
    int show_trace_, show_mline_;
    
 */

Config::Config(void) : fps_(30), gconst_(6.67e-7),
                       xrng_(1e3), yrng_(1e3), scrw_(600), scrh_(600),
                       show_trace_(0), show_mline_(1),
                       mass_scale_(1e10) {
}

Config::Config(const string& config_file) :
    fps_(30), gconst_(6.67e-7),
    xrng_(1e3), yrng_(1e3), scrw_(600), scrh_(600),
    show_trace_(0), show_mline_(1),
    mass_scale_(1e10)
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
        if (line[0] == '[' && line[line.length()-1] == ']') {
            if (grp_name != "") {
                token_[grp_name] = tokens;
            }
            grp_name = line.substr(1, line.length() - 2);
            tokens.clear();
        }
        
        eqs_pos = line.find('=');
        if (eqs_pos == string::npos) {
            continue;
        }
        tokens[line.substr(0, eqs_pos)] = line.substr(eqs_pos+1);
    }

    fs.close();
}


void Config::parseConfig(void) {
    map<string, map<string, string> >::iterator grp_it = token_.begin();
    map<string, string>::iterator tok_it;
    
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
                } else if (key == "GRAVITATION_CONSTANT") {
                    gconst_ = atof(val.c_str());
                } else {
                    printf("what the hell it is: [%s]->[%s]\n",
                           key.c_str(), val.c_str());
                } /* if (key == ***) */
            } /* for (tokit++) */
        } /* if (group name == "CONFIG") */
        
        if (grp_it->first.substr(0,3) == "OBJ") {
            const string& type = grp_it->second["TYPE"];
            int n = parseInteger(grp_it->second["N"]);
            (n <= 0) && (n = 1);

            if (type == "BODY") {
                while (n--) {
                    objs_.push_back(
                        new Body(
                            parseFloat(grp_it->second["X"]),
                            parseFloat(grp_it->second["Y"]), 
                            parseFloat(grp_it->second["MASS"]),
                            Vector(parseFloat(grp_it->second["AX"]),
                                   parseFloat(grp_it->second["AX"]))));
                } /* while (n--) */
            } else if (type == "BLACKHOLE") {
                objs_.push_back(
                        new BlackHole(
                            parseFloat(grp_it->second["X"]),
                            parseFloat(grp_it->second["Y"]), 
                            parseFloat(grp_it->second["MASS"])));
            } /* if (type == ***) */
        } else {
            /* pass */

        }/* if (group name == "OBJ*") */
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
        return atol(str.c_str());
    }
    ldel = str.find('(') + 1;
    rdel = str.find(',');
    lbound = atof(str.substr(ldel, rdel-ldel).c_str());
    ldel = rdel+1;
    rdel = str.find(')');
    ubound = atof(str.substr(ldel, rdel-ldel).c_str());
    
    return (rand()*rand()+rand())%1000000/1000000.0 * (ubound-lbound) +lbound;
}
