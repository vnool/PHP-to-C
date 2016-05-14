php_var strpos(php_var haystack, php_var needle, php_var pos = 0)
{
  	int ret;
  	if((ret = haystack.container.find(needle.container, (int)pos)) != string::npos)
  		return (php_var) ret;
	else
		return((php_var)false);
}		
