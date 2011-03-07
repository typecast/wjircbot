/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

#ifndef __IRC_HPP__
#define __IRC_HPP__

#include "tcp.hpp"

namespace wjirc
{
	namespace IRC
	{
		class Client
		{
			public:
				Client(const char* raddr, const char* rport, const char* laddr,
							const char* lport);
				Client();
				~Client();
				int irc_start(const char *raddr, const char *rport);
				int irc_register(const char* nick, const char* altnick,
												const char* user, const char* realname,
												const char* vhost_addr, const char *vhost_port);
				int irc_autojoin(const char* channels);
				int irc_pingback(const char* serv_ping);
				int irc_send(const char* command, const char* cmd_args);
				int irc_recv(char msgbin[512]);
			private:
				Raw::Client raw_client;
		};
		class Parser
		{
			public:
				Parser(IRC::Client& irc_cl_in);
				~Parser();
				int irc_parse(char rawmsg[512]);
				char irc_src[56];
				char irc_cmd[56];
				char irc_arg[56];
			private:
				Client irc_client;
		};
		class Commands
		{
			public:
				Commands(IRC::Client& irc_cl_in);
				~Commands();
			private:
				Client irc_client;
		};
	};
};

#endif /* __IRC_HPP__ */
