/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

#include "config.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace wjirc;

int Config::Map::load_config(const char* file_path)
{
  std::ifstream file_in(file_path, std::ios::in);
  
  if(!file_in.is_open())
    return -1;

  while(!file_in.eof())
  {
    char bin[512];
    file_in.getline(bin, 511, '\n');
    
    if(bin[0] == '#')
      continue;
      
    std::string sbin(bin);
    size_t pos = sbin.find("=");
    
    if(pos == std::string::npos)
      continue;
      
    std::string key = sbin.substr(0, pos);
    
    std::string value = sbin.substr(++pos);
    
    set_value(key, value);
  }
  
  file_in.close();
  
  return 0;
}

int Config::Map::set_value(std::string& key, std::string& value)
{
  cfg_map[key] = value;
  return 0;
}

std::string& Config::Map::get_value(std::string& key)
{
  return cfg_map[key];
}
