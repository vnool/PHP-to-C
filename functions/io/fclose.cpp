php_var fclose(php_var handle)
{
	if(fclose((FILE *)handle.res)==0)
		return (php_var)true;
	return (php_var)false;
}