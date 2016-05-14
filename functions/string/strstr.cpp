php_var strstr(php_var haystack, php_var needle)
{
	int pos = 0;
	php_var ret;
	if((pos = haystack.container.find(needle.container)) != string::npos)
	{
		ret.type = PHP_STRING;
		ret.container = haystack.container.substr(pos, haystack.container.length() - pos);
		return ret;
	}
	else
		return((php_var)false);
}		
