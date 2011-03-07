/*
 * Copyright (C) 2010  Kevin Morris
 * Closed-source license (self-signed)
 * wjircbot (A simple IRC bot)
*/

// Local headers
#include "tcp.hpp"

// CPP headers
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

// UNIX socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace wjirc;

// Default construction
Raw::Client::Client() { }

// Global deconstruction
Raw::Client::~Client()
{
	if(cl_sock != (-1))
		close(cl_sock);
}

int Raw::Client::cl_connect(const char* raddr, const char* rport)
{
	struct addrinfo hints, *res = NULL, *ptr = NULL;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	int err = getaddrinfo(raddr, rport, &hints, &res);
	
	if(err != 0)
		return -1;
	
	for(ptr = res; ptr != NULL; ptr = ptr->ai_next)
	{
		cl_sock = socket(ptr->ai_family, ptr->ai_socktype,
										ptr->ai_protocol);
		if(cl_sock == -1)
			return -2;
		if(connect(cl_sock, ptr->ai_addr, ptr->ai_addrlen) != 0)
			return -3;
	}
	
	freeaddrinfo(res);
	
	printf("Successfully connected!\n");
	
	return 0;
}

int Raw::Client::cl_close()
{
	if(cl_sock == -1)
		close(cl_sock);
	else
		return -1;
	return 0;
}

int Raw::Client::cl_cycle(const char* raddr, const char* rport,
													int timeout)
{
	if(cl_close() != 0)
		return -1;
	if(timeout >= 0)
		sleep(timeout);
	int err = cl_connect(raddr, rport);
	if(err != 0)
		return err;
	return 0;
}

int Raw::Client::cl_send(const char* lmsg)
{
	return send(cl_sock, lmsg, strlen(lmsg), 0);
}

int Raw::Client::cl_recv(char rmsg[512])
{
	char tmp[512];
	int b = recv(cl_sock, tmp, 511, 0);
	if(b <= 0)
		return -1;
	else
		tmp[b - 1] = 0;
	sprintf(rmsg, "%s", tmp);
	return 0;
}
			
