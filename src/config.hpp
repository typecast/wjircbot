/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <map>
#include <iostream>

namespace wjirc
{
  namespace Config
  {
    class Map
    {
      public:
        int load_config(const char* file_path);
        int set_value(std::string& key, std::string& value);
        std::string& get_value(std::string& key);
      private:
        std::map<std::string,std::string> cfg_map;
    };
  };
};

#endif /* __CONFIG_HPP__ */
