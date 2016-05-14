php_var mysql_error(php_var mysql = global_mysql)
{
	php_var ret = mysql_error(mysql);
	return ret;
}
