#ifndef __CONIFG_H__
#define __CONIFG_H__


#include <string>
#include <map>
#include <vector>

class Object;

enum {
    DISPLAY_RADIUS = 0,
    DISPLAY_MASS = 1
};

class Config {
public:
    Config(void);
    explicit Config(const std::string& config_file);

public:
    void loadConfig(const std::string& config_file);
    void loadDefault(void);

    void parseConfig(void);

    double parseFloat(const std::string& str);
    long parseInteger(const std::string& str);

public:
    static Config s_config;

private:
    void init(void);

public:
    std::map<std::string, std::map<std::string, std::string> > token_;
    std::vector<Object*> objs_;

    float mps_;
    double gconst_;
    long xrng_, yrng_;
    int scrw_, scrh_;
    int show_trace_, show_mline_, fulscr_;
    int merge_mode_;
    int display_mode_;
    int precision_;

    int pause_;
};

extern Config& g_config;



#endif /* __CONIFG_H__ */
