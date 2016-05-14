php_var implode(php_var delim, php_var arr)
{
	php_var str;
	int i;
	for(i = 0; i < (arr.keys.size() - 1); ++i)
	{
		str += arr[i];
		str += delim;
	}
	str += arr[i];
	return str;
}
