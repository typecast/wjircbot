/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

// Local headers // includes <map> and <iostream>
#include "config.hpp"
#include "tcp.hpp"
#include "irc.hpp"
#include "wjircbot.hpp"

// CPP headers
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace wjirc;
using namespace std;

const std::string wjirc_version = std::string(Version::major) + "." +
        std::string(Version::minor) + "." + std::string(Version::patch);
				
int main(int argc, char *argv[])
{
  using namespace Colors;
  printf("wjircbot v%s by Kevin Morris\n\n", wjirc_version.c_str());
  IRC::Client icl;
  IRC::Parser iparse(icl);
  IRC::Commands icmd(icl);
  
  const char* home = getenv("HOME");
  string shome = string(home) + "/.wjirc.conf";
  Config::Map cfg;
  cfg.load_config(shome.c_str());
  
  cout << CY << "Processing configuration file..." << CN << "\n\n";
  
  const int amt = 10;
  string key[amt] = {"irc_addr", "irc_port", "vhost_addr", "vhost_port",
                    "irc_nick", "irc_altnick", "irc_user", "irc_real",
                    "irc_client", "autojoin"};
										 
  for(int i = 0; i < amt; i++)
  {
    if(cfg.get_value(key[i]).empty())
    {
      cout << CW << key[i] << ": " << CR
            << "Missing configuration! Check your config! (Quitting)"
            << CN << "\n\n";
      return -1;
    }
    else
    {
      cout << CW << key[i] << ": " << CG << cfg.get_value(key[i])
            << " (OK!)" << CN << endl;
    }
  }
  cout << "\n" << CG << "Configuration file OK! Moving on..." << CN
        << "\n\n";
	
  cout << CY << "Connecting to " << CW << cfg.get_value(key[0])
        << CY << ":" << CW << cfg.get_value(key[1]) << CN << "\n\n";
	
  if(icl.irc_start(cfg.get_value(key[0]).c_str(),
                  cfg.get_value(key[1]).c_str()) != 0)
  {
    cout << CR << "Failed to connect to " << CW << cfg.get_value(key[0])
          << CR << ":" << CW << cfg.get_value(key[1]) << CN << "\n\n";
    return -2;
  }
  else
  {
    cout << CG << "Successfully connected to " << CW
         << cfg.get_value(key[0]) << CG << ":" << CW
         << cfg.get_value(key[1]) << CG << "!" << CN << "\n\n";
  }
	
  if(icl.irc_register(cfg.get_value(key[4]).c_str(),
                    cfg.get_value(key[5]).c_str(),
                    cfg.get_value(key[6]).c_str(),
                    cfg.get_value(key[7]).c_str(),
                    cfg.get_value(key[2]).c_str(),
                    cfg.get_value(key[3]).c_str()) != 0)
  {
    cout << CG << "CLIENT -> " << CR << "Authentication failed!" << CN
          << "\n";
    return -3;
  }
  else
  {
    cout << CG << "CLIENT -> Successfully authenticated to the server."
          << CN << "\n";
  }
	
  cout << CG << "CLIENT -> Sleeping for a second before channel joins"
        << CN << "\n";
  
  sleep(1);
  
  if(icl.irc_autojoin(cfg.get_value(key[9]).c_str()) != 0)
  {
    cout << CG << "CLIENT -> " << CR << "Channel autojoin failed!" << CN
          << "\n";
    return -4;
  }
  else
  {
    cout << CG << "CLIENT -> Sent channel autojoin commands." << CN
          << "\n";
  }

  char msgbin[512];
  while(icl.irc_recv(msgbin) == 0)
  {
    if(msgbin[0] == 'P')
    {
      cout << CG << "CLIENT -> Checking PING request." << CN << "\n";
      if(icl.irc_pingback(msgbin) != 0)
      {
        cout << CG << "CLIENT -> " << CR << "Pingback failed!"
              << " Quitting now..." << CN << "\n";
        return -5;
      }
      else
      {
        cout << CG << "CLIENT -> Successfully pinged back!" << CN
              << "\n";
        continue;
      }
    }
    cout << CW << msgbin << CN << endl;
  }

  return 0;
}
