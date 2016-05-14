php_var mysql_fetch_array(php_var result, php_var result_type = MYSQL_BOTH)
{
	php_var ret;
	unsigned int num_fields;
	MYSQL_ROW row;
	MYSQL_FIELD* fields;
	if(row = mysql_fetch_row((MYSQL_RES*)result.res))
	{
		ret = array();
		num_fields = mysql_num_fields((MYSQL_RES*)result.res);
        fields = mysql_fetch_fields((MYSQL_RES*)result.res);
		int i;
		for(i = 0; i < num_fields; ++i)
		{
			if(result_type == MYSQL_NUM || result_type == MYSQL_BOTH)
				ret[i] = row[i];
			if(result_type == MYSQL_ASSOC || result_type == MYSQL_BOTH)
				ret[fields[i].name] = row[i];
		}
		free(fields);
		return ret;
	}
	else
		return((php_var)false);
}
