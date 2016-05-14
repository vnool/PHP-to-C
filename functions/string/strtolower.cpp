php_var strtolower(php_var str)
{
	for(int i = 0; i < str.container.length(); i++)
		str.container[i] = tolower(str.container[i]);

	return (php_var) str;
}
