php_var fwrite(php_var handle, php_var str)
{
	return (php_var)fwrite((const char *)str,1,(unsigned int)strlen(str),(FILE *)handle.res);
}


php_var fwrite(php_var handle, php_var str, php_var len)
{
	return (php_var)fwrite((const char *)str,1,(unsigned int)len,(FILE *)handle.res);
}