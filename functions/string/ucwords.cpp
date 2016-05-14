php_var ucwords(php_var str)
{
	php_var arr = explode(" ", str);
	int i;
	for(i = 0; i < arr.keys.size(); ++i)
	{
		arr.data[i].container[0] = toupper(arr.data[i].container[0]);
	}
	return implode(" ", arr);
}
