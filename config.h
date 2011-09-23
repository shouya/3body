#ifndef __CONIFG_H__
#define __CONIFG_H__


#include <string>
#include <map>
#include <vector>

class Object;

class Config {
public:
    Config(void);
    Config(const std::string& config_file);

public:
    void loadConfig(const std::string& config_file);
    void loadDefault(void);

    void parseConfig(void);

    double parseFloat(const std::string& str);
    long parseInteger(const std::string& str);


private:
    std::map<std::string, std::map<std::string, std::string> > token_;
    std::vector<Object*> objs_;
    float fps_;
    double gconst_;
    long xrng_, yrng_;
    int scrw_, scrh_;
    int show_trace_, show_mline_;
    double mass_scale_;
    
};


extern Config g_config;


#endif /* __CONIFG_H__ */
