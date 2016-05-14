php_var strlen(php_var str)
{
	return (php_var) str.container.length();
}
php_var strlen(string str)
{
	return (php_var) str.length();
}