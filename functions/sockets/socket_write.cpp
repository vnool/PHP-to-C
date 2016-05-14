php_var socket_write(php_var sock, php_var buf, int len = 0)
{
	php_socket *socket = (php_socket *) sock.res;
	if(len == 0)
		len = buf.container.length();
	#ifdef WIN32
	if(send(socket->sock, buf.container.c_str(), (int) len,0) < 0)
	#else
	if(write(socket->sock, buf.container.c_str(), (int) len) < 0)
	#endif
		return (php_var) false;
	return (php_var) true;
}