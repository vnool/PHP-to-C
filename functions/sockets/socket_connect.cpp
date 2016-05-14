php_var socket_connect(php_var sock, php_var addr, php_var port = 0)
{
	in_addr tmp;
	php_socket *socket = (php_socket *) sock.res;
	int ret;
	hostent *host_entry;
	sockaddr_in	sin;
	sin.sin_family	= AF_INET;
	sin.sin_port	= htons((unsigned short int)(int)port);
	#ifdef WIN32
	if((tmp.s_addr=inet_addr(addr))==INADDR_NONE)
	#else
	if(inet_aton(addr, &tmp))
		sin.sin_addr.s_addr = tmp.s_addr;
	else
	#endif
	{
		if(!(host_entry = gethostbyname(addr)))
			return (php_var) false;
		if(host_entry->h_addrtype != AF_INET)
			return (php_var) false;
		memcpy(&(sin.sin_addr.s_addr), host_entry->h_addr_list[0], host_entry->h_length);
	}
	memset(&(sin.sin_zero), '\0', 8);
	ret = connect(socket->sock, (sockaddr *)&sin, sizeof(sockaddr));
	if(ret < 0)
		return (php_var) false;
	return (php_var) true;
}
