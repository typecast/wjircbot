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
				Client();
				~Client();
				int cl_connect(const char* raddr, const char* rport);
				int cl_close();
				int cl_cycle(const char* raddr, const char* rport, int timeout);
				int cl_send(const char* lmsg);
				int cl_recv(char rmsg[]);
			protected:
				int cl_sock;
		};
	};
};

#endif /* __TCP_HPP__ */
