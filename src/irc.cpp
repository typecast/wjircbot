/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

#include "config.hpp"
#include "tcp.hpp"
#include "irc.hpp"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

using namespace wjirc;

IRC::Client::Client(const char* raddr, const char* rport,
										const char* laddr, const char* lport)
{
  raw_client = Raw::Client();
  if(irc_start(raddr, laddr) != 0)
    throw std::runtime_error("irc_start failed!");
}

IRC::Client::Client()
{
  raw_client = Raw::Client();
}

IRC::Client::~Client()
{
  raw_client.cl_close();
}

int IRC::Client::irc_start(const char *raddr, const char *rport)
{
  if(raw_client.cl_connect(raddr, rport) != 0)
    return -1;
  return 0;
}

int IRC::Client::irc_register(const char* nick, const char* altnick,
                        const char* user, const char* realname,
                        const char* vhost_addr, const char *vhost_port)
{
  std::string nickstr = "NICK " + std::string(nick) + " "
                      + std::string(altnick) + "\n";
	
  int b = raw_client.cl_send(nickstr.c_str());
  if(b <= 0)
    return -1;
		
  std::string userstr = "USER " + std::string(user) + " "
                      + std::string(vhost_addr) + " "
                      + std::string(vhost_port) + " :"
                      + std::string(realname) + " \n";
	
  b = raw_client.cl_send(userstr.c_str());
  if(b <= 0)
    return -1;
	
  return 0;
}

int IRC::Client::irc_autojoin(const char* channels)
{
  std::string joinstr = "JOIN :" + std::string(channels) + "\n";
  int b = raw_client.cl_send(joinstr.c_str());
  if(b <= 0)
    return -1;
  return 0;
}

int IRC::Client::irc_pingback(const char* serv_ping)
{
  std::string sping(serv_ping);
  size_t pos = 5;
  std::string resp = sping.substr(0, pos);
  if(resp == "PING ")
  {
    resp = sping.substr(pos+1);
    std::string pongstr = "PONG " + resp;
    if(raw_client.cl_send(pongstr.c_str()) <= 0)
      return -1;
  }
  else
  {
    return -2;
  }
  return 0;
}

int IRC::Client::irc_send(const char* command, const char* cmd_args)
{
  std::string to_send = std::string(command) + " :"
                      + std::string(cmd_args) + "\n";
  if(raw_client.cl_send(to_send.c_str()) <= 0)
    return -1;
  return 0;
}

int IRC::Client::irc_recv(char msgbin[512])
{
  char tmp[512];
  if(raw_client.cl_recv(tmp) != 0)
    return -1;
  sprintf(msgbin, "%s", tmp);
  return 0;
}

IRC::Parser::Parser(IRC::Client& irc_cl_in)
{
  irc_client = irc_cl_in;
}

IRC::Parser::~Parser()
{
}

int IRC::Parser::irc_parse(char rawmsg[512])
{
  return 0;
}

IRC::Commands::Commands(IRC::Client& irc_cl_in)
{
  irc_client = irc_cl_in;
}

IRC::Commands::~Commands()
{
}
				
