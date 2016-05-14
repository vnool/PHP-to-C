php_var substr(php_var str, php_var pos, php_var len)
{
	if(len == 0)
		len = str.container.length() - pos;
	return (php_var) str.container.substr(pos, len);
}
php_var substr(php_var str, long pos, long len)
{
	if(len == 0)
		len = str.container.length() - pos;
	return (php_var) str.container.substr(pos, len);
}