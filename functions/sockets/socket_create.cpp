typedef struct {
	int		sock;
	int		type;
	int		error;
} php_socket;

php_var socket_create(php_var domain, php_var type, php_var protocol)
{
	static php_socket sock;
	#ifdef WIN32
	static int done_start=0;
	if(done_start==0) {
		WORD wVersionRequested = MAKEWORD(2, 0);
		WSADATA wsaData;
		if (WSAStartup(wVersionRequested, &wsaData) != 0) {
			return (php_var)false;
		}
		done_start=1;
	}
	#endif
	sock.sock = socket((long) domain, (long) type, (long) protocol);
	#ifdef WIN32
	if(sock.sock == INVALID_SOCKET)
	#else
	if(sock.sock < 0)
	#endif
		return (php_var) false;
	sock.type = type;
	php_var ret;
	ret.res = (void *) &sock;
	return ret;
}