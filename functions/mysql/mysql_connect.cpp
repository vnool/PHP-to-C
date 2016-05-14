php_var mysql_connect(php_var host = "localhost:3306", php_var user = "", php_var passwd = "")
{
	MYSQL* mysql;
	mysql_init(mysql);
	unsigned int port = 3306;
	if(!mysql_real_connect(mysql, host, user.container.c_str(), passwd.container.c_str(), NULL, port, host_ext[1].container.c_str(), 0))
	{
		//handle errors
	}
	php_var ret;
	ret.res = (void*)mysql;
	ret.type = PHP_RESOURCE;
	global_mysql.res = (void*)mysql;
	global_mysql.type = PHP_RESOURCE;
	return ret;
}
