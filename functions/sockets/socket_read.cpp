#define PHP_BINARY_READ 0
#define PHP_NORMAL_READ 1
php_var socket_read(php_var sock, php_var len, php_var type = PHP_BINARY_READ)
{
	php_socket *socket = (php_socket *) sock.res;
	int ret;
	char *buf;
	buf = (char*)malloc((int)len+1);
	memset(buf,0,(int)len+1);
	ret = recv(socket->sock, buf, (int)len, 0);
	if(ret < 0)
		return (php_var) false;
	php_var retu = buf;
	free(buf);
	return retu;
}