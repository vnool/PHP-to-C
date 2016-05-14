php_var stristr(php_var haystack, php_var needle)
{
	int pos = 0;
	php_var ret;
	string temp = (strtolower(haystack)).container;
	string temp2 = (strtolower(needle)).container;
	if((pos = temp.find(temp2)) != string::npos)
	{
		ret.type = PHP_STRING;
		ret.container = haystack.container.substr(pos, haystack.container.length() - pos);
		return ret;
	}
	else
		return((php_var)false);
}
