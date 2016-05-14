php_var unlink(php_var file)
{
	if(unlink(file.container.c_str()) == 0) {
		return (php_var) true;
	}
	return (php_var) false;
}