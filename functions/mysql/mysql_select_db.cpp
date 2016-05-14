php_var mysql_select_db(php_var db, php_var mysql = global_mysql)
{
	if(mysql_select_db((MYSQL*)mysql.res, db.container.c_str()) == 0)
		return true;
	return false;
}
		
