/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

#ifndef __TCP_HPP__
#define __TCP_HPP__

namespace wjirc
{
  namespace Raw
  {
    class Client
    {
      public:
        int cl_connect(const char* raddr, const char* rport);
        int cl_close();
        int cl_cycle(const char* raddr, const char* rport, int timeout);
        int cl_send(const char* lmsg);
        int cl_recv(char rmsg[]);
      private:
        int cl_sock;
    };
    class Server
    {
      public:
        int sv_host(const char* laddr, const char* lport);
        int sv_close();
        int sv_cycle(const char* laddr, const char* rport, int timeout);
        int sv_recv(char rmsg[]);
        int sv_send(const char* lmsg);
      private:
        int sv_sock;
    };
  };
};

#endif /* __TCP_HPP__ */
