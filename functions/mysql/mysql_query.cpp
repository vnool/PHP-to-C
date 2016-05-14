php_var mysql_query(php_var query, php_var mysql = global_mysql)
{
	MYSQL_RES* result = NULL;
	php_var ret;
	if(mysql_real_query((MYSQL*)mysql.res, query.container.c_str(),query.container.length()) != 0)
	{
		return (php_var) false;
	}
	else
	{
		result = mysql_store_result((MYSQL*) (mysql.res));
		if(result)
		{
			ret.type = PHP_RESOURCE;
			ret.res = (void*)result;
			return ret;
		}
		else
		{
			if(mysql_field_count((MYSQL *) mysql.res) == 0)
				return((php_var)true);
			else
				return((php_var)false);
		}
	}
}
