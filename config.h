#ifndef __CONIFG_H__
#define __CONIFG_H__


#include <string>

class Config {
public:
    Config(void);
    Config(const std::string& config_file);

public:
    void loadConfig(const std::string& config_file);
    void loadDefault(void);



private:
    std::vector<std::vector<std::string>> token_;
    std::vector<Object*> objs_;
};


extern Config g_config;


#endif /* __CONIFG_H__ */
