php_var mysql_fetch_row(php_var result)
{
	php_var ret;
	unsigned int num_fields;
	MYSQL_ROW row;
	if(row = mysql_fetch_row((MYSQL_RES*)result.res))
	{
		ret = array();
		num_fields = mysql_num_fields((MYSQL_RES*)result.res);
		int i;
		for(i = 0; i < num_fields; ++i)
			ret[i] = row[i];
		return ret;
	}
	else
		return((php_var)false);
}
